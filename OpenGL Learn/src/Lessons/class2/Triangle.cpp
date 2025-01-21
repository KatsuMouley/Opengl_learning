#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <math.h>

// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";

// The main purpose of the fragment shader is to calculate the final color of a pixel and this is usually the stage where all the advanced OpenGL effects occur. 
// Usually the fragment shader contains data about the 3D scene that it can use to calculate the final pixel color (like lights, shadows, color of the light and so on).


//Triangle Lesson

//Vertex Shader

//Shape Assembly
//Geometry Shader
//Tests and Blending
//Fragment Shader
//Rasterization

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
    GLFWwindow* window = glfwCreateWindow(800, 800, "Triangle :)", NULL, NULL);
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
	// In this case the viewport goes from x = 0, y = 0, to x = 800, y = 800
    glViewport(0, 0, 800, 800);


	// Create Vertex Shader Object and get its reference
    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
	// Attach Vertex Shader source to the Vertex Shader Object
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	// Compile the Vertex Shader into machine code
    glCompileShader(vertexShader);
// The first part of the pipeline is the vertex shader that takes as input a single vertex. 
// The main purpose of the vertex shader is to transform 3D coordinates into different 3D coordinates 
// (more on that later) and the vertex shader allows us to do some basic processing on the vertex attributes.



	// Create Fragment Shader Object and get its reference
    GLuint fragmentShader = glCreateShader(GL_VERTEX_SHADER);
    // A fragment in OpenGL is all the data required for OpenGL to render a single pixel.

	// Attach Fragment Shader source to the Fragment Shader Object
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	// Compile the Vertex Shader into machine code
    glCompileShader(fragmentShader);


	// Create Shader Program Object and get its reference
    GLuint shaderProgram = glCreateProgram();
	// Attach the Vertex and Fragment Shaders to the Shader Program
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
	// Wrap-up/Link all the shaders together into the Shader Program
    glLinkProgram(shaderProgram);


	// Delete the now useless Vertex and Fragment Shader objects
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


	// Vertices coordinates
    GLfloat vertices[] =
    {
        // X, Y, Z
        -0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.5f, -0.5f * float(sqrt(3)) / 3, 0.0f,
        0.0f, 0.5f * float(sqrt(3)) * 2 / 3, 0.0f
    };


	// Create reference containers for the Vartex Array Object and the Vertex Buffer Object
    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


	// Make the VAO the current Vertex Array Object by binding it
    glBindVertexArray(VAO);

    //BInding means we're making a certain object the current object
	// Bind the VBO specifying it's a GL_ARRAY_BUFFER
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    
	// Introduce the vertices into the VBO
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);


	// Configure the Vertex Attribute so that OpenGL knows how to read the VBO
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    
	// Enable the Vertex Attribute so that OpenGL knows to use it
    glEnableVertexAttribArray(0);


	// Bind both the VBO and VAO to 0 so that we don't accidentally modify the VAO and VBO we created
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);

    //Main while loop
    while (!glfwWindowShouldClose(window)){
		// Specify the color of the background
        glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
		// Clean the back buffer and assign the new color to it
        glClear(GL_COLOR_BUFFER_BIT);
		// Tell OpenGL which Shader Program we want to use
        glUseProgram(shaderProgram);
		// Bind the VAO so OpenGL knows to use it
        glBindVertexArray(VAO);
		// Draw the triangle using the GL_TRIANGLES primitive
        glDrawArrays(GL_TRIANGLES, 0, 3);
        // The output of the vertex shader stage is optionally passed to the geometry shader.
        // The geometry shader takes as input a collection of vertices that form a primitive and has the ability to generate other shapes by emitting new vertices to form new (or other) primitive(s).
        // In this example case, it generates a second triangle out of the given shape.
        
        // The primitive assembly stage takes as input all the vertices (or vertex if GL_POINTS is chosen) from the vertex (or geometry) 
        // shader that form one or more primitives and assembles all the point(s) in the primitive shape given; in this case two triangles.
        
        // In order for OpenGL to know what to make of your collection of coordinates and color values OpenGL requires you to hint what kind of render types you want to form with the data. 
        // Do we want the data rendered as a collection of points, a collection of triangles or perhaps just one long line? Those hints are called primitives and are given to OpenGL while calling any of the drawing commands. 
        // Some of these hints are GL_POINTS, GL_TRIANGLES and GL_LINE_STRIP.

		// Swap the back buffer with the front buffer
        glfwSwapBuffers(window);
        //take care of all glfw events(Closing, resizing the window and etc)
		// Take care of all GLFW events
        glfwPollEvents();
    }
    
    //the name of the following functions describes everything
	// Delete all the objects we've created
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);
    
	// Delete window before ending the program
    glfwDestroyWindow(window);
	// Terminate GLFW before ending the program
    glfwTerminate();
    return 0;
}
