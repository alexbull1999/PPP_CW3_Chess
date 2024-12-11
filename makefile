#Compiler and flags
CXX := g++
CXXFLAGS := -g -Wall

#Files
SRC := ChessMain.cpp ChessGame.cpp ChessPiece.cpp Pawn.cpp Rook.cpp Knight.cpp Bishop.cpp Queen.cpp King.cpp
OBJ := $(SRC:.cpp=.o)
EXEC := chess

#Default target
all: $(EXEC)

#Linking
$(EXEC): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $@

#Compilation
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

#Clean target
.PHONY: clean
clean:
	rm -f $(OBJ) $(EXEC)


