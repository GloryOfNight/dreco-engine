#pragma once

#ifdef __ANDROID__
#include "SDL_opengl.h"
#else
#include "SDL2/SDL_opengl.h"
#endif
#include "load_gl_func.hxx"

// clang-format off
inline PFNGLCREATESHADERPROC             glCreateShader             = nullptr;
inline PFNGLSHADERSOURCEPROC             glShaderSource             = nullptr;
inline PFNGLCOMPILESHADERPROC            glCompileShader            = nullptr;
inline PFNGLGETSHADERIVPROC              glGetShaderiv              = nullptr;
inline PFNGLGETSHADERINFOLOGPROC         glGetShaderInfoLog         = nullptr;
inline PFNGLDELETESHADERPROC             glDeleteShader             = nullptr;
inline PFNGLCREATEPROGRAMPROC            glCreateProgram            = nullptr;
inline PFNGLATTACHSHADERPROC             glAttachShader             = nullptr;
inline PFNGLBINDATTRIBLOCATIONPROC       glBindAttribLocation       = nullptr;
inline PFNGLLINKPROGRAMPROC              glLinkProgram              = nullptr;
inline PFNGLGETPROGRAMIVPROC             glGetProgramiv             = nullptr;
inline PFNGLGETPROGRAMINFOLOGPROC        glGetProgramInfoLog        = nullptr;
inline PFNGLDELETEPROGRAMPROC            glDeleteProgram            = nullptr;
inline PFNGLUSEPROGRAMPROC               glUseProgram               = nullptr;
inline PFNGLVERTEXATTRIBPOINTERPROC      glVertexAttribPointer      = nullptr;
inline PFNGLENABLEVERTEXATTRIBARRAYPROC  glEnableVertexAttribArray  = nullptr;
inline PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = nullptr;
inline PFNGLGETUNIFORMLOCATIONPROC       glGetUniformLocation       = nullptr;
inline PFNGLGETUNIFORMLOCATIONPROC       glGetAttribLocation       	= nullptr;
inline PFNGLUNIFORM1IPROC                glUniform1i                = nullptr;
inline PFNGLACTIVETEXTUREPROC            glActiveTexture_           = nullptr;
inline PFNGLUNIFORM4FVPROC               glUniform4fv               = nullptr;
inline PFNGLUNIFORMMATRIX3FVPROC         glUniformMatrix3fv         = nullptr;
inline PFNGLUNIFORMMATRIX4FVPROC         glUniformMatrix4fv         = nullptr;
inline PFNGLGENBUFFERSPROC               glGenBuffers               = nullptr;
inline PFNGLDELETEBUFFERSPROC            glDeleteBuffers            = nullptr;
inline PFNGLBINDBUFFERPROC               glBindBuffer               = nullptr;
inline PFNGLBUFFERDATAPROC               glBufferData               = nullptr;
inline PFNGLBUFFERSUBDATAPROC            glBufferSubData            = nullptr;
inline PFNGLGETBUFFERPARAMETERIVPROC	 glGetBufferParameteriv 	= nullptr;
//inline PFNGLDELETETEXTURESEXTPROC		 glDeleteTextures		 	= nullptr;
// clang-format on

inline void LoadGlFunctions()
{
	load_gl_func("glCreateShader", glCreateShader);
	load_gl_func("glShaderSource", glShaderSource);
	load_gl_func("glCompileShader", glCompileShader);
	load_gl_func("glGetShaderiv", glGetShaderiv);
	load_gl_func("glGetShaderInfoLog", glGetShaderInfoLog);
	load_gl_func("glDeleteShader", glDeleteShader);
	load_gl_func("glCreateProgram", glCreateProgram);
	load_gl_func("glAttachShader", glAttachShader);
	load_gl_func("glBindAttribLocation", glBindAttribLocation);
	load_gl_func("glLinkProgram", glLinkProgram);
	load_gl_func("glGetProgramiv", glGetProgramiv);
	load_gl_func("glGetProgramInfoLog", glGetProgramInfoLog);
	load_gl_func("glDeleteProgram", glDeleteProgram);
	load_gl_func("glUseProgram", glUseProgram);
	load_gl_func("glVertexAttribPointer", glVertexAttribPointer);
	load_gl_func("glEnableVertexAttribArray", glEnableVertexAttribArray);
	load_gl_func("glDisableVertexAttribArray", glDisableVertexAttribArray);
	load_gl_func("glGetUniformLocation", glGetUniformLocation);
	load_gl_func("glGetAttribLocation", glGetAttribLocation);
	load_gl_func("glUniform1i", glUniform1i);
	load_gl_func("glActiveTexture", glActiveTexture_);
	load_gl_func("glUniform4fv", glUniform4fv);
	load_gl_func("glUniformMatrix3fv", glUniformMatrix3fv);
	load_gl_func("glUniformMatrix4fv", glUniformMatrix4fv);
	load_gl_func("glGenBuffers", glGenBuffers);
    load_gl_func("glDeleteBuffers", glDeleteBuffers);
	load_gl_func("glBindBuffer", glBindBuffer);
	load_gl_func("glBufferData", glBufferData);
	load_gl_func("glBufferSubData", glBufferSubData);
	load_gl_func("glGetBufferParameteriv", glGetBufferParameteriv);
	//load_gl_func("glDeleteTextures", glDeleteTextures);
}