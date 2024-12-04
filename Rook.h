#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"

// virtual public inheritance to allow multiple inheritance with the Queen
// class, whilst avoiding the 'diamond problem' of the Queen doubly inheriting
// ChessPiece
class Rook : virtual public ChessPiece {
	public:
		//Rook Constructor
		Rook(Colour pieceColour, Name pieceName);
		
		//Rook clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Rook
		bool isValidMove(char const move_from[2], char const move_to[2], 
				ChessGame* cg, bool& isPieceTaken) override;
		// printPiece function I used during testing + to output the piece - the
		// printPiece function enables dynamic binding within the static ostream <<
		// operator
		void printPiece(std::ostream&) override;
		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. through  dynamic binding)
		~Rook() override;

};

#endif
