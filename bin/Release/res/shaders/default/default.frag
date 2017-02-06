#version 330 core

uniform vec2 light_position;
uniform bool light_on = true;

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

uniform sampler2D textures[32];

void main()
{
	float intensity = light_on ? 2.0 / length(fs_in.position.xy - light_position) : 1.0f;
	
	vec4 tex_color = fs_in.color;
	vec4 sampled;
	if (fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5);
		tex_color =  fs_in.color * texture2D(textures[tid], fs_in.uv);
	}
    gl_FragColor = tex_color * intensity;
}