#include "sdl_event_manager.hxx"

using namespace dreco;

sdl_event_manager::sdl_event_manager()
{
}

void sdl_event_manager::ProcessEvents()
{
    SDL_Event event;
    while(SDL_PollEvent(&event)) 
    {
        switch(event.type) 
        {
            case SDL_KEYDOWN:
            ProcessKeyBindindEvent(event);
            break;
            case SDL_KEYUP:
            ProcessKeyBindindEvent(event);
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

 inline void sdl_event_manager::ProcessKeyBindindEvent(SDL_Event& event) 
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