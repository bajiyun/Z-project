

#include "shaderNoise.hlsl"

Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);


// �萔�o�b�t�@
cbuffer ConstatntBuffer : register(b0)
{
    matrix World;
    matrix View;
    matrix Projection;

    float4 CameraPosition;
    float4 Para;
}

//=============================================================================
// �s�N�Z���V�F�[�_
//=============================================================================
void main(  in float4 inPosition		: SV_POSITION,
            in float4 inWorldPosition   : POSITION0,
			in float4 inLocalPosition   : POSITION1,
			in float4 inNormal			: NORMAL0,
			in float4 inDiffuse		    : COLOR0,
			in float2 inTexCoord		: TEXCOORD0,

			out float4 outDiffuse		: SV_Target )
{

    //�X�g���C�v
    //outDiffuse.rgb = fmod(floor(inLocalPosition.x * 10.0 + 20.0), 2);

    //�z���C�g�m�C�Y
    //outDiffuse.rgb = random3(inLocalPosition.xyz);

    //�o�����[�m�C�Y
    //outDiffuse.rgb = valueNoise3(inLocalPosition.xyz*40.0);
    
    //�p�[�����m�C�Y
    //outDiffuse.rgb = perlinNoise3(inLocalPosition.xyz * 10.0) * 0.5 + 0.5;
    
    //�t���N�^���m�C�Y
    //outDiffuse.rgb = fbm3(inLocalPosition.xyz * 10.0, 4) * 0.5 + 0.5;
    
    //�ؖ�
    //float color = fbm3(inLocalPosition.xyz * 2.0, 2);
    //color = (sin(color * 100) * 0.5 + 0.5);
    //outDiffuse.rgb = float3(0.5, 0.2, 0.1) * color + float3(0.9, 0.7, 0.4) * (1.0 - color);
    
    
    //����
    float color1 = fbm3(inLocalPosition.xyz * 8.0 , 6) * 0.5 + 0.5;
    color1 = step(color1, 0.5);
    
    outDiffuse.rgb = float3(0.2, 0.3, 0.2) * color1 + (1.0 - color1);
    
    float color2 = fbm3(inLocalPosition.xyz * 5.0 + 40.0, 4) * 0.5 + 0.5;
    color2 = step(color2, 0.5);
    
    outDiffuse.rgb += float3(0.2, 0.4, 0.2) * color2 + (1.0 - color2);
    
    outDiffuse.rgb -= 1.1;
    
    //------------------------------------------------    
    
    outDiffuse.a = 1.0f;

    //���C�e�B���O
    float3 lightDir = float3(1.0, -1.0, 1.0);
    lightDir = normalize(lightDir);
    
    float light = 0.5 - dot(inNormal.xyz, lightDir) * 0.5;
    outDiffuse.rgb *= light;

	outDiffuse.a = 1.0;
  
}
