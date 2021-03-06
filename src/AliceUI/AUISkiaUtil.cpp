#include "pch.h"
#include "AUISkiaUtil.h"

constexpr SkTextEncoding GetWideCharTextEncoding() {
    return (2 == sizeof(wchar_t)) ? SkTextEncoding::kUTF16 : SkTextEncoding::kUTF32;
}

SkMatrix AUISkiaUtil::ToSkMat(const glm::mat4& m)
{
    SkMatrix mat;
    mat.setAll(m[0][0], m[0][1], m[0][3], m[1][0], m[1][1], m[1][3], m[3][0], m[3][1], m[3][3]);
    return mat;
}

SkColor AUISkiaUtil::MixColor(const SkColor& src, const SkColor& dst, SkScalar weight)
{
    const auto a = static_cast<U8CPU>(std::clamp(SkColorGetA(src) * weight + SkColorGetA(dst) * (1.0f - weight), 0.0f, 255.0f));
    const auto r = static_cast<U8CPU>(std::clamp(SkColorGetR(src) * weight + SkColorGetR(dst) * (1.0f - weight), 0.0f, 255.0f));
    const auto g = static_cast<U8CPU>(std::clamp(SkColorGetG(src) * weight + SkColorGetG(dst) * (1.0f - weight), 0.0f, 255.0f));
    const auto b = static_cast<U8CPU>(std::clamp(SkColorGetB(src) * weight + SkColorGetB(dst) * (1.0f - weight), 0.0f, 255.0f));

    return SkColorSetARGB(a, r, g, b);
}

bool AUISkiaUtil::IsInRect(const SkRect& rect, const SkPoint& p)
{
    return rect.left() <= p.x() && rect.right() >= p.x() && rect.top() <= p.y() && rect.bottom() >= p.y();
}

bool AUISkiaUtil::IsInRect(const SkRect& rect, SkScalar x, SkScalar y)
{
    return rect.left() <= x && rect.right() >= x && rect.top() <= y && rect.bottom() >= y;
}

glm::vec4 AUISkiaUtil::SkColorToVec4(const SkColor color)
{
    return glm::vec4(float(SkColorGetR(color)) / 255.0f, float(SkColorGetG(color)) / 255.0f, float(SkColorGetB(color)) / 255.0f, float(SkColorGetA(color)) / 255.0f);
}

glm::vec3 AUISkiaUtil::SkColor2vec3(const SkColor color)
{
    return glm::vec3(float(SkColorGetR(color)) / 255.0f, float(SkColorGetG(color)) / 255.0f, float(SkColorGetB(color)) / 255.0f);
}

SkScalar AUISkiaUtil::MeasureTextBound( const std::wstring& text, SkRect& bound, bool useTrailingSpace, const SkPaint& paint )
{
    if ( text.empty() )
    {
        bound.setEmpty();
        return SkScalar( 0 );
    }

    auto wtext = text;
    static const auto DummyText = std::wstring( L"." );
    if ( useTrailingSpace )
        wtext += DummyText;

    // TODO : Re-implement
    auto advance = SkFont().measureText(wtext.c_str(), wtext.length() * sizeof(std::wstring::value_type), GetWideCharTextEncoding(), &bound);

    if ( useTrailingSpace )
    {
        const auto dummyAdvance = SkFont().measureText( DummyText.c_str(), DummyText.length() * sizeof( std::wstring::value_type ), GetWideCharTextEncoding() );

        // Remove dummy text size
        advance -= dummyAdvance;
        ( bound ).fRight -= dummyAdvance;
    }

    return advance;
}

SkScalar AUISkiaUtil::MeasureTextBound(const std::wstring& text, const SkPaint& paint)
{
    SkRect tmpBound;
    return AUISkiaUtil::MeasureTextBound( text, tmpBound, false, paint );
}

