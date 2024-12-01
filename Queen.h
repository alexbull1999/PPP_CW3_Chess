#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

class Queen : public Bishop, Rook {
	public:
		//Queen Constructor now has to pass through Bishop and Rook constructors
		//to reach the ChessPiece constructor and initialise its pieceColour
		Queen(Colour pieceColour, Name pieceName);

		//Queen clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Queen
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg) override;
		// printPiece function I used during testing + to output the piece - the
		// printPiece function enables dynamic binding within the static ostream <<
		// operator
		void printPiece(std::ostream&) override;
		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. through  dynamic binding)
		~Queen() override;


};

#endif
