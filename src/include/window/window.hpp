#pragma once

#include <string>
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Renderer;
class Model;

class Window
{
    public:
        bool init(unsigned int width, unsigned int height, std::string title);
        void main_loop();
        void clean_up();

        Window();
        ~Window();
    
    private:
        GLFWwindow* m_window = nullptr;

        std::unique_ptr<Renderer> m_renderer;
        std::unique_ptr<Model> m_model;

        unsigned int m_width = 640;
        unsigned int m_height = 480;
};