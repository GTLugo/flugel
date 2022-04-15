
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "vulkan_shader.hpp"

#include "core/app.hpp"

namespace ff {
  VulkanShader::VulkanShader(const std::string &shaderFilePath) {
    link({
        {Shader::Vertex, readFile(shaderFilePath + "_vertex.spv")},
        {Shader::Fragment, readFile(shaderFilePath + "_fragment.spv")},
    });
  }

  void VulkanShader::link(const std::unordered_map<Shader::Type, std::string>& sources) {

  }

  u32 VulkanShader::compile(const std::string& src, Shader::Type shaderType) {
    return -1;
  }

  VulkanShader::~VulkanShader() {
    
  }

  void VulkanShader::bind() const {
    
  }

  void VulkanShader::unbind() const {
    
  }

  void VulkanShader::pushMat4(const mat4& matrix, const std::string& name) const {
    
  }
}