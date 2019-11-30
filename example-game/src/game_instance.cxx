#include "game_instance.hxx"

#include "core/engine.hxx"
#include "core/sdl_event_manager.hxx"
#include "game_objects/camera_base.hxx"
#include "math/mat2x3.hxx"
#include "renderer/shader_properties.hxx"
#include "renderer/vertex.hxx"
#include "utils/file_utils.hxx"

#include <vector>

game_instance::game_instance(dreco::engine& _e) : game_base(_e)
{
}

game_instance::~game_instance()
{
}

void game_instance::Init()
{
	GetEngine()->GetEventManager()->AddEventBinding(SDL_MOUSEBUTTONDOWN,
	 std::bind(&game_instance::event_MouseButton, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddEventBinding(SDL_MOUSEBUTTONUP,
	 std::bind(&game_instance::event_MouseButton, this, std::placeholders::_1));
	 
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_UP, std::bind(&game_instance::key_Up, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_DOWN, std::bind(&game_instance::key_Down, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_LEFT, std::bind(&game_instance::key_Left, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_RIGHT, std::bind(&game_instance::key_Right, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_q, std::bind(&game_instance::key_q, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_e, std::bind(&game_instance::key_e, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_r, std::bind(&game_instance::key_r, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_t, std::bind(&game_instance::key_t, this, std::placeholders::_1));

	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_1, std::bind(&game_instance::key_1, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_2, std::bind(&game_instance::key_2, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddKeyBinding(
		SDLK_3, std::bind(&game_instance::key_3, this, std::placeholders::_1));

	dreco::game_world* new_world = new world(*this);
	new_world->Init();

	SetCurrentWorld(new_world);
}

void game_instance::Tick(const float& DeltaTime)
{
	using namespace dreco;

	auto obj = GetCurrentWorld()->GetObject(selected_object);

	transform t = obj->GetObjectTransform();

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
	if (bScaleUp) 
	{
		t.scale += 0.5 * DeltaTime;
	}
	if (bScaleDown) 
	{
		t.scale -= 0.5 * DeltaTime;
	}

	if (bMouseDown && IsWindowInFocus()) 
	{
		vec2 mouse_screen_pos = GetMouseScreenPos();
		t.translation = ScreenToWorld(mouse_screen_pos);
	}

	obj->SetObjectTransform(t);

	GetCurrentWorld()->Tick(DeltaTime);
}

void game_instance::event_MouseButton(const SDL_Event& _e) 
{
	bMouseDown = _e.button.state == SDL_PRESSED ? true : false;
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

void game_instance::key_1(uint32_t _e_type)
{
	selected_object = "1";
}

void game_instance::key_2(uint32_t _e_type)
{
	selected_object = "2";
}

void game_instance::key_3(uint32_t _e_type)
{
	selected_object = "3";
}

void game_instance::key_r(uint32_t _e)
{
	bScaleDown = _e == SDL_KEYDOWN;
}

void game_instance::key_t(uint32_t _e)
{
	bScaleUp = _e == SDL_KEYDOWN;
}
