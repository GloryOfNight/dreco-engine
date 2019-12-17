#include "game_objects/mesh_object.hxx"

class gem : public dreco::mesh_object
{
    public:
	gem(const dreco::vertex_properties& _v, const dreco::shader_properties& _shader_prop);
};