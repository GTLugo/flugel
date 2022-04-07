//
// Created by galex on 4/3/2022.
//

#include "render_system.hpp"

#include "core/app.hpp"

namespace ff {
  void RenderSystem::onUpdate() {
    auto& cameraEntity{App::instance().activeWorld()->masterCamera()};
    auto& camera{cameraEntity.getRef<Camera>()};

    for (auto& entity : entities) {
      auto& mesh{entity.getRef<Mesh>()};

      mesh.shader->pushMat4(camera.viewProjMatrix(), "vpMatrix");
      mesh.shader->bind();
      Renderer::submit(mesh.vertexArray);
      mesh.shader->unbind();
    }
  }
}