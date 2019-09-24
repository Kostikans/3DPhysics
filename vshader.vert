#version 140
attribute vec4 a_position;
attribute vec2 a_texcoord;
attribute vec3 a_normal;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;
varying vec4 v_position;
varying vec2 v_texcoord;
varying vec3 v_normal;

void main(void)
{
    mat4 mv_matrix = viewMatrix * modelMatrix;
    gl_Position = projectionMatrix * mv_matrix *  a_position;

    v_texcoord = a_texcoord;
    v_normal = mat3(transpose(inverse(modelMatrix))) * a_normal;
    v_position = vec4(modelMatrix * a_position);
}
