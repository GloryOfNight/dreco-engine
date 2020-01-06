#version 100

precision mediump float;
varying vec2 v_tex_coord;
varying vec4 v_color;
uniform sampler2D s_texture;

uniform int is_color;
uniform vec3 pick_color;

void main()
{
    if (is_color <= 0) 
    {
        vec2 flipped_texcoord = vec2(v_tex_coord.x, 1.0 - v_tex_coord.y);
        gl_FragColor = texture2D(s_texture, flipped_texcoord);
    }
    else 
    {
        gl_FragColor = vec4(pick_color, 1.0);
    }
    
    
    //vec4(1.0, 1.0, 1.0, 1.0);
    //texture2D(s_texture, v_tex_coord);
}