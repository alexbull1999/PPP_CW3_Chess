#ifndef QUEEN_H
#define QUEEN_H
#include "ChessPiece.h"
#include "Bishop.h"
#include "Rook.h"

/* The Queen class represents the Queen pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list. It utilises the isValidRookMove and isValidBishopMove
 * protected methods in ChessPiece.h to require a minimum amount of
 * new code for its isValidMove function. */
 

class Queen : public ChessPiece {
	public:
		/*@brief: Queen Constructor
		* @params: pieceColour, the colour of the piece being created */
		Queen(Colour pieceColour);

		//Queen clone method now redundant, and not used at all
		ChessPiece* clone() const override;

		/*@brief: a function to determine whether a submitted move is legal
		 * according to a queen's movement rules
		 *@params: move_from, the square being moved from
		* move_to, the square being moved to
		 * cg, an instance of a ChessGame object passed as a pointer
		 */
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
		~Queen() override;


};

#endif
