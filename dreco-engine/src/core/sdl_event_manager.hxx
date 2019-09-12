#pragma once
#include "SDL2/SDL.h"

#include <functional>
#include <map>
#include <string>

namespace dreco
{
typedef std::function<void(uint32_t)> key_callback_func;

class sdl_event_manager
{
public:
	sdl_event_manager();

	void ProcessEvents();

	void AddKeyBinding(uint32_t key, key_callback_func callback_func);

	void RemoveKeyBinding(uint32_t key_type);

private:
	inline void ProcessKeyBindingEvent(SDL_Event& event);
	
	std::map<uint32_t, key_callback_func> key_bindings = {};
};
}	// namespace dreco