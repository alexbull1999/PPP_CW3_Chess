#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <iostream>

/* This is the upper bound length of FEN strings; allowing 64 characters for pieces/
 * squares, 7 slashes, 1 for colour (w/b), 4 for castling, 2dgdsgefor en passant 
 * (should one wish to implement that), 3 for the halfmove clock (should one wish
 * to implement that), and 4 for the full move number (with the maximum game length
 * < 9999 due to the 50-move rule). There are also 5 space characters between fields.
 * This results in 64+7+1+4+2+3+4+5=90 characters long. */

int const MAX_FSN_LENGTH = 90;


//declaring Colour enum and signalling it will be overloaded for ostreams
enum Colour {WHITE, BLACK};
std::ostream& operator << (std::ostream&, Colour&);

//declaring pieceName enum and signalling it will be overloaded for ostreams
enum Name {PAWN, ROOK, KNIGHT, BISHOP, QUEEN, KING};
std::ostream& operator << (std::ostream&, Name&);

//declaring a further enum to indicate the outcome of a given submitted move
//and assigning binary values to be able to do a bitwise or operation
enum MoveOutcome {
	NOT_VALID_MOVE = 0b00, //binary value of 0
	VALID_NO_CAPTURE = 0b01, //binary value of 1
	VALID_WITH_CAPTURE = 0b11, //binary value of 3
};


//Forward declaration of ChessPiece class, so it can be used in ChessGame class
class ChessPiece;

//Declare ChessGame class - extend comment to describe class and its methods/attributes
//Fine to use default constructor, so not explicitly stating it
class ChessGame {
	public:
		//default ChessGame constructor that sets boardState array to nullptr to start with
		ChessGame();

		void loadState(char const board_string[MAX_FSN_LENGTH]);
		void submitMove(char const move_from[2], char const move_to[2]);

		//Getter function for other classes to see what pieces occupy what board
		//positions
		ChessPiece* getBoardPiece(char const boardPosition[2]);


		//"getter" function used to print board state to check my working as I coded
		void displayBoard();

		//Declaring the copy constructor for ChessGame objects to allow deep copies
		// this is needed to test if a move is valid when a King is in check (we 
		// overload the copy constructor in the .cpp file)
		ChessGame(const ChessGame& other);

		//ChessGame Destructor to clean up heap allocated pointers
		~ChessGame();

		//Assignment operator for deep copying, to be overloaded
		ChessGame& operator=(const ChessGame& other);



		// helper function to determine if a submitted move leads to a piece being
		// taken
		bool capturesPiece(char const move_from[2], char const move_to[2]);

	private:
		ChessPiece* boardState[8][8]; 
		Colour whoseTurn;
		int whiteCount;
		int blackCount;

		// helper function to ensure validity of FSN string
		bool isValidPiece(char letter, int rank_counter, int file_counter);
		
		//helper function to find a square occupied by a King of a given colour
		char* getKingPosition(Colour kingColour);

		//helper function to determine if a King is currently in check
		bool isInCheck(Colour kingColour);

		//helper function to determine if a move will take a King out of check or
		//put a King in check
		bool willBeInCheck(Colour kingColour, char const move_from[2], 
				char const move_to[2]);

		//helper function to determine if a King is in checkmate or stalemate
		bool isInCheckOrStalemate(Colour kingColour);	

		//helper function to update board position after having confirmed
		//the validity of a move
		void updateBoard(ChessPiece* movedPiece, char const move_from[2], 
				char const move_to[2]);
		

};


#endif
