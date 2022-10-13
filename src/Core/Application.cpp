#include "Application.h"
#include "Debug/Debug.h"
#include <iostream>
#include <utility>

void Application::OnUpdate()
{
  m_Chess->UpdateBoard();
}
void Application::OnMouseCursorEvent(MouseCursorEvent &cursorEvent)
{
  m_Chess->HandleCursorEvent(cursorEvent);
}

void Application::OnMouseButtonEvent(MouseButtonEvent &buttonEvent)
{
  m_Chess->HandlePlayerFocusPiece(buttonEvent);
  m_Chess->DispatchPlayerMoves(buttonEvent);
}

Application::Application(const int width, const int height, const std::string &title)
    : m_Chess(new Chess(width, height))
{
  m_Window = new Window({width, height, title});
}
Application::~Application()
{
  delete m_Window;
  delete m_Chess;
}
void Application::Run()
{
  m_Running = true;
  m_Window->SetWindowRunning(true);
  m_Window->SetOnUpdateFn([this]()
                          { OnUpdate(); });
  m_Window->SetMouseCursorEventCallback([this](MouseCursorEvent &e)
                                        { OnMouseCursorEvent(e); });
  m_Window->SetMouseButtonEventCallback([this](MouseButtonEvent &e)
                                        { OnMouseButtonEvent(e); });

  m_Chess->Init();
  m_Window->Run();

  m_Window->Close();
}
void Application::ShutDown()
{
  m_Running = false;
  m_Window->SetWindowRunning(false);
}
