#include "pch.h"
#include "AUICanvasHelper.h"
#include "AUISkiaUtil.h"
#include "AUINinePatch.h"

constexpr bool IsWideCharUTF16() {
    return 2 == sizeof(std::wstring::value_type);
}
constexpr SkTextEncoding GetWideCharTextEncoding() {
    return IsWideCharUTF16() ? SkTextEncoding::kUTF16 : SkTextEncoding::kUTF32;
}

AUICanvasHelper::AUICanvasHelper( SkCanvas* const pCanvas )
    : m_pCanvas( pCanvas )
{
    AUIAssert( GetCanvas() );
}

AUICanvasHelper::~AUICanvasHelper()
{

}

void AUICanvasHelper::drawText( const std::wstring& text, SkScalar x, SkScalar y, const SkPaint& paint )
{
    if constexpr (IsWideCharUTF16()) {
        GetCanvas()->drawSimpleText(text.c_str(), text.length() * sizeof(std::wstring::value_type), SkTextEncoding::kUTF16, x, y, SkFont(), paint);
    } else {
        GetCanvas()->drawSimpleText(text.c_str(), text.length() * sizeof(std::wstring::value_type), SkTextEncoding::kUTF32, x, y, SkFont(), paint);
    }
}

void AUICanvasHelper::drawText(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint )
{
    const auto p = AUISkiaUtil::CalcTextStartPos( text, textArea, vAlign, hAlign, false, paint );
    drawText( text, p.x(), p.y(), paint );
}

void AUICanvasHelper::drawText(const std::wstring& text, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, bool useTrailingSpace, const SkPaint& paint)
{
    const auto p = AUISkiaUtil::CalcTextStartPos( text, textArea, vAlign, hAlign, useTrailingSpace, paint );
    drawText( text, p.x(), p.y(), paint );
}

void AUICanvasHelper::drawPosText( const std::wstring& text, const SkPoint pos[], const SkPaint& paint )
{
    const auto pTextBlob = SkTextBlob::MakeFromPosText(text.c_str(), text.length() * sizeof(std::wstring::value_type), pos, SkFont(), GetWideCharTextEncoding());
    GetCanvas()->drawTextBlob(pTextBlob, 0.0f, 0.0f, paint);
}

void AUICanvasHelper::drawPosTextH( const std::wstring& text, const SkScalar xpos[], SkScalar constY, const SkPaint& paint )
{
    const auto pTextBlob = SkTextBlob::MakeFromPosTextH(text.c_str(), text.length() * sizeof(std::wstring::value_type), xpos, constY, SkFont(), GetWideCharTextEncoding());
    GetCanvas()->drawTextBlob(pTextBlob, 0.0f, 0.0f, paint);
}

void AUICanvasHelper::drawNinePatch( const AUINinePatch& ninepatch, const SkRect& rect, const SkPaint* paint /*= nullptr */)
{
    GetCanvas()->drawImageNine( ninepatch, ninepatch.GetCenter(), rect, paint );
}

void AUICanvasHelper::drawMultilineText( const std::vector< std::wstring >& arrTexts, const SkRect& textArea, AUITextVertAlign vAlign, AUITextHorzAlign hAlign, const SkPaint& paint, const SkScalar lineHeight)
{
    const auto arrPos = AUISkiaUtil::CalcTextStartPos(arrTexts, textArea, vAlign, hAlign, paint, lineHeight);
    
    AUIAssert( arrPos.size() == arrTexts.size() );
    for ( auto idx = 0 ; idx < arrTexts.size() ; idx++ )
    {
        const auto text = arrTexts[idx];
        const auto pTextBlob = SkTextBlob::MakeFromText(text.c_str(), text.length() * sizeof(std::wstring::value_type), SkFont(), GetWideCharTextEncoding());
        GetCanvas()->drawTextBlob(pTextBlob, arrPos[idx].x(), arrPos[idx].y(), paint);
    }
}

void AUICanvasHelper::drawTextOnLine(const std::wstring& text, SkScalar x0, SkScalar y0, SkScalar x1, SkScalar y1, const SkPaint& paint)
{
    const auto _dx = x1 - x0;
    const auto _dy = y1 - y0;
    const auto _len = (std::sqrt)(_dx * _dx + _dy * _dy);
    const auto _scos = (_dx / _len);
    const auto _ssin = (_dy / _len);
    auto _tx = x0;
    auto _ty = y0;

    std::vector<SkRSXform> transforms(text.length(), { 0.0f, });

    AUIAssert(transforms.size() == text.length());
    for (size_t idx = 0; idx < text.length(); ++idx)
    {
        const auto _ch = text[idx];
        const auto _adv = SkFont().measureText(&_ch, sizeof(std::wstring::value_type), GetWideCharTextEncoding());
        transforms[idx] = SkRSXform::Make(_scos, _ssin, _tx, _ty);
        _tx += _adv * _scos;
        _ty += _adv * _ssin;
    }
    const auto pTextBlob = SkTextBlob::MakeFromRSXform(text.c_str(), text.length() * sizeof(std::wstring::value_type), transforms.data(), SkFont(), GetWideCharTextEncoding());
    GetCanvas()->drawTextBlob(pTextBlob, 0.0f, 0.0f, paint);
}

void AUICanvasHelper::drawTextOnLine(const std::wstring& text, SkPoint p0, SkPoint p1, const SkPaint& paint)
{
    this->drawTextOnLine(text, p0.fX, p0.fY, p1.fX, p1.fY, paint);
}
