#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target0,out float4 outNormal :SV_Target1)
{
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outNormal = In.Normal;
}
