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
                uint shaderProgramID = CGLMakeShaderProgramVF(Properties.Resources.VertexShader, Properties.Resources.FragmentShader);

                while (!CGLWindowShouldClose())
                {
                    CGLClearColour(Color.Gray);

                    CGLAddTriangle2D(new Vector2(-0.25f, 0.0f), new Vector2(0.0f, 0.5f), new Vector2(0.25f, 0.0f), Vector4.One);
                    CGLAddTriangle2D(new Vector2(-0.5f, -0.5f), new Vector2(-0.25f, 0.0f), new Vector2(0.0f, -0.5f), Vector4.One);
                    CGLAddTriangle2D(new Vector2(0.0f, -0.5f), new Vector2(0.25f, 0.0f), new Vector2(0.5f, -0.5f), Vector4.One);

                    //CGLDrawQuad2D(new Vector2(-0.6f, 0.6f), new Vector2(0.6f, 0.6f), new Vector2(0.6f, -0.6f), new Vector2(-0.6f, -0.6f), Color.Aqua);

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
