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
#include <CBCore/File.h>

class CVertex {
public:
  glm::vec3 mPos;
  glm::vec2 mTex;

  CVertex(glm::vec3 const& pos, glm::vec2 const& tex) : mPos(pos), mTex(tex) {}
  CVertex(float x, float y, float z, float s, float t) : mPos(x, y, z), mTex(s, t) {}
};

int WinMain(char*) {
//int main(char* argv[], int argc) {
  auto sdlVideo = cb::sdl::System(cb::sdl::SystemFlags(cb::sdl::SystemFlag::VIDEO));

  cb::sdl::setContextCreationAttributes({
    {cb::sdl::GLAttribute::BUFFER_SIZE, 32},
    {cb::sdl::GLAttribute::DEPTH_SIZE, 24},
    {cb::sdl::GLAttribute::STENCIL_SIZE, 8},
    {cb::sdl::GLAttribute::DOUBLEBUFFER, 1},
                                        });

  auto window = cb::sdl::Window(L"OpenGL Test",
                                cb::sdl::Window::PosCentered,
                                glm::uvec2(640, 480),
                                cb::sdl::WindowFlag::OPENGL);

  window.show();
  auto glctx = cb::sdl::GLContext(window);
  cb::gl::initextensions();

  auto buffer = cb::gl::Buffer();
  auto indices = cb::gl::Buffer(cb::gl::BufferTarget::ELEMENT_ARRAY);
  {
    auto vbuf = cb::gl::bind(buffer);
    buffer.setData(std::vector<CVertex>{
      { -0.5f, -0.5f, -0.5f, 0.0f, 0.0f },
      { 0.5f, -0.5f, -0.5f, 1.0f, 0.0f },
      { 0.5f, 0.5f, -0.5f, 1.0f, 1.0f },
      { -0.5f, 0.5f, -0.5f, 0.0f, 1.0f },
    });
  }
  {
    auto gind = cb::gl::bind(indices);
    auto data = std::vector<unsigned short>{ 0, 1, 2, 0, 2, 3 };
    indices.setData(data);
  }

  auto program = cb::gl::Program{
    {
      {cb::gl::ShaderType::VERTEX, cb::readtextfileutf8(L"shader_v.glsl")},
      {cb::gl::ShaderType::FRAGMENT, cb::readtextfileutf8(L"shader_f.glsl")},
    },
    {
      {0, L"vInVertex"},
      {1, L"vInTCoord"},
    },
  };
  if (!program.isLinked()) {
    std::wcout << program.getLinkLog() << std::endl;
    throw std::exception("Shader program link failed.");
  }

  auto vsources = cb::gl::VertexSourceList();
  vsources.add<CVertex, glm::vec3>(0);
  vsources.add<CVertex, glm::vec2>(1);

  auto vdef = cb::gl::VertexDefinition(vsources);

  auto texture = cb::gl::Texture({ 128,128 }, cb::gl::TextureFormat::RGBA8);
  {
    auto font = cb::sdl::Font(L"Instruction.otf", 96);

    auto fontSurf = font.renderBlended(L"T", { 1.0f, 1.0f, 1.0f, 1.0f });
    fontSurf = fontSurf.convert(cb::sdl::PixelFormat::RGBA32);
    auto texSurf = cb::sdl::Surface({ 128, 128 }, 32, cb::sdl::PixelFormat::RGBA32);
    texSurf.paste({ 0, 0 }, fontSurf);
    texSurf.flip(cb::sdl::FlipDir::Vertical);

    texture.setData(cb::gl::InputFormat::RGBA, texSurf.getPixels());
  }

  auto timer = cb::sdl::PerformanceTimer();
  auto event = cb::sdl::Event();
  auto run = true;
  while (run) {
    timer.update();

    while (cb::sdl::Event::poll(event)) {
      if (event.getType() == cb::sdl::EventType::WINDOWEVENT &&
          event.window().getType() == cb::sdl::WindowEventType::CLOSE) {
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

      auto s = (glm::vec2(2.0f, 2.0f) * glm::vec2(4.0f / 3.0f, 1.0f)) / 2.0f;
      program.setUniform(L"mTransform", glm::transpose(glm::ortho(-s.x, s.x, -s.y, s.y)));
      program.setUniform(L"texBase", 0);

      if (!program.isValid()) {
        auto info = program.getLinkLog();
        std::wcout << info << std::endl;
      }

      cb::gl::drawElements(cb::gl::PrimitiveType::TRIANGLES, 6);
    }

    glctx.swapWindow(window);
  }

  return 0;
}