#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

const int boardSize = 8;


class Piece {
  /**
   * General class for all pieces to inherit, with basic stats
  */
  public:
    char file; // current file the piece is on
    int rank; // current rank the piece is on
    char player; // which player the piece is
    int numOfMoves; // number of times the piece has moved

  public:
    Piece(char f, int r, char p){
      // Initializer
      file = f;
      rank = r;
      player = p;
      numOfMoves = 0;
    }

    Piece(){
      // Initializer for the 2d chessboard array
      file = ' ';
      rank = 0;
      player = ' ';
      numOfMoves = 0;
    }

    static int fileToIndex(char file){
      /**
       * @brief: Converts a file char to an index
       * @params: file - file the piece is on
      */
      return file - 97; // Char math magic
    }

    static int rankToIndex(int rank){
      /**
       * @brief: Converts a rank to an index, created for consistency
       * @params: rank - rank the piece is on
      */
      return rank - 1;
    }

    virtual string toString(){
      // Function that represents the pieces into strings
      if (player == 'w'){
        // If player is white
        return "w";
      } else if (player == 'b'){
        // If player is black
        return "b";
      } else {
        // If it's an empty square
        return "  ";
      }
    }

    bool isInRange(char file, int rank){
      /**
       * @brief: Checks if the piece is in range
       * @params: file - file of piece
       * @params: rank - rank of piece
      */
      string files = "abcdefgh"; // String with all the available files

      if (files.find(file) != -1){
        // If the file is within the string of available files
        if (rank >= 1 && rank <= 8){
          // If the it's in is valid
          return true;
        }
      }

      return false;
    }

    bool isTaking(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief: Checks if the piece is taking another piece
       * @params: toF - the file the piece is going to
       * @params: toR - the rank the piece is going to
       * @params: chessBoard - 2d array that stores the current position of the board
      */
      if (
        chessBoard[fileToIndex(toF)][rankToIndex(toR)]->toString() != " "
        &&
        chessBoard[fileToIndex(toF)][rankToIndex(toR)]->player !=
        chessBoard[fileToIndex(file)][rankToIndex(rank)]->player
      ){
        // If the position the piece is going to has a piece that's different to the position that is being moved from
        return true;
      }

      return false;
    }

    virtual bool isMoveValid(
      char toF, 
      int toR, 
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief: Checks if the current move is valid, this will get overridden by every piece, contains basic calculations
       * @params: toF - the file the piece is going to
       * @params: toR - the rank the piece is going to
       * @params: chessBoard - 2d array that stores the current position of the board
      */
      cout << rank << file << endl;
      cout << toR << toF << endl;
      cout << "Base check " << (chessBoard[rankToIndex(toR)][fileToIndex(toF)]->player != chessBoard[rankToIndex(rank)][fileToIndex(file)]->player) << endl;
      cout << "Range check " << isInRange(toF, toR) << endl;
      if (
        (
          chessBoard[rankToIndex(toR)][fileToIndex(toF)]->player !=
          chessBoard[rankToIndex(rank)][fileToIndex(file)]->player
        ) && isInRange(toF, toR)
      ){
        // Checks if the piece is going to a square that's in range, and if it's going to a square with a different colour piece
        if (toF != file || toR != rank){
          // Checks if the piece is going somewhere else
          return true;
        }
      }
      return false;
    }

};

