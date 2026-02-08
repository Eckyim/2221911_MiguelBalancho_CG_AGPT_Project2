#version 330 core
in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D spriteTexture;
uniform vec2 texOffset;
uniform vec2 texSize;

void main()
{
    vec2 actualTexCoord = texOffset + TexCoord * texSize;
    vec4 texColor = texture(spriteTexture, actualTexCoord);
    
    if (texColor.a < 0.01)
        discard;
    
    FragColor = texColor;
}