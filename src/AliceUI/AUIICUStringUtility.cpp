#include "pch.h"
#include "AUIICUStringUtility.h"
#include "AUIStringConvert.h"

namespace
{
    const char* GetPlatformTextEncoding()
    {
#ifdef _WIN32
        return "UTF-16LE";  // wchar_t == UTF-16
#else
        return "UTF-32LE";  // wchar_t == UTF-32
#endif
    }

    template< typename _CharType >
    void ConvertStringT( UConverter* pConverter, icu::UnicodeString& out, const _CharType* pStr, const size_t len )
    {
        if ( len == 0 )
        {
            out.remove();
            return;
        }

        UErrorCode err = U_ZERO_ERROR;
        ucnv_reset( pConverter );

        // Buffer with offset
        const auto _BufferSize = static_cast< int32_t >( len * 2 );
        const auto pOutBuf = out.getBuffer( _BufferSize );

        // Input size in bytes
        const auto strSizeInBytes = static_cast<int32_t>( len * sizeof( _CharType ) );

        // Fill buffer
        const auto outLengh = ucnv_toUChars( pConverter, pOutBuf, _BufferSize, reinterpret_cast<const char*>( pStr ), strSizeInBytes, &err );
        pOutBuf[outLengh] = '\0';
        AUIAssert( U_SUCCESS( err ) );

        // Shrink buffer
        out.releaseBuffer( outLengh );
        AUIAssert( outLengh == out.length() );
    }

    void ConvertString( UConverter* pConverter, std::wstring& out, const icu::UnicodeString& in )
    {
        typedef std::wstring _targetstring;
        const auto inLength = in.length();
        if ( 0 == inLength )
        {
            out.clear();
            return;
        }

        UErrorCode err = U_ZERO_ERROR;
        ucnv_reset( pConverter );

        // Calc text size
        const auto outCapacitySizeInBytes = UCNV_GET_MAX_BYTES_FOR_STRING( inLength, ucnv_getMaxCharSize( pConverter ) );
        const auto outCapacitySizeInValueType = outCapacitySizeInBytes / sizeof( _targetstring::value_type );

        // Allocate buffer
        out.resize( outCapacitySizeInValueType );

        const auto outSizeInBytes = ucnv_fromUChars( pConverter,
            reinterpret_cast<char*>( const_cast<_targetstring::value_type*>( out.data() ) ), outCapacitySizeInBytes,
            in.getBuffer(), inLength, &err );
        const auto outSizeInValueType = outSizeInBytes / sizeof( _targetstring::value_type );
        out.at( outSizeInValueType ) = L'0';
        AUIAssert( U_SUCCESS( err ) );

        // Shrink buffer
        out.resize( outSizeInValueType );
    }

    void ConvertString( UConverter* pConverter, std::string& out, const icu::UnicodeString& in )
    {
        typedef std::string _targetstring;
        const auto inLength = in.length();
        if ( 0 == inLength )
        {
            out.clear();
            return;
        }

        UErrorCode err = U_ZERO_ERROR;
        ucnv_reset( pConverter );

        // Calc text size
        const auto outCapacitySizeInBytes = UCNV_GET_MAX_BYTES_FOR_STRING( inLength, ucnv_getMaxCharSize( pConverter ) );
        const auto outCapacitySizeInValueType = outCapacitySizeInBytes / sizeof( _targetstring::value_type );

        // Allocate buffer
        out.resize( outCapacitySizeInValueType );

        const auto outSizeInBytes = ucnv_fromUChars( pConverter,
            reinterpret_cast<char*>( const_cast<_targetstring::value_type*>( out.data() ) ), outCapacitySizeInBytes,
            in.getBuffer(), inLength, &err );
        const auto outSizeInValueType = outSizeInBytes / sizeof( _targetstring::value_type );
        out.at( outSizeInValueType ) = L'0';
        AUIAssert( U_SUCCESS( err ) );

        // Shrink buffer
        out.resize( outSizeInValueType );
    }