class Pawn: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      // Adding to calling the base function from inherited class
      return Piece::toString() + 'P';
    }

    bool isDirectionValid(char toF, int toR){
      /**
       * @brief: Checks if the direction of the piece is valid
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
      */
      if (player == 'w' && toR > rank){
        // If player is white, it should move up the ranks
        return true;
      } else if (player == 'b' && toR < rank){
        // If player is black, it should move down the ranks
        return true;
      }
      return false;
    }

    bool isDistanceValid(char toF, int toR){
      if (rank == 2 || rank == 7){
        if (abs(toR - rank) < 3 && abs(toR - rank) > 0){
          return true;
        }
      } else {
        if (abs(toR - rank) == 1){
          return true;
        }
      }

      return false;
    }

    bool isMoveDiagonal(char toF, int toR){
      if (abs(toF - file) == 1 && abs(toR - file) == 1){
        return true;
      }

      return false;
    }

    int squaresMoved(char toF, int toR){
      return abs(toF - file) + abs(toR - rank);
    }

    bool isEnpassant(
      char toF, 
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (isMoveDiagonal(toF, toR) && squaresMoved(toF, toR) == 2){
        if (player == 'w' && rank == 6){
          if (chessBoard[rankToIndex(6)][fileToIndex(toF)]->numOfMoves == 1){
            return true;
          }
        } else if (player == 'b' && rank == 3){
          if (chessBoard[rankToIndex(3)][fileToIndex(toF)]->numOfMoves == 1){
            return true;
          }
        }
      }

      return false;
    }

    bool isIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (toR > rank){
        for (int i = rankToIndex(rank) + 1; i <= rankToIndex(toR); i++){
          if (chessBoard[i][fileToIndex(toF)]->player != 'e'){
            return true;
          }
        }
      } else {
        for (int i = rankToIndex(rank) - 1; i >= rankToIndex(toR); i--){
          if (chessBoard[i][fileToIndex(toF)]->player != 'e'){
            return true;
          }
        }
      }

      return false;
    }

    bool isMoveValid(
      char toF, 
      int toR, 
      Piece* chessBoard[boardSize][boardSize]
    ) override {
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        cout << "Base check passed" << endl;
        cout << "Directional check: " << isDirectionValid(toF, toR) << endl;
        cout << "Distance check: " << isDistanceValid(toF, toR) << endl;
        cout << "Interception check: " << isIntercepted(toF, toR, chessBoard) << endl;
        cout << "Taking check: " << isTaking(toF, toR, chessBoard) << endl;
        cout << "En passant check: " << isEnpassant(toF, toR, chessBoard) << endl;
        if (
          (
            isDirectionValid(toF, toR) && 
            isDistanceValid(toF, toR) && 
            !isIntercepted(toF, toR, chessBoard)
          ) || (
            isTaking(toF, toR, chessBoard) &&
            isMoveDiagonal(toF, toR)
          )
        ){
          return true;
        } else {
          if (isEnpassant(toF, toR, chessBoard)){
            return true;
          }
        }
      }

      return false;
    }
};

class Rook: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + 'R';
    }

    bool isDirectionValid(
      char toF,
      int toR
    ){
      if (toF == file || toR == rank){
        return true;
      }

      return false;
    }

    bool isIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (toF == file){
        if (toR > rank){
          for (int i = rankToIndex(rank) + 1; i < rankToIndex(toR); i++){
            if (chessBoard[i][fileToIndex(file)]->player != 'e'){
              return true;
            }
          }
        } else {
          for (int i = rankToIndex(rank) - 1; i > rankToIndex(toR); i--){
            if (chessBoard[i][fileToIndex(file)]->player != 'e'){
              return true;
            }
          }
        }
      } else if (toR == rank){
        if (toF > file){
          for (int i = fileToIndex(file); i < fileToIndex(toF); i++){
            if (chessBoard[rankToIndex(rank)][i]->player != 'e'){
              return true;
            }
          }
        } else {
          for (int i = rank - 1; i > rankToIndex(toR); i--){
            if (chessBoard[rankToIndex(rank)][i]->player != 'e'){
              return false;
            }
          }
        }
      }

      return false;
    }

    bool isMoveValid(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ) override {
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        if (
          isDirectionValid(toF, toR) && 
          !isIntercepted(toF, toR, chessBoard)
        ){
          return true;
        }
      }
      return false;
    }
};

class Knight: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + 'N';
    }

    bool isDirectionValid(
      char toF,
      int toR
    ){
      if (abs(toF - file) == 1 && abs(toR - rank) == 2){
        return true;
      } else if (abs(toF - file) == 2 && abs(toR - rank) == 1){
        return true;
      }
      return false;
    }

    bool isMoveValid(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (Piece::isMoveValid(toF, toR, chessBoard) && isDirectionValid(toF, toR)){
        return true;
      }

      return false;
    }
};

class Bishop: public Piece {
  using Piece::Piece;
  public:
    string toString() override {
      return Piece::toString() + "B";
    }

    bool isDirectionValid(
      char toF,
      int toR
    ){
      if (abs(toF-file) == abs(toR-rank)){
        return true;
      }

      return false;
    }

