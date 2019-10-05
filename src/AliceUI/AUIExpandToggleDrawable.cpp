#include "pch.h"
#include "AUIExpandToggleDrawable.h"

AUIExpandToggleDrawable::AUIExpandToggleDrawable()
    : m_DefaultColor( SkColorSetRGB( 68, 68, 68 ) )
    , m_HoverColor( SkColorSetRGB( 130, 186, 255 ) )
    , m_PressColor( SkColorSetRGB( 130, 186, 255 ) )
{

}

AUIExpandToggleDrawable::~AUIExpandToggleDrawable()
{

}

void AUIExpandToggleDrawable::OnDraw( SkCanvas* const canvas )
{
    canvas->translate( 4.0f, 4.0f );

    SkPaint iconPaint;
    iconPaint.setAntiAlias( true );
    iconPaint.setColor( m_DefaultColor );
    const auto state = GetDrawUIState();
    if ( state.IsMouseHovered() )
    {
        iconPaint.setColor( m_HoverColor );
    }
    if ( state.IsPressed() )
    {
        iconPaint.setColor( m_PressColor );
    }

    const auto triSize = 6.0f;//(std::min)( width, height );
    SkPath triPath;
    triPath.moveTo( 0, 0 );
    triPath.lineTo( triSize, triSize * 0.5f );
    triPath.lineTo( 0, triSize );
    triPath.close();

    SkMatrix triMat;
    triMat.reset();
    triMat.postRotate( 90.0f * GetBlendFactor(), triSize * 0.5f, triSize * 0.5f );
    triPath.transform( triMat );



    canvas->save();
    canvas->drawPath( triPath, iconPaint );
    canvas->restore();

}