    //////////////////////////////////////////////////////////////////////////
    // Converter
    class ConverterImpl final
    {
    public:
        ConverterImpl()
        {
            UErrorCode err = U_ZERO_ERROR;
            m_pConverter = std::unique_ptr< UConverter, std::function< void( UConverter* ) > >( ucnv_open( GetPlatformTextEncoding(), &err ), ucnv_close );
            AUIAssert( m_pConverter );
            AUIAssert( U_SUCCESS( err ) );
        }
        ~ConverterImpl()
        {

        }
    public:
        void CvtStr( icu::UnicodeString& out, const wchar_t* pIn, const size_t len )
        {
            auto inLen = len;
            if ( inLen == AUIICUNullTerm )
            {
                inLen = wcslen( pIn );
            }
            AUIAssert(AUIICUNullTerm != inLen );
            ConvertStringT< wchar_t >( GetConverter(), out, pIn, inLen );
        }
        void CvtStr( icu::UnicodeString& out, const char* pIn, const size_t len )
        {
            auto inLen = len;
            if ( inLen == AUIICUNullTerm)
            {
                inLen = strlen( pIn );
            }
            AUIAssert(AUIICUNullTerm != inLen );
            ConvertStringT< char >( GetConverter(), out, pIn, inLen );
        }
        void CvtStr( icu::UnicodeString& out, const std::wstring& in )
        {
            ConvertStringT< std::wstring::value_type >( GetConverter(), out, in.c_str(), in.length() );
        }
        void CvtStr( icu::UnicodeString& out, const std::string& in )
        {
            ConvertStringT< std::string::value_type >( GetConverter(), out, in.c_str(), in.length() );
        }
        void CvtStr( std::wstring& out, const icu::UnicodeString& in )
        {
            ConvertString( GetConverter(), out, in );
        }
        void CvtStr( std::string& out, const icu::UnicodeString& in )
        {
            ConvertString( GetConverter(), out, in );
        }
    private:
        UConverter * GetConverter() const { AUIAssert( m_pConverter ); return m_pConverter.get(); }
        std::unique_ptr< UConverter, std::function< void( UConverter* ) > > m_pConverter;
    };
}

icu::UnicodeString AUIICUStringUtility::CvtToUStr( const std::wstring& in )
{
    icu::UnicodeString out;
    ConverterImpl converter;
    converter.CvtStr( out, in );
    return out;
}

icu::UnicodeString AUIICUStringUtility::CvtToUStr( const std::string& in )
{
    icu::UnicodeString out;
    ConverterImpl converter;
    converter.CvtStr( out, in );
    return out;
}

icu::UnicodeString AUIICUStringUtility::CvtToUStr( const char* pIn, const size_t len /*= AUINullTerm */ )
{
    icu::UnicodeString out;
    ConverterImpl converter;
    converter.CvtStr( out, pIn, len );
    return out;
}

icu::UnicodeString AUIICUStringUtility::CvtToUStr( const wchar_t* pIn, const size_t len /*= AUINullTerm */ )
{
    icu::UnicodeString out;
    ConverterImpl converter;
    converter.CvtStr( out, pIn, len );
    return out;
}

std::wstring AUIICUStringUtility::CvtToWStr( const icu::UnicodeString& in )
{
    std::wstring out;
    ConverterImpl converter;
    converter.CvtStr( out, in );
    return out;
}

std::wstring AUIICUStringUtility::CvtToWStr( const std::string& in )
{
    return AUIStringConvert::ACPToWCS(in);
}

std::wstring AUIICUStringUtility::CvtToWStr( const char* in)
{
    return AUIStringConvert::ACPToWCS(in);
}

std::string AUIICUStringUtility::CvtToStr( const wchar_t* in )
{
    return AUIStringConvert::WCSToACP(in);
}

std::string AUIICUStringUtility::CvtToStr( const std::wstring& in )
{
    return AUIStringConvert::WCSToACP(in);
}

std::string AUIICUStringUtility::CvtToStr( const icu::UnicodeString& in )
{
    std::string out;
    ConverterImpl converter;
    converter.CvtStr( out, in );
    return out;
}
