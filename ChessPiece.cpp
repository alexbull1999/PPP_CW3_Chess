#include "ChessGame.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include <iostream>

using namespace std;

ChessPiece::ChessPiece(Colour pieceColour) :
	pieceColour(pieceColour) {};

// Chess Piece destructor
ChessPiece::~ChessPiece() {};

//Overloading of ostream for ChessPiece pointers
ostream& operator << (std::ostream& os, ChessPiece* cp) {
	if (cp != nullptr) {
		cp->printPiece(os);
	}
	else {
		os << ". ";
	}
	return os;
}

bool ChessPiece::isValidRookMove(char const move_from[2], char const move_to[2],
		ChessGame* cg, bool& isPieceTaken) {
	/* check first if either the rank or the file of move_to is the same as
	 * move_from, but not both */
	if ((move_from[0] != move_to[0] && move_from[1] != move_to[1]) ||
			(move_from[0] == move_to[0] && move_from[1] == move_to[1])) {
		/* update isPieceTaken to be false first, before returning - as it is an
		 * invalid move regardless of whether move_to contains an opposing piece */
		isPieceTaken = false;
		return false;
	}

	//Determine the direction the Rook is moving in
	int rankDirection;
	int fileDirection;
	if (move_to[1] > move_from[1]) {
		rankDirection = 1; //rook moving vertically up the board
	}
	else if (move_to[1] < move_from[1]) {
		rankDirection = -1; //rook moving vertically down the board
	}
	else {
		rankDirection = 0; //rook moving horizontally
	}

	if (rankDirection != 0) {
		fileDirection = 0; //if moving vertically, cannot move horizontally
	}
	else if (move_to[0] > move_from[0]) {
		fileDirection = 1; //moving horizontally to the right
	}
	else {
		fileDirection = -1; //moving horizontally to the left
	}

	char checkFile = move_from[0] + fileDirection;
	char checkRank = move_from[1] + rankDirection;
	char checkSpace[2] = {checkFile, checkRank};

	//iterate through the rook's path of movement checking for empty
	//squares

	while (checkSpace[0] != move_to[0] || checkSpace[1] != move_to[1]) {
		if (cg->getBoardPiece(checkSpace)) {
			//invalid move as it cannot cross a square containing a piece
			isPieceTaken = false;
			return false;
		}
		checkSpace[0] += fileDirection;
		checkSpace[1] += rankDirection;
	}

	if (cg->capturesPiece(move_from, move_to)) {
		isPieceTaken = true;
	}

	return true;
}

bool ChessPiece::isValidBishopMove(char const move_from[2], char const move_to[2],
		ChessGame* cg, bool& isPieceTaken) {
	/* bishops can only move diagonally, so a first way to check if a move is
	 * valid is to see if the number of squares moved vertically and horizontally
	 * are equal */
	if (abs(move_from[0] - move_to[0]) != abs(move_from[1] - move_to[1]) ||
			(move_from[0] == move_to[0] && move_from[1] == move_to[1])) {
		/* before returning false we need to update isPieceTaken. Regardless of
		 * move_to containing an enemy piece, no piece
		 * is being taken, because it is an invalid move */
		isPieceTaken = false;
		return false;
			}

	//Determine the vertical direction of movement
	int rankDirection = (move_to[1] > move_from[1]) ? 1 : -1;
	//Determine the horizontal direction of movement
	int fileDirection = (move_to[0] > move_from[0]) ? 1 : -1;

	/* Iterate through the diagonal the bishop is moving on to ensure all empty
	 * spaces - we don't need to check the final square, as that has been checked
	 * in submitMove already */
	for (char rank = move_from[1] + rankDirection,
			file = move_from[0] + fileDirection;
			rank != move_to[1] && file != move_to[0];
			rank += rankDirection, file += fileDirection) {

		char checkSpace[2] = {file, rank};
		//cg->getBoardPiece is only true if there is a piece (i.e. not a nullptr)
		if (cg->getBoardPiece(checkSpace)) {
			//Before returning false we need to update isPieceTaken to false
			isPieceTaken = false;
			return false;
		}
			}
	//If we reach this point the move is hence valid, and isPieceTaken takes care
	//of whether a piece has been taken or not
	return true;
}