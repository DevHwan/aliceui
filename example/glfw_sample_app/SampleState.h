#pragma once

#include "OpenGLCommon.h"

class SampleState final
{
public:
    SampleState() noexcept = default;
    ~SampleState();
    
    SampleState(const SampleState&) = delete;
    SampleState& operator=(const SampleState&) = delete;
    
    SampleState(SampleState&& other);
    SampleState& operator=(SampleState&& other);

    bool IsValid() const;
    bool Create();
    bool Destroy();

    inline GLuint Id() const noexcept {
        return m_Id;
    }
private:
    GLuint m_Id = 0;
};
