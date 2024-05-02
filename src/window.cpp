#include <window/window.hpp>
#include <tool/logger.hpp>
#include <ogl/renderer.hpp>
#include <model/model.hpp>

Window::Window()
{}

Window::~Window()
{}

bool Window::init(unsigned int width, unsigned int height, std::string title)
{
  if (!glfwInit())
  {
    Logger::log(1, "%s: glfwInit() error\n", __FUNCTION__);
    return false;
  }

  /* set a "hint" for the NEXT window created*/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  if (!m_window)
  {
    Logger::log(1, "%s: Could not create window\n", __FUNCTION__);
    glfwTerminate();
    return false;
  }

  Logger::log(1, "%s: Window successfully initialized\n", __FUNCTION__);

  glfwMakeContextCurrent(m_window);

  m_renderer = std::make_unique<Renderer>(m_window);
  if(!m_renderer->init(width, height))
  {
    glfwTerminate();
    Logger::log(1, "%s error: Could not initialize OpenGL\n", __FUNCTION__);
    return false;
  }

  /* save the pointer to the instance as user pointer. m_window is a mandatory parameter in every glfwWindow functions */
  glfwSetWindowUserPointer(m_window, m_renderer.get());

  glfwSetWindowSizeCallback(m_window, [](GLFWwindow *win, int width, int height) {
    auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
    renderer->set_size(width, height);
  });

  glfwSetKeyCallback(m_window, [](GLFWwindow* win, int key, int scancode, int action, int mods) {
    auto renderer = static_cast<Renderer*>(glfwGetWindowUserPointer(win));
    renderer->handle_key_events(key, scancode, action, mods);
  });

  m_model = std::make_unique<Model>();
  m_model->init();

  Logger::log(1, "%s: mockup model data loaded\n", __FUNCTION__);

  Logger::log(1, "%s: Window with OpenGL 4.6 successfully initialized\n", __FUNCTION__);

  return true;
}

void Window::main_loop()
{
  /*
    Before going into the loop, we will activate the wait for the vertical sync with a call to the GLFW 
    function, glfwSwapInterval(). Without waiting for it, the window might flicker, or tearing 
    might occur, as the update and buffer switch will be done as fast as possible
  */
  glfwSwapInterval(1); /* Force VSYNC */

  /* upload data */
  m_renderer->upload_data(m_model->get_vertex_data());

  while (!glfwWindowShouldClose(m_window))
  {

    m_renderer->draw();

    glfwSwapBuffers(m_window);
    /* poll events in a loop */
    glfwPollEvents();

  }
}

void Window::clean_up()
{

  m_renderer->clean_up();

  Logger::log(1, "%s: Terminating Window\n", __FUNCTION__);
  glfwDestroyWindow(m_window);
  glfwTerminate();
}