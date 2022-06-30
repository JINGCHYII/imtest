#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec3 aIndex;     

out vec2 TexCoord;
out vec3 Normal;
out vec3 oIndex;
out float isSelected;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec2 selectionX;
uniform vec2 selectionY;

void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0f);
	// TexCoord = vec2(aTexCoord.x, aTexCoord.y);
	mat3 normalMatrix = transpose(inverse(mat3(model)));
	Normal = normalize(normalMatrix * aNormal);
	
    oIndex = aIndex;

	if (gl_Position.x > selectionX.x && gl_Position.x < selectionX.y &&
		gl_Position.y > selectionY.x && gl_Position.y < selectionY.y)
		isSelected = 1;
	else
		isSelected = 0;
}