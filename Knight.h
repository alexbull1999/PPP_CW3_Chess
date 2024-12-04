#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

class Knight : public ChessPiece {
	public:
		//Knight Constructor
		Knight(Colour pieceColour, Name pieceName);

		//Knight clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Knight
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg, bool& isPieceTaken) override;
		// printPiece function I used during testing + to output the piece - the
		// printPiece function enables dynamic binding within the static ostream <<
		// operator
		void printPiece(std::ostream&) override;
		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. through  dynamic binding)
		~Knight() override;


};

#endif
