#pragma once

#include "AUIRecyclerLayoutManager.h"

class ALICEUI_API AUIRecyclerLinearLayoutManager : public AUIRecyclerLayoutManager
{
public:
    AUIRecyclerLinearLayoutManager();
    ~AUIRecyclerLinearLayoutManager() override;

    //////////////////////////////////////////////////////////////////////////
    // Interface
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;


    //////////////////////////////////////////////////////////////////////////
    // Update position
protected:
    void UpdateChild_Horizontal();
    void UpdateChild_Vertical();

    //////////////////////////////////////////////////////////////////////////
    // Orientation
public:
    bool IsHorizontal() const noexcept {
        return m_bHorizontal;
    }
    void SetHorizontal(bool horizontal) noexcept {
        m_bHorizontal = horizontal;
    }
    
private:
    bool m_bHorizontal = false;
};
