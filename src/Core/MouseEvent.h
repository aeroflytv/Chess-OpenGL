#pragma once

struct MousePosition
{
  double XPos;
  double YPos;
};

class MouseCursorEvent
{
public:
  MouseCursorEvent(double xPos, double yPos) : m_Pos({xPos, yPos}){};

  inline MousePosition GetPosition() const { return m_Pos; };

private:
  MousePosition m_Pos;
};

class MouseButtonEvent
{
public:
  MouseButtonEvent(int button, int action) : m_Button(button), m_Action(action){};

  inline int GetButton() const
  {
    return m_Button;
  };
  inline int GetAction() const
  {
    return m_Action;
  };

private:
  int m_Button;
  int m_Action;
};
