#include "../include/Piece.h"
#include "../include/Chess.h"
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
  
    string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
    Chess a(board);
    string localBoard = board;
    bool isWhiteTurn = true;
    int codeResponse = 0;
    string res = a.getInput(); 
    while (res != "exit")
    {

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
    bool srcIsWhite = (srcPiece >= 'A' && srcPiece <= 'Z');
    if (isWhiteTurn && !srcIsWhite)
        return 12;
    if (!isWhiteTurn && srcIsWhite)
        return 12;

    if (destPiece != '#' && destPiece != ' ')
    {
        bool destIsWhite = (destPiece >= 'A' && destPiece <= 'Z');
        if (isWhiteTurn && destIsWhite)
            return 13;
        if (!isWhiteTurn && !destIsWhite)
            return 13;
    }


    Piece *piece = createPiece(srcPiece);
    if (piece == nullptr)
        return 21; // Unknown piece.

    bool valid = piece->isValidMove(srcRow, srcCol, destRow, destCol, boardState);
    delete piece;

    if (!valid)
        return 21;
    return 42;
}
