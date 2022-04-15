
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "opengl_shader.hpp"

#include "core/app.hpp"
#include <glad/gl.h>

namespace ff {
  OpenGLShader::OpenGLShader(const std::string &shaderFilePath) {
    compileAndLinkSpirv({
        {Shader::Vertex, readFile(shaderFilePath + "_vertex.spv")},
        {Shader::Fragment, readFile(shaderFilePath + "_fragment.spv")},
    });
  }

  OpenGLShader::OpenGLShader(const std::string &shaderFilePath, bool glsl) {
    auto sources = parseFile(shaderFilePath);
    compileAndLinkGlsl(sources[Shader::Vertex], sources[Shader::Fragment]);
  }

  u32 OpenGLShader::compileSpirv(const std::string& src, Shader::Type shaderType) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    i32 glShaderType;
    switch (shaderType) {
      case Shader::Vertex: {
        glShaderType = GL_VERTEX_SHADER;
        break;
      }
      case Shader::Fragment: {
        glShaderType = GL_FRAGMENT_SHADER;
        break;
      }
      default: { FF_ASSERT_E(false, "Unsupported/unknown shader type!"); }
    };

    // Create an empty shader handle
    u32 shader{gl->CreateShader(glShaderType)};
    gl->ShaderBinary(1, &shader, GL_SHADER_BINARY_FORMAT_SPIR_V, src.c_str(), static_cast<i32>(src.size()));
    gl->SpecializeShader(shader, "main", 0, nullptr, nullptr);

    i32 isCompiled{0};
    gl->GetShaderiv(shader, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled) {
      i32 maxLength{1};
      //gl->GetShaderiv(shader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetShaderInfoLog(shader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      gl->DeleteShader(shader);

      // Use the infoLog as you see fit.
      Log::error_e("SHADER ERROR | {}", infoLog.data());
      FF_ASSERT_E(false, "Failed to compile " + names[shaderType] + " shader!");

      // In this simple program, we'll just leave
      return -1;
    }

