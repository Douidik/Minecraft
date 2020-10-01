#version 460 core

out vec4 result;
in vec3 v_color;

void main()
{
    result = vec4(v_color, 1.0);
}