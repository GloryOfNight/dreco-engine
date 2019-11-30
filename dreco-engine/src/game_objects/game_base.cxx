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

vec2 game_base::GetWindowSize() const 
{
	int x;
	int y;
	SDL_GetWindowSize(game_engine->GetWindow(), &x, &y);
	return vec2(x, y);
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
	vec2 window_size = GetWindowSize();
	auto projection_mat = GetCurrentWorld()->GetPlayerCamera()->GetProjectionMatrix();
	
	mat2x3 pm2x3 = mat2x3::identiry();
	// convert 3x4 mat to 2x3;
	pm2x3.mat[0][0] = projection_mat.mat[0][0];
	pm2x3.mat[0][1] = projection_mat.mat[0][1];
	pm2x3.mat[0][2] = projection_mat.mat[0][2];
	pm2x3.mat[1][0] = projection_mat.mat[1][0];
	pm2x3.mat[1][1] = projection_mat.mat[1][1];
	pm2x3.mat[1][2] = projection_mat.mat[1][2];

	return opengles2_renderer::UnProject(_screen_coor, window_size,
	 GetCurrentWorld()->GetPlayerCamera()->GetViewMatrix(),
	  pm2x3);
}