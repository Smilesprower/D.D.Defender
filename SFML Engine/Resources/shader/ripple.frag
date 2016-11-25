varying vec2 v_texcoord;
uniform sampler2D texture;
uniform float time;
uniform vec2 centre;
uniform vec2 resolution;
uniform float wave_amount;
uniform float wave_distortion;
uniform float wave_speed;

void main()
{ 
	vec2 uv = v_texcoord;
    uv.x *= (resolution.x/resolution.y);
    float centre_x = (centre.x / resolution.x) * (resolution.x/resolution.y);
    float centre_y = centre.y / resolution.y;
  
    vec2 dir = v_texcoord - vec2(0.5);
    float dist = distance(uv, vec2(centre_x,centre_y));
    vec2 offset = dir * (sin(dist * wave_amount - time * wave_speed)) / wave_distortion;
 
    gl_FragColor = texture2D(texture,v_texcoord + offset);
}
