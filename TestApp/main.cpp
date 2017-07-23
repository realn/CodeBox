#include <iostream>

#define SDL_MAIN_HANDLED

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <CBSDL/Consts.h>
#include <CBSDL/System.h>
#include <CBSDL/Window.h>
#include <CBSDL/Events.h>
#include <CBSDL/GLContext.h>
#include <CBGL/System.h>
#include <CBGL/Rendering.h>
#include <CBGL/Buffer.h>
#include <CBGL/VertexDefinition.h>
#include <CBGL/Shader.h>
#include <CBGL/Program.h>
#include <CBIO/File.h>

int main(char* argv[], int argc) {
  auto sdlVideo = cb::sdl::CSubSystem(cb::sdl::SubSystemFlag::Video);
  auto window = cb::sdl::CWindow(L"OpenGL Test",
                                 cb::sdl::CWindow::PosCentered,
                                 glm::uvec2(640, 480),
                                 cb::sdl::WindowFlag::OPENGL);
  window.Show();
  auto glattrs = cb::sdl::GLAttributeMapT{
    {cb::sdl::GLAttribute::BUFFER_SIZE, 32},
    {cb::sdl::GLAttribute::DEPTH_SIZE, 24},
    {cb::sdl::GLAttribute::STENCIL_SIZE, 8},
    {cb::sdl::GLAttribute::DOUBLEBUFFER, 1},
  };
  auto glctx = cb::sdl::CGLContext(window, glattrs);
  cb::gl::initextensions();

  auto buffer = cb::gl::CBuffer();
  {
    auto vbuf = cb::gl::bind(buffer);
    auto verts = {
      glm::vec3(0.0f, 0.5f, -.5f),
      glm::vec3(-0.4f, -0.3f, -.5f),
      glm::vec3(0.4f, -0.3f, -.5f),
    };

    buffer.SetData(verts);
  }

  auto program = cb::gl::CProgram();
  {
    auto vshader = cb::gl::CShader(cb::gl::ShaderType::VERTEX);
    if(!vshader.Compile(cb::readtextfileutf8(L"shader_v.glsl"))) {
      std::wcout << vshader.GetCompileLog() << std::endl;
      throw std::exception("Shader compile failed.");
    }
    auto fshader = cb::gl::CShader(cb::gl::ShaderType::FRAGMENT);
    if(!fshader.Compile(cb::readtextfileutf8(L"shader_f.glsl"))) {
      std::wcout << fshader.GetCompileLog() << std::endl;
      throw std::exception("Shader compile failed.");
    }
    program.Attach(vshader);
    program.Attach(fshader);
  }
  program.SetInLocation(0, L"vInVertex");
  if(!program.Link()) {
    std::wcout << program.GetLinkLog() << std::endl;
    throw std::exception("Shader program link failed.");
  }

  auto vdef = cb::gl::CVertexDefinition{
    {0, cb::gl::DataType::FLOAT, 3, sizeof(glm::vec3)}
  };

  auto event = cb::sdl::CEvent();
  auto run = true;
  while(run) {
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

      program.SetUniform(L"mTransform", glm::transpose(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f)));
      cb::gl::drawArrays(cb::gl::PrimitiveType::TRIANGLES, 3);
    }

    glctx.SwapWindow(window);
  }

  return 0;
}