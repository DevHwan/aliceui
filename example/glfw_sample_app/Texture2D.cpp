#include "Texture2D.h"

#include <AUISkiaConfig.h>

#include <utility>
#include <cassert>

Texture2D::~Texture2D() {
    this->Destroy();
}

Texture2D::Texture2D(Texture2D&& other) {
    (*this) = std::move(other);
}

Texture2D& Texture2D::operator=(Texture2D &&other) {
    this->Destroy();
    this->m_Id = other.m_Id;
    other.m_Id = 0;
    return *this;
}

bool Texture2D::IsValid() const {
    return (GL_FALSE != glIsTexture(this->m_Id));
}

bool Texture2D::Create() {
    glGenTextures(1, &this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    glBindTexture(GL_TEXTURE_2D, this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    
    // Dummy single pixel buffer
    char tmp[4] = { 0, };
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1, 1, 0, GL_BGRA, GL_UNSIGNED_BYTE, tmp);
    assert(GL_NO_ERROR == glGetError());
    
    if (false == this->IsValid())
        return false;
    
    return true;
}

bool Texture2D::UpdateImage(const SkPixmap& pixmap) {
    if (false == this->IsValid())
        return false;
    glBindTexture(GL_TEXTURE_2D, this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, pixmap.width(), pixmap.height(), 0, GL_BGRA, GL_UNSIGNED_BYTE, pixmap.addr());
    assert(GL_NO_ERROR == glGetError());
    return true;
}

bool Texture2D::Destroy() {
    if (this->IsValid()) {
        glDeleteTextures(1, &this->m_Id);
        assert(GL_NO_ERROR == glGetError());
        this->m_Id = 0;
        return true;
    }
    return false;
}

bool Texture2D::Bind() const {
    if (false == this->IsValid())
        return false;
    glBindTexture(GL_TEXTURE_2D, this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    return true;
}
