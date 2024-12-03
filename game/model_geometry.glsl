#version 460 core
layout (triangles) in;
layout (triangle_strip, max_vertices = 256) out;

uniform int count;
uniform mat4 projection;
int index = 0;

in VS_OUT
{
	vec3 FragPos;
	vec3 Normal;
	vec2 TexCoords;
	vec3 Tangent;
} fs_in[];

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;
out vec3 Tangent;

void GenerateTriangles(vec3 pos[3], int depth)
{
    vec3 stack[256][3];
    int stackDepth[256];
    int stackIndex = 0;

    stack[stackIndex][0] = pos[0];
    stack[stackIndex][1] = pos[1];
    stack[stackIndex][2] = pos[2];
    stackDepth[stackIndex] = depth;
    stackIndex++;

    while (stackIndex > 0)
    {
        stackIndex--;
        vec3 currentPos[3] = { stack[stackIndex][0], stack[stackIndex][1], stack[stackIndex][2] };
        int currentDepth = stackDepth[stackIndex];

        if (currentDepth == 0)
        {
            gl_Position = vec4(currentPos[0], 1.0);
            EmitVertex();
            gl_Position = vec4(currentPos[1], 1.0);
            EmitVertex();
            gl_Position = vec4(currentPos[2], 1.0);
            EmitVertex();
            EndPrimitive();
        }
        else
        {
            vec3 mid[3];
            mid[0] = mix(currentPos[0], currentPos[1], 0.5);
            mid[1] = mix(currentPos[1], currentPos[2], 0.5);
            mid[2] = mix(currentPos[2], currentPos[0], 0.5);

            vec3 newPos[3][3] = {
                {currentPos[0], mid[0], mid[2]},
                {mid[0], currentPos[1], mid[1]},
                {mid[2], mid[1], currentPos[2]}
            };

            for (int i = 0; i < 3; ++i)
            {
                stack[stackIndex][0] = newPos[i][0];
                stack[stackIndex][1] = newPos[i][1];
                stack[stackIndex][2] = newPos[i][2];
                stackDepth[stackIndex] = currentDepth - 1;
                stackIndex++;
            }
        }
    }
}

void main()
{
    vec3 pos_in[3];
    for (int i = 0; i < 3; ++i) {
        pos_in[i] = gl_in[i].gl_Position.xyz;
    }
    GenerateTriangles(pos_in, count);
    FragPos = fs_in[0].FragPos;
    Normal = fs_in[0].Normal;
    TexCoords = fs_in[0].TexCoords;
    Tangent = fs_in[0].Tangent;

}