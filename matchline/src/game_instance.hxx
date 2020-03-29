#pragma once
#ifdef __ANDROID__
#include "SDL.h"
#else
#include "SDL2/SDL.h"
#endif
#include "game_objects/game_base.hxx"
#include "game_objects/mesh_object.hxx"
#include "math/vectors.hxx"
#include "world.hxx"

#include <stdint.h>

class game_instance : public dreco::game_base
{
public:
	game_instance(dreco::engine& _e);
	~game_instance();

	void Tick(const float& DeltaTime) override;

	void event_MouseButton(const SDL_Event& _e);

	dreco::game_object* GetSelectedObject() const;

	bool GetIsMouseButtonDown() const;
private:
	dreco::game_object* selected_object = nullptr;	

	bool bMouseDown = false;
	
	dreco::vec2 LastMousePos;
};