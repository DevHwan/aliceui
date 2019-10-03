#pragma once

#include "OpenGLCommon.h"

class CubeModel final
{
public:
    CubeModel() noexcept = default;
    ~CubeModel();
    
    CubeModel(const CubeModel&) = delete;
    CubeModel& operator=(const CubeModel&) = delete;
    
    CubeModel(CubeModel&& other);
    CubeModel& operator=(CubeModel&& other);

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

