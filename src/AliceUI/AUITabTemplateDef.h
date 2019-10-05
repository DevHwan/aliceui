#pragma once

#include "AUITemplate.h"
#include "AUITabWidget.h"
#include "AUITab.h"

template< class _TabWidget >
class MAUITabTemplate : public AUITemplate
{
    static_assert(std::is_base_of< AUITabWidget, _TabWidget >::value, "Derived from tab widget only.");
public:
    MAUITabTemplate() = default;
    ~MAUITabTemplate() override = default;

protected:
    std::shared_ptr<AUIWidget> OnCreateWidget() override {
        auto pWidget = std::make_shared<_TabWidget>();
        return pWidget;
    }
    void OnUpdateParam(AUIWidget* const pRoot, const AUITemplParam& param) override {
        auto _pTab = pRoot->DynCast<_TabWidget>();
        if (nullptr == _pTab)
        {
            AUIAssertFailReason("Incorrect widget");
            return;
        }
        if (param.fType == AUITemplParam::TEMPL_PARAM_CHILD_SHOW)
        {
            auto tChildshow = std::get<AUITemplParam::_temp_show>(param.fParam);
            if (auto pTargetTab = _pTab->FindTabByWidget(tChildshow.fWidget))
            {
                _pTab->HideTab(pTargetTab, !tChildshow.fShow);
                auto pCurrentTab = _pTab->GetCurrentTab();

                if (tChildshow.fShow == false && pCurrentTab == pTargetTab)
                {
                    for (auto i = 0; i < _pTab->GetTabCount(); i++)
                    {
                        if (false == _pTab->IsHiddenTab(i))
                        {
                            _pTab->SetCurrentTab(_pTab->FindTabByIndex(i));
                            break;
                        }
                    }


                }
            }
        }
        else if (param.fType == AUITemplParam::TEMPL_PARAM_MSS)
        {
            auto pMss = std::get<std::shared_ptr<const AUIWidgetStyle> >(param.fParam);
            _pTab->SetStyleSheet(pMss);
        }
    }
    void OnUpdateInsert(AUIWidget* const pRoot, const AUITemplInput& input) override {
        auto _pTab = pRoot->DynCast<AUITabWidget>();
        if (nullptr == _pTab)
        {
            AUIAssertFailReason("Incorrect widget");
            return;
        }

        const auto _text = input.fText;
        const auto _image = input.fImage;
        const auto _pWidget = input.fWidget;
        if (nullptr == _pWidget)
            return;

        AUIAssert(_pWidget);
        _pTab->AddTab(AUITab::CreateTab(_text, _image, _pWidget));
    }
    void OnUpdateRemove(AUIWidget* const pRoot, const AUITemplInput& input) override {
        auto _pTab = pRoot->DynCast<AUITabWidget>();
        if (nullptr == _pTab)
        {
            AUIAssertFailReason("Incorrect widget");
            return;
        }
        const auto _text = input.fText;
        //const auto image = input.fImage;
        const auto _pWidget = input.fWidget;
        if (nullptr == _pWidget)
            return;

        AUIAssert(_pWidget);
        _pTab->RemoveTab(_pWidget);
    }
    void OnUpdateClear(AUIWidget* const pRoot, const AUITemplInput& input) override {
        auto _pTab = pRoot->DynCast<AUITabWidget>();
        if (nullptr == _pTab)
        {
            AUIAssertFailReason("Incorrect widget");
            return;
        }
        _pTab->ClearTab();
    }
};
