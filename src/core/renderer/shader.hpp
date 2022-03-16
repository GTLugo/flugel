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
    static Shared<Shader> create(const std::string& vertSrc, const std::string& fragSrc);

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

  protected:
    static inline const std::string preprocessorToken{"#type"};
    static inline std::unordered_map<std::string, Shader::Type> types{
        {"vertex", Type::Vertex},
        {"fragment", Type::Fragment},
        //{"compute", Type::Fragment}
    };

  private:
    static std::string readFile(const std::string& shaderFilePath);
    virtual std::unordered_map<Shader::Type, std::string> parseFile(const std::string& shaderFilePath) = 0;
  };
}