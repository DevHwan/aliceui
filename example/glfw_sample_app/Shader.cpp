#include "Shader.h"

#include <utility>
#include <cassert>

Shader::~Shader() {
    this->Destroy();
}

Shader::Shader(Shader&& other) {
    (*this) = std::move(other);
}

Shader& Shader::operator=(Shader&& other) {
    this->Destroy();
    this->m_Id = other.m_Id;
    other.m_Id = 0;
    return *this;
}

bool Shader::IsValid() const {
    return (GL_FALSE != glIsShader(m_Id));
}

bool Shader::CreateVertexShader(const char* shaderCode) {
    m_Id = glCreateShader(GL_VERTEX_SHADER);
    assert(GL_NO_ERROR == glGetError());
    if (!this->IsValid())
        return false;
    glShaderSource(m_Id, 1, &shaderCode, nullptr);
    assert(GL_NO_ERROR == glGetError());
    glCompileShader(m_Id);
    assert(GL_NO_ERROR == glGetError());
    int result = GL_FALSE;
    glGetShaderiv(m_Id, GL_COMPILE_STATUS, &result);
    assert(GL_NO_ERROR == glGetError());
    if (GL_FALSE == result) {
        this->Destroy();
        return false;
    }
    return true;
}

bool Shader::CreateFragmentShader(const char *shaderCode) {
    m_Id = glCreateShader(GL_FRAGMENT_SHADER);
    assert(GL_NO_ERROR == glGetError());
    if (!this->IsValid())
        return false;
    glShaderSource(this->m_Id, 1, &shaderCode, nullptr);
    assert(GL_NO_ERROR == glGetError());
    glCompileShader(this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    int result = GL_FALSE;
    glGetShaderiv(this->m_Id, GL_COMPILE_STATUS, &result);
    assert(GL_NO_ERROR == glGetError());
    if (GL_FALSE == result) {
        this->Destroy();
        return false;
    }
    return true;
}

bool Shader::Destroy() {
    if (this->IsValid()) {
        glDeleteShader(this->m_Id);
        assert(GL_NO_ERROR == glGetError());
        this->m_Id = 0;
        return true;
    }
    return false;
}
