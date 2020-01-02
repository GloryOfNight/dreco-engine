#pragma once
#include "SDL2/SDL.h"
#include "game_objects/game_base.hxx"
#include "game_objects/mesh_object.hxx"
#include "math/vec2.hxx"
#include "world.hxx"

#include <stdint.h>

class game_instance : public dreco::game_base
{
public:
	game_instance(dreco::engine& _e);
	~game_instance();

	void Init() override;

	void Tick(const float& DeltaTime) override;

	void event_MouseButton(const SDL_Event& _e);

	dreco::game_object* GetSelectedObject() const;

	bool GetIsMouseButtonDown() const;
private:
	dreco::game_object* selected_object = nullptr;	

	bool bMouseDown = false;
	dreco::vec2 LastMousePos;
};