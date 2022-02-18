//
// Created by galex on 2/17/2022.
//

#include "renderer.hpp"

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
        renderDispatcher = makeUnique<OpenGLRenderDispatcher>();
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
    renderDispatcher->clear(color);
  }

  void Renderer::beginScene() {

  }

  void Renderer::submit(const Shared<VertexArray>& vertexArray) {
    // this will eventually be moved to a queue system where submission happens
    // at any time, but this draw method is called at the end of the frame.
    draw(vertexArray);
  }

  void Renderer::endScene() {

  }

  void Renderer::draw(const Shared<VertexArray>& vertexArray) {
    vertexArray->bind();
    renderDispatcher->draw(vertexArray);
    vertexArray->unbind();
  }
}
