#version 460 core

out vec4 result;
uniform sampler2D u_TextureAtlas;
in vec2 v_TextureCoords;

void main()
{
    result = texture(u_TextureAtlas, v_TextureCoords);
}