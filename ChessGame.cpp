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

// Set default ChessGame constructor to initialize boardState array to nullptrs
ChessGame::ChessGame() : boardState(), whiteCount(0), blackCount(0) {};

//loadState function

void ChessGame::loadState(char const board_string[MAX_FSN_LENGTH]) {
	// clean the ChessGame board so any preexisting memory is deleted and
	// assigned to nullptrs (important as we are calling loadState
	// several times on the same ChessGame object) 
	for (int rank_counter = 0; rank_counter < 8; rank_counter++) {
		for (int file_counter = 0; file_counter < 8; file_counter++) {
			if (boardState[rank_counter][file_counter] == nullptr) {
				continue;
			}
			else {
				delete boardState[rank_counter][file_counter];
				boardState[rank_counter][file_counter] = nullptr;
			}
		}
	}
	//reset whiteCount and blackCount to 0; in case they were previously
	//initialised from a different board state. And castling options.
	whiteCount = 0;
	blackCount = 0;
	//using 4 digit binary number to represent castling options
	castlingOptions = 0b0000; 


	// now create new board state, having deleted previous board
	// We combine all counters into one loiop to maximise efficiency
	// We use a helper function isValidPiece to defensively check the validity
	// of the FSN notation provided to us
	// NOTE: ADD SOME TRY/CATCH EXCEPTION HANDLING
	int FSNCounter = 0;
	for (int rank_counter = 7, file_counter = 0; board_string[FSNCounter] != ' ';
			FSNCounter++) {
		
		if (rank_counter < 0) {
			cerr << "Warning - error; rank_counter has gone below 0";
		}

		if (isValidPiece(board_string[FSNCounter], rank_counter, file_counter)) {
			file_counter++;
			continue;
		}

		else if (board_string[FSNCounter] >= '1' && 
				board_string[FSNCounter] <= '8') {
			for (int emptyCount = '0'; emptyCount < board_string[FSNCounter]; 
					emptyCount++) {
				boardState[rank_counter][file_counter] = nullptr;
				file_counter++;
			}
		}

		else if (board_string[FSNCounter] == '/') {
			file_counter = 0;
			rank_counter--;
		}

		else {
			cerr << "Invalid FSN notation inputted - cannot load game\n";
			exit(1);
		}
	}
	//at this point FSNCounter has now hit the first space in the FSN string
	//so we can determine whose move it is. Doing it this way allows us to load 
	//chess states halfway through games, where black has the 'first' turn
	FSNCounter++;
	if (board_string[FSNCounter] == 'w') {
		whoseTurn = Colour::WHITE;
	}
	else if (board_string[FSNCounter] == 'b') {
		whoseTurn = Colour::BLACK;
	}
	else {
		cerr << "Invalid FSN notation inputted - cannot load game \n";
		exit(1);
	}
	FSNCounter += 2; //skips over the space onto first castling characters

	// we know there is a max of 4 castling characters, and that as soon as
	// we encounter a - or the sentinel value (end of string) we should stop
	
	for (int limit = FSNCounter + 4; FSNCounter <= limit; FSNCounter++ ) { //test edge cases
		if (board_string[FSNCounter] == '-' || board_string[FSNCounter] == '\0') {
			cout << "A new board state is loaded!\n";
			return;
		}
		else if (board_string[FSNCounter] == 'K') {
			//White can castle kingside, stored as bit 0 of castlingOptions
			castlingOptions |= 0b0001; //using bitwise or
		}
		else if (board_string[FSNCounter] == 'Q') {
			//White can castle queenside, stored as bit 1
			castlingOptions |= 0b0010;
		}
		else if (board_string[FSNCounter] == 'k') {
			//black can castle kingside, stored as bit 2
			castlingOptions |= 0b0100;
		}
		else if (board_string[FSNCounter] == 'q') {
			//black can castle queenside, stored as bit 3
			castlingOptions |= 0b1000;
		}
	}
	

	throw logic_error("Unreachable code reached in load_state function");
}

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

//overloading ostream operator for name enum
ostream& operator << (ostream& os, Name& name) {
	switch(name)
	{
		case Name::PAWN:
			os << "Pawn";
			break;
		case Name::ROOK:
			os << "Rook";
			break;
		case Name::KNIGHT:
			os << "Knight";
			break;
		case Name::BISHOP:
			os << "Bishop";
			break;
		case Name::QUEEN:
			os << "Queen";
			break;
		case Name::KING:
			os << "King";
			break;
	}
	return os;
}



