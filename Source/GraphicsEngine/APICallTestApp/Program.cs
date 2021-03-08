using System;
using System.Drawing;
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
                    GLClearColour(Color.Green);

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
