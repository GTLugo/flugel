//
// Created by galex on 2/17/2022.
//

#include "renderer.hpp"

#include "core/app.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/opengl_render_dispatcher.hpp"
#endif

namespace fge {
  void Renderer::setApi(Renderer::API api) {
    renderingAPI_ = api;
    FGE_INFO("Selected Rendering API: {}", api);
    switch (api) {
      case Renderer::API::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        break;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        renderDispatcher_ = makeUnique<OpenGLRenderDispatcher>();
        #else
        FGE_ASSERT_ENG(false, "OpenGL not supported!");
        #endif
        break;
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FGE_ASSERT_ENG(false, "Vulkan not implemented!");
        #else
        FGE_ASSERT_ENG(false, "Vulkan not supported!");
        #endif
        break;
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FGE_ASSERT_ENG(false, "D3D11 not implemented!");
        #else
        FGE_ASSERT_ENG(false, "D3D11 not supported!");
        #endif
        break;
      }
      default: {
        FGE_ASSERT_ENG(false, "Unknown render api!");
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
