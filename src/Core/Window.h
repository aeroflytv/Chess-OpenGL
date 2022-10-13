#include <string>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include "Core/MouseEvent.h"

struct WindowData
{
  const int Width;
  const int Height;
  const std::string Title;

  std::function<void(MouseCursorEvent &)> MouseCursorEventCallbackFn = nullptr;
  std::function<void(MouseButtonEvent &)> MouseButtonEventCallbackFn = nullptr;
};

class Window
{
public:
  Window(WindowData windowData);

  void Run();
  void Close();

  inline void SetOnUpdateFn(std::function<void()> fn) { m_OnUpdateFn = fn; };
  inline void SetWindowRunning(bool shouldClose) { m_Running = shouldClose; };
  inline void SetMouseCursorEventCallback(std::function<void(MouseCursorEvent &)> e) { m_WindowData.MouseCursorEventCallbackFn = e; };
  inline void SetMouseButtonEventCallback(std::function<void(MouseButtonEvent &)> e) { m_WindowData.MouseButtonEventCallbackFn = e; };

  inline WindowData GetWindowData() { return m_WindowData; };

private:
  GLFWwindow *m_Window;
  WindowData m_WindowData;
  bool m_Running = true;
  std::function<void()> m_OnUpdateFn = nullptr;
};
