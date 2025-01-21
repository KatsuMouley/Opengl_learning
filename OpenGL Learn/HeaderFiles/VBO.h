#ifndef VBO_CLASS_H
#define VBO_CLASS_H

#include <glad/glad.h>

class VBO
{
    public:
        GLuint ID;
        VBO(GLfloat* vertices, GLsizeiptr size);

        void Bind();
        void Unbind();
        void Delete();
        GLuint GetID() const; // Método para obter o ID do VBO
};

#endif