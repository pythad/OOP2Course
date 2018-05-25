#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;

out vec3 FragPos;
out vec3 Normal;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform int axis;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    if (axis == 1) {
        FragPos.x /= 100;
    } else if (axis == 2) {
        FragPos.y /= 100;
    } else if (axis == 3) {
        FragPos.z /= 100;
    }
    Normal = mat3(transpose(inverse(model))) * aNormal;

    gl_Position = projection * view * vec4(FragPos, 1.0);
}
