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

    void SetObjectTransform(transform& _t);

private:
    game_world* world = nullptr;
    transform object_transform = transform();
};
}	// namespace dreco