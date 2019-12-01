#include "opengles2_renderer.hxx"

#include "game_objects/game_world.hxx"
#include "game_objects/mesh_object.hxx"
#include "core/engine.hxx"
#include "gl_inline_functions.hxx"
#include "gl_check.hxx"
#include "math/vec3.hxx"
#include "utils/file_utils.hxx"

using namespace dreco;

opengles2_renderer::opengles2_renderer(engine& _e)
{
	engine_owner = &_e;
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

	gl_context = SDL_GL_CreateContext(engine_owner->GetWindow());

	LoadGlFunctions();

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	GL_CHECK();

	glEnable(GL_STENCIL_TEST);
	glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);
	GL_CHECK();
}

opengles2_renderer::~opengles2_renderer()
{
	SDL_GL_DeleteContext(gl_context);
}

void opengles2_renderer::Tick(const float& DeltaTime)
{
	ClearBuffers();
	DrawScene();
	SwapBuffer();
}

void opengles2_renderer::UpdateViewportSize()
{
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(engine_owner->GetWindow(), &w, &h);

	glViewport(0, 0, w, h);
}

vec2 opengles2_renderer::UnProject(const vec2& _wincoord, const vec2& _viewport, 
const mat2x3& _m, const mat2x3& _p_coord)
{
	mat2x3 pm = _p_coord  *_m;
	pm = mat2x3::inverse(pm);

	vec3 in;
	in.x = 	((_wincoord.x / _viewport.x) * 2) - 1.0f;
	in.y = 1.0f - ((_wincoord.y / _viewport.y) * 2);
	in.z = 1;

	vec2 res;
    res.x = in.x *pm.mat[0][0] + in.x *pm.mat[1][0] + pm.mat[0][2];
    res.y = in.y * pm.mat[0][1] + in.y * pm.mat[1][1] + pm.mat[1][2];

	return res;
}

int opengles2_renderer::GetStencilIndexFromPixel(const vec2& _p_coord) 
{
	uint8_t index;
	int win_h;
	SDL_GetWindowSize(engine_owner->GetWindow(), nullptr, &win_h);
	glReadPixels(_p_coord.x, win_h -_p_coord.y, 1, 1, GL_STENCIL_INDEX, GL_UNSIGNED_BYTE, &index);
	GL_CHECK();
	return index;
}

void opengles2_renderer::DrawScene() 
{
	auto world = engine_owner->GetOwnedGame()->GetCurrentWorld();
	
	if (world) 
	{
		const world_objects_map& wom = world->GetWorldObjects();

		int stencil_counter = 0;
		for (auto i : wom) 
		{
			mesh_object* mesh = dynamic_cast<mesh_object*>(i.second);

			if (mesh) 
			{
				glStencilFunc(GL_ALWAYS, ++stencil_counter, -1);
				GL_CHECK();
				mesh->stencil_index = stencil_counter;
				mesh->StartDraw();
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
	glClearStencil(0);
	glClear(GL_COLOR_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	GL_CHECK();
}