#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <CBSDL/Consts.h>
#include <CBSDL/System.h>
#include <CBSDL/Window.h>
#include <CBSDL/Events.h>
#include <CBSDL/GLContext.h>
#include <CBSDL/Surface.h>
#include <CBSDL/Font.h>
#include <CBSDL/Timer.h>
#include <CBGL/System.h>
#include <CBGL/Rendering.h>
#include <CBGL/Buffer.h>
#include <CBGL/VertexDefinition.h>
#include <CBGL/Shader.h>
#include <CBGL/Program.h>
#include <CBGL/Texture.h>
#include <CBIO/File.h>

class CVertex {
public:
  glm::vec3 mPos;
  glm::vec2 mTex;

  CVertex(glm::vec3 const& pos, glm::vec2 const& tex) : mPos(pos), mTex(tex) {}
  CVertex(float x, float y, float z, float s, float t) : mPos(x, y, z), mTex(s, t) {}
};

int main(char* argv[], int argc) {
  auto sdlVideo = cb::sdl::CSystem(cb::sdl::System::VIDEO);
  auto window = cb::sdl::CWindow(L"OpenGL Test",
                                 cb::sdl::CWindow::PosCentered,
                                 glm::uvec2(640, 480),
                                 cb::sdl::WindowFlag::OPENGL);
  window.Show();
  auto glctx = cb::sdl::CGLContext(window, {
    {cb::sdl::GLAttribute::BUFFER_SIZE, 32},
    {cb::sdl::GLAttribute::DEPTH_SIZE, 24},
    {cb::sdl::GLAttribute::STENCIL_SIZE, 8},
    {cb::sdl::GLAttribute::DOUBLEBUFFER, 1},
  });
  cb::gl::initextensions();

  auto buffer = cb::gl::CBuffer();
  auto indices = cb::gl::CBuffer(cb::gl::BufferTarget::ELEMENT_ARRAY);
  {
    auto vbuf = cb::gl::bind(buffer);
    buffer.SetData(std::vector<CVertex>{
      {-0.5f, -0.5f, -0.5f, 0.0f, 0.0f},
      {0.5f, -0.5f, -0.5f, 1.0f, 0.0f},
      {0.5f, 0.5f, -0.5f, 1.0f, 1.0f},
      {-0.5f, 0.5f, -0.5f, 0.0f, 1.0f},
    });
  }
  {
    auto gind = cb::gl::bind(indices);
    auto data = std::vector<unsigned short>{0, 1, 2, 0, 2, 3};
    indices.SetData(data);
  }

  auto program = cb::gl::CProgram{
    {
      {cb::gl::ShaderType::VERTEX, cb::readtextfileutf8(L"shader_v.glsl")},
      {cb::gl::ShaderType::FRAGMENT, cb::readtextfileutf8(L"shader_f.glsl")},
    },
    {
      {0, L"vInVertex"},
      {1, L"vInTCoord"},
    },
  };
  if(!program.IsLinked()) {
    std::wcout << program.GetLinkLog() << std::endl;
    throw std::exception("Shader program link failed.");
  }

  auto vdef = cb::gl::CVertexDefinition{
    {0, cb::gl::DataType::FLOAT, 3, sizeof(CVertex)},
    {1, cb::gl::DataType::FLOAT, 2, sizeof(CVertex), sizeof(glm::vec3)},
  };

  auto texture = cb::gl::CTexture({128,128}, cb::gl::TextureFormat::RGBA8);
  {
    auto font = cb::sdl::CFont(L"Instruction.otf", 96);

    auto fontSurf = font.RenderBlended(L"T", {1.0f, 1.0f, 1.0f, 1.0f});
    fontSurf = fontSurf.Convert(cb::sdl::PixelFormat::RGBA32);
    auto texSurf = cb::sdl::CSurface({128, 128}, 32, cb::sdl::PixelFormat::RGBA32);
    texSurf.Paste({0, 0}, fontSurf);
    texSurf.Flip(cb::sdl::FlipDir::Vertical);

    texture.SetData(cb::gl::InputFormat::RGBA, texSurf.GetPixels());
  }

  auto timer = cb::sdl::CPerfTimer();
  auto event = cb::sdl::CEvent();
  auto run = true;
  while(run) {
    timer.Update();

    while(cb::sdl::CEvent::Poll(event)) {
      if(event.GetType() == cb::sdl::EventType::WINDOWEVENT &&
         event.Window().GetType() == cb::sdl::WindowEventType::CLOSE) {
        run = false;
      }
    }

    cb::gl::clearColor(glm::vec4(0.2f, 0.2f, 0.5f, 1.0f));
    cb::gl::clear(cb::gl::ClearBuffer::COLOR);

    {
      auto gprog = cb::gl::bind(program);

      auto gvbuf = cb::gl::bind(buffer);
      auto gvdef = cb::gl::bind(vdef);

      auto gind = cb::gl::bind(indices);

      auto gtex = cb::gl::bind(texture, 0);

      auto s = (glm::vec2(2.0f, 2.0f) * glm::vec2(4.0f/3.0f, 1.0f)) / 2.0f;
      program.SetUniform(L"mTransform", glm::transpose(glm::ortho(-s.x, s.x, -s.y, s.y)));
      program.SetUniform(L"texBase", 0);

      if(!program.IsValid()) {
        auto info = program.GetLinkLog();
        std::wcout << info << std::endl;
      }

      cb::gl::drawElements(cb::gl::PrimitiveType::TRIANGLES, 6);
    }

    glctx.SwapWindow(window);
  }

  return 0;
}