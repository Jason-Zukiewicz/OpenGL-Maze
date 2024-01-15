varying vec4 N;
varying vec4 L;
varying vec4 V;
varying float distance;

varying vec2 texCoord;
uniform sampler2D texture;

 float shininess;
 float attenuation_constant;
 float attenuation_linear;
 float attenuation_quadratic;

vec4 ambient, diffuse, specular;

uniform float aFlag, dFlag, sFlag;
uniform float aFactor;

void main()
{
    attenuation_quadratic = 100.0f;
    attenuation_constant = 1.0f;
    attenuation_linear = 0.09f;
    attenuation_quadratic = 0.032f;

    vec4 color = texture2D(texture, texCoord);
    vec4 NN = normalize(N);
    vec4 VV = normalize(V);
    vec4 LL = normalize(L);
    if (aFlag == 1.0){
        ambient = color * aFactor;
    } else {
        ambient = color;
    }


    if (dFlag == 1.0){
        diffuse = max(dot(LL, NN), 0.0) * 0.8 * color;
    } else {
        diffuse = vec4(0.0, 0.0, 0.0, 1.0);
    }
    

    if (sFlag == 1.0){
        vec4 H = normalize(LL + VV);
        specular = pow(max(dot(NN, H), 0.0), shininess) * vec4(0.2, 0.2, 0.0, 0.0);
    } else {
        specular = vec4(0.0, 0.0, 0.0, 1.0);
    }

    float attenuation = 1.0 / (attenuation_constant + (attenuation_linear * distance) + (attenuation_quadratic * distance * distance));
    gl_FragColor = ambient + attenuation * (diffuse + specular);
}
