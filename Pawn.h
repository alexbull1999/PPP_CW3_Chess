#ifndef PAWN_H
#define PAWN_H

#include "ChessPiece.h"

/* The Pawn class represents the Pawn pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list; but overrides the virtual methods 
 * declared to ensure they are appropriate for the Pawn context */

class Pawn : public ChessPiece {
	public:
		//Pawn Constructor
		Pawn(Colour pieceColour, Name pieceName);

		//Pawn clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Pawn
		bool isValidMove(char const move_from[2], char const move_to[2], 
				ChessGame* cg, bool& isPieceTaken) override; 
		
		void printPiece(std::ostream&) override;
		~Pawn() override;


};

#endif
