#ifndef CHESSPIECE_H
#define CHESSPIECE_H

#include "ChessGame.h"

/* The Chess Piece class is an abstract class  that all
 * Chess Pieces (e.g. King, Queen, etc.) will inherit from.
 *
 * Attributes:
 * The class contains two attributes shared by all Chess Pieces,
 * their pieceColour (of type enum Colour), and their name (of type
 * enum Name). Note, both enums are declared in ChessGame.h
 *
 * Methods (Public):
 *  - A pure virtual method, isValidMove, of return type bool that takes input
 *    parameters of (char const move_from[2], char const move_to[2], 
 *    ChessGame* cg, and bool& isPieceTaken)
 *  - Functionality:
 *    This pure virtual method allows each ChessPiece to define their own
 *    rules for what constitues a valid move, according to how that piece is
 *    allowed to move in Chess
 *
 *  - A pure virtual method, clone, of return type ChessPiece*, that is used
 *    to create deep copies of ChessPieces, in the ChessGame copy constructor
 *
 * - A pure virtual method, printPiece, of return type void, that I used during
 *   development, in conjunction with the displayBoard() function in ChessGame.h
 *   This enables each ChessPiece to print their own symbol 
 *
 * - A virtual destructor, that needs to be overwritten by each subclass, to
 *   ensure proper memory management when deleting pieces and boardStates
 *  */




class ChessPiece {
	public:
		//Constructor only ever invoked by subclasses as ChessPiece is abstract
		ChessPiece(Colour pieceColour, Name pieceName);
		
		virtual bool isValidMove(char const move_from[2], 
				char const move_to[2], ChessGame* cg, bool& isPieceTaken) = 0;

			virtual ChessPiece* clone() const = 0;

		//signalling overloading of the ostream operator
		friend std::ostream& operator << (std::ostream&, ChessPiece*);
		//We need to make use of dynamic binding within the ostream overloading, so
		//the correct piece name is printed each time from the 2d boardState array
		virtual void printPiece(std::ostream&) = 0;

		//virtual destructor required to allow deletion of derived objects that
		//undergo pointer conversion
		virtual ~ChessPiece();

		//friend to allow ChessGame class to see piece colour and ensure it matches 
		//with whose turn it is to go
		friend class ChessGame;
	
		//required to allow the King to check for the Rook's existence, and colour
		//when ensuring castling validity, as pieceColour & pieceName are protected
		friend class King; 

	protected:
		Colour pieceColour;
		Name pieceName;


};


#endif 
