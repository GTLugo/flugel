//
// Created by galex on 2/17/2022.
//

#include "opengl_render_dispatcher.hpp"

#include "core/app.hpp"

#include <glad/gl.h>

namespace ff {
  void OpenGLRenderDispatcher::clear(Color color) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->ClearColor(color.r, color.g, color.b, color.a);
    gl->Clear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRenderDispatcher::draw(const Shared<VertexArray>& vertexArray) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->DrawElements(GL_TRIANGLES, vertexArray->indexCount(), GL_UNSIGNED_INT, nullptr);
  }

  void OpenGLRenderDispatcher::setDepthTest(bool enabled) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    if (enabled) {
      gl->Enable(GL_DEPTH_TEST);
    } else {
      gl->Disable(GL_DEPTH_TEST);
    }
  }
}