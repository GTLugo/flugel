#pragma once

#define BUFFER_ELEMENT(type, name) fge::BufferElement{fge::BufferElement::dataTypeToShaderDataType<type>(), #name}

namespace ff {
  struct VertexAttributeBase {
    enum class Type {
      None = 0,
      Bool,
      Int, Int2, Int3, Int4,
      Float, Float2, Float3, Float4,
      Mat3, Mat4
    };

    Type type{Type::Float};
    std::string name{"unnamed_attribute"};
    u32 componentCount{1};
    u32 size{sizeof(float)};
    u32 offset{0};
    bool normalized{false};
  };

  template<class T>
  struct VertexAttribute : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::None,
        .name = std::move(name_),
        .componentCount = 1,
        .size = sizeof(T),
        .offset = 0,
        .normalized = normalized_
    } {
      FF_ASSERT_E(false, "Unsupported vertex attribute data type!");
    }
  };

  template<>
  struct VertexAttribute<bool> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Bool,
        .name = std::move(name_),
        .componentCount = 1,
        .size = sizeof(bool),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<int> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Int,
        .name = std::move(name_),
        .componentCount = 1,
        .size = sizeof(int),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<ivec2> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Int2,
        .name = std::move(name_),
        .componentCount = 2,
        .size = sizeof(ivec2),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<ivec3> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Int3,
        .name = std::move(name_),
        .componentCount = 3,
        .size = sizeof(ivec3),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<ivec4> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Int4,
        .name = std::move(name_),
        .componentCount = 4,
        .size = sizeof(ivec4),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<float> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Float,
        .name = std::move(name_),
        .componentCount = 1,
        .size = sizeof(float),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<vec2> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Float2,
        .name = std::move(name_),
        .componentCount = 2,
        .size = sizeof(vec2),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<vec3> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Float3,
        .name = std::move(name_),
        .componentCount = 3,
        .size = sizeof(vec3),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<vec4> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Float4,
        .name = std::move(name_),
        .componentCount = 4,
        .size = sizeof(vec4),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<mat3> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Mat3,
        .name = std::move(name_),
        .componentCount = 3 * 3,
        .size = sizeof(mat3),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  template<>
  struct VertexAttribute<mat4> : public VertexAttributeBase {
    VertexAttribute(std::string name_, bool normalized_ = false): VertexAttributeBase{
        .type = Type::Mat4,
        .name = std::move(name_),
        .componentCount = 4 * 4,
        .size = sizeof(mat4),
        .offset = 0,
        .normalized = normalized_
    } {}
  };

  class VertexBufferLayout {
  public:
    VertexBufferLayout(const std::initializer_list<VertexAttributeBase>& elements = {{}})
      : elements_{elements} {
      calculateOffsetAndStride();
    }

    [[nodiscard]] const std::vector<VertexAttributeBase>& elements() const { return elements_; }
    [[nodiscard]] u32 stride() const { return stride_; }

    [[nodiscard]] std::vector<VertexAttributeBase>::iterator begin() { return elements_.begin(); }
    [[nodiscard]] std::vector<VertexAttributeBase>::iterator end()   { return elements_.end(); }
    [[nodiscard]] std::vector<VertexAttributeBase>::const_iterator begin() const { return elements_.begin(); }
    [[nodiscard]] std::vector<VertexAttributeBase>::const_iterator end()   const { return elements_.end(); }
  private:
    // Polymorphism is unnecessary, so this is stored as pure base class, not base class ptr
    std::vector<VertexAttributeBase> elements_;
    u32 stride_{0};

    void calculateOffsetAndStride() {
      u32 offset = 0;
      for (auto& e : elements_) {
        e.offset = offset;
        offset += e.size;
      }
      stride_ = offset;
    }
  };

  class VertexBuffer {
  public:
    virtual ~VertexBuffer() = default;

    // set vertex data?
    // virtual u32 id() const = 0;
    [[nodiscard]] virtual const VertexBufferLayout& layout() const = 0;
    virtual void setLayout(const VertexBufferLayout& layout) = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static Shared<VertexBuffer> create(float* vertices, u32 bitSize);
    static Shared<VertexBuffer> create(std::vector<float>& vertices);
    static Shared<VertexBuffer> create(const std::initializer_list<float>& vertices);
  };

  class IndexBuffer {
  public:
    virtual ~IndexBuffer() = default;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    [[nodiscard]] virtual u32 count() const = 0;

    static Shared<IndexBuffer> create(u32* indices, u32 count);
    static Shared<IndexBuffer> create(std::vector<u32>& indices);
    static Shared<IndexBuffer> create(const std::initializer_list<u32>& indices);
  };
}