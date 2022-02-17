#pragma once

namespace fge {
  class Shader {
  public:
    enum Type {
      Vertex,
      Fragment
    };

    virtual ~Shader() = default;

    static Shared<Shader> create(const std::string& shaderFilePath);
    static Shared<Shader> create(const std::string& vertSrc, const std::string& fragSrc);

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

  private:
    static inline const std::string preprocessorToken{"#type"};
    static inline std::unordered_map<std::string, Shader::Type> types{
        {"vertex", Type::Vertex},
        {"fragment", Type::Fragment},
        //{"compute", Type::Fragment}
    };

    static std::string readFile(const std::string& shaderFilePath);
    static std::unordered_map<Shader::Type, std::string> parseFile(const std::string& shaderFileSrc);

    };
}