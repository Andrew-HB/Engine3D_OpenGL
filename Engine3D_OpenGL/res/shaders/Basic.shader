#shader vertex
#version 330 core

layout(location = 0) in vec4 positions;
layout(location = 0) in float vertexColor;

out float fragmentColor;

void main()
{
	fragmentColor = vertexColor;
    gl_Position = positions;
};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in float fragmentColor;

out vec3 color;

void main() {
    color.x = fragmentColor * 255;
    color.y = fragmentColor * 255;
    color.z = fragmentColor * 255;
}