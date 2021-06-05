//ŒõŒ¹Œ¤‹†—p
#include "Main.h"
#include "Renderer.h"
#include "light.h"
#include <cstring>
#include <DirectXMath.h>
#include <wrl/client.h>
#include <string>
#include <d3d11_1.h>

ID3D11Buffer*	 CLight::m_LightBuffer;
LightBuffer CLight::m_Light;

void CLight::InitResource()
{
	D3D11_BUFFER_DESC cbd;
	ZeroMemory(&cbd, sizeof(cbd));
	cbd.Usage = D3D11_USAGE_DYNAMIC;
	cbd.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	cbd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	cbd.MiscFlags = 0;
	cbd.StructureByteStride = sizeof(float);
	cbd.ByteWidth = sizeof(LightBuffer);

	CRenderer::GetDevice()->CreateBuffer(&cbd, nullptr, &m_LightBuffer);
	CRenderer::GetDeviceContext()->VSSetConstantBuffers(7, 1, &m_LightBuffer);
	CRenderer::GetDeviceContext()->PSSetConstantBuffers(7, 1, &m_LightBuffer);

	m_Light.dirLight[0].Ambient = D3DXVECTOR4(0.1f, 0.1f, 0.1f, 1.0f);
	m_Light.dirLight[0].Diffuse = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light.dirLight[0].Specular = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light.dirLight[0].Direction = D3DXVECTOR3(1.0f, -1.0f, -1.0f);

	m_Light.pointLight[0].Ambient = D3DXVECTOR4(0.3f, 0.3f, 0.3f, 1.0f);
	m_Light.pointLight[0].Diffuse = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light.pointLight[0].Specular = D3DXVECTOR4(0.5f, 0.5f, 0.5f, 1.0f);
	m_Light.pointLight[0].Position = D3DXVECTOR3(3.0f, 3.0f, -3.0f);
	m_Light.pointLight[0].Range = 8.0f;
	m_Light.pointLight[0].Att = D3DXVECTOR3(0.1f, 0.1f, 0.0f);

	m_Light.numDirLight = 1;
	m_Light.numPointLight = 1;
	m_Light.numSpotLight = 0;

	m_Light.numDirLight = 1;
	m_Light.numPointLight = 1;
	m_Light.numSpotLight = 0;

	//CRenderer::SetLightBuffer(m_Light);
	//CRenderer::GetDeviceContext()->UpdateSubresource(m_LightBuffer, 0, NULL, &m_Light, 0, 0);
}

void CLight::AddDirLight(DirectionalLight& light)
{
	if (m_Light.numDirLight >= 9)
	{
		return;
	}
	m_Light.dirLight[m_Light.numDirLight].Ambient = light.Ambient;
	m_Light.dirLight[m_Light.numDirLight].Diffuse = light.Diffuse;
	m_Light.dirLight[m_Light.numDirLight].Specular = light.Specular;
	m_Light.dirLight[m_Light.numDirLight].Direction = light.Direction;

	m_Light.numDirLight++;
	UpdateLightConstantBuffer();
}

void CLight::AddPointLight(PointLight& light)
{
	if (m_Light.numPointLight >= 9)
	{
		return;
	}
	m_Light.pointLight[m_Light.numPointLight].Ambient = light.Ambient;
	m_Light.pointLight[m_Light.numPointLight].Diffuse = light.Diffuse;
	m_Light.pointLight[m_Light.numPointLight].Specular = light.Specular;
	m_Light.pointLight[m_Light.numPointLight].Position = light.Position;
	m_Light.pointLight[m_Light.numPointLight].Range = light.Range;
	m_Light.pointLight[m_Light.numPointLight].Att = light.Att;

	m_Light.numPointLight++;
	UpdateLightConstantBuffer();
}

void CLight::AddSpotLight(SpotLight& light)
{
	if (m_Light.numSpotLight >= 9)
	{
		return;
	}
	m_Light.spotLight[m_Light.numDirLight].Ambient = light.Ambient;
	m_Light.spotLight[m_Light.numDirLight].Diffuse = light.Diffuse;
	m_Light.spotLight[m_Light.numDirLight].Specular = light.Specular;
	m_Light.spotLight[m_Light.numDirLight].Position = light.Position;
	m_Light.spotLight[m_Light.numDirLight].Range = light.Range;
	m_Light.spotLight[m_Light.numDirLight].Direction = light.Direction;
	m_Light.spotLight[m_Light.numDirLight].Spot = light.Spot;
	m_Light.spotLight[m_Light.numDirLight].Att = light.Att;

	m_Light.numSpotLight++;
	UpdateLightConstantBuffer();
}

void CLight::ResetDirLight(DirectionalLight& light, int id)
{
	if (id < 0 || id > m_Light.numDirLight - 1)
	{
		return;
	}
	m_Light.dirLight[id].Ambient = light.Ambient;
	m_Light.dirLight[id].Diffuse = light.Diffuse;
	m_Light.dirLight[id].Specular = light.Specular;
	m_Light.dirLight[id].Direction = light.Direction;

	UpdateLightConstantBuffer();
}

void CLight::ResetPointLight(PointLight& light, int id)
{
	if (id < 0 || id > m_Light.numPointLight - 1)
	{
		return;
	}
	m_Light.pointLight[id].Ambient = light.Ambient;
	m_Light.pointLight[id].Diffuse = light.Diffuse;
	m_Light.pointLight[id].Specular = light.Specular;
	m_Light.pointLight[id].Position = light.Position;
	m_Light.pointLight[id].Range = light.Range;
	m_Light.pointLight[id].Att = light.Att;

	UpdateLightConstantBuffer();
}

void CLight::ResetSpotLight(SpotLight& light, int id)
{
	if (id < 0 || id > m_Light.numSpotLight - 1)
	{
		return;
	}
	m_Light.spotLight[id].Ambient = light.Ambient;
	m_Light.spotLight[id].Diffuse = light.Diffuse;
	m_Light.spotLight[id].Specular = light.Specular;
	m_Light.spotLight[id].Position = light.Position;
	m_Light.spotLight[id].Range = light.Range;
	m_Light.spotLight[id].Direction = light.Direction;
	m_Light.spotLight[id].Spot = light.Spot;
	m_Light.spotLight[id].Att = light.Att;

	UpdateLightConstantBuffer();
}

void CLight::UpdateLightConstantBuffer()
{
	D3D11_MAPPED_SUBRESOURCE mappedData;
	CRenderer::GetDeviceContext()->Map(m_LightBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &mappedData);
	memcpy_s(mappedData.pData, sizeof(LightBuffer), &m_Light, sizeof(LightBuffer));
	CRenderer::GetDeviceContext()->Unmap(m_LightBuffer, 0);
}