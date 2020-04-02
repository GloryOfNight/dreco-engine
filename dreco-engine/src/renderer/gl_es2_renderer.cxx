#include "gl_es2_renderer.hxx"

#include "core/engine.hxx"
#include "game_objects/game_world.hxx"
#include "game_objects/mesh_object.hxx"
#include "gl_check.hxx"
#include "gl_inline_functions.hxx"
#include "utils/file_utils.hxx"

using namespace dreco;

gl_es2_renderer::gl_es2_renderer(engine& _e) : engine_owner(&_e)
{
}

gl_es2_renderer::~gl_es2_renderer()
{
	SDL_GL_DeleteContext(gl_context);
	SDL_DestroyWindow(window);

	for (auto i : meshes_buffers_info)
	{
		const gl_mesh_buffers_info& buff_info = i.second;
		glDeleteBuffers(1, &buff_info.vbo_vertex);
		glDeleteBuffers(1, &buff_info.vbo_tc);
		glDeleteBuffers(1, &buff_info.ibo_element);

		delete i.first;
	}
}

int gl_es2_renderer::Init(const char* _title)
{
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);

	window = SDL_CreateWindow(_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 540,
		960, SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);

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

void gl_es2_renderer::Tick(const float& DeltaTime)
{
	ClearBuffers();
	DrawScene();
	SwapBuffer();
}

void gl_es2_renderer::UpdateViewportSize()
{
	int w = 0;
	int h = 0;
	SDL_GetWindowSize(engine_owner->GetWindow(), &w, &h);

	glViewport(0, 0, w, h);
}

int gl_es2_renderer::GetColorIndexFromPixel(const vec2& _p_coord)
{
	uint8_t rgb[4];
	int win_h;
	SDL_GetWindowSize(engine_owner->GetWindow(), nullptr, &win_h);
	glReadPixels(_p_coord.x, win_h - _p_coord.y, 1, 1, GL_RGBA, GL_UNSIGNED_BYTE, &rgb);
	GL_CHECK();

	return rgb[0] + rgb[1] * 256 + rgb[2] * 65536;
}

void gl_es2_renderer::DrawScene()
{
	const auto world = engine_owner->GetOwnedGame()->GetCurrentWorld();

	if (world)
	{
		const world_objects_map& world_objects = world->GetWorldObjectsRef();

		for (auto obj : world_objects)
		{
			mesh_object* mesh = dynamic_cast<mesh_object*>(obj.second);
			if (mesh)
			{
				mesh->StartDraw();
			}
		}
	}
}

SDL_Window* gl_es2_renderer::GetWindow() const
{
	return window;
}

void gl_es2_renderer::AddMeshData(mesh_data* _mesh_data)
{
	if (_mesh_data && meshes_buffers_info.end() == meshes_buffers_info.find(_mesh_data))
	{
		GLuint buffs[3];
		glGenBuffers(3, buffs);

		gl_mesh_buffers_info buff_info{buffs[0], buffs[1], buffs[2]};

		glBindBuffer(GL_ARRAY_BUFFER, buff_info.vbo_vertex);
		glBufferData(GL_ARRAY_BUFFER,
			_mesh_data->vertexes_size * sizeof(_mesh_data->vertexes[0]),
			&_mesh_data->vertexes[0], GL_STATIC_DRAW);
		GL_CHECK();

		glBindBuffer(GL_ARRAY_BUFFER, buff_info.vbo_tc);
		glBufferData(GL_ARRAY_BUFFER,
			_mesh_data->texture_coordinates_size *
				sizeof(_mesh_data->texture_coordinates[0]),
			&_mesh_data->texture_coordinates[0], GL_STATIC_DRAW);
		GL_CHECK();

		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buff_info.ibo_element);
		glBufferData(GL_ELEMENT_ARRAY_BUFFER,
			_mesh_data->elements_size * sizeof(_mesh_data->elements[0]),
			&_mesh_data->elements[0], GL_STATIC_DRAW);
		GL_CHECK();

		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

		meshes_buffers_info.emplace(_mesh_data, buff_info);
	}
}

gl_mesh_buffers_info gl_es2_renderer::GetMeshDataBufferInfo(
	const mesh_data* _mesh_data) const
{
	// for some reason .at() and operator[] with map not compiling here
	// if you know why, please contact @GloryOfNight github
	for (const auto i : meshes_buffers_info)
	{
		if (i.first == _mesh_data)
		{
			return i.second;
		}
	}
	return gl_mesh_buffers_info(0, 0, 0);
}

void gl_es2_renderer::SwapBuffer()
{
	SDL_GL_SwapWindow(engine_owner->GetWindow());
}

void gl_es2_renderer::ClearBuffers()
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT);
	GL_CHECK();
}