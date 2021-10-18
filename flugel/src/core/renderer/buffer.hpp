#pragma once

namespace fge {
  class VertexBuffer {
  public:
    virtual ~VertexBuffer() {}

    // set vertex data?

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    static VertexBuffer* create(double* verts, uint32_t bitSize);
    static VertexBuffer* create(std::vector<vector3_t>& verts);
  };

  class IndexBuffer {
  public:
    virtual ~IndexBuffer() {}

    virtual void bind() const = 0;
    virtual void unbind() const = 0;

    virtual uint32_t count() const = 0;

    static IndexBuffer* create(uint32_t* indices, uint32_t count);
    static IndexBuffer* create(std::vector<uint32_t>& indices);
  };
}