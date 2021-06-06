
#include "shaderNoise.hlsl"


Texture2D		g_Texture : register(t0);
SamplerState	g_SamplerState : register(s0);



//=============================================================================
// ピクセルシェーダ
//=============================================================================
void main( in  float4 inPosition		: SV_POSITION,
			in  float4 inNormal			: NORMAL0,
			in  float4 inDiffuse		: COLOR0,
			in  float2 inTexCoord		: TEXCOORD0,

			out float4 outDiffuse		: SV_Target )
{
    
   //outDiffuse.rgb = fmod(inTexCoord.x,2);
   //outDiffuse.rgb = floor(inTexCoord.x);

    //黒白並べ
    
    //float n, m;
    //if (fmod(floor(inTexCoord.y), 2) == 0)
    //    n = 1;
    //else
    //    n = -1;
    //if (fmod(floor(inTexCoord.x), 2) == 0)
    //    m = -1;
    //else
    //    m = 1;
    
    //float2 random = (1, 2);
    
    //outDiffuse.rgb = clamp(m * n, 0, 1);
    //outDiffuse.a = 1.0f;

    //黒白並べ（方法２
      
    //outDiffuse.rgb = 1 - inPosition.x / 200;

    //int x = inPosition.x / 20;
    //int y = inPosition.y / 20;
    
    //if (x % 2 == 1 && y % 2 == 1)
    //{
    //    outDiffuse.rgb = 1;
    //}
    //else if (x % 2 == 1 && y % 2 == 0)
    //{
    //    outDiffuse.rgb = 0;
    //}
    //else if (x % 2 == 0 && y % 2 == 1)
    //{
    //    outDiffuse.rgb = 0;
    //}
    //else if (x % 2 == 0 && y % 2 == 0)
    //{
    //    outDiffuse.rgb = 1;
    //}

    //outDiffuse.a = 1.0;

    //ホワイトノイズ

    //outDiffuse.rgb = random2(inTexCoord);
    //outDiffuse.a = 1.0;
    
    //バリューノイズ
    
    //float color = voronoi2(inTexCoord);
    //outDiffuse.rgb = color;
    
    //outDiffuse.a = 1.0;
    
    //バリューノイズの応用
    
    //float color = voronoi2(inTexCoord * 0.2);
    //outDiffuse.rgb = fmod(color * 20.0, 2);
    
    //outDiffuse.a = 1.0;
    
    //パーリンノイズ

    //outDiffuse.rgb = perlinNoise2(inTexCoord) * 0.5 + 0.5;
    //outDiffuse.a = 1.0;
    
    //パーリンノイズの応用
    
    //float color = perlinNoise2(inTexCoord * 0.5) * 0.5 + 0.5;
    //outDiffuse.rgb = fmod(color * 20.0, 2);
    
    //outDiffuse.a = 1.0;
    
    //フラクタルノイズ
    
    //float color = fbm2(inTexCoord * 0.5, 10) * 0.5 + 0.5;
    //outDiffuse.rgb = sin(color * 20.0);
    //outDiffuse.a = 1.0;
    
    //フラクタルノイズの応用
    
    //float color = fbm2(inTexCoord * 0.5, 10) * 0.5 + 0.5;
    //outDiffuse.rgb = step(color, 0.5);
    //outDiffuse.a = 1.0;

    //雲
    
    //float color = fbm2(inTexCoord * 0.5, 10) * 0.5 + 0.5;
    //outDiffuse.rgb = color;
    //outDiffuse.a = 1.0;
    
    //木目
    
    //float color = fbm2(inTexCoord * 0.2, 2);
    //color = (sin(color * 100) * 0.5 + 0.5);
    //outDiffuse.rgb = float3(0.5, 0.2, 0.1) * color + float3(0.9, 0.7, 0.4) * (1.0 - color);
    //outDiffuse.a = 1.0;
    
}
