using CustomGraphicsLib.Enums;
using System;
using System.Drawing;
using System.Numerics;
using System.Runtime.CompilerServices;
using System.Threading;
using static CustomGraphicsLib.GraphicsLib;

namespace APICallTestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            if (CGLInitWindow("Fancy new OpenGL window!", 1280, 720))
            {
                uint shaderId = CGLCompileShader(ShaderType.GL_VERTEX_SHADER, Properties.Resources.VertexShader);

                while (!CGLWindowShouldClose())
                {
                    CGLClearColour(Color.Gray);

                    CGLDrawTriangle2D(new Vector2(-0.25f, 0.0f), new Vector2(0.0f, 0.5f), new Vector2(0.25f, 0.0f), Color.Yellow);
                    CGLDrawTriangle2D(new Vector2(-0.5f, -0.5f), new Vector2(-0.25f, 0.0f), new Vector2(0.0f, -0.5f), Color.Yellow);
                    CGLDrawTriangle2D(new Vector2(0.0f, -0.5f), new Vector2(0.25f, 0.0f), new Vector2(0.5f, -0.5f), Color.Yellow);

                    CGLDrawQuad2D(new Vector2(-0.6f, 0.6f), new Vector2(0.6f, 0.6f), new Vector2(0.6f, -0.6f), new Vector2(-0.6f, -0.6f), Color.Aqua);

                    CGLSwapBuffers();
                    CGLPollEvents();
                }
                CGLCloseWindow();
            }
            else
            {
                Console.WriteLine("Something went wrong!");
                Console.ReadKey();
            }
        }
    }
}
