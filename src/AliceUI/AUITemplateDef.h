#pragma once


#include "AUICommonDef.h"
#include <variant>

class AUIDrawable;
class AUIWidget;
class AUIWidgetStyle;

struct AUITemplParam
{
    enum TEMPL_PARAM
    {
        TEMPL_PARAM_CHILD_SHOW,
        TEMPL_PARAM_MSS,
        TEMPL_PARAM_COMPONENT_MSS,
        TEMPL_PARAM_TEXT,
        TEMPL_PARAM_IMAGE,
    };
    struct _temp_show {
        std::shared_ptr<AUIWidget > fWidget;
        bool fShow;
        _temp_show(std::shared_ptr<AUIWidget > _widget, bool _show) :fWidget(_widget), fShow(_show) {}
    };
    struct _temp_comp_mss
    {
        std::wstring fComponent;
        std::shared_ptr<const AUIWidgetStyle> fMss;
        _temp_comp_mss(std::wstring _comp, std::shared_ptr<const AUIWidgetStyle> _mss) : fComponent(_comp), fMss(_mss) {}
    };


    TEMPL_PARAM fType;
    std::variant
        <
        std::wstring,
        std::shared_ptr< const AUIDrawable >,
        std::shared_ptr<const AUIWidgetStyle>,
        _temp_show,
        _temp_comp_mss
        > fParam;

    AUITemplParam(std::shared_ptr<AUIWidget > _widget, bool _show) :fType(TEMPL_PARAM_CHILD_SHOW), fParam(_temp_show(_widget, _show)) {  }
    AUITemplParam(std::shared_ptr< const AUIDrawable > _image) :fType(TEMPL_PARAM_IMAGE), fParam(_image) {  }
    AUITemplParam(std::wstring _text) :fType(TEMPL_PARAM_TEXT), fParam(_text) {  }
    AUITemplParam(std::shared_ptr<const AUIWidgetStyle> _mss) :fType(TEMPL_PARAM_MSS), fParam(_mss) {  }
    AUITemplParam(std::wstring _comp, std::shared_ptr<const AUIWidgetStyle> _mss) :fType(TEMPL_PARAM_COMPONENT_MSS), fParam(_temp_comp_mss(_comp, _mss)) {  }



    //         std::wstring fVar;
    //         std::wstring fText;
    //         std::shared_ptr< const SkBitmap > fImage;
             //std::shared_ptr< AUIWidget > fWidget;
             //std::shared_ptr< MSSStyleSheet const> fMss;
    //         bool fHasShow;
    //         bool fSubShow;
    //         bool fShow;
    //         AUITemplParam() : fHasShow( false ), fSubShow( false ), fShow( true ) { }
    //         AUITemplParam( bool _show ) : fHasShow( true ), fSubShow( false ), fShow( _show ) { }
    //         AUITemplParam( bool _show, const std::shared_ptr< AUIWidget >& _widget ) : fHasShow( false ), fSubShow( true ), fShow( _show ), fWidget( _widget ) { }
    //         AUITemplParam( const std::wstring& _var, const std::wstring& _text ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fText( _text ) { }
    //         AUITemplParam( const std::wstring& _var, const std::shared_ptr< const SkBitmap >& _image ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fImage( _image ) { }
    //         AUITemplParam( const std::wstring& _var, const std::shared_ptr< AUIWidget >& _widget ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fWidget( _widget ) { }
    //         AUITemplParam( const std::wstring& _var, const std::wstring& _text, const std::shared_ptr< const SkBitmap >& _image ) : fHasShow( false ), fSubShow( false ), fShow( true ), fVar( _var ), fText( _text ), fImage( _image ) { }

};

struct AUITemplInput
{
    std::wstring fVar;
    std::wstring fText;
    std::shared_ptr< AUIDrawable > fImage;
    std::shared_ptr< AUIWidget > fWidget;

    AUITemplInput() { }
    AUITemplInput(const std::wstring& _var, const std::shared_ptr< AUIWidget >& _widget) : fVar(_var), fWidget(_widget) { }
    AUITemplInput(const std::wstring& _var, const std::wstring& _text, const std::shared_ptr< AUIWidget >& _widget) : fVar(_var), fText(_text), fWidget(_widget) { }
    AUITemplInput(const std::wstring& _var, const std::wstring& _text) : fVar(_var), fText(_text) { }
    AUITemplInput(const std::wstring& _var, const std::shared_ptr< AUIDrawable >& _image) : fVar(_var), fImage(_image) { }
    AUITemplInput(const std::wstring& _var, const std::wstring& _text, const std::shared_ptr< AUIDrawable >& _image, const std::shared_ptr< AUIWidget >& _widget) : fVar(_var), fText(_text), fImage(_image), fWidget(_widget) { }
};
