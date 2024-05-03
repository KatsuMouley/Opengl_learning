#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

// Window default size
const unsigned int SCR_WIDTH = 1000;
const unsigned int SCR_HEIGHT = 500;

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    //We are telling GLFW what version of Opengl We are using, in this case we're using Opengl 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    //In this following line, we're telling GLFW that we are using the CORE profile, which inplies that we only have the modern functions
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // In here, we're creating a Window Object with width and height, and a name
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Metal Lab Engine", NULL, NULL);
    //check if the window failed to create
    if(window == NULL){
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    //make the window the current context
    glfwMakeContextCurrent(window);
    //load glad to configure OpenGL
    gladLoadGL();
    //specify the Opengl in the viewport
    glViewport(0, 0, 1000, 500);
    //background color
    glClearColor(.14f, .29f, .16f, 1.0f);
    // Clean the back buffer and assign the new color to it
    glClear(GL_COLOR_BUFFER_BIT);
    //Swap the buffers(back with front)
    glfwSwapBuffers(window);
    //Main while loop
    while (!glfwWindowShouldClose(window)){
        //take care of all glfw events(Closing, resizing the window and etc)
        glfwPollEvents();
    }
    
    //the name of the following functions describes everything
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
