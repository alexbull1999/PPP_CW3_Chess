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
		Pawn(Colour pieceColour);

		//Pawn clone method
		ChessPiece* clone() const override final;

		//isValidMove declaration for Pawn
		bool isValidMove(char const move_from[2], char const move_to[2], 
				ChessGame* cg) override final;
		
		void printPiece(std::ostream&) override final;

		//Getter for the piece name, returning a string literal representing the name of a piece
		const char* getPieceName() const override;

		~Pawn() override final;


};

#endif
