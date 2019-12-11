#ifndef VERTEX_ARRAY_HPP_INCLUDED
#define VERTEX_ARRAY_HPP_INCLUDED

#include <GL/glew.h>
#include <cstdint>
#include <vector>
#include <iostream>



class buffer {
public:
    using native_handle_type = GLuint;
    using buffer_type_type = GLenum;
    using draw_type_type = GLenum;
    buffer() : m_handle(0) {}
    buffer(native_handle_type handle) : m_handle(handle) {}
    buffer(const buffer && o) = delete;
    buffer(buffer && o) : m_handle(o.m_handle) {
        o.m_handle = 0;
    }
    buffer & operator=(const buffer && o) = delete;
    buffer & operator=(buffer && o){
        m_handle = o.m_handle;
        o.m_handle = 0;
        return *this;
    }
    buffer(const void * data, std::size_t size, buffer_type_type buffer_type, draw_type_type draw_type) 
    : m_handle(0) {
        glCreateBuffers(1, &m_handle);
        if (!m_handle)
            return;
        glBindBuffer(buffer_type, m_handle);
        glBufferData(buffer_type, size, data, draw_type);
    }
    ~buffer() {
        reset();
    }
    void reset(native_handle_type handle = 0) {
        if (m_handle)
            glDeleteBuffers(1, &m_handle);
        m_handle = handle;
    }
    native_handle_type native_handle() const {
        return m_handle;
    }
    operator bool() const {
        return m_handle;
    }
    void bind(buffer_type_type type) {
        glBindBuffer(type, m_handle);
    }
    native_handle_type get() const {
        return m_handle;
    }
private:
    native_handle_type m_handle;
};

class vertex_attribute {
public:
    using native_buffer_handle_type = GLuint;
    using size_type = GLint;
    using index_type = GLuint;
    using normalized_type = GLboolean;
    using type_type = GLenum;
    using stride_type = GLsizei;
    using pointer_type = const void *;
    vertex_attribute(): 
        m_enabled(false), 
        m_index(0), 
        m_size(0), 
        m_type(GL_FLOAT),
        m_normalized(GL_FALSE),
        m_offset(nullptr),
        m_buffer_handle(0) {}
    vertex_attribute(const vertex_attribute &) = default;
    vertex_attribute & operator =(const vertex_attribute &) = default;
    vertex_attribute & set_index(index_type index) {
        m_index = index;
        return *this;
    }
    vertex_attribute & set_enabled(bool enabled = true) {
        m_enabled = enabled;
        return *this;
    }
    vertex_attribute & set_normalized(bool normalized = true) {
        m_normalized = normalized ? GL_TRUE : GL_FALSE;
        return *this;
    }
    vertex_attribute & set_size(size_type size) {
        m_size = size;
        return *this;
    }
    vertex_attribute & set_type(type_type type) {
        m_type = type;
        return *this;
    }
    vertex_attribute & set_stride(stride_type stride) {
        m_stride = stride;
        return *this;
    }
    vertex_attribute & set_offset(std::uintptr_t offset) {
        m_offset = reinterpret_cast<void*>(offset);
        return *this;
    }
    vertex_attribute & set_offset_pointer(pointer_type pointer) {
        m_offset = pointer;
        return *this;
    }
    vertex_attribute & set_buffer_handle(native_buffer_handle_type buffer_handle) {
        m_buffer_handle = buffer_handle;
        return *this;
    }
    vertex_attribute & bind() {
        // glBindBuffer(GL_ARRAY_BUFFER, m_buffer_handle);
        // glVertexAttribPointer(m_index, m_size, m_type, m_normalized, m_stride, m_offset);
        // glEnableVertexAttribArray(m_index);
        return *this;
    }
    vertex_attribute & set_buffer(const buffer & the_buffer) {
        m_buffer_handle = the_buffer.native_handle();
        return *this;
    }
    native_buffer_handle_type buffer_handle() const {
        return m_buffer_handle;
    }
    bool is_enabled() const {
        return m_enabled;
    }
    size_type size() const {
        return m_size;
    }
    type_type type() const {
        return m_type;
    }
    bool is_normalized() const {
        return m_normalized;
    }
    normalized_type normalized() const {
        return m_normalized;
    }
    stride_type stride() const {
        return m_stride;
    }
    pointer_type offset_pointer() const {
        return m_offset;
    }
    std::uintptr_t offset() const {
        return reinterpret_cast<std::uintptr_t>(m_offset);
    }
    index_type index() {
        return m_index;
    }
private:
    bool m_enabled;
    index_type m_index;
    size_type m_size;
    type_type m_type;
    normalized_type m_normalized;
    stride_type m_stride;
    pointer_type m_offset;
    native_buffer_handle_type m_buffer_handle;
};

