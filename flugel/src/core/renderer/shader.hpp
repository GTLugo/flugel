#pragma once

namespace fge {
  class Shader {
  public:
    Shader(const std::string& vertSrc, const std::string& fragSrc);
    virtual ~Shader();

    void bind() const;
    void unbind() const;
  private:
    uint32_t shaderId_;
  };
}