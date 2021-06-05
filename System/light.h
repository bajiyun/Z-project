#pragma once
#include "LightHelper.h"

struct LightBuffer
{
	DirectionalLight dirLight[10];
	PointLight pointLight[10];
	SpotLight spotLight[10];
	int numDirLight;
	int numPointLight;
	int numSpotLight;
	float pad;
};

class CLight
{
public:
	static void InitResource();

	static void AddDirLight(DirectionalLight& light);
	static void AddPointLight(PointLight& light);
	static void AddSpotLight(SpotLight& light);

	static void ResetDirLight(DirectionalLight& light, int id);
	static void ResetPointLight(PointLight& light, int id);
	static void ResetSpotLight(SpotLight& light, int id);

	static void UpdateLightConstantBuffer();

	static ID3D11Buffer* GetLightBuffer() { return m_LightBuffer; }
	static LightBuffer GetLBuffer() { return m_Light; }
private:
	static ID3D11Buffer* m_LightBuffer;
	static LightBuffer m_Light;
};