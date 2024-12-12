#include "ChessPiece.h"
#include "Pawn.h"
#include <iostream>
#include <cstdlib> //for abs function

using namespace std;

// Pawn constructor
Pawn::Pawn(Colour pieceColour) : ChessPiece(pieceColour) {};

//Pawn destructor
Pawn::~Pawn() {};

//Pawn clone method invoked in the ChessGame copy constructor
ChessPiece* Pawn::clone() const {
	return new Pawn(*this);
}

void Pawn::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "p ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "P ";
	}
};

//Getter for the piece name, returning a string literal representing
//the name of a piece
const char* Pawn::getPieceName() const { return "Pawn"; }


bool Pawn::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg) {

	//Black pawns can only move down the board (rank wise), white pawns only
	//up the board.
	int pawnDirection = (pieceColour == Colour::BLACK) ? -1 : 1;

	/* We can first check for Pawn captures, to handle diagonal moves */
	ChessPiece* targetPiece = cg->getBoardPiece(move_to);

	//we already check in submitMove that targetPiece cannot be of Pawn's
	//own colour so don't need to check again here
	if (targetPiece != nullptr) {
		//check pawn moves diagonally by only one square, in the right direction
		if(abs(move_from[0] - move_to[0]) == 1 && 
				(move_to[1] - move_from[1]) == pawnDirection) {
			return true; //valid diagonal capture
		}
		return false;
	}

	//now handle the cases where the pawn is not taking a piece, and hence they
	//can only move vertically
	if (move_from[0] != move_to[0]) {
		return false; //as they are not moving only vertically
	}

	/* Handle single square forward moves. We do not need to check if the
		 * move_to square is empty, as if it had not been empty, we would
		 * have gone down the target piece if branch ...*/
	if (move_to[1] - move_from[1] == pawnDirection) {
		return true;
	}

	//handle two square forward move from starting position
	char startingRank = (pieceColour == Colour::BLACK) ? '7' : '2';
	if (((move_to[1] - move_from[1]) == (pawnDirection * 2)) &&
	    move_from[1] == startingRank) {
		/*we don't need to check the move_to square (as handled by above
		 *if branch) but we do need to check the middle square the Pawn moves
		 *through to make sure its empty */
		char move_through_file = move_from[0];
		char move_through_rank = move_from[1] + pawnDirection;
		char move_through[2] = {move_through_file, move_through_rank};
		if(cg->getBoardPiece(move_through)) {
			return false; //cannot move through a board piece
		}
		return true;
	}
	//the above branches cover all valid pawn moves, so reaching this 
	//means it is an invalid pawn move
	return false;
}




