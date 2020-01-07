#include "resource.hxx"

using namespace dreco;

resource::resource(const resource_type& _t) : type(_t)
{
}

resource::~resource()
{
}

bool resource::GetIsResourceLoaded() const 
{
    return is_resource_loaded;
}