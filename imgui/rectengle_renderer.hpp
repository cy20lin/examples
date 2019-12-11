#ifndef RECTENGLE_RENDERER_HPP_INCLUDED
#define RECTENGLE_RENDERER_HPP_INCLUDED

#include <GL/glew.h>
#include <iostream>
#include "vertex_array.hpp"

class rectengle_renderer
{
  unsigned int VBO, VAO;
  bool m_is_setup;
  bool m_is_compiled;
  int shaderProgram;

public:
  rectengle_renderer() : m_is_setup(false), m_is_compiled(false)
  {
    build_and_compile_shader();
    setup_vertex();
  }
  ~rectengle_renderer()
  {
    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    if (m_is_setup)
    {
      glDeleteVertexArrays(1, &VAO);
      glDeleteBuffers(1, &VBO);
      m_is_setup = false;
    }
  }
  void render()
  {
    m_program.use();
    m_vao.bind();
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
  }
  void build_and_compile_shader()
  {
    if (m_is_compiled)
      return;
    const char* vertexShaderSource = "#version 330 core\n"
                                     "layout (location = 0) in vec3 aPos;\n"
                                     "void main()\n"
                                     "{\n"
                                     "   gl_Position = vec4(aPos, 1.0);\n"
                                     "}\0";
    const char* fragmentShaderSource = "#version 330 core\n"
                                       "out vec4 FragColor;\n"
                                       "void main()\n"
                                       "{\n"
                                       "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
                                       "}\n\0";
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
    m_program = shader_program_builder()
    .attach_shader(vertex_shader)
    .attach_shader(fragment_shader)
    .build();
    m_is_compiled = true;
  }
  void setup_vertex()
  {
    if (m_is_setup)
    {
      return;
    }
    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
    float vertices[] = {
      0,-0.5f, -0.5f, 0.0f, 1.,  // left-buttom
      0,0.5f,  -0.5f, 0.0f, 1.,// right-buttom
      0,-0.5f,  0.5f,  0.0f, 1.,  // left-top
      0,0.5f,  0.5f,  0.0f, 1.,  // right-top
    };
    unsigned int indics[] = {0,1,2,1,2,3};
    m_vbo = buffer(vertices, sizeof(vertices), GL_ARRAY_BUFFER, GL_STATIC_DRAW);
    m_ebo = buffer(indics, sizeof(indics), GL_ELEMENT_ARRAY_BUFFER, GL_STATIC_DRAW);
    std::cout << "ebo : " << m_ebo.native_handle() << std::endl;
    m_vao = vertex_array_builder{}
                .push_vertex_attribute(vertex_attribute{}
                                          .set_buffer(m_vbo)
                                          .set_enabled(true)
                                          .set_index(0)
                                          .set_size(3)
                                          .set_normalized(false)
                                          .set_stride(5 * sizeof(float))
                                          .set_offset(1 * sizeof(float)))
                .set_element_array_buffer(m_ebo)
                .build();
    m_is_setup = true;
  }
  buffer m_ebo;
  buffer m_vbo;
  vertex_array m_vao;
  shader_program m_program;
};
#endif