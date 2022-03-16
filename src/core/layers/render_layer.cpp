#include "render_layer.hpp"

#include "core/app.hpp"

namespace ff {
  bool RenderLayer::onRenderEvent(RenderEvent& e) {
    switch (e.action()) {
      case RenderEvent::Start: {
        App& app{App::instance()};
        defaultFrameBuffer_ = FrameBuffer::create(
            TextureBuffer::Format::RGB,
            App::instance().window().dims().x,
            App::instance().window().dims().y,
            nullptr);
        Renderer::setDefaultFrameBuffer(defaultFrameBuffer_);

        return false;
      }
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