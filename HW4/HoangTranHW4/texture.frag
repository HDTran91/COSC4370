
#version 330 core
out vec4 color;

in vec2 UV;
uniform sampler2D myTextureSampler;

void main()
{
    // TODO: pub with your code...

    // Output color = color of the texture at the specified UV
    color = texture(myTextureSampler, UV);
}
