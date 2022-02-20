#pragma once

#define BUFFER_ELEMENT(type, name) fge::BufferElement{fge::BufferElement::dataTypeToShaderDataType<type>(), #name}

namespace fge {
  struct FGE_API BufferElement {
    enum class DataType {
      None = 0,
      Bool,
      Int, Int2, Int3, Int4,
      Float, Float2, Float3, Float4,
      Mat3, Mat4
    };

    DataType type;
    std::string name;
    u32 componentCount;
    u32 size;
    u32 offset;
    bool normalized;

    template<typename U>
    static inline BufferElement create(const std::string& name) {
      return {fge::BufferElement::dataTypeToShaderDataType<U>(), name};
    }

    BufferElement(DataType type = DataType::Float, std::string name = "buffer_element", bool normalized = false)
        : type{type},
          name{std::move(name)},
          componentCount{dataTypeComponentCount(type)},
          size{shaderDataTypeSize(type)},
          offset{0},
          normalized{normalized} {}

    template<typename U>
    static DataType dataTypeToShaderDataType() {
      if (typeid(U) == typeid(bool)) {
        return DataType::Bool;
      } else if (typeid(U) == typeid(int)) {
        return DataType::Int;
      } else if (typeid(U) == typeid(ivec2)) {
        return DataType::Int2;
      } else if (typeid(U) == typeid(ivec3)) {
        return DataType::Int3;
      } else if (typeid(U) == typeid(ivec4)) {
        return DataType::Int4;
      } else if (typeid(U) == typeid(vec2)) {
        return DataType::Float2;
      } else if (typeid(U) == typeid(vec3)) {
        return DataType::Float3;
      } else if (typeid(U) == typeid(vec4)) {
        return DataType::Float4;
      } else if (typeid(U) == typeid(mat3)) {
        return DataType::Mat3;
      } else if (typeid(U) == typeid(mat4)) {
        return DataType::Mat4;
      }
      FGE_ASSERT_ENG(false, "Failed to find supported buffer element data type!");
      return DataType::None;
    }

    static u32 dataTypeComponentCount(DataType type) {
      switch (type) {
        case DataType::Bool:   { return 1; }
        case DataType::Int:    { return 1; }
        case DataType::Int2:   { return 2; }
        case DataType::Int3:   { return 3; }
        case DataType::Int4:   { return 4; }
        case DataType::Float:  { return 1; }
        case DataType::Float2: { return 2; }
        case DataType::Float3: { return 3; }
        case DataType::Float4: { return 4; }
        case DataType::Mat3:   { return 3 * 3; }
        case DataType::Mat4:   { return 4 * 4; }
        default:               { return 0; }
      }
    }

    static u32 shaderDataTypeSize(DataType type) {
      switch (type) {
        case DataType::Bool:   { return sizeof(bool); }
        case DataType::Int:    { return sizeof(i32); }
        case DataType::Int2:   { return sizeof(i32) * 2; }
        case DataType::Int3:   { return sizeof(i32) * 3; }
        case DataType::Int4:   { return sizeof(i32) * 4; }
        case DataType::Float:  { return sizeof(float); }
        case DataType::Float2: { return sizeof(float) * 2; }
        case DataType::Float3: { return sizeof(float) * 3; }
        case DataType::Float4: { return sizeof(float) * 4; }
        case DataType::Mat3:   { return sizeof(float) * 3 * 3; }
        case DataType::Mat4:   { return sizeof(float) * 4 * 4; }
        default:               { return 0; }
      }
    }
  };

  class FGE_API BufferLayout {
  public:
    BufferLayout(const std::initializer_list<BufferElement>& elements = {{}})
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

  class FGE_API VertexBuffer {
  public:
    virtual ~VertexBuffer() = default;

    // set vertex data?
    // virtual u32 id() const = 0;
    [[nodiscard]] virtual const BufferLayout& layout() const = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static Shared<VertexBuffer> create(float* vertices, u32 bitSize);
    static Shared<VertexBuffer> create(std::vector<float>& vertices);
    static Shared<VertexBuffer> create(const std::initializer_list<float>& vertices);
  };

  class FGE_API IndexBuffer {
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