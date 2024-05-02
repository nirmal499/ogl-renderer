#pragma once

#include <vector>
#include <glm/glm.hpp>

#include <ogl/renderdata.hpp>

class Model
{
    public:
        void init();

        Mesh get_vertex_data();

        Model();
        ~Model();

    private:
        Mesh m_vertex_data;
};