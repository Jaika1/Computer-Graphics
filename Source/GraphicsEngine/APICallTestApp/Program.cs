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
                    GLClearColour(Color.Gray);

                    GLDrawQuad2D(new Vector2(-0.1f, 0.1f), new Vector2(0.13f, 0.12f), new Vector2(-0.1f, -0.1f), new Vector2(0.15f, -0.15f), Color.Aqua);

                    GLDrawTriangle2D(new Vector2(-0.25f, 0.0f), new Vector2(0.0f, 0.5f), new Vector2(0.25f, 0.0f), Color.Yellow);
                    GLDrawTriangle2D(new Vector2(-0.5f, -0.5f), new Vector2(-0.25f, 0.0f), new Vector2(0.0f, -0.5f), Color.Yellow);
                    GLDrawTriangle2D(new Vector2(0.0f, -0.5f), new Vector2(0.25f, 0.0f), new Vector2(0.5f, -0.5f), Color.Yellow);


                    GLSwapBuffers();
                    GLPollEvents();
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
