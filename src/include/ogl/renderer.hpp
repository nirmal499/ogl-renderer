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
        void handle_key_events(int key, int scancode, int action, int mods);

        Renderer(GLFWwindow* window);
        ~Renderer();

    private:
        Shader m_basic_shader{};
        Shader m_changed_shader{};

        bool m_use_changed_shader = false;

        Framebuffer m_frame_buffer{};
        Texture m_texture{};
        VertexBuffer m_vertex_buffer{};

        GLFWwindow* m_window = nullptr;

        int m_triangle_count = 0;

        int m_width = 0;
        int m_height = 0;
};