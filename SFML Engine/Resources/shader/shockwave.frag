
// Shockwave
varying vec2 v_texcoord;
uniform sampler2D texture;
uniform float time;
uniform vec2 centre;
uniform vec2 resolution;
uniform float shock_amplitude;
uniform float shock_refraction;
uniform float shock_width;


void main()
{ 
    vec2 uv = v_texcoord;
    uv.x *= (resolution.x/resolution.y);
    
    vec2 texCoord = v_texcoord;  
    
    float centre_x = (centre.x / resolution.x) * (resolution.x/resolution.y);
    float centre_y = centre.y / resolution.y;
  
    float dist = distance(uv, vec2(centre_x,centre_y));
    
    if ( (dist <= (time + shock_width)) && (dist >= (time - shock_width))) 
    {
        float dif = (dist - time); 
        float powDiff = 1.0 - pow(abs(dif*shock_amplitude),shock_refraction); 
        float diffTime = dif  * powDiff;
        vec2 diffUV = normalize(uv - centre); 
        texCoord = uv + (diffUV * diffTime);
        texCoord.x *= (resolution.y/resolution.x);
    } 
 
    gl_FragColor = texture2D(texture,texCoord);
}
/*
// Ripple
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



varying vec2 v_texcoord;
uniform sampler2D texture;
uniform float time;
uniform float wave_amount;
uniform float wave_distortion;
uniform float wave_speed;

void main()
{ 
    vec2 uv = v_texcoord;
    uv.x = uv.x+cos(uv.y*wave_amount+time*wave_speed)/wave_distortion;
    uv.y = uv.y+sin(uv.x*wave_amount+time*wave_speed)/wave_distortion;
 
    gl_FragColor = texture2D(texture,uv);
}
*/