using System;
using System.Drawing;
using System.Numerics;
using System.Runtime.InteropServices;

namespace CustomGraphicsLib
{
    public static class GraphicsLib
    {
        #region Imports

        /// <summary>
        /// A dummy command that prints "Hello World!" to the console. Used internally for testing.
        /// </summary>
        /// <param name="fancy">Set this to true if you have CVTS enabled. Makes things super-fancy!</param>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void PrintHello(bool fancy = false);

        /// <summary>
        /// Attemps to enable Console Virtual Terminal Sequences (CVTS), a recently added windows feature created for Windows Subsystem for Linux (WSL).
        /// </summary>
        /// <returns>True if the operation succeeded, otherwise false.</returns>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern bool TryEnableCVTS();

        /// <summary>
        /// Initializes a new OpenGL window to start drawing into with the specified <paramref name="width"/> and <paramref name="height"/>.
        /// </summary>
        /// <param name="title">The title of this window.</param>
        /// <param name="width">The width of the draw area for this new window in pixels.</param>
        /// <param name="height">The height of the draw area for this new window in pixels.</param>
        /// <returns>True if the operation succeeded, otherwise false.</returns>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern bool GLInitWindow(string title, int width, int height);

        /// <summary>
        /// Esenntially just an export for the glfwShouldWindowClose function. Returns true if the window should close, otherwise false.
        /// </summary>
        /// <returns>True if the window should close, otherwise false.</returns>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern bool GLWindowShouldClose();

        /// <summary>
        /// Closes the current window and terminates glfw.
        /// </summary>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void GLCloseWindow();

        /// <summary>
        /// Swaps the back and front buffers around. Since we are almost always drawing to the back buffer, this essentially displays the next frame. Call this after all drawing is done.
        /// </summary>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void GLSwapBuffers();

        /// <summary>
        /// Should be called at the end of every frame to allow GLFW to poll for events from the OS. (This includes key presses!)
        /// </summary>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void GLPollEvents();

        /// <summary>
        /// Clears the currently selected buffer with the specified colour.
        /// </summary>
        /// <param name="red">The red component represented as a float between 0.0 and 1.0.</param>
        /// <param name="green">The green component represented as a float between 0.0 and 1.0.</param>
        /// <param name="blue">The blue component represented as a float between 0.0 and 1.0.</param>
        /// <param name="alpha">The alpha (or transparency) component represented as a float between 0.0 and 1.0.</param>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void GLClearColour(float red, float green, float blue, float alpha = 1.0f);

        /// <summary>
        /// Render a triangle to the back buffer.
        /// </summary>
        /// <param name="pos1">The position of the first vertex of the triangle.</param>
        /// <param name="pos2">The position of the second vertex of the triangle.</param>
        /// <param name="pos3">The position of the third vertex of the triangle.</param>
        /// <param name="colour">The colour to use when drawing this triangle.</param>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void GLDrawTriangle2D(Vector2 pos1, Vector2 pos2, Vector2 pos3, Vector4 colour);

        /// <summary>
        /// Render a quad to the back buffer.
        /// </summary>
        /// <param name="pos1">The position of the first vertex of the quad. This should be the top-left vertice of the quad.</param>
        /// <param name="pos2">The position of the second vertex of the quad. This should be the top-right vertice of the quad.</param>
        /// <param name="pos3">The position of the third vertex of the quad. This should be the bottom-right vertice of the quad.</param>
        /// <param name="pos4">The position of the fourth vertex of the quad. This should be the bottom-left vertice of the quad.</param>
        /// <param name="colour">The colour to use when drawing this quad. For a square, this would be the top-left corner.</param>
        [DllImport("CustomGraphicsLib.dll")]
        public static extern void GLDrawQuad2D(Vector2 pos1, Vector2 pos2, Vector2 pos3, Vector2 pos4, Vector4 colour);

        #endregion


        #region Extras

        /// <summary>
        /// Clears the currently selected buffer with the specified colour.
        /// </summary>
        /// <param name="colour">The colour to clear the buffer with.</param>
        public static void GLClearColour(Color colour) => GLClearColour(colour.R / 255f, colour.G / 255f, colour.B / 255f, colour.A / 255f);

        /// <summary>
        /// Render a triangle to the back buffer.
        /// </summary>
        /// <param name="pos1">The position of the first vertex of the triangle. This should be the bottom-left vertice of the triangle.</param>
        /// <param name="pos2">The position of the second vertex of the triangle. This should be the top-mid vertice of the triangle.</param>
        /// <param name="pos3">The position of the third vertex of the triangle. This should be the bottom-right vertice of the triangle.</param>
        /// <param name="colour">The colour to use when drawing this triangle.</param>
        public static void GLDrawTriangle2D(Vector2 pos1, Vector2 pos2, Vector2 pos3, Color colour) => GLDrawTriangle2D(pos1, pos2, pos3, new Vector4(colour.R / 255f, colour.G / 255f, colour.B / 255f, colour.A / 255f));

        /// <summary>
        /// Render a quad to the back buffer.
        /// </summary>
        /// <param name="pos1">The position of the first vertex of the quad. This should be the top-left vertice of the quad.</param>
        /// <param name="pos2">The position of the second vertex of the quad. This should be the top-right vertice of the quad.</param>
        /// <param name="pos3">The position of the third vertex of the quad. This should be the bottom-right vertice of the quad.</param>
        /// <param name="pos4">The position of the fourth vertex of the quad. This should be the bottom-left vertice of the quad.</param>
        /// <param name="colour">The colour to use when drawing this quad. For a square, this would be the top-left corner.</param>
        public static void GLDrawQuad2D(Vector2 pos1, Vector2 pos2, Vector2 pos3, Vector2 pos4, Color colour) => GLDrawQuad2D(pos1, pos2, pos3, pos4, new Vector4(colour.R / 255f, colour.G / 255f, colour.B / 255f, colour.A / 255f));
        #endregion
    }
}
