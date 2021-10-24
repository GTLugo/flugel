
// https://www.khronos.org/opengl/wiki/Shader_Compilation
#include "opengl_shader.hpp"

#include <glad/gl.h>

namespace fge {
  OpenGLShader::OpenGLShader(const std::string& vertSrc, const std::string& fragSrc) {
    //auto gl{gladGetGLContext()};

    // Create an empty vertex shader handle
    uint32_t vertexShader = glCreateShader(GL_VERTEX_SHADER);

    // Send the vertex shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    const char* source = vertSrc.c_str();
    glShaderSource(vertexShader, 1, &source, 0);

    // Compile the vertex shader
    glCompileShader(vertexShader);

    int32_t isCompiled = 0;
    glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &isCompiled);
    if(!isCompiled) {
    	int32_t maxLength = 0;
    	glGetShaderiv(vertexShader, GL_INFO_LOG_LENGTH, &maxLength);

    	// The maxLength includes the NULL character
    	std::vector<char> infoLog(maxLength);
    	glGetShaderInfoLog(vertexShader, maxLength, &maxLength, &infoLog[0]);

    	// We don't need the shader anymore.
    	glDeleteShader(vertexShader);

    	// Use the infoLog as you see fit.
      FGE_ERROR_ENG("SHADER ERROR | {}", infoLog.data());
      FGE_ASSERT_ENG(false, "Failed to compile vertex shader!");

    	// In this simple program, we'll just leave
    	return;
    }

    // Create an empty fragment shader handle
    uint32_t fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);

    // Send the fragment shader source code to GL
    // Note that std::string's .c_str is NULL character terminated.
    source = fragSrc.c_str();
    glShaderSource(fragmentShader, 1, &source, 0);

    // Compile the fragment shader
    glCompileShader(fragmentShader);

    glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &isCompiled);
    if (!isCompiled) {
    	int32_t maxLength = 0;
    	glGetShaderiv(fragmentShader, GL_INFO_LOG_LENGTH, &maxLength);

    	// The maxLength includes the NULL character
    	std::vector<char> infoLog(maxLength);
    	glGetShaderInfoLog(fragmentShader, maxLength, &maxLength, &infoLog[0]);

    	// We don't need the shader anymore.
    	glDeleteShader(fragmentShader);
    	// Either of them. Don't leak shaders.
    	glDeleteShader(vertexShader);

    	// Use the infoLog as you see fit.
      FGE_ERROR_ENG("SHADER ERROR | {}", infoLog.data());
      FGE_ASSERT_ENG(false, "Failed to compile fragment shader!");

    	// In this simple program, we'll just leave
    	return;
    }

    // Vertex and fragment shaders are successfully compiled.
    // Now time to link them together into a program.
    // Get a program object.
    shaderId_ = glCreateProgram();

    // Attach our shaders to our program
    glAttachShader(shaderId_, vertexShader);
    glAttachShader(shaderId_, fragmentShader);

    // Link our program
    glLinkProgram(shaderId_);

    // Note the different functions here: glGetProgram* instead of glGetShader*.
    int32_t isLinked = 0;
    glGetProgramiv(shaderId_, GL_LINK_STATUS, (int *)&isLinked);
    if (!isLinked) {
    	int32_t maxLength = 0;
    	glGetProgramiv(shaderId_, GL_INFO_LOG_LENGTH, &maxLength);

    	// The maxLength includes the NULL character
    	std::vector<char> infoLog(maxLength);
    	glGetProgramInfoLog(shaderId_, maxLength, &maxLength, &infoLog[0]);

    	// We don't need the program anymore.
    	glDeleteProgram(shaderId_);
    	// Don't leak shaders either.
    	glDeleteShader(vertexShader);
    	glDeleteShader(fragmentShader);

    	// Use the infoLog as you see fit.
      FGE_ERROR_ENG("SHADER ERROR | {}", infoLog.data());
      FGE_ASSERT_ENG(false, "Failed to link shader!");

    	// In this simple program, we'll just leave
    	return;
    }

    // Always detach shaders after a successful link.
    glDetachShader(shaderId_, vertexShader);
    glDetachShader(shaderId_, fragmentShader);
  }

  OpenGLShader::~OpenGLShader() {
    //auto gl = gladGetGLContext();
    glDeleteProgram(shaderId_);
  }

  void OpenGLShader::bind() const {
    //auto gl = gladGetGLContext();
    glUseProgram(shaderId_);
  }

  void OpenGLShader::unbind() const {
    //auto gl = gladGetGLContext();
    glUseProgram(0);
  }
}