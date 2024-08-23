//begin: vertex_shader
#version 300 es

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TextureCoordinate;

out vec2 v_TextureCoordinate;

void main() {
	v_TextureCoordinate = a_TextureCoordinate;

	gl_Position = vec4(a_Position, 1.0);
}
//end: vertex_shader

//begin: fragment_shader
#version 300 es
			
precision lowp float;

layout(location = 0) out vec4 color;

in vec2 v_TextureCoordinate;

uniform sampler2D u_Texture;

void main() {
	color = texture(u_Texture, v_TextureCoordinate);
}
//end: fragment_shader