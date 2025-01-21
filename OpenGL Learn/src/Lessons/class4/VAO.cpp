#include "VAO.h"

VAO::VAO()
{
    glGenVertexArrays(1, &ID);
}
void VAO::LinkVBO(VBO VBO, GLuint layout){
    VBO.Bind();
    glVertexAttribPointer(layout, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(layout);
    VBO.Unbind();
}

void VAO::Bind()
{
    glBindVertexArray(ID);
}

void VAO::Unbind()
{
    glBindVertexArray(ID);
}

void VAO::Delete()
{
    glDeleteVertexArrays(1, &ID);
}

GLuint VAO::GetID() const
{
    return ID; // Retorna o ID do buffer para ser utilizado na verificação
}