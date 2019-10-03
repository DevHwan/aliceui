#pragma once

#include "OpenGLCommon.h"

class Shader;
class Texture2D;
class SampleState;

class ShaderProgram final {
public:
    ShaderProgram() noexcept = default;
    ~ShaderProgram();

    ShaderProgram(const ShaderProgram&) = delete;
    ShaderProgram& operator=(const ShaderProgram&) = delete;

    ShaderProgram(ShaderProgram&& other);
    ShaderProgram& operator=(ShaderProgram&& other);
    
    bool IsValid() const;
    bool Create(const Shader& vtxShader, const Shader& fragmentShader);
    bool Destroy();
    GLuint GetUniformId(const char* name) const;
    bool UseProgram();
    bool UnuseProgram();
    
    bool BindTexture(const Texture2D& texture, const SampleState& sampleState, const char* uniformName, const int uniformIndex);

    inline GLuint Id() const noexcept {
        return this->m_Id;
    }
private:
    GLuint m_Id = 0;
};
