#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureFur : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    
    outDiffuse *= In.Diffuse;
    outDiffuse.a *= g_TextureFur.Sample(g_SamplerState, In.TexCoord).a;
}