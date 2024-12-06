#ifndef KING_H
#define KING_H
#include "ChessPiece.h"

class King : public ChessPiece {
	public:
		//King Constructor
		King(Colour pieceColour, Name pieceName);

		//King clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for King
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg, bool& isPieceTaken) override;

		//Helper function to update the castlingOptions attribute if the King has
		//moved - signalling castling no longer available
		void updateCastlingOptions(Colour kingColour, ChessGame* cg);

		//Helper function to determine if a King is trying to castle and doing so
		//validly or not (from my research online, it seems that castling should be
		//interpreted as the King's move, and hence a player trying to castle would
		//submit a move of e.g. ("E1", "G1"))
		bool checkForCastlingMove(char const move_from[2], char const move_to[2],
				ChessGame* cg);

		// printPiece function I used during testing + to output the piece - the
		// printPiece function enables dynamic binding within the static ostream <<
		// operator
		void printPiece(std::ostream&) override;

		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. through  dynamic binding)
		~King() override;

};

#endif
