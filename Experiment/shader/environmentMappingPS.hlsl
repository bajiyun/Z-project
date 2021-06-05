#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureEnv : register(t3);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float4 normal = normalize(In.Normal);
    
    //ランバート
    float light = -dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);
    
    //ハーフランバート
    //float light = 0.5 - 0.5 * dot(normal.xyz, Light.Direction.xyz);
    //light = saturate(light);
    
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    //outDiffuse.rgb *= round(In.Diffuse.rgb * light * 2) / 2;
    outDiffuse.a *= In.Diffuse.a;
    
    
    //スペキュラー(フォン）
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular *= saturate(1.0 + dot(eyev, normal.xyz));
    
    outDiffuse.rgb += specular;
    


    float3 refv2 = reflect(eyev, normal.xyz);
    refv2 = normalize(refv2);
    
    //環境マッピング
    float2 envTexCoord;
    envTexCoord.x = -refv2.x * 0.45 + 0.5;
    envTexCoord.y = -refv2.y * 0.45 + 0.5;
    
    outDiffuse.rgb += g_TextureEnv.Sample(g_SamplerState, envTexCoord).rgb;
    //outDiffuse.rgb += g_TextureEnv.SampleBias(g_SamplerState, envTexCoord, 3.0);
    
    
    //float n = 0.67;
    //float f0 = (1 - n) / (1 + n);
    //float fr = f0 + (1 - f0) * pow((1 - dot(refv, normal)), 5);
    //outDiffuse.rgb = outDiffuse.rgb + fr * envDiffuse.rgb;
    
}