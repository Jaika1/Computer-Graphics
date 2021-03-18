using System;
using System.Drawing;
using JGraphicsLib;
using JGraphicsLib.Structs;

namespace GLGame
{
    class Program
    {
        static int Main(string[] args)
        {
            if (!JGLib.InitializeWindow("Game window", 320, 224))
            {
                Console.WriteLine("An error occured while initializing the game window!");
                return -1;
            }

            while (!JGLib.ShouldWindowClose())
            {
                JGLib.ClearBackBuffer(Color.Red);
                JGLib.EndDraw();
            }

            JGLib.DestroyWindow();
            return 0;
        }
    }
}
