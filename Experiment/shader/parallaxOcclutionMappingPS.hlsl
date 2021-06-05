#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
Texture2D g_TextureDisplacement : register(t2);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    float heightMax = 0.03;
    float step = 64;
    float heightScale = heightMax / step;
    
    float2 offset = eyev.xy * heightScale;
    offset.x = -eyev.x * heightScale / eyev.y;
    offset.y = eyev.z * heightScale / eyev.y;
    
    float4 normalMap;
    float heightMap;
    float currentHeight = 0.0;
    
    float2 tex = In.TexCoord;
    tex.x = In.TexCoord.x + eyev.x * heightMax / eyev.y;
    tex.y = In.TexCoord.y - eyev.z * heightMax / eyev.y;

    
    for (int i = 0; i < step ; ++i)
    {
        heightMap = 1 - g_TextureDisplacement.Sample(g_SamplerState, tex).r;
        
        if(currentHeight >= (heightMap)*heightMax)
        {
            break;
        }
        
        tex += offset;
        currentHeight += heightScale;

    }
    
    
    normalMap = g_TextureNormal.Sample(g_SamplerState, tex);
    normalMap = (normalMap * 2.0) - 1.0;
    normalMap.xyz = (normalMap.x * In.Tangent) + (-normalMap.y * In.Binormal) + (normalMap.z * In.Normal.xyz);
    normalMap.w = 0;
    float4 normal = normalize(normalMap);
    
    outDiffuse = g_Texture.Sample(g_SamplerState, tex);
    
    //ハーフランバート
    float light = 0.5 - 0.5 * dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);
    
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    outDiffuse.a *= In.Diffuse.a;
    
    

    //スペキュラー(フォン）    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 30);
    
    outDiffuse.rgb += specular * 1.0;
    
    
}