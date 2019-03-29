#include "pch.h"
#include "AUIRulerWidget.h"
#include "AUIRulerDrawable.h"

AUIRulerWidget::AUIRulerWidget()
    : m_pRulerDrawable( std::make_shared< AUIRulerDrawable >() )
{
	SetBackgroundDrawable( m_pRulerDrawable );
    SetDefaultSize(50.0f, 50.0f);
}

AUIRulerWidget::~AUIRulerWidget()
{

}

void AUIRulerWidget::SetRefPos( SkScalar pos )
{
    GetRulerDrawable()->SetRefPos( pos );
}

SkScalar AUIRulerWidget::GetRefPos() const
{
    return GetRulerDrawable()->GetRefPos();
}

void AUIRulerWidget::SetLocation( AUIRulerLocation location )
{
    GetRulerDrawable()->SetLocation( location );
    Invalidate();
}

AUIRulerLocation AUIRulerWidget::GetLocation() const
{
    return GetRulerDrawable()->GetLocation();
}

void AUIRulerWidget::SetScale( SkScalar val )
{
    GetRulerDrawable()->SetScale( val );
	Invalidate();
}

AUIRulerDrawable* const AUIRulerWidget::GetRulerDrawable() const
{
    return m_pRulerDrawable.get();
}

SkScalar AUIRulerWidget::GetScale() const
{
    return GetRulerDrawable()->GetScale();
}

void AUIRulerWidget::SetUseMarking(bool val)
{
    GetRulerDrawable()->SetUseMarking(val);
}

bool AUIRulerWidget::IsUseMarking() const
{
    return GetRulerDrawable()->IsUseMarking();
}

void AUIRulerWidget::SetBasis( SkScalar val )
{
    GetRulerDrawable()->SetBasis( val );
    Invalidate();
}

SkScalar AUIRulerWidget::GetBasis() const
{
    return GetRulerDrawable()->GetBasis();
}

void AUIRulerWidget::SetGradationSize( SkScalar val )
{
    GetRulerDrawable()->SetGradationSize( val );
    Invalidate();
}

SkScalar AUIRulerWidget::GetGradationSize() const
{
    return GetRulerDrawable()->GetGradationSize();
}

void AUIRulerWidget::SetMaxTextWidth( SkScalar val )
{
    GetRulerDrawable()->SetMaxTextWidth( val );
}

void AUIRulerWidget::SetMaxTextHeight( SkScalar val )
{
    GetRulerDrawable()->SetMaxTextHeight( val );
}

SkScalar AUIRulerWidget::GetMaxTextWidth() const
{
    return GetRulerDrawable()->GetMaxTextWidth();
}

SkScalar AUIRulerWidget::GetMaxTextHeight() const
{
    return GetRulerDrawable()->GetMaxTextHeight();
}

void AUIRulerWidget::SetLineColor( SkColor color )
{
    GetRulerDrawable()->RefLinePaint().setColor( color );
}

void AUIRulerWidget::SetTextColor( SkColor color )
{
    GetRulerDrawable()->RefTextPaint().setColor( color );
}

SkColor AUIRulerWidget::GetLineColor() const
{
    return GetRulerDrawable()->RefLinePaint().getColor();
}

SkColor AUIRulerWidget::GetTextColor() const
{
    return GetRulerDrawable()->RefTextPaint().getColor();
}

void AUIRulerWidget::SetTextSize( SkScalar size )
{
    GetRulerDrawable()->RefTextPaint().setTextSize( size );
}

SkScalar AUIRulerWidget::GetTextSize() const
{
    return GetRulerDrawable()->RefTextPaint().getTextSize();
}

void AUIRulerWidget::SetRulerPadding( SkScalar l, SkScalar t, SkScalar r, SkScalar b )
{
    GetRulerDrawable()->SetDrawPadding( SkRect::MakeLTRB( l, t, r, b ) );
}
