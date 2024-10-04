/*
 * V11
 *
 * Параллелограмм (одна из сторон направлена по оси OY)
 */
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>

#include "common/shader.hpp"
#include "common/camera.hpp"


void process_input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

int main(int argc, const char** argv) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  GLFWwindow *window = glfwCreateWindow(800, 600, argv[0], NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate();
    return -1;
  }
  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return -1;
  }

  shader_t default_shader("vert.vs", "frag.fs");

  float vertices[] = {
      5.0f, 3.0f, 0.0f,   // top right
      0.0f, 0.0f, 1.0f,   // color
      0.0f, 0.0f, 1.0f,   // normal
                          //
      5.0f, -1.0f, 0.0f,  // bottom right
      0.0f, 1.0f, 0.0f,   // color
      0.0f, 0.0f, 1.0f,   // normal
                          //
      0.0f, -5.0f, 0.0f,  // bottom left
      0.0f, 1.0f, 1.0f,   // color
      0.0f, 0.0f, 1.0f,   // normal
                          //
      0.0f, 6.0f, 0.0f,   // top left
      1.0f, 0.0f, 0.0f,   // top left color
      0.0f, 0.0f, 1.0f    // normal
  };
  unsigned int indices[] = {0, 1, 3, 1, 2, 3};
  unsigned int VBO, VAO, EBO;
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);
  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices,
               GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float), (void *)0);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                        (void *)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 9 * sizeof(float),
                        (void *)(6 * sizeof(float)));
  glEnableVertexAttribArray(2);

  glBindBuffer(GL_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  glm::mat4 proj = glm::mat4(1.0f);
  proj = glm::perspective(glm::radians(45.0f), 800.0f / 600.0f, 0.1f, 100.0f);
  camera_t camera(glm::vec3{20.0f, 20.0f, 20.0f},
                  glm::vec3{-1.0f, -1.0f, -1.0f});
  glm::mat4 view = camera.get_view_mat();
  glm::vec3 light_pos = glm::vec3(100.f, 100.f, 100.f);
  glm::vec3 light_color = glm::vec3(1.0f, 1.0f, 1.0f);

  while (!glfwWindowShouldClose(window)) {
    process_input(window);

    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    default_shader.activate();
    default_shader.set_mat4("u_projection", proj);
    default_shader.set_mat4("u_view", view);
    default_shader.set_vec3("u_light_pos", light_pos);
    default_shader.set_vec3("u_light_color", light_color);

    glm::mat4 model = glm::mat4(1.0f);
    float angle = glfwGetTime();
    model = glm::rotate(model, angle, glm::vec3(0.0f, 1.0f, 0.0f));
    default_shader.set_mat4("u_model", model);

    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);

  glfwTerminate();
  return 0;
}
