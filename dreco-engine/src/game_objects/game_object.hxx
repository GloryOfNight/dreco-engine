#pragma once

namespace dreco
{
class game_object
{
public:
	game_object() = default;

    virtual void Init();

    virtual void Tick(const float& DeltaTime);
};
}	// namespace dreco