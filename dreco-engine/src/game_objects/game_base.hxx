#pragma once

namespace dreco
{
class engine;

class game_base
{
public:
	game_base(engine& engine_based_on);

	virtual void Init();

	virtual void Tick(const float& DeltaTime);

	engine* GetEngine() const;

private:
	engine* game_engine = nullptr;
};
}	// namespace dreco