    bool isIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (toF - file > 0){
        // If going right
        for (int i = fileToIndex(file + 1); i < fileToIndex(toF); i++){
          if (toR - rank > 0){
            // Looping from one file to the right to toF
            for (int j = rankToIndex(rank + 1); j < rankToIndex(toR); j++){
              // Looping from one rank up to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          }
        }
      } else {
        // If going left
        for (int i = fileToIndex(file - 1); i > fileToIndex(toF); i--){
          if (toR - rank > 0){
            // Looping from one file to the right to toF
            for (int j = rankToIndex(rank + 1); j < rankToIndex(toR); j++){
              // Looping from one rank up to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          }
        }
      }

      return false;
    }

    bool isMoveValid(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ) override {
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        if (isDirectionValid(toF, toR) && !isIntercepted(toF, toR, chessBoard)){
          return true;
        }
      }

      return false;
    }
};

class Queen: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + "Q";
    }

    bool isStraightValid(
      char toF,
      int toR
    ){
      if (toF == file || toR == rank){
        return true;
      }

      return false;
    }

    bool isStraightIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (toF == file){
        if (toR > rank){
          for (int i = rankToIndex(rank) + 1; i < rankToIndex(toR); i++){
            if (chessBoard[i][fileToIndex(file)]->player != 'e'){
              return true;
            }
          }
        } else {
          for (int i = rankToIndex(rank) - 1; i > rankToIndex(toR); i--){
            if (chessBoard[i][fileToIndex(file)]->player != 'e'){
              return true;
            }
          }
        }
      } else if (toR == rank){
        if (toF > file){
          for (int i = fileToIndex(file); i < fileToIndex(toF); i++){
            if (chessBoard[rankToIndex(rank)][i]->player != 'e'){
              return true;
            }
          }
        } else {
          for (int i = rank - 1; i > rankToIndex(toR); i--){
            if (chessBoard[rankToIndex(rank)][i]->player != 'e'){
              return true;
            }
          }
        }
      }

      return false;
    }

    bool isDiagonalValid(
      char toF,
      int toR
    ){
      if (abs(toF-file) == abs(toR-rank)){
        return true;
      }

      return false;
    }

    bool isDiagonalIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      if (toF - file > 0){
        // If going right
        for (int i = fileToIndex(file + 1); i < fileToIndex(toF); i++){
          if (toR - rank > 0){
            // Looping from one file to the right to toF
            for (int j = rankToIndex(rank + 1); j < rankToIndex(toR); j++){
              // Looping from one rank up to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          }
        }
      } else {
        // If going left
        for (int i = fileToIndex(file - 1); i > fileToIndex(toF); i--){
          if (toR - rank > 0){
            // Looping from one file to the right to toF
            for (int j = rankToIndex(rank + 1); j < rankToIndex(toR); j++){
              // Looping from one rank up to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[j][i]->player != 'e'){
                  return true;
                }
              }
            }
          }
        }
      }

      return false;
    }



    bool isMoveValid(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ) override {
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        cout << "Straight Check " << isStraightValid(toF, toR) << endl;
        cout << "Straight interception " << isStraightIntercepted(toF, toR, chessBoard) << endl;
        if (
          isStraightValid(toF, toR) && 
          !isStraightIntercepted(toF, toR, chessBoard)
        ){
          return true;
        } else if (
          isDiagonalValid(toF, toR) && 
          !isDiagonalIntercepted(toF, toR, chessBoard)
        ){
          return true;
        }
      }

      return false;
    }
};

class King: public Piece {
  using Piece::Piece;
  public:
    string toString() override {
      return Piece::toString() + 'K';
    }
};

void makeBackgroundBlack(){
  cout << "\x1b[40m";
}

void makeBackgroundWhite(){
  cout << "\x1b[47m";
}

void printBlankSpaces(bool isStartingBlack){
  cout << "   ";
  for (int i = 0; i < 57; i++){
    if (i % 7 == 0){
      cout << "\x1b[0m";
      cout << '|';
    } else {
      if (isStartingBlack){
        if (i % 14 > 0 && i % 14 < 7){
          makeBackgroundBlack();
          cout << ' ';
        } else if (i % 14 > 7 && i % 14 != 0){
          makeBackgroundWhite();
          cout << ' ';
        }
      } else {
        if (i % 14 > 0 && i % 14 < 7){
          makeBackgroundWhite();
          cout << ' ';
        } else if (i % 14 > 7 && i % 14 != 0){
          makeBackgroundBlack();
          cout << ' ';
        }
      }
      if (i == 56){
        cout << '|';
      }
    }
  }
}

