#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    mat3 normalMatrix = transpose(inverse(mat3(model)));
	vec3 Normal = normalize(normalMatrix * aNormal) * 0.00001;
	gl_Position = projection * view * model * vec4(aPos, 1.0f) + vec4(Normal, 1.0);
}