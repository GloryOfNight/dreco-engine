#include "game_base.hxx"

#include "../core/engine.hxx"

using namespace dreco;

game_base::game_base(engine& _e)
{
	game_engine = &_e;
}

game_base::~game_base()
{
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
}

void game_base::GetViewSize(int& _w, int& _h) const
{
	SDL_GetWindowSize(GetEngine()->GetWindow(), &_w, &_h);
}