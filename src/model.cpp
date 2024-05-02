#include <model/model.hpp>
#include <tool/logger.hpp>

Model::Model(){}
Model::~Model(){}

void Model::init()
{
  m_vertex_data.vertices.resize(6);

  m_vertex_data.vertices[0].position = glm::vec3(-0.5f, -0.5f,  0.5f);
  m_vertex_data.vertices[1].position = glm::vec3( 0.5f,  0.5f,  0.5f);
  m_vertex_data.vertices[2].position = glm::vec3(-0.5f,  0.5f,  0.5f);
  m_vertex_data.vertices[3].position = glm::vec3(-0.5f, -0.5f,  0.5f);
  m_vertex_data.vertices[4].position = glm::vec3( 0.5f, -0.5f,  0.5f);
  m_vertex_data.vertices[5].position = glm::vec3( 0.5f,  0.5f,  0.5f);

  m_vertex_data.vertices[0].uv = glm::vec2(0.0, 0.0);
  m_vertex_data.vertices[1].uv = glm::vec2(1.0, 1.0);
  m_vertex_data.vertices[2].uv = glm::vec2(0.0, 1.0);
  m_vertex_data.vertices[3].uv = glm::vec2(0.0, 0.0);
  m_vertex_data.vertices[4].uv = glm::vec2(1.0, 0.0);
  m_vertex_data.vertices[5].uv = glm::vec2(1.0, 1.0);

  Logger::log(1, "%s: loaded %d vertices\n", __FUNCTION__, m_vertex_data.vertices.size());
}

Mesh Model::get_vertex_data()
{
  return m_vertex_data;
}