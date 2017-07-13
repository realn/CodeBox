#include "stdafx.h"
#include "CppUnitTest.h"

#include <glm/glm.hpp>

#include <CBSDL/Consts.h>
#include <CBSDL/System.h>
#include <CBSDL/Window.h>
#include <CBSDL/Events.h>
#include <CBSDL/GLContext.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std::literals;

namespace TestCBSDL {
  TEST_CLASS(SdlUnitTest) {
  public:
    TEST_METHOD(SubSystemsInit) {
      auto vidsys = cb::sdl::CSubSystem(cb::sdl::SubSystemFlag::Video);
      auto win = cb::sdl::CWindow(L"Test window.", cb::sdl::CWindow::PosCentered,
                                  glm::uvec2(640, 480),
                                  {cb::sdl::WindowFlag::OpenGL});

      auto attribs = cb::sdl::GLAttributeMapT{
        {SDL_GL_BUFFER_SIZE, 32},
        {SDL_GL_DEPTH_SIZE, 24},
        {SDL_GL_STENCIL_SIZE, 8}
      };
      auto ctx = cb::sdl::CGLContext(win, attribs);

      win.Show();

      auto event = cb::sdl::CEvent();
      bool run = true;
      while(run) {
        if(cb::sdl::CEvent::Poll(event)) {
          if((event.GetType() == cb::sdl::EventType::Window && event.Get().window.type == SDL_WINDOWEVENT_CLOSE) ||
             event.GetType() == cb::sdl::EventType::Quit) {
            run = false;
          }
        }

        ctx.SwapWindow(win);
      }
    }
  };
}