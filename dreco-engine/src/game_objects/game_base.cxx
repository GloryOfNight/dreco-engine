#include "game_base.hxx"

#include "camera_base.hxx"
#include "core/engine.hxx"
#include "game_objects/game_object.hxx"
#include "game_objects/game_world.hxx"
#include "game_objects/mesh_object.hxx"
#include "utils/math_utils.hxx"

using namespace dreco;

game_base::game_base(engine& _e) : game_engine(&_e)
{
}

game_base::~game_base()
{
	if (current_world)
		delete current_world;
}

void game_base::Init()
{
}

void game_base::Tick(const float& DeltaTime)
{
	if (current_world)
	{
		current_world->Tick(DeltaTime);
	}
}

engine* game_base::GetEngine() const
{
	return game_engine;
}

void game_base::OnWindowResize()
{
	if (const game_world* world = GetCurrentWorld(); world)
	{
		world->GetPlayerCamera()->OnScreenSizeUpdate();
	}
}

void game_base::GetViewSize(int& _w, int& _h) const
{
	SDL_GetWindowSize(GetEngine()->GetWindow(), &_w, &_h);
}

game_world* game_base::GetCurrentWorld() const
{
	return current_world;
}

void game_base::SetCurrentWorld(game_world* _w)
{
	current_world = _w;
}

vec2 game_base::GetWindowSize() const
{
	int x;
	int y;
	SDL_GetWindowSize(game_engine->GetWindow(), &x, &y);
	return vec2(x, y);
}

bool game_base::IsWindowInFocus() const
{
	return SDL_GetMouseFocus() == game_engine->GetWindow();
}

vec2 game_base::GetMouseScreenPos() const
{
	int x;
	int y;
	SDL_GetMouseState(&x, &y);
	return vec2(x, y);
}

vec2 game_base::ScreenToWorld(const vec2& _screen_coor) const
{
	const vec2 window_size = GetWindowSize();
	const mat2x3 proj_mat = GetCurrentWorld()->GetPlayerCamera()->GetProjectionMatrix();

	return math_utils::UnProject(_screen_coor, window_size,
		GetCurrentWorld()->GetPlayerCamera()->GetViewMatrix(), proj_mat);
}

game_object* game_base::TryGetObectFromScreen(const vec2& _coor)
{
	const uint8_t stencil_index =
		game_engine->GetRenderer()->GetColorIndexFromPixel(_coor);

	if (stencil_index != 0 && current_world)
	{
		const auto objects = current_world->GetWorldObjectsRef();
		for (auto obj : objects)
		{
			mesh_object* mesh = dynamic_cast<mesh_object*>(obj.second);
			if (mesh && mesh->GetObjectIndex() == stencil_index)
			{
				return mesh;
			}
		}
	}

	return nullptr;
}

resource_manager* game_base::GetResourceManager() const
{
	return GetEngine()->GetResourceManager();
}

audio_manager* game_base::GetAudioManager() const 
{
	return GetEngine()->GetAudioManager();
}