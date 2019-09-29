#pragma once

namespace dreco
{
class engine;

class game_world;

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
private:
	engine* game_engine = nullptr;

	game_world* current_world = nullptr;
};
}	// namespace dreco