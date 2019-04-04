#include "pch.h"
#include "AUILocaleImpl.h"

AUILocale::Impl::Impl(const Impl& other)
{
    CopyFrom(other);
}

AUILocale::Impl& AUILocale::Impl::operator=(const Impl& other)
{
    CopyFrom(other);
    return *this;
}

void AUILocale::Impl::CopyFrom(const Impl& other)
{
    RefLocale() = other.RefLocale();
}
