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

#include <CBGL\COpenGL.h>

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

    glEnableClientState(GL_VERTEX_ARRAY);
    {
      auto vbuf = cb::gl::bind(buffer);

      cb::gl::loadMatrix(glm::transpose(glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f)));
      cb::gl::setVertexSource(3, cb::gl::DataType::FLOAT, 0);
      cb::gl::drawArrays(cb::gl::PrimitiveType::TRIANGLES, 3);
    }

    glctx.SwapWindow(window);
  }

  return 0;
}