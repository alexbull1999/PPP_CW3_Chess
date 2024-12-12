#include "ChessPiece.h"
#include "Rook.h"
#include <iostream>
#include <cstring>

using namespace std;

// Rook constructor
Rook::Rook(Colour pieceColour) : ChessPiece(pieceColour) {};

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

//Getter for the piece name, returning a string literal representing the name of a piece
const char* Rook::getPieceName() const { return "Rook"; }

bool Rook::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg, bool& isPieceTaken) {

	if (isValidRookMove(move_from, move_to, cg, isPieceTaken)) {
		// at this point we know its a valid move, need to check if we need to update any of the castlingOptions
		if ((pieceColour == Colour::WHITE && (!strcmp(move_from, "A1")|| !strcmp(move_from, "H1")))
			|| (pieceColour == Colour::BLACK &&(!strcmp(move_from, "A8") || !strcmp(move_from, "H8")))) {
			updateCastlingOptions(move_from, pieceColour, cg);
			}
		return true;
	}
	return false;
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




