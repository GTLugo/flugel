#pragma once

#include "core/renderer/shader.hpp"

namespace fge {
  class OpenGLShader : public Shader {
  public:
    OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
    virtual ~OpenGLShader();

    virtual void bind() const;
    virtual void unbind() const;
  private:
    u32 shaderId_;
  };
}