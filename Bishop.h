#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"


/* The Bishop class represents the Bishop pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list; but overrides the virtual methods 
 * declared to ensure they are appropriate for the Bishop context. Unlike
 * the Pawn, Knight and King chess piece classes, Bishop (and Rook) use
 * virtual public inheritance from the abstract chess piece class to allow 
 * multiple inheritance with the Queen class, whilst avoiding the 
 * 'diamond problem' of the Queen doubly inheriting ChessPiece */


class Bishop : virtual public ChessPiece {
	public:
		//Bishop Constructor
		Bishop(Colour pieceColour, Name pieceName);

		//Bishop clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Bishop
		bool isValidMove(char const move_from[2], char const move_to[2], 
				ChessGame* cg, bool& isPieceTaken) override;

		// printPiece function I used during testing to output the piece - the
		// function enables dynamic binding within the static ostream << operator
		void printPiece(std::ostream&) override;

		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. dynamic binding)
		~Bishop() override;

};

#endif
