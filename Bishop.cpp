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
		//before returning false we need to update isPieceTaken so that submitMove
		//enum works. Regardless of move_to containing an enemy piece, no piece
		//is being taken, because it is an invalid move
		isPieceTaken = false;
		return false;
	}

	//Determine the vertical direction of movement  
	int rankDirection = (move_to[1] > move_from[1]) ? 1 : -1;
	//Determine the horizontal direction of movement
	int fileDirection = (move_to[0] > move_from[0]) ? 1 : -1;

	//Iterate through the diagonal the bishop is moving on to ensure all empty
	//spaces - we don't need to check the final square, as that has been checked
	//in submitMove already
	for (char rank = move_from[1] + rankDirection, file = move_from[0] + fileDirection;
			rank != move_to[1] && file != move_to[0]; rank += rankDirection, file += fileDirection) {
		char checkSpace[2] = {file, rank};
		if (cg->getBoardPiece(checkSpace)) {
			//cg->getBoardPiece is only true if there is a piece in that square
			//Before returning false we need to update isPieceTaken to false
			isPieceTaken = false;
			return false; 
		}
	}
	//If we reach point the move is valid, and isPieceTaken takes care of whether
	//a piece has been taken or not
	return true;
}


