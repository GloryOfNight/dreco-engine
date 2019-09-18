#include "sdl_event_manager.hxx"

using namespace dreco;

sdl_event_manager::sdl_event_manager()
{
}

void sdl_event_manager::ProcessEvents()
{
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_KEYDOWN:
				ProcessKeyBindingEvent(event);
			case SDL_KEYUP:
				ProcessKeyBindingEvent(event);
			default:
				ProcessEventBinding(event);
				break;

		}
	}
}

void sdl_event_manager::AddKeyBinding(uint32_t key, key_callback_func callback_func)
{
	key_bindings.emplace(key, callback_func);
}

void sdl_event_manager::RemoveKeyBinding(uint32_t key_type)
{
	key_bindings.erase(key_type);
}

void sdl_event_manager::AddEventBinding(uint32_t event_type, event_callback_func callback_func) 
{
	event_bindings.emplace(event_type, callback_func);
}

void sdl_event_manager::RemoveEventBinding(uint32_t event_type) 
{
	event_bindings.erase(event_type);
}

inline void sdl_event_manager::ProcessKeyBindingEvent(SDL_Event& event)
{
	if (key_bindings.find(event.key.keysym.sym) != key_bindings.end())
	{
		auto& binding = key_bindings.at(event.key.keysym.sym);

		if (binding)
		{
			binding(event.type);
		}
	}
}

inline void sdl_event_manager::ProcessEventBinding(const SDL_Event& event) 
{
	if (event_bindings.find(event.type) != event_bindings.end()) 
	{
		auto binding = event_bindings.at(event.type);

		if (binding) 
		{
			binding();
		}
	}
}