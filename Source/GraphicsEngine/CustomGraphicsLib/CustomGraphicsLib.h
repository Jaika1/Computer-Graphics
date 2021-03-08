#pragma once

#pragma region Export/import definitions

#ifdef GRAPHICSLIB_EXPORTS
#define GRAPHICSLIB_API __declspec(dllexport)
#else
#define GRAPHICSLIB_API __declspec(dllimport)
#endif

#pragma endregion

struct GLFWwindow;

/// <value>The pointer that will be used to store a window upon creation for our functions to call.</value>
extern GLFWwindow* windowPointer;


/// <summary>
/// A dummy command that prints "Hello World!" to the console. Used internally for testing.
/// </summary>
/// <param name="fancy">Set this to true if you have CVTS enabled. Makes things super-fancy!</param>
extern "C" GRAPHICSLIB_API void PrintHello(bool fancy = false);

/// <summary>
/// Attemps to enable Console Virtual Terminal Sequences (CVTS), a recently added windows feature created for Windows Subsystem for Linux (WSL).
/// </summary>
/// <returns>True if the operation succeeded, otherwise false.</returns>
extern "C" GRAPHICSLIB_API bool TryEnableCVTS();

/// <summary>
/// Initializes a new OpenGL window to start drawing into with the specified <paramref name="width"/> and <paramref name="height"/>.
/// </summary>
/// <param name="title">The title of this window.</param>
/// <param name="width">The width of the draw area for this new window in pixels.</param>
/// <param name="height">The height of the draw area for this new window in pixels.</param>
/// <returns>True if the operation succeeded, otherwise false.</returns>
extern "C" GRAPHICSLIB_API bool GLInitWindow(const char* title, int width, int height);

/// <summary>
/// Esenntially just an export for the glfwShouldWindowClose function. Returns true if the window should close, otherwise false.
/// </summary>
/// <returns>True if the window should close, otherwise false.</returns>
extern "C" GRAPHICSLIB_API bool GLWindowShouldClose();

/// <summary>
/// Closes the current window and terminates glfw.
/// </summary>
extern "C" GRAPHICSLIB_API void GLCloseWindow();

/// <summary>
/// Swaps the back and front buffers around. Since we are almost always drawing to the back buffer, this essentially displays the next frame. Call this after all drawing is done.
/// </summary>
extern "C" GRAPHICSLIB_API void GLSwapBuffers();

/// <summary>
/// Clears the currently selected buffer with the specified colour.
/// </summary>
/// <param name="red">The red component represented as a float between 0.0 and 1.0.</param>
/// <param name="green">The green component represented as a float between 0.0 and 1.0.</param>
/// <param name="blue">The blue component represented as a float between 0.0 and 1.0.</param>
/// <param name="alpha">The alpha (or transparency) component represented as a float between 0.0 and 1.0.</param>
extern "C" GRAPHICSLIB_API void GLClearColour(float red, float green, float blue, float alpha = 1.0f);