
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "shader.hpp"

#if defined(FLUGEL_USE_OPENGL)
  #include "api/opengl/opengl_shader.hpp"
#endif

#include "core/renderer/renderer.hpp"

namespace fge {
  Shared<Shader> Shader::create(const std::string& shaderFilePath) {
    auto sources = parseFile(readFile(shaderFilePath));
    return create(sources[Shader::Vertex], sources[Shader::Fragment]);
  }

  Shared<Shader> Shader::create(const std::string& vertSrc, const std::string& fragSrc) {
    if (vertSrc.empty() || fragSrc.empty()) {
      FGE_ERROR_ENG("Failed to create shader! (Shader file *might* be empty, in which case this is expected)");
      return nullptr;
    }

    switch (Renderer::api()) {
      case Renderer::None: {
        FGE_ASSERT_ENG(false, "Running with no API not implemented!");
        return nullptr;
      }
      case Renderer::OpenGL: {
        #if defined(FLUGEL_USE_OPENGL)
        return makeShared<OpenGLShader>(vertSrc, fragSrc);
        #else
        FGE_ASSERT_ENG(false, "OpenGL not supported!");
          return nullptr;
        #endif
      }
      case Renderer::Vulkan: {
        #if defined(FLUGEL_USE_VULKAN)
        FGE_ASSERT_ENG(false, "Vulkan not implemented!");
          return nullptr;
        #else
        FGE_ASSERT_ENG(false, "Vulkan not supported!");
        return nullptr;
        #endif
      }
      case Renderer::D3D11: {
        #if defined(FLUGEL_USE_D3D11)
        FGE_ASSERT_ENG(false, "D3D11 not implemented!");
          return nullptr;
        #else
        FGE_ASSERT_ENG(false, "D3D11 not supported!");
        return nullptr;
        #endif
      }
      default: {
        FGE_ASSERT_ENG(false, "Unknown render api!");
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
      FGE_ERROR_ENG("Failed to open shader file \"{}\"", shaderFilePath);
    }
    return fileContents;
  }

  std::unordered_map<Shader::Type, std::string> Shader::parseFile(const std::string& shaderFileSrc) {
    std::unordered_map<Shader::Type, std::string> srcs;

    std::stringstream shaderStream{shaderFileSrc};
    std::string nextWord;
    shaderStream >> nextWord;
    while (shaderStream) {
      std::stringstream outputStream;
      if (nextWord == preprocessorToken) {
        // Grab type of shader
        std::string type;
        shaderStream >> type;
        FGE_ASSERT_ENG(types.find(type) != types.end(), "Shader type \"", type, "\" is not supported!");
        // Loop through shader section body
        shaderStream >> nextWord;
        while (shaderStream && nextWord != preprocessorToken) {
          // If #version line, it's necessary to add a \n after the version line
          if (nextWord == "#version") {
            // add "#version" and version number
            for (i32 i{0}; shaderStream && i < 2; ++i) {
              outputStream << nextWord << ' ';
              shaderStream >> nextWord;
            }
            // check if "core" follows the version number, then add \n
            if (nextWord == "core") {
              outputStream << nextWord << '\n';
              shaderStream >> nextWord;
            } else {
              outputStream << '\n';
            }
          }
          // Add word normally
          outputStream << nextWord << ' ';
          shaderStream >> nextWord;
        }
        srcs[types[type]] = outputStream.str();
      }
    }

    return srcs;
  }
}