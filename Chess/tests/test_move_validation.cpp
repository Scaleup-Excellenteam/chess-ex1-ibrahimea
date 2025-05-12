#include <cassert>
#include "../include/Piece.h"
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
    string board = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR";
    int code = validateMove(board, true, "b2b3");
    assert(code == 42);
    code = validateMove(board, true, "b2c2");
    assert(code == 21);
    code = validateMove(board, true, "d4d5");
    assert(code == 11);
    code = validateMove(board, true, "b2a1");
    assert(code == 13);

    cout << "All tests passed." << endl;
}

int main() {
    runTests();
    return 0;
}
