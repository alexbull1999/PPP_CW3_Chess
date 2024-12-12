#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessGame.h"

/* The Chess Piece class is an abstract class  that all
 * Chess Pieces (e.g. King, Queen, etc.) will inherit from.
 *
 * Attributes:
 * The class contains one attribute shared by all Chess Pieces,
 * their pieceColour (of type enum Colour)
 *
 * Methods (Public):
 *  - A pure virtual method, isValidMove, of return type bool that takes input
 *    parameters of (char const move_from[2], char const move_to[2], 
 *    ChessGame* cg, and bool& isPieceTaken)
 *  - Functionality:
 *    This pure virtual method allows each ChessPiece to define their own
 *    rules for what constitutes a valid move, according to how that piece is
 *    allowed to move in Chess
 *
 *  - A pure virtual method, clone, of return type ChessPiece*, that was used
 *    to create deep copies of ChessPieces, in the ChessGame copy constructor
 *
 *  - A pure virtual method, getPieceName, that ChessPieces define in their
 *	  subclasses to return a string literal of their own name
 *
 * - A pure virtual method, printPiece, of return type void, that I used during
 *   development, in conjunction with the displayBoard() function in ChessGame.h
 *   This enables each ChessPiece to print their own symbol
 *
 * - A virtual destructor, that needs to be overwritten by each subclass, to
 *   ensure proper memory management when deleting pieces and boardStates
 *
 * Methods (Protected):
 *	- isValidRookMove, containing the logic for whether a rook move is valid or
 *	  not, placed in this ChessPiece class, so both the Rook and the Queen is
 *	  able to access it without duplicating the code
 * - isValidBishopMove, containing the logic for whether a bishop move is valid,
*	 placed in this ChessPiece class, so both the Bishop and the Queen is
 *	  able to access it without duplicating the code
 *
 *  */


class ChessPiece {
	public:
		/*@brief: ChessPiece Constructor, only ever invoked by subclasses as
		 * ChessPiece is an abstract class
		 * @params: pieceColour, the colour of the piece being created */
		ChessPiece(Colour pieceColour);

		/*@brief: a pure virtual isValidMove function to determine whether a
		 *submitted move is legal according to a piece's movement rules
		 *@params: move_from, the square being moved from
		 * move_to, the square being moved to
		 * cg, an instance of a ChessGame object passed as a pointer
		 */
		virtual bool isValidMove(char const move_from[2], 
				char const move_to[2], ChessGame* cg) = 0;

		/*this method is now redundant (was used during development when I made
		 * deep copies of the board */
		virtual ChessPiece* clone() const = 0;

		/*@brief: pure virtual getter function that pieces  use to get
		 * define and then access their own names */
		virtual const char* getPieceName() const = 0;

		//signalling overloading of the ostream operator
		friend std::ostream& operator << (std::ostream&, ChessPiece*);

		/*@brief: A helper function so displayBoard() works correctly
		 *Allows us to make use of dynamic binding within ostream overloading,
		 *so the correct piece name is printed each time from the 2d boardState
		 * array */
		virtual void printPiece(std::ostream&) = 0;

		/* @brief: virtual destructor required to allow deletion of derived
		 * objects that undergo pointer conversion */
		virtual ~ChessPiece();

		/* friend is required to allow ChessGame class to see piece colour and
		 * ensure it matches with whose turn it is to go */
		friend class ChessGame;
	
		/*required to allow the King to check for the Rook's existence,
		 *and colour when ensuring castling validity,
		 *as pieceColour & pieceName are protected */
		friend class King; 

	protected:
		Colour pieceColour;

		/*@brief: A function to determine if a submitted chess move is valid
		 *by rook logic
		 *@params: move_from, the square being moved from
		 *move_to, the square being moved to
		 *cg, an instance of a ChessGame object passed as a pointer
		 */
		bool isValidRookMove(char const move_from[2], char const move_to[2],
			ChessGame* cg);

		/*@brief: A function to determine if a submitted chess move is valid
		*by bishop logic
		*@params: move_from, the square being moved from
		*move_to, the square being moved to
		*cg, an instance of a ChessGame object passed as a pointer
		*/
		bool isValidBishopMove(char const move_from[2], char const move_to[2],
			ChessGame* cg);

};


#endif 
