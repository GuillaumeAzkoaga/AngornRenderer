#version 400

layout(triangles, equal_spacing, ccw) in;

// Phong tess patch data
struct PhongPatch
{
 float termIJ;
 float termJK;
 float termIK;
};

uniform mat4 projMat;                

in vec3 WorldPos_ES_in[];                                                                      
in vec2 TexCoord_ES_in[];                                                                      
in vec3 Normal_ES_in[];
in PhongPatch oPhongPatch[];

out vec3 WorldPos0;                                                                         
out vec2 UV;                                                                        
out vec3 Normal0;

uniform float uTessAlpha;

vec2 interpolate2D(vec2 v0, vec2 v1, vec2 v2)                                                   
{                                                                                            
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;   
}   

vec3 interpolate3D(vec3 v0, vec3 v1, vec3 v2)                                                   
{                                                                                            
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;   
}

void main()                                                                                     
{             
	// Interpolate the attributes of the output vertex using the barycentric coordinates        
    UV = interpolate2D(TexCoord_ES_in[0], TexCoord_ES_in[1], TexCoord_ES_in[2]);    
    Normal0 = interpolate3D(Normal_ES_in[0], Normal_ES_in[1], Normal_ES_in[2]);            
    Normal0 = normalize(Normal0);     
	// interpolated position
	vec3 barPos = interpolate3D(WorldPos_ES_in[0], WorldPos_ES_in[1], WorldPos_ES_in[2]);
	
	// build terms
	vec3 termIJ = vec3(oPhongPatch[0].termIJ, oPhongPatch[1].termIJ, oPhongPatch[2].termIJ);
	vec3 termJK = vec3(oPhongPatch[0].termJK, oPhongPatch[1].termJK, oPhongPatch[2].termJK);
	vec3 termIK = vec3(oPhongPatch[0].termIK, oPhongPatch[1].termIK, oPhongPatch[2].termIK);
	
	// precompute squared tesscoords
	vec3 tc2 = gl_TessCoord * gl_TessCoord;
	
	// phong tesselated pos
	vec3 phongPos   = 	tc2[0]*WorldPos_ES_in[0] 
						+ tc2[1]*WorldPos_ES_in[1] 
						+ tc2[2]*WorldPos_ES_in[2] 
						+ gl_TessCoord[0]*gl_TessCoord[1]*termIJ 
						+ gl_TessCoord[1]*gl_TessCoord[2]*termJK 
						+ gl_TessCoord[2]*gl_TessCoord[0]*termIK;
	
	// final position
	WorldPos0 = (1.0 - uTessAlpha) * barPos + uTessAlpha * phongPos;
	gl_Position   = projMat * vec4(WorldPos0,1.0);                                           
}                                                                                               
