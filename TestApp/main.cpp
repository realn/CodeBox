#include <iostream>

#define SDL_MAIN_HANDLED

#include <glm/glm.hpp>
#include <CBSDL/Consts.h>
#include <CBSDL/System.h>
#include <CBSDL/Window.h>
#include <CBSDL/Events.h>
#include <CBSDL/GLContext.h>
#include <CBGL/System.h>

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

  auto event = cb::sdl::CEvent();
  auto run = true;
  while(run) {
    if(cb::sdl::CEvent::Poll(event)) {
      if(event.GetType() == cb::sdl::EventType::WINDOWEVENT) {
        auto winEvt = cb::sdl::CWindowEvent(event);
        if(winEvt.GetType() == cb::sdl::WindowEventType::CLOSE) {
          run = false;
        }
      }
    }
    glClearColor(0.2f, 0.2f, 0.5f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glctx.SwapWindow(window);
  }

  return 0;
}