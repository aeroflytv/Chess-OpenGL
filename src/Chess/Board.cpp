#include "Board.h"
#include "Debug/Debug.h"

#include <glad/glad.h>

#include <iostream>
#include <fstream>
#include <sstream>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <stb_image/stb_image.h>

struct ShaderProgramSource
{
  std::string VertexSource;
  std::string FragmentSource;
};

static ShaderProgramSource ParseShader(const std::string &path)
{
  std::ifstream stream(path);
  std::stringstream ss[2];
  std::string line;

  enum class ShaderType
  {
    NONE = -1,
    VERTEX = 0,
    FRAGMENT = 1
  };
  ShaderType type = ShaderType::NONE;

  while (getline(stream, line))
  {
    if (line.find("#shader") != std::string::npos)
    {
      if (line.find("vertex") != std::string::npos)
      {
        type = ShaderType::VERTEX;
      }
      else if (line.find("fragment") != std::string::npos)
      {
        type = ShaderType::FRAGMENT;
      }
    }
    else
    {
      ss[(int)type] << line << '\n';
    }
  }

  return {ss[0].str(), ss[1].str()};
}

Board::Board(int screenWidth, int screenHeight)
    : m_WindowSize(screenWidth, screenHeight)
{
}
void Board::Init()
{
  float width = (float)m_WindowSize.first;
  float height = (float)m_WindowSize.second;

  float vertices[] = {
      0.0f,
      0.0f,
      0.0f,
      0.0f,
      width / 8.0f,
      0.0f,
      1.0f,
      0.0f,
      width / 8.0f,
      height / 8.0f,
      1.0f,
      1.0f,
      0.0f,
      height / 8.0f,
      0.0f,
      1.0f,
  };

  u_int32_t indices[] = {
      0, 1, 2,
      0, 3, 2};

  int idx = 0;
  for (int row = 0; row < 8; row++)
  {
    for (int col = 0; col < 8; col++)
    {
      if (row % 2 == 0)
      {
        if (col % 2 == 0)
        {
          CreateTile(TileType::Black, idx, width / 8.0f * (float)col, height / 8.0f * (float)row, vertices, indices, row + 1, col + 1);
        }
        else
        {
          CreateTile(TileType::White, idx, width / 8.0f * (float)col, height / 8.0f * (float)row, vertices, indices, row + 1, col + 1);
        }
      }
      else
      {
        if (col % 2 == 0)
        {
          CreateTile(TileType::White, idx, width / 8.0f * (float)col, height / 8.0f * (float)row, vertices, indices, row + 1, col + 1);
        }
        else
        {
          CreateTile(TileType::Black, idx, width / 8.0f * (float)col, height / 8.0f * (float)row, vertices, indices, row + 1, col + 1);
        }
      }
      idx++;
    }
  }
}

void Board::PlaceChessPiece(Piece &piece)
{
  PieceType type = piece.GetType();
  auto &tiles = m_Tiles;
  for (int i = 0; i < tiles.size(); i++)
  {
    auto &tile = tiles[i];
    if (tile.Row == piece.GetPosition().Row)
    {
      if (tile.Col == piece.GetPosition().Col)
      {
        tile.Piece = &piece;
      }
    }
  }
  InitPossibleMoveTex();
}

void Board::DrawPiecePossibleMoves(Piece &piece)
{
  const auto &moves = piece.GetPossibleMoves();
  auto &tiles = m_Tiles;
  for (auto &tile : tiles)
  {
    for (const auto &move : moves)
    {
      std::cout << "ROW: " << move.Row << std::endl;
      std::cout << "COL: " << move.Col << std::endl;
      if (tile.Row != move.Row)
        return;
      if (tile.Col != move.Col)
        return;
      tile.IsPossibleMoveTexEnabled = true;
    }
  }
}

void Board::RemoveChessPiece(Piece &piece)
{
  PieceType type = piece.GetType();
  auto &tiles = m_Tiles;

  for (int i = 0; i < tiles.size(); i++)
  {
    auto &tile = tiles[i];
    if (tile.Row == piece.GetPosition().Row)
    {
      if (tile.Col == piece.GetPosition().Col)
      {
        tile.Piece = nullptr;
      }
    }
  }
}

void Board::Draw()
{
  const auto &tiles = m_Tiles;
  for (int i = 0; i < tiles.size(); i++)
  {
    const auto &tile = tiles[i];
    GLCall(glUseProgram(tile.RenderIds.program));
    GLCall(glUniformMatrix4fv(glGetUniformLocation(tile.RenderIds.program, "u_MVP"), 1, GL_FALSE, glm::value_ptr(tile.MVP)));
    GLCall(glUniform1i(glGetUniformLocation(tile.RenderIds.program, "u_Texture"), 0));
    if (tile.Piece || tile.IsPossibleMoveTexEnabled)
    {
      GLCall(glUniform1i(glGetUniformLocation(tile.RenderIds.program, "u_WithTex"), true));
    }
    else
    {
      GLCall(glUniform1i(glGetUniformLocation(tile.RenderIds.program, "u_WithTex"), false));
    }

    GLCall(glBindVertexArray(tile.RenderIds.va));

    if (tile.Piece)
    {
      GLCall(glActiveTexture(GL_TEXTURE0));
      GLCall(glBindTexture(GL_TEXTURE_2D, tile.Piece->GetTexture()));
    }
    else if (tile.IsPossibleMoveTexEnabled)
    {
      GLCall(glActiveTexture(GL_TEXTURE0));
      GLCall(glBindTexture(GL_TEXTURE_2D, m_PossibleMoveTex));
    }

    GLCall(glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr));

    if (tile.Piece || tile.IsPossibleMoveTexEnabled)
    {
      GLCall(glBindTexture(GL_TEXTURE_2D, 0));
    }

    GLCall(glUseProgram(0));
    GLCall(glBindVertexArray(0));
  }
}

