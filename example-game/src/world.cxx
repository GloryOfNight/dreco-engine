#include "world.hxx"
#include "game_objects/mesh_object.hxx"
#include "utils/file_utils.hxx"

void world::Init() 
{
    const auto vert_src = dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.vert");
	const auto frag_src = dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.frag");

	const dreco::glShaderAtributes s_attr = {{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}};

	dreco::shader_properties p = dreco::shader_properties(vert_src.c_str(), frag_src.c_str(), s_attr);

	std::vector<float> verts = 
	{
		-0.5f, 0.5f, 0.0f, 
		-0.5f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.0f,
		0.5f, 0.5f, 0.0f,
		-0.5f, 0.5f, 0.0f,
		0.5f, 0.0f, 0.0f
	};
	
	dreco::mesh_object* obj = new dreco::mesh_object(verts, p);	
    RegisterObject("1", *obj);
    obj = new dreco::mesh_object(verts, p);	
    RegisterObject("2", *obj);
    obj = new dreco::mesh_object(verts, p);	
    RegisterObject("3", *obj);
}