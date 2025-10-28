#version 330 core
in vec2 TexCoords;
out vec4 color;

uniform sampler2D text;
uniform vec3 textColor;

void main()
{    
    // get grayscale value
    float alpha = texture(text, TexCoords).r;

    if (alpha < 0.3)
        discard;

    color = vec4(textColor, 1.0);
}
