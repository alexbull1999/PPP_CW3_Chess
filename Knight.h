#ifndef KNIGHT_H
#define KNIGHT_H

#include "ChessPiece.h"

/* The Knight class represents the Knight pieces on the chess board.
 * It does not have any attributes or methods that ChessPiece.h
 * does not already list; but overrides the virtual methods 
 * declared to ensure they are appropriate for the Knight context */

class Knight : public ChessPiece {
	public:

		/*@brief: Knight Constructor
		* @params: pieceColour, the colour of the piece being created */
		Knight(Colour pieceColour);

		//Knight clone method, now entirely redundant
		ChessPiece* clone() const override;

		/*@brief: a function to determine whether a submitted move is legal
		* according to a knight's movement rules
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
		~Knight() override;


};

#endif
