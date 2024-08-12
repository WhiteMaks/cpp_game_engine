//begin: vertex_shader
#version 300 es

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

uniform mat4 u_ViewProjectionMatrix;
uniform mat4 u_ModelMatrix;

out vec2 v_TextureCoordinate;

void main() {
	v_TextureCoordinate = a_TextureCoordinate;
	gl_Position = u_ViewProjectionMatrix * u_ModelMatrix * vec4(a_Position, 1.0);
}
//end: vertex_shader

//begin: fragment_shader
#version 300 es
			
precision lowp float;

layout(location = 0) out vec4 color;

in vec2 v_TextureCoordinate;

uniform sampler2D u_Texture;
uniform vec4 u_Color;

void main() {
	color = texture(u_Texture, v_TextureCoordinate) * u_Color;
}
//end: fragment_shader