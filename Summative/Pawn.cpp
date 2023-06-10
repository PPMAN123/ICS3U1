#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <stdlib.h>

using namespace std;

const int boardSize = 8;

class Piece {
  public:
    char file;
    int rank;
    char player;
    int numOfMoves;

  public:
    Piece(char f, int r, char p){
      file = f;
      rank = r;
      player = p;
      numOfMoves = 0;
    }

    Piece(){
      file = ' ';
      rank = 0;
      player = ' ';
      numOfMoves = 0;
    }

    virtual string toString(){
      if (player == 'w'){
        return "w";
      } else if (player == 'b'){
        return "b";
      } else {
        return "  ";
      }
    }

    int fileToIndex(char file){
      return file - 97;
    }

    int rankToIndex(int rank){
      return rank - 1;
    }

    bool isInRange(char file, int rank){
      string files = "abcdefgh";

      if (files.find(file) != -1){
        if (rank >= 1 && rank <= 8){
          return true;
        }
      }

      return false;
    }

    bool isTaking(
      char toF,
      int toR,
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (
        chessBoard[fileToIndex(toF)][rankToIndex(toR)]->toString() != " "
        &&
        chessBoard[fileToIndex(toF)][rankToIndex(toR)]->player !=
        chessBoard[fileToIndex(file)][rankToIndex(rank)]->player
      ){
        return true;
      }

      return false;
    }

