#version 330 core
layout(location = 0) in vec3 inVert;
layout(location = 1) in vec3 inNorm;
layout(location = 2) in vec2 inTexCoord;

uniform mat4 mvp;
out vec2 texCoord;
out vec3 normal;


void main(){
  gl_Position = mvp * vec4(inVert.x, inVert.y, inVert.z, 1.0);
  texCoord = inTexCoord;
  normal = inNorm;
}