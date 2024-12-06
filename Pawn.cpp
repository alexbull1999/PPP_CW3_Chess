#include "ChessPiece.h"
#include "Pawn.h"
#include <iostream>
#include <cstdlib> //for abs function

using namespace std;

// Pawn constructor
Pawn::Pawn(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour, 
		pieceName) {};

//Pawn destructor, temporarily printing destructed messages to see memory mgmt
Pawn::~Pawn() {};

//Pawn clone method
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

//CHECK AFTER IF better to combine into fewer if statements for efficiency?
bool Pawn::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg, bool& isPieceTaken) {

	//Black pawns can only move down the board (rank wise), white pawns only
	//up the board. We al
	int pawnDirection = (pieceColour == Colour::BLACK) ? -1 : 1;

	//We can first use the isPieceTaken parameter to handle Pawn captures
	//If isPieceTaken is set to true from submitMove, we know there should be
	//a capture move we need to check the validity of
	if (isPieceTaken) {
		//ensure the pawn is moving diagonally by only one square, and in the right direction
		if(abs(move_from[0] - move_to[0]) == 1 && (move_to[1] - move_from[1]) == pawnDirection) {
			return true; //valid diagonal capture
		}
		else {
			//update isPieceTaken to be false, as it is an invalid diagonal capture 
			//and an invalid move
			isPieceTaken = false;
			return false;
		}
	}
	//now handle the cases where the pawn is not taking a piece, and hence they
	//can only move vertically
	else {
		if (move_from[0] != move_to[0]) {
			return false; //as they are not moving only vertically
		}

		//handle single square forward move
		//we do not need to check if the move_to square is empty, as if it had not
		//been empty, isPieceTaken would be set to true, and we would not have gone
		//down this code branch...
		if (move_to[1] - move_from[1] == pawnDirection) {
			return true;
		}

		//handle two square forward move from starting position
		char startingRank = (pieceColour == Colour::BLACK) ? '7' : '2';
		if (((move_to[1] - move_from[1]) == (pawnDirection * 2)) && 
				move_from[1] == startingRank) {
			//we don't need to check the move_to square (as handled by isPieceTaken)
			//but we do need to check the middle square the Pawn moves through
			char move_through_file = move_from[0];
			char move_through_rank = move_from[1] + pawnDirection;
			char move_through[2] = {move_through_file, move_through_rank};
			if(cg->getBoardPiece(move_through)) {
				return false; //cannot move through a board piece 
			}
			else {
				return true;
			}
		}
	}
	//the above if/else branches cover all possible pawn options, so reaching this
	//code means an invalid pawn move
	return false;
}




