#include <iostream>
#include <utility>

using namespace std;

const int boardSize = 8;

class Piece{
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

    virtual bool isMoveValid(
      char toF, 
      int toR, 
      Piece* (&chessBoard)[boardSize][boardSize]
    ){
      return isInRange(toF, toR);
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
          isDirectionValid(toF, toR) && 
          isDistanceValid(toF, toR) && 
          !isIntercepted(toF, toR, chessBoard)
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
};

class Knight: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + "N";
    }
};

class Bishop: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + "B";
    }
};

class Queen: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + "Q";
    }
};

class King: public Piece {
  using Piece::Piece;
  public:
    string toString() override{
      return Piece::toString() + "K";
    }
};

void printCurrentBoard(Piece* chessBoard[boardSize][boardSize]){
  for (int y = 7; y >= 0; y--){
    for (int x = 0; x < boardSize; x++){
      cout << chessBoard[y][x]->toString() << ' ';
    }
    cout << endl;
  }
}

int main(){
  Piece* chessBoard[boardSize][boardSize];

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
    chessBoard[6][i] = new Pawn(97 + i, 6, 'w');
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
}