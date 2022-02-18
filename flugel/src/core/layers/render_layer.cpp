#include "render_layer.hpp"

#include "core/app.hpp"

namespace fge {
  bool RenderLayer::onRenderEvent(RenderEvent& e) {
    switch (e.type()) {
      case RenderEventType::BeginFrame: {
        Renderer::clear(clearColor_);
        Renderer::beginScene();

        return false;
      }
      case RenderEventType::EndFrame: {
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