void printFiles(){
  string files = "abcdefgh";

  cout << "   ";

  for (int i = 0, j = 0; i < 57; i++){
    if (i % 7 == 3){
      cout << files[j];
      j++;
    } else {
      cout << ' ';
    }
  }

  cout << endl;
}

void printCurrentBoard(Piece* chessBoard[boardSize][boardSize]){
  bool isSquareBlack = false;
  bool isStartingBlack = false;

  printFiles();

  for (int y = 7; y >= 0; y--){
    cout << "   ";
    for (int i = 0; i < 57; i++){
        if (i % 7 == 0){
          cout << '+';
        } else {
          cout << "-";
        }
      }

    cout << endl;

    printBlankSpaces(isStartingBlack);

    cout << endl;
    cout << y + 1;
    cout << "  ";
    for (int x = 0; x < boardSize; x++){
      cout << "\x1b[0m";
      cout << '|';

      if (isSquareBlack){
        makeBackgroundBlack();
        cout << "  ";
        cout << "\x1b[37m";
        cout << chessBoard[y][x]->toString();
        cout << "  ";
      } else {
        makeBackgroundWhite();
        cout << "  ";
        cout << "\x1b[37m";
        cout << chessBoard[y][x]->toString();
        cout << "  ";
      }

      if (x == 7){
        cout << "\x1b[0m";
        cout << '|';
      }

      if (x != 7){
        isSquareBlack = !isSquareBlack;
      }
    }

    cout << "  ";
    cout << y + 1;
    cout << endl;

    printBlankSpaces(isStartingBlack);

    cout << endl;
    isStartingBlack = !isStartingBlack;

  }

  cout << "   ";
  for (int i = 0; i < 57; i++){
    if (i % 7 == 0){
      cout << '+';
    } else {
      cout << "-";
    }
  }

  cout << endl;
  
  printFiles();
}

bool isUnderCheck(
  Piece* chessBoard[boardSize][boardSize],
  char currentPlayer
){
  Piece* king;
  for (int r = 0; r < boardSize; r++){
    for (int f = 0; f < boardSize; f++){
      string currentPiece = chessBoard[r][f]->toString();
      if (currentPiece[0] == currentPlayer && currentPiece[1] == 'K'){
        king = chessBoard[r][f];
      }
    }
  }

  char opponentPlayer = currentPlayer == 'w' ? 'b' : 'w';

  for (int r = 0; r < boardSize; r++){
    for (int f = 0; f < boardSize; f++){
      Piece* currentPiece = chessBoard[r][f];
      if (currentPiece->player == opponentPlayer){
        if (currentPiece->isMoveValid(king->file, king->rank, chessBoard)){
          cout << "CHECK" << endl;
          cout << currentPiece->toString() << endl;
          cout << currentPiece->file << currentPiece->rank << endl;
          return true;
        }
      }
    }
  }

  return false;
}

void saveFen(
  Piece* chessBoard[boardSize][boardSize],
  char currentPlayer
){
  ofstream gameFens ("Fens.txt");

  if (gameFens.is_open()){
    for (int i = 0; i < boardSize; i++){
      string line = "";
      int emptySpaces = 0;
      for (int j = 0; j < boardSize; j++){
        if (chessBoard[i][j]->toString() == "  "){
          emptySpaces++;
        } else {
          char currentPiece = chessBoard[i][j]->toString()[1];
          if (chessBoard[i][j]->player == 'b'){
            if (emptySpaces > 0){
              line += emptySpaces + toupper(currentPiece);
            } else {
              line += toupper(currentPiece);
            }
          } else {
            if (emptySpaces > 0){
              line += emptySpaces + tolower(currentPiece);
            } else {
              line += tolower(currentPiece);
            }
          }
        }
        if (j == 7){
          if (emptySpaces > 0){
            line = "8";
          }
        }
      }
      gameFens << line;
      if (i < 7){
        gameFens << '/'; 
      }
    }
    gameFens << ' ' << currentPlayer;
  } else {
    cout << "\nERROR, FILE BROKEN" << endl;
  }
}

