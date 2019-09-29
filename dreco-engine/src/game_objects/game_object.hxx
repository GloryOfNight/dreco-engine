#pragma once
#include "game_world.hxx"
#include "math/transform.hxx"

namespace dreco
{
class game_object
{
public:
	game_object() = default;

	virtual void Init(game_world& _w);

	virtual void Tick(const float& DeltaTime);

	transform GetObjectTransform() const;

	virtual void SetObjectTransform(const transform& _t);

	game_world* GetWorld() const;

	game_base* GetGameInstance() const;

protected:
	transform object_transform = transform();

private:
	game_world* world = nullptr;
};
}	// namespace dreco