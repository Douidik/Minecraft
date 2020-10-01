#version 460 core
#define TEXTURE_TILE_WIDTH 16
#define TEXTURE_TILE_HEIGHT 16
#define TEXTURE_COUNT_WIDTH  8
#define TEXTURE_COUNT_HEIGHT 8

#define TEXTURE_WIDTH (TEXTURE_TILE_WIDTH * TEXTURE_COUNT_WIDTH)
#define TEXTURE_HEIGHT (TEXTURE_TILE_HEIGHT * TEXTURE_COUNT_HEIGHT)

layout(location = 0) in vec3 a_Position;
layout(location = 1) in int a_Index;
layout(location = 2) in int a_TextureIndex;

uniform mat4 u_ViewProjection;
uniform mat4 u_Transform;

out vec2 v_TextureCoords;

ivec2 offsets[] =
{
    ivec2(0, 0),
    ivec2(1, 0),
    ivec2(0, 1),
    ivec2(1, 1)
};

void main()
{
    gl_Position = u_ViewProjection * u_Transform * vec4(a_Position, 1.0);

    /* Computing texture coordinates from index */

    ivec2 offset = offsets[a_Index];
    vec2 coordinates;
    coordinates.x = (a_TextureIndex % TEXTURE_COUNT_WIDTH) + offset.x;
    coordinates.y = (a_TextureIndex / TEXTURE_COUNT_WIDTH) + offset.y;

    vec2 pixelCoords;
    pixelCoords.x = coordinates.x * TEXTURE_TILE_WIDTH;
    pixelCoords.y = coordinates.y * TEXTURE_TILE_HEIGHT;

    /* Converting pixel texture coordinates to normalized texture coordinates */
    v_TextureCoords.x = pixelCoords.x / TEXTURE_WIDTH;
    v_TextureCoords.y = pixelCoords.y / TEXTURE_HEIGHT;
}