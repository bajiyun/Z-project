#include "common.hlsl"

Texture2D g_Texture : register(t0);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 normal = normalize(In.Normal);
    
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.a *= In.Diffuse.a;
    
    //ハーフランバート
    float light = 0.5 - 0.8 * dot(normal.xyz, Light.Direction.xyz);    
    //light = saturate(light);
    
    if (light >0.5)
        light = 1.0;
    else
        light = 0.5;
    
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    
    //輪郭
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float d = dot(eyev, normal.xyz);
    
    if(d > -0.3)
        outDiffuse.rgb *= 0.3;
}