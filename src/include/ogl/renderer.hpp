#pragma once

#include <vector>
#include <string>

#include <glm/glm.hpp>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <ogl/framebuffer.hpp>
#include <ogl/vertexbuffer.hpp>
#include <ogl/texture.hpp>
#include <ogl/shader.hpp>
#include <ogl/renderdata.hpp>

class Renderer
{
    public:
        bool init(unsigned int width, unsigned int height);
        void set_size(unsigned int width, unsigned int height);
        void upload_data(Mesh vertexData);
        void draw();
        void clean_up();

        Renderer();
        ~Renderer();

    private:
        Shader m_shader{};
        Framebuffer m_frame_buffer{};
        Texture m_texture{};
        VertexBuffer m_vertex_buffer{};

        int m_triangle_count = 0;
};