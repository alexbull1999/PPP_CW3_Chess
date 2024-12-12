#include "ChessGame.h"
#include "ChessPiece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include <iostream>
#include <cassert>
#include <cctype> //for isalpha()
#include <stdexcept> //for logic_error

using namespace std;

//overloading ostream operator for colour enum
ostream& operator << (ostream& os, Colour& colour) {
	switch(colour)
	{
		case Colour::WHITE:
			os << "White";
			break;
		case Colour::BLACK:
			os << "Black";
			break;
	}
	return os;
}

/* Default ChessGame constructor (initializes boardState array to nullptrs).
All other attributes initialized, but most are meaningfully assigned in
loadState function */
ChessGame::ChessGame() : boardState(), whoseTurn(Colour::WHITE), whiteCount(0), 
	blackCount(0), castlingOptions(0b0000), gameOver(false), boardLoaded(false) {};


void ChessGame::loadState(char const board_string[MAX_FEN_LENGTH]) {
	
	// first clean the ChessGame board if there was a previous game
	if (boardLoaded) {
		for (int rank_counter = 0; rank_counter < 8; rank_counter++) {
			for (int file_counter = 0; file_counter < 8; file_counter++) {
				delete boardState[rank_counter][file_counter];
				boardState[rank_counter][file_counter] = nullptr;
			}
		}
		//reset whiteCount, blackCount, and castlingOptions attributes
		whiteCount = 0;
		blackCount = 0;
		castlingOptions = NO_CASTLING;
	}

	/* now we can create a new board state, using a helper function isValidPiece
	 * to defensively check the validity of the FEN string provided to us */
	int FENCounter = 0;
	for (int rank_counter = 7, file_counter = 0; board_string[FENCounter] != ' ';
			FENCounter++) {
		
		/* if (rank_counter < 0) {
			cerr << "Warning - error; rank_counter has gone below 0";
		}  (this if branched was used in testing, but not needed anymore) */

		if (isValidPiece(board_string[FENCounter], rank_counter, file_counter)) {
			file_counter++;
			continue;
		}

		if (board_string[FENCounter] >= '1' &&
				board_string[FENCounter] <= '8') {
			for (int emptyCount = '0'; emptyCount < board_string[FENCounter]; 
					emptyCount++) {
				boardState[rank_counter][file_counter] = nullptr;
				file_counter++;
			}
		}

		else if (board_string[FENCounter] == '/') {
			file_counter = 0;
			rank_counter--;
		}

		else {
			cout << "Invalid FEN notation inputted - cannot load game\n";
			return;
		}
	}

	//once the above for loop is complete, the FENCounter has hit the first space
	//in the FEN string so we can next determine whose move it is.
	FENCounter++;

	if (board_string[FENCounter] == 'w') {
		whoseTurn = Colour::WHITE;
	}
	else if (board_string[FENCounter] == 'b') {
		whoseTurn = Colour::BLACK;
	}
	else {
		cout << "Invalid FEN notation inputted - cannot load game \n";
		return;
	}

	FENCounter += 2; //skips over the space onto first castling characters

	// we know there is a max of 4 castling characters, and that as soon as
	// we encounter a - or the sentinel value (end of string) we should stop
	
	for (int limit = FENCounter + 4; FENCounter <= limit; FENCounter++ ) { //test edge cases
		if (board_string[FENCounter] == '-' || board_string[FENCounter] == '\0') {
			cout << "A new board state is loaded!\n";
			gameOver = false; //in case it had been set to true in a previous game
			boardLoaded = true;
			return;
		}
		if (board_string[FENCounter] == 'K') {
			//White can castle kingside, stored as bit 0 of castlingOptions
			castlingOptions |= CASTLE_WHITE_KINGSIDE;
		}
		else if (board_string[FENCounter] == 'Q') {
			//White can castle queenside, stored as bit 1
			castlingOptions |= CASTLE_WHITE_QUEENSIDE;
		}
		else if (board_string[FENCounter] == 'k') {
			//black can castle kingside, stored as bit 2
			castlingOptions |= CASTLE_BLACK_KINGSIDE;
		}
		else if (board_string[FENCounter] == 'q') {
			//black can castle queenside, stored as bit 3
			castlingOptions |= CASTLE_BLACK_QUEENSIDE;
		}
	}
	
	//if code has reached this point, it means a longer FEN string 
	//has been loaded with information beyond the spec, so we can ignore it
	//and cout and return
	cout << "A new board state is loaded";
	gameOver = false; //in case it had been set to true in a previous game
	boardLoaded = true;
	return;
}

