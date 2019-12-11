#ifndef SHADER_PROGRAM_HPP_INCLUDED
#define SHADER_PROGRAM_HPP_INCLUDED

#include <string>
#include <utility> // std::move
#include <GL/glew.h>
#if __cplusplus < 201703L
#endif
#include <vector>
#include <iostream>

using native_shader_handle = GLuint;
using native_shader_program_handle = GLuint;

class shader {
public:
    friend class shader_builder;
    using native_handle_type = GLuint;
    shader() : m_handle(0) {}
    shader(native_handle_type handle) : m_handle(handle) {}
    shader(const shader &) = delete;
    shader(shader && a_shader): m_handle(a_shader.m_handle) {
        a_shader.m_handle = 0;
    }
    shader & operator=(const shader &) = delete;
    shader & operator=(shader && o) {
        m_handle = o.m_handle;
        o.m_handle = 0;
    }
    ~shader() {
        reset();
    }
    void reset(native_handle_type handle = 0) {
        if (is_valid()) {
            glDeleteShader(m_handle);
        }
        m_handle = handle;
    }
    bool is_valid() const {
        return m_handle;
    }
    native_handle_type native_handle() const {
        return m_handle;
    }
    native_handle_type get() const {
        return m_handle;
    }
protected:
    native_handle_type m_handle;
};

class shader_builder {
    using shader_type_type = GLenum;
public:
    shader_builder()
        : m_shader_type(0),
        m_is_shader_setted(false),
        m_is_create_sucess(false),
        m_is_compile_sucess(false),
        m_message(),
        m_source_code()
    {}
    shader_builder & set_source_code(std::string s) {
        m_source_code = std::move(s);
        return *this;
    }
    std::string source_code() {
        return m_source_code;
    }
    std::string message() {
        return m_message;
    }
    shader build() {
        // Create Shader
        // GL_VERTEX_SHADER
        int shader_handle = glCreateShader(m_shader_type);
        m_is_create_sucess = shader_handle != 0;
        if (!m_is_create_sucess) {
            return shader();
            // Maybe glGetError() ??
        }
        // Compile Shader
        const GLchar * source_code_list[1] = { m_source_code.c_str() };
        const GLint source_code_size_list[1] = { static_cast<GLint>(m_source_code.size()) };
        glShaderSource(shader_handle, 1, source_code_list, source_code_size_list);
        glCompileShader(shader_handle);

        // Compilation status check
        GLint success;
        glGetShaderiv(shader_handle, GL_COMPILE_STATUS, &success);
        m_is_compile_sucess = (success == GL_TRUE) ? true : false;

        // Compilation infomation log
        GLint length;
        glGetShaderiv(shader_handle, GL_INFO_LOG_LENGTH, &length);
        length = length > 0 ? length - 1 : 0; // decrease size for null-terminator
        m_message.resize(length);
        if (length > 0) {
#if __cplusplus >= 201703L 
            glGetShaderInfoLog(shader_handle, length, NULL, m_message.data());
#elif __cplusplus >= 201103L
            std::vector<char> buffer(length);
            glGetShaderInfoLog(shader_handle, length, NULL, buffer.data());
            std::copy(buffer.begin(), buffer.end(), m_message.begin());
#else
#error "Compiler under C++11 is not supported."
#endif
        }
        return shader(shader_handle);
    }
    shader_type_type shader_type() const {
        return m_shader_type;
    }
    shader_builder & set_shader_type(shader_type_type shader_type) {
        m_shader_type = shader_type;
        return *this;
    }
    bool is_success() {
        return m_is_create_sucess && m_is_compile_sucess;
    }
    std::string message() const {
        return m_message;
    }
    bool clear() {
        m_is_shader_setted = false;
        m_is_compile_sucess = false;
        m_is_create_sucess = false;
        m_message = "";
        m_source_code = "";
    }
private:
    shader_type_type m_shader_type;
    bool m_is_shader_setted;
    bool m_is_create_sucess;
    bool m_is_compile_sucess;
    std::string m_message;
    std::string m_source_code;
};

