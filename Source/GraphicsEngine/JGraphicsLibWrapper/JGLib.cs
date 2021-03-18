using JGraphicsLib.Structs;
using System;
using System.Drawing;
using System.Numerics;
using System.Runtime.InteropServices;

namespace JGraphicsLib
{
    public static class JGLib
    {
        [DllImport("JGraphicsLib.dll", EntryPoint = "JGL_InitializeWindow")]
        public static extern bool InitializeWindow(string title, int width, int height);

        [DllImport("JGraphicsLib.dll", EntryPoint = "JGL_DestroyWindow")]
        public static extern void DestroyWindow();

        [DllImport("JGraphicsLib.dll", EntryPoint = "JGL_ShouldWindowClose")]
        public static extern bool ShouldWindowClose();

        [DllImport("JGraphicsLib.dll", EntryPoint = "JGL_EndDraw")]
        public static extern void EndDraw();

        [DllImport("JGraphicsLib.dll", EntryPoint = "JGL_GetDeltaTime")]
        public static extern float GetDeltaTime();

        [DllImport("JGraphicsLib.dll", EntryPoint = "JGL_ClearBackBuffer")]
        public static extern void ClearBackBuffer(Vector4 colour);
        public static void ClearBackBuffer(Color colour) => ClearBackBuffer(new Vector4(colour.R / 255.0f, colour.G / 255.0f, colour.B / 255.0f, colour.A / 255.0f));


    }
}
