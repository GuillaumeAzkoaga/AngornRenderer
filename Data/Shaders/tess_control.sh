#version 400

                                             
layout (vertices = 3) out;

uniform float uTessLevelsOuter;
uniform float uTessLevelsInner;
uniform int useAdaptive;

uniform float slope;
uniform float m;

uniform vec3 camera_pos;

struct PhongPatch
{
 float termIJ;
 float termJK;
 float termIK;
};

                                                          
in vec3 Position[];                                                                       
in vec2 TextureCoord[];                                                                       
in vec3 Normal[];

                                                             
out vec3 WorldPos_ES_in[];                                                                     
out vec2 TexCoord_ES_in[];                                                                     
out vec3 Normal_ES_in[];
out PhongPatch oPhongPatch[];   
                                                                


float GetOuterTessLevelAdaptive(int index)                                            
{     
	float distance;
	switch(index)
	{
		case 0:
		{
			vec3 average = (Position[1] + Position[2]) / 2.0;
			distance = length(camera_pos - average);
			break;
		}
		case 1:
		{
			vec3 average = (Position[0] + Position[2]) / 2.0;
			distance = length(camera_pos - average);
			break;
		}
		case 2:
		{
			vec3 average = (Position[0] + Position[1]) / 2.0;
			distance = length(camera_pos - average);
			break;
		}
	}
	float level = slope * distance + 10.0;
	return max(level, 1.0);
}


float GetInnerTessLevel()                                            
{
	vec3 average = (Position[0] + Position[1] + Position[2]) / 3.0;
	float distance = length(camera_pos - average);
	
	float level = slope * distance + 10.0;
	return max(level, 1.0);
}

float PIi(int i, vec3 q)
{
	 vec3 q_minus_p = q - Position[i];
	 return q[gl_InvocationID] - dot(q_minus_p, Normal[i]) * Normal[i][gl_InvocationID];
}

float ComputeDepth(int index)
{
	return (1.0 - dot(Normal[index], normalize(-Position[index]))) * m;
}

float GetOuterSubdivisionLvl(int index)
{
	switch(index)
	{
	case 0:
		return (ComputeDepth(1) + ComputeDepth(2)) / 2.0;
	case 1:
		return (ComputeDepth(0) + ComputeDepth(2)) / 2.0;
	case 2:
		return (ComputeDepth(0) + ComputeDepth(1)) / 2.0;
   }
}

void main()                                                                                     
{                                                                                               
    // Set the control points of the output patch                                               
    TexCoord_ES_in[gl_InvocationID] = TextureCoord[gl_InvocationID];                          
    Normal_ES_in[gl_InvocationID]   = Normal[gl_InvocationID];                            
    WorldPos_ES_in[gl_InvocationID] = Position[gl_InvocationID];
	
	// compute patch data
	oPhongPatch[gl_InvocationID].termIJ = PIi(0,Position[1]) + PIi(1,Position[0]);
	oPhongPatch[gl_InvocationID].termJK = PIi(1,Position[2]) + PIi(2,Position[1]);
	oPhongPatch[gl_InvocationID].termIK = PIi(2,Position[0]) + PIi(0,Position[2]);

	// Compute the tessellation levels
	if(useAdaptive == 0)	
	{
		gl_TessLevelOuter[0] = uTessLevelsOuter;
		gl_TessLevelOuter[1] = uTessLevelsOuter;
		gl_TessLevelOuter[2] = uTessLevelsOuter;

		gl_TessLevelInner[0] =  uTessLevelsInner;
	}
	else
	{
		gl_TessLevelOuter[gl_InvocationID] = GetOuterSubdivisionLvl(gl_InvocationID) * GetOuterTessLevelAdaptive(gl_InvocationID);
	
		if(gl_InvocationID == 0)
		{
			gl_TessLevelInner[0] = ((ComputeDepth(0) + ComputeDepth(1) + ComputeDepth(2)) / 3.0) * GetInnerTessLevel();
		}
	}
}                                                                                               