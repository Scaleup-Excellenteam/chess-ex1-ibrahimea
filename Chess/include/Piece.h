#pragma once
#include <string>
#include <cstdlib>
#include <cmath>

class Piece {
public:
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const = 0;
    virtual ~Piece() {}
};


class Rook : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};


class Bishop : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};


class Queen : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

class Knight : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};


class King : public Piece {
public:
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
};

class Pawn : public Piece {
public:
    Pawn(bool isWhite) : m_isWhite(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const std::string &board) const override;
private:
    bool m_isWhite;
};

Piece* createPiece(char piece);
