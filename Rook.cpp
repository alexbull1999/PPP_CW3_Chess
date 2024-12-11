#include "ChessPiece.h"
#include "Rook.h"
#include <iostream>
#include <cstring>

using namespace std;

// Rook constructor
Rook::Rook(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour, 
		pieceName) {};

//Rook destructor
Rook::~Rook() {};

//Rook clone method invoked in the ChessGame copy constructor
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

	/* Note, if this function was being used for a Rook piece
	we would not need to take care of checking the final move_to 
	square, because the isPieceTaken function takes care of this.
	But, we actually do still need to check the final square, 
	because of the Queen's multiple inheritance from the Bishop and Rook
	
	The Queen's return statement uses the logical or operator, checking
	if a move is valid using Bishop logic first, and Rook logic second
	
	That means, if the move is invalid via Bishop logic, isPieceTaken
	will have been reset to false by the Bishop, so if a piece is 
	actually being taken here by a Queen using the Rook's logic, 
	we may need to reset it to be true.
	
	Whilst this extra check is suboptimal, I would argue it is still more 
	efficient than the inverse situation of not using the isPieceTaken
	reference parameter, where every piece class would have to check 
	an additional final square; and where you lose the benefit in submitMove
	of very quickly returning invalid moves that land on a square of your
	own colour */

	// For the above reasons, check the final square and reset isPieceTaken to 
	// true, if there is an opposing piece there (in case a Bishop had set it to 
	// false, when this function is used by a Queen)
	
	if (cg->capturesPiece(move_from, move_to)) {
		isPieceTaken = true; 
	}

	// at this point we know its a valid move, but before returning true we
	// need to check if we need to update any of the castlingOptions
	if ((pieceColour == Colour::WHITE && 
				(!strcmp(move_from, "A1") || !strcmp(move_from, "H1")))
			|| (pieceColour == Colour::BLACK && 
				(!strcmp(move_from, "A8") || !strcmp(move_from, "H8")))) {
		updateCastlingOptions(move_from, pieceColour, cg);
	}
	return true;
}


void Rook::updateCastlingOptions(char const move_from[2],
		Colour rookColour, ChessGame* cg) {
	//we need to check both what colour the rook is, and what side of
	//the king it is, to know which castlingOption todisable
	if (rookColour == Colour::BLACK) {
		if (move_from[0] == 'A') {
			//disable black queenside castlingOptions
			cg->castlingOptions &= ~CASTLE_BLACK_QUEENSIDE;
		}
		else if (move_from[0] == 'H') {
			//disable black kingside castling
			cg->castlingOptions &= ~CASTLE_BLACK_KINGSIDE;
		}
	}
	else if (rookColour == Colour::WHITE) {
		if (move_from[0] == 'A') {
			//disable white queenside castling
			cg->castlingOptions &= ~CASTLE_WHITE_QUEENSIDE;
		}
		else if (move_from[0] == 'H') {
			//disable white kingside castling
			cg->castlingOptions &= ~CASTLE_WHITE_KINGSIDE;
		}
	}
}




