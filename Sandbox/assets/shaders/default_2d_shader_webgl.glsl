//begin: vertex_shader
#version 300 es

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
layout(location = 2) in vec2 a_TextureCoordinate;
layout(location = 3) in float a_TextureIndex;

uniform mat4 u_ViewProjectionMatrix;

out vec4 v_Color;
out vec2 v_TextureCoordinate;

out float v_TextureIndex;

void main() {
	v_Color = a_Color;
	v_TextureCoordinate = a_TextureCoordinate;
	v_TextureIndex = a_TextureIndex;

	gl_Position = u_ViewProjectionMatrix * vec4(a_Position, 1.0);
}
//end: vertex_shader

//begin: fragment_shader
#version 300 es
			
precision lowp float;

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TextureCoordinate;

in float v_TextureIndex;

uniform sampler2D u_Textures[16];

vec4 getTexture() {
	int index = int(v_TextureIndex);
					
	//amd, intel, nvidia support
	switch (index) {
		case 0: return texture(u_Textures[0], v_TextureCoordinate);
		case 1: return texture(u_Textures[1], v_TextureCoordinate);
		case 2: return texture(u_Textures[2], v_TextureCoordinate);
		case 3: return texture(u_Textures[3], v_TextureCoordinate);
		case 4: return texture(u_Textures[4], v_TextureCoordinate);
		case 5: return texture(u_Textures[5], v_TextureCoordinate);
		case 6: return texture(u_Textures[6], v_TextureCoordinate);
		case 7: return texture(u_Textures[7], v_TextureCoordinate);
		case 8: return texture(u_Textures[8], v_TextureCoordinate);
		case 9: return texture(u_Textures[9], v_TextureCoordinate);
		case 10: return texture(u_Textures[10], v_TextureCoordinate);
		case 11: return texture(u_Textures[11], v_TextureCoordinate);
		case 12: return texture(u_Textures[12], v_TextureCoordinate);
		case 13: return texture(u_Textures[13], v_TextureCoordinate);
		case 14: return texture(u_Textures[14], v_TextureCoordinate);
		case 15: return texture(u_Textures[15], v_TextureCoordinate);
	};
					
	return vec4(1.0, 1.0, 1.0, 1.0);
}

void main() {
	color = getTexture() * v_Color;
}
//end: fragment_shader