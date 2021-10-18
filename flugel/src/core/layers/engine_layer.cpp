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
        // Vertex Array
        auto gl = gladGetGLContext();
        gl->GenVertexArrays(1, &vertexArray_);
        gl->BindVertexArray(vertexArray_);

        // Vertex Buffer
        std::vector<vector3_t> verts{
          {-.5, -.5,  0.},
          { .5, -.5,  0.},
          { 0.,  .5,  0.}
        };
        vertexBuffer_.reset(VertexBuffer::create(verts));
        //vertexBuffer_.bind();

        gl->EnableVertexAttribArray(0);
        gl->VertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(double) * 3, nullptr);

        // Index Buffer
        std::vector<uint32_t> indices{
          0, 1, 2
        };
        indexBuffer_.reset(IndexBuffer::create(indices.data(), indices.size()));
        //indexBuffer_.bind();

        std::string vertSrc = R"(
          #version 460 core

          layout (location = 0) in vec4 pos;

          out vec3 vertPos;

          void main() {
            vertPos = vec3(pos.x, pos.y, pos.z);
            gl_Position = pos;
          }
        )";

        std::string fragSrc = R"(
          #version 460 core

          in vec3 vertPos;

          layout (location = 0) out vec4 fragColor;

          void main() {
            fragColor = vec4(vertPos * 0.5 + 0.5, 1.0);
            //fragColor = vec4(0.94, 0.24, 0.18, 1.0);
          }
        )";

        shader_.reset(Shader::create(vertSrc, fragSrc));

        return false;
      }
      case AppEventType::RenderUpdate: {  
        auto gl = gladGetGLContext();
        gl->ClearColor(clearColor_.r, clearColor_.g, clearColor_.b, clearColor_.a);
        gl->Clear(GL_COLOR_BUFFER_BIT);
        
        shader_->bind();
        gl->BindVertexArray(vertexArray_);
        gl->DrawElements(GL_TRIANGLES, indexBuffer_->count(), GL_UNSIGNED_INT, nullptr);
        shader_->unbind();

        App::instance().window().context().swapBuffers();
        return false;
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