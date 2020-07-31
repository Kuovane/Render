
#version 110

attribute vec3 vPos;
attribute vec2 vTex;


uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;


varying vec2 v_texCoord;


void main()
{
    gl_Position = projection * view * model * vec4(vPos, 1.0);
    //gl_Position = vec4(vPos, 1.0);
    v_texCoord = vTex;
}