// Helper function to defensively ensure the validity of the board
// during the loadState function
bool ChessGame::isValidPiece(char letter, int rank_counter, int file_counter) {

	if (!isalpha(letter)) {
		return false;
	}

	Colour pieceColour = isupper(letter) ? Colour::WHITE : Colour::BLACK;
	ChessPiece* cp = nullptr;

	switch (tolower(letter)) {
		case 'p': {
								cp = new Pawn(pieceColour);
								break;
							}
		case 'r': {
								cp = new Rook(pieceColour);
								break;
							}
		case 'n': {
								cp = new Knight(pieceColour);
								break;
							}
		case 'b': {
								cp = new Bishop(pieceColour);
								break;
							}
		case 'q': {
								cp = new Queen(pieceColour);
								break;
							}
		case 'k': {
								cp = new King(pieceColour);
								break;
							}
		default:
							{
								cout << "Error - Invalid FSN notation\n";
								break;
							}
	}

	if (cp == nullptr) {
		return false;
	}
	boardState[rank_counter][file_counter] = cp;
	pieceColour == Colour::BLACK ? blackCount++ : whiteCount++;
	return true;
}



void ChessGame::submitMove(char const move_from[2], char const move_to[2]) {
	//check load state has been called so there is a valid board to play with
	if (!boardLoaded) {
		cout << "You need to load a board, before being able to play a move!\n";
		return;
	}
	
	//check the game is not already over 
	if (gameOver) {
		cout << "Game is already over, you cannot submit a move! Please load a new game.\n";
		return;
	}
	
	//check the move coordinates are valid
	if (!isValidCoordinate(move_from) || !isValidCoordinate(move_to)) {
		cout << "Invalid board coordinates submitted\n";
		return;
	}
	
	//check for a piece at move_from square, via helper function getBoardPiece
	ChessPiece* movedPiece = getBoardPiece(move_from);
	if (movedPiece == nullptr) {
		cout << "There is no piece at position " << move_from << "!\n";
		return;
	}
	//if there is a piece, check it matches the colour of whose turn it is
	 if(movedPiece->pieceColour != whoseTurn) {
		cout << "It is not " << movedPiece->pieceColour << "'s turn to move!\n";
		return;
	}
	
	/* The isPieceTaken parameter is updated to true if there is an
	 * enemy piece in the move_to square. This is passed by reference to the
	 * isValidMove helper function. If the submitted move is invalid, this is 
	 * updated back to false. If it remains true, then we take the piece. */
	bool isPieceTaken = false;

	/* Check if the move_to square is occupied by one of your own pieces as this 
	 * is always invalid, so we can return immediately without further checks */
	ChessPiece* takenPiece = getBoardPiece(move_to);
	// check to not dereference a nullptr
	if (takenPiece != nullptr) { 
		if (movedPiece->pieceColour == takenPiece->pieceColour) {
			cout << whoseTurn << "'s " << movedPiece->getPieceName() << " cannot move to "
				<< move_to << "!\n";
			return;
		}
		isPieceTaken = true;
	}
	
	/* We now check the validity of the move according to the movement
	 * rules of each piece and store the result in validMove. Note: 
	 * if a move is invalid, the isPieceTaken bool is also set back to false */
	bool validMove = movedPiece->isValidMove(move_from, move_to, this);
	if (!validMove) { isPieceTaken = false; } //regardless of if there is a piece in move_to

	/* Even if a move is valid by piece movement rules, you can't move yourself
	 * into check, so we need to check this as well */
	try {
		if (validMove && willBeInCheck(whoseTurn, move_from, move_to, isPieceTaken)) {
			cout << whoseTurn << "'s " << movedPiece->getPieceName() << " cannot move to "
			<< move_to << "!\n";
			return;
		}
	} catch (logic_error& e) {
		cout << "Game Over: " << e.what() << "\n";
		return;
	}
	
	/*Update the flags below depending on the outcomes of the isValidMove and 
	 * isPieceTaken bools. This allows us to use the MoveOutcome enum to 
	 * determine what to do next */
	int validFlag = validMove ? 0b01 : 0b00; //0b01 indicates a valid move
	int captureFlag = isPieceTaken ? 0b10 : 0b00; //0b10 indicates a move that takes a piece
	MoveOutcome outcome = static_cast<MoveOutcome>(validFlag | captureFlag);
	
	switch(outcome) {
		case NOT_VALID_MOVE:
		{
			cout << whoseTurn << "'s " << movedPiece->getPieceName() << " cannot move to "
				<< move_to << "!\n";
			return;			
		}

		/* Note, we never worry about dereferencing a nullptr for takenPiece in this case
		 * since the captureFlag indicates by necessity that takenPiece is not null */
		case VALID_WITH_CAPTURE: 
		{
			cout << whoseTurn << "'s " << movedPiece->getPieceName() << " moves from " <<
				move_from << " to " << move_to << " taking " << takenPiece->pieceColour
				<< "'s " << takenPiece->getPieceName() << "\n";
			//delete the taken piece from the board
			delete takenPiece;
			takenPiece = nullptr;

			// decrement the pieceCounter for the colour whose piece has been taken
			movedPiece->pieceColour == Colour::BLACK ? whiteCount-- : blackCount--;
			break;
		}
		
		case VALID_NO_CAPTURE:
		{
			cout << whoseTurn << "'s " <<  movedPiece->getPieceName() << " moves from " <<
				move_from << " to " << move_to << endl;
		}
	}

	/* For both valid with capture, and valid no capture moves, we can now move 
	 * the piece to its new position, and assign its old position to nullptr */
	
	updateBoard(movedPiece, move_from, move_to);
	whoseTurn = (whoseTurn == Colour::BLACK) ? Colour::WHITE : Colour::BLACK;

	/* Before returning, we need to check if the person whoseTurn is next is
	 * now in check or in checkmate */

	//We check for check first, as you cannot be in checkmate without check
	try {
		if (isInCheck(whoseTurn)) {
			if (isInCheckOrStalemate(whoseTurn)) {
				cout << whoseTurn << " is in checkmate\n";
				gameOver = true;
			}
			else {
				cout << whoseTurn << " is in check\n";
			}
		}
		else if (isInCheckOrStalemate(whoseTurn)) {
			cout << whoseTurn << " is in stalemate\n";
			gameOver = true;
		}
	} catch (const logic_error& e) {
		cout << "Game Over: " << e.what() << "\n";
	}
	return;
}


