#version 330 core

in vec2 texCoord;
out vec3 color;

uniform sampler2D textureData;

void main(){
  color = texture(textureData, texCoord).xyz;
}
