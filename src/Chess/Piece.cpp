#include "Piece.h"

#include <glad/glad.h>
#include <stb_image/stb_image.h>
#include <sys/_types/_u_char.h>

#include "Debug/Debug.h"

Piece::Piece(PieceType type, PieceColor color)
    : m_Type(type), m_Color(color), m_Texture(0)
{
  std::string filePath;
  if (m_Color == PieceColor::White)
  {
    switch (m_Type)
    {
    case PieceType::Pawn1:
      m_Pos = PiecePosition({2, 1});
      m_PossibleMoves.push_back({2 + 1, 1});
      m_PossibleMoves.push_back({2 + 2, 1});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn2:
      m_Pos = PiecePosition({2, 2});
      m_PossibleMoves.push_back({2 + 1, 2});
      m_PossibleMoves.push_back({2 + 2, 2});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn3:
      m_Pos = PiecePosition({2, 3});
      m_PossibleMoves.push_back({2 + 1, 3});
      m_PossibleMoves.push_back({2 + 2, 3});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn4:
      m_Pos = PiecePosition({2, 4});
      m_PossibleMoves.push_back({2 + 1, 4});
      m_PossibleMoves.push_back({2 + 2, 4});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn5:
      m_Pos = PiecePosition({2, 5});
      m_PossibleMoves.push_back({2 + 1, 5});
      m_PossibleMoves.push_back({2 + 2, 5});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn6:
      m_Pos = PiecePosition({2, 6});
      m_PossibleMoves.push_back({2 + 1, 6});
      m_PossibleMoves.push_back({2 + 2, 6});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn7:
      m_Pos = PiecePosition({2, 7});
      m_PossibleMoves.push_back({2 + 1, 7});
      m_PossibleMoves.push_back({2 + 2, 7});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Pawn8:
      m_Pos = PiecePosition({2, 8});
      m_PossibleMoves.push_back({2 + 1, 8});
      m_PossibleMoves.push_back({2 + 2, 8});
      filePath = "../res/textures/Chess_plt60.png";
      break;
    case PieceType::Rook1:
      m_Pos = PiecePosition({1, 1});
      filePath = "../res/textures/Chess_rlt60.png";
      break;
    case PieceType::Rook2:
      m_Pos = PiecePosition({1, 8});
      filePath = "../res/textures/Chess_rlt60.png";
      break;
    case PieceType::Knight1:
      m_Pos = PiecePosition({1, 2});
      m_PossibleMoves.push_back({2 + 2, 2 - 1});
      m_PossibleMoves.push_back({2 + 2, 2 + 1});
      filePath = "../res/textures/Chess_nlt60.png";
      break;
    case PieceType::Knight2:
      m_Pos = PiecePosition({1, 7});
      m_PossibleMoves.push_back({2 + 2, 7 - 1});
      m_PossibleMoves.push_back({2 + 2, 7 + 1});
      filePath = "../res/textures/Chess_nlt60.png";
      break;
    case PieceType::Bishop1:
      m_Pos = PiecePosition({1, 3});
      filePath = "../res/textures/Chess_blt60.png";
      break;
    case PieceType::Bishop2:
      m_Pos = PiecePosition({1, 6});
      filePath = "../res/textures/Chess_blt60.png";
      break;
    case PieceType::Queen:
      m_Pos = PiecePosition({1, 4});
      filePath = "../res/textures/Chess_qlt60.png";
      break;
    case PieceType::King:
      m_Pos = PiecePosition({1, 5});
      filePath = "../res/textures/Chess_klt60.png";
      break;
    }
  }
  else if (m_Color == PieceColor::Black)
  {
    switch (m_Type)
    {
    case PieceType::Pawn1:
      m_Pos = PiecePosition({7, 1});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 1});
      m_PossibleMoves.push_back({7 + 2, 1});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn2:
      m_Pos = PiecePosition({7, 2});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 2});
      m_PossibleMoves.push_back({7 + 2, 2});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn3:
      m_Pos = PiecePosition({7, 3});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 3});
      m_PossibleMoves.push_back({7 + 2, 3});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn4:
      m_Pos = PiecePosition({7, 4});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 4});
      m_PossibleMoves.push_back({7 + 2, 4});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn5:
      m_Pos = PiecePosition({7, 5});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 5});
      m_PossibleMoves.push_back({7 + 2, 5});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn6:
      m_Pos = PiecePosition({7, 6});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 6});
      m_PossibleMoves.push_back({7 + 2, 6});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn7:
      m_Pos = PiecePosition({7, 7});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 7});
      m_PossibleMoves.push_back({7 + 2, 7});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Pawn8:
      m_Pos = PiecePosition({7, 8});
      m_Category = PieceCategory::Pawn;
      m_PossibleMoves.push_back({7 + 1, 8});
      m_PossibleMoves.push_back({7 + 2, 8});
      filePath = "../res/textures/Chess_pdt60.png";
      break;
    case PieceType::Rook1:
      m_Pos = PiecePosition({8, 1});
      m_Category = PieceCategory::Rook;
      filePath = "../res/textures/Chess_rdt60.png";
      break;
    case PieceType::Rook2:
      m_Pos = PiecePosition({8, 8});
      m_Category = PieceCategory::Rook;
      filePath = "../res/textures/Chess_rdt60.png";
      break;
    case PieceType::Knight1:
      m_Pos = PiecePosition({8, 2});
      m_Category = PieceCategory::Knight;
      m_PossibleMoves.push_back({8 - 2, 2 + 1});
      m_PossibleMoves.push_back({8 - 2, 2 - 1});
      filePath = "../res/textures/Chess_ndt60.png";
      break;
    case PieceType::Knight2:
      m_Pos = PiecePosition({8, 7});
      m_Category = PieceCategory::Knight;
      m_PossibleMoves.push_back({8 - 2, 7 + 1});
      m_PossibleMoves.push_back({8 - 2, 7 - 1});
      filePath = "../res/textures/Chess_ndt60.png";
      break;
    case PieceType::Bishop1:
      m_Pos = PiecePosition({8, 3});
      m_Category = PieceCategory::Bishop;
      filePath = "../res/textures/Chess_bdt60.png";
      break;
    case PieceType::Bishop2:
      m_Pos = PiecePosition({8, 6});
      m_Category = PieceCategory::Bishop;
      filePath = "../res/textures/Chess_bdt60.png";
      break;
    case PieceType::Queen:
      m_Pos = PiecePosition({8, 4});
      m_Category = PieceCategory::Queen;
      filePath = "../res/textures/Chess_qdt60.png";
      break;
    case PieceType::King:
      m_Pos = PiecePosition({8, 5});
      m_Category = PieceCategory::King;
      filePath = "../res/textures/Chess_kdt60.png";
      break;
    }
  }

  stbi_set_flip_vertically_on_load(true);

  int width = 0, height = 0, bpp = 0;

  unsigned char *localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

  GLCall(glGenTextures(1, &m_Texture));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_Texture));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  if (localBuffer)
    stbi_image_free(localBuffer);
}
