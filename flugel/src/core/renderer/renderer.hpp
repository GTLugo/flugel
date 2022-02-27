#pragma once

#include "render_dispatcher.hpp"

#include "core/renderer/shader.hpp"
#include "core/renderer/vertex_array/vertex_array.hpp"
#include "core/renderer/framebuffer/frame_buffer.hpp"

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

    static inline void setDefaultFrameBuffer(const Shared<FrameBuffer>& frameBuffer) { frameBuffer_ = frameBuffer; }
    static inline Weak<FrameBuffer>& defaultFrameBuffer() { return frameBuffer_; }

    static void clear(Color color);
    static void beginScene();
    static void submit(const Shared<VertexArray>& vertexArray, bool drawToDefaultFrameBuffer = true);
    static void endScene();
    static void setDepthTest(bool enabled);

  private:

    static inline API renderingAPI_{Renderer::API::None};
    static inline Unique<RenderDispatcher> renderDispatcher_;

    static inline Weak<FrameBuffer> frameBuffer_;
    static inline Weak<TextureBuffer> frameTexture_;

    static void draw(const Shared<VertexArray>& vertexArray);

    i32 amount = 2880. - 664.44 - 766.03 - 1133.15;
  };
}