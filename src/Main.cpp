#include <iostream>
#include "Core/Application.h"

int main()
{
  const int WIDTH = 600;
  const int HEIGHT = 600;
  const char* TITLE = "Chess";

  Application* app = new Application(WIDTH, HEIGHT, TITLE);
  app->Run();

  delete app;
  return EXIT_SUCCESS;
}
