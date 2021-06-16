#type vertex
#version 430

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;

out vec2 v_TexCoord;

void main()
{
	vec4 position = vec4(a_Position.x,a_Position.y, 0.0, 1.0);
	v_TexCoord = a_TexCoord;
	gl_Position = position;
}

#type fragment
#version 430

in vec2 v_TexCoord;
out vec4 outColor;

uniform sampler2D u_Texture;

void main()
{
	vec3 color = texture(u_Texture, v_TexCoord).rgb;
	outColor = vec4(color, 1.0);
}
