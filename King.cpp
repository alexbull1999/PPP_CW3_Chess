#include "ChessPiece.h"
#include "King.h"
#include <iostream>
#include <cstdlib> //for abs
#include <cstring>

using namespace std;

// King constructor - check is set to false by default; checked at start of each turn
King::King(Colour pieceColour, Name pieceName) : ChessPiece(pieceColour,
		pieceName) {};

//King destructor, temporarily printing destructed messages to see memory mgmt
King::~King() {};

//King clone method
ChessPiece* King::clone() const {
	return new King(*this); //Using default copy constructor for King
}

void King::printPiece(ostream& os) {
	if (pieceColour == Colour::BLACK) {
		os << "k ";
	}
	else if (pieceColour == Colour::WHITE) {
		os << "K ";
	}
};


bool King::isValidMove(char const move_from[2], char const move_to[2],
		ChessGame* cg, bool& isPieceTaken) {
	//first check if the king is castling as this is the exception case
	if(checkForCastlingMove(move_from, move_to, cg)) {
		return true;
	}

	//then check if the king is being moved only one square, as if the king
	//is not castling and not moving only one square the moved is defacto invalid
	//The below logic ensures we are also checking that the king is not moving 0
	//squares which would be invalid
	if (!(
				((abs(move_from[0] - move_to[0]) == 1) && 
				(abs(move_from[1] - move_to[1]) < 2)) || 
				((abs(move_from[1] - move_to[1]) == 1) &&
				 (abs(move_from[0] - move_to[0]) < 2))
				)) {
		//update isPieceTaken before returning false; as even if there was
		//an opponent piece in the move_to square, it won't be taken due to
		//invalid move (again making sure the bitwise enum works in submitMove)
		isPieceTaken = false;
		return false;
	}
	// else its a valid move, so we can update castling options, and return
	// true
	else {
		//we only need to updateCastlingOptions once, if the King is moving from
		//its home square
		if ((pieceColour == Colour::BLACK && !strcmp(move_from, "E8")) ||
				(pieceColour == Colour::WHITE && !strcmp(move_from, "E1"))) {
			updateCastlingOptions(pieceColour, cg);
		}
		return true; 
	}
}


void King::updateCastlingOptions(Colour kingColour, ChessGame* cg) {
	if (kingColour == Colour::BLACK) {
		//use bitwise and and not to update castlingOptions to show no
		//castling possibilities for black (clear bits 2 and 3)
		cg->castlingOptions &= ~0b1100; 
	}
	else if (kingColour == Colour::WHITE) {
		//Mirror logic but to disable white castling possibilities
		//(clear bits 0 and 1)
		cg->castlingOptions &= ~0b0011;
	}
}


//In my interpretation of castling; and from researching online it seems
//like only the King can initiate the castling move (i.e. it is always
//the 'king's' move, the also needs to move the rook)

//note we do not need to pass bool &isPieceTaken into this function, 
//because you are not allowed to take a piece when castling, and 
//isPieceTaken will by logic have been set to false, if this method returns true.
//Because this method checks that the squares the king is castling through are 
//empty

