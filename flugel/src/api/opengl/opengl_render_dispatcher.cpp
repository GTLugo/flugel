//
// Created by galex on 2/17/2022.
//

#include "opengl_render_dispatcher.hpp"

#include <glad/gl.h>

namespace fge {
  void OpenGLRenderDispatcher::clear(Color color) {
    //auto gl{gladGetGLContext()};
    glClearColor(color.r, color.g, color.b, color.a);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  }

  void OpenGLRenderDispatcher::draw(const Shared<VertexArray>& vertexArray) {
    //auto gl{gladGetGLContext()};
    glDrawElements(GL_TRIANGLES, vertexArray->indexCount(), GL_UNSIGNED_INT, nullptr);
  }
}