#include "ChessPiece.h"
#include "Rook.h"
#include <iostream>

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
		ChessGame* cg) {
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
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
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
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
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
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
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
			return true; 
		}
		// if move_to occupied by an opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
			return true;
		}
		// if move_to occupied by your own piece return false
		return false;
	}
	return false;
}



