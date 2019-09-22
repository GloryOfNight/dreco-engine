#include "game_instance.hxx"

#include "core/engine.hxx"
#include "core/sdl_event_manager.hxx"
#include "math/mat2x3.hxx"
#include "renderer/vertex.hxx"

#include <vector>

game_instance::game_instance(dreco::engine& _e) : game_base(_e)
{
}

game_instance::~game_instance()
{
}

void game_instance::Init() 
{
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_UP, std::bind(&game_instance::key_Up, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_DOWN, std::bind(&game_instance::key_Down, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_LEFT, std::bind(&game_instance::key_Left, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_RIGHT, std::bind(&game_instance::key_Right, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_q, std::bind(&game_instance::key_q, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(SDLK_e, std::bind(&game_instance::key_e, this, std::placeholders::_1));
}

void game_instance::Tick(const float& DeltaTime)
{
	using namespace dreco;

	std::vector<vertex> vertexes = {};
	vertexes.reserve(3);

	vertexes.push_back(vertex(-0.5f, 0.5f, 0.0f));
	vertexes.push_back(vertex(-0.5f, 0.0f, 0.0f));
	vertexes.push_back(vertex(0.5f, 0.0f, 0.0f));

	vertexes.push_back(vertex(0.5f, 0.5f, 0.0f));
	vertexes.push_back(vertex(-0.5f, 0.5f, 0.0f));
	vertexes.push_back(vertex(0.5f, 0.0f, 0.0f));


	if (bGoUp) 
	{
		translation.y += 1 * DeltaTime;
	}
	if (bGoDown) 
	{
		translation.y -= 1 * DeltaTime;
	}
	if (bGoLeft) 
	{
		translation.x -= 1 * DeltaTime;
	}
	if (bGoRight) 
	{
		translation.x += 1 * DeltaTime;
	}
	if (bRotateForward) 
	{
		rotation += 0.5 * DeltaTime;
	}
	if (bRotateBackward) 
	{
		rotation -= 0.5 * DeltaTime;
	}
	const mat2x3 m_t = mat2x3::translate(translation);
	const mat2x3 m_r = mat2x3::rotate(rotation);
	const mat2x3 m_s = mat2x3::scale(1.0f, 1.0f);

	const mat2x3 m_f = m_r * m_t * m_s;

	GetEngine()->GetRenderer()->DrawVertexArray(vertexes, m_f);
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