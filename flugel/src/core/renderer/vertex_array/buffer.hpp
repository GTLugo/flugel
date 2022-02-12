#pragma once

namespace fge {
  enum class ShaderDataType {
    None = 0,
    Bool,
    Int, Int2, Int3, Int4,
    Float, Float2, Float3, Float4,
    Mat3, Mat4
  };

<<<<<<< Updated upstream
  static uint32_t shaderDataTypeSize(ShaderDataType type) {
    switch (type) {
      case ShaderDataType::Bool:   { return sizeof(bool); }
      case ShaderDataType::Int:    { return sizeof(int32_t); }
      case ShaderDataType::Int2:   { return sizeof(int32_t) * 2; }
      case ShaderDataType::Int3:   { return sizeof(int32_t) * 3; }
      case ShaderDataType::Int4:   { return sizeof(int32_t) * 4; }
=======
  static u32 shaderDataTypeSize(ShaderDataType type) {
    switch (type) {
      case ShaderDataType::Bool:   { return sizeof(bool); }
      case ShaderDataType::Int:    { return sizeof(i32); }
      case ShaderDataType::Int2:   { return sizeof(i32) * 2; }
      case ShaderDataType::Int3:   { return sizeof(i32) * 3; }
      case ShaderDataType::Int4:   { return sizeof(i32) * 4; }
>>>>>>> Stashed changes
      case ShaderDataType::Float:  { return sizeof(float); }
      case ShaderDataType::Float2: { return sizeof(float) * 2; }
      case ShaderDataType::Float3: { return sizeof(float) * 3; }
      case ShaderDataType::Float4: { return sizeof(float) * 4; }
      case ShaderDataType::Mat3:   { return sizeof(float) * 3 * 3; }
      case ShaderDataType::Mat4:   { return sizeof(float) * 4 * 4; }
      default:                     { return 0; }
    }
  }

  struct BufferElement {
    ShaderDataType type;
    std::string name;
<<<<<<< Updated upstream
    uint32_t size;
    uint32_t offset;
=======
    u32 size;
    u32 offset;
>>>>>>> Stashed changes
    bool normalized;

    BufferElement(ShaderDataType type = ShaderDataType::Float,
                  const std::string& name = "buffer_element",
                  bool normalized = false)
      : type{type}, name{name}, size{shaderDataTypeSize(type)}, offset{0}, normalized{normalized} {}

<<<<<<< Updated upstream
    uint32_t componentCount() const {
=======
    u32 componentCount() const {
>>>>>>> Stashed changes
      switch (type) {
        case ShaderDataType::Bool:   { return 1; }
        case ShaderDataType::Int:    { return 1; }
        case ShaderDataType::Int2:   { return 2; }
        case ShaderDataType::Int3:   { return 3; }
        case ShaderDataType::Int4:   { return 4; }
        case ShaderDataType::Float:  { return 1; }
        case ShaderDataType::Float2: { return 2; }
        case ShaderDataType::Float3: { return 3; }
        case ShaderDataType::Float4: { return 4; }
        case ShaderDataType::Mat3:   { return 3 * 3; }
        case ShaderDataType::Mat4:   { return 4 * 4; }
        default:                     { return 0; }
      }
    }
  };

  class BufferLayout {
  public:
    BufferLayout(const std::initializer_list<BufferElement>& elements = {{}})
      : elements_{elements} {
      calculateOffsetAndStride();
    }

    const std::vector<BufferElement>& elements() const { return elements_; }
<<<<<<< Updated upstream
    const uint32_t stride() const { return stride_; }
=======
    const u32 stride() const { return stride_; }
>>>>>>> Stashed changes

    std::vector<BufferElement>::iterator begin() { return elements_.begin(); }
    std::vector<BufferElement>::iterator end()   { return elements_.end(); }
    std::vector<BufferElement>::const_iterator begin() const { return elements_.begin(); }
    std::vector<BufferElement>::const_iterator end()   const { return elements_.end(); }
  private:
    std::vector<BufferElement> elements_;
<<<<<<< Updated upstream
    uint32_t stride_{0};

    void calculateOffsetAndStride() {
      uint32_t offset = 0;
=======
    u32 stride_{0};

    void calculateOffsetAndStride() {
      u32 offset = 0;
>>>>>>> Stashed changes
      for (auto& e : elements_) {
        e.offset = offset;
        offset += e.size;
      }
      stride_ = offset;
    }
  };

  class VertexBuffer {
  public:
    virtual ~VertexBuffer() {}

    // set vertex data?
<<<<<<< Updated upstream
    // virtual uint32_t id() const = 0;
=======
    // virtual u32 id() const = 0;
>>>>>>> Stashed changes
    virtual const BufferLayout& layout() const = 0;
    virtual void setLayout(const BufferLayout& layout) = 0;

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

<<<<<<< Updated upstream
    static Shared<VertexBuffer> create(float* vertices, uint32_t bitSize);
=======
    static Shared<VertexBuffer> create(float* vertices, u32 bitSize);
>>>>>>> Stashed changes
    static Shared<VertexBuffer> create(std::vector<float>& vertices);
    static Shared<VertexBuffer> create(const std::initializer_list<float>& vertices);
  };

  class IndexBuffer {
  public:
    virtual ~IndexBuffer() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

<<<<<<< Updated upstream
    virtual uint32_t count() const = 0;

    static Shared<IndexBuffer> create(uint32_t* indices, uint32_t count);
    static Shared<IndexBuffer> create(std::vector<uint32_t>& indices);
    static Shared<IndexBuffer> create(const std::initializer_list<uint32_t>& indices);
=======
    virtual u32 count() const = 0;

    static Shared<IndexBuffer> create(u32* indices, u32 count);
    static Shared<IndexBuffer> create(std::vector<u32>& indices);
    static Shared<IndexBuffer> create(const std::initializer_list<u32>& indices);
>>>>>>> Stashed changes
  };
}