SkScalar AUISkiaUtil::MeasureTextBound(const std::wstring& text, SkRect& bound, const SkPaint& paint)
{
    return AUISkiaUtil::MeasureTextBound( text, bound, false, paint );
}

SkScalar AUISkiaUtil::MeasureTextBound(const std::wstring& text, bool useTrailingSpace, const SkPaint& paint)
{
    SkRect tmpBound;
    return AUISkiaUtil::MeasureTextBound( text, tmpBound, useTrailingSpace, paint );
}

SkScalar AUISkiaUtil::MeasureTextBound( const std::vector< std::wstring >& arrTexts, SkRect& bound, const SkPaint& paint )
{
    bound.setEmpty();

    // TODO : Font
    const auto lineHeight = SkFont().getSpacing();
    const auto totalHeight = ( lineHeight ) * arrTexts.size();

    bool first = true;
    for ( const auto& text : arrTexts )
    {
        if ( first )
        {
            // TODO : Font
            SkFont().measureText(text.c_str(), text.length() * sizeof(std::wstring::value_type), GetWideCharTextEncoding(), &bound);
            first = false;
            continue;
        }

        SkRect tmpBound;
        SkFont().measureText( text.c_str(), text.length() * sizeof( std::wstring::value_type ), GetWideCharTextEncoding(), &tmpBound );
        bound.fLeft = (std::min)( bound.left(), tmpBound.left() );
        bound.fRight = (std::max)( bound.right(), tmpBound.right() );
    }
    bound.fTop = 0.0f;
    bound.fBottom = bound.fTop + totalHeight;

    return bound.width();
}

SkPoint AUISkiaUtil::CalcTextStartPos(const SkRect& textBound, const SkRect& textArea, const AUITextVertAlign vAlign, const AUITextHorzAlign hAlign, const SkPaint& paint)
{
    // TODO : Font
    SkFontMetrics metrics;
    SkFont().getMetrics(&metrics);
    
    // Horizontal
    float textStartX = textArea.left();
    if ( hAlign == AUITextHorzAlign::kCenter )
        textStartX += textArea.width() * 0.5f - ( textBound.left() + textBound.right() ) * 0.5f;
    else if ( hAlign == AUITextHorzAlign::kRight )
        textStartX = textArea.right() - textBound.right();

    // Vertical
    float textStartY = textArea.top();
    if ( vAlign == AUITextVertAlign::kTop )
        textStartY -= metrics.fTop;
    else if ( vAlign == AUITextVertAlign::kCenter )
        textStartY += textArea.height() * 0.5f - ( metrics.fTop + metrics.fBottom ) * 0.5f;
    else if ( vAlign == AUITextVertAlign::kBottom )
        textStartY = textArea.bottom() - metrics.fBottom;

    return SkPoint::Make( SkScalarFloorToScalar( textStartX ), SkScalarFloorToScalar( textStartY ) );
}

SkPoint AUISkiaUtil::CalcTextStartPos(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, const SkPaint& paint )
{
    SkRect tmpBound;
    AUISkiaUtil::MeasureTextBound( text, tmpBound, useTrailingSpace, paint );
    return AUISkiaUtil::CalcTextStartPos( tmpBound, textArea, vAlign, hAlign, paint );
}

SkPoint AUISkiaUtil::CalcTextStartPos(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, SkRect& textBound, const SkPaint& paint)
{
    AUISkiaUtil::MeasureTextBound( text, textBound, false, paint );
    return AUISkiaUtil::CalcTextStartPos( textBound, textArea, vAlign, hAlign, paint );
}

SkPoint AUISkiaUtil::CalcTextStartPos(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, SkRect& textBound, const SkPaint& paint)
{
    AUISkiaUtil::MeasureTextBound( text, textBound, useTrailingSpace, paint );
    return AUISkiaUtil::CalcTextStartPos( textBound, textArea, vAlign, hAlign, paint );
}

