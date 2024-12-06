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
		return false;
	}
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




