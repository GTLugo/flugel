
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "shader.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/opengl_shader.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace ff {
  Shared<Shader> Shader::create(const std::string& shaderFilePath) {
    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLShader>(shaderFilePath);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        return nullptr;
        #endif
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        return nullptr;
      }
    }
  }

  Shared<Shader> Shader::create(const std::string& vertSrc, const std::string& fragSrc) {
    if (vertSrc.empty() || fragSrc.empty()) {
      Log::debug_e("Failed to create shader! (Shader file *might* be empty, in which case this is expected)");
      return nullptr;
    }

    switch (Renderer::api()) {
      case Renderer::API::None: {
        FF_ASSERT_E(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::API::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLShader>(vertSrc, fragSrc);
        #else
        FF_ASSERT_E(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::API::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FF_ASSERT_E(false, "Vulkan not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "Vulkan not supported!");
        return nullptr;
        #endif
      }
      case Renderer::API::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FF_ASSERT_E(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FF_ASSERT_E(false, "D3D11 not supported!");
        return nullptr;
        #endif
      }
      default: {
        FF_ASSERT_E(false, "Unknown render api!");
        return nullptr;
      }
    }
  }

  std::string Shader::readFile(const std::string& shaderFilePath) {
    std::ifstream shaderFile{shaderFilePath};
    std::string fileContents;
    if (shaderFile.is_open()) {
      // get length of file
      shaderFile.seekg(0, std::ifstream::end);
      fileContents.resize(shaderFile.tellg());
      shaderFile.seekg(0, std::ifstream::beg);
      // read file
      shaderFile.read(&fileContents[0], fileContents.size());
    } else {
      Log::debug_e("Failed to open shader file \"{}\"", shaderFilePath);
    }
    return fileContents;
  }
}