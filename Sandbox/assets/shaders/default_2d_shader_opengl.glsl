//begin: vertex_shader
#version 460 core

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
#version 460 core

layout(location = 0) out vec4 color;

in vec4 v_Color;
in vec2 v_TextureCoordinate;

in float v_TextureIndex;

uniform sampler2D u_Textures[32];

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
		case 16: return texture(u_Textures[16], v_TextureCoordinate);
		case 17: return texture(u_Textures[17], v_TextureCoordinate);
		case 18: return texture(u_Textures[18], v_TextureCoordinate);
		case 19: return texture(u_Textures[19], v_TextureCoordinate);
		case 20: return texture(u_Textures[20], v_TextureCoordinate);
		case 21: return texture(u_Textures[21], v_TextureCoordinate);
		case 22: return texture(u_Textures[22], v_TextureCoordinate);
		case 23: return texture(u_Textures[23], v_TextureCoordinate);
		case 24: return texture(u_Textures[24], v_TextureCoordinate);
		case 25: return texture(u_Textures[25], v_TextureCoordinate);
		case 26: return texture(u_Textures[26], v_TextureCoordinate);
		case 27: return texture(u_Textures[27], v_TextureCoordinate);
		case 28: return texture(u_Textures[28], v_TextureCoordinate);
		case 29: return texture(u_Textures[29], v_TextureCoordinate);
		case 30: return texture(u_Textures[30], v_TextureCoordinate);
		case 31: return texture(u_Textures[31], v_TextureCoordinate);
	};
					
	return vec4(1.0, 1.0, 1.0, 1.0);
}

void main() {
	color = getTexture() * v_Color;
}
//end: fragment_shader