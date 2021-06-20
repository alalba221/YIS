#type vertex
#version 430

layout(location = 0) in vec3 a_Position;


out vec3 v_Position;
uniform mat4 u_ViewProjectionMatrix;
void main()
{
	vec4 position = u_ViewProjectionMatrix*vec4(a_Position, 1.0);
	gl_Position =  position.xyww;

	v_Position = a_Position;
}

#type fragment
#version 430

layout(location = 0) out vec4 finalColor;

uniform samplerCube u_Texture;

in vec3 v_Position;

void main()
{
	finalColor = texture(u_Texture, v_Position);
	//finalColor = vec4(0.2,0.9,0.3,1.0);
}
