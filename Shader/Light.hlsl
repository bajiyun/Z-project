#include "Common.hlsl"

struct DirectionalLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    float3 Direction;
    float Pad;
};

struct PointLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;
    
    float3 Position;
    float Range;
    
    float3 Att;
    float Pad;
};

struct SpotLight
{
    float4 Ambient;
    float4 Diffuse;
    float4 Specular;

    float3 Position;
    float Range;

    float3 Direction;
    float Spot;

    float3 Att;
    float Pad;
};


cbuffer LightBuffer : register(b7)
{
    DirectionalLight dirLight[10];
    PointLight pointLight[10];
    SpotLight spotLight[10];
    int numDirLight;
    int numPointLight;
    int numSpotLight;
    float Pad;
}

void ComputeDirectionalLight(MATERIAL mat, DirectionalLight L, float3 normal, float3 toEye,
        out float4 ambient, out float4 diffuse, out float4 spec)
{
    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    float3 lightVec = -L.Direction;
    lightVec = normalize(lightVec);
    
    ambient = mat.Ambient * L.Ambient;
    
    float diffuseFactor = dot(lightVec, normal);
    
    [flatten]
    if (diffuseFactor > 0.0f)
    {
        float3 r = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(r, toEye), 0.0f), mat.Shininess);
        
        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }
}



void ComputePointLight(MATERIAL mat, PointLight L, float3 pos, float3 normal, float3 toEye,
        out float4 ambient, out float4 diffuse, out float4 spec)
{

    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    

    float3 lightVec = L.Position - pos;

    float d = length(lightVec);
    

    if (d > L.Range)
    {
        return;
    }
    

    lightVec /= d;
    

    ambient = mat.Ambient * L.Ambient;
    

    float diffuseFactor = dot(lightVec, normal);
    
    [flatten]
    if (diffuseFactor > 0.0f)
    {
        float3 r = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(r, toEye), 0.0f), mat.Shininess);
        
        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }
    

    float att = 1.0f / dot(L.Att, float3(1.0f, d, d * d));
    
    diffuse *= att;
    spec *= att;
}

void ComputeSpotLight(MATERIAL mat, SpotLight L, float3 pos, float3 normal, float3 toEye,
        out float4 ambient, out float4 diffuse, out float4 spec)
{

    ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    

    float3 lightVec = L.Position - pos;
    

    float d = length(lightVec);
    

    if (d > L.Range)
    {
        return;
    }
    

    lightVec /= d;
    

    ambient = mat.Ambient * L.Ambient;
    

    float diffuseFactor = dot(lightVec, normal);
    
    [flatten]
    if (diffuseFactor > 0.0f)
    {
        float3 r = reflect(-lightVec, normal);
        float specFactor = pow(max(dot(r, toEye), 0.0f), mat.Shininess);
        
        diffuse = diffuseFactor * mat.Diffuse * L.Diffuse;
        spec = specFactor * mat.Specular * L.Specular;
    }
    

    float spot = pow(max(dot(-lightVec, L.Direction), 0.0f), L.Spot);
    float att = spot / dot(L.Att, float3(1.0f, d, d * d));
    
    ambient *= spot;
    diffuse *= att;
    spec *= att;
}





float4 ComputeCommonLights(PS_IN In, float4 texColor, float3 normal, float3 toEyeW)
{

    float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 spec = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 A = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 D = float4(0.0f, 0.0f, 0.0f, 0.0f);
    float4 S = float4(0.0f, 0.0f, 0.0f, 0.0f);
    
    int i; //cnt
    

    for (i = 0; i < numDirLight; ++i)
    {
        ComputeDirectionalLight(Material, dirLight[i], normal, toEyeW, A, D, S);
        ambient += A;
        diffuse += D;
        spec += S;
    }
    
         

    for (i = 0; i < numPointLight; ++i)
    {
        ComputePointLight(Material, pointLight[i], In.WorldPosition.xyz, normal, toEyeW, A, D, S);
        ambient += A;
        diffuse += D;
        spec += S;
    }
        
    

    for (i = 0; i < numSpotLight; ++i)
    {
        ComputeSpotLight(Material, spotLight[i], In.WorldPosition.xyz, normal, toEyeW, A, D, S);
        ambient += A;
        diffuse += D;
        spec += S;
    }
    
    float4 litColor = texColor * (ambient + diffuse) + spec;
    litColor.a = Material.Diffuse.a * In.Diffuse.a;
    
    return litColor;
}