#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>
// This is the original code
#include "shaderClass.h"
#include "VBO.h"
#include "VAO.h"
#include "EBO.h"

// Vertex Shader source code
const char *vertexShaderSource = "#version 330 core\n"
                                 "layout (location = 0) in vec3 aPos;\n"
                                 "void main()\n"
                                 "{\n"
                                 "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
                                 "}\0";
// Fragment Shader source code
const char *fragmentShaderSource = "#version 330 core\n"
                                   "out vec4 FragColor;\n"
                                   "void main()\n"
                                   "{\n"
                                   "   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
                                   "}\n\0";

int main()
{
    // Vertices coordinates
    GLfloat vertices[] =
        {
            -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,    // Lower left corner
            0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,        // Lower right corner
            0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f,    // Upper corner
            -0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f, // Inner left
            0.5f / 2, 0.5f * float(sqrt(3)) / 6, 0.0f,    // Inner right
            0.0f, -0.5f * float(sqrt(3)) / 3, 0.0f        // Inner down
        };

    GLuint indices[] =
        {
            0, 3, 5, // Lower left triangle
            3, 2, 4, // Lower right triangle
            5, 4, 1     // Upper triangle
        };

    // Initialize GLFW
    if (!glfwInit())
    {
        std::cout << "Failed to initialize GLFW!" << std::endl;
        return -1;
    }

    // Tell GLFW what version of OpenGL we are using
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create a GLFWwindow object of 800 by 800 pixels, naming it "OrganizedFiles class"
    GLFWwindow *window = glfwCreateWindow(800, 800, "OrganizedFiles class", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    // Load GLAD so it configures OpenGL
    if (!gladLoadGL())
    {
        std::cout << "Failed to initialize OpenGL context!" << std::endl;
        return -1;
    }

    // Specify the viewport of OpenGL in the Window
    glViewport(0, 0, 800, 800);

    // Load shaders
    Shader ShaderProgram("ResourceFiles/Shaders/default.vert", "ResourceFiles/Shaders/default.frag");
    if (!ShaderProgram.IsCompiled())
    {
        std::cout << "Shader compilation failed!" << std::endl;
        return -1;
    }

    VAO VAO1;
    VAO1.Bind();

    VBO VBO1(vertices, sizeof(vertices));
    EBO EBO1(indices, sizeof(indices));

    VAO1.LinkVBO(VBO1, 0);
    VAO1.Unbind();
    VBO1.Unbind();
    EBO1.Unbind();

    // Check VAO, VBO, and EBO creation
    if (!glIsBuffer(VBO1.GetID()))
    {
        std::cout << "Failed to create VBO!" << std::endl;
        return -1;
    }

    if (!glIsVertexArray(VAO1.GetID()))
    {
        std::cout << "Failed to create VAO!" << std::endl;
        return -1;
    }

    // Main while loop
    while (!glfwWindowShouldClose(window))
    {
        // Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
        // Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);

        // Tell OpenGL which Shader Program we want to use
        ShaderProgram.Activate();

        // Bind the VAO so OpenGL knows to use it
        VAO1.Bind();

        // Draw the triangle using the GL_TRIANGLES primitive
        glDrawElements(GL_TRIANGLES, 9, GL_UNSIGNED_INT, 0);

        // Swap the back buffer with the front buffer
        glfwSwapBuffers(window);

        // Take care of all GLFW events
        glfwPollEvents();
    }

    // Delete all the objects we've created
    VAO1.Delete();
    VBO1.Delete();
    EBO1.Delete();
    ShaderProgram.Delete();

    // Delete window before ending the program
    glfwDestroyWindow(window);

    // Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
