chess: ChessMain.o ChessGame.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o
	g++ -g -Wall ChessMain.o ChessGame.o ChessPiece.o Pawn.o Rook.o Knight.o Bishop.o Queen.o King.o -o chess

ChessMain.o: ChessMain.cpp ChessGame.h
	g++ -g -Wall -c ChessMain.cpp

ChessGame.o: ChessGame.cpp ChessGame.h ChessPiece.h Pawn.h Rook.h Knight.h Bishop.h Queen.h King.h
	g++ -g -Wall -c ChessGame.cpp

ChessPiece.o: ChessPiece.cpp ChessPiece.h
	g++ -g -Wall -c ChessPiece.cpp

Pawn.o: Pawn.cpp ChessPiece.h Pawn.h
	g++ -g -Wall -c Pawn.cpp

Rook.o: Rook.cpp Rook.h ChessPiece.h
	g++ -g -Wall -c Rook.cpp

Knight.o: Knight.cpp Knight.h ChessPiece.h
	g++ -g -Wall -c Knight.cpp

Bishop.o: Bishop.cpp Bishop.h ChessPiece.h
	g++ -g -Wall -c Bishop.cpp

Queen.o: Queen.cpp Queen.h ChessPiece.h
	g++ -g -Wall -c Queen.cpp

King.o: King.cpp King.h ChessPiece.h
	g++ -g -Wall -c King.cpp

clean:
	rm -f *.o execute
