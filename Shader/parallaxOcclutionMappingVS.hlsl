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
    
    float3 Eye = normalize(CameraPosition - In.Position);
    
    Out.Eye.x = dot(Eye, In.Tangent);
    Out.Eye.y = dot(Eye, In.Binormal);
    Out.Eye.z = dot(Eye, In.Normal.xyz);
    Out.Eye = Out.Eye;
    
    //float3 m_Light = -Light.Direction.xyz;
    
    //Out.Light.x = dot(m_Light, In.Tangent);
    //Out.Light.y = dot(m_Light, In.Binormal);
    //Out.Light.z = dot(m_Light, In.Normal.xyz);
    //Out.Light = Out.Light;
    
    Out.Position = mul(In.Position, wvp);
    Out.WorldPosition = mul(In.Position, World);
    Out.Normal = worldNormal;
    Out.Diffuse = In.Diffuse;
    Out.TexCoord = In.TexCoord;
    Out.Tangent = normalize(mul(In.Tangent, (float3x3) World));
    Out.Binormal = normalize(mul(In.Binormal, (float3x3) World));

}