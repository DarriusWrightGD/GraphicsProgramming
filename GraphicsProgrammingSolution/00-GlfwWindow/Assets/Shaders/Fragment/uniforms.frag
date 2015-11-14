#version 450 core

in VS_OUT{
	vec4 color;
}fs_in;

out vec4 color;

//void main()
//{
//	color = fs_in.color;
//}

float far = 1000.0f;
float near = 1.0f;

float LinearizeDepth(float depth) 
{
    float z = depth * 2.0 - 1.0; // Back to NDC 
    return (2.0 * near * far) / (far + near - z * (far - near));	
}

void main()
{             
    float depth = LinearizeDepth(gl_FragCoord.z) / far; // divide by far for demonstration
    color = vec4(vec3(depth), 1.0f);
}