#pragma once
#include <glm.hpp>

#pragma region Export/import definitions

#define GRAPHICSLIB_EXPORT __declspec(dllexport)
#define GRAPHICSLIB_IMPORT __declspec(dllimport)

#pragma endregion

struct GLFWwindow;


/// <value>The pointer that will be used to store a window upon creation for our functions to call.</value>
extern GLFWwindow* windowPointer;


/// <summary>
/// A dummy command that prints "Hello World!" to the console. Used internally for testing.
/// </summary>
/// <param name="fancy">Set this to true if you have CVTS enabled. Makes things super-fancy!</param>
extern "C" GRAPHICSLIB_IMPORT void PrintHello(bool fancy = false);

/// <summary>
/// Attemps to enable Console Virtual Terminal Sequences (CVTS), a recently added windows feature created for Windows Subsystem for Linux (WSL).
/// </summary>
/// <returns>True if the operation succeeded, otherwise false.</returns>
extern "C" GRAPHICSLIB_IMPORT bool TryEnableCVTS();

/// <summary>
/// Initializes a new OpenGL window to start drawing into with the specified <paramref name="width"/> and <paramref name="height"/>.
/// </summary>
/// <param name="title">The title of this window.</param>
/// <param name="width">The width of the draw area for this new window in pixels.</param>
/// <param name="height">The height of the draw area for this new window in pixels.</param>
/// <returns>True if the operation succeeded, otherwise false.</returns>
extern "C" GRAPHICSLIB_IMPORT bool GLInitWindow(const char* title, int width, int height);

/// <summary>
/// Esenntially just an export for the glfwShouldWindowClose function. Returns true if the window should close, otherwise false.
/// </summary>
/// <returns>True if the window should close, otherwise false.</returns>
extern "C" GRAPHICSLIB_IMPORT bool GLWindowShouldClose();

/// <summary>
/// Closes the current window and terminates glfw.
/// </summary>
extern "C" GRAPHICSLIB_IMPORT void GLCloseWindow();

/// <summary>
/// Swaps the back and front buffers around. Since we are almost always drawing to the back buffer, this essentially displays the next frame. Call this after all drawing is done.
/// </summary>
extern "C" GRAPHICSLIB_IMPORT void GLSwapBuffers();

/// <summary>
/// Should be called at the end of every frame to allow GLFW to poll for events from the OS. (This includes key presses!)
/// </summary>
extern "C" GRAPHICSLIB_IMPORT void GLPollEvents();

/// <summary>
/// Clears the currently selected buffer with the specified colour.
/// </summary>
/// <param name="red">The red component represented as a float between 0.0 and 1.0.</param>
/// <param name="green">The green component represented as a float between 0.0 and 1.0.</param>
/// <param name="blue">The blue component represented as a float between 0.0 and 1.0.</param>
/// <param name="alpha">The alpha (or transparency) component represented as a float between 0.0 and 1.0.</param>
extern "C" GRAPHICSLIB_IMPORT void GLClearColour(float red, float green, float blue, float alpha = 1.0f);

/// <summary>
/// Render a triangle to the back buffer.
/// </summary>
/// <param name="pos1">The position of the first vertex of the triangle.</param>
/// <param name="pos2">The position of the second vertex of the triangle.</param>
/// <param name="pos3">The position of the third vertex of the triangle.</param>
/// <param name="colour">The colour to use when drawing this triangle.</param>
extern "C" GRAPHICSLIB_IMPORT void GLDrawTriangle2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec4 colour);

/// <summary>
/// Render a quad to the back buffer.
/// </summary>
/// <param name="pos1">The position of the first vertex of the quad.</param>
/// <param name="pos2">The position of the second vertex of the quad.</param>
/// <param name="pos3">The position of the third vertex of the quad.</param>
/// <param name="pos4">The position of the fourth vertex of the quad.</param>
/// <param name="colour">The colour to use when drawing this quad.</param>
extern "C" GRAPHICSLIB_IMPORT void GLDrawQuad2D(glm::vec2 pos1, glm::vec2 pos2, glm::vec2 pos3, glm::vec2 pos4, glm::vec4 colour);