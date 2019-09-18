#pragma once
#include "SDL2/SDL.h"

#include <functional>
#include <map>
#include <string>

namespace dreco
{
typedef std::function<void(uint32_t)> key_callback_func;

typedef std::function<void()> event_callback_func;

class sdl_event_manager
{
public:
	sdl_event_manager();

	void ProcessEvents();

	void AddKeyBinding(uint32_t key, key_callback_func callback_func);

	void RemoveKeyBinding(uint32_t key_type);

	void AddEventBinding(uint32_t event_type, event_callback_func callback_func);

	void RemoveEventBinding(uint32_t event_type);

private:
	inline void ProcessKeyBindingEvent(SDL_Event& event);
	
	inline void ProcessEventBinding(const SDL_Event& event);
	
	std::map<uint32_t, key_callback_func> key_bindings = {};

	std::map<uint32_t, event_callback_func> event_bindings = {};
};
}	// namespace dreco