#include "shader.hpp"

#include <fstream>
#include <glad/glad.h>
#include <iostream>

shader_t::shader_t(const std::string &vertex_shader_filename,
                   const std::string &fragment_shader_filename) {
  std::string vertex_src, fragment_src;
  std::ifstream vertex_file, fragment_file;
  vertex_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  fragment_file.exceptions(std::ifstream::failbit | std::ifstream::badbit);
  try {
    vertex_file.open(vertex_shader_filename);
    fragment_file.open(fragment_shader_filename);
    std::getline(vertex_file, vertex_src, '\0');
    std::getline(fragment_file, fragment_src, '\0');
  } catch (std::ifstream::failure e) {
    std::cerr << "[ERR] SHADER: CAN\'T READ SHADER SRC FILES ";
    std::cerr << "(" << vertex_shader_filename << ", "
              << fragment_shader_filename << ")" << std::endl;
  }
  int frag_id = compile_shader(GL_FRAGMENT_SHADER, fragment_src);
  int vert_id = compile_shader(GL_VERTEX_SHADER, vertex_src);

  id = glCreateProgram();
  glAttachShader(id, frag_id);
  glAttachShader(id, vert_id);
  glLinkProgram(id);
  int success;
  glGetProgramiv(id, GL_LINK_STATUS, &success);
  if (!success) {
    char log[512];
    glGetProgramInfoLog(id, 512, NULL, log);
    std::cerr << "[ERR] SHADER: CAN\'T LINK PROGRAM: " << log << std::endl;
  }
  glDeleteShader(vert_id);
  glDeleteShader(frag_id);
}

shader_t::~shader_t() { 
  // glDeleteProgram(id); 
}

void shader_t::activate() { glUseProgram(id); }

int shader_t::compile_shader(uint32_t type, const std::string &src) {
  int success;
  int now_id = glCreateShader(type);
  const char *src_ptr = src.c_str();
  glShaderSource(now_id, 1, &src_ptr, NULL);
  glCompileShader(now_id);
  glGetShaderiv(now_id, GL_COMPILE_STATUS, &success);
  if (!success) {
    char log[512];
    glGetShaderInfoLog(now_id, 512, NULL, log);
    std::cerr << "[ERR] SHADER CAN\'T COMPILE: " << log << std::endl;
  }
  return now_id;
}
