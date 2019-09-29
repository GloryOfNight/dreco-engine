#pragma once
#include "world.hxx"
#include "game_objects/game_base.hxx"
#include "math/vec2.hxx"
#include "game_objects/mesh_object.hxx"
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

	void key_1(uint32_t _e_type);
	void key_2(uint32_t _e_type);
	void key_3(uint32_t _e_type);
	
	virtual void OnWindowResize() override;

private:	
	std::string selected_object = "1";
	
	world* game_world = nullptr;

	bool bGoUp = false;
	bool bGoDown = false;
	bool bGoLeft = false;
	bool bGoRight = false;

	bool bRotateForward = false;
	bool bRotateBackward = false;
};