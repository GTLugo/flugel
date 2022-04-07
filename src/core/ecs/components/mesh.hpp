//
// Created by galex on 4/3/2022.
//

#pragma once

#include "core/renderer/vertex_array/vertex_array.hpp"
#include "core/renderer/shader.hpp"

namespace ff {
  struct Mesh {
    // TODO: Overhaul mesh creation.


    Shared<VertexArray> vertexArray;
    Shared<Shader> shader;
  };
}

