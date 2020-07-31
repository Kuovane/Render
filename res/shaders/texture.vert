
#version 110

attribute vec3 vPos;
attribute vec2 vTex;

varying vec2 v_texCoord;


void main()
{
    gl_Position = vec4(vPos, 1.0);
    v_texCoord = vTex;
}

