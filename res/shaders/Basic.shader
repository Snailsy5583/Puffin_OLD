#shader vertex
#version 330 core

layout(location = 0) in vec4 position;
layout(location = 1) in vec2 texCoord;

out vec2 v_TexCoord;
out vec3 fragPos;

//uniform mat4 u_MVP;
uniform mat4 u_Model;
uniform mat4 u_View;
uniform mat4 u_Projection;

void main()
{
	gl_Position = u_Projection * u_View * u_Model * position;
	v_TexCoord = texCoord;
	fragPos = vec3(u_Model * position);
};

#shader geometry
#version 330 core

layout(triangles) in;
layout(triangle_strip, max_vertices=3) out;

out vec3 u_Normal;

vec3 GetNormal()
{
	vec3 a = vec3(gl_in[0].gl_Position) - vec3(gl_in[1].gl_Position);
	vec3 b = vec3(gl_in[2].gl_Position) - vec3(gl_in[1].gl_Position);
	return normalize(cross(a, b));
}

void main()
{
	u_Normal = GetNormal();
}

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoord;

in vec3 u_Normal;
in vec3 fragPos;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main()
{
	vec4 texColor = texture(u_Texture, v_TexCoord);
	color = u_Color * texColor * dot(u_Normal, vec3(0, 0, 1));
};