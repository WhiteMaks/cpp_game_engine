//begin: vertex_shader
#version 460 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoordinate;

uniform mat4 u_ViewProjectionMatrix;

out vec4 v_Color;
out vec2 v_TextureCoordinate;

void main() {
	v_TextureCoordinate = a_TextureCoordinate;
	v_Color = a_Color;
	gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}
//end: vertex_shader

//begin: fragment_shader
#version 460 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TextureCoordinate;

void main() {
	//color = texture(u_Texture, v_TextureCoordinate) * v_Color;
	color = v_Color;
}
//end: fragment_shader