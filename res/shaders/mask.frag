
#version 110


varying vec2 v_texCoord;

uniform	sampler2D texture;
uniform vec4 u_color;

void main()
{

	vec4 result = texture2D(texture, v_texCoord);
    gl_FragColor = result;

  
	//gl_FragColor = vec4(0.0, 0.0, 0.0, 0.0);
}

