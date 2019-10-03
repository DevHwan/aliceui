#pragma once

#include "OpenGLCommon.h"

class QuadModel final
{
public:
    QuadModel() noexcept = default;
    ~QuadModel();
    
    QuadModel(const QuadModel&) = delete;
    QuadModel& operator=(const QuadModel&) = delete;
    
    QuadModel(QuadModel&& other);
    QuadModel& operator=(QuadModel&& other);

    bool IsValid() const;
    bool Create();
    bool Destroy();
    void Draw();
    
    inline GLuint Id() const noexcept {
        return this->m_Id;
    }
    inline GLuint IdVtx() const noexcept {
        return this->m_IdVtx;
    }
    inline GLuint IdTex() const noexcept {
        return this->m_IdTex;
    }
private:
    GLuint m_Id = 0;
    GLuint m_IdVtx = 0;
    GLuint m_IdTex = 0;
};

