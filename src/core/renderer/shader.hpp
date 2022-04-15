#pragma once

namespace ff {
  class Shader {
  public:
    enum Type {
      Vertex,
      Fragment
    };

    virtual ~Shader() = default;

    static Shared<Shader> create(const std::string& shaderFilePath);

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual void pushMat4(const mat4& matrix, const std::string& name) const = 0;
  protected:
    static inline const std::string preprocessorToken{"#type"};
    static inline std::unordered_map<std::string, Shader::Type> types{
        {"vertex"  , Type::Vertex  },
        {"fragment", Type::Fragment}
    };
    static inline std::unordered_map<Shader::Type, std::string> names{
        {Type::Vertex  , "vertex"  },
        {Type::Fragment, "fragment"}
    };

    static std::string readFile(const std::string& shaderFilePath);
    virtual std::unordered_map<Shader::Type, std::string> parseFile(const std::string& shaderFilePath) = 0;
  };
}