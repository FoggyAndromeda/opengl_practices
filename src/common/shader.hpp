#pragma once

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <stdint.h>
#include <string>

class shader_t {
public:
  shader_t(const std::string &, const std::string &);
  ~shader_t();
  void activate();

  inline void set_bool(const std::string &name, bool value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), (int)value);
  }
  inline void set_int(const std::string &name, int value) const {
    glUniform1i(glGetUniformLocation(id, name.c_str()), value);
  }
  inline void set_float(const std::string &name, float value) const {
    glUniform1f(glGetUniformLocation(id, name.c_str()), value);
  }
  inline void set_vec2(const std::string &name, glm::vec2 &value) const {
    glUniform2fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
  }
  inline void set_vec3(const std::string &name, glm::vec3 &value) const {
    glUniform3fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
  }
  inline void set_vec4(const std::string &name, glm::vec4 &value) const {
    glUniform4fv(glGetUniformLocation(id, name.c_str()), 1, &value[0]);
  }
  inline void set_mat2(const std::string &name, glm::mat2 &mat) const {
    glUniformMatrix2fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }
  inline void set_mat3(const std::string &name, glm::mat3 &mat) const {
    glUniformMatrix3fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }
  inline void set_mat4(const std::string &name, glm::mat4 &mat) const {
    glUniformMatrix4fv(glGetUniformLocation(id, name.c_str()), 1, GL_FALSE,
                       &mat[0][0]);
  }

private:
  int compile_shader(uint32_t, const std::string &);

private:
  uint32_t id;
};