//getBoardPiece "getter" function
ChessPiece* ChessGame::getBoardPiece(char const boardPosition[2]) {
	int file_counter = boardPosition[0] - 'A';
	int rank_counter = boardPosition[1] - '1'; 
	ChessPiece* cp = boardState[rank_counter][file_counter];
	return cp;
}


/* A function I used during coding to check the loadState function was working
 * as expected but is not used in the final program */
void ChessGame::displayBoard() {
	for (int rank_counter = 7; rank_counter >= 0; rank_counter--) {
		for (int file_counter = 0; file_counter < 8; file_counter++) {
			if (file_counter != 7) {
				cout << boardState[rank_counter][file_counter];
			}
			else if (file_counter == 7) {
				cout << boardState[rank_counter][file_counter] << "\n";
			}
		}
	}
	return;
}


/* Defining the copy constructor for ChessGame objects, so that
 * deep copies (i.e. a new board on the heap) is created. This is used
 * in the willBeInCheck function, to test if a move played would 
 * result in a player putting themselves in check */ 
ChessGame::ChessGame(const ChessGame& other) {
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			if (other.boardState[rank][file] != nullptr) {
				//Clone ChessPiece object using clone method
				boardState[rank][file] = other.boardState[rank][file]->clone();
			}
			else {
				boardState[rank][file] = nullptr;
			}
		}
	}
	whoseTurn = other.whoseTurn;
	whiteCount = other.whiteCount;
	blackCount = other.blackCount;
	castlingOptions = other.castlingOptions;
	gameOver = other.gameOver;
	boardLoaded = other.boardLoaded;
}

