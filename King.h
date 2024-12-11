#ifndef KING_H
#define KING_H
#include "ChessPiece.h"

/* The King class represents the King pieces on the chess board.
 * It overrides the virtual methods declared in ChessPiece.h to ensure 
 * they are appropriate for the King context.
 *
 * Furthermore, in addition to the methods declared in ChessPiece.h,King.h
 * defines additional methods for the King class:
 *  - updateCastlingOptions
 *		- Return type: void
 *		- Parameters: Colour kingColour, ChessGame* cg
 *		- Functionality: Update the castling options available to a player
 *		  if their King moves from their home square
 *	- checkForCastlingMove:
 *		- Return type: bool
 *		- Parameters: char const move_from[2], char const move_to[2],
 *		  ChessGame* cg.
 *		- Functionality: Checks if a King's submitted move is trying to make
 *		  a valid castle, and if so enables that castling move to be played
 *
 * Both functions ar private, as only required by the King */

class King : public ChessPiece {
	public:
		//King Constructor
		King(Colour pieceColour, Name pieceName);

		//King clone method
		ChessPiece* clone() const override final;

		//isValidMove declaration for King
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg, bool& isPieceTaken) override final;

		// printPiece function I used during testing to output the piece - the
		// function enables dynamic binding within the static ostream << operator
		void printPiece(std::ostream&) override final;

		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. dynamic binding)
		~King() override final;

	private:
		//Helper function to update the castlingOptions attribute if the King has
		//moved - signalling castling no longer available
		void updateCastlingOptions(Colour kingColour, ChessGame* cg);

		//Helper function to determine if a King is trying to castle and doing so
		//validly or not (from my research online, it seems that castling should be
		//interpreted as the King's move, and hence a player trying to castle would
		//submit a move of e.g. ("E1", "G1"))
		bool checkForCastlingMove(char const move_from[2], char const move_to[2],
				ChessGame* cg);






};

#endif
