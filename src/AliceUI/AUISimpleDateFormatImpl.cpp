#include "pch.h"
#include "AUISimpleDateFormatImpl.h"

AUISimpleDateFormat::Impl::Impl(const std::wstring& pattern)
{
    UErrorCode errCode(U_ZERO_ERROR);
    m_pDateFormat = std::unique_ptr<icu::SimpleDateFormat>(new icu::SimpleDateFormat(AUIICUStringUtility::CvtToUStr(pattern), errCode));
    assert(U_SUCCESS(errCode));
    assert(m_pDateFormat);
}

AUISimpleDateFormat::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

AUISimpleDateFormat::Impl& AUISimpleDateFormat::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void AUISimpleDateFormat::Impl::CopyFrom(const Impl& other)
{
    assert(m_pDateFormat);
    *GetDF() = *other.GetDF();
}
