#pragma once

#include "AUIAPIDef.h"
#include <unordered_map>
#include <memory>

class AUITemplate;
class AUITemplateProcessor;
class ALICEUI_API AUITemplatePool : public std::enable_shared_from_this<AUITemplatePool>
{
public:
    AUITemplatePool();
    ~AUITemplatePool();

    //////////////////////////////////////////////////////////////////////////
    // Pool
public:
    void Clear();
    bool Insert(const std::wstring& tag, const std::shared_ptr< AUITemplate >& pTemplate);
    bool Remove(const std::wstring& tag);
    AUITemplate* GetTemplate(const std::wstring& tag) const;
    std::vector< std::wstring > GetTags() const;
    bool Has(const std::wstring& tag) const { return m_mapTag2Template.end() != m_mapTag2Template.find(tag); }
private:
    std::unordered_map< std::wstring, std::shared_ptr< AUITemplate > > m_mapTag2Template;
};

