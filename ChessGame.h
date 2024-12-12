#ifndef CHESSGAME_H
#define CHESSGAME_H

#include <iostream>

/* The class ChessGame has been created to represent, and keep track of a
 * ChessGame. Any ChessGame instance has the following attributes and methods.
 *
 * Attributes (all private to ensure they are not meddled with):
 * - boardState: A 2d 8x8 array of ChessPiece pointers, that keeps track of the
 *   Chess Pieces. An array position occupied by a nullptr indicates
 *   an empty square.
 * - whoseTurn: An attribute of type enum Colour, which can take two possible
 *   values, WHITE or BLACK, to keep track of whose turn it is.
 * - whiteCount/blackCount: Attributes of type int, used to keep track of the 
 *   total number of white/black pieces respectively in a current game.
 * - castlingOptions: A four digit binary integer, used to keep track of the
 *   whether castling is available for white (bits 0/1), and black (bits 2/3)
 * - gameOver: A boolean attribute that is set to true, from false, if a
 *   checkmate or stalemate has been reached.
 * - boardLoaded: A boolean attribute that is set to true, from false, once a
 *   chess board state has been successfully loaded; ensuring a move cannot
 *   be submitted without a valid board.
 *
 * Methods (Public):
 * - ChessGame:
 *   - The ChessGame constructor
 *   - Parameters: None
 *   - Functionality: Constructs a ChessGame instance, filling the boardState
 *     2d array with nullptrs, whoseTurn to WHITE, white/blackCount to 0,
 *     castlingOptions to 0b0000, gameOver to false, and boardLoaded to false
 *
 * - loadState:
 *		- Return type: void
 *		- Parameters: A const character array, of max length 90; which is the
 *		  upper bound length of a FEN string (when allowing for en passant,
 *		  halfmove clock, and full move number, in case we wanted to extend
 *		  development later).
 *		- Functionality: Takes an FEN string as its parameter, and updates the
 *		  ChessGame instance to mirror the FEN string.
 *
 * - submitMove:
 *   - Return type: void
 *   - Parameters: two char const arrays, each of size [2]. The first contains
 *		 the board square being moved from, the second the board square being
 *		 moved to, in file then rank notation (e.g. "A1").
 *	 - Functionality: Checks the validity of a move being submitted. If the
 *	   move is valid, it will update the boardState accordingly; prior to
 *	   checking if the submitted move has resulted in the opponent being in
 *	   check, checkmate, or stalemate
 *
 * - getBoardPiece:
 *   - Return type: ChessPiece*
 *   - Parameters: One char const array of size [2], representing the board 
 *     square you want to get the chess piece from, e.g. "A1".
 *   - Functionality: A simple getter function, returning the chess piece
 *     at a given square, because the boardState is private
 *
 * - displayBoard:
 *   - Return type: void
 *   - Parameters: none
 *   - Functionality: A helper function that prints out the current board
 *     state, to help me check my functions were working as intended during
 *     development.
 *
 * - capturesPiece:
 *   - Return type: bool
 *   - Parameters: Two char const arrays of size [2], representing move_from
 *     and move_to squares.
 *   - Functionality: Now defunct, was used in early stages of development
 * 
 *  
 * Methods (Private):
 * - isValidPiece:
 *   - Return type: bool
 *   - Parameters: char letter, int rank_counter, int file_counter
 *   - Functionality: Helper function for loadState; called when a letter is
 *		 encountered when parsing an FEN string (before the first space). If the
 *		 letter represents a valid chess pice, isValidPiece will construct the
 *		 piece and place its pointer in the correct location in boardState 
 *
 * - isInCheck:
 *   - Return type: bool
 *   - Parameters: Colour kingColour
 *   - Functionality: Helper function for submitMove, used to determine if a
 *     player is currently in check, by finding the location of the King
 *     according to their colour; and then calling the squareUnderAttack
 *     function. Returns true, if the player is in check.
 *
 * - squareUnderAttack:
 *   - Return type: bool
 *   - Parameters: char const board_square[2], Colour yourPieceColour
 *   - Functionality: Checks if any pieces of opposite colour to your colour
 *     can validly attack the board square indicated in the input parameter.
 *     Returns true if they can.
 *
 * - willBeInCheck:
 *   - Return type: bool
 *   - Parameters: Colour kingColour, char const move_from[2],
 *     char const move_to[2]
 *   - Functionality: Helper function to test if a proposed move would
 *     lead to a player being taken into or out of check. To do this, it
 *     temporarily modifies the ChessGame board, and calls the isInCheck
 *     function on the modified board. Before returning the outcome of isInCheck
 *     it resets the board to its original state.
 *
 * - isInCheckOrStalemate:
 *   - Return type: bool
 *   - Parameters: Colour kingColour
 *   - Functionality: Iterates through all possible moves for all pieces that
 *     are of your own colour, to see if any of them are able to take your
 *     King out of check. Returns true if in check/stalemate, false otherwise
 *
 * - updateBoard:
 *   - Return type: void
 *   - Parameters: ChessPiece* movedPiece, char const move_from[2], 
 *     char const move_to[2]
 *   - Functionality: A helper function to update the boardState once all
 *     checks have been completed on a submitted move to ensure it is valid
 *

 * */

