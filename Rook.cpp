#include "ChessPiece.h"
#include "Rook.h"
#include <iostream>
#include <cstring>

using namespace std;

// Rook constructor
Rook::Rook(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour, 
		pieceName) {};

//Rook destructor, temporarily printing destructed messages to see memory mgmt
Rook::~Rook() {};

//Rook clone method
ChessPiece* Rook::clone() const {
	return new Rook(*this); //Using default copy constructor for Rook
}

void Rook::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "r ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "R ";
	}
};

bool Rook::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg, bool& isPieceTaken) {
	//check first if either the rank or the file of move_to is the same as move_from,
	//but not both
	if ((move_from[0] != move_to[0] && move_from[1] != move_to[1]) || 
			(move_from[0] == move_to[0] && move_from[1] == move_to[1])) {
		//update isPieceTaken to be false first, before returning - as it is an invalid
		//move regardless of whether move_to contains an opposing piece
		isPieceTaken = false;
		return false;
	}

	//Determine the direciton the Rook is moving in
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
	else if (move_to[0] < move_from[0]) {
		fileDirection = -1; //moving horizontally to the left
	}

	char checkFile = move_from[0] + fileDirection;
	char checkRank = move_from[1] + rankDirection;
	char checkSpace[2] = {checkFile, checkRank};
	
	/*Note, whilst if this Rook function was being used for a Rook
	we would not need to take care of checking the final move_to 
	square, because the isPieceTaken function takes care of this;
	we still need to check the final square, because of the Queen's
	multiple inheritance from the Bishop and Rook
	
	The Queen's return statement uses the logical or operator, checking
	if a move is valid using Bishop logic first, and Rook logic second
	That means, if the move is invalid via Bishop logic, isPieceTaken
	will have been reset to false by the Bishop, so if a piece is 
	actually being taken here by a Queen, we may need to reset it to be
	true.
	
	Whilst this is suboptimal, I would argue it is still more efficient
	than the inverse situation, where every piece class has to check an 
	additional final square; and where you lose the benefit in submitMove
	of very quickly returning invalid moves that land on a square of your
	own colour*/
	

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

	//check the final square and reset isPieceTaken to true, if there is
	//an opposing piece there (in case a Bishop had set it to false, when
	//this function is used by a Queen)
	
	if (cg->capturesPiece(move_from, move_to)) {
		isPieceTaken = true; //update if reset by Bishop, otherwise this stays the same
	}

	// at this point we know its a valid move, but before returning true we
	// need to check if we need to update any of the castlingOptions available
	if ((pieceColour == Colour::WHITE && (!strcmp(move_from, "A1") || !strcmp(move_from, "H1")))
			|| (pieceColour == Colour::BLACK && (!strcmp(move_from, "A8") || !strcmp(move_from, "H8")))) {
		updateCastlingOptions(move_from, pieceColour, cg);
	}
	return true;
}


	


/*
	//if rook is moving in increasing file direction 
	else if (move_from[0] < move_to[0]) {
		for (char file = move_from[0] + 1; file < move_to[0]; file++) {
			char checkSpace[2] = {file, move_from[1]};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// if move_to also empty return true
		if(!cg->getBoardPiece(move_to)) {
			//if the rook is moving from its home square we need to
			//updateCastlingOptions. This will only affect rooks
			//starting on A file, as we are checking increasing file direction
			if ((pieceColour == Colour::BLACK && !strcmp(move_from, "A8")) ||
					(pieceColour == Colour::WHITE && !strcmp(move_from, "A1"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece is taken
			//if the rook is moving from its home square we need to
			//updateCastlingOptions
			if ((pieceColour == Colour::BLACK && !strcmp(move_from, "A8")) ||
					(pieceColour == Colour::WHITE && !strcmp(move_from, "A1"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true;
		}
		// if move_to occupied by your own piece return false
		return false;
	}

	// if rook is moving in decreasing file direction
	else if (move_from[0] > move_to[0]) {
		for (char file = move_from[0] - 1; file > move_to[0]; file--) {
			char checkSpace[2] = {file, move_from[1]};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// if move_to also empty return true
		if(!cg->getBoardPiece(move_to)) {
			//if the rook is moving from its home square we need to
			//updateCastlingOptions - only applicable for rooks starting
			//on H-file given the direction of travel we are checking
			if ((pieceColour == Colour::BLACK && !strcmp(move_from, "H8")) ||
					(pieceColour == Colour::WHITE && !strcmp(move_from, "H1"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece is taken
			//if the rook is moving from its home square we need to
			//updateCastlingOptions
			if ((pieceColour == Colour::BLACK && !strcmp(move_from, "H8")) ||
					(pieceColour == Colour::WHITE && !strcmp(move_from, "H1"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true;
		}
		// if move_to occupied by your own piece return false
		return false;
	}

	// if rook is moving in increasing rank direction
	else if (move_from[1] < move_to[1]) {
		for (char rank = move_from[1] + 1; rank < move_to[1]; rank++) {
			char checkSpace[2] = {move_from[0], rank};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// if move_to also empty return true
		if(!cg->getBoardPiece(move_to)) {
			//if the rook is moving from its home square we need to
			//updateCastlingOptions - only affects white rooks here
			if (pieceColour == Colour::WHITE && (!strcmp(move_from, "A1") ||
					!strcmp(move_from, "H1"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece being taken
			//if the rook is moving from its home square we need to
			//updateCastlingOptions - only affects white rooks here
			if (pieceColour == Colour::WHITE && (!strcmp(move_from, "A1") ||
					!strcmp(move_from, "H1"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true;
		}
		// if move_to occupied by your own piece return false
		return false;
	}

	// if rook is moving in decreasing rank direction
	else if (move_from[1] > move_to[1]) {
		for (char rank = move_from[1] - 1; rank > move_to[1]; rank--) {
			char checkSpace[2] = {move_from[0], rank};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// if move_to also empty return true
		if(!cg->getBoardPiece(move_to)) {
			//if the rook is moving from its home square we need to
			//updateCastlingOptions - only affects black rooks here
			if (pieceColour == Colour::BLACK && (!strcmp(move_from, "A8") ||
					!strcmp(move_from, "H8"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece being taken
			//if the rook is moving from its home square we need to
			//updateCastlingOptions - only affects black rooks here
			if (pieceColour == Colour::BLACK && (!strcmp(move_from, "A8") ||
					!strcmp(move_from, "H8"))) {
				updateCastlingOptions(move_from, pieceColour, cg);
			}
			return true;
		}
		// if move_to occupied by your own piece return false
		return false;
	}
	return false;
}

*/

void Rook::updateCastlingOptions(char const move_from[2],
		Colour rookColour, ChessGame* cg) {
	//we need to check both what colour the rook is, and what side of
	//the king it is, to know which castlingOption to clear/disable
	if (rookColour == Colour::BLACK) {
		if (move_from[0] == 'A') {
			//disable black queenside castlingOptions
			cg->castlingOptions &= ~0b1000;
		}
		else if (move_from[0] == 'H') {
			//disable black kingside castling
			cg->castlingOptions &= ~0b0100;
		}
	}
	else if (rookColour == Colour::WHITE) {
		if (move_from[0] == 'A') {
			//disable white queenside castling
			cg->castlingOptions &= ~0b0010;
		}
		else if (move_from[0] == 'H') {
			//disable white kingside castling
			cg->castlingOptions &= ~0b0001;
		}
	}
}




