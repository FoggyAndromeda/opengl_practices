#version 330 core
out vec4 frag_color;

in vec4 vert_color;
in vec3 norm;
in vec3 frag_pos;
in vec3 light_pos;
in vec3 light_color;

void main()
{
  vec3 light_dir = normalize(light_pos - frag_pos);
  float diff = max(dot(light_dir, norm), 0.0f);
  vec3 diffuse = diff * light_color;
  vec3 result_color = diffuse * vert_color.xyz;
  frag_color = vec4(result_color, 1.0f);
} 