bool King::checkForCastlingMove(char const move_from[2], char const move_to[2], 
		ChessGame* cg) {
	//check if move is exactly 2 spaces long first moving only in file direction
	if (!((move_from[1] - move_to[1] == 0) && (abs(move_from[0] - move_to[0]) == 2))) {
		return false;
	}
	
	//now check if the correct castling options are available
	//option 1 black castling kingside
	if(!strcmp(move_to, "G8")) {
		if (!(cg->castlingOptions & 0b0100)) {
			return false; // as black kingside castling is unavailable
		}
		//check that the rook hasn't been taken that you are trying to
		//castle with (castlingOptions only updates if the Rook
		//moves, not if its taken)
		ChessPiece* cp = cg->getBoardPiece("H8");
		if(!(cp->pieceName == Name::ROOK && cp->pieceColour == Colour::BLACK)) {
			return false;
		}
		//Now we need to check that the King is not in check
		if (cg->squareUnderAttack("E8", Colour::BLACK)) {
			return false;
		}
		// Now we need to check that none of 
		// the squares the king will pass through will be under attack. We
		// can simultaneously check that the squares are also empty
		for (char file = 'F', rank = '8'; file < 'H'; file++) {
			char board_square[2] = {file, rank};
			if (cg->squareUnderAttack(board_square, Colour::BLACK) ||
					cg->getBoardPiece(board_square)) {
				return false;
			}
		}

		//If none of the above has returned false, then castling conditions
		//are satisfied and we can update the Rook's position here, and return
		//true, where the King's position will be updated in submitMove
		cg->updateBoard(cp, "H8", "F8");
		//disable all castling options for black
		updateCastlingOptions(Colour::BLACK, cg);
		return true;			
	}

	//option 2 black castling queenside
	if(!strcmp(move_to, "C8")) {
		if (!(cg->castlingOptions & 0b1000)) {
			return false; // as black queenside castling is unavailable
		}
		//check that the rook hasn't been taken that you are trying to
		//castle with (castlingOptions only updates if the Rook
		//moves, not if its taken)
		ChessPiece* cp = cg->getBoardPiece("A8");
		if(!(cp->pieceName == Name::ROOK && cp->pieceColour == Colour::BLACK)) {
			return false;
		}
		// Now we need to check the King is not in check
		if (cg->squareUnderAttack("E8", Colour::BLACK)) {
			return false;
		}
		// Now check that none  
		// the squares the king will pass through will be under attack
		for (char file = 'D', rank = '8'; file > 'B'; file--) {
			char board_square[2] = {file, rank};
			if (cg->squareUnderAttack(board_square, Colour::BLACK) ||
					cg->getBoardPiece(board_square)) {
				return false;
			}
		}
		//If none of the above has returned false, then castling conditions
		//are satisfied and we can update the Rook's position here, and return
		//true, where the King's position will be updated in submitMove
		cg->updateBoard(cp, "A8", "D8");
		//disable all castling options for black
		updateCastlingOptions(Colour::BLACK, cg);
		return true;			
	}

	//option 3 white castling kingside
	if(!strcmp(move_to, "G1")) {
		if (!(cg->castlingOptions & 0b0001)) {
			return false; // as white kingside castling is unavailable
		}
		//check that the rook hasn't been taken that you are trying to
		//castle with (castlingOptions only updates if the Rook
		//moves, not if its taken)
		ChessPiece* cp = cg->getBoardPiece("H1");
		if(!(cp->pieceName == Name::ROOK && cp->pieceColour == Colour::WHITE)) {
			return false;
		}
		// Now we need to check the King is not in check
		if (cg->squareUnderAttack("E1", Colour::WHITE)) {
			return false;
		}
		// Also check that none of 
		// the squares the king will pass through will be under attack
		for (char file = 'F', rank = '1'; file < 'H'; file++) {
			char board_square[2] = {file, rank};
			if (cg->squareUnderAttack(board_square, Colour::WHITE) ||
					cg->getBoardPiece(board_square)) {
				return false;
			}
		}
		//If none of the above has returned false, then castling conditions
		//are satisfied and we can update the Rook's position here, and return
		//true, where the King's position will be updated in submitMove
		cg->updateBoard(cp, "H1", "F1");
		//disable all castling options for white
		updateCastlingOptions(Colour::WHITE, cg);
		return true;			
	}
	
	//option 4 white castling queenside
	if(!strcmp(move_to, "C1")) {
		if (!(cg->castlingOptions & 0b0010)) {
			return false; // as white queenside castling is unavailable
		}
		//check that the rook hasn't been taken that you are trying to
		//castle with (castlingOptions only updates if the Rook
		//moves, not if its taken)
		ChessPiece* cp = cg->getBoardPiece("A1");
		if(!(cp->pieceName == Name::ROOK && cp->pieceColour == Colour::WHITE)) {
			return false;
		}
		// Now we need to check the King is not in check 
		if (cg->squareUnderAttack("E1", Colour::WHITE)) {
			return false;
		}
		// Also check that none of 
		// the squares the king will pass through will be under attack
		for (char file = 'D', rank = '1'; file > 'B'; file--) {
			char board_square[2] = {file, rank};
			if (cg->squareUnderAttack(board_square, Colour::WHITE) ||
					cg->getBoardPiece(board_square)) {
				return false;
			}
		}
		//If none of the above has returned false, then castling conditions
		//are satisfied and we can update the Rook's position here, and return
		//true, where the King's position will be updated in submitMove
		cg->updateBoard(cp, "A1", "D1");
		//disable all castling options for white
		updateCastlingOptions(Colour::WHITE, cg);
		return true;			
	}
	
	//castling conditions not fulfilled
	return false;
}


