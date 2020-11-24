#include "mepch.h"
#include "VertexArray.h"
#include "ShaderProgram.h"

namespace gl
{

    VertexBuffer createStaticVertexBuffer(size_t bufferSize, const void* buffer)
    {
        VertexBuffer vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vbo;
    }

    VertexBuffer createDynamicVertexBuffer(size_t bufferSize, const void* buffer)
    {
        VertexBuffer vbo;
        glGenBuffers(1, &vbo);
        glBindBuffer(GL_ARRAY_BUFFER, vbo);
        glBufferData(GL_ARRAY_BUFFER, bufferSize, buffer, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ARRAY_BUFFER, 0);

        return vbo;
    }

    ElementBuffer createStaticElementBuffer(size_t bufferSize, const void* buffer)
    {
        ElementBuffer ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, buffer, GL_STATIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return ebo;
    }

    ElementBuffer createDynamicElementBuffer(size_t bufferSize, const void* buffer)
    {
        ElementBuffer ebo;
        glGenBuffers(1, &ebo);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, bufferSize, buffer, GL_DYNAMIC_DRAW);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

        return ebo;
    }

    VertexArray createVertexArray(ElementBuffer ebo, std::vector<VertexAttribute> attributes)
    {
        VertexArray vao;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo);
        for (int i = 0; i < attributes.size(); i++)
        {
            VertexAttribute& attribute = attributes[i];
            glBindBuffer(GL_ARRAY_BUFFER, attribute.vbo);
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i, attribute.length, attribute.dataType, GL_FALSE, attribute.stride, attribute.offset);
            glVertexAttribDivisor(i, attribute.divisor);
        }
        glBindVertexArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    
        return vao;
    }

    void deleteVertexBuffer(VertexBuffer vbo)
    {
        glDeleteBuffers(1, &vbo);
    }

    void deleteElementBuffer(ElementBuffer ebo)
    {
        glDeleteBuffers(1, &ebo);
    }

    void deleteVertexArray(VertexArray vao)
    {
        glDeleteVertexArrays(1, &vao);
    }

}