class shader_program {
    using native_handle_type = native_shader_program_handle;
    friend class shader_program_builder;
public:
    shader_program() : m_handle(0) {}
    shader_program(const shader_program && o) = delete;
    shader_program(native_handle_type handle) : m_handle(handle) {}
    shader_program(shader_program && o) : m_handle(o.m_handle) {
        o.m_handle = 0;
    }
    shader_program & operator=(shader_program const &) = delete;
    shader_program & operator=(shader_program && o) {
        m_handle = o.m_handle;
        o.m_handle = 0;
        return *this;
    }
    ~shader_program() {
        reset();
    }
    void operator()() const {
        if (m_handle)
            glUseProgram(m_handle);
    }
    shader_program & use() {
        if (m_handle)
            glUseProgram(m_handle);
        return *this;
    }
    shader_program & set_uniform_bool(const std::string & name, bool value) {
        if (!m_handle)
            return *this;
        glUniform1i(glGetUniformLocation(m_handle, name.c_str()), (int)value);
        return *this;
    }
    shader_program & set_uniform_int(const std::string & name, int value) {
        if (!m_handle)
            return *this;
        glUniform1i(glGetUniformLocation(m_handle, name.c_str()), value);
        return *this;
    }
    shader_program & set_uniform_float(const std::string & name, float value) {
        if (!m_handle)
            return *this;
        glUniform1i(glGetUniformLocation(m_handle, name.c_str()), value);
        return *this;
    }
    
    void reset(native_handle_type handle = 0) {
        if (m_handle) {
            glDeleteProgram(m_handle);
        }
        m_handle = handle;
    }
    native_handle_type native_handle() const {
        return m_handle;
    }
    bool is_valid() {
        return m_handle;
    }
    native_handle_type get() const {
        return m_handle;
    }
private:
    native_handle_type m_handle;
};

class shader_program_builder {
public:
    shader_program_builder() = default;
    shader_program_builder(shader_program_builder &&) = default;
    shader_program_builder(const shader_program_builder &) = default;
    shader_program_builder & attach_shader(const shader & a_shader) {
        m_shader_handle_list.push_back(a_shader.native_handle());
        return *this;
    }
    shader_program build() {
        native_shader_program_handle shader_program_handle;
        shader_program_handle = glCreateProgram();
        for (auto shader_handle : m_shader_handle_list) {
            glAttachShader(shader_program_handle, shader_handle);
        }
        glLinkProgram(shader_program_handle);

        // Linking status check
        GLint success;
        glGetProgramiv(shader_program_handle, GL_LINK_STATUS, &success);
        m_is_link_sucess = (success == GL_TRUE) ? true : false;

        // Linking infomation log
        GLint length;
        glGetProgramiv(shader_program_handle, GL_INFO_LOG_LENGTH, &length);
        length = length > 0 ? length - 1 : 0; // decrease size for null-terminator
        m_message.resize(length);
        if (length > 0) {
#if __cplusplus >= 201703L 
            glGetProgramInfoLog(shader_program_handle, length, NULL, m_message.data());
#elif __cplusplus >= 201103L
            std::vector<char> buffer(length);
            glGetProgramInfoLog(shader_program_handle, length, NULL, buffer.data());
            std::copy(buffer.begin(), buffer.end(), m_message.begin());
#else
#error "Compiler under C++11 is not supported."
#endif
        }
        return shader_program(shader_program_handle);
    }
    shader_program_builder & clear() {
        m_shader_handle_list.clear();
        return *this;
    }
    std::string message() const {
        return m_message;
    }
private:
    bool m_is_create_sucess;
    bool m_is_link_sucess;
    std::vector<native_shader_handle> m_shader_handle_list;
    std::string m_message;
};
#endif // SHADER_PROGRAM_HPP_INCLUDED