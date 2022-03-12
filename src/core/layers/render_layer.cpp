#include "render_layer.hpp"

#include "core/app.hpp"

namespace fge {
  bool RenderLayer::onRenderEvent(RenderEvent& e) {
    switch (e.action()) {
      case RenderEvent::Start: {
        App& app{App::instance()};
        frameBuffer_ = FrameBuffer::create(
            TextureBuffer::Format::RGB,
            App::instance().window().dims().x,
            App::instance().window().dims().y,
            nullptr);
        Renderer::setDefaultFrameBuffer(frameBuffer_);

        frameQuad_ = VertexArray::create(
            // Vertices
            {
                -1.f, -1.f, .1f, /**/ 0, 0,
                1.f, -1.f, .1f, /**/  1, 0,
                1.f,  1.f, .1f, /**/  1, 1,
                -1.f,  1.f, .1f, /**/ 0, 1,
            },
            // Layout
            {
                BufferElement::create<vec3>("pos"),
                BufferElement::create<vec2>("texCoords"),
            },
            // Indices
            {0, 1, 2, 2, 3, 0}
        );

        frameShader_ = Shader::create("res/flugel/shaders/simple_texture.glsl");

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