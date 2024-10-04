#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

class camera_t {
 public:
  glm::vec3 pos;
  glm::vec3 direction;
  glm::vec3 up;
  glm::vec3 right;
  const glm::vec3 world_up{0.0f, 1.0f, 0.0f};

 public:
  camera_t(glm::vec3 position, glm::vec3 dir) : pos(position), direction(dir) {
    recalculate_vectors();
  };

  glm::mat4 get_view_mat() { return glm::lookAt(pos, pos + direction, up); }

 private:
  void recalculate_vectors() {
    right = glm::normalize(glm::cross(direction, world_up));
    up = glm::normalize(glm::cross(right, direction));
  }
};