bool movePiece(
  Piece* (&chessBoard)[boardSize][boardSize],
  char &currentPlayer
){
  string fromSquare, toSquare;

  cout << "\nEnter the piece you want to move and where to move it to: ";
  cin >> fromSquare; // d2
  cin >> toSquare; // d4
  int fromR = fromSquare[1] - '0';
  int toR = toSquare[1] - '0';

  cout << "From indices " << Piece::rankToIndex(fromR) << Piece::fileToIndex(fromSquare[0]) << endl;

  Piece* movingPiece = chessBoard[Piece::rankToIndex(fromR)][Piece::fileToIndex(fromSquare[0])];

  Piece* destination = chessBoard[Piece::rankToIndex(toR)][Piece::fileToIndex(toSquare[0])];

  cout << fromR << toR << endl;
  cout << movingPiece->file << movingPiece->rank << endl;
  cout << movingPiece->toString() << endl;

  if (movingPiece->player == currentPlayer){
    cout << "Proper player" << endl;
    if (movingPiece->isMoveValid(toSquare[0], toR, chessBoard)){
      cout << "Valid Move" << endl;
      movingPiece->file = toSquare[0];
      movingPiece->rank = toR;
      chessBoard[Piece::rankToIndex(toR)][Piece::fileToIndex(toSquare[0])] = movingPiece;

      chessBoard[Piece::rankToIndex(fromR)][Piece::fileToIndex(fromSquare[0])] = new Piece(fromSquare[0], fromR, 'e'); 

      if (isUnderCheck(chessBoard, currentPlayer)){
        movingPiece->file = fromSquare[0];
        movingPiece->rank = fromR;
        chessBoard[Piece::rankToIndex(toR)][Piece::fileToIndex(toSquare[0])] = destination;
        chessBoard[Piece::rankToIndex(fromR)][Piece::fileToIndex(fromSquare[0])] = movingPiece;

        return false;
      }
    }
  } else {
    return false;
  }

  return true;
}

int main(){
  Piece* chessBoard[boardSize][boardSize];
  char currentPlayer = 'w';

  chessBoard[0][0] = new Rook('a', 1, 'w');
  chessBoard[0][1] = new Knight('b', 1, 'w');
  chessBoard[0][2] = new Bishop('c', 1, 'w');
  chessBoard[0][3] = new Queen('d', 1, 'w');
  chessBoard[0][4] = new King('e', 1, 'w');
  chessBoard[0][5] = new Bishop('f', 1, 'w');
  chessBoard[0][6] = new Knight('g', 1, 'w');
  chessBoard[0][7] = new Rook('h', 1, 'w');

  for (int i = 0; i < boardSize; i++){
    chessBoard[1][i] = new Pawn(97 + i, 2, 'w');
  }

  for (int i = 2; i < boardSize - 2; i++){
    for (int j = 0; j < boardSize; j++){
      chessBoard[i][j] = new Piece(97 + j, i + 1, 'e');
    }
  }

  for (int i = 0; i < boardSize; i++){
    chessBoard[6][i] = new Pawn(97 + i, 7, 'b');
  }

  chessBoard[7][0] = new Rook('a', 8, 'b');
  chessBoard[7][1] = new Knight('b', 8, 'b');
  chessBoard[7][2] = new Bishop('c', 8, 'b');
  chessBoard[7][3] = new Queen('d', 8, 'b');
  chessBoard[7][4] = new King('e', 8, 'b');
  chessBoard[7][5] = new Bishop('f', 8, 'b');
  chessBoard[7][6] = new Knight('g', 8, 'b');
  chessBoard[7][7] = new Rook('h', 8, 'b');

  while (true) {
    printCurrentBoard(chessBoard);
    cout << currentPlayer << endl;
    bool validMove = movePiece(chessBoard, currentPlayer);
    if (validMove){
      currentPlayer = currentPlayer == 'w' ? 'b' : 'w';
    } else {
      cout << "Invalid move" << endl;
    }
    cout << currentPlayer << endl;
    saveFen(chessBoard, currentPlayer);
  }
}