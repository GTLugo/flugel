#pragma once

#define BUFFER_ELEMENT(type, name) fge::BufferElement{fge::BufferElement::dataTypeToShaderDataType<type>(), #name}

namespace ff {
  struct BufferElement {
    enum class Type {
      None = 0,
      Bool,
      Int, Int2, Int3, Int4,
      Float, Float2, Float3, Float4,
      Mat3, Mat4
    };

    Type type{Type::Float};
    std::string name{"unnamed_buffer_element"};
    u32 componentCount{1};
    u32 size{sizeof(float)};
    u32 offset{0};
    bool normalized{false};

    template<typename T>
    static BufferElement create(std::string name_, bool normalized_ = false) {
      FF_ASSERT_E(false, "Unsupported buffer element data type!");
      return {.name = std::move(name_), .normalized = normalized_};
    }

    template<>
    BufferElement create<bool>(std::string name_, bool normalized_) {
      return {
          .type = Type::Bool,
          .name = std::move(name_),
          .componentCount = 1,
          .size = sizeof(bool),
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<int>(std::string name_, bool normalized_) {
      return {
        .type = Type::Int,
        .name = std::move(name_),
        .componentCount = 1,
        .size = sizeof(int),
        .offset = 0,
        .normalized = normalized_
      };
    }

    template<>
    BufferElement create<ivec2>(std::string name_, bool normalized_) {
      return {
          .type = Type::Int2,
          .name = std::move(name_),
          .componentCount = 2,
          .size = sizeof(int) * 2,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<ivec3>(std::string name_, bool normalized_) {
      return {
          .type = Type::Int3,
          .name = std::move(name_),
          .componentCount = 3,
          .size = sizeof(int) * 3,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<ivec4>(std::string name_, bool normalized_) {
      return {
          .type = Type::Int4,
          .name = std::move(name_),
          .componentCount = 4,
          .size = sizeof(int) * 4,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<float>(std::string name_, bool normalized_) {
      return {
          .type = Type::Float,
          .name = std::move(name_),
          .componentCount = 1,
          .size = sizeof(float),
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<vec2>(std::string name_, bool normalized_) {
      return {
          .type = Type::Float2,
          .name = std::move(name_),
          .componentCount = 2,
          .size = sizeof(float) * 2,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<vec3>(std::string name_, bool normalized_) {
      return {
          .type = Type::Float3,
          .name = std::move(name_),
          .componentCount = 3,
          .size = sizeof(float) * 3,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<vec4>(std::string name_, bool normalized_) {
      return {
          .type = Type::Float4,
          .name = std::move(name_),
          .componentCount = 4,
          .size = sizeof(float) * 4,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<mat3>(std::string name_, bool normalized_) {
      return {
          .type = Type::Mat3,
          .name = std::move(name_),
          .componentCount = 3 * 3,
          .size = sizeof(float) * 3 * 3,
          .offset = 0,
          .normalized = normalized_
      };
    }

    template<>
    BufferElement create<mat4>(std::string name_, bool normalized_) {
      return {
          .type = Type::Mat4,
          .name = std::move(name_),
          .componentCount = 4 * 4,
          .size = sizeof(float) * 4 * 4,
          .offset = 0,
          .normalized = normalized_
      };
    }
  };

  class VertexBufferLayout {
  public:
    VertexBufferLayout(const std::initializer_list<BufferElement>& elements = {{}})
      : elements_{elements} {
      calculateOffsetAndStride();
    }

    [[nodiscard]] const std::vector<BufferElement>& elements() const { return elements_; }
    [[nodiscard]] u32 stride() const { return stride_; }

    [[nodiscard]] std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
    [[nodiscard]] std::vector<BufferElement>::iterator end()   { return elements_.end(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
    [[nodiscard]] std::vector<BufferElement>::const_iterator end()   const { return elements_.end(); }
  private:
    std::vector<BufferElement> elements_;
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