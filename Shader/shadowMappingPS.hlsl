#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureShadowDepth : register(t4);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    
    
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    
    outDiffuse *= In.Diffuse;
    
    In.ShadowPosition.xyz /= In.ShadowPosition.w;
    In.ShadowPosition.x = In.ShadowPosition.x * 0.5 + 0.5;
    In.ShadowPosition.y = -In.ShadowPosition.y * 0.5 + 0.5;
    
    float depth = g_TextureShadowDepth.Sample(g_SamplerState, In.ShadowPosition.xy);
    
    float2 data[4];
    data[0] = float2(-0.94201624, -0.39906216);
    data[1] = float2(0.94558609, -0.76890725);
    data[2] = float2(-0.094184101, -0.92938870);
    data[3] = float2(0.34495938, 0.29387760);
    
    float v = 1.0;
    
    for (int i = 0; i < 4; i++)
    {
        depth = g_TextureShadowDepth.Sample(g_SamplerState, In.ShadowPosition.xy + data[i] / 700.0);
        if (depth < In.ShadowPosition.z - 0.01)
            v -= 0.2;
    }

    outDiffuse *= v;
    outDiffuse.a = 1.0;

}