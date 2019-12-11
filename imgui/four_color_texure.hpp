#ifndef FOUR_COLOR_TEXTURE_HPP_INCLUDED
#define FOUR_COLOR_TEXTURE_HPP_INCLUDED
#include <GL/glew.h>
#include <cstdint>

class four_color_texure
{
  public:
  using texture_type = GLuint;
  std::uint8_t m_rgba_color_data[4 * sizeof(std::uint32_t)];
  texture_type m_texture;
  four_color_texure(four_color_texure && o) : m_texture(o.m_texture) {
    o.m_texture = 0;
  }
  four_color_texure(std::uint32_t top_left_rgba_color = 0xf65314ff, std::uint32_t top_right_rgba_color = 0x00a1f1ff,
                    std::uint32_t buttom_left_rgba_color = 0x7cbb00ff,
                    std::uint32_t buttom_right_rgba_color = 0xffbb00ff)
    : m_rgba_color_data{ std::uint8_t((buttom_left_rgba_color >> (8 * 3)) & 0xff),  std::uint8_t((buttom_left_rgba_color >> (8 * 2)) & 0xff),
                         std::uint8_t((buttom_left_rgba_color >> (8 * 1)) & 0xff),  std::uint8_t((buttom_left_rgba_color >> (8 * 0)) & 0xff),
                         std::uint8_t((buttom_right_rgba_color >> (8 * 3)) & 0xff), std::uint8_t((buttom_right_rgba_color >> (8 * 2)) & 0xff),
                         std::uint8_t((buttom_right_rgba_color >> (8 * 1)) & 0xff), std::uint8_t((buttom_right_rgba_color >> (8 * 0)) & 0xff),
                         std::uint8_t((top_left_rgba_color >> (8 * 3)) & 0xff),     std::uint8_t((top_left_rgba_color >> (8 * 2)) & 0xff),
                         std::uint8_t((top_left_rgba_color >> (8 * 1)) & 0xff),     std::uint8_t((top_left_rgba_color >> (8 * 0)) & 0xff),
                         std::uint8_t((top_right_rgba_color >> (8 * 3)) & 0xff),    std::uint8_t((top_right_rgba_color >> (8 * 2)) & 0xff),
                         std::uint8_t((top_right_rgba_color >> (8 * 1)) & 0xff),    std::uint8_t((top_right_rgba_color >> (8 * 0)) & 0xff) }
    , m_texture(0)
  {
    using size_type = GLsizei;
    constexpr size_type width = 2;
    constexpr size_type height = 2;
    glGenTextures(1, &m_texture);
    glBindTexture(GL_TEXTURE_2D, m_texture);
    // set the texture wrapping/filtering options (on the currently bound texture object)
    // GL_MIRRORED_REPEAT
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_rgba_color_data);
  }
  texture_type texture() const
  {
    return m_texture;
  }
  ~four_color_texure() {
    if (m_texture) {
      glDeleteTextures(1, &m_texture);
      m_texture = 0;
    }

  }
};
#endif // FOUR_COLOR_TEXTURE_HPP_INCLUDED