void ChessGame::submitMove(char const move_from[2], char const move_to[2]) {
	// check the move coordinates are valid to start with
	if (move_from[0] > 'H' || move_from[0] < 'A' || move_from[1] > '8' || 
			move_from[1] < '1' || move_to[0] > 'H' || move_to[0] < 'A' || move_to[1]
			> '8' || move_to[1] < '1') {
		cout << "Invalid board coordinates submitted\n";
		return;
	}
	
	ChessPiece* movedPiece = getBoardPiece(move_from);
	if (movedPiece == nullptr) {
		cout << "There is no piece at position " << move_from << "!\n";
		return;
	}
	else if(movedPiece->pieceColour != whoseTurn) {
		cout << "It is not " << movedPiece->pieceColour << "'s turn to move!\n";
		return;
	}
	
	//setting an isPieceTaken parameter, that is updated to true if there is an
	//enemy piece in the move_to square. this is passed as a reference param to
	//isValidMove, and if the move is invalid, then this is changed back to false
	//so that the enum MoveOutcome and bitwise or operation still works
	bool isPieceTaken = false;

	//We can also check at this point already if the move_to square is already
	//occupied by a piece of the same colour, as the piece trying to move - as
	//this is always invalid, we can avoid bothering to check the more complicated
	//piece move logic in isValidMove
	ChessPiece* takenPiece = getBoardPiece(move_to);
	if (takenPiece != nullptr) { //check first to not derefence nullptr
		if (movedPiece->pieceColour == takenPiece->pieceColour) {
			cout << whoseTurn << "'s" << movedPiece->pieceName << " cannot move to "
				<< move_to << "!\n";
		}
		else {
			isPieceTaken = true;
		}
	}

	bool validMove = movedPiece->isValidMove(move_from, move_to, this, 
			isPieceTaken); //this updates isPieceTaken to true or false

	// you can't play a move that puts yourself in check even if it follows
	// piece placement rules - we need to check this separately
	if (validMove && willBeInCheck(whoseTurn, move_from, move_to, isPieceTaken)) {
		cout << whoseTurn << "'s " << movedPiece->pieceName << " cannot move to "
			<< move_to << "!\n";
		return;
	}
	
	int validFlag = validMove ? 0b01 : 0b00;
	int captureFlag = isPieceTaken ? 0b10 : 0b00;
	//Now we can do a bitwise or and reassign the value to the 
	//MoveOutcome enum
	MoveOutcome outcome = static_cast<MoveOutcome>(validFlag | captureFlag);
	
	switch(outcome) {
		case NOT_VALID_MOVE:
		{
			cout << whoseTurn << "'s " << movedPiece->pieceName << " cannot move to " <<
				move_to << "!\n";
			return;			
		}
		
		case VALID_WITH_CAPTURE: 
		{
			cout << whoseTurn << "'s " << movedPiece->pieceName << " moves from " <<
				move_from << " to " << move_to << " taking " << takenPiece->pieceColour
				<< "'s " << takenPiece->pieceName << "\n";
			//delete the taken piece from the board
			delete takenPiece;
			takenPiece = nullptr;

			// decrement the pieceCounter for the colour whose piece has been taken
			movedPiece->pieceColour == Colour::BLACK ? whiteCount-- : blackCount--;
			break;
		}
		
		case VALID_NO_CAPTURE:
		{
			cout << whoseTurn << "'s " <<  movedPiece->pieceName << " moves from " <<
				move_from << " to " << move_to << endl;
		}
	}

	// we can now move the piece to its new position, and assign its old
	// position to a nullptr; and change whose turn it is
	updateBoard(movedPiece, move_from, move_to);
	whoseTurn = (whoseTurn == Colour::BLACK) ? Colour::WHITE : Colour::BLACK;

	//Before returning, we need to check if the person whoseTurn is now next is
	//now in check or in checkmate

	//We check for check first, as you cannot be in checkmate without check
	if (isInCheck(whoseTurn)) {
		if (isInCheckOrStalemate(whoseTurn)) {
			cout << whoseTurn << " is in checkmate\n";
		}
		else {
			cout << whoseTurn << " is in check\n";
		}
	}
	else if (isInCheckOrStalemate(whoseTurn)) {
		cout << whoseTurn << " is in stalemate\n";
	}

	return;
}


/* A function I used during coding to check the loadState function was working
 * as expected */
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


