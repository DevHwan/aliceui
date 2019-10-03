#include "CubeModel.h"

#include <array>
#include <utility>
#include <cassert>

CubeModel::~CubeModel() {
    this->Destroy();
}

CubeModel::CubeModel(CubeModel&& other) {
    (*this) = std::move(other);
}

CubeModel& CubeModel::operator=(CubeModel &&other) {
    this->Destroy();
    this->m_Id = other.m_Id;
    this->m_IdVtx = other.m_IdVtx;
    this->m_IdTex = other.m_IdTex;
    other.m_Id = 0;
    other.m_IdVtx = 0;
    other.m_IdTex = 0;
    return *this;
}

bool CubeModel::IsValid() const {
    return (GL_FALSE != glIsVertexArray(this->m_Id));
}

bool CubeModel::Create() {
    glGenVertexArrays(1, &this->m_Id);
    assert(GL_NO_ERROR == glGetError());
    glBindVertexArray(this->m_Id);
    assert(GL_NO_ERROR == glGetError());

    glGenBuffers(1, &this->m_IdVtx);
    assert(GL_NO_ERROR == glGetError());
    
    static const std::array<float, 108> sVtxData = {
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
         1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f, -1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f,
        -1.0f,  1.0f,  1.0f,
         1.0f, -1.0f,  1.0f
    };

    glBindBuffer(GL_ARRAY_BUFFER, this->m_IdVtx);
    assert(GL_NO_ERROR == glGetError());
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sVtxData.size(), sVtxData.data(), GL_STATIC_DRAW);
    assert(GL_NO_ERROR == glGetError());

    static const std::array<float, 12> sTexCoordData = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };
    
    glGenBuffers(1, &this->m_IdTex);
    assert(GL_NO_ERROR == glGetError());
    glBindBuffer(GL_ARRAY_BUFFER, this->m_IdTex);
    assert(GL_NO_ERROR == glGetError());
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * sTexCoordData.size(), sTexCoordData.data(), GL_STATIC_DRAW);
    assert(GL_NO_ERROR == glGetError());

    if (false == this->IsValid())
        return false;

    return true;
}

bool CubeModel::Destroy() {
    if (this->IsValid()) {
        glDeleteBuffers(1, &this->m_IdTex);
        assert(GL_NO_ERROR == glGetError());
        glDeleteBuffers(1, &this->m_IdVtx);
        assert(GL_NO_ERROR == glGetError());
        glDeleteVertexArrays(1, &this->m_Id);
        assert(GL_NO_ERROR == glGetError());
        this->m_Id = 0;
        this->m_IdVtx = 0;
        this->m_IdTex = 0;
        return true;
    }
    return false;
}

void CubeModel::Draw() {
    if (false == this->IsValid())
          return;
      glBindVertexArray(this->m_Id);
      assert(GL_NO_ERROR == glGetError());

      glEnableVertexAttribArray(0);
      assert(GL_NO_ERROR == glGetError());
      glBindBuffer(GL_ARRAY_BUFFER, this->m_IdVtx);
      assert(GL_NO_ERROR == glGetError());
      glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
      assert(GL_NO_ERROR == glGetError());

      glEnableVertexAttribArray(1);
      assert(GL_NO_ERROR == glGetError());
      glBindBuffer(GL_ARRAY_BUFFER, this->m_IdTex);
      assert(GL_NO_ERROR == glGetError());
      glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<void*>(0));
      assert(GL_NO_ERROR == glGetError());

      glDrawArrays(GL_TRIANGLES, 0, 36);
      assert(GL_NO_ERROR == glGetError());

      glDisableVertexAttribArray(0);
      assert(GL_NO_ERROR == glGetError());
}
  
