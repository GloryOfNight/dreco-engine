#pragma once

namespace dreco
{
class engine;

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

private:
	engine* game_engine = nullptr;
};
}	// namespace dreco