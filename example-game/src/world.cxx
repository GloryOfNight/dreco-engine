#include "world.hxx"

#include "game_objects/camera_base.hxx"
#include "game_objects/mesh_object.hxx"
#include "utils/file_utils.hxx"

#include <memory>

void world::Init()
{
	game_world::Init();

	const auto vert_src =
		dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.vert");
	const auto frag_src =
		dreco::file_utils::LoadSourceFromFile("res/shaders/default_shader.frag");

	const dreco::glShaderAtributes s_attr = {
		{0, "a_position"}, {1, "a_color"}, {2, "a_tex_coord"}};

	const dreco::shader_properties shader_prop =
		dreco::shader_properties(vert_src.c_str(), frag_src.c_str(), s_attr);

	// clang-format off
	std::vector<float> verts = 
	{
		-0.25f, 0.5f, 0.0f, 
		-0.25f, 0.0f, 0.0f,
		0.25f, 0.0f, 0.0f,
		0.25f, 0.5f, 0.0f,
		-0.25f, 0.5f, 0.0f,
		0.25f, 0.0f, 0.0f
	};


	dreco::vertex_properties vert_prop;
	vert_prop.vertexes = verts;
	vert_prop.texture_coords = { 0.0, 1.0,
								0.0, 0.0,
								1.0, 0.0,

								1.0, 1.0,
								0.0, 1.0,
								1.0, 0.0,
								};
	// clang-format on

	vert_prop.texture_ptr =
		std::make_shared<dreco::texture>(*(new dreco::texture("res/textures/tank.png")));

	dreco::mesh_object* obj = new dreco::mesh_object(vert_prop, shader_prop);
	RegisterObject("1", *obj);

	vert_prop.texture_ptr =
		std::make_shared<dreco::texture>(*(new dreco::texture("res/textures/tank1.png")));

	obj = new dreco::mesh_object(vert_prop, shader_prop);
	RegisterObject("2", *obj);

	obj = new dreco::mesh_object(vert_prop, shader_prop);
	RegisterObject("3", *obj);
}

void world::Tick(const float& DeltaTime)
{
	game_world::Tick(DeltaTime);

	// auto t = GetPlayerCamera()->GetObjectTransform();

	// t.translation.y -= 0.1 *DeltaTime;

	// GetPlayerCamera()->SetObjectTransform(t);
}