// Defensive programming to ensure first part of FSN string to load
// a Chess Game is as expected; even if spec says we can assume its
// valid
bool ChessGame::isValidPiece(char letter, int rank_counter, int file_counter) {

	if (!isalpha(letter)) {
		return false;
	}

	Colour pieceColour = isupper(letter) ? Colour::WHITE : Colour::BLACK;
	ChessPiece* cp = nullptr;

// Switch only on the letter
// default to null ptr and return false
// return true only if not... 


	switch (tolower(letter)) {
		case 'p': {
								cp = new Pawn(pieceColour, Name::PAWN);
								break;
							}
		case 'r': {
								cp = new Rook(pieceColour, Name::ROOK);
								break;
							}
		case 'n': {
								cp = new Knight(pieceColour, Name::KNIGHT);
								break;
							}
		case 'b': {
								cp = new Bishop(pieceColour, Name::BISHOP);
								break;
							}
		case 'q': {
								cp = new Queen(pieceColour, Name::QUEEN);
								break;
							}
		case 'k': {
								cp = new King(pieceColour, Name::KING);
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
	else {
		boardState[rank_counter][file_counter] = cp;
		pieceColour == Colour::BLACK ? blackCount++ : whiteCount++;
		return true;
	}

}

//Overloading the copy constructor for ChessGame objects
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
}

//Defining the destructor so we clean up heap allocated memory properly
ChessGame::~ChessGame() {
	for (int rank_counter = 7; rank_counter >= 0; rank_counter--) {
		for (int file_counter = 0; file_counter < 8; file_counter++) {
			delete boardState[rank_counter][file_counter];
			boardState[rank_counter][file_counter] = nullptr;
		}
	}
}

//Assignment operator for deep copying
//Note I don't actually use this assignment operator anywhere in my code
//but it is good practice with the rule of 3, to also overload this
//given I have overloaded the copy constructor
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




//capturesPiece function to determine if a submitted move leads to a piece being
//taken
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



//getBoardPiece "getter" function
ChessPiece* ChessGame::getBoardPiece(char const boardPosition[2]) {
	int file_counter = boardPosition[0] - 'A';
	int rank_counter = boardPosition[1] - '1'; 
	ChessPiece* cp = boardState[rank_counter][file_counter];
	return cp;
}


//getKing "getter" function
bool ChessGame::isInCheck(Colour kingColour) {
	//we need to allocate the King's position to the heap
	//so it doesn't get deleted as a local variable and can be
	//passed onto the checkingCheck function
	char* kingPosition = new char[2];
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
			if (boardState[rank][file] == nullptr) {
				continue;				
			}
			else {
				ChessPiece* cp = boardState[rank][file];
				if (cp->pieceName == Name::KING && cp->pieceColour == kingColour) {
					kingPosition[0] = file + 'A';
					kingPosition[1] = rank + '1';
					//once king position found, see if it is under attack
					bool isCheck = squareUnderAttack(kingPosition, kingColour);
					delete[] kingPosition; //Free the heap allocated memory
					return isCheck ? true : false;
				}
			}
		}
	}
	// failsafe in case king is not found for whatever reason
	delete[] kingPosition;
	throw logic_error("Unreachable code reached in isInCheck function");
}

bool ChessGame::squareUnderAttack(char const board_square[2], 
		Colour yourPieceColour) {
	int oppoPieceCount = (yourPieceColour == Colour::BLACK) ? whiteCount : blackCount;
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file <8; file++) {

			//avoid dereferencing a nullptr
			if (boardState[rank][file] == nullptr) {
				continue;
			}
			else {
				ChessPiece* cp = boardState[rank][file];
				if (cp->pieceColour != yourPieceColour) {
					char letterFile = file + 'A';
					char letterRank = rank + '1';
					char cpPosition[2] = {letterFile, letterRank};
					//by default isPieceTaken is true, here as we are checking if the
					//square is under attack from an enemy piece.
					bool isPieceTaken = true;
					if (cp->isValidMove(cpPosition, board_square, this, isPieceTaken)) {
						return true;
					}
					else {
						oppoPieceCount--;
						// use of oppoPieceCount helps avoid iterating through entire board
						if (oppoPieceCount == 0) {
							return false;
						}
					}
				}
			}
		}
	}
	//flow of control should never reach this far but adding a failsafe 
	throw logic_error("Unreachable code reached in squareUnderAttack function");
}


// Testing if a proposed move that is valid by the rules of Chess takes a King
// out of Check
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

	// Move the piece being moved to the new position on the copied
	// board
	copiedGame.updateBoard(movedPiece, move_from, move_to);
	if (copiedGame.isInCheck(kingColour)) {
		//destructor overloading should automatically destroy copiedGame as it is
		//a local variable
		return true;
	}
	else {
		return false;
	}
}


bool ChessGame::isInCheckOrStalemate(Colour kingColour) {
	int friendlyCount = (kingColour == Colour::BLACK) ? blackCount : whiteCount;
	//loop through the board to find pieces of your own colour
	for (int rank = 0; rank < 8; rank++) {
		for (int file = 0; file < 8; file++) {
	
			if (boardState[rank][file] == nullptr) {
				continue;
			}
			else if (boardState[rank][file]->pieceColour == kingColour) {
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
						//Copying the logic of submitMove, checking first for if a piece
						//will be taken				
						bool isPieceTaken = false;
						ChessPiece* takenPiece = getBoardPiece(move_to);
						if (takenPiece != nullptr) { //check first to not derefence nullptr
							if (kingColour == takenPiece->pieceColour) {
								continue; //invalid move as you can't move to a square of own colour
							}
							else {
								isPieceTaken = true;
							}
						}
						if (friendlyPiece-> isValidMove(move_from, move_to, this, isPieceTaken)) {
							//if valid, check if the move results in the king free from check
							if (!willBeInCheck(kingColour, move_from, move_to, isPieceTaken)) {
								return false; //i.e. not in checkmate
							}
						}

					}
				}
				// once all board moves for that piece have been exhausted we can
				// decrement the friendlyCount, and look for the next friendly piece
				// allows us to avoid iterating through entire board
				friendlyCount--;
				if (friendlyCount == 0) {
					return true; //i.e. no friendly piece can get king out of check
				}
			}
		}
	}
	//flow of control should never reach here
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
