#version 330 core
out vec4 FragColor;

in VS_DATA {
    vec2 TexCoords;
} vs_in;

uniform sampler2D frontTexture;
uniform sampler2D backTexture;

void main()
{   
    FragColor = texture(frontTexture, vs_in.TexCoords);
}
