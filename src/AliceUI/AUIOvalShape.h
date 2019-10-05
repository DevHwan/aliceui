#pragma once

#include "AUIRoundRectShape.h"

class ALICEUI_API AUIOvalShape : public AUIRoundRectShape
{
public:
    AUIOvalShape();
    ~AUIOvalShape() override;


    //////////////////////////////////////////////////////////////////////////
    // Size
protected:
    void OnResize(float width, float height) override;
};