std::vector< SkPoint > AUISkiaUtil::CalcTextStartPos( const std::vector< std::wstring >& arrTexts, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint, const SkScalar lineHeight)
{
    std::vector< SkPoint > arrStartPos;
    if ( 0 == arrTexts.size() )
        return arrStartPos;

    arrStartPos.resize( arrTexts.size(), SkPoint::Make( 0.0f, 0.0f ) );

    // TODO : Font
    SkFontMetrics metric;
    SkFont().getMetrics(&metric);

    // TODO : Font
    const auto lineSpacing = (lineHeight >= 1.0f) ? lineHeight : SkFont().getSpacing();
    const auto totalHeight = (lineSpacing) * arrTexts.size();


    AUIAssert( arrStartPos.size() == arrTexts.size() );
    if ( AUITextVertAlign::kTop == vAlign )
    {
        for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
        {
            arrStartPos[idx].fY = textArea.top() - metric.fTop + (lineSpacing) * idx;
        }
    }
    else if ( AUITextVertAlign::kCenter == vAlign )
    {
        for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
        {
            arrStartPos[idx].fY = textArea.centerY() - totalHeight * 0.5f - metric.fTop + (lineSpacing) * idx;
        }
    }
    else if ( AUITextVertAlign::kBottom == vAlign )
    {
        for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
        {
            arrStartPos[idx].fY = textArea.bottom() - totalHeight - metric.fTop + (lineSpacing) * idx;
        }
    }
    else
    {
        AUIAssertFailReason("Corrupted enum value");
    }

    if ( AUITextHorzAlign::kLeft == hAlign )
    {
        for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
        {
            arrStartPos[idx].fX = textArea.left();
        }
    }
    else if ( AUITextHorzAlign::kCenter == hAlign )
    {
        for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
        {
            SkRect bound;
            AUISkiaUtil::MeasureTextBound( arrTexts[idx], bound, false, paint );
            arrStartPos[idx].fX = textArea.left() + textArea.width() * 0.5f - ( bound.left() + bound.right() ) * 0.5f;
        }
    }
    else if ( AUITextHorzAlign::kRight == hAlign )
    {
        for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
        {
            SkRect bound;
            AUISkiaUtil::MeasureTextBound( arrTexts[idx], bound, false, paint );
            arrStartPos[idx].fX = textArea.right() - bound.right();
        }
    }
    else
    {
        AUIAssertFailReason("Corrupted enum value");
    }

    return arrStartPos;
}

size_t AUISkiaUtil::BreakText( const std::wstring& text, bool useTrailingSpace, SkScalar maxWidth, SkScalar* measuredWidth, const SkPaint& paint )
{
    // TODO : Re-implement measurement using shaping library (e.g. Harfbuzz)
    
    auto wtext = text;
    static const auto DummyText = std::wstring( L"." );
    if ( useTrailingSpace )
        wtext += DummyText;
    
    const auto textWidth = SkFont().measureText(wtext.c_str(), wtext.length() * sizeof(std::wstring::value_type), GetWideCharTextEncoding());
    auto averageCharacterWidth = textWidth / static_cast<SkScalar>(wtext.length());
    size_t possibleCharCount = 0;
    if (SkScalarNearlyZero(averageCharacterWidth)) {
        possibleCharCount = wtext.length();
    } else {
        possibleCharCount = static_cast<size_t>(maxWidth / averageCharacterWidth);
    }
    if (measuredWidth)
        *measuredWidth = textWidth;
    if ( useTrailingSpace )
    {
        if ( possibleCharCount >= wtext.size() )
            possibleCharCount = wtext.size() - 1;
        if (measuredWidth)
            *measuredWidth = textWidth - averageCharacterWidth;
    }
    return possibleCharCount;
}

size_t AUISkiaUtil::BreakText( const std::wstring& text, bool useTrailingSpace, SkScalar maxWidth, const SkPaint& paint )
{
    return AUISkiaUtil::BreakText( text, useTrailingSpace, maxWidth, nullptr, paint );
}
