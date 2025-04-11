#version 330 core
in vec3 FragPos;
in vec3 Normal;
in vec3 Color;

out vec4 FragColor;

uniform vec3 lightDir = normalize(vec3(-0.5, -1.0, -0.3));
uniform vec3 lightColor = vec3(1.0);
uniform vec3 ambientColor = vec3(0.3);

void main() {
    float diff = max(dot(normalize(Normal), -lightDir), 0.0);
    vec3 lighting = (ambientColor + diff * lightColor) * Color;
    FragColor = vec4(lighting, 1.0);
}
