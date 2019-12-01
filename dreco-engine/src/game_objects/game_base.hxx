#pragma once
#include "math/vec2.hxx"

namespace dreco
{
class engine;

class game_world;

class game_object;

class game_base
{
public:
	game_base(engine& _e);

	virtual ~game_base();

	virtual void Init();

	virtual void Tick(const float& DeltaTime);

	engine* GetEngine() const;

	virtual void OnWindowResize();

	void GetViewSize(int& _w, int& _h) const;

	game_world* GetCurrentWorld() const;

	void SetCurrentWorld(game_world* _w);

	vec2 GetWindowSize() const;

	bool IsWindowInFocus() const;

	vec2 GetMouseScreenPos() const;
	
	vec2 ScreenToWorld(const vec2& _screen_coor) const;

	game_object* TryGetObectFromScreen(const vec2& _coor);

private:
	engine* game_engine = nullptr;

	game_world* current_world = nullptr;
};
}	// namespace dreco