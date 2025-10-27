#include "texture.h"

Texture2D::Texture2D()
    : m_width(0), m_height(0), m_internalFormat(GL_RGB), m_imageFormat(GL_RGB),
    m_wrapS(GL_REPEAT), m_wrapT(GL_REPEAT), m_filterMin(GL_NEAREST), m_filterMax(GL_NEAREST)
{
    glGenTextures(1, &m_ID);
}

void Texture2D::generate(GLuint width, GLuint height, unsigned char *data)
{
    m_width = width;
    m_height = height;

    // create texture
    glBindTexture(GL_TEXTURE_2D, m_ID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_internalFormat,
                 m_width, m_height, 0, m_imageFormat,
                 GL_UNSIGNED_BYTE, data);

    // set texture wrap and filter modes
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, m_wrapS);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, m_wrapT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, m_filterMin);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, m_filterMax);

    // unbind texture
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture2D::bind() const
{
    glBindTexture(GL_TEXTURE_2D, m_ID);
}

