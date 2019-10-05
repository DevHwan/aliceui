#pragma once

#include "AUISkiaConfig.h"

#include <string>

//////////////////////////////////////////////////////////////////////////
// Galleria - Image cache data module
class AUIGalleriaCache final
{
public:
    AUIGalleriaCache();
    ~AUIGalleriaCache();


    //////////////////////////////////////////////////////////////////////////
    // Cached Data
public:
    bool Has(const std::wstring& key) const;
    sk_sp<SkImage> Get(const std::wstring& key) const;
    sk_sp<SkImage> GetCopy(const std::wstring& key) const;
    void Set(const std::wstring& key, const sk_sp<SkImage>& pImage);
    void ClearKeyPrefix(const std::wstring& keyPrefix);
    void ClearAll();


    // Statistics
public:
    std::wstring GetStatistics() const;
    
private:
    mutable std::mutex m_mtxKey2Image;
    std::unordered_map<std::wstring, sk_sp<SkImage>> m_mapKey2Image;

};
