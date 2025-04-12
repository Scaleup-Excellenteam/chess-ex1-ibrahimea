#pragma once
#include <string>
#include <cstdlib>
#include <cmath>

// Abstract base class for a chess piece.
class Piece {
public:
    // Validate the move based on source/destination indices (0–7) and the board string.
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const = 0;
    virtual ~Piece() {}
};

// Rook – moves horizontally or vertically.
class Rook : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

// Bishop – moves diagonally.
class Bishop : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

// Queen – combines rook and bishop movement.
class Queen : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

// Knight – moves in an L-shape.
class Knight : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

// King – moves one square in any direction.
class King : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

// Pawn – moves forward (without diagonal capture).
// Note: We use a bool member to record its color.
// In our solution: white pieces are in lowercase so m_isWhite==true means white,
// and black pieces are in uppercase so m_isWhite==false.
class Pawn : public Piece {
public:
    Pawn(bool isWhite) : m_isWhite(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
private:
    bool m_isWhite;
};

// Factory function: Given a piece character, return a pointer to the appropriate Piece object.
// For our mapping, lowercase letters (r, n, b, q, k, p) are white and uppercase (R, N, B, Q, K, P) are black.
Piece* createPiece(char piece);
