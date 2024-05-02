#include <ogl/renderer.hpp>
#include <tool/logger.hpp>

#define SHADER_PATH "/home/nbaskey/Desktop/nirmal/projects/ogl-engine/shader/"
#define TEXTURE_PATH "/home/nbaskey/Desktop/nirmal/projects/ogl-engine/texture/"

Renderer::Renderer(){}
Renderer::~Renderer(){}

bool Renderer::init(unsigned int width, unsigned int height)
{
  /* initalize GLAD */
  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
  {
    Logger::log(1, "%s error: failed to initialize GLAD\n", __FUNCTION__);
    return false;
  }

  if (!GLAD_GL_VERSION_4_6)
  {
    Logger::log(1, "%s error: failed to get at least OpenGL 4.6\n", __FUNCTION__);
    return false;
  }

  GLint majorVersion, minorVersion;
  glGetIntegerv(GL_MAJOR_VERSION, &majorVersion);
  glGetIntegerv(GL_MINOR_VERSION, &minorVersion);

  Logger::log(1, "%s: OpenGL %d.%d initializeed\n", __FUNCTION__, majorVersion, minorVersion);

  if (!m_frame_buffer.init(width, height))
  {
    Logger::log(1, "%s error: could not init Framebuffer\n", __FUNCTION__);
    return false;
  }

  Logger::log(1, "%s: framebuffer succesfully initialized\n", __FUNCTION__);

  if (!m_texture.load_texture(TEXTURE_PATH "crate.png"))
  {
    Logger::log(1, "%s: texture loading failed\n", __FUNCTION__);
    return false;
  }

  Logger::log(1, "%s: texture successfully loaded\n", __FUNCTION__);

  m_vertex_buffer.init();
  Logger::log(1, "%s: vertex buffer successfully created\n", __FUNCTION__);

  if (!m_shader.load_shaders(SHADER_PATH "basic.vert", SHADER_PATH "basic.frag"))
  {
    Logger::log(1, "%s: shader loading failed\n", __FUNCTION__);
    return false;
  }

  Logger::log(1, "%s: shaders succesfully loaded\n", __FUNCTION__);

  return true;
}

void Renderer::set_size(unsigned int width, unsigned int height)
{
  
  /* handle minimize */
  if (width == 0 || height == 0)
  {
    return;
  }

  m_frame_buffer.resize(width, height);
  glViewport(0, 0, width, height);

  Logger::log(1, "%s: resized window to %dx%d\n", __FUNCTION__, width, height);
}

void Renderer::upload_data(Mesh vertexData)
{
  m_triangle_count = vertexData.vertices.size() / 3;
  m_vertex_buffer.upload_data(vertexData);
}

void Renderer::draw()
{
  /* draw to framebuffer */
  m_frame_buffer.bind();

  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClearDepth(1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glEnable(GL_CULL_FACE);
  glEnable(GL_DEPTH_TEST);

  m_shader.use();
  m_texture.bind();
  m_vertex_buffer.bind();

  m_vertex_buffer.draw(GL_TRIANGLES, 0, m_triangle_count * 3);
  m_vertex_buffer.unbind();
  m_texture.unbind();

  m_frame_buffer.unbind();

  /* blit color buffer to screen */
  m_frame_buffer.draw_to_screen();
}

void Renderer::clean_up()
{
  m_shader.clean_up();
  m_texture.clean_up();
  m_vertex_buffer.clean_up();
  m_frame_buffer.clean_up();
}