class vertex_array {
public:
using native_handle_type = GLuint;
    vertex_array() : m_handle(0) {}
    vertex_array(native_handle_type handle) : m_handle(handle) {}
    vertex_array(const vertex_array &) = delete;
    vertex_array(vertex_array && o) : m_handle(o.m_handle) {
        o.m_handle = 0;
    }
    vertex_array & operator=(const vertex_array &) = delete;
    vertex_array & operator=(vertex_array && o) {
        m_handle = o.m_handle;
        o.m_handle = 0;
    }
    void bind() { 
        glBindVertexArray(m_handle); 
    }
    void unbind() {
        glBindVertexArray(0);
    }
    native_handle_type native_handle() const {
        return m_handle;
    }
    bool is_valid() const {
        return m_handle;
    }
    operator bool() const {
        return m_handle;
    }
    void reset(native_handle_type handle = 0) {
        if (m_handle) {
            glDeleteVertexArrays(1, &m_handle);
        }
        m_handle = handle;
    }
    ~vertex_array() {
        reset();
    }
    native_handle_type get() const {
        return m_handle;
    }
private:
    native_handle_type m_handle;
};
class vertex_array_builder {
public:
    using attribute_list_type = std::vector<vertex_attribute>;
    using native_element_array_buffer_handle = GLuint;
    vertex_array_builder() : m_attributes(), m_element_array_buffer_handle(0) {}
    vertex_array_builder(const vertex_array_builder &) = default;
    vertex_array_builder(vertex_array_builder &&) = default;
    vertex_array_builder& operator=(vertex_array_builder &&) = default;
    vertex_array_builder& operator=(const vertex_array_builder &) = default;
    attribute_list_type & attributes() {
        return m_attributes;
    }
    const attribute_list_type & attributes() const {
        return m_attributes;
    }
    vertex_array_builder & push_vertex_attribute(vertex_attribute const & attribute) {
        m_attributes.push_back(attribute);
        return *this;
    }
    vertex_array_builder & clear_vertex_attribute() {
        m_attributes.clear();
        return *this;
    }
    vertex_array_builder & set_element_array_buffer_handle(native_element_array_buffer_handle handle = 0) {
        m_element_array_buffer_handle = handle;
        return *this;
    }
    vertex_array_builder & set_element_array_buffer(const buffer & the_buffer) {
        m_element_array_buffer_handle = the_buffer.native_handle();
        return *this;
    }
    vertex_array build() {
        vertex_array::native_handle_type vertex_array_handle;
        glCreateVertexArrays(1, &vertex_array_handle);
        if (!vertex_array_handle)
            return vertex_array();
        glBindVertexArray(vertex_array_handle);
        if (m_element_array_buffer_handle) {
            std::cout << "bind ebo" << std::endl;
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_element_array_buffer_handle);
        }
        for (auto & attribute : m_attributes) {
            std::cout << "build attribute.bind()" << std::endl;
            glBindBuffer(GL_ARRAY_BUFFER, attribute.buffer_handle());
            #define X(_x) #_x "= " << _x << std::endl
            std::cout
            << std::boolalpha
            << X(attribute.index())
            << X(attribute.size())
            << X(attribute.is_enabled())
            << X(attribute.is_normalized())
            << X(attribute.stride())
            << X(attribute.offset())
            ;

            glVertexAttribPointer(attribute.index(), attribute.size(), attribute.type(), attribute.normalized(), attribute.stride(),attribute.offset_pointer());
            glEnableVertexAttribArray(attribute.index());
            // or 
            glEnableVertexArrayAttrib(vertex_array_handle, attribute.index());
        }
        glBindVertexArray(0);
        return vertex_array(vertex_array_handle);
    }
private:
    attribute_list_type m_attributes;
    native_element_array_buffer_handle m_element_array_buffer_handle; // EBO
};

#endif // VERTEX_ARRAY_HPP_INCLUDED