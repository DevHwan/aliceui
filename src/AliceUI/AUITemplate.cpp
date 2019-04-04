#include "pch.h"
#include "AUITemplate.h"

AUITemplate::AUITemplate()
{

}

AUITemplate::~AUITemplate()
{

}

std::shared_ptr< AUIWidget > AUITemplate::CreateWidget()
{
    return OnCreateWidget();
}

void AUITemplate::UpdateParam( AUIWidget* const pRoot, const AUITemplParam& param )
{
    OnUpdateParam( pRoot, param );
}

void AUITemplate::UpdateInsert( AUIWidget* const pRoot, const AUITemplInput& input )
{
    OnUpdateInsert( pRoot, input );
}

void AUITemplate::UpdateRemove( AUIWidget* const pRoot, const AUITemplInput& input )
{
    OnUpdateRemove( pRoot, input );
}

void AUITemplate::UpdateClear( AUIWidget* const pRoot, const AUITemplInput& input )
{
    OnUpdateClear( pRoot, input );
}
