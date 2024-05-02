#include <ogl/vertexbuffer.hpp>
#include <tool/logger.hpp>

void VertexBuffer::init()
{
  glGenVertexArrays(1, &m_vao);
  glGenBuffers(1, &m_vertex_vbo);

  glBindVertexArray(m_vao);

  glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, position));
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, color));
  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), (void*) offsetof(Vertex, uv));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  Logger::log(1, "%s: VAO and VBO initialized\n", __FUNCTION__);
}

void VertexBuffer::clean_up()
{
  glDeleteBuffers(1, &m_vertex_vbo);
  glDeleteVertexArrays(1, &m_vao);
}

void VertexBuffer::upload_data(Mesh vertexData)
{
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertex_vbo);

  glBufferData(GL_ARRAY_BUFFER, vertexData.vertices.size() * sizeof(Vertex), &vertexData.vertices.at(0), GL_DYNAMIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void VertexBuffer::bind()
{
  glBindVertexArray(m_vao);
}

void VertexBuffer::unbind()
{
  glBindVertexArray(0);
}

void VertexBuffer::draw(GLuint mode, unsigned int start, unsigned int num)
{
  glDrawArrays(mode, start, num);
}

