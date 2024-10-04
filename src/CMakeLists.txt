function(add_practice bin_name source_files)
message("Adding ${bin_name}. Source files: ${source_files}")
    add_executable(${bin_name} ${source_files})
    target_include_directories(${bin_name} 
                               PRIVATE ${GLFW_INCLUDES}
                               PRIVATE ${GLAD_INCLUDES}
                               PRIVATE ${GLM_INCLUDES})
    
    target_link_libraries(${bin_name} glad glfw)
endfunction()

set(
    COMMON_FILES

    common/shader.cpp
)

add_practice(prac1 "practice1.cpp;${COMMON_FILES}")
add_practice(prac2 "practice2.cpp;${COMMON_FILES}")
