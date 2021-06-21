#type vertex
#version 430

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec3 a_Normal;

out vec3 Normal;
out vec3 Position;

uniform mat4 u_ViewProjectionMatrix;

void main()
{
	
	Normal =  a_Normal;
	Position = a_Position;
	gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}

#type fragment
#version 430

in vec3 Normal;
in vec3 Position;
layout(location = 0) out vec4 finalColor;

uniform vec3 u_CameraPosition;
uniform samplerCube u_Texture;


void main()
{
	vec3 I = normalize(Position - u_CameraPosition);
    vec3 R = reflect(I, normalize(Normal));

	finalColor = vec4(texture(u_Texture, R).rgb, 1.0);	

}
