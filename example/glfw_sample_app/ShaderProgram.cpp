#include "ShaderProgram.h"
#include "Shader.h"
#include "Texture2D.h"
#include "SampleState.h"

#include <utility>
#include <cassert>

ShaderProgram::~ShaderProgram() {
    this->Destroy();
}

ShaderProgram::ShaderProgram(ShaderProgram&& other) {
    (*this) = std::move(other);
}

ShaderProgram& ShaderProgram::operator=(ShaderProgram&& other) {
    this->Destroy();
    this->m_Id = other.m_Id;
    other.m_Id = 0;
    return *this;
}

bool ShaderProgram::IsValid() const {
    return (GL_FALSE != glIsProgram(m_Id));
}

bool ShaderProgram::Create(const Shader& vtxShader, const Shader& fragmentShader) {
    if (false == vtxShader.IsValid())
        return false;
    if (false == fragmentShader.IsValid())
        return false;

    this->m_Id = glCreateProgram();
    assert(GL_NO_ERROR == glGetError());
    if (false == IsValid())
        return false;

    glAttachShader(this->m_Id, vtxShader.Id());
    assert(GL_NO_ERROR == glGetError());
    glAttachShader(this->m_Id, fragmentShader.Id());
    assert(GL_NO_ERROR == glGetError());
    glLinkProgram(this->m_Id);
    assert(GL_NO_ERROR == glGetError());

    int result = GL_FALSE;
    glGetProgramiv(this->m_Id, GL_LINK_STATUS, &result);
    assert(GL_NO_ERROR == glGetError());
    if (GL_FALSE == result) {
        this->Destroy();
        return false;
    }

    glDetachShader(this->m_Id, vtxShader.Id());
    assert(GL_NO_ERROR == glGetError());
    glDetachShader(this->m_Id, fragmentShader.Id());
    assert(GL_NO_ERROR == glGetError());

    return true;
}

bool ShaderProgram::Destroy() {
    if (this->IsValid()) {
        glDeleteProgram(this->m_Id);
        assert(GL_NO_ERROR == glGetError());
        this->m_Id = 0;
        return true;
    }
    return false;
}

GLuint ShaderProgram::GetUniformId(const char *name) const {

    if (false == this->IsValid())
        return 0;
    const auto loc = glGetUniformLocation(this->m_Id, name);
    assert(GL_NO_ERROR == glGetError());
    return loc;
}

bool ShaderProgram::UseProgram() {
    if (this->IsValid()) {
        glUseProgram(this->m_Id);
        assert(GL_NO_ERROR == glGetError());
        return true;
    }
    return false;
}

bool ShaderProgram::UnuseProgram() {
    glUseProgram(0);
    assert(GL_NO_ERROR == glGetError());
    return true;
}

bool ShaderProgram::BindTexture(const Texture2D& texture, const SampleState& sampleState, const char* uniformName, const int uniformIndex) {

    const auto textureUniformId = this->GetUniformId(uniformName);
    glUniform1i(textureUniformId, uniformIndex);
    assert(GL_NO_ERROR == glGetError());
    glActiveTexture(GL_TEXTURE0 + uniformIndex);
    assert(GL_NO_ERROR == glGetError());
    texture.Bind();
    glBindSampler(uniformIndex, sampleState.Id());
    assert(GL_NO_ERROR == glGetError());
}