/* Defining the destructor so we clean up heap allocated memory properly 
 * given the explicit definition of the copy constructor */
ChessGame::~ChessGame() {
	for (int rank_counter = 7; rank_counter >= 0; rank_counter--) {
		for (int file_counter = 0; file_counter < 8; file_counter++) {
			delete boardState[rank_counter][file_counter];
			boardState[rank_counter][file_counter] = nullptr;
		}
	}
}

/* Defining the assignment operator, given the definitions of the
 * Copy constructor and destructor for the ChessGame class. Note: 
 * I don't actually use this assignment operator anywhere in my code
 * but am doing this to abide by good practice (rule of 3) */
ChessGame& ChessGame::operator=(const ChessGame& other) {
	if (this != &other) {
		//clean up whatever the existing 'this' board is
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				delete boardState[rank][file];
			}
		}
	}

	//deep copy the other board
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			if (other.boardState[rank][file] != nullptr) {
				boardState[rank][file] = other.boardState[rank][file]->clone();
			}
			else {
				boardState[rank][file] = nullptr;
			}
		}
	}
	whoseTurn = other.whoseTurn;
	whiteCount = other.whiteCount;
	blackCount = other.blackCount;
	return *this;
}


/* Helper function to determine if a submitted move leads to a piece being 
 * taken. This previously was used frequently within my isValidMove function
 * for ChessPiece classes; but since optimising my code with the bool 
 * isPieceTaken parameter in submitMove, is rarely required now. It's sole
 * use is to resolve an edge case re. multiple inheritance with a Queen */
bool ChessGame::capturesPiece(char const move_from[2], char const move_to[2]) {
	ChessPiece* takenPiece = getBoardPiece(move_to);
	if (takenPiece == nullptr) {
		return false;
	}
	ChessPiece* takingPiece = getBoardPiece(move_from);
	if (takingPiece->pieceColour == takenPiece->pieceColour) {
		//cout << "You cannot take a piece of your own colour, fool!\n";
		return false;
	}
	return true;
};


/* Helper function to determine if a player is in check, by locating
 * the player's king, and then calling the squareUnderAttack function 
 * on the King's position */
bool ChessGame::isInCheck(Colour kingColour) {
	char kingPosition[2];
	try {
		for (int rank = 0; rank < 8; rank++) {
			for (int file = 0; file < 8; file++) {
				if (boardState[rank][file] == nullptr) {
					continue;
				}
				ChessPiece* cp = boardState[rank][file];
				if (dynamic_cast<King*>(cp) && cp->pieceColour == kingColour) {
					kingPosition[0] = file + 'A';
					kingPosition[1] = rank + '1';
					//once the king position found, see if it is under attack
					return squareUnderAttack(kingPosition, kingColour);
				}
			}
		}
		// failsafe in case king is not found, but should never be reached
		throw logic_error("The board is already missing a King, please reload a new board state");
	} catch (logic_error& error) {
		gameOver = true;
		throw; //rethrow the error
	}
}


/* Helper function to determine if a given square in the board is currently 
 * ine a line of attack from an opponent's piece */
bool ChessGame::squareUnderAttack(char const board_square[2], 
		Colour yourPieceColour) {
	int oppoPieceCount = (yourPieceColour == Colour::BLACK) ? whiteCount : blackCount;
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file <8; file++) {

			//avoid dereferencing a nullptr
			if (boardState[rank][file] == nullptr) {
				continue;
			}
			ChessPiece* cp = boardState[rank][file];
			if (cp->pieceColour != yourPieceColour) {
				char letterFile = file + 'A';
				char letterRank = rank + '1';
				char cpPosition[2] = {letterFile, letterRank};
				if (cp->isValidMove(cpPosition, board_square, this)) {
					return true;
				}
				oppoPieceCount--;
				// use of oppoPieceCount helps avoid iterating through entire board
				if (oppoPieceCount == 0) {
					return false;
				}
			}
		}
	}
	//flow of control should never reach this far but adding a failsafe 
	throw logic_error("Unreachable code in squareUnderAttack function; you are likely already missing a King "
				   "and need to reload the board state with a new game.");
}


