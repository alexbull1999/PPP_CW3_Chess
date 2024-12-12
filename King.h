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

		/*@brief: Pawn Constructor
		* @params: pieceColour, the colour of the piece being created */
		King(Colour pieceColour);

		//King clone method, now entirely redundant
		ChessPiece* clone() const override;

		/*@brief: a function to determine whether a submitted move is legal
		* according to a pawn's movement rules
		*@params: move_from, the square being moved from
		* move_to, the square being moved to
		* cg, an instance of a ChessGame object passed as a pointer */
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg) override;

		/*@brief: A helper function so displayBoard() works correctly
		*Allows us to make use of dynamic binding within ostream overloading,
		*so the correct piece name is printed each time from the 2d boardState
		* array */
		void printPiece(std::ostream&) override;

		/*@brief: A getter function that the queen can use to
		* define and then access its own name */
		const char* getPieceName() const override;

		/* @brief: overriding the virtual ChessPiece destructor to ensure
		* proper memory management during implicit pointer conversion */
		~King() override;

	private:
		/*@brief: Helper function to update the castlingOptions attribute
		 *if the King has moved - signalling castling no longer available
		 * @params: kingColour, the colour of the king being moved
		 * cg: a pointer to the ChessGame object in which to update the castling
		 * options
		 */
		void updateCastlingOptions(Colour kingColour, ChessGame* cg);

		/* @brief: Helper function to determine if a King is trying to castle,
		 * and if they are doing so validly or not (from my research online,
		 * it seems that castling should be interpreted as the King's move,
		 * and hence a player trying to castle would submit a move of
		 * e.g. ("E1", "G1")) */
		bool checkForCastlingMove(char const move_from[2], char const move_to[2],
				ChessGame* cg);






};

#endif
