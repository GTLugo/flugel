
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "opengl_shader.hpp"

#include <glad/gl.h>

namespace fge {
  OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc) {
    auto gl{gladGetGLContext()};

    // Create an empty vertex shader handle
    uint32_t vertexShader = gl->CreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const char* source = vertSrc.c_str();
    gl->ShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    gl->CompileShader(vertexShader);

    int32_t isCompiled = 0;
    gl->GetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled) {
    	int32_t maxLength = 0;
    	gl->GetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    	// The maxLength includes the NULL character
    	std::vector<char> infoLog(maxLength);
    	gl->GetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    	// We don't need the shader anymore.
    	gl->DeleteShader(vertexShader);

    	// Use the infoLog as you see fit.
      FGE_ERROR_ENG("SHADER ERROR | {}", infoLog.data());
      FGE_ASSERT_ENG(false, "Failed to compile vertex shader!");

    	// In this simple program, we'll just leave
    	return;
    }

    // Create an empty fragment shader handle
    uint32_t fragmentShader = gl->CreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = fragSrc.c_str();
    gl->ShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    gl->CompileShader(fragmentShader);

    gl->GetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
    	int32_t maxLength = 0;
    	gl->GetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    	// The maxLength includes the NULL character
    	std::vector<char> infoLog(maxLength);
    	gl->GetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    	// We don't need the shader anymore.
    	gl->DeleteShader(fragmentShader);
    	// Either of them. Don't leak shaders.
    	gl->DeleteShader(vertexShader);

    	// Use the infoLog as you see fit.
      FGE_ERROR_ENG("SHADER ERROR | {}", infoLog.data());
      FGE_ASSERT_ENG(false, "Failed to compile fragment shader!");

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
    int32_t isLinked = 0;
    gl->GetProgramiv(shaderId_, GL_LINK_STATUS, (int *)&isLinked);
    if (!isLinked) {
    	int32_t maxLength = 0;
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
      FGE_ERROR_ENG("SHADER ERROR | {}", infoLog.data());
      FGE_ASSERT_ENG(false, "Failed to link shader!");

    	// In this simple program, we'll just leave
    	return;
    }

    // Always detach shaders after a successful link.
    gl->DetachShader(shaderId_, vertexShader);
    gl->DetachShader(shaderId_, fragmentShader);
  }

  OpenGLShader::~OpenGLShader() {
    auto gl = gladGetGLContext();
    gl->DeleteProgram(shaderId_);
  }

  void OpenGLShader::bind() const {
    auto gl = gladGetGLContext();
    gl->UseProgram(shaderId_);
  }

  void OpenGLShader::unbind() const {
    auto gl = gladGetGLContext();
    gl->UseProgram(0);
  }
}