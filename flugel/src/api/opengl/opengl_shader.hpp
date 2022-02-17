#pragma once

#include "core/renderer/shader.hpp"

namespace fge {
  class OpenGLShader : public Shader {
  public:
    explicit OpenGLShader(const std::string& shaderFilePath);
    OpenGLShader(const std::string& vertSrc, const std::string& fragSrc);
    ~OpenGLShader() override;

    void bind() const override;
    void unbind() const override;
  private:
    u32 shaderId_{};

    void init(const std::string& vertSrc, const std::string& fragSrc);
    std::unordered_map<Shader::Type, std::string> parseFile(const std::string& shaderFilePath) final;
  };
}