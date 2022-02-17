#pragma once

#include "core/renderer/shader.hpp"

namespace fge {
  class OpenGLShader : public Shader {
  public:
    OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
    ~OpenGLShader() override;

    void bind() const override;
    void unbind() const override;
  private:
    u32 shaderId_;
  };
}