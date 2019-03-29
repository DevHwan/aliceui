#include "pch.h"
#include "AUILocale.h"
#include "AUILocaleImpl.h"

AUILocale::AUILocale()
    : m_pImpl( new Impl() )
{
    this->SetDefault();
}

AUILocale::AUILocale( const AUILocale& other )
    : m_pImpl( new Impl() )
{
    *GetImpl() = *other.GetImpl();
}

AUILocale::AUILocale( AUILocale&& other ) noexcept
    : m_pImpl( std::move( other.m_pImpl ) )
{

}

AUILocale::~AUILocale()
{

}


void AUILocale::Set( const std::wstring& language, const std::wstring& country /*= L""*/, const std::wstring& variant /*= L""*/, const std::wstring& keywordAndValues /*= L"" */ )
{
    const auto utf8language = AUIICUStringUtility::CvtToStr( language );
    const auto utf8country = AUIICUStringUtility::CvtToStr( country );
    const auto utf8variant = AUIICUStringUtility::CvtToStr( variant );
    const auto utf8keywordAndValues = AUIICUStringUtility::CvtToStr( keywordAndValues );

    GetImpl()->RefLocale() = icu::Locale( utf8language.c_str(), utf8country.c_str(), utf8variant.c_str(), utf8keywordAndValues.c_str() );
}

void AUILocale::SetDefault()
{
    GetImpl()->RefLocale() = icu::Locale::getDefault();
}

void AUILocale::SetEnglish()
{
    GetImpl()->RefLocale() = icu::Locale::getEnglish();
}

void AUILocale::SetFrench()
{
    GetImpl()->RefLocale() = icu::Locale::getFrench();

}

void AUILocale::SetGerman()
{
    GetImpl()->RefLocale() = icu::Locale::getGerman();

}

void AUILocale::SetItalian()
{
    GetImpl()->RefLocale() = icu::Locale::getItalian();

}

void AUILocale::SetJapanese()
{
    GetImpl()->RefLocale() = icu::Locale::getJapanese();

}

void AUILocale::SetKorean()
{
    GetImpl()->RefLocale() = icu::Locale::getKorean();

}

void AUILocale::SetChinese()
{
    GetImpl()->RefLocale() = icu::Locale::getChinese();

}

void AUILocale::SetSimplifiedChinese()
{
    GetImpl()->RefLocale() = icu::Locale::getSimplifiedChinese();

}

void AUILocale::SetTraditionalChinese()
{
    GetImpl()->RefLocale() = icu::Locale::getTraditionalChinese();

}

void AUILocale::SetFrance()
{
    GetImpl()->RefLocale() = icu::Locale::getFrance();

}

void AUILocale::SetGermany()
{
    GetImpl()->RefLocale() = icu::Locale::getGermany();

}

void AUILocale::SetItaly()
{
    GetImpl()->RefLocale() = icu::Locale::getItaly();

}

void AUILocale::SetJapan()
{
    GetImpl()->RefLocale() = icu::Locale::getJapan();

}

void AUILocale::SetKorea()
{
    GetImpl()->RefLocale() = icu::Locale::getKorea();

}

void AUILocale::SetChina()
{
    GetImpl()->RefLocale() = icu::Locale::getChina();

}

void AUILocale::SetTaiwan()
{
    GetImpl()->RefLocale() = icu::Locale::getTaiwan();

}

void AUILocale::SetUK()
{
    GetImpl()->RefLocale() = icu::Locale::getUK();

}

void AUILocale::SetUS()
{
    GetImpl()->RefLocale() = icu::Locale::getUS();

}

void AUILocale::SetCanada()
{
    GetImpl()->RefLocale() = icu::Locale::getCanada();

}

void AUILocale::SetCanadaFrench()
{
    GetImpl()->RefLocale() = icu::Locale::getCanadaFrench();

}

std::wstring AUILocale::GetLanguage() const
{
    return AUIICUStringUtility::CvtToWStr( GetImpl()->RefLocale().getLanguage() );
}

std::wstring AUILocale::GetScript() const
{
    return AUIICUStringUtility::CvtToWStr( GetImpl()->RefLocale().getScript() );
}

std::wstring AUILocale::GetCountry() const
{

    return AUIICUStringUtility::CvtToWStr( GetImpl()->RefLocale().getCountry() );
}

std::wstring AUILocale::GetVariant() const
{

    return AUIICUStringUtility::CvtToWStr( GetImpl()->RefLocale().getVariant() );
}

bool AUILocale::IsScriptRightToLeft() const
{
    return !!GetImpl()->RefLocale().isRightToLeft();
}

bool AUILocale::IsEqual( const AUILocale& locale ) const
{
    return !!( GetImpl()->RefLocale() == locale.GetImpl()->RefLocale() );
}
