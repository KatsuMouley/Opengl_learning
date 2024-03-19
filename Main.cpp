#include <iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>

int myFirstGlfwFunction();

int main(){

	//GLFW configurations
	//Start glfw
	glfwInit();
	//specify the glfw version
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	//An Opengl profile is a package of functions, the core, that contains all modern functions, and compatibility which contains all the modern and the old functions
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Here we're specifying the window height and width and its name, and also if its full screen and other option that's not important for now.
	GLFWwindow* window = glfwCreateWindow(800, 800, "My First Opengl Program", NULL, NULL);

	//if the window doesn't open, it will end the program
	if (window == NULL) 
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}

	//search!!!
	glfwMakeContextCurrent(window);
	
	gladLoadGL();

	glViewport(0, 0, 800, 800);
	//RED GREEN BLUE and ALPHA
	glClearColor( 0.07f, 0.12f, 0.27f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	glfwSwapBuffers(window);

	//search!!!
	while (!glfwWindowShouldClose(window)) 
	{
		//This command process the all the window poll events. I need to search and learn what's Poll events
		glfwPollEvents();
	}

	//Destroy Window
	glfwDestroyWindow(window);
	glfwTerminate();
	return 0;
}