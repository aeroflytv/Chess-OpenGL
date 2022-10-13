#pragma once

#include <vector>
#include <glm/glm.hpp>

#include "Piece.h"

enum TileType
{
  Black,
  White
};

struct RenderIDs
{
  u_int32_t va;
  u_int32_t vb;
  u_int32_t ib;
  u_int32_t program;
};

struct Tiles
{
  int Row;
  int Col;
  std::pair<int, int> XPos;
  std::pair<int, int> YPos;

  glm::mat4 MVP;
  RenderIDs RenderIds;
  Piece *Piece = nullptr;
  bool IsPossibleMoveTexEnabled = false;
  u_int32_t PossibleMoveTex;
};

struct Boundaries
{
  std::pair<int, int> XBoundary;
  std::pair<int, int> YBoundary;
};

class Board
{
public:
  Board(int screenWidth, int screenHeight);

  void Init();
  void Draw();
  void Close();

  void PlaceChessPiece(Piece &piece);
  void RemoveChessPiece(Piece &piece);
  void DrawPiecePossibleMoves(Piece &piece);

  inline std::vector<Tiles> GetEmptyTiles() { return m_EmptyTiles; };
  inline std::vector<Tiles> GetTiles() { return m_Tiles; };

  inline void PushEmptyTile(const Tiles &tile)
  {
    m_EmptyTiles.push_back(tile);
  }
  inline Boundaries GetTileBoundaries(int row, int col)
  {
    const auto &tiles = m_Tiles;
    for (const auto &tile : tiles)
    {
      if (tile.Row == row && tile.Col == col)
      {
        return {tile.XPos, tile.YPos};
      }
    }
    return {{0, 0}, {0, 0}};
  }

private:
  void CreateTile(TileType type, int idx, float x, float y, float *vertices, u_int32_t *indices, int row, int col);
  void InitPossibleMoveTex();

private:
  std::vector<Tiles> m_Tiles;
  std::vector<Tiles> m_EmptyTiles;
  std::pair<int, int> m_WindowSize;
  glm::mat4 m_MVP;
  u_int32_t m_PossibleMoveTex;
};
