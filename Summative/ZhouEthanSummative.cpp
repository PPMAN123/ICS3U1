#include <iostream>
#include <utility>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <ctype.h>

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

    Piece(Piece* p){
      file = p->file;
      rank = p->rank;
      player = p->player;
      numOfMoves = p->numOfMoves;
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

    bool isEnpassant(
      char toF, 
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      return false;
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
        chessBoard[rankToIndex(toR)][fileToIndex(toF)]->player != 'e'
        &&
        (
          chessBoard[rankToIndex(toR)][fileToIndex(toF)]->player !=
        chessBoard[rankToIndex(rank)][fileToIndex(file)]->player
        )
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
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board
      */

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

  /**
   * Class for logic of pawns
   */

  public:
    string toString() override {
      // Creating the string representation of a pawn
      return Piece::toString() + 'P';
    }

    bool isDirectionValid(char toF, int toR){
      /**
       * @brief Checks if the direction of the piece is valid
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns a boolean that is true when the direction of the pawn is valid
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
      /**
       * @brief Checks if the pawn's distance is valid
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns a boolean that is true when the distance is valid for the pawn
       */
      if (file == toF){
        if (rank == 2 || rank == 7){
          // If the pieces are at starting squares
          if (abs(toR - rank) <= 2 && abs(toR - rank) > 0){
            // You can move up to 2 spaces forward
            return true;
          }
        } else {
          // If pawn is not on starting square
          if (abs(toR - rank) == 1){
            // Can only move 1 rank up
            return true;
          }
        }
      }

      return false;
    }

    bool isMoveDiagonal(char toF, int toR){
      /**
       * @brief Checks if the pawn is moving diagonally forward
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns a boolean that is true when the pawn is moving diagonally
       */
      if (abs(toF - file) == 1 && abs(toR - rank) == 1){
        return true;
      }

      return false;
    }

    int squaresMoved(char toF, int toR){
      /**
       * @brief Function that returns the amount of squares the pawn moved (don't kno w why it's here, but it works, so I'm not changing anything)
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns an integer that has the total amount of displacement the piece did
       */
      return abs(toF - file) + abs(toR - rank);
    }

    bool isEnpassant(
      char toF, 
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief Checks if the pawn is doing an en-passant (HOLY HELL!1!1!)
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board
       * @returns a boolean that is true when the pawn is doing an en passant
       */
      if (isMoveDiagonal(toF, toR) && squaresMoved(toF, toR) == 2){
        // If the pawn is moving diagnoally by 1 square up and sideways
        if (player == 'w' && rank == 5){
          // If player is white, it can only happen on rank 5
          if (
            chessBoard[rankToIndex(5)][fileToIndex(toF)]->numOfMoves == 1 &&
            chessBoard[rankToIndex(5)][fileToIndex(toF)]->toString()[1] == 'P'
          ){
            // If the piece that's next to the pawn doing the en passant is it's first move, and if it's a pawn, you can en passant
            return true;
          }
        } else if (player == 'b' && rank == 4){
          // If player is black, it can only happen on rank 4
          if (chessBoard[rankToIndex(4)][fileToIndex(toF)]->numOfMoves == 1){
            // If the piece that's next to the pawn doing the en passant is it's first move, and if it's a pawn, you can en passant
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
      /**
       * @brief Function that checks if the pawn is blocked by something in front
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the pawn is blocked
       */
      if (toR > rank){
        // If the pawn is going up the ranks
        for (int i = rankToIndex(rank) + 1; i <= rankToIndex(toR); i++){
          // Loop until the rank it wants to go to
          if (chessBoard[i][fileToIndex(toF)]->player != 'e'){
            // If there's a square that isn't empty, it's intercepted
            return true;
          }
        }
      } else {
        // Same logic except it's for when the pawn is going down the ranks
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
      /**
       * @brief Overridden function that checks if the move is valid for a pawn
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the move is valid
       */
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        // Base check
        if (
          (
            isDirectionValid(toF, toR) && 
            isDistanceValid(toF, toR) && 
            !isIntercepted(toF, toR, chessBoard)
          ) || (
            isTaking(toF, toR, chessBoard) &&
            isMoveDiagonal(toF, toR) &&
            isDirectionValid(toF, toR)
          )
        ){
          // If the direction, distance are valid and it's not intercepted, or if the pawn is taking something and is moving diagonally, it's valid
          return true;
        } else {
          if (isEnpassant(toF, toR, chessBoard)){
            // If it's en passanting, return valid as well (made because en passant breaks a lot of the normal pawn rules)
            return true;
          }
        }
      }

      return false;
    }
};

class Rook: public Piece {
  using Piece::Piece;
  /**
   * Class that has the logic for rooks
   */
  public:
    string toString() override {
      // String representation of a rook
      return Piece::toString() + 'R';
    }

    bool isDirectionValid(
      char toF,
      int toR
    ){
      /**
       * @brief Checks if the direction of the rook is valid
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns a boolean that is true when the direction of the rook is valid
       */
      if (toF == file || toR == rank){
        // Either the file stays the same, or the rank stays the same
        return true;
      }

      return false;
    }

    bool isIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief If the rook's path is intercepted by another piece
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the rook is intercepted
       */

      if (toF == file){
        // When its going sideways
        if (toR > rank){
          // If it's going up the ranks
          for (int i = rankToIndex(rank) + 1; i < rankToIndex(toR); i++){
            // Loop up to the square before it's going to
            if (chessBoard[i][fileToIndex(file)]->player != 'e'){
              // If there's a square that isn't empty, return true
              return true;
            }
          }
        } else {
          // If it's going down the ranks, logic below is the same as above, except going down ranks
          for (int i = rankToIndex(rank) - 1; i > rankToIndex(toR); i--){
            if (chessBoard[i][fileToIndex(file)]->player != 'e'){
              return true;
            }
          }
        }
      } else if (toR == rank){
        // If it's going up and down
        // Logic is the same as above, except loops through file indexes instead of rank
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
      /**
       * @brief Overridden function that checks if the move is valid for a rook
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the move is valid
       */
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        // Base check
        if (
          isDirectionValid(toF, toR) && 
          !isIntercepted(toF, toR, chessBoard)
        ){
          // If the direction is valid, and it's not intercepted, return true
          return true;
        }
      }
      return false;
    }
};

class Knight: public Piece {
  using Piece::Piece;

  /**
   * Class that handles logic of a knight
   */
  public:
    string toString() override{
      // String representation of a knight
      return Piece::toString() + 'N';
    }

    bool isDirectionValid(
      char toF,
      int toR
    ){
      /**
       * @brief Checks if the direction of the knight is valid
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns a boolean that is true when the direction of the knight is valid
       */
      if (abs(toF - file) == 1 && abs(toR - rank) == 2){
        // If the file changes by 1, and rank by 2, it's an L shape
        return true;
      } else if (abs(toF - file) == 2 && abs(toR - rank) == 1){
        // If file changes by 2, and rank by 1, it's an L shape
        return true;
      }
      return false;
    }

    bool isMoveValid(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief Overridden function that checks if the move is valid for a knight
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the move is valid
       */
      if (Piece::isMoveValid(toF, toR, chessBoard) && isDirectionValid(toF, toR)){
        // If base check passed and if the direction is valid
        return true;
      }

      return false;
    }
};

class Bishop: public Piece {
  using Piece::Piece;
  public:
    string toString() override {
      // String representation of the bishop
      return Piece::toString() + "B";
    }

    bool isDirectionValid(
      char toF,
      int toR
    ){
      /**
       * @brief Checks if the direction of the bishop is valid
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @returns a boolean that is true when the direction of the knight is valid
       */
      if (abs(toF-file) == abs(toR-rank)){
        // If the file and the rank difference is equal, it's going diagonal
        return true;
      }

      return false;
    }

    bool isIntercepted(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief Checks if the bishop is intercepted on its way to the destination square
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board
       * @returns a boolean that is true when the bishop is intercepted
      */

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
      /**
       * @brief Overridden function that checks if the move is valid for a Bishop
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the move is valid
       */
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        if (isDirectionValid(toF, toR) && !isIntercepted(toF, toR, chessBoard)){
          // If direction is valid and not intercepted, it's a valid move
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
      // String representation of the queen
      return Piece::toString() + "Q";
    }

    bool isStraightValid(
      char toF,
      int toR
    ){
      // The isDirectionValid function stolen from the rook
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
      // The isIntercepted function from the rook
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
      // The isDirectionValid function from the bishop
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
      // The isIntercepted function from the bishop
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
      /**
       * @brief Overridden function that checks if the move is valid for a Queen
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the move is valid
       */
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        if (
          isStraightValid(toF, toR) && 
          !isStraightIntercepted(toF, toR, chessBoard)
        ){
          // If it's moving like a rook, it's valid
          return true;
        } else if (
          isDiagonalValid(toF, toR) && 
          !isDiagonalIntercepted(toF, toR, chessBoard)
        ){
          // Or if it's moving like a bishop, it's valid
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
      // String representation of the king
      return Piece::toString() + 'K';
    }

    bool isMoveValid(
      char toF,
      int toR,
      Piece* chessBoard[boardSize][boardSize]
    ){
      /**
       * @brief Overridden function that checks if the move is valid for a King
       * @params: toF - file the piece is going to
       * @params: toR - rank the piece is going to
       * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
       * @returns a boolean that is true when the move is valid
       */
      if (Piece::isMoveValid(toF, toR, chessBoard)){
        if (abs(toF - file) <= 1 && abs(toR - rank) <= 1){
          // If the file and rank moves less or equal to one square, it's valid (Base check already checks for if it's moving to same position)
          return true;
        }
      }

      return false;
    }
};

void makeBackgroundBlack(){
  // Helper function to print the board, makes background black
  cout << "\x1b[40m";
}

void makeBackgroundWhite(){
  // Helper function to print the board, makes background white
  cout << "\x1b[47m";
}

void printBlankSpaces(bool isStartingBlack){
  /**
   * @brief A helper function that prints the empty filler spaces within the chess board
   * @params: isStartingBlack - boolean that keeps track if the starting grid of the row is black
  */

  cout << "   "; // Spacer

  for (int i = 0; i < 57; i++){
    // 57 square wide
    if (i % 7 == 0){
      // Every 7 spaces, print a bar
      cout << "\x1b[0m"; // Resets the background colours
      cout << '|';
    } else {
      if (isStartingBlack){
        // If it starts with black
        if (i % 14 > 0 && i % 14 < 7){
          // Makes the grid black, and prints empty spaces
          makeBackgroundBlack();
          cout << ' ';
        } else if (i % 14 > 7 && i % 14 != 0){
          // Makes the grid white, and prints empty spaces
          makeBackgroundWhite();
          cout << ' ';
        }
      } else {
        // If it starts with white, flip the operations
        if (i % 14 > 0 && i % 14 < 7){
          makeBackgroundWhite();
          cout << ' ';
        } else if (i % 14 > 7 && i % 14 != 0){
          makeBackgroundBlack();
          cout << ' ';
        }
      }
      if (i == 56){
        // Print a bar at the end of every line
        cout << '|';
      }
    }
  }
}

void printFiles(){
  /**
   * @brief Prints the files of the board
  */

  string files = "abcdefgh"; // String of all the files

  cout << "   "; // Spacer

  for (int i = 0, j = 0; i < 57; i++){
    // 57 Wide grid

    if (i % 7 == 3){
      // When it's at the middle of the square
      cout << files[j]; // Print the current file
      j++; // Increment iterator for the string
    } else {
      cout << ' '; // Print an empty square when it's not in the middle of a square
    }
  }

  cout << endl;
}

void printCurrentBoard(Piece* chessBoard[boardSize][boardSize]){
  /**
   * @brief Function that prints out the chess board
   * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
   */

  bool isSquareBlack = false;
  bool isStartingBlack = false;

  printFiles(); // Print the files of the chess board

  for (int y = 7; y >= 0; y--){
    // Prints out the borders
    cout << "   "; // Spacer
    for (int i = 0; i < 57; i++){
      // 57 Wide board
      if (i % 7 == 0){
        // Every 7 spaces, print edge
        cout << '+';
      } else {
        // Otherwise, print a dash
        cout << "-";
      }
    }

    cout << endl;

    printBlankSpaces(isStartingBlack); // Print the blank spaces

    cout << endl;

    cout << y + 1; // Print the ranks
    cout << "  ";

    for (int x = 0; x < boardSize; x++){
      // Loop through the pieces
      cout << "\x1b[0m"; // Print a normal bar
      cout << '|';

      if (isSquareBlack){
        // If square is black
        makeBackgroundBlack();

        // Print the piece text in white text
        cout << "  ";
        cout << "\x1b[37m";
        cout << chessBoard[y][x]->toString();
        cout << "  ";
      } else {
        // If square is white
        makeBackgroundWhite();

        // Print the piece text in black text
        cout << "  ";
        cout << "\x1b[37m";
        cout << chessBoard[y][x]->toString();
        cout << "  ";
      }

      if (x == 7){
        // Print a normal bar in the end
        cout << "\x1b[0m";
        cout << '|';
      }

      if (x != 7){
        // Swap the colours
        isSquareBlack = !isSquareBlack;
      }
    }

    cout << "  ";
    cout << y + 1;
    cout << endl;

    printBlankSpaces(isStartingBlack);

    cout << endl;
    isStartingBlack = !isStartingBlack; // Swap the starting grid colour
  }

  cout << "   ";
  for (int i = 0; i < 57; i++){
    // Print edge on the end
    if (i % 7 == 0){
      cout << '+';
    } else {
      cout << "-";
    }
  }

  cout << endl;
  
  printFiles(); // Print the files again
}

bool isUnderCheck(
  Piece* chessBoard[boardSize][boardSize],
  char currentPlayer
){
  /**
   * @brief Checks if the current player is under check
   * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
   * @params: currentPlayer - char the keeps track of the current player
   * @returns a boolean that is true when the current player is under check
   */
  Piece* king;
  for (int r = 0; r < boardSize; r++){
    for (int f = 0; f < boardSize; f++){
      // Find the king of the current player on the board
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
          // If an opponent piece can take the king, it is under check
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
  /**
   * @brief Saves the current position in FEN notation
   * @params: chessBoard - 2d pointer array of pieces that stores the current position of the board 
   * @params: currentPlayer - char the keeps track of the current player
   */

  ofstream gameFens ("Fens.txt");
  string position = ""; // String that keeps track of what to input into the text file

  if (gameFens.is_open()){
    for (int r = 7; r >= 0; r--){
      // Loop through the ranks of the chess board
      int emptySpaces = 0; // Integer that keeps track of the empty spaces
      for (int f = 0; f < boardSize; f++){
        // Loop through the files of the chessboard
        if (chessBoard[r][f]->player == 'w'){
          // If piece is white
          if (emptySpaces > 0){
            // If empty spaces are more than zero, add it to the string
            position += to_string(emptySpaces);
            emptySpaces = 0;
          }
          position += toupper(chessBoard[r][f]->toString()[1]); // Add upper case of current piece to the string
        } else if (chessBoard[r][f]->player == 'b'){
          // Same logic but for black pieces
          if (emptySpaces > 0){
            position += to_string(emptySpaces);
            emptySpaces = 0;
          }
          position += tolower(chessBoard[r][f]->toString()[1]); // Add lower case of current piece to string
        } else {
          emptySpaces++; // If it's an empty space, increment counter of empty spaces
        }

        if (f == 7){
          // If reached the end of the rank
          if (emptySpaces > 0){
            position += to_string(emptySpaces); // Add emtpy spaces count to the string if it's more than 0
            emptySpaces = 0; // Reset number of empty spaces
          }
        }
      }
      position += '/'; // Add a forward slash after every rank
    }

    gameFens << position; // Write position into file
    gameFens << ' ' << currentPlayer; // Write current player after
    gameFens.close();
  } else {
    // If file won't open
    cout << "\nERROR, FILE BROKEN" << endl;
  }
}

int menu(){
  int choice;
  cout << "\nWelcome to Ethan's Chess game" << endl;
  cout << "\n1) Load game" << endl;
  cout << "\n2) Start new game" << endl;
  cout << "\n3) Read the rules" << endl;
  cout << "\n4) Exit" << endl;

  do{
    cout << "\nMake your choice (1-4): ";
    cin >> choice;
    if (choice < 1 || choice > 4){
      cout << "\nInvalid option!" << endl;
    }
  } while (choice < 1 || choice > 4);

  return choice;
}

bool castleLong(
  Piece* (&chessBoard)[boardSize][boardSize],
  char &currentPlayer
){
  if (currentPlayer == 'w'){
    Piece* king = chessBoard[0][4];
    Piece* rook = chessBoard[0][0];
    if (
      king->player == 'w' && 
      rook->player == 'w' && 
      king->toString()[1] == 'K' 
      && rook->toString()[1] == 'R'
    ){
      if (
        chessBoard[0][1]->player == 'e' && 
        chessBoard[0][2]->player == 'e' &&
        chessBoard[0][3]->player == 'e'
      ){
        if (chessBoard[0][0]->numOfMoves == 0 && 
            chessBoard[0][4]->numOfMoves == 0
        ){
          rook->file = 'd';
          king->file = 'c';

          chessBoard[0][0] = new Piece('a', 1, 'e');
          chessBoard[0][4] = new Piece('e', 1, 'e');

          chessBoard[0][2] = king;
          chessBoard[0][3] = rook;

          if (isUnderCheck(chessBoard, currentPlayer)){
            rook->file = 'a';
            king->file = 'e';

            chessBoard[0][0] = rook;
            chessBoard[0][4] = king;

            chessBoard[0][1] = new Piece('b', 1, 'e');
            chessBoard[0][2] = new Piece('c', 1, 'e');
            chessBoard[0][3] = new Piece('d', 1, 'e');

            return false;
          } else {
            chessBoard[0][2]->numOfMoves++;
            chessBoard[0][3]->numOfMoves++;

            return true;
          }
        }
      }
    }
  } else if (currentPlayer == 'b'){
    Piece* king = chessBoard[7][4];
    Piece* rook = chessBoard[7][0];
    if (
      king->player == 'b' && 
      rook->player == 'b' &&
      king->toString()[1] == 'K' &&
      rook->toString()[1] == 'R'
    ){
      if (chessBoard[7][1]->player == 'e' && 
          chessBoard[7][2]->player == 'e' &&
          chessBoard[7][3]->player == 'e'
      ){
        if (chessBoard[7][0]->numOfMoves == 0 && 
            chessBoard[7][4]->numOfMoves == 0
        ){
          rook->file = 'd';
          king->file = 'c';

          chessBoard[7][0] = new Piece('a', 1, 'e');
          chessBoard[7][4] = new Piece('e', 1, 'e');

          chessBoard[7][2] = king;
          chessBoard[7][3] = rook;

          if (isUnderCheck(chessBoard, currentPlayer)){
            rook->file = 'a';
            king->file = 'e';

            chessBoard[7][0] = rook;
            chessBoard[7][4] = king;

            chessBoard[7][1] = new Piece('b', 8, 'e');
            chessBoard[7][2] = new Piece('c', 8, 'e');
            chessBoard[7][3] = new Piece('d', 8, 'e');

            return false;
          } else {
            chessBoard[7][2]->numOfMoves++;
            chessBoard[7][3]->numOfMoves++;

            return true;
          }
        }
      }
    }
  }

  return false;
}

bool castleShort(
  Piece* (&chessBoard)[boardSize][boardSize],
  char &currentPlayer
){
  if (currentPlayer == 'w'){
    Piece* king = chessBoard[0][4];
    Piece* rook = chessBoard[0][7];
    if (
      king->player == 'w' && 
      rook->player == 'w' && 
      king->toString()[1] == 'K' 
      && rook->toString()[1] == 'R'
    ){
      if (chessBoard[0][6]->player == 'e' && 
          chessBoard[0][5]->player == 'e'
      ){
        if (chessBoard[0][7]->numOfMoves == 0 && 
            chessBoard[0][4]->numOfMoves == 0
        ){
          rook->file = 'f';
          king->file = 'g';

          chessBoard[0][7] = new Piece('a', 1, 'e');
          chessBoard[0][4] = new Piece('e', 1, 'e');

          chessBoard[0][6] = king;
          chessBoard[0][5] = rook;

          if (isUnderCheck(chessBoard, currentPlayer)){
            rook->file = 'h';
            king->file = 'e';

            chessBoard[0][7] = rook;
            chessBoard[0][4] = king;

            chessBoard[0][5] = new Piece('f', 1, 'e');
            chessBoard[0][6] = new Piece('g', 1, 'e');
            return false;
          } else {
            chessBoard[0][6]->numOfMoves++;
            chessBoard[0][5]->numOfMoves++;

            return true;
          }
        }
      }
    }
  } else if (currentPlayer == 'b'){
    Piece* king = chessBoard[7][4];
    Piece* rook = chessBoard[7][7];
    if (
      king->player == 'b' && 
      rook->player == 'b' &&
      king->toString()[1] == 'K' &&
      rook->toString()[1] == 'R'
    ){
      if (chessBoard[7][6]->player == 'e' && 
          chessBoard[7][5]->player == 'e'
      ){
        if (chessBoard[7][7]->numOfMoves == 0 && 
            chessBoard[7][4]->numOfMoves == 0
        ){
          rook->file = 'f';
          king->file = 'g';

          chessBoard[7][7] = new Piece('a', 8, 'e');
          chessBoard[7][4] = new Piece('e', 8, 'e');

          chessBoard[7][6] = king;
          chessBoard[7][5] = rook;

          if (isUnderCheck(chessBoard, currentPlayer)){
            rook->file = 'h';
            king->file = 'e';

            chessBoard[7][7] = rook;
            chessBoard[7][4] = king;

            chessBoard[7][5] = new Piece('f', 8, 'e');
            chessBoard[7][6] = new Piece('g', 8, 'e');

            return false;
          } else {
            chessBoard[7][6]->numOfMoves++;
            chessBoard[7][5]->numOfMoves++;

            return true;
          }
        }
      }
    }
  }

  return false;
}

string lowerString(
  string inputString
){
  // Helper function that lower cases an entire string
  string newString = "";
  for (int i = 0; i < inputString.length(); i++){
    newString += tolower(inputString[i]);
  }

  return newString;
}

bool movePiece(
  Piece* (&chessBoard)[boardSize][boardSize],
  char &currentPlayer
){
  string fromSquare, toSquare;

  cout << "\nEnter the piece you want to move and where to move it to: ";
  cin >> fromSquare; // d2
  cin >> toSquare; // d4

  if (fromSquare != lowerString("castle")){
    int fromR = fromSquare[1] - '0';
    int toR = toSquare[1] - '0';

    cout << "From indices " << Piece::rankToIndex(fromR) << Piece::fileToIndex(tolower(fromSquare[0])) << endl;

    Piece* movingPiece = chessBoard[Piece::rankToIndex(fromR)][Piece::fileToIndex(tolower(fromSquare[0]))];

    Piece* destination = chessBoard[Piece::rankToIndex(toR)][Piece::fileToIndex(tolower(toSquare[0]))];

    if (movingPiece->player == currentPlayer){
      if (movingPiece->isMoveValid(tolower(toSquare[0]), toR, chessBoard)){
        movingPiece->file = tolower(toSquare[0]);
        movingPiece->rank = toR;
        chessBoard[Piece::rankToIndex(toR)][Piece::fileToIndex(tolower(toSquare[0]))] = movingPiece;

        chessBoard[Piece::rankToIndex(fromR)][Piece::fileToIndex(tolower(fromSquare[0]))] = new Piece(tolower(fromSquare[0]), fromR, 'e'); 

        if (movingPiece->toString()[1] == 'P'){
          if (movingPiece->player == 'w'){
            chessBoard[Piece::rankToIndex(toR) - 1][Piece::fileToIndex(tolower(toSquare[0]))] = new Piece(tolower(fromSquare[0]), fromR - 1, 'e');
          } else if (movingPiece->player == 'b'){
            chessBoard[Piece::rankToIndex(toR) + 1][Piece::fileToIndex(tolower(toSquare[0]))] = new Piece(tolower(fromSquare[0]), fromR + 1, 'e');
          }
        }

        if (isUnderCheck(chessBoard, currentPlayer)){
          movingPiece->file = tolower(fromSquare[0]);
          movingPiece->rank = fromR;
          chessBoard[Piece::rankToIndex(toR)][Piece::fileToIndex(tolower(toSquare[0]))] = destination;
          chessBoard[Piece::rankToIndex(fromR)][Piece::fileToIndex(tolower(fromSquare[0]))] = movingPiece;

          return false;
        } else {
          movingPiece->numOfMoves++;
        }
      } else {
        return false;
      }
    } else {
      return false;
    }
  } else {
    if (toSquare == lowerString("long")){
      return castleLong(chessBoard, currentPlayer);
    } else if (toSquare == lowerString("short")){
      return castleShort(chessBoard, currentPlayer);
    } else {
      return false;
    }
  }

  return true;
}

bool isCheckmate(
  Piece* chessBoard[boardSize][boardSize],
  char currentPlayer
){
  char opponentPlayer = currentPlayer == 'w' ? 'b' : 'w';

  if (isUnderCheck(chessBoard, opponentPlayer)){
    for (int r = 0; r < boardSize; r++){
      for (int f = 0; f < boardSize; f++){
        Piece* currentPiece = chessBoard[r][f];
        cout << "CURRENT MOVING PIECE FOR TESTING CHECKMATE" << currentPiece->toString() << r << f << endl;
        if (currentPiece->player == opponentPlayer){
          for (int toR = 0; toR < boardSize; toR++){
            for (int toF = 0; toF < boardSize; toF++){
              Piece* targetPiece = chessBoard[toR][toF];
              if (currentPiece->isMoveValid(toF + 97, toR + 1, chessBoard)){
                currentPiece->file = toF + 97;
                currentPiece->rank = toR + 1;

                chessBoard[toR][toF] = currentPiece;
                chessBoard[r][f] = new Piece(f + 97, r + 1, 'e');
                bool checkStatus = isUnderCheck(chessBoard, opponentPlayer);
                
                currentPiece->file = f + 97;
                currentPiece->rank = r + 1;
                chessBoard[r][f] = currentPiece;
                chessBoard[toR][toF] = targetPiece;

                if (!checkStatus){
                  return false;
                }
              }
            }
          }
        }
      }
    }

    return true;
  }

  return false;
}

void readFen(
  Piece* (&chessBoard)[boardSize][boardSize],
  char &currentPlayer
){
  ifstream gameFens ("Fens.txt");
  string boardLayout;

  if (gameFens.is_open()){
    gameFens >> boardLayout;
    gameFens >> currentPlayer;

    char player;

    for (int i = 0, r = 7, f = 0; i < boardLayout.length(); i++){
      if (boardLayout[i] == '/'){
        r--;
        f = 0;
      } else if (isdigit(boardLayout[i])){
        for (int j = f; j < f + (boardLayout[i] - '0'); j++){
          chessBoard[r][j] = new Piece(j + 97, r + 1, 'e');
        }

        f += (boardLayout[i] - '0');
      } else {
        if (isupper(boardLayout[i])){
          player = 'w';
        } else {
          player = 'b';
        }

        switch(toupper(boardLayout[i])){
          case 'P':
            chessBoard[r][f] = new Pawn(f + 97, r + 1, player);
            break;
          case 'N':
            chessBoard[r][f] = new Knight(f + 97, r + 1, player);
            break;
          case 'R':
            chessBoard[r][f] = new Rook(f + 97, r + 1, player);
            break;
          case 'B':
            chessBoard[r][f] = new Bishop(f + 97, r + 1, player);
            break;
          case 'Q':
            chessBoard[r][f] = new Queen(f + 97, r + 1, player);
            break;
          case 'K':
            chessBoard[r][f] = new King(f + 97, r + 1, player);
            break;
        }

        f++;
      }

    }

  } else {
    cout << "\nERROR OPENING FILE" << endl;
  }

}

void initializeBoard(Piece* (&chessBoard)[boardSize][boardSize]){
  // Initializes the board

  // Puts the white pieces where they go
  chessBoard[0][0] = new Rook('a', 1, 'w');
  chessBoard[0][1] = new Knight('b', 1, 'w');
  chessBoard[0][2] = new Bishop('c', 1, 'w');
  chessBoard[0][3] = new Queen('d', 1, 'w');
  chessBoard[0][4] = new King('e', 1, 'w');
  chessBoard[0][5] = new Bishop('f', 1, 'w');
  chessBoard[0][6] = new Knight('g', 1, 'w');
  chessBoard[0][7] = new Rook('h', 1, 'w');

  for (int i = 0; i < boardSize; i++){
    // Puts the white pawns where they go
    chessBoard[1][i] = new Pawn(97 + i, 2, 'w');
  }

  for (int i = 2; i < boardSize - 2; i++){
    for (int j = 0; j < boardSize; j++){
      // Puts the empty spaces in the middle
      chessBoard[i][j] = new Piece(97 + j, i + 1, 'e');
    }
  }

  for (int i = 0; i < boardSize; i++){
    // Puts the black pawns on rank 7
    chessBoard[6][i] = new Pawn(97 + i, 7, 'b');
  }

  // Puts the black pieces where they go
  chessBoard[7][0] = new Rook('a', 8, 'b');
  chessBoard[7][1] = new Knight('b', 8, 'b');
  chessBoard[7][2] = new Bishop('c', 8, 'b');
  chessBoard[7][3] = new Queen('d', 8, 'b');
  chessBoard[7][4] = new King('e', 8, 'b');
  chessBoard[7][5] = new Bishop('f', 8, 'b');
  chessBoard[7][6] = new Knight('g', 8, 'b');
  chessBoard[7][7] = new Rook('h', 8, 'b');
}

void printRules(){
  // Function that prints out the rules of the game

  // system("CLS"); // For windows
  system("clear"); // For linux
  char confirm;

  cout << "RULES OF ETHAN'S CHESS" << endl;
  cout << "\n1. When moving a piece, type in the square of the piece, then type in the square of where it should go to" << endl;
  cout << "\n2. Win by checkmate" << endl;
  cout << "\n3. There's no promotions (I'm a bad programmer)" << endl;

  // Lets the user move on by typing in a char
  cout << "\nType any key to continue: ";
  cin >> confirm;
}

bool menuSwitch(
  Piece* (&chessBoard)[boardSize][boardSize],
  char &currentPlayer
){
  // system("CLS"); // For Windows
  system("clear"); // For linux
  
  switch(menu()){
    case 1:
      readFen(chessBoard, currentPlayer);
      break;
    case 2:
      initializeBoard(chessBoard);
      break;
    case 3:
      printRules();
      menuSwitch(chessBoard, currentPlayer);
      break;
    case 4:
      return true;
      break;
  }

  return false;
}

int main(){
  Piece* chessBoard[boardSize][boardSize]; // 2D array of chess board
  char currentPlayer = 'w'; // Char that keeps track of current player
  
  if (menuSwitch(chessBoard, currentPlayer)){
    // Quits game if user wants to quit
    return 0;
  }

  bool isGameOver = false; // Keeps track of game status
  bool validMove = true; // Keeps track of move validity

  while (!isGameOver) {
    // system("CLS"); // For windows
    system("clear"); // For linux

    printCurrentBoard(chessBoard);
    saveFen(chessBoard, currentPlayer);

    if (!validMove){
      cout << "\nINVALID MOVE" << endl;
    }

    if (currentPlayer == 'w'){
      cout << "\nWHITE TO PLAY" << endl;
    } else {
      cout << "\nBLACK TO PLAY" << endl;
    }
    
    validMove = movePiece(chessBoard, currentPlayer);
    if (validMove){
      // If move is valid, check if game is over
      isGameOver = isCheckmate(chessBoard, currentPlayer);
      currentPlayer = currentPlayer == 'w' ? 'b' : 'w';
    }
  }

  // system("CLS"); // For Windows
  system("clear"); // For linux

  if (currentPlayer == 'b'){
    // Since I change the players after, the players are flipped
    cout << "WHITE WINS" << endl;
  } else{
    cout << "BLACK WINS" << endl;
  }
}