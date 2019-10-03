#include "game_base.hxx"

#include "camera_base.hxx"
#include "core/engine.hxx"
#include "game_world.hxx"

using namespace dreco;

game_base::game_base(engine& _e)
{
	game_engine = &_e;
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
}

engine* game_base::GetEngine() const
{
	return game_engine;
}

void game_base::OnWindowResize()
{
	game_world* world = GetCurrentWorld();
	if (world)
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