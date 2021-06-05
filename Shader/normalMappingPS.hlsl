#include "common.hlsl"

Texture2D g_Texture : register(t0);
Texture2D g_TextureNormal : register(t1);
Texture2D g_TextureDisplacement : register(t2);
SamplerState g_SamplerState : register(s0);

void main(in PS_IN In, out float4 outDiffuse : SV_Target)
{
    float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    eyev = normalize(eyev);
    
    outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
   
    
    //法線マッピング
    //float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord + Parameter.x);
    float4 normalMap = g_TextureNormal.Sample(g_SamplerState, In.TexCoord);
    normalMap = (normalMap * 2.0) - 1.0;
    
    //normalMap.xyz = (normalMap.x * In.Tangent) + (-normalMap.y * In.Binormal) + (normalMap.z * In.Normal.xyz);
    //normalMap.w = 0;
    //normalMap = normalize(normalMap);
    
    
    float4 normal = normalMap;
    normal.x = normalMap.x;
    normal.y = normalMap.z;
    normal.z = normalMap.y;
    normal.w = 0.0;
    
    normal = normalize(normal);
    
    //outDiffuse = g_Texture.Sample(g_SamplerState, tex);
    
    //ランバート
    //float light = -dot(normal.xyz, Light.Direction.xyz);
    //light = saturate(light);
    
    //ハーフランバート
    float light = 0.5 - 0.5 * dot(normal.xyz, Light.Direction.xyz);
    light = saturate(light);
    
    //outDiffuse = g_Texture.Sample(g_SamplerState, In.TexCoord);
    outDiffuse.rgb *= In.Diffuse.rgb * light;
    //outDiffuse.rgb *= round(In.Diffuse.rgb * light * 2) / 2;
    outDiffuse.a *= In.Diffuse.a;
    
    
    //スペキュラー(フォン）
    //float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    //eyev = normalize(eyev);
    
    float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    refv = normalize(refv);
    
    float specular = -dot(eyev, refv);
    specular = saturate(specular);
    specular = pow(specular, 30);
    
    outDiffuse.rgb += specular *1.0;
    

    //ベルベット
    //float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    //eyev = normalize(eyev);
    
    //float3 refv = reflect(Light.Direction.xyz, normal.xyz);
    //refv = normalize(refv);
    
    //float specular = -dot(eyev, refv);
    //specular = saturate(specular);
    //specular *= saturate(1.0 + dot(eyev, normal.xyz));
    //outDiffuse.rgb += specular;
    
    
    
    ////スペキュラー（ブリン）
    //float3 eyev = In.WorldPosition.xyz - CameraPosition.xyz;
    //eyev = normalize(eyev);
    
    //float3 halfv = eyev + Light.Direction.xyz;
    //halfv = normalize(halfv);
    
    //float specular = -dot(halfv, normal.xyz);
    //specular = saturate(specular);
    //specular = pow(specular, 30);
    
    //outDiffuse.rgb += specular;
    
    
    
    //リムライティング
    //float rim = 1.0 + dot(eyev, normal.xyz);
    //rim = saturate(rim);
    //rim = pow(rim, 3) * 0.4;
    //outDiffuse.rgb += rim;
    
    //float rim = 1.0 + dot(eyev, normal.xyz);
    //rim = pow(rim, 3);
    //outDiffuse.rgb += rim * 0.4;
    
    
    //フレネル反射
    //float fresnel = 1.0 + dot(eyev, normal.xyz);
    //fresnel = 0.2 + (1.0 - 0.2) * pow(fresnel, 5.0);
    //outDiffuse.rgb *= 1.0 - fresnel;
    //outDiffuse.rgb += fresnel;
    
    
    //線性フォグ
    //float dist = distance(in.worldposition.xyz, cameraposition.xyz);
    //float fog = saturate(dist / 10.0);
    
    //outdiffuse.rgb = outdiffuse.rgb * (1.0 - fog) + float3(0.5, 0.5, 0.5) * fog;
    //outdiffuse.rgb = lerp(outdiffuse.rgb, float3(0.5, 0.5, 0.5), fog);
    
    
    
}