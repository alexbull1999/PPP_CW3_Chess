#include "ChessPiece.h"
#include "Knight.h"
#include <iostream>
#include <cstdlib> //for abs function

using namespace std;

// Knight constructor
Knight::Knight(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour, 
		pieceName) {};

//Knight destructor, temporarily printing destructed messages to see memory mgmt
Knight::~Knight() {};

//Knight clone method
ChessPiece* Knight::clone() const {
	return new Knight(*this); //Using default copy constructor for Knight
}

void Knight::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "n ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "N ";
	}
};

bool Knight::isValidMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg) {
	//check to make sure that either it is moving 2 squares horizontally and 1
	//square vertically, or vice versa (no other combo is legal)
	if (!(((abs(move_from[0] - move_to[0]) == 2) && (abs(move_from[1] - move_to[1]) == 1)) 
				|| ((abs(move_from[0] - move_to[0]) == 1) && (abs(move_from[1] - move_to[1]) == 2)))
				) {
		return false;
	}
	// if move_to is empty; valid move
	else if(!cg->getBoardPiece(move_to)) {
		return true; 
	}
	// if move_to occupied by an opposing piece; valid move
	else if (cg->capturesPiece(move_from, move_to)) {
		return true;
	}
	// else (e.g. if move_to occupied by your piece) invalid move
	return false;
}


