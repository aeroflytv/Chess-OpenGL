#pragma once
#include <string>

#include "Core/MouseEvent.h"
#include "Board.h"
#include "Core/Window.h"

class Chess
{
public:
  Chess(int width, int height);
  ~Chess();

  void Init();

  void UpdateBoard();
  void HandleCursorEvent(MouseCursorEvent &cursorEvent);
  void HandlePlayerFocusPiece(MouseButtonEvent &buttonEvent);
  void DispatchPlayerMoves(MouseButtonEvent &buttonEvent);

private:
  void MovePiece(Piece &piece, PiecePosition newPos);
  void CalculatePossibleMoves(Piece &piece);

private:
  PieceColor m_WhosTurn = PieceColor::White;
  Tiles *m_CurrentHoveredTile;
  Piece *m_CurrentFocusedPiece;
  Board *m_Board;
  WindowData m_WindowData;
  std::vector<Piece *> m_Pieces;
  std::pair<double, double> m_UserCursorPos;
};
