#pragma once
#include <ctime>
#include <glm.hpp>

#define JGL_IMPORTS __declspec(dllimport)

using namespace glm;

struct GLFWwindow;


extern GLFWwindow* g_gameWindow;

extern float g_deltaTime;

extern clock_t g_timer;


extern "C" JGL_IMPORTS bool JGL_InitializeWindow(const char* title, int width, int height);

extern "C" JGL_IMPORTS void JGL_DestroyWindow();

extern "C" JGL_IMPORTS bool JGL_ShouldWindowClose();

extern "C" JGL_IMPORTS void JGL_EndDraw();

extern "C" JGL_IMPORTS float JGL_GetDeltaTime();

extern "C" JGL_IMPORTS void JGL_ClearBackBuffer(vec4 colour);