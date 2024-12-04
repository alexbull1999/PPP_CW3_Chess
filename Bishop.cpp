#include "ChessPiece.h"
#include "Bishop.h"
#include <iostream>
#include <cstdlib> //for abs() function

using namespace std;

// Bishop constructor
Bishop::Bishop(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour,
		pieceName) {};

//Bishop destructor, temporarily printing destructed messages to see memory mgmt
Bishop::~Bishop() {};

//Bishop clone method
ChessPiece* Bishop::clone() const {
	return new Bishop(*this); //Using default copy constructor for Bishop
}

void Bishop::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "b ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "B ";
	}
};

bool Bishop::isValidMove(char const move_from[2], char const move_to[2],
		ChessGame* cg, bool& isPieceTaken) {
	// bishops can only move diagonally, so a first way to check if a move is
	// valid is to see if the number of squares moved vertically and horizontally
	// are equal
	if (abs(move_from[0] - move_to[0]) != abs(move_from[1] - move_to[1]) ||
			(move_from[0] == move_to[0] && move_from[1] == move_to[1])) {
		return false;
	}
	//now we need to check that each tile it moves until its final position are
	////empty (the final position can have a piece if it is to be taken)
	
	//4 possible moves:
	////1) rank decreasing and file increasing
	if (move_to[0] > move_from[0] && move_to[1] < move_from[1]) {
		//check for empty spaces up until move_to
		for (char file = move_from[0] + 1, rank = move_from[1] - 1;
				file < move_to[0]; file++, rank--) {
			char checkSpace[2] = {file, rank};
			//if any of the board spaces the bishop traverses through are occupied, return false
			if(cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		//if move_to is also empty, return true
		if (!cg->getBoardPiece(move_to)) {
			return true;
		}
		//if move_to is occupied, check its occupied by an opposing piece
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece being taken
			return true;
		}
		return false;
	}

	//2) rank decreasing and file decreasing (mirroring above logic)
	else if (move_to[0] < move_from[0] && move_to[1] < move_from[1]) {
		for (char file = move_from[0] - 1, rank = move_from[1] - 1; 
				file > move_to[0]; rank--, file--) {
			char checkSpace[2] = {file, rank};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// move_to also empty
		if(!cg->getBoardPiece(move_to)) {
			return true; 
		}
		// move_to occupied by an opposing piece
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece being taken
			return true;
		}
		return false;
	}

	//3) rank increasing and file decreasing (mirroring above logic)
	else if (move_to[0] < move_from[0] && move_to[1] > move_from[1]) {
		for (char file = move_from[0] - 1, rank = move_from[1] + 1; 
				file > move_to[0]; rank++, file--) {
			char checkSpace[2] = {file, rank};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// if move_to also empty, return true
		if(!cg->getBoardPiece(move_to)) {
			return true;
		}
		// if move_to occupied by opposing piece return true
		else if(cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //Indicate piece being taken
			return true;
		}
		return false;
	}

	//4) rank increasing and file increasing (mirroring above logic)
	else if (move_to[0] > move_from[0] && move_to[1] > move_from[1]) {
		for (char file = move_from[0] + 1, rank = move_from[1] + 1; 
				file < move_to[0]; rank++, file++) {
			char checkSpace[2] = {file, rank};
			if (cg->getBoardPiece(checkSpace)) {
				return false;
			}
		}
		// if move_to also empty, return true
		if (!cg->getBoardPiece(move_to)) {
			return true;
		}
		// if move_to occupied by opposing piece return true
		else if (cg->capturesPiece(move_from, move_to)) {
			isPieceTaken = true; //indicate piece being taken
			return true;
		}
	}
	return false;
}
