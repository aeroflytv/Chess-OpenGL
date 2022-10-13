#shader vertex
#version 330 core

layout (location = 0) in vec4 a_Pos;
layout (location = 1) in vec2 a_TexCoords;

uniform mat4 u_MVP;
out vec2 o_TexCoords;

void main()
{
  o_TexCoords = a_TexCoords;
  gl_Position = u_MVP * a_Pos;
}

#shader fragment 
#version 330 core

out vec4 FragColor;

in vec2 o_TexCoords;

uniform sampler2D u_Texture;
uniform bool u_WithTex;

void main()
{
  if(u_WithTex == true)
  {
    vec4 color = vec4(0.5, 0.5, 0.5, 1.0);
    vec4 texture = texture(u_Texture, o_TexCoords);

    vec4 finalColor = vec4(mix(color.rgb, texture.bgr, texture.a), 1);

    FragColor = finalColor;
  }
  else
  {
    FragColor = vec4(0.5, 0.5, 0.5, 1.0);
  }
}
