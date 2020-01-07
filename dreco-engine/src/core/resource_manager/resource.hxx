#pragma once
#include "resource_type.hxx"

namespace dreco
{
class resource
{
public:
	resource(const resource_type& _t);
	virtual ~resource();

	const resource_type type;

	bool GetIsResourceLoaded() const;
protected:
	bool is_resource_loaded = false;
};
}	 // namespace dreco