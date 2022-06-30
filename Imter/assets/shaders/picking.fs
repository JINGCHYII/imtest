#version 430 core                                                                        

in float gObjectIndex;                                                          
in float gDrawIndex;                                                                                       

out vec3 FragColor;                    
// void main()                                                                         
// {                                                                                   
//    FragColor = vec4(float(gObjectIndex), float(gDrawIndex), 0, 1);           
//    // FragColor = vec4(float(gObjectIndex), float(gDrawIndex), float(gl_PrimitiveID + 1), 1);
//    // FragColor = vec4(0.1,0.5,0.6,1.0);                 
// }

void main()                                                                         
{                                                                                   
   FragColor = vec3(float(gObjectIndex), float(gDrawIndex), 1);                 
}