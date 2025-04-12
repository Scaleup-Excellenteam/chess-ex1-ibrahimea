#include "Pieces.h"
#include "Chess.h"
#include <iostream>
#include <string>
using namespace std;

// validateMove returns one of the error codes:
// 11 – no piece at source
// 12 – piece belongs to the opponent
// 13 – destination square already holds a friendly piece
// 21 – move does not follow the piece's movement rules
// 42 – legal move
int validateMove(const string &boardState, bool isWhiteTurn, const string &move);

int main()
{
    // Initial board string (64 characters, row-major order):
    // White pieces are lowercase, Black pieces are uppercase.
    // Row 0: white major pieces, row 1: white pawns, rows 2-5: empty,
    // row 6: black pawns, row 7: black major pieces.
    string board = "rnbqkbnrpppppppp################################PPPPPPPPRNBQKBNR";

    // Create the Chess object (do not change Chess.h/Chess.cpp).
    Chess a(board);

    // Maintain a local board copy (64-character string).
    string localBoard = board;

    // isWhiteTurn == true means it is White's turn (white pieces are lowercase).
    bool isWhiteTurn = true;

    int codeResponse = 0;
    string res = a.getInput();  // getInput() handles input and board display.
    while (res != "exit")
    {
        // Validate the move using our polymorphic piece classes.
        codeResponse = validateMove(localBoard, isWhiteTurn, res);
        cout << "code response computed: " << codeResponse << endl;

        // Set the response code in the Chess engine.
        a.setCodeResponse(codeResponse);

        // If the move is legal (42), update the local board and switch turn.
        if (codeResponse == 42)
        {
            int srcRow = res[0] - 'a';
            int srcCol = res[1] - '1';
            int destRow = res[2] - 'a';
            int destCol = res[3] - '1';
            int srcIndex = srcRow * 8 + srcCol;
            int destIndex = destRow * 8 + destCol;
            char piece = localBoard[srcIndex];
            localBoard[srcIndex] = '#';
            localBoard[destIndex] = piece;
            // Switch turn.
            isWhiteTurn = !isWhiteTurn;
        }

        res = a.getInput();
    }

    cout << endl << "Exiting " << endl;
    return 0;
}

int validateMove(const string &boardState, bool isWhiteTurn, const string &move)
{
    // Convert move string positions to board indices.
    int srcRow = move[0] - 'a';
    int srcCol = move[1] - '1';
    int destRow = move[2] - 'a';
    int destCol = move[3] - '1';
    int srcIndex = srcRow * 8 + srcCol;
    int destIndex = destRow * 8 + destCol;

    char srcPiece = boardState[srcIndex];
    char destPiece = boardState[destIndex];

    // Error 11: No piece at source.
    if (srcPiece == '#' || srcPiece == ' ')
        return 11;

    // Determine piece color.
    // In this scheme, white is lowercase.
    bool srcIsWhite = (srcPiece >= 'a' && srcPiece <= 'z');
    if (isWhiteTurn && !srcIsWhite)
        return 12;
    if (!isWhiteTurn && srcIsWhite)
        return 12;

    // Error 13: Destination square already contains a friendly piece.
    if (destPiece != '#' && destPiece != ' ')
    {
        bool destIsWhite = (destPiece >= 'a' && destPiece <= 'z');
        if (isWhiteTurn && destIsWhite)
            return 13;
        if (!isWhiteTurn && !destIsWhite)
            return 13;
    }

    // Create the appropriate piece validator using our factory.
    Piece *piece = createPiece(srcPiece);
    if (piece == nullptr)
        return 21; // Unknown piece.

    bool valid = piece->isValidMove(srcRow, srcCol, destRow, destCol, boardState);
    delete piece;

    if (!valid)
        return 21;
    return 42;
}
