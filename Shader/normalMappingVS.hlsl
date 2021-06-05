#include "common.hlsl"

void main(in VS_IN In, out PS_IN Out)
{
    matrix wvp;
    wvp = mul(World, View);
    wvp = mul(wvp, Projection);
    
    float4 worldNormal, normal;
    normal = float4(In.Normal.xyz, 0.0);
    worldNormal = mul(normal, World);
    worldNormal = normalize(worldNormal);
    
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.Normal = worldNormal;
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
    Out.Tangent = normalize(mul(In.Tangent, (float3x3) World));
    Out.Binormal = normalize(mul(In.Binormal, (float3x3) World));

}