    return shader;
  }

  void OpenGLShader::compileAndLinkSpirv(const std::unordered_map<Shader::Type, std::string>& sources) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    u32 vert{compileSpirv(sources.at(Shader::Vertex), Shader::Vertex)};
    u32 frag{compileSpirv(sources.at(Shader::Fragment), Shader::Fragment)};

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    shaderId_ = gl->CreateProgram();

    // Attach our shaders to our program
    gl->AttachShader(shaderId_, vert);
    gl->AttachShader(shaderId_, frag);

    // Link our program
    gl->LinkProgram(shaderId_);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    i32 isLinked{0};
    gl->GetProgramiv(shaderId_, GL_LINK_STATUS, (int *)&isLinked);
    if (!isLinked) {
      i32 maxLength{1};
      gl->GetProgramiv(shaderId_, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetProgramInfoLog(shaderId_, maxLength, &maxLength, &infoLog[0]);

      // We don't need the program anymore.
      gl->DeleteProgram(shaderId_);
      // Don't leak shaders either.
      gl->DeleteShader(vert);
      gl->DeleteShader(frag);

      // Use the infoLog as you see fit.
      Log::debug_e("SHADER ERROR | {}", infoLog.data());
      FF_ASSERT_E(false, "Failed to link shaders!");

      // In this simple program, we'll just leave
      return;
    }

    // Always detach shaders after a successful link.
    gl->DetachShader(shaderId_, vert);
    gl->DetachShader(shaderId_, frag);
  }

  void OpenGLShader::compileAndLinkGlsl(const std::string& vertSrc, const std::string& fragSrc) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};

    // Create an empty vertex shader handle
    u32 vertexShader{gl->CreateShader(GL_VERTEX_SHADER)};

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const char* source{vertSrc.c_str()};
    gl->ShaderSource(vertexShader, 1, &source, nullptr);

    // Compile the vertex shader
    gl->CompileShader(vertexShader);

    i32 isCompiled{0};
    gl->GetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled) {
      i32 maxLength{1};
      //gl->GetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      gl->DeleteShader(vertexShader);

      // Use the infoLog as you see fit.
      Log::error_e("SHADER ERROR | {}", infoLog.data());
      FF_ASSERT_E(false, "Failed to compile vertex shader!");

      // In this simple program, we'll just leave
      return;
    }

    // Create an empty fragment shader handle
    u32 fragmentShader{gl->CreateShader(GL_FRAGMENT_SHADER)};

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = fragSrc.c_str();
    gl->ShaderSource(fragmentShader, 1, &source, nullptr);

    // Compile the fragment shader
    gl->CompileShader(fragmentShader);

    gl->GetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
      i32 maxLength{1};
      gl->GetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      gl->DeleteShader(fragmentShader);
      // Either of them. Don't leak shaders.
      gl->DeleteShader(vertexShader);

      // Use the infoLog as you see fit.
      Log::error_e("SHADER ERROR | {}", infoLog.data());
      FF_ASSERT_E(false, "Failed to compile fragment shader!");

      // In this simple program, we'll just leave
      return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    shaderId_ = gl->CreateProgram();

    // Attach our shaders to our program
    gl->AttachShader(shaderId_, vertexShader);
    gl->AttachShader(shaderId_, fragmentShader);

    // Link our program
    gl->LinkProgram(shaderId_);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    i32 isLinked{0};
    gl->GetProgramiv(shaderId_, GL_LINK_STATUS, (int *)&isLinked);
    if (!isLinked) {
      i32 maxLength{1};
      gl->GetProgramiv(shaderId_, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetProgramInfoLog(shaderId_, maxLength, &maxLength, &infoLog[0]);

      // We don't need the program anymore.
      gl->DeleteProgram(shaderId_);
      // Don't leak shaders either.
      gl->DeleteShader(vertexShader);
      gl->DeleteShader(fragmentShader);

      // Use the infoLog as you see fit.
      Log::debug_e("SHADER ERROR | {}", infoLog.data());
      FF_ASSERT_E(false, "Failed to link shader!");

      // In this simple program, we'll just leave
      return;
    }

    // Always detach shaders after a successful link.
    gl->DetachShader(shaderId_, vertexShader);
    gl->DetachShader(shaderId_, fragmentShader);
  }

  OpenGLShader::~OpenGLShader() {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->DeleteProgram(shaderId_);
  }

  void OpenGLShader::bind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->UseProgram(shaderId_);
  }

  void OpenGLShader::unbind() const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->UseProgram(0);
  }

  void OpenGLShader::pushMat4(const mat4& matrix, const std::string& name) const {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};
    gl->UseProgram(shaderId_);

    auto location{gl->GetUniformLocation(shaderId_, name.c_str())};
    FF_ASSERT_E(location >= 0, "Invalid uniform location!");
//    FF_ASSERT_E(location != GL_INVALID_INDEX, "Invalid uniform location!");
    gl->UniformMatrix4fv(location, 1, false, glm::value_ptr(matrix));
    gl->UseProgram(0);
  }

  std::unordered_map<Shader::Type, std::string> OpenGLShader::parseFile(const std::string& shaderFilePath) {
    Log::trace_e("Parsing \"{}\"", shaderFilePath);
    std::unordered_map<Shader::Type, std::string> srcs;

    std::ifstream shaderFile{shaderFilePath};
    std::string nextWord;
    shaderFile >> nextWord;
    while (shaderFile) {
      std::stringstream sectionStream;
      if (nextWord == preprocessorToken) {
        // Grab type of shader
        std::string type;
        shaderFile >> type;
        FF_ASSERT_E(types.find(type) != types.end(), "Shader type \"", type, "\" is not supported!");
        Log::trace_e("Building {} in \"{}\"", type, shaderFilePath);

        // Loop through shader section body
        shaderFile >> nextWord;
        while (shaderFile && nextWord != preprocessorToken) {
          // If a preprocessor line, it's necessary to add a \n after it, else add word normally
          if (nextWord[0] == '#') {
            char line[256];
            shaderFile.getline(&line[0], 256);
            sectionStream << nextWord << line << '\n';
          } else {
            sectionStream << nextWord << ' ';
          }
          shaderFile >> nextWord;
        }

        // add to result map
        srcs[types[type]] = sectionStream.str();
      }
    }

    return srcs;
  }
}