void Board::CreateTile(TileType type, int idx, float x, float y, float *vertices, u_int32_t *indices, int row, int col)
{
  u_int32_t va, vb, ib, program;

  glm::mat4 projection = glm::mat4(1.0f);
  glm::mat4 view = glm::mat4(1.0f);
  glm::mat4 model = glm::mat4(1.0f);

  projection = glm::ortho(0.0f, (float)m_WindowSize.first, 0.0f, (float)m_WindowSize.second);
  model = glm::translate(model, glm::vec3(x, y, 0.0f));

  glm::mat4 mvp = projection * view * model;

  m_Tiles.push_back({row, col, {x, x + (float)m_WindowSize.first / 8.0f}, {y, y + (float)m_WindowSize.second / 8.0f}, mvp, {va, vb, ib, program}});

#define TILE_ID_VA m_Tiles[idx].RenderIds.va
#define TILE_ID_VB m_Tiles[idx].RenderIds.vb
#define TILE_ID_IB m_Tiles[idx].RenderIds.ib
#define TILE_ID_PROGRAM m_Tiles[idx].RenderIds.program

  GLCall(glGenVertexArrays(1, &TILE_ID_VA));
  GLCall(glBindVertexArray(TILE_ID_VA));

  GLCall(glGenBuffers(1, &TILE_ID_VB));
  GLCall(glBindBuffer(GL_ARRAY_BUFFER, TILE_ID_VB));
  GLCall(glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 16, vertices, GL_STATIC_DRAW));

  GLCall(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, nullptr));
  GLCall(glEnableVertexAttribArray(0));

  GLCall(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 4, (const void *)8));
  GLCall(glEnableVertexAttribArray(1));

  GLCall(glGenBuffers(1, &TILE_ID_IB));
  GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, TILE_ID_IB));
  GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(u_int32_t) * 6, indices, GL_STATIC_DRAW));

  GLCall(glBindVertexArray(0));

  ShaderProgramSource source;

  switch (type)
  {
  case TileType::White:
    source = ParseShader("../res/shaders/WhiteTile.shader");
    break;
  case TileType::Black:
    source = ParseShader("../res/shaders/BlackTile.shader");
    break;
  }

  const char *vSource = source.VertexSource.c_str();
  const char *fSource = source.FragmentSource.c_str();

  GLCall(u_int32_t vs = glCreateShader(GL_VERTEX_SHADER));
  GLCall(u_int32_t fs = glCreateShader(GL_FRAGMENT_SHADER));

  GLCall(glShaderSource(vs, 1, &vSource, nullptr));
  GLCall(glShaderSource(fs, 1, &fSource, nullptr));
  GLCall(glCompileShader(vs));
  GLCall(glCompileShader(fs));

  GLCall(TILE_ID_PROGRAM = glCreateProgram());
  GLCall(glAttachShader(TILE_ID_PROGRAM, vs));
  GLCall(glAttachShader(TILE_ID_PROGRAM, fs));
  GLCall(glLinkProgram(TILE_ID_PROGRAM));
  GLCall(glValidateProgram(TILE_ID_PROGRAM));

  GLCall(glDeleteShader(vs));
  GLCall(glDeleteShader(fs));
}

void Board::Close()
{
  const auto &tiles = m_Tiles;
  for (int i = 0; i < tiles.size(); i++)
  {
    const auto &tile = tiles[i];
    glDeleteBuffers(1, &tile.RenderIds.vb);
    glDeleteBuffers(1, &tile.RenderIds.ib);
    glDeleteVertexArrays(1, &tile.RenderIds.va);
    glDeleteProgram(tile.RenderIds.program);
  }
}

void Board::InitPossibleMoveTex()
{
  const std::string filePath = "../res/textures/black-cirlce.png";
  stbi_set_flip_vertically_on_load(true);

  int width = 0, height = 0, bpp = 0;

  unsigned char *localBuffer = stbi_load(filePath.c_str(), &width, &height, &bpp, 4);

  GLCall(glGenTextures(1, &m_PossibleMoveTex));
  GLCall(glBindTexture(GL_TEXTURE_2D, m_PossibleMoveTex));

  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
  GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

  GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, localBuffer));
  GLCall(glBindTexture(GL_TEXTURE_2D, 0));

  if (localBuffer)
    stbi_image_free(localBuffer);
}
