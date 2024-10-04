add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glfw)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glm)
add_subdirectory(${CMAKE_CURRENT_LIST_DIR}/glad)

set(GLAD_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/glad/include)
set(GLFW_INCLUDES ${CMAKE_CURRENT_LIST_DIR}/glfw/include)
set(GLM_INCLUDES  ${CMAKE_CURRENT_LIST_DIR}/glm)
