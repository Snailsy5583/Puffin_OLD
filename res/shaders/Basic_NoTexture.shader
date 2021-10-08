#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

//uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

out vec3 fragPos;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * position;
	fragPos = vec3(u_Model * position);
};

#shader geometry
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

out vec3 normal;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

void main()
{
	normal = GetNormal();

	gl_Position = gl_in[0].gl_Position;
	EmitVertex();

	gl_Position = gl_in[1].gl_Position;
	EmitVertex();

	gl_Position = gl_in[2].gl_Position;
	EmitVertex();

	EndPrimitive();
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform vec3 u_LightPos;

in vec3 normal;
in vec3 fragPos;

void main()
{
	vec3 lightDir = normalize(u_LightPos - fragPos);
	color = u_Color * max(dot(normal, lightDir), 0.075f);
};