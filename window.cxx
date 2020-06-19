#include "window.h"
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void processInput(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

Window::Window(const std::string &name, unsigned int width,
       unsigned int height)
    : m_width(width), m_height(height) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window =
      glfwCreateWindow(width, height, name.c_str(), nullptr, nullptr);
  if (window == nullptr) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
  m_window = std::make_any<GLFWwindow*>(window);
}

void Window::loop(const std::function<void()> &fun) {
  GLFWwindow *window = std::any_cast<GLFWwindow *>(m_window);
  while(!glfwWindowShouldClose(window)) {
    processInput(window);

    fun();

    glfwSwapBuffers(window);
    glfwPollEvents();
  }
}

Window::~Window() {
  glfwTerminate();
}
