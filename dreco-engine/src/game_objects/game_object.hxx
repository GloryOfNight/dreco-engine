#pragma once
#include "math/transform.hxx"

namespace dreco
{
class game_object
{
public:
	game_object() = default;

    virtual void Init();

    virtual void Tick(const float& DeltaTime);

    transform GetObjectTransform();

    void SetObjectTransform(transform& _t);
private:
    transform object_transform = transform();
};
}	// namespace dreco