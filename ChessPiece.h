#ifndef CHESSPIECE_H
#define CHESSPIECE_H

/* Defining an abstract class for ChessPiece.h, that all
 * Chess Pieces (e.g. King, Queen, etc.) will inherit from.
 * Each Chess Piece class defining the rules of its own valid
 * moves */

#include "ChessGame.h"
#include <iostream>

class ChessPiece {
	public:
		ChessPiece(Colour pieceColour, Name pieceName); //constructor for other pieces
		
		//pure virtual method for isValidMove for child classes to have to overwrite
		virtual bool isValidMove(char const move_from[2], 
				char const move_to[2], ChessGame* cg, bool& isPieceTaken) = 0;

		//pure virtual method for cloning, to enable deep copies of a ChessGame
		virtual ChessPiece* clone() const = 0;


		friend std::ostream& operator << (std::ostream&, ChessPiece*);
		//We need to make use of dynamic binding within the ostream overloading, so
		//the correct piece name is printed each time from the 2d array of ChessPieces
		virtual void printPiece(std::ostream&) = 0;

		//virtual destructor required to allow deletion of derived objects that have
		//undergone pointer conversion
		virtual ~ChessPiece();

		//friend to allow ChessGame class to see piece colour and ensure it matches with
		//whose turn it is to go
		friend class ChessGame; 

	protected:
		Colour pieceColour;
		Name pieceName;


};


#endif 
