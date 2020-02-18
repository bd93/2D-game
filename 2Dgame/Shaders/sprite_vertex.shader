#version 330 core
layout (location = 0) in vec4 aPos;

out vec2 TexCoords;

uniform mat4 model;
uniform mat4 projection;

void main()
{ 
	TexCoords = vec2(aPos.z, aPos.w);
	gl_Position = projection * model * vec4(aPos.x, aPos.y, 0.0, 1.0);
}