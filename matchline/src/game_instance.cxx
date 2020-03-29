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
	GetEngine()->GetEventManager()->AddEventBinding(SDL_MOUSEBUTTONDOWN,
		std::bind(&game_instance::event_MouseButton, this, std::placeholders::_1));
	GetEngine()->GetEventManager()->AddEventBinding(SDL_MOUSEBUTTONUP,
		std::bind(&game_instance::event_MouseButton, this, std::placeholders::_1));

	dreco::game_world* new_world = new world(this);

	SetCurrentWorld(new_world);
}

game_instance::~game_instance()
{
}

void game_instance::Tick(const float& DeltaTime)
{
	game_base::Tick(DeltaTime);

	if (bMouseDown)
	{
		LastMousePos = GetMouseScreenPos();
		selected_object = TryGetObectFromScreen(LastMousePos);
	}
	else 
	{
		selected_object = nullptr;
	}
}

void game_instance::event_MouseButton(const SDL_Event& _e)
{
	bMouseDown = _e.button.state == SDL_PRESSED ? true : false;
}

dreco::game_object* game_instance::GetSelectedObject() const
{
	return selected_object;
}

bool game_instance::GetIsMouseButtonDown() const
{
	return bMouseDown;
}