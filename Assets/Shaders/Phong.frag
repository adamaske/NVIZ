#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec3 LightPos;   // extra in variable, since we need the light position in view space we calculate this in the vertex shader

uniform vec3 u_LightColor = vec3(1.0, 1.0, 1.0);
uniform vec3 u_ObjectColor = vec3(0.9, 0.35, 0.25);
uniform float u_Opacity = 1.0; 
void main()
{
    // ambient
    float ambientStrength = 0.1;
    vec3 ambient = ambientStrength * u_LightColor;    
    
     // diffuse 
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(LightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * u_LightColor;
    
    // specular
    float specularStrength = 0.2;
    vec3 viewDir = normalize(-FragPos); // the viewer is always at (0,0,0) in view-space, so viewDir is (0,0,0) - Position => -Position
    vec3 reflectDir = reflect(-lightDir, norm);  
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32);
    vec3 specular = specularStrength * spec * u_LightColor; 
    
    vec3 result = (ambient + diffuse + specular) * u_ObjectColor;
    FragColor = vec4(result, u_Opacity);
}