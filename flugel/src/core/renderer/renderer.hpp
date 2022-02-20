#pragma once

#include "util/color/color.hpp"
#include "core/renderer/vertex_array/vertex_array.hpp"
#include "render_dispatcher.hpp"

namespace fge {

  class FGE_API Renderer {
  public:
    enum class API {
      None = 0,
      OpenGL,
      Vulkan,
      D3D11,
    };

    static API api() { return renderingAPI_; }
    static void setApi(API api);

    static void clear(Color color);
    static void beginScene();
    static void submit(const Shared<VertexArray>& vertexArray);
    static void endScene();

  private:
    static inline API renderingAPI_{Renderer::API::None};
    static inline Unique<RenderDispatcher> renderDispatcher;

    static void draw(const Shared<VertexArray>& vertexArray);
  };
}