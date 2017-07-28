#pragma once

#ifndef GLEW_STATIC
#define GLEW_STATIC
#endif

#include <string>
#include <vector>
#include <map>
#include <exception>
#include <algorithm>

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

extern void checkGLErrors();

#ifdef _DEBUG
#define CB_GL_CHECKERRORS() checkGLErrors()
#else
#define CB_GL_CHECKERRORS()
#endif