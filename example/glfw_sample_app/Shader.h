#pragma once

#include "OpenGLCommon.h"

class Shader final {
public:
    Shader() noexcept = default;
    ~Shader();
    
    Shader(const Shader&) = delete;
    Shader& operator=(const Shader&) = delete;

    Shader(Shader&& other);
    Shader& operator=(Shader&& other);

    bool IsValid() const;
    bool CreateVertexShader(const char* shaderCode);
    bool CreateFragmentShader(const char* shaderCode);
    bool Destroy();

    inline GLuint Id() const noexcept {
        return this->m_Id;
    }
private:
    GLuint m_Id = 0;
};
