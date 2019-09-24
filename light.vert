attribute vec4 a_position;
uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;


void main(void)
{
    mat4 mv_matrix = viewMatrix * modelMatrix;
    gl_Position = projectionMatrix * mv_matrix *  a_position;
}
