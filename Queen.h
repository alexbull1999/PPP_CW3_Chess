#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

/* The Queen class represents the Queen pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list. It utilises multiple inheritance to inherit
 * both from Rook and Bishop classes, and in doing so requires a minimum amount of
 * new code for its isValidMove function. */
 

class Queen : public ChessPiece {
	public:
		//Queen Constructor now has to pass through Bishop and Rook constructors
		//to reach the ChessPiece constructor and initialise its pieceColour
		Queen(Colour pieceColour);

		//Queen clone method
		ChessPiece* clone() const override final;

		//isValidMove declaration for Queen
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg) override final;

		// printPiece function I used during testing to output the piece - the
		// function enables dynamic binding within the static ostream << operator
		void printPiece(std::ostream&) override final;

		//Getter for the piece name, returning a string literal representing the name of a piece
		const char* getPieceName() const override;

		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. dynamic binding)
		~Queen() override final;


};

#endif
