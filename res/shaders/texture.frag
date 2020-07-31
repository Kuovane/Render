
#version 110

varying vec2 v_texCoord;
uniform	sampler2D texture;

void main()
{

	vec4 result = texture2D(texture, v_texCoord);


    gl_FragColor = result;
   // gl_FragColor = vec4(1.0, 0.5, 0.31,1.0);

}

