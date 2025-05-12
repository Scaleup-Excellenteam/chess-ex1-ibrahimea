#include "../include/Piece.h"


static bool isPathClear(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) {
    int dRow = (destRow > srcRow) ? 1 : (destRow < srcRow ? -1 : 0);
    int dCol = (destCol > srcCol) ? 1 : (destCol < srcCol ? -1 : 0);
    int curRow = srcRow + dRow, curCol = srcCol + dCol;
    while (curRow != destRow || curCol != destCol) {
        if (board[curRow * 8 + curCol] != '#' && board[curRow * 8 + curCol] != ' ')
            return false;
        curRow += dRow;
        curCol += dCol;
    }
    return true;
}


bool Rook::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const {
    if (srcRow != destRow && srcCol != destCol)
        return false;
    return isPathClear(srcRow, srcCol, destRow, destCol, board);
}

// Bishop: must move diagonally.
bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const {
    if (std::abs(destRow - srcRow) != std::abs(destCol - srcCol))
        return false;
    return isPathClear(srcRow, srcCol, destRow, destCol, board);
}

// Queen: can move as a rook or bishop.
bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const {
    if (srcRow == destRow || srcCol == destCol || std::abs(destRow - srcRow) == std::abs(destCol - srcCol))
        return isPathClear(srcRow, srcCol, destRow, destCol, board);
    return false;
}

// Knight: moves in an L-shape.
bool Knight::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const {
    int dRow = std::abs(destRow - srcRow);
    int dCol = std::abs(destCol - srcCol);
    return (dRow == 2 && dCol == 1) || (dRow == 1 && dCol == 2);
}

// King: moves one square in any direction.
bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const {
    int dRow = std::abs(destRow - srcRow);
    int dCol = std::abs(destCol - srcCol);
    return (dRow <= 1 && dCol <= 1);
}

// Pawn: moves straight ahead.
// For white (m_isWhite true), the pawn moves downward (increasing row).
// For black (m_isWhite false), it moves upward (decreasing row).
bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const {
    // Must move straight (same column).
    if (srcCol != destCol)
        return false;

    if (m_isWhite) {
        // White pawn: one step forward.
        if (destRow - srcRow == 1)
            return true;
        // Two steps forward from starting row (row 1).
        if (srcRow == 1 && destRow - srcRow == 2) {
            if (board[(srcRow + 1) * 8 + srcCol] == '#' || board[(srcRow + 1) * 8 + srcCol] == ' ')
                return true;
        }
    } else {
        // Black pawn: one step forward (moving upward).
        if (srcRow - destRow == 1)
            return true;
        // Two steps forward from starting row (row 6).
        if (srcRow == 6 && srcRow - destRow == 2) {
            if (board[(srcRow - 1) * 8 + srcCol] == '#' || board[(srcRow - 1) * 8 + srcCol] == ' ')
                return true;
        }
    }
    return false;
}

Piece* createPiece(char piece) {
    bool isWhite = (piece >= 'a' && piece <= 'z'); // White if lowercase.
    char p = toupper(piece);
    switch (p) {
        case 'R': return new Rook();
        case 'B': return new Bishop();
        case 'Q': return new Queen();
        case 'N': return new Knight();
        case 'K': return new King();
        case 'P': return new Pawn(isWhite);
        default:  return nullptr;
    }
}
