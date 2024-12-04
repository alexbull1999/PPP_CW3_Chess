#include "ChessPiece.h"
#include "Pawn.h"
#include <iostream>

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

	//isPieceTaken ref parameter starts by default as false from submitMove call
	
	//If a Pawn is not taking another piece it can only move straight forward
	//by 1 space normally, or by 2 if from starting position
	if(pieceColour == Colour::BLACK) {
		//check staying in same file
		if(move_from[0] == move_to[0]) {
			//moving one space forward is valid, if that space is empty
			if(move_from[1] - move_to[1] == 1) {
				//if the space is empty, getBoardPiece returns a nullptr which evaluates to false
				if(!cg->getBoardPiece(move_to)) {
					return true;
				}
			}
			//moving two spaces forward is valid, if both empty and from start 
			else if(move_from[1] == '7' && move_from[1] - move_to[1] == 2) {
				char  move_past[2];
				move_past[0] = move_to[0];
				move_past[1] = move_to[1] + 1;
				if(!cg->getBoardPiece(move_past) && !cg->getBoardPiece(move_to)) {
					return true;
				}
			}			
		}
		//handle the possibility of a pawn moving diagonally to take a piece
		if(abs(move_from[0] - move_to[0]) == 1 && move_from[1] - move_to[1] == 1) {
			if(cg->capturesPiece(move_from, move_to)) {
				//update isPieceTaken to indicate piece being taken
				isPieceTaken = true;
				return true;
			}
		}
		return false;
	}

	if(pieceColour == Colour::WHITE) {
		//mirror logic for black but switching move_to and move_from
		if(move_from[0] == move_to[0]) {
			if(move_to[1] - move_from[1] == 1) {
				if(!cg->getBoardPiece(move_to)) {
					return true;
				}
			}
			else if(move_from[1] == '2' && move_to[1] - move_from[1] == 2) {
				char move_past[2];
				move_past[0] = move_to[0];
				move_past[1] = move_to[1] - 1;
				if(!cg->getBoardPiece(move_past) && !cg->getBoardPiece(move_to)) {
					return true;
				}
			}
		}
		//mirror logic for a white pawn taking a piece
		if(abs(move_from[0] - move_to[0]) == 1 && move_to[1] - move_from[1] == 1) {
			if(cg->capturesPiece(move_from, move_to)) {
				isPieceTaken = true;
				return true;
			}
		}
	}
	return false;
}