//defining constants used in the ChessGame
const int MAX_FEN_LENGTH = 90;
const int CASTLE_WHITE_KINGSIDE = 0b0001;
const int CASTLE_WHITE_QUEENSIDE = 0b0010;
const int CASTLE_BLACK_KINGSIDE = 0b0100;
const int CASTLE_BLACK_QUEENSIDE = 0b1000;
const int NO_CASTLING = 0b0000;


//declaring Colour enum and signalling it will be overloaded for ostreams
enum Colour {WHITE, BLACK};
std::ostream& operator << (std::ostream&, Colour&);

//declaring a MoveOutcome enum and assigning it binary values. Bitwise
//operations improve the efficiency and elegance of our submitMove method
enum MoveOutcome {
	NOT_VALID_MOVE = 0b00, 
	VALID_NO_CAPTURE = 0b01, 
	VALID_WITH_CAPTURE = 0b11, 
};

//Forward declaration of ChessPiece class, so it can be used in ChessGame class
class ChessPiece;

class ChessGame {
	public:
		/*@brief: Constructs a Chess Game */
		ChessGame();

		/*@brief: Loads a chess board onto a chess game , via a FEN string
		 * @params: board_string: The FEN string of max 90 chars.
		 */
		void loadState(char const board_string[MAX_FEN_LENGTH]);

		/* @brief: Submits a chess move and checks its validity, updating
		 * the board if valid
		 * @params: move_from: the board square being moved from. move_to: the
		 * board square being moved to.
		 */
		void submitMove(char const move_from[2], char const move_to[2]);

		/* @brief: A getter function used to get a board piece on a given square
		 * @params: boardPosition: the square you want to get the piece from
		 */
		ChessPiece* getBoardPiece(char const boardPosition[2]);

		/* @brief: A helper function during coding to print the board */
		void displayBoard();

		/* @brief: Declaring the copy constructor, for when I previously
		 * explicitly defined it to make deep copies. No longer used in code
		 * @params: other: another ChessGame passed as reference
		 */
		ChessGame(const ChessGame& other);

		/* @brief: The ChessGame destructor, explicitly defined in .cpp
		 * implementation to ensure proper memory management */
		~ChessGame();

		/* @brief: Assignment operator was also explicitly defined
		 * in accordance with the rule of 3; but like my copy constructor is
		 * never actually used anymore in the code
		 * @params: other: another ChessGame passed as reference
		 */
		ChessGame& operator=(const ChessGame& other);

	private:

		/*@brief: A method I used during development to work out if a move
		 * captured a piece or not. Is no longer used at all due to code
		 * optimisations since development.
		 * @params: move_from, the square a piece is being moved from. move_to,
		 * the square a piece is being moved to.
		 */
		bool capturesPiece(char const move_from[2], char const move_to[2]);
		
		//required for King and Rook classes to be able to view and update 
		//the castlingOptions private attribute
		friend class King;
		friend class Rook;

	private:
		ChessPiece* boardState[8][8]; 
		Colour whoseTurn;
		int whiteCount;
		int blackCount;
		int castlingOptions;
		bool gameOver;
		bool boardLoaded;

		/*@brief: A helper function to check the validity of a FEN string
		 * defensively ensuring correct input from the user.
		 * @params: letter; the letter representing a piece in the FEN string
		 * rank_counter: the rank where the piece is supposed to be placed on
		 * the board
		 * file_counter: the file where the piece is to be placed on the board
		 */
		bool isValidPiece(char letter, int rank_counter, int file_counter);

		/*@brief: a function to check if a player is in check
		 *@params: kingColour: the colour of the player who is to be checked*/
		bool isInCheck(Colour kingColour);

		/*@brief: a function to check if a square is under attack
		 * @params: board_square: the square in question to check
		 * yourPieceColour: the colour of the active player
		 */
		bool squareUnderAttack(char const board_square[2], Colour yourPieceColour);

		/*@brief: a function to check if a player will be in check when making
		 * a theoretical move
		 * @params: kingColour: the player's colour to check
		 * move_from: the square the player is moving a piece from
		 * move_to: the square the player is moving a piece to
		 */
		bool willBeInCheck(Colour kingColour, char const move_from[2], 
				char const move_to[2]);

		/*@brief: a function to check if a player is in check or stalemate, i.e.
		 *is out of valid moves
		 * @params: kingColour: the colour of the player to check
		 */
		bool isInCheckOrStalemate(Colour kingColour);	

		/*@brief: a helper function to update a board, once a move is confirmed
		 * as valid
		 * @params: movedPiece: a pointer to the chess piece being moved
		 * move_from: the board square the piece is being moved
		 * move_to: the board square being moved to
		 */
		void updateBoard(ChessPiece* movedPiece, char const move_from[2], 
				char const move_to[2]);

		/*@brief: a helper function to defensively check the validity of a
		 *coordinate being submitted in a move
		 * @params: coord: the coordinate reference in question
		 */
		bool isValidCoordinate(char const coord[2]);
};


#endif
