//
// Created by galex on 2/17/2022.
//

#include "renderer.hpp"

#include "core/app.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/opengl_render_dispatcher.hpp"
#endif

namespace ff {
  void Renderer::setApi(Renderer::API api) {
    renderingAPI_ = api;
    Log::info_e("Selected Rendering API: {}", api);
    switch (api) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        renderDispatcher_ = makeUnique<OpenGLRenderDispatcher>();
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        break;
      }
    }
  }

  void Renderer::clear(Color color) {
    renderDispatcher_->clear(color);
  }

  void Renderer::beginScene() {
  }

  void Renderer::submit(const Shared<VertexArray>& vertexArray, bool drawToDefaultFrameBuffer) {
    // this will eventually be moved to a queue system where submission happens
    // at any time, but this draw method is called at the end of the frame.
    if (Shared<FrameBuffer> fbShared = frameBuffer_.lock()) {
      if (drawToDefaultFrameBuffer) fbShared->bind();
    }
    draw(vertexArray);
    if (Shared<FrameBuffer> fbShared = frameBuffer_.lock()) {
      if (drawToDefaultFrameBuffer) fbShared->unbind();
    }
  }

  void Renderer::endScene() {
  }

  void Renderer::setDepthTest(bool enabled) {
    renderDispatcher_->setDepthTest(enabled);
  }

  void Renderer::draw(const Shared<VertexArray>& vertexArray) {
    vertexArray->bind();
    renderDispatcher_->draw(vertexArray);
    vertexArray->unbind();
  }
}
