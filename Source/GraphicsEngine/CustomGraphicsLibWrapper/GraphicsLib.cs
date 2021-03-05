using System;
using System.Runtime.InteropServices;

namespace CustomGraphicsLib
{
    public static class GraphicsLib
    {
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
    }
}