    virtual bool isMoveValid(
      char toF, 
      int toR, 
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (
        (
          chessBoard[fileToIndex(toF)][rankToIndex(toR)]->player !=
          chessBoard[fileToIndex(file)][rankToIndex(rank)]->player
        ) && isInRange(toF, toR)
      ){
        if (toF != file || toR != rank){
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
      return Piece::toString() + "P";
    }

    bool isDirectionValid(char toF, int toR){
      if (player == 'w' && toR > rank){
        return true;
      } else if (player == 'b' && toR < rank){
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
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (isMoveDiagonal(toF, toR) && squaresMoved(toF, toR) == 2){
        if (player == 'w' && rank == 6){
          if (chessBoard[fileToIndex(toF)][rankToIndex(6)]->numOfMoves == 1){
            return true;
          }
        } else if (player == 'b' && rank == 3){
          if (chessBoard[fileToIndex(toF)][rankToIndex(3)]->numOfMoves == 1){
            return true;
          }
        }
      }

      return false;
    }

    bool isIntercepted(
      char toF,
      int toR,
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (toR > rank){
        for (int i = rankToIndex(rank) + 1; i <= rankToIndex(toR); i++){
          if (chessBoard[fileToIndex(toF)][i]->player != ' '){
            return true;
          }
        }
      } else {
        for (int i = rankToIndex(rank) - 1; i >= rankToIndex(toR); i--){
          if (chessBoard[fileToIndex(toF)][i]->player != ' '){
            return true;
          }
        }
      }

      return false;
    }

    bool isMoveValid(
      char toF, 
      int toR, 
      Piece* (&chessBoard)[boardSize][boardSize]
    ) override {
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        if (
          (
            isDirectionValid(toF, toR) && 
            isDistanceValid(toF, toR) && 
            !isIntercepted(toF, toR, chessBoard)
          ) || isTaking(toF, toR, chessBoard)
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
      return Piece::toString() + "R";
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
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (toF == file){
        if (toR > rank){
          for (int i = rank + 1; i < rankToIndex(toR); i++){
            if (chessBoard[fileToIndex(file)][i]->toString() != "  "){
              return false;
            }
          }
        } else {
          for (int i = rank - 1; i > rankToIndex(toR); i--){
            if (chessBoard[fileToIndex(file)][i]->toString() != "  "){
              return false;
            }
          }
        }
      } else if (toR == rank){
        if (toF > file){
          for (int i = fileToIndex(file); i < fileToIndex(toF); i++){
            if (chessBoard[i][rankToIndex(rank)]->toString() != "  "){
              return false;
            }
          }
        } else {
          for (int i = rank - 1; i > rankToIndex(toR); i--){
            if (chessBoard[i][rankToIndex(rank)]->toString() != "  "){
              return false;
            }
          }
        }
      }

      return true;
    }

    bool isMoveValid(
      char toF,
      int toR,
      Piece* (&chessBoard)[boardSize][boardSize]
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
      return Piece::toString() + "N";
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
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (Piece::isMoveValid(toF, toR, chessBoard) && isDirectionValid(toF, toR)){
        return true;
      }
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
      Piece* (&chessBoard)[boardSize][boardSize]
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
                if (chessBoard[i][j]->toString() != "  "){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[i][j]->toString() != "  "){
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
                if (chessBoard[i][j]->toString() != "  "){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[i][j]->toString() != "  "){
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
      Piece* (&chessBoard)[boardSize][boardSize]
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
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      if (toF == file){
        if (toR > rank){
          for (int i = rank + 1; i < rankToIndex(toR); i++){
            if (chessBoard[fileToIndex(file)][i]->toString() != "  "){
              return false;
            }
          }
        } else {
          for (int i = rank - 1; i > rankToIndex(toR); i--){
            if (chessBoard[fileToIndex(file)][i]->toString() != "  "){
              return false;
            }
          }
        }
      } else if (toR == rank){
        if (toF > file){
          for (int i = fileToIndex(file); i < fileToIndex(toF); i++){
            if (chessBoard[i][rankToIndex(rank)]->toString() != "  "){
              return false;
            }
          }
        } else {
          for (int i = rank - 1; i > rankToIndex(toR); i--){
            if (chessBoard[i][rankToIndex(rank)]->toString() != "  "){
              return false;
            }
          }
        }
      }

      return true;
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
      Piece* (&chessBoard)[boardSize][boardSize]
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
                if (chessBoard[i][j]->toString() != "  "){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[i][j]->toString() != "  "){
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
                if (chessBoard[i][j]->toString() != "  "){
                  return true;
                }
              }
            }
          } else {
            for (int j = rankToIndex(rank - 1); j > rankToIndex(toR); j--){
              // Looping from one rank down to toR
              if (abs(i - fileToIndex(file)) == abs(j - rankToIndex(rank))){
                // If it's on diagonal of piece
                if (chessBoard[i][j]->toString() != "  "){
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
      Piece* (&chessBoard)[boardSize][boardSize]
    ) override {
      if (Piece::isMoveValid(toF, toR, chessBoard)){
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
    string toString() override{
      return Piece::toString() + "K";
    }
};

void makeBackgroundBlack(){
  cout << "\x1b[40m";
}

void makeBackgroundWhite(){
  cout << "\x1b[47m";
}

void printBlankSpaces(bool isStartingBlack){
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

void printCurrentBoard(Piece* chessBoard[boardSize][boardSize]){

  bool isSquareBlack = false;
  bool isStartingBlack = false;

  for (int y = 7; y >= 0; y--){
    for (int i = 0; i < 57; i++){
        if (i % 7 == 0){
          cout << '+';
        } else {
          cout << "─";
        }
      }

    cout << endl;

    printBlankSpaces(isStartingBlack);

    cout << endl;

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
    cout << endl;

    printBlankSpaces(isStartingBlack);

    cout << endl;
    isStartingBlack = !isStartingBlack;

  }

  for (int i = 0; i < 57; i++){
    if (i % 7 == 0){
      cout << '+';
    } else {
      cout << "─";
    }
  }

  cout << endl;
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
    chessBoard[6][i] = new Pawn(97 + i, 6, 'b');
  }

  chessBoard[7][0] = new Rook('a', 8, 'b');
  chessBoard[7][1] = new Knight('b', 8, 'b');
  chessBoard[7][2] = new Bishop('c', 8, 'b');
  chessBoard[7][3] = new Queen('d', 8, 'b');
  chessBoard[7][4] = new King('e', 8, 'b');
  chessBoard[7][5] = new Bishop('f', 8, 'b');
  chessBoard[7][6] = new Knight('g', 8, 'b');
  chessBoard[7][7] = new Rook('h', 8, 'b');

  printCurrentBoard(chessBoard);
  saveFen(chessBoard, currentPlayer);
}