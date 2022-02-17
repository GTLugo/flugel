#include "render_layer.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace fge {
  bool RenderLayer::onRenderEvent(RenderEvent& e) {
    switch (e.type()) {
      case RenderEventType::Start: {
        vao_ = VertexArray::create(
          // Vertices
          {-.5, -.5,  0., /**/.7, .1, .1, 1.,
            .5, -.5,  0., /**/.1, .7, .1, 1.,
            0.,  .5,  0., /**/.1, .1, .7, 1.},
          // Layout
          {{ShaderDataType::Float3, "pos"},
           {ShaderDataType::Float4, "color"}},
          // Indices
          {0, 1, 2}
        );

        vaoSqr_ = VertexArray::create(
          // Vertices
          {-.75, -.75, .1, /**/ .1, .1, .1, 1.,
            .75, -.75, .1, /**/ .1, .1, .1, 1.,
            .75,  .75, .1, /**/ .7, .6, .6, 1.,
           -.75,  .75, .1, /**/ .7, .6, .6, 1.},
          // Layout
          {{ShaderDataType::Float3, "pos"},
           {ShaderDataType::Float4, "color"}},
          // Indices
          {0, 1, 2, 2, 3, 0}
        );

        shader_ = Shader::create("res/flugel/shaders/simple_shader.glsl");

        return false;
      }
      case RenderEventType::BeginFrame: {
        //auto gl{gladGetGLContext()};
        glClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
        glClear(GL_COLOR_BUFFER_BIT);
        return false;
      }
      case RenderEventType::EndFrame: { 
        //auto gl{gladGetGLContext()};

        //RenderCommand::setClearColor()
        //Renderer::beginScene();

        shader_->bind();

        vaoSqr_->bind();
        glDrawElements(GL_TRIANGLES, vaoSqr_->indexCount(), GL_UNSIGNED_INT, nullptr);
        vaoSqr_->unbind();


        vao_->bind();
        glDrawElements(GL_TRIANGLES, vao_->indexCount(), GL_UNSIGNED_INT, nullptr);
        vao_->unbind();

        //Renderer::submit(vaoSqr_);
        shader_->unbind();
        //Renderer::endScene();
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