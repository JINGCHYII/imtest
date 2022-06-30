#version 430 core
out vec4 FragColor;

in vec2 TexCoord;
in vec3 Normal;
in vec3 oIndex;       
in float isSelected;

// texture samplers
uniform sampler2D texture1;
uniform sampler2D texture2;

uniform vec3 viewNormal;
// uniform float selectedId;

void main()
{
	// linearly interpolate between both textures (80% container, 20% awesomeface)
	//FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
	if (oIndex.z != 0 || (isSelected != 0))
		FragColor = vec4(0.8549, 0.1451, 0.8549, 1.0);
	else
	{
		if (dot(viewNormal, Normal) > 0)
			FragColor = vec4(1.0, 0.0, 0.0, 1);
		else
			FragColor = vec4(0.0, 0.0, 1.0, 1);
	}
}