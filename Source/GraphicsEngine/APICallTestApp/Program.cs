using System;
using System.Drawing;
using System.Numerics;
using System.Threading;
using static CustomGraphicsLib.GraphicsLib;

namespace APICallTestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            if (GLInitWindow("Fancy new OpenGL window!", 1280, 720))
            {
                while (!GLWindowShouldClose())
                {
                    GLClearColour(Color.Lime);

                    GLDrawTriangle2D(new Vector2(-0.9f, -0.1f), new Vector2(-0.85f, 0.1f), new Vector2(-0.8f, -0.1f));
                    GLDrawTriangle2D(new Vector2(0.8f, -0.1f), new Vector2(0.85f, 0.1f), new Vector2(0.9f, -0.1f));

                    GLSwapBuffers();
                }
                GLCloseWindow();
            }
            else
            {
                Console.WriteLine("Something went wrong!");
                Console.ReadKey();
            }
        }
    }
}
