#ifndef EMPTYPIECE_H
#define EMPTYPIECE_H

#include "ChessPiece.h"

class EmptyPiece : public ChessPiece {
	public:
		EmptyPiece();
		bool isValidMove(char const move_from[2], char const move_to[2],
				ChessGame* cg) override;
		void printPiece(std::ostream& override);
		~EmptyPiece() override;
};

#endif
