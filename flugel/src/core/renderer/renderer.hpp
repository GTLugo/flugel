#pragma once

namespace fge {

  class Renderer {
  public:
    enum API {
      None = 0,
      OpenGL,
      Vulkan,
      D3D11,
    };

    static API api() { return renderingAPI_s; }
    static void setApi(API api) { renderingAPI_s = api; }
  private:
    static API renderingAPI_s;
  };
}