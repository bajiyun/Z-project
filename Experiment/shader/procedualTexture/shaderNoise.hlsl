

float random2(in float2 vec)
{
    //return frac(sin(dot(vec.xy, float2(12.998, 78.233))) * 4378.545);
    return frac(sin(dot(vec.xy, float2(13.998, 52.233))) * 2378.545);
}

float2 random22(in float2 vec)
{
    vec = float2(dot(vec, float2(127.1, 311.7)), dot(vec, float2(269.5, 183.3)));
    return frac(sin(vec) * (4378.545));
}

float random3(in float3 vec)
{
    return frac(sin(dot(vec.xyz,float3(12.9898, 78.233, 47.2311))) * 4358.54);

}

float3 random33(in float3 vec)
{
    vec = float3(dot(vec, float3(127.1, 311.7, 245.4)),
                        dot(vec, float3(269.5, 183.3, 131.2)),
                        dot(vec, float3(522.3, 243.1, 532.4)));
    return frac(sin(vec) * 4358.54);
}

float2 voronoi2(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);
    
    float value = 1.0;
    
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1;x++)
        {
            float2 offset = float2(x, y);
            
            float2 position;
            position = random22(ivec + offset);
            
            float dist = distance(position + offset, fvec);
            
            value = min(value, dist);
            
        }
    }
    return value;
}

float3 voronoi3(in float3 vec)
{
    float3 ivec = floor(vec);
    float3 fvec = frac(vec);
    
    float value = 1.0;
    
    for (int z = -1; z <= 1;z++)
    {   
        for (int y = -1; y <= 1; y++)
        {
            for (int x = -1; x <= 1; x++)
            {
                float3 offset = float3(x, y,z);
            
                float3 position;
                position = random33(ivec + offset);
            
                float dist = distance(position + offset, fvec);
            
                value = min(value, dist);
            
            }
        }
    }
    return value;
}
float valueNoise2(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);
    
    float a = random2(ivec + float2(0.0, 0.0));
    float b = random2(ivec + float2(1.0, 0.0));
    float c = random2(ivec + float2(0.0, 1.0));
    float d = random2(ivec + float2(1.0, 1.0));
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    return lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y);
    
}

float valueNoise3(in float3 vec)
{
    float3 ivec = floor(vec);
    float3 fvec = frac(vec);
    
    float a = random3(ivec + float3(0.0, 0.0,0.0));
    float b = random3(ivec + float3(1.0, 0.0,0.0));
    float c = random3(ivec + float3(0.0, 1.0,0.0));
    float d = random3(ivec + float3(1.0, 1.0,0.0));
    
    float e = random3(ivec + float3(0.0, 0.0, 1.0));
    float f = random3(ivec + float3(1.0, 0.0, 1.0));
    float g = random3(ivec + float3(0.0, 1.0, 1.0));
    float h = random3(ivec + float3(1.0, 1.0, 1.0));
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    float v1 = lerp(a, b, fvec.x);
    float v2 = lerp(c, d, fvec.x);
    float v3 = lerp(v1, v2, fvec.y);
    
    float v4 = lerp(e, f, fvec.x);
    float v5 = lerp(g, h, fvec.x);
    float v6 = lerp(v4, v5, fvec.y);
    
    float v7 = lerp(v3, v6, fvec.z);
    
    return v7;
}

float perlinNoise2(in float2 vec)
{
    float2 ivec = floor(vec);
    float2 fvec = frac(vec);
    
    float a = dot(random22(ivec + float2(0.0, 0.0)) * 2.0 - 1.0, fvec - float2(0.0, 0.0));
    float b = dot(random22(ivec + float2(1.0, 0.0)) * 2.0 - 1.0, fvec - float2(1.0, 0.0));
    float c = dot(random22(ivec + float2(0.0, 1.0)) * 2.0 - 1.0, fvec - float2(0.0, 1.0));
    float d = dot(random22(ivec + float2(1.0, 1.0)) * 2.0 - 1.0, fvec - float2(1.0, 1.0));
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    return lerp(lerp(a, b, fvec.x), lerp(c, d, fvec.x), fvec.y);
}

float perlinNoise3(in float3 vec)
{
    float3 ivec = floor(vec);
    float3 fvec = frac(vec);
    
    float a = dot(random33(ivec + float3(0.0, 0.0,0.0)) * 2.0 - 1.0, fvec - float3(0.0, 0.0,0.0));
    float b = dot(random33(ivec + float3(1.0, 0.0,0.0)) * 2.0 - 1.0, fvec - float3(1.0, 0.0,0.0));
    float c = dot(random33(ivec + float3(0.0, 1.0,0.0)) * 2.0 - 1.0, fvec - float3(0.0, 1.0,0.0));
    float d = dot(random33(ivec + float3(1.0, 1.0,0.0)) * 2.0 - 1.0, fvec - float3(1.0, 1.0,0.0));
    
    float e = dot(random33(ivec + float3(0.0, 0.0, 1.0)) * 2.0 - 1.0, fvec - float3(0.0, 0.0, 1.0));
    float f = dot(random33(ivec + float3(1.0, 0.0, 1.0)) * 2.0 - 1.0, fvec - float3(1.0, 0.0, 1.0));
    float g = dot(random33(ivec + float3(0.0, 1.0, 1.0)) * 2.0 - 1.0, fvec - float3(0.0, 1.0, 1.0));
    float h = dot(random33(ivec + float3(1.0, 1.0, 1.0)) * 2.0 - 1.0, fvec - float3(1.0, 1.0, 1.0));
    
    fvec = smoothstep(0.0, 1.0, fvec);
    
    float v1 = lerp(a, b, fvec.x);
    float v2 = lerp(c, d, fvec.x);
    float v3 = lerp(v1, v2, fvec.y);
    
    float v4 = lerp(e, f, fvec.x);
    float v5 = lerp(g, h, fvec.x);
    float v6 = lerp(v4, v5, fvec.y);
    
    float v7 = lerp(v3, v6, fvec.z);
    
    return v7;
}


//非整数ブラウン運動2D（フラクタルパーリンノイズ
float fbm2 (in float2 vec, int octave)
{
    float value = 0.0;
    float amplitude = 1.0;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * perlinNoise2(vec);
        vec *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}

float fbm3(in float3 vec, int octave)
{
    float value = 0.0;
    float amplitude = 1.0;
    
    for (int i = 0; i < octave; i++)
    {
        value += amplitude * perlinNoise3(vec);
        vec *= 2.0;
        amplitude *= 0.5;
    }
    return value;
}