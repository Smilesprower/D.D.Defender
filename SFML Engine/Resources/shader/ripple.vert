varying vec4 vColor;
varying vec2 v_texcoord;

void main()
{
	v_texcoord = (gl_TextureMatrix[0] * gl_MultiTexCoord0).xy;
    gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
    vColor = gl_Color;
}