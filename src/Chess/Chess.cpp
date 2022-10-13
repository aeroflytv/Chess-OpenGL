#include "Chess.h"
#include "Debug/Debug.h"

#include <GLFW/glfw3.h>

// TODO!
// 1. Implement piece possible moves.

Chess::Chess(int width, int height)
    : m_Board(new Board(width, height)), m_WindowData({width, height})
{
}

void Chess::Init()
{
  m_Board->Init();

#define INSTANTIATE_WHITE_PIECE(y) m_Pieces.push_back(new Piece(y, PieceColor::White))
#define INSTANTIATE_BLACK_PIECE(y) m_Pieces.push_back(new Piece(y, PieceColor::Black))

  INSTANTIATE_WHITE_PIECE(PieceType::Pawn1);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn2);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn3);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn4);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn5);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn6);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn7);
  INSTANTIATE_WHITE_PIECE(PieceType::Pawn8);
  INSTANTIATE_WHITE_PIECE(PieceType::Rook1);
  INSTANTIATE_WHITE_PIECE(PieceType::Rook2);
  INSTANTIATE_WHITE_PIECE(PieceType::Knight1);
  INSTANTIATE_WHITE_PIECE(PieceType::Knight2);
  INSTANTIATE_WHITE_PIECE(PieceType::Bishop1);
  INSTANTIATE_WHITE_PIECE(PieceType::Bishop2);
  INSTANTIATE_WHITE_PIECE(PieceType::Queen);
  INSTANTIATE_WHITE_PIECE(PieceType::King);

  INSTANTIATE_BLACK_PIECE(PieceType::Pawn1);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn2);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn3);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn4);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn5);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn6);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn7);
  INSTANTIATE_BLACK_PIECE(PieceType::Pawn8);
  INSTANTIATE_BLACK_PIECE(PieceType::Rook1);
  INSTANTIATE_BLACK_PIECE(PieceType::Rook2);
  INSTANTIATE_BLACK_PIECE(PieceType::Knight1);
  INSTANTIATE_BLACK_PIECE(PieceType::Knight2);
  INSTANTIATE_BLACK_PIECE(PieceType::Bishop1);
  INSTANTIATE_BLACK_PIECE(PieceType::Bishop2);
  INSTANTIATE_BLACK_PIECE(PieceType::Queen);
  INSTANTIATE_BLACK_PIECE(PieceType::King);

  const auto &pieces = m_Pieces;
  for (const auto &piece : pieces)
  {
    m_Board->PlaceChessPiece(*piece);
    CalculatePossibleMoves(*piece);
  }

  const auto &tiles = m_Board->GetTiles();
  for (const auto &tile : tiles)
  {
    if (!tile.Piece)
      m_Board->PushEmptyTile(tile);
  }
}

void Chess::CalculatePossibleMoves(Piece &piece)
{
  PieceCategory category = piece.GetCategory();
  switch (category)
  {
  case PieceCategory::Pawn:
    if (piece.GetColor() == PieceColor::White)
    {
      if (piece.GetPosition().Row == 2)
      {
        piece.PushPossibleMoves({piece.GetPosition().Row + 1, piece.GetPosition().Col});
        piece.PushPossibleMoves({piece.GetPosition().Row + 2, piece.GetPosition().Col});
      }
      else
      {
        piece.PushPossibleMoves({piece.GetPosition().Row + 1, piece.GetPosition().Col});
      }
    }
    else if (piece.GetColor() == PieceColor::Black)
    {
      if (piece.GetPosition().Row == 7)
      {
        piece.PushPossibleMoves({piece.GetPosition().Row - 1, piece.GetPosition().Col});
        piece.PushPossibleMoves({piece.GetPosition().Row - 2, piece.GetPosition().Col});
      }
      else
      {
        piece.PushPossibleMoves({piece.GetPosition().Row - 1, piece.GetPosition().Col});
      }
    }
    break;
  case PieceCategory::Rook:
    break;
  case PieceCategory::Knight:
    break;
  case PieceCategory::Bishop:
    break;
  case PieceCategory::Queen:
    break;
  case PieceCategory::King:
    break;
  }
}

