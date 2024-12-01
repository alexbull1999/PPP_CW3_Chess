#ifndef BISHOP_H
#define BISHOP_H

#include "ChessPiece.h"

// virtual public inheritance to allow multiple inheritance with the Queen
// class, whilst avoiding the 'diamond problem' of the Queen doubly inheriting
// ChessPiece
class Bishop : virtual public ChessPiece {
	public:
		//Bishop Constructor
		Bishop(Colour pieceColour, Name pieceName);

		//Bishop clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Bishop
		bool isValidMove(char const move_from[2], char const move_to[2], 
				ChessGame* cg) override;
		// printPiece function I used during testing + to output the piece - the
		// printPiece function enables dynamic binding within the static ostream <<
		// operator
		void printPiece(std::ostream&) override;
		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. through  dynamic binding)
		~Bishop() override;
		
		//Queen's can move like Bishop's (diagonally) or like rook's (left and right)
		//So we want the Queen isValidMove function to borrow from both
		friend class Queen;


};

#endif
