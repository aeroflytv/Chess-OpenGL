#include "Window.h"
#include "GLFW/glfw3.h"
#include <iostream>
#include "MouseEvent.h"

Window::Window(WindowData windowProps)
    : m_WindowData(windowProps)
{
  while (true)
  {
#define WINDOW_ERROR(x)                                             \
  std::cout << "[WINDOW]: " << x << " at" << __LINE__ << std::endl; \
  break
#define WINDOW_SUCCESS(x)                   \
  std::cout << "[WINDOW]: " x << std::endl; \
  break
    if (!glfwInit())
    {
      WINDOW_ERROR("Glfw library initialization failed!");
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
    m_Window = glfwCreateWindow(m_WindowData.Width, m_WindowData.Height, m_WindowData.Title.c_str(), nullptr, nullptr);
    if (!m_Window)
    {
      WINDOW_ERROR("Window is null!");
      glfwTerminate();
    }
    glfwMakeContextCurrent(m_Window);
    glfwSetWindowUserPointer(m_Window, &m_WindowData);
    glfwSetCursorPosCallback(m_Window, [](GLFWwindow *window, double xpos, double ypos)
                             { 
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseCursorEvent event(xpos, ypos);
        if(event.GetPosition().XPos <= data.Width && event.GetPosition().XPos >= 0 && event.GetPosition().YPos <= data.Height && event.GetPosition().YPos >= 0)
          data.MouseCursorEventCallbackFn(event); });
    glfwSetMouseButtonCallback(m_Window, [](GLFWwindow *window, int button, int action, int mods)
                               {
        WindowData& data = *(WindowData*)glfwGetWindowUserPointer(window);
        MouseButtonEvent event(button, action);
        data.MouseButtonEventCallbackFn(event); });
    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    WINDOW_SUCCESS("Glfw Window Successfully initialized!");
  }
}

void Window::Run()
{
  while (!glfwWindowShouldClose(m_Window))
  {
    if (!m_Running)
      glfwSetWindowShouldClose(m_Window, true);

    glClear(GL_COLOR_BUFFER_BIT);
    glfwPollEvents();

    if (m_OnUpdateFn)
      m_OnUpdateFn();

    glfwSwapBuffers(m_Window);
  }
}

void Window::Close()
{
  glfwTerminate();
}
