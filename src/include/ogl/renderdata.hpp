#pragma once

#include <vector>

#include <glm/glm.hpp>

struct Vertex
{
    glm::vec3 position;
    glm::vec2 uv;
};

struct Mesh
{
    std::vector<Vertex> vertices;
};