#version 330 core
layout (triangles) in;
layout (line_strip, max_vertices = 3) out;

// in vec3 Normal;

// const float MAGNITUDE = 0.4;

void main() 
{    
    gl_Position = gl_in[0].gl_Position;
    EmitVertex();   
    gl_Position = gl_in[1].gl_Position;
    EmitVertex();   
    gl_Position = gl_in[2].gl_Position;
    EmitVertex();   
    EndPrimitive();
}

// void GenerateLine(int index)
// {
//     gl_Position = gl_in[index].gl_Position;
//     EmitVertex();
//     gl_Position = gl_in[index].gl_Position + vec4(Normal, 0.0) * MAGNITUDE;
//     EmitVertex();
//     EndPrimitive();
// }

// void main()
// {
//     GenerateLine(0); 
//     GenerateLine(1); 
//     GenerateLine(2);
// }