#pragma once
#include "game_objects/game_base.hxx"
#include "math/vec2.hxx"

#include <stdint.h>

class game_instance : public dreco::game_base
{
public:
	game_instance(dreco::engine& _e);
	~game_instance();

	void Init() override;

	void Tick(const float& DeltaTime) override;

	void key_Up(uint32_t _e_type);
	void key_Down(uint32_t _e_type);
	void key_Left(uint32_t _e_type);
	void key_Right(uint32_t _e_type);
	void key_q(uint32_t _e_type);
	void key_e(uint32_t _e_type);

private:
	float rotation = 0.0f;
	dreco::vec2 translation = dreco::vec2();

	bool bGoUp = false;
	bool bGoDown = false;
	bool bGoLeft = false;
	bool bGoRight = false;

	bool bRotateForward = false;
	bool bRotateBackward = false;
};