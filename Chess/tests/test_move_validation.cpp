#include "Pieces.h"
#include <cassert>
#include <iostream>
#include <string>
using namespace std;

int validateMove(const string &boardState, bool isWhiteTurn, const string &move)
{
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';
    int srcIndex = srcRow * 8 + srcCol;
    int destIndex = destRow * 8 + destCol;

    char srcPiece = boardState[srcIndex];
    char destPiece = boardState[destIndex];

    if (srcPiece == '#' || srcPiece == ' ')
        return 11;

    bool srcIsWhite = (srcPiece >= 'a' && srcPiece <= 'z');
    if (isWhiteTurn && !srcIsWhite)
        return 12;
    if (!isWhiteTurn && srcIsWhite)
        return 12;

    if (destPiece != '#' && destPiece != ' ')
    {
        bool destIsWhite = (destPiece >= 'a' && destPiece <= 'z');
        if (isWhiteTurn && destIsWhite)
            return 13;
        if (!isWhiteTurn && !destIsWhite)
            return 13;
    }

    Piece* piece = createPiece(srcPiece);
    if (piece == nullptr)
        return 21;
    bool valid = piece->isValidMove(srcRow, srcCol, destRow, destCol, boardState);
    delete piece;

    if (!valid)
        return 21;
    return 42;
}

void runTests() {
    // Arrange an initial board string: white pieces (lowercase) at the top, black pieces (uppercase) at the bottom.
    string board = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR";

    // Test 1: Legal move for a white pawn (e.g., "b2b3")
    int code = validateMove(board, true, "b2b3");
    assert(code == 42);

    // Test 2: Illegal sideways move for a white pawn (e.g., "b2c2")
    code = validateMove(board, true, "b2c2");
    assert(code == 21);

    // Test 3: No piece at source (e.g., an empty square "d4d5")
    code = validateMove(board, true, "d4d5");
    assert(code == 11);

    // Test 4: Destination already occupied by a friendly piece (e.g., white pawn "b2a1" moving onto a white piece)
    code = validateMove(board, true, "b2a1");
    assert(code == 13);

    cout << "All tests passed." << endl;
}

int main() {
    runTests();
    return 0;
}
