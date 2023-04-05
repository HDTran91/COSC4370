
#version 330 core
layout (location = 0) in vec3 position;
layout(location = 1) in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    // TODO: Your code here
    // Remember to set gl_Position (correctly) or you will get a black screen...
// Transform the vertex position into clip space 
    vec4 posClipSpace = projection * view * model * vec4(position, 1.0);
    
    // Set the output position 
    gl_Position = posClipSpace;
    
    // Insert the vertex UV coordinates to fragment shader
    UV = vec2(vertexUV.x, 10-vertexUV.y);
}
