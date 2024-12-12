#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

/* The Knight class represents the Knight pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list; but overrides the virtual methods 
 * declared to ensure they are appropriate for the Knight context */

class Knight : public ChessPiece {
	public:
		//Knight Constructor
		Knight(Colour pieceColour);

		//Knight clone method
		ChessPiece* clone() const override final;

		//isValidMove declaration for Knight
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg) override final;

		// printPiece function I used during testing to output the piece - the
			void printPiece(std::ostream&) override final;

		//Getter for the piece name, returning a string literal representing the name of a piece
		const char* getPieceName() const override;

		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. through dynamic binding)
		~Knight() override final;


};

#endif
