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

	void key_Up(uint32_t _e_type);
	void key_Down(uint32_t _e_type);
	void key_Left(uint32_t _e_type);
	void key_Right(uint32_t _e_type);
	void key_q(uint32_t _e_type);
	void key_e(uint32_t _e_type);
	void key_r(uint32_t _e);
	void key_t(uint32_t _e);

	void key_1(uint32_t _e_type);
	void key_2(uint32_t _e_type);
	void key_3(uint32_t _e_type);

private:
	dreco::game_object* selected_object = nullptr;
	dreco::vec2 selection_offset = dreco::vec2();

	bool bMouseDown = false;
	dreco::vec2 LastMousePos;

	bool bGoUp = false;
	bool bGoDown = false;
	bool bGoLeft = false;
	bool bGoRight = false;

	bool bRotateForward = false;
	bool bRotateBackward = false;

	bool bScaleUp = false; 
	bool bScaleDown = false;
};