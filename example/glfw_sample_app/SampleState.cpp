#include "SampleState.h"

#include <utility>
#include <cassert>


SampleState::~SampleState() {
    this->Destroy();
}

SampleState::SampleState(SampleState&& other) {
    (*this) = std::move(other);
}

SampleState& SampleState::operator=(SampleState&& other) {
    this->Destroy();
    this->m_Id = other.m_Id;
    other.m_Id = 0;
    return *this;
}

bool SampleState::IsValid() const {
    return (GL_FALSE != glIsSampler(this->m_Id));
}

bool SampleState::Create() {
    glGenSamplers(1, &this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    if (false == IsValid())
        return false;
    glSamplerParameteri(this->m_Id, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    assert(GL_NO_ERROR == glGetError());
    glSamplerParameteri(this->m_Id, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    assert(GL_NO_ERROR == glGetError());
    glSamplerParameteri(this->m_Id, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    assert(GL_NO_ERROR == glGetError());
    glSamplerParameteri(this->m_Id, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    assert(GL_NO_ERROR == glGetError());
    return true;
}

bool SampleState::Destroy() {
    if (this->IsValid()) {
        glDeleteSamplers(1, &this->m_Id);
        assert(GL_NO_ERROR == glGetError());
        this->m_Id = 0;
        return true;
    }
    return false;
}
