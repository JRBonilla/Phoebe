#version 330 core

layout (location = 0) out vec4 color;

uniform vec2 light_pos;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D tex;

void main()
{
	vec4 texColor = fs_in.color;
	vec4 sampled = vec4(1.0, 1.0, 1.0, texture(tex, fs_in.uv).r);
    color = fs_in.color * sampled;
}