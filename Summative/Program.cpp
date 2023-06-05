#include <iostream>
#include <string>

using namespace std;

const int boardSize = 8;

void populateBoard(char (&chessBoard)[][boardSize]){
  chessBoard[0][0] = 'r';
  chessBoard[0][1] = 'n';
  chessBoard[0][2] = 'b';
  chessBoard[0][3] = 'q';
  chessBoard[0][4] = 'k';
  chessBoard[0][5] = 'b';
  chessBoard[0][6] = 'n';
  chessBoard[0][7] = 'r';

  for (int i = 0; i < boardSize; i++){
    chessBoard[1][i] = 'p';
  }

  for (int i = 2; i < boardSize - 2; i++){
    for (int j = 0; j < boardSize; j++){
      chessBoard[i][j] = 'e';
    }
  }

  for (int i = 0; i < boardSize; i++){
    chessBoard[6][i] = 'P';
  }

  chessBoard[7][0] = 'R';
  chessBoard[7][1] = 'N';
  chessBoard[7][2] = 'B';
  chessBoard[7][3] = 'Q';
  chessBoard[7][4] = 'K';
  chessBoard[7][5] = 'B';
  chessBoard[7][6] = 'N';
  chessBoard[7][7] = 'R';
}

void printChessBoard(char chessBoard[][boardSize]){
  for (int i = 7; i >= 0; i--){
    for (int j = 0; j < boardSize; j++){
      cout << chessBoard[i][j] << ' ';
    }
    cout << endl;
  }
}

int main(){
  char chessBoard[8][8];
  // Capital letters are BLACK
  // Lowercase letters are White
  // Empty squares are 'e'

  populateBoard(chessBoard);
  printChessBoard(chessBoard);
}