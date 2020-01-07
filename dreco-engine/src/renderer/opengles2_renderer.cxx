#include "opengles2_renderer.hxx"

#include "core/engine.hxx"
#include "game_objects/game_world.hxx"
#include "game_objects/mesh_object.hxx"
#include "gl_check.hxx"
#include "gl_inline_functions.hxx"
#include "math/vec3.hxx"
#include "utils/file_utils.hxx"

using namespace dreco;

opengles2_renderer::opengles2_renderer(engine& _e) : engine_owner(&_e)
{
}

opengles2_renderer::~opengles2_renderer()
{
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);
}

int opengles2_renderer::Init(const std::string& _window_title)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	window = SDL_CreateWindow(_window_title.c_str(), SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED, 540, 960, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

	if (!window)
	{
		std::cerr << "Init(): SDL_Create_Window():  " << SDL_GetError() << std::endl;
		return INIT_FAILED;
	}

	gl_context = SDL_GL_CreateContext(window);

	LoadGlFunctions();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GL_CHECK();

	if (!gl_context)
	{
		std::cerr << "Renderer->Init(): SDL_Create_Window():  " << SDL_GetError()
				  << std::endl;
		return INIT_FAILED;
	}

	return INIT_SUCCESS;
}

void opengles2_renderer::Tick(const float& DeltaTime)
{
	ClearBuffers();
	DrawScene(false);
	SwapBuffer();
	DrawScene(true);
}

void opengles2_renderer::UpdateViewportSize()
{
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(engine_owner->GetWindow(), &w, &h);

	glViewport(0, 0, w, h);
}

int opengles2_renderer::GetStencilIndexFromPixel(const vec2& _p_coord)
{
	uint8_t rgb[4];
	int win_h;
	SDL_GetWindowSize(engine_owner->GetWindow(), nullptr, &win_h);
	glReadPixels(_p_coord.x, win_h - _p_coord.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &rgb);
	GL_CHECK();

	return rgb[0] + rgb[1] * 256 + rgb[2] * 65536;
}

void opengles2_renderer::DrawScene(const bool _is_color_pass)
{
	auto world = engine_owner->GetOwnedGame()->GetCurrentWorld();

	if (world)
	{
		const world_objects_map& wos = world->GetWorldObjects();

		int index = 1;
		for (auto o : wos)
		{
			mesh_object* mesh = dynamic_cast<mesh_object*>(o.second);
			if (mesh)
			{
				mesh->SetObjectIndex(index);
				++index;
				!_is_color_pass ? mesh->StartDraw() : mesh->DrawObjPickColor();
			}
		}
	}
}

void opengles2_renderer::SwapBuffer()
{
	SDL_GL_SwapWindow(engine_owner->GetWindow());
}

void opengles2_renderer::ClearBuffers()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	GL_CHECK();
}

SDL_Window* opengles2_renderer::GetWindow() const
{
	return window;
}