#pragma once

#include "core/renderer/shader.hpp"

namespace ff {
  class VulkanShader : public Shader {
  public:
    explicit VulkanShader(const std::string& shaderFilePath);
    ~VulkanShader() override;

    void bind() const override;
    void unbind() const override;

    void pushMat4(const mat4& matrix, const std::string& name) const override;
  private:
    u32 shaderId_{};

    void link(const std::unordered_map<Shader::Type, std::string>& sources);
    u32 compile(const std::string& src, Shader::Type shaderType);
    std::unordered_map<Shader::Type, std::string> parseFile(const std::string& shaderFilePath) override {
      return {};
    }
  };
}