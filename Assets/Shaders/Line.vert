#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec4 a_Color;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ProjectionMatrix;
uniform mat4 u_Transform; 

uniform float u_LineWidth; // Used for metadata/debug (ignored by rasterizer for thickness)
 

void main()
{
    
    gl_Position = u_ProjectionMatrix * u_ViewMatrix * u_Transform * vec4(a_Position, 1.0);
}