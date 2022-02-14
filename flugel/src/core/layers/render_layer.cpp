#include "render_layer.hpp"

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

        shader_ = Shader::create(
          // Vertex
          R"(#version 460 core
   
             layout (location = 0) in vec4 pos;
             layout (location = 1) in vec4 color;
   
             out vec4 vertColor;
   
             void main() {
               vertColor = color;
               gl_Position = pos;
             })",
          // Fragment
          R"(#version 460 core
             
             in vec4 vertColor;
   
             layout (location = 0) out vec4 fragColor;
   
             void main() {
               fragColor = vertColor;
             })"
        );

        return false;
      }
      case RenderEventType::EndFrame: { 
        //auto gl{gladGetGLContext()};
        shader_->bind();
        
        vaoSqr_->bind();
        glDrawElements(GL_TRIANGLES, vaoSqr_->indexCount(), GL_UNSIGNED_INT, nullptr);
        vaoSqr_->unbind();

        vao_->bind();
        glDrawElements(GL_TRIANGLES, vao_->indexCount(), GL_UNSIGNED_INT, nullptr);
        vao_->unbind();
      
        shader_->unbind();

        return false;
      }
      default: {
        return false;
      }
    }
  }
}