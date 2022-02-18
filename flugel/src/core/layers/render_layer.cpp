#include "render_layer.hpp"

#include "core/app.hpp"

namespace fge {
  bool RenderLayer::onRenderEvent(RenderEvent& e) {
    switch (e.action()) {
      case RenderEvent::BeginFrame: {
        Renderer::clear(clearColor_);
        Renderer::beginScene();

        return false;
      }
      case RenderEvent::EndFrame: {
        Renderer::endScene();
        //Renderer::flush();
        App::instance().window().context().swapBuffers();

        return false;
      }
      default: {
        return false;
      }
    }
  }
}