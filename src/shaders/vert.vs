#version 330 core
layout (location = 0) in vec3 in_pos;
layout (location = 1) in vec3 in_color;
layout (location = 2) in vec3 in_norm;

out vec4 vert_color;
out vec3 norm;
out vec3 frag_pos;
out vec3 light_pos;
out vec3 light_color;

uniform mat4 u_projection;
uniform mat4 u_view;
uniform mat4 u_model;
uniform vec3 u_light_pos;
uniform vec3 u_light_color;

void main()
{
    gl_Position = u_projection * u_view * u_model * vec4(in_pos, 1.0);
    frag_pos = vec3(u_model * vec4(in_pos, 1.0));
    vert_color = vec4(in_color, 1.0);
    norm = normalize(in_norm);
    light_pos = u_light_pos;
    light_color = u_light_color;
}
