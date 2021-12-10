#version 330 core
out vec4 FragColor;
in vec3 ourColor;
in vec2 texCoord;
uniform sampler2D textureWall;
uniform sampler2D texturePhoto;
uniform sampler2D textureSmall;

void main()
{
    //FragColor = vec4(ourColor,1.0f);
    //FragColor = mix(texture2D(textureWall,texCoord),texture2D(texturePhoto,texCoord),0.5);
    FragColor = texture2D(textureSmall,texCoord);
}
