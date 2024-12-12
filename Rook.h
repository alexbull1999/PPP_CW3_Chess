#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"


/* The Rook class represents the Rook pieces on the chess board.
 * It overrides the virtual methods declared in ChessPiece.h to ensure 
 * they are appropriate for the Rook context.
 *
 * Furthermore, in addition to the methods declared in ChessPiece.h, Rook.h
 * defines an additional private method for the Rook class,
 * updateCastlingOptions.
 *
 * This function is of return type void, and takes input parameters of
 * char const move_from[2], char const move_to[2], Colour rookColour, and
 * ChessGame* cg.
 * The purpose of this function is to check if a Rook is moving from its home
 * square, and if so, to disable the appropriate castling option.
 * */


class Rook : public ChessPiece {
	public:

		/*@brief: Rook Constructor
		* @params: pieceColour, the colour of the piece being created 
		* @returns: a rook object */
		Rook(Colour pieceColour);
		
		//Rook clone method now redundant, and not used at all
		ChessPiece* clone() const override;

		/*@brief: a function to determine whether a submitted move is legal
		* according to a rook's movement rules
		*@params: move_from, the square being moved from
		* move_to, the square being moved to
		* cg, an instance of a ChessGame object passed as a pointer
		* @returns: a bool, true if the move is valid for a rook
		*/
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg) override;

		/*@brief: A helper function so displayBoard() works correctly
		*Allows us to make use of dynamic binding within ostream overloading,
		*so the correct piece name is printed each time from the 2d boardState
		* array */
		void printPiece(std::ostream&) override;

		/*@brief: A getter function that the queen can use to
		* define and then access its own name
		* @returns: a string literal of the word "Rook" */
		const char* getPieceName() const override;

		/* @brief: overriding the virtual ChessPiece destructor to ensure
		* proper memory management during implicit pointer conversion */
		~Rook() override;

	private:
		/*@brief: helper function to determine if a rook has moved from its
		 *home square, and update the bits used to represent castling options
		 * in a chess game if so
		 * @params: move_from: the board square a rook is moved from
		 * rookColour: the colour of the rook being moved
		 * cg: a pointer to the ChessGame object in which the castling bits
		 * require updating
		 */
		void updateCastlingOptions(char const move_from[2], 
				Colour rookColour, ChessGame* cg);


};

#endif
