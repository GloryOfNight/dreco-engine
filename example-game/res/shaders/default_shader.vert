uniform mat3 u_matrix;
uniform mat4 u_projection;

attribute vec2 a_position;

attribute vec2 a_tex_coord;
attribute vec4 a_color;

varying vec4 v_color;
varying vec2 v_tex_coord;

void main()
{
    v_tex_coord = a_tex_coord;
    v_color = a_color;
    vec3 pos = vec3(a_position, 1.0f) * u_matrix;
    gl_Position = u_projection * vec4(pos, 1.0);
}