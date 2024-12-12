#ifndef ROOK_H
#define ROOK_H

#include "ChessPiece.h"


/* The Rook class represents the Rook pieces on the chess board.
 * It overrides the virtual methods declared in ChessPiece.h to ensure 
 * they are appropriate for the Rook context. Unlike the Pawn, Knight and King 
 * chess piece classes, Rook (and Bishop) use
 * virtual public inheritance from the abstract chess piece class to allow 
 * multiple inheritance with the Queen class, whilst avoiding the 
 * 'diamond problem' of the Queen doubly inheriting ChessPiece 
 *
 * Furthermore, in addition to the methods declared in ChessPiece.h, Rook.h
 * defines an additional method for the Rook class, updateCastlingOptions.
 * This function is private, as we do not want the Queen who inherits from
 * Rook (and Bishop), to have access to updateCastlingOptions
 *
 * This function is of return type void, and takes input parameters of
 * char const move_from[2], char const move_to[2], Colour rookColour, and
 * ChessGame* cg.
 * The purpose of this function is to check if a Rook is moving from its home
 * square, and if so, to disable the appropriate castling option.
 * */


class Rook : public ChessPiece {
	public:
		//Rook Constructor
		Rook(Colour pieceColour);
		
		//Rook clone method
		ChessPiece* clone() const override;

		//isValidMove declaration for Rook
		bool isValidMove(char const move_from[2], char const move_to[2], 
				ChessGame* cg, bool& isPieceTaken) override;

		// printPiece function I used during testing to output the piece - the
		// function enables dynamic binding within the static ostream << operator
		void printPiece(std::ostream&) override;

		//Getter for the piece name, returning a string literal representing the name of a piece
		const char* getPieceName() const override;

		// overriding the ChessPiece virtual destructor, so memory management works
		// whilst using an array of ChessPiece pointers (i.e. dynamic binding)
		~Rook() override;

	private:
		//Helper function to update the castlingOptions attribute if the Rook has
		//moved - signalling castling no longer available
		void updateCastlingOptions(char const move_from[2], 
				Colour rookColour, ChessGame* cg);


};

#endif
