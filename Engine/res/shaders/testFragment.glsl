#version 410 core

in vec3 normal;
in vec2 uv;
in vec3 color;

out vec4 fragColor;

void main()
{
	float ambientStrength = 0.3;
    vec3 ambient = ambientStrength * vec3(1);

	vec3 norm = normalize(normal);
	vec3 lightDir = normalize(-vec3(-0.3, -0.4, 0));
	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * vec3(1);

    vec3 result = (ambient + diffuse) * vec3(0.6, 0.6, 0.6);

	fragColor = vec4(result, 1);
}