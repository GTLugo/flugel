//
// Created by galex on 2/17/2022.
//

#pragma once

#include "util/color/color.hpp"
#include "core/renderer/vertex_array/vertex_array.hpp"

namespace fge {
  class RenderDispatcher {
  public:
    virtual void clear(Color color) = 0;
    virtual void draw(const Shared<VertexArray>& vertexArray) = 0;
  };
}

