
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "opengl_shader.hpp"

#include "core/app.hpp"
#include <glad/gl.h>

namespace ff {
  OpenGLShader::OpenGLShader(const std::string &shaderFilePath) {
    auto sources = parseFile(shaderFilePath);
    init(sources[Shader::Vertex], sources[Shader::Fragment]);
  }

  OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc) {
    init(vertSrc, fragSrc);
  }

  void OpenGLShader::init(const std::string& vertSrc, const std::string& fragSrc) {
    auto gl{static_cast<GladGLContext*>(App::instance().window().context().nativeContext())};

    // Create an empty vertex shader handle
    u32 vertexShader{gl->CreateShader(GL_VERTEX_SHADER)};

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const char* source = vertSrc.c_str();
    gl->ShaderSource(vertexShader, 1, &source, nullptr);

    // Compile the vertex shader
    gl->CompileShader(vertexShader);

    i32 isCompiled = 0;
    gl->GetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled) {
      i32 maxLength = 0;
      gl->GetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      gl->DeleteShader(vertexShader);

      // Use the infoLog as you see fit.
      Log::debug_e("SHADER ERROR | {}", infoLog.data());
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
      i32 maxLength = 0;
      gl->GetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

      // The maxLength includes the NULL character
      std::vector<char> infoLog(maxLength);
      gl->GetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

      // We don't need the shader anymore.
      gl->DeleteShader(fragmentShader);
      // Either of them. Don't leak shaders.
      gl->DeleteShader(vertexShader);

      // Use the infoLog as you see fit.
      Log::debug_e("SHADER ERROR | {}", infoLog.data());
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
    i32 isLinked = 0;
    gl->GetProgramiv(shaderId_, GL_LINK_STATUS, (int *)&isLinked);
    if (!isLinked) {
      i32 maxLength = 0;
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