#pragma once

#pragma region Export/import definitions

#ifdef GRAPHICSLIB_EXPORTS
#define GRAPHICSLIB_API __declspec(dllexport)
#else
#define GRAPHICSLIB_API __declspec(dllimport)
#endif

#pragma endregion


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