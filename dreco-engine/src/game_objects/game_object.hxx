#pragma once
#include "game_world.hxx"
#include "math/transform.hxx"

namespace dreco
{
class game_object
{
public:
	game_object(game_world* _w);

	virtual ~game_object();

	virtual void Begin();

	virtual void Tick(const float& DeltaTime);

	transform GetTransform() const;

	virtual void SetTransform(const transform& _t);

	game_world* GetWorld() const;

	game_base* GetGameInstance() const;

	bool GetIsBegined() const;

protected:
	transform object_transform;

private:
	bool IsBegined;

	game_world* world;
};
}	// namespace dreco