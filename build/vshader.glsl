attribute vec4 vPosition;

attribute vec4 vNormal;
attribute vec2 vTexCoord;
varying vec2 texCoord;

uniform mat4 ctm, model_view_matrix, projection_matrix;
uniform vec4 light_position;
varying vec4 N;
varying vec4 L;
varying vec4 V;
varying float distance;





void main()
{
	texCoord = vTexCoord;
    gl_Position = projection_matrix * model_view_matrix * ctm * vPosition;
    N = normalize(model_view_matrix * ctm * vNormal);
    vec4 L_temp = model_view_matrix * (light_position - ctm * vPosition);
    L = normalize(L_temp);
    vec4 eye_point = vec4(0.0, 0.0, 0.0, 1.0);
    V = normalize(eye_point - (model_view_matrix * ctm * vPosition));
    distance = length(L_temp);
}