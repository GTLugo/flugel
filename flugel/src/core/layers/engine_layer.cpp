#include "engine_layer.hpp"

#include "core/app.hpp"
#include "core/input/input.hpp"

#include <glad/gl.h>

namespace fge {
  bool EngineLayer::onWindowEvent(WindowEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    switch (e.type()) {
      case WindowEventType::Close: {
        FGE_DEBUG_ENG("{0}: {1}", name_, e);
        App::instance().close();
        return true;
      }
      default: {
        return false;
      }
    }
  }

  bool EngineLayer::onAppEvent(AppEvent& e) {
    switch (e.type()) {
      case AppEventType::RenderStart: {
        vao_ = VertexArray::create(
          // Vertices
          {-.5, -.5,  0., /**/ .9, .9, .9, 1.,
            .5, -.5,  0., /**/ .9, .9, .9, 1.,
            0.,  .5,  0., /**/ .9, .9, .9, 1.},
          // Layout
          {{ShaderDataType::Float3, "pos"},
           {ShaderDataType::Float4, "color"}},
          // Indices
          {0, 1, 2}
        );

        vaoSqr_ = VertexArray::create(
          // Vertices
          {-.75, -.75, .1, /**/ .9, .1, .1, 1.,
            .75, -.75, .1, /**/ .1, .9, .1, 1.,
            .75,  .75, .1, /**/ .1, .1, .9, 1.,
           -.75,  .75, .1, /**/ .9, .9, .1, 1.},
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
      case AppEventType::RenderUpdate: {  
        auto gl{gladGetGLContext()};
        gl->ClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
        gl->Clear(GL_COLOR_BUFFER_BIT);
        
        shader_->bind();
        
        vaoSqr_->bind();
        gl->DrawElements(GL_TRIANGLES, vaoSqr_->indexCount(), GL_UNSIGNED_INT, nullptr);
        vaoSqr_->unbind();

        vao_->bind();
        gl->DrawElements(GL_TRIANGLES, vao_->indexCount(), GL_UNSIGNED_INT, nullptr);
        vao_->unbind();
      
        shader_->unbind();

        App::instance().window().context().swapBuffers();
        return false;
      }
      case AppEventType::MainUpdate: {
        App::instance().window().pollEvents();
      }
      default: {
        return false;
      }
    }
  }

  bool EngineLayer::onKeyboardEvent(KeyboardEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (Input::isPressed(Key::Enter) && Input::isPressed(Key::LeftAlt)) {
      FGE_DEBUG_ENG("{0}: Fullscreen({1})", name_, !App::instance().window().isFullscreen());
      App::instance().window().setFullscreen(!App::instance().window().isFullscreen());
    }
    return true;
  }

  bool EngineLayer::onMouseEvent(MouseEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    // custom dragging and close button
    if (App::instance().window().isUsingCustomDecor()) {
      pollCustomDecor(e);
    }
    return true;
  }

  bool EngineLayer::onCursorEvent(CursorEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    if (draggingWindowDecor_) {
      App::instance().window().dragWindow(windowDragOffset_);
    }
    
    return true;
  }

  bool EngineLayer::onScrollEvent(ScrollEvent& e) {
    //FGE_DEBUG_ENG("{0} [Thread: {1}]", e, threadNames_.at(std::this_thread::get_id()));
    
    return true;
  }
  void EngineLayer::pollCustomDecor(MouseEvent& e) {
    if (App::instance().window().isFullscreen()) {
      draggingWindowDecor_ = false;
      closingWindowDecor_ = false;
      return;
    }
    if (e.button() == Mouse::Left) {
      if (e.buttonState() == Mouse::Pressed
        && Input::cursorPos().y < 50 && Input::cursorPos().x < (App::instance().window().dims().x - 50)) {
        draggingWindowDecor_ = true;
        windowDragOffset_ = {glm::floor(Input::cursorPos().x), glm::floor(Input::cursorPos().y)};
      } else {
        draggingWindowDecor_ = false;
      }
      if (closingWindowDecor_ && e.buttonState() == Mouse::Released
        && Input::cursorPos().y < 50 && Input::cursorPos().x >= (App::instance().window().dims().x - 50)) {
        App::instance().close();
      }
      if (e.buttonState() == Mouse::Pressed
        && Input::cursorPos().y < 50 && Input::cursorPos().x >= (App::instance().window().dims().x - 50)) {
        closingWindowDecor_ = true;
      } else {
        closingWindowDecor_ = false;
      }
    }
  }
}