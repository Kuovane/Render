
#version 110

attribute vec4 a_position;
uniform mat4 projection;
uniform mat4 u_MVPMatrix;

void main(void)
{ 
    gl_Position =  projection * u_MVPMatrix * a_position;
}
          