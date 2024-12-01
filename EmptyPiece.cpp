#include "ChessPiece.h"
#include "EmptyPiece.h"
#include <iostream>

using namespace std;

// constructing empty piece
EmptyPiece::EmptyPiece() : ChessPiece() {};

// EmptyPiece destructor
EmptyPiece::~EmptyPiece() {};

void EmptyPiece::printPiece(ostream& os) {
	os << ". ";
};

bool EmptyPiece::isValidMove(char const move_from[2], char const move_to[2],
		ChessGame* cg) {
	return false; //trying to move emptypiece always false
}
