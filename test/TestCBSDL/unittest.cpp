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
      using namespace cb::sdl;
      auto vidsys = CSubSystem(SubSystemFlag::Video);
      auto win = CWindow(L"Test window.", CWindow::PosCentered,
                                  glm::uvec2(640, 480),
                                  WindowFlag::OPENGL | WindowFlag::RESIZABLE);

      auto attribs = GLAttributeMapT{
        {SDL_GL_BUFFER_SIZE, 32},
        {SDL_GL_DEPTH_SIZE, 24},
        {SDL_GL_STENCIL_SIZE, 8}
      };
      auto ctx = CGLContext(win, attribs);

      win.Show();

      auto event = CEvent();
      bool run = true;
      while(run) {
        if(CEvent::Poll(event)) {
          if((event.GetType() == EventType::WINDOWEVENT && CWindowEvent(event).GetType() == WindowEventType::CLOSE) ||
             event.GetType() == EventType::QUIT) {
            run = false;
          }
        }

        ctx.SwapWindow(win);
      }
    }
  };
}