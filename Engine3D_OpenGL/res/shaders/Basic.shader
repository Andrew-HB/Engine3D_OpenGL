#shader vertex
#version 330 core

layout(location = 0) in vec4 positions;
layout(location = 1) in float vertexColor;

out vec3 fragmentColor;

void main()
{
	fragmentColor = vec3(vertexColor);
	gl_Position = positions;
};

#shader fragment
#version 330 core

in vec3 fragmentColor;
out vec3 color;

void main()
{
	color = vec3(fragmentColor);
};