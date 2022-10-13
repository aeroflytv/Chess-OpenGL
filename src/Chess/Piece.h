#pragma once

#include <sys/_types/_u_int32_t.h>
#include <vector>

struct PiecePosition
{
  int Row;
  int Col;
};

enum class PieceType
{
  Pawn1,
  Pawn2,
  Pawn3,
  Pawn4,
  Pawn5,
  Pawn6,
  Pawn7,
  Pawn8,
  Rook1,
  Rook2,
  Knight1,
  Knight2,
  Bishop1,
  Bishop2,
  Queen,
  King
};

enum class PieceCategory
{
  Pawn,
  Rook,
  Knight,
  Bishop,
  Queen,
  King
};

enum class PieceColor
{
  White,
  Black
};

class Piece
{
public:
  Piece(PieceType type, PieceColor color);

  inline PiecePosition GetPosition() { return m_Pos; };
  inline PieceType GetType() { return m_Type; };
  inline PieceColor GetColor() { return m_Color; };
  inline u_int32_t GetTexture() { return m_Texture; };
  inline PieceCategory GetCategory() { return m_Category; };
  inline std::vector<PiecePosition> GetPossibleMoves() { return m_PossibleMoves; };

  inline void PushPossibleMoves(PiecePosition pos) { m_PossibleMoves.push_back(pos); };
  inline void SetPosition(PiecePosition pos) { m_Pos = pos; };

private:
  PieceCategory m_Category;
  PiecePosition m_Pos;
  PieceType m_Type;
  PieceColor m_Color;
  std::vector<PiecePosition> m_PossibleMoves;
  u_int32_t m_Texture;
};
