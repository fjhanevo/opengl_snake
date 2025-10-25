#pragma once

#include <glad/glad.h>

class Texture2D 
{
public:
    // constructor
    Texture2D();

    // ID of texture objects
    GLuint m_ID; 

    // dimensions
    GLuint m_width, m_height;

    // texture format
    GLuint m_internalFormat, m_imageFormat;

    // texture configuration
    GLuint m_wrapS;               // wrapping mode on S axis
    GLuint m_wrapT;               // wrapping mode on T axis
    GLuint m_filterMin;           // filtering mode px < screen px
    GLuint m_filterMax;           // filtering mode 

    // generates texture from image data
    void generate(GLuint width, GLuint height, unsigned char *data);

    // binds the texture as the current active GL_TEXTURE_2D object
    void bind() const;
};
