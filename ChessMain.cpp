#include"ChessGame.h"

#include<iostream>

using std::cout;

int main() {

	cout << "========================\n";
	cout << "Testing the Chess Engine\n";
	cout << "========================\n\n";

	ChessGame cg;

	//

	cg.loadState("8/8/8/3p4/2P5/8/8/8 w - - 0 1");
	cout << '\n';
	cg.displayBoard();
	cout << '\n';
	cg.submitMove("C4", "C5");
	cg.displayBoard();
	cout << '\n';

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

	//

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

	return 0;
}
