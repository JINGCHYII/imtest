#version 430 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;     
layout (location = 2) in vec3 aIndex;      
                                                                                    
uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;     

out float gObjectIndex;
out float gDrawIndex;

void main()                                                                         
{                                               
    gl_Position = projection * view * model * vec4(aPos, 1.0f);

    gObjectIndex = aIndex.x;	                                    
    gDrawIndex = aIndex.y;
}