void Chess::UpdateBoard()
{
  m_Board->Draw();
}

void Chess::DispatchPlayerMoves(MouseButtonEvent &buttonEvent)
{
  if (buttonEvent.GetButton() == GLFW_MOUSE_BUTTON_1 && buttonEvent.GetAction() == GLFW_PRESS)
  {
    if (!m_CurrentFocusedPiece)
      return;
    if (!m_CurrentHoveredTile)
      return;
    if (m_CurrentFocusedPiece->GetPosition().Row == m_CurrentHoveredTile->Row && m_CurrentFocusedPiece->GetPosition().Col == m_CurrentHoveredTile->Col)
      return;
    MovePiece(*m_CurrentFocusedPiece, {m_CurrentHoveredTile->Row, m_CurrentHoveredTile->Col});
  }
}

void Chess::HandlePlayerFocusPiece(MouseButtonEvent &buttonEvent)
{
  if (!m_CurrentHoveredTile)
    return;
  if (m_CurrentHoveredTile->Piece)
  {
    if (m_WhosTurn == PieceColor::White)
    {
      if (m_CurrentHoveredTile->Piece->GetColor() != PieceColor::White)
        return;
      if (buttonEvent.GetButton() == GLFW_MOUSE_BUTTON_1 && buttonEvent.GetAction() == GLFW_PRESS)
      {
        m_CurrentFocusedPiece = m_CurrentHoveredTile->Piece;
        m_Board->DrawPiecePossibleMoves(*m_CurrentFocusedPiece);
      }
    }
    else if (m_WhosTurn == PieceColor::Black)
    {
      if (m_CurrentHoveredTile->Piece->GetColor() != PieceColor::Black)
        return;
      if (buttonEvent.GetButton() == GLFW_MOUSE_BUTTON_1 && buttonEvent.GetAction() == GLFW_PRESS)
      {
        m_CurrentFocusedPiece = m_CurrentHoveredTile->Piece;
        m_Board->DrawPiecePossibleMoves(*m_CurrentFocusedPiece);
      }
    }
  }
}

void Chess::HandleCursorEvent(MouseCursorEvent &cursorEvent)
{
  // should change to local variable
  m_UserCursorPos = {cursorEvent.GetPosition().XPos, fabs(cursorEvent.GetPosition().YPos - (double)m_WindowData.Height)};

  for (auto &tile : m_Board->GetTiles())
  {
    if (tile.XPos.first <= m_UserCursorPos.first && tile.XPos.second >= m_UserCursorPos.first)
    {
      if (tile.YPos.first <= m_UserCursorPos.second && tile.YPos.second >= m_UserCursorPos.second)
      {
        m_CurrentHoveredTile = &tile;
      }
    }
  }
}

void Chess::MovePiece(Piece &piece, PiecePosition newPos)
{

  const auto &ps = m_Pieces;
  for (const auto &p : ps)
  {
    if (p->GetColor() == piece.GetColor())
    {
      if (p->GetPosition().Row == piece.GetPosition().Row && p->GetPosition().Col == piece.GetPosition().Col)
      {
        m_Board->RemoveChessPiece(*p);
        piece.SetPosition(newPos);
        m_Board->PlaceChessPiece(piece);

        CalculatePossibleMoves(piece);
      }
    }
  }
  if (m_WhosTurn == PieceColor::White)
    m_WhosTurn = PieceColor::Black;
  else if (m_WhosTurn == PieceColor::Black)
    m_WhosTurn = PieceColor::White;
  m_CurrentFocusedPiece = nullptr;
}

Chess::~Chess()
{
  const auto &pieces = m_Pieces;
  for (const auto &piece : pieces)
  {
    delete piece;
  }
  m_Board->Close();
  delete m_Board;
}