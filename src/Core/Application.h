#pragma once

#include "Core/MouseEvent.h"
#include "Chess/Chess.h"


class Application
{
public:
  Application(const int width, const int height, const std::string& title);
  ~Application();
  
  void Run();

private:
  void OnUpdate();
  void OnMouseCursorEvent(MouseCursorEvent& e);
  void OnMouseButtonEvent(MouseButtonEvent& e);
  void ShutDown();

private:
  Window* m_Window = nullptr;
  Chess* m_Chess;
  bool m_Running;
};
