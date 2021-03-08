using System;
using System.Collections.Generic;
using System.ComponentModel.DataAnnotations;
using System.Text;

namespace CustomGraphicsLib.Enums
{
    public enum ShaderType : uint
    {
        GL_FRAGMENT_SHADER = 0x8B30u,
        GL_VERTEX_SHADER = 0x8B31u,
        GL_GEOMETRY_SHADER = 0x8DD9,
        GL_TESS_EVALUATION_SHADER = 0x8E87,
        GL_TESS_CONTROL_SHADER = 0x8E88,
        GL_COMPUTE_SHADER = 0x91B9u
    }
}
