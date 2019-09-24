uniform sampler2D qt_Texture0;
uniform vec3 u_lightPosition;
uniform vec3 u_eyePosition;

varying vec4 v_position;
varying vec2 v_texcoord;
varying vec3 v_normal;


uniform bool blinn;

void main()
{
    vec3 color = texture2D(qt_Texture0, v_texcoord);
    // ambient
    vec3 ambient = 0.05 * color;
    // diffuse
    vec3 lightDir = normalize(u_lightPosition - v_position);
    vec3 normal = normalize(v_normal);
    float diff = max(dot(lightDir, normal), 0.0);
    vec3 diffuse = diff * color;
    // specular
    vec3 viewDir = normalize(u_eyePosition - v_position);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = 0.0;
    if(blinn)
    {
        vec3 halfwayDir = normalize(lightDir + viewDir);
        spec = pow(max(dot(normal, halfwayDir), 0.0), 32.0);
    }
    else
    {
        vec3 reflectDir = reflect(-lightDir, normal);
        spec = pow(max(dot(viewDir, reflectDir), 0.0), 8.0);
    }
    vec3 specular = vec3(0.3) * spec; // assuming bright white light color
    gl_FragColor = vec4(ambient + diffuse + specular, 1.0);
}
