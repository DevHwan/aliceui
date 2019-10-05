#pragma once

#include "AUIRecyclerCommonDef.h"
#include "AUILayoutWidget.h"

class ALICEUI_API AUIRecyclerWidget : public AUILayoutWidget
{
    using SuperWidget = AUILayoutWidget;
    using Adapter = AUIRecyclerAdapter;
    using LayoutManager = AUIRecyclerLayoutManager;
public:
    AUIRecyclerWidget();
    ~AUIRecyclerWidget() override;


    //////////////////////////////////////////////////////////////////////////
    // Adapter
public:
    void SetAdapter(std::shared_ptr<Adapter> pAdapter);
    std::shared_ptr<Adapter> GetAdapter() const {
        return m_pAdapter;
    }

    //////////////////////////////////////////////////////////////////////////
    // LayoutManager
public:
    void SetLayoutManager(std::unique_ptr<LayoutManager> pLayoutManager);
    LayoutManager* GetLayoutManager() const {
        AUIAssert(m_pLayoutManager);
        return m_pLayoutManager.get();
    }

    //////////////////////////////////////////////////////////////////////////
    // Measure
protected:
    void OnMeasureSize(SkScalar width, AUIMeasureSpec widthSpec, SkScalar height, AUIMeasureSpec heightSpec) override;
    void OnUpdateChildPosition() override;

    //////////////////////////////////////////////////////////////////////////
    // Internal
protected:
    void SyncAdapter();
    const std::vector<std::shared_ptr<AUIRecyclerWidgetHolder>>& GetWidgetHolders() const noexcept {
        return m_WidgetHolders;
    }
private:
    void NotifyChange();
    void ItemChanged(size_t pos);
    void ItemInserted(size_t pos);
    void ItemMoved(size_t fromPos, size_t toPos);
    void ItemRemoved(size_t pos);
    void ItemRangeChanged(size_t startPos, size_t itemCount);
    void ItemRangeInserted(size_t startPos, size_t itemCount);
    void ItemRangeRemoved(size_t startPos, size_t itemCount);
    
    
private:
    std::shared_ptr<Adapter> m_pAdapter;
    std::unique_ptr<LayoutManager> m_pLayoutManager;
    std::vector<std::shared_ptr<AUIRecyclerWidgetHolder>> m_WidgetHolders;
    AUISlotPool m_spoolAdapter;
};