/* Helper function to test if a proposed move that is valid by the rules of 
 * Chess takes a King into or out of Check */
bool ChessGame::willBeInCheck(Colour kingColour, char const move_from[2], 
		 char const move_to[2], bool isPieceTaken) {
	// Create a deep copy of the current board
	ChessGame copiedGame(*this);

	ChessPiece* movedPiece = copiedGame.getBoardPiece(move_from);

	//Commit the proposed move to the copied board
	//Dealing with possibility of capturing a piece or moving to an 
	//empty square
	if (isPieceTaken) {	
		ChessPiece* takenPiece = copiedGame.getBoardPiece(move_to);
		if (takenPiece != nullptr) {
			delete takenPiece;
			takenPiece = nullptr;
		}
		movedPiece->pieceColour == Colour::BLACK ? copiedGame.whiteCount-- : copiedGame.blackCount--;		
	}

	// Move the piece being moved to the new position on the copied board
	copiedGame.updateBoard(movedPiece, move_from, move_to);
	if (copiedGame.isInCheck(kingColour)) {
		//Defined destructor automatically destroy copiedGame upon returning
		return true;
	}
	return false;
}


/* Helper function to determine if a player has any valid moves left. If they
 * do not, and they are in check - then they are in checkmate - otherwise they
 * are in stalemate */
bool ChessGame::isInCheckOrStalemate(Colour kingColour) {
	int friendlyCount = (kingColour == Colour::BLACK) ? blackCount : whiteCount;
	//loop through the board to find pieces of your own colour
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
	
			if (boardState[rank][file] == nullptr) {
				continue;
			}
			if (boardState[rank][file]->pieceColour == kingColour) {
				char letterRank = rank + '1';
				char letterFile = file + 'A';
				char move_from[2] = {letterFile, letterRank};
				ChessPiece* friendlyPiece = getBoardPiece(move_from);

				//loop through all possible valid piece moves, to see if there are
				//any available that will get you out of Check
				for (char moveFile = 'A'; moveFile < 'I'; moveFile++) {
					for (char moveRank = '1'; moveRank < '9'; moveRank++) {
						char move_to[2] = {moveFile, moveRank};

						//check if the move would be valid by piece movement rules

						bool isPieceTaken = false;
						ChessPiece* takenPiece = getBoardPiece(move_to);
						if (takenPiece != nullptr) {
							if (kingColour == takenPiece->pieceColour) {
								continue; //invalid move
							}
							isPieceTaken = true;
						}
						if (friendlyPiece-> isValidMove(move_from, move_to, this)) {
							//if valid, check if the move frees the king from check
							if (!willBeInCheck(kingColour, move_from, move_to,
							                   isPieceTaken)) {
								return false; //i.e. not in checkmate
							}
						}

					}
				}
				/* once all board moves for that piece have been exhausted we 
				 * decrement the friendlyCount. Looking only for friendly pieces
				 * allows us to avoid iterating through entire board */
				friendlyCount--;
				if (friendlyCount == 0) {
					return true; //i.e. no friendly piece can get king out of check
				}
			}
		}
	}
	/* flow of control should never reach here
	 * isInCheckmate only ever called after isInCheck function, so if the board is missing a King, an error will
	 * already have been thrown by this isInCheck function */
	throw logic_error("Unreachable code reached in isInCheckmate function");
}



//Helper function to update board position after having confirmed the validity
//of a ChessMove
void ChessGame::updateBoard(ChessPiece* movedPiece, char const move_from[2], 
		char const move_to[2]) {
	int new_file_position = move_to[0] - 'A';
	int new_rank_position = move_to[1] - '1';
	boardState[new_rank_position][new_file_position] = movedPiece;
	int old_file_position = move_from[0] - 'A';
	int old_rank_position = move_from[1] - '1';
	boardState[old_rank_position][old_file_position] = nullptr;
}

bool ChessGame::isValidCoordinate(char const coord[2]) {
	return coord[0] >= 'A' && coord[0] <= 'H' && coord[1] >= '1' && coord[1] <= '8';
}


