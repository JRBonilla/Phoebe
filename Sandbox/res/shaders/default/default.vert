#version 330 core

layout (location = 0) in vec3 position; // The position variable has attribute position 0
layout (location = 1) in vec2 uv;
layout (location = 2) in float tid;
layout (location = 3) in vec4 color;	// The color variable has attribute position 3

uniform mat4 pr_matrix;
uniform mat4 vw_matrix = mat4(1.0);
uniform mat4 ml_matrix = mat4(1.0);

out DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} vs_out;

void main()
{
    gl_Position = pr_matrix * vw_matrix * ml_matrix * vec4(position, 1.0);
	vs_out.position = ml_matrix * vec4(position, 1.0);
	vs_out.uv = uv;
	vs_out.tid = tid;
	vs_out.color = color;
}