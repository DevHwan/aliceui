#pragma once

#include "AUIDrawableWidget.h"

class ALICEUI_API AUI3DDrawableWidget : public AUIDrawableWidget
{
public:
    AUI3DDrawableWidget();
    virtual ~AUI3DDrawableWidget();


    //////////////////////////////////////////////////////////////////////////
    // Matrix
public:
    void SetMatrix(const glm::mat4& mat) { m_matModel = mat; }
    const glm::mat4& GetMatrix() { return m_matModel; }
private:
    glm::mat4 m_matModel = glm::mat4(1.0f);
};
