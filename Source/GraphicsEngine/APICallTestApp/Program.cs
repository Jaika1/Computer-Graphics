using System;
using CustomGraphicsLib;

namespace APICallTestApp
{
    class Program
    {
        static void Main(string[] args)
        {
            bool cvtsEnabled = GraphicsLib.TryEnableCVTS();
            GraphicsLib.PrintHello(cvtsEnabled);
            Console.ReadKey();
        }
    }
}
