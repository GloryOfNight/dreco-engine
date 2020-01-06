#pragma once
#ifdef __ANDROID__
#include "SDL_log.h"
#else
#include "SDL2/SDL_log.h"
#endif
#include <cassert>
#include <iostream>

#define GL_CHECK()                                                                     \
	{                                                                                  \
		const int error = glGetError();                                                \
		if (error != GL_NO_ERROR)                                                      \
		{                                                                              \
			const std::string error_message = "GL_CHECK() ERROR HANDLED: ";            \
			switch (error)                                                             \
			{                                                                          \
				case GL_INVALID_ENUM:                                                  \
					SDL_Log("GL_CHECK() ERROR HANDLED: GL_INVALID_ENUM");              \
					std::cerr << error_message << "GL_INVALID_ENUM" << std::endl;      \
					break;                                                             \
				case GL_INVALID_VALUE:                                                 \
					SDL_Log("GL_CHECK() ERROR HANDLED: GL_INVALID_VALUE");             \
					std::cerr << error_message << "GL_INVALID_VALUE" << std::endl;     \
					break;                                                             \
				case GL_INVALID_OPERATION:                                             \
					SDL_Log("GL_CHECK() ERROR HANDLED: GL_INVALID_OPERATION");         \
					std::cerr << error_message << "GL_INVALID_OPERATION" << std::endl; \
					break;                                                             \
				case GL_INVALID_FRAMEBUFFER_OPERATION:                                 \
					SDL_Log(                                                           \
						"GL_CHECK() ERROR HANDLED: GL_INVALID_FRAMEBUFFER_OPERATION"); \
					std::cerr << error_message << "GL_INVALID_FRAMEBUFFER_OPERATION"   \
							  << std::endl;                                            \
					break;                                                             \
				case GL_OUT_OF_MEMORY:                                                 \
					SDL_Log("GL_CHECK() ERROR HANDLED: OUT_OF_MEMORY");                \
					std::cerr << error_message << "OUT_OF_MEMORY" << std::endl;        \
					break;                                                             \
			}                                                                          \
			std::cerr << "GL_CHECK() ERROR CODE: " << error << std::endl;              \
			assert(false);                                                             \
		}                                                                              \
	}
