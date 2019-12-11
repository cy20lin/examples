#ifndef TEXTURE_RENDERER_HPP_INCLUDED
#define TEXTURE_RENDERER_HPP_INCLUDED
#include <GL/glew.h>
#include <iostream>
#include "shader_program.hpp"
#include "vertex_array.hpp"

class texture_renderer
{
public:
  using texture_type = GLuint;
  texture_renderer(texture_type texture = 0) : m_texture(texture)
  {
    setup_buffer2();
    setup_shader();
  }
  void setup_shader()
  {
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "layout (location = 1) in vec2 aTexCoord;\n"
                                     "out vec2 TexCoord;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "   TexCoord = aTexCoord;\n"
                                     "}";
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "in vec2 TexCoord;\n"
                                       "out vec4 FragColor;\n"
                                       "uniform sampler2D ourTexture;\n"
                                       "void main()\n"
                                       "{\n"
                                      //  "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "   FragColor = texture(ourTexture, TexCoord);\n"
                                       "}\n";
    // build and compile our shader program
    // ------------------------------------
    // vertex shader
    shader_builder vertex_shader_builder;
    shader vertex_shader =
        vertex_shader_builder.set_shader_type(GL_VERTEX_SHADER).set_source_code(vertexShaderSource).build();
    if (!vertex_shader_builder.is_success())
    {
      std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << vertex_shader_builder.message() << std::endl;
    }
    shader_builder fragment_shader_builder;
    shader fragment_shader =
        fragment_shader_builder.set_shader_type(GL_FRAGMENT_SHADER).set_source_code(fragmentShaderSource).build();
    if (!fragment_shader_builder.is_success())
    {
      std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << vertex_shader_builder.message() << std::endl;
    }
    m_program = shader_program_builder().attach_shader(vertex_shader).attach_shader(fragment_shader).build();
    m_program.use().set_uniform_int("ourTexture", 0);  // TEXTURE0
  }
  void setup_buffer()
  {
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
      0, -0.5f, -0.5f, 0.0f, 0., 0.,   // left-buttom
      0, +0.5f, -0.5f, 0.0f, 1., 0.,   // right-buttom
      0, -0.5f, +0.5f, 0.0f, 0., 1.,  // left-top
      0, +0.5f, +0.5f, 0.0f, 1, 1  // right-top
    };
    unsigned int indics[] = { 0, 1, 2, 1, 2, 3 };
    m_vbo = buffer(vertices, sizeof(vertices), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    m_ebo = buffer(indics, sizeof(indics), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    std::cout << "ebo : " << m_ebo.native_handle() << std::endl;
    // GLuint vao;
    // glCreateVertexArrays(1, &vao);
    // glBindVertexArray(vao);
    // // m_ebo.bind(GL_ELEMENT_ARRAY_BUFFER);
    // // m_vbo.bind(GL_ARRAY_BUFFER);
    // glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ebo.native_handle());
    // glBindBuffer(GL_ARRAY_BUFFER, m_vbo.native_handle());
    // glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
    //                       reinterpret_cast<void*>(static_cast<std::uintptr_t>(1 * sizeof(float))));
    // // glEnableVertexArrayAttrib(vao, 0);
    // glBindBuffer(GL_ARRAY_BUFFER, m_vbo.native_handle());
    // glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float),
    //                       reinterpret_cast<void*>(static_cast<std::uintptr_t>(4 * sizeof(float))));
    // // glEnableVertexArrayAttrib(vao, 1);

    // // glBindVertexArray(vao);
    // glEnableVertexAttribArray(0);
    // // glBindVertexArray(vao);
    // glEnableVertexAttribArray(1);
    // glBindVertexArray(0);
    // m_vao.reset(vao);
    m_vao = vertex_array_builder{}
                .push_vertex_attribute(vertex_attribute{}
                                           .set_buffer(m_vbo)
                                           .set_enabled(true)
                                           .set_index(0)
                                           .set_size(3)
                                           .set_normalized(false)
                                           .set_stride(6 * sizeof(float))
                                           .set_offset(1 * sizeof(float)))
                .push_vertex_attribute(vertex_attribute{}
                                           .set_buffer(m_vbo)
                                           .set_enabled(true)
                                           .set_index(1)
                                           .set_size(2)
                                           .set_normalized(false)
                                           .set_stride(6 * sizeof(float))
                                           .set_offset(4 * sizeof(float)))
                .set_element_array_buffer(m_ebo)
                .build();
  }

  void setup_buffer2()
  {
    // m_vbo = buffer(vertics() ,sizeof(vertics()), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    float vertics[] = {
      -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,  // bottom left
      +0.5f, -0.5,  0.0f, 1.0f, 0.0f,  // bottom right
      -0.5f, +0.5f, 0.0f, 0.0f, 1.0f,  // top left
      +0.5f, +0.5f, 0.0f, 1.0f, 1.0f,  // top right
    };
    m_vbo = buffer(vertics, sizeof(vertics), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    // m_ebo = buffer(vertics() ,sizeof(indics()), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    unsigned int indics[] = { 0, 1, 2, 1, 2, 3 };
    m_ebo = buffer(indics, sizeof(indics), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    m_vao = vertex_array_builder{}
                .push_vertex_attribute(vertex_attribute{}
                                           .set_buffer(m_vbo)
                                           .set_enabled(true)
                                           .set_index(0)
                                           .set_size(3)
                                           .set_type(GL_FLOAT)
                                           .set_normalized(false)
                                           .set_stride(5 * sizeof(float))
                                           .set_offset(0))
                .push_vertex_attribute(vertex_attribute{}
                                           .set_buffer(m_vbo)
                                           .set_enabled(true)
                                           .set_index(1)
                                           .set_size(2)
                                           .set_type(GL_FLOAT)
                                           .set_normalized(false)
                                           .set_stride(5 * sizeof(float))
                                           .set_offset(3 * sizeof(float)))
                .set_element_array_buffer(m_ebo)
                .build();
  }
  void render()
  {
    m_program.use();
    m_vao.bind();
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
  void set_texture(texture_type texture)
  {
    m_texture = texture;
  }
  texture_type texture()
  {
    return m_texture;
  }

private:
  texture_type m_texture;
  vertex_array m_vao;
  buffer m_vbo;
  buffer m_ebo;
  shader_program m_program;
};
#endif  // TEXTURE_RENDERER_HPP_INCLUDED