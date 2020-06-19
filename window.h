#pragma once

#include <any>
#include <functional>
#include <string>

class Window {
  unsigned int m_height;
  unsigned int m_width;
  std::any m_window;
public:
  Window(const std::string &name, unsigned int width = 800,
         unsigned int height = 600);
  ~Window();

  void loop(const std::function<void()>& fun);
};
