#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"


/* The Bishop class represents the Bishop pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list; but overrides the virtual methods 
 * declared to ensure they are appropriate for the Bishop context. */


class Bishop : public ChessPiece {
	public:
		/*@brief: Rook Constructor
		* @params: pieceColour, the colour of the piece being created */
		Bishop(Colour pieceColour);

		//Bishop clone method, now entirely redundant and not in use
		ChessPiece* clone() const override;

		/*@brief: a function to determine whether a submitted move is legal
		* according to a bishop's movement rules
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

		/* @brief: overriding the virtual ChessPiece destructor to ensure
		* proper memory management during implicit pointer conversion */
		~Bishop() override;

		/*@brief: A getter function that the queen can use to
		* define and then access its own name */
		const char* getPieceName() const override;


};

#endif
