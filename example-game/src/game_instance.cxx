#include "game_instance.hxx"

#include "core/engine.hxx"
#include "core/sdl_event_manager.hxx"
#include "math/mat2x3.hxx"
#include "renderer/vertex.hxx"
#include "renderer/shader_properties.hxx"
#include "utils/file_utils.hxx"

#include <vector>

game_instance::game_instance(dreco::engine& _e) : game_base(_e)
{
}

game_instance::~game_instance()
{
	delete sample_mesh;
}

void game_instance::Init()
{
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_UP, std::bind(&game_instance::key_Up, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_DOWN, std::bind(&game_instance::key_Down, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_LEFT, std::bind(&game_instance::key_Left, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_RIGHT, std::bind(&game_instance::key_Right, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_q, std::bind(&game_instance::key_q, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_e, std::bind(&game_instance::key_e, this, std::placeholders::_1));

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
	
	sample_mesh = new dreco::mesh_object(verts, p);	
}

void game_instance::Tick(const float& DeltaTime)
{
	using namespace dreco;

	transform t = sample_mesh->GetObjectTransform();
	if (bGoUp)
	{
		t.translation.y += 1 * DeltaTime;
	}
	else if (bGoDown)
	{
		t.translation.y -= 1 * DeltaTime;
	}
	if (bGoLeft)
	{
		t.translation.x -= 1 * DeltaTime;
	}
	else if (bGoRight)
	{
		t.translation.x += 1 * DeltaTime;
	}
	if (bRotateForward)
	{
		t.rotation += 0.5f * DeltaTime;
	}
	else if (bRotateBackward)
	{
		t.rotation -= 0.5f * DeltaTime;
	}

	sample_mesh->SetObjectTransform(t);
	sample_mesh->Tick(DeltaTime);
}

void game_instance::key_Up(uint32_t _e_type)
{
	bGoUp = _e_type == SDL_KEYDOWN ? true : false;
}

void game_instance::key_Down(uint32_t _e_type)
{
	bGoDown = _e_type == SDL_KEYDOWN ? true : false;
}

void game_instance::key_Left(uint32_t _e_type)
{
	bGoLeft = _e_type == SDL_KEYDOWN ? true : false;
}

void game_instance::key_Right(uint32_t _e_type)
{
	bGoRight = _e_type == SDL_KEYDOWN ? true : false;
}

void game_instance::key_q(uint32_t _e_type)
{
	bRotateBackward = _e_type == SDL_KEYDOWN ? true : false;
}

void game_instance::key_e(uint32_t _e_type)
{
	bRotateForward = _e_type == SDL_KEYDOWN ? true : false;
}