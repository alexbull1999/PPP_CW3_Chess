#include"ChessGame.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessGame cg;

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cg.submitMove("D7", "D6");
	cout << '\n';

	cg.submitMove("D4", "H6");
	cout << '\n';

	cg.submitMove("D2", "D4");
	cout << '\n';

	cg.submitMove("F8", "B4");
	cout << '\n';

	cout << "=========================\n";
	cout << "Alekhine vs. Vasic (1931)\n";
	cout << "=========================\n\n";

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';

	cg.submitMove("E2", "E4");
	cg.submitMove("E7", "E6");
	cout << '\n';

	cg.submitMove("D2", "D4");
	cg.submitMove("D7", "D5");
	cout << '\n';

	cg.submitMove("B1", "C3");
	cg.submitMove("F8", "B4");
	cout << '\n';

	cg.submitMove("F1", "D3");
	cg.submitMove("B4", "C3");
	cout << '\n';

	cg.submitMove("B2", "C3");
	cg.submitMove("H7", "H6");
	cout << '\n';

	cg.submitMove("C1", "A3");
	cg.submitMove("B8", "D7");
	cout << '\n';

	cg.submitMove("D1", "E2");
	cg.submitMove("D5", "E4");
	cout << '\n';

	cg.submitMove("D3", "E4");
	cg.submitMove("G8", "F6");
	cout << '\n';

	cg.submitMove("E4", "D3");
	cg.submitMove("B7", "B6");
	cout << '\n';

	cg.submitMove("E2", "E6");
	cg.submitMove("F7", "E6");
	cout << '\n';

	cg.submitMove("D3", "G6");
	cout << '\n';


	/* Tests I wrote to check my try/catch exceptions deal gracefully with a
	 * state where no Kings are loaded on a board, or just one King is loaded

	cg.loadState("8/8/8/3p4/2P5/8/8/8 w - - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("C4", "C5");
	cg.displayBoard();
	cout << '\n';

	cg.loadState("8/8/8/3p4/2P5/8/8/4K3 w - - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("C4", "C5");
	cg.displayBoard();
	cout << '\n';

	////////End of exceptions tests */

	/* Tests for invalid board coordinates

	cg.loadState("8/8/8/3p4/2P5/8/8/8 w - - 0 1");
	cg.submitMove("K8", "B9");

	//end of tests */

	/* Testing castling kingside for black/white, then commenting out
	 * and testing castling queenside

	cg.loadState("r3k2r/pppppppp/8/8/8/8/PPPPPPPP/R3K2R w KQkq - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	//cg.submitMove("E1", "G1");
	//cg.submitMove("E8", "G8");
	cg.submitMove("E1", "C1");
	cg.submitMove("E8", "C8");
	cg.displayBoard();
	cout << '\n';

	// end of castling tests */

	/* Testing castling when it is invalid i.e. the castling
	 * bits have been disabled

	cg.loadState("r3k2r/pppp1ppp/8/8/8/8/PPPP1PPP/R3K2R w KQkq - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("E1", "E2"); //move king forward should disable white castling
	cg.submitMove("E8", "E7"); // mirror for black
	cg.submitMove("E2", "E1"); //move King back into home square
	cg.submitMove("E7", "E8"); //move King back into home square
	cg.submitMove("E1", "G1"); // try and castle
	cg.submitMove("E1", "E2"); // so it goes to black's turn
	cg.submitMove("E8", "G8"); //try to castle

	// end of tests */

	/* Testing castling when it is invalid i.e. the castling
	 * bits have been disabled this time by rooks

	cg.loadState("r3k2r/1ppp1ppp/8/8/8/8/PPPP1PP1/R3K2R w KQkq - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("H1", "H2"); //move rook forward should
	cg.submitMove("A8", "A7"); // mirror for black
	cg.submitMove("H2", "H1"); //move rook back
	cg.submitMove("A7", "A8"); //move rook back
	cg.submitMove("E1", "G1"); // try and castle
	cg.submitMove("E1", "E2"); // so it goes to black's turn
	cg.submitMove("E8", "C8"); //try to castle

	// end of tests */

	/* Testing castling through check or when in check
	cg.loadState("r3k2r/8/4Q3/8/8/7q/8/R3K2R w KQkq - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("E1", "G1"); //should be invalid, castling through check
	cg.submitMove("E1", "C1"); //should be valid, as white king not in check
	cg.submitMove("E8", "G8"); //should be invalid castling in check

	// ending castling tests */


	/* Testing stalemate behaving as expected and someone trying to
	 * play a move when in stalemate

	cg.loadState("7k/8/6K1/8/8/8/8/5Q2 w - - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("F1", "F7");
	cg.displayBoard();
	cg.submitMove("H8", "G8");

	// end of stalemate tests */

	/* Illegal move tests

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
	cout << '\n';
	cg.displayBoard();
	cg.submitMove("E2", "E5"); //invalid, pawns cannot move 3 squares
	cg.submitMove("D1", "D6"); //invalid, queens cannot jump over pieces
	cg.submitMove("B1", "D4"); //invalid, knights cannot jump that far
	cg.submitMove("B2", "B4"); //valid pawn move
	cg.submitMove("C7", "C5"); //valid pawn move
	cg.submitMove("A1", "B2"); //invalid, rooks cannot move diagonally
	cg.submitMove("C1", "B2"); //valid bishop move
	cg.submitMove("C8", "C7"); //invalid bishop move, cannot move vertically

	// end of illegal moves tests */

	/* Check and Checkmate Tests, and someone trying to play a move in checkmate

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/4q3/PPPPPPPP/3K4 b KQkq - 0 2");
	cout << '\n';
	cg.displayBoard();
	cg.submitMove("E3", "E2"); //this should put white in check
	cg.submitMove("D1", "E1"); //this should be invalid as king stays in check
	cg.submitMove("D1", "C1");
	cg.submitMove("E2", "E1"); // this should put white in checkmate
	cg.submitMove("C1", "B1"); // this should be invalid as already checkmate


	//Variations on the above tests

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/4q3/PPPPPPPP/3K3R b KQkq - 0 2");
	cout << '\n';
	cg.displayBoard();
	cg.submitMove("E3", "E2"); //this should put white in check
	cg.submitMove("D1", "E1"); //this should be invalid as  king stays in check
	cg.submitMove("H1", "E1"); // invalid as queen could still take diagonally
	cg.submitMove("D1", "C1"); // this should be valid
	cg.submitMove("E2", "E1"); // this should put white back in check
	cg.submitMove("H1", "E1"); // takes the queen, puts white out of check

	//further variations involving check with a knight
	cg.loadState("rnb1kb1r/pppppppp/8/8/8/4q3/nPPPPPPP/3K3R b KQkq - 0 2");
	cout << '\n';
	cg.displayBoard();
	cg.submitMove("A2", "C3"); //white in check through the knight
	cg.submitMove("H1", "E1"); //should be invalid
	cg.submitMove("D1", "C1"); //should be valid
	cg.submitMove("C3", "D1"); //valid but not in check
	cg.displayBoard();

	// end of check and checkmate tests */

	/* Someone starting a new game, submitting a move without calling loadState

	ChessGame cg2;
	cg2.submitMove("E2", "E4");
	cg2.submitMove("E3", "E5");

	// end of loadState tests */

	/* Someone trying to take their own piece
	 * and someone trying to move to the same square they're on

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("D1", "D2"); //invalid white queen cannot take white pawn
	cg.submitMove("D2", "D2"); //invalid pawns can't stand still
	cg.submitMove("A1", "A1"); //invalid rooks can't stand still
	cg.submitMove("B1", "B1"); //invalid knight
	cg.submitMove("C1", "C1"); //invalid bishop
	cg.submitMove("D1", "D1"); // invalid queen
	cg.submitMove("E1", "E1"); //invalid king

	// end of tests for invalid moves */



	/* Testing a long game - Bobby Fischer vs Ratmir Kholmov -
	 * (includes castling) and check

	cg.loadState("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("D2", "D4");
	cg.submitMove("G8", "F6");
	cg.submitMove("G1", "F3");
	cg.submitMove("G7", "G6");
	cg.submitMove("G2", "G3");
	cg.submitMove("F8", "G7");
	cg.submitMove("F1", "G2");
	cg.submitMove("E8", "G8");
	cg.submitMove("E1", "G1");
	cg.submitMove("D7", "D6");
	cg.submitMove("B1", "C3");
	cg.submitMove("B8", "D7");
	cg.submitMove("B2", "B3");
	cg.submitMove("E7", "E5");
	cg.submitMove("D4", "E5");
	cg.submitMove("D6", "E5");
	cg.submitMove("E2", "E4");
	cg.submitMove("F8", "E8");
	cg.submitMove("C1", "A3");
	cg.submitMove("C7", "C6");
	cg.submitMove("A3", "D6");
	cg.submitMove("D8", "A5");
	cg.submitMove("D1", "D3");
	cg.submitMove("E8", "E6");
	cg.submitMove("B3", "B4");
	cg.submitMove("A5", "A3");
	cg.submitMove("D6", "C7");
	cg.submitMove("A3", "B4");
	cg.submitMove("A1", "B1");
	cg.submitMove("B4", "E7");
	cg.submitMove("F1", "D1");
	cg.submitMove("F6", "E8");
	cg.submitMove("C7", "A5");
	cg.submitMove("E6", "D6");
	cg.submitMove("D3", "E2");
	cg.submitMove("D6", "D1");
	cg.submitMove("E2", "D1");
	cg.submitMove("G7", "F8");
	cg.submitMove("F3", "D2");
	cg.submitMove("E7", "A3");
	cg.submitMove("D2", "C4");
	cg.submitMove("A3", "C5");
	cg.submitMove("G2", "F1");
	cg.submitMove("B7", "B5");
	cg.submitMove("C4", "D2");
	cg.submitMove("C5", "A3");
	cg.submitMove("D2", "B3");
	cg.submitMove("D7", "C5");
	cg.submitMove("F1", "B5");
	cg.submitMove("C6", "B5");
	cg.submitMove("C3", "B5");
	cg.submitMove("A3", "A4");
	cg.submitMove("B3", "C5");
	cg.submitMove("A4", "A5");
	cg.submitMove("D1", "D5");
	cg.submitMove("A8", "B8");
	cg.submitMove("A2", "A4");
	cg.submitMove("C8", "H3");
	cg.submitMove("D5", "E5");
	cg.submitMove("B8", "C8");
	cg.submitMove("C5", "D3");
	cg.submitMove("A5", "A4");
	cg.submitMove("D3", "E1");
	cg.submitMove("A7", "A6");
	cg.displayBoard();

	// End of Fischer vs Kholmov test */


	return 0;
}
