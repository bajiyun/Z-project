#include "common.hlsl"

Texture2D g_TextureDiffuse : register(t0);
Texture2D g_TextureNormal : register(t1);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In,out float4 outDiffuse :SV_Target)
{
    float4 diffuse = g_TextureDiffuse.Sample(g_SamplerState, In.TexCoord);
    float4 normal = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
    
    //ランバート
    float light = -dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);    
    outDiffuse.rgb = diffuse.rgb * light;
        
    //スペキュラー(フォン）
    /*
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 20);
    outDiffuse.rgb += specular;
    */
    
    
    outDiffuse.a = diffuse.a;
    //outDiffuse.rgb = normal.rgb;
}