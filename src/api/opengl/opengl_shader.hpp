#pragma once

#include "core/renderer/shader.hpp"

namespace ff {
  class OpenGLShader : public Shader {
  public:
    explicit OpenGLShader(const std::string& shaderFilePath);
    explicit OpenGLShader(const std::string& shaderFilePath, bool glsl);
    ~OpenGLShader() override;

    void bind() const override;
    void unbind() const override;

    void pushMat4(const mat4& matrix, const std::string& name) const override;
  private:
    u32 shaderId_{};

    u32 compileSpirv(const std::string& src, Shader::Type shaderType);
    void compileAndLinkSpirv(const std::unordered_map<Shader::Type, std::string>& sources);
    void compileAndLinkGlsl(const std::string& vertSrc, const std::string& fragSrc);
    std::unordered_map<Shader::Type, std::string> parseFile(const std::string& shaderFilePath) final;
  };
}