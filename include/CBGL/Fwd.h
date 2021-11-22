#pragma once

#include "Defines.h"

namespace cb {
  namespace gl {
    enum class BufferTarget;
    enum class BufferUsage;
    enum class PrimitiveType;
    enum class DataType;
    enum class ClearBuffer;
    enum class ShaderType;
    enum class TextureFormat;
    enum class InputFormat;
    enum class TextureFilter;
    enum class TextureWrap;
    enum class BlendFactor;
    enum class BlendFunc;
    enum class CullFace;
    enum class FrontFace;
    enum class DepthFunc;
    enum class State;

    struct BlendState;
    struct CullState;
    struct DepthState;

    class Buffer;
    class Shader;
    class Program;
    class Texture;
    class VertexSource;
    class VertexDefinition;
  }
}