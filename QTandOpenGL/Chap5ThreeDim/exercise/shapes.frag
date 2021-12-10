#version 330 core
out vec4 FragColor;
//in vec3 ourColor;
in vec2 texCoord;
uniform sampler2D textureWall;
uniform sampler2D texturePhoto;
uniform sampler2D textureSmall;
uniform float ratio;




void main()
{
    //FragColor = vec4(ourColor,1.0f);
    //FragColor = mix(texture2D(textureWall,texCoord),texture2D(textureSmall,texCoord),0.5);
    //FragColor = texture2D(textureSmall,vec2(1-texCoord.x,texCoord.y));
    //FragColor = texture2D(textureSmall,texCoord);
    //FragColor = mix(texture2D(textureWall,texCoord),texture2D(textureSmall,texCoord),0.5);
    FragColor = mix(texture2D(textureWall,texCoord),texture2D(textureSmall,texCoord),ratio);
}
