#include "BasicShaderHeader.hlsli"

VSOutput main(float4 pos:POSITION, float3 normal : NORMAL, float2 uv : TEXCOORD,
	float3 tangent : TANGENT, float3 binormal : BINORMAL)
{
	VSOutput output;//sNZVF[_[Én·l
	////sñðposÉ½f
	output.svpos = mul(world, pos);
	output.svpos = mul(view, output.svpos);
	output.svpos = mul(projection, output.svpos);

	//uvð½f
	output.uv = uv;

	//@üÆsñÌvZ
	output.normal = mul(world, normal);
	output.normal = normalize(output.normal);

	//
	output.tangent = mul(world, tangent);
	output.tangent = normalize(output.tangent);

	//
	output.binormal = mul(world, binormal);
	output.binormal = normalize(output.binormal);

	return output;
}