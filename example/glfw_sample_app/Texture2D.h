#pragma once

#include "OpenGLCommon.h"

class SkPixmap;

class Texture2D final
{
public:
    Texture2D() noexcept = default;
    ~Texture2D();
    
    Texture2D(const Texture2D&) = delete;
    Texture2D& operator=(const Texture2D&) = delete;
    
    Texture2D(Texture2D&& other);
    Texture2D& operator=(Texture2D&& other);
    
    bool IsValid() const ;
    bool Create();

    bool UpdateImage(const SkPixmap& pixmap);

    bool Destroy();
    bool Bind() const;
    
    inline GLuint Id() const {
        return this->m_Id;
    }
private:
    GLuint m_Id = 0;
};

