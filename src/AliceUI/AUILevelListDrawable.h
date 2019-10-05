#pragma once

#include "AUIDrawable.h"

class ALICEUI_API AUILevelListDrawable : public AUIDrawable
{
public:
    AUILevelListDrawable();
    ~AUILevelListDrawable() override;


    //////////////////////////////////////////////////////////////////////////
    // Draw
protected:
    void OnDraw(SkCanvas* const canvas) override;
    bool IsRefreshDraw() const override {
        return m_bRefreshDraw;
    }


    //////////////////////////////////////////////////////////////////////////
    // Level Index
protected:
    void OnChangeLevelIndex() override;


    //////////////////////////////////////////////////////////////////////////
    // Drawable
public:
    void ClearLevel();
    void AddLevel(int low, int high, const std::shared_ptr< AUIDrawable >& pDrawable);
    void AddLevel(int val, const std::shared_ptr< AUIDrawable >& pDrawable) {
        AddLevel(val, val, pDrawable);
    }
protected:
    AUIDrawable* GetCurDrawable() const noexcept {
        return m_pCurDrawable.get();
    }
private:
    struct IndexData
    {
        int fLowBound = 0;
        int fHighBound = 0;
        std::shared_ptr<AUIDrawable> fDrawable;
        IndexData() = default;
        IndexData(int _low, int _high, const std::shared_ptr<AUIDrawable>& _pDrawable) : fLowBound(_low), fHighBound(_high), fDrawable(_pDrawable) {}
    };
    
    
private:
    std::shared_ptr<AUIDrawable> m_pCurDrawable;
    std::vector<IndexData> m_IndexData;
    bool m_bRefreshDraw = false;
};
