#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "scene.h"
#include "ui_number.h"
#include "camera.h"

ID3D11Buffer* CUiNumber::m_VertexBuffer = NULL;
ID3D11ShaderResourceView* CUiNumber::m_Texture = NULL;

void CUiNumber::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(50.0f, 0.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[1].TexCoord = D3DXVECTOR2(0.2f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(0.0f, 50.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 0.2f);

	vertex[3].Position = D3DXVECTOR3(50.0f, 50.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[3].TexCoord = D3DXVECTOR2(0.2f, 0.2f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DYNAMIC;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/number.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexShader.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "pixelShader.cso");
}

void CUiNumber::Uninit()
{
}

void CUiNumber::Update()
{
}

void CUiNumber::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	//入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダー設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	float x = m_Count % 5 * (1.0f / 5);
	float y = m_Count / 5 * (1.0f / 5);

	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(number_Position.x - 25.0f, number_Position.y - 25.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[0].TexCoord = D3DXVECTOR2(x, y);

	vertex[1].Position = D3DXVECTOR3(number_Position.x + 25.0f, number_Position.y - 25.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[1].TexCoord = D3DXVECTOR2(x + (1.0f / 5), y);

	vertex[2].Position = D3DXVECTOR3(number_Position.x - 25.0f, number_Position.y + 25.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[2].TexCoord = D3DXVECTOR2(x, y + (1.0f / 5));

	vertex[3].Position = D3DXVECTOR3(number_Position.x + 25.0f, number_Position.y + 25.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[3].TexCoord = D3DXVECTOR2(x + (1.0f / 5), y + (1.0f / 5));

	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//マトリクス設定
	CRenderer::SetWorldViewProjection2D();
	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}

void CUiNumber::Draw(D3DXVECTOR2 Position, int number)
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	//入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダー設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

	float x = number % 5 * (1.0f / 5);
	float y = number / 5 * (1.0f / 5);

	D3D11_MAPPED_SUBRESOURCE msr;
	CRenderer::GetDeviceContext()->Map(m_VertexBuffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &msr);
	VERTEX_3D* vertex = (VERTEX_3D*)msr.pData;

	vertex[0].Position = D3DXVECTOR3(Position.x - 25.0f, Position.y - 25.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[0].TexCoord = D3DXVECTOR2(x, y);

	vertex[1].Position = D3DXVECTOR3(Position.x + 25.0f, Position.y - 25.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[1].TexCoord = D3DXVECTOR2(x + (1.0f / 5), y);

	vertex[2].Position = D3DXVECTOR3(Position.x - 25.0f, Position.y + 25.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[2].TexCoord = D3DXVECTOR2(x, y + (1.0f / 5));

	vertex[3].Position = D3DXVECTOR3(Position.x + 25.0f, Position.y + 25.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.8f);
	vertex[3].TexCoord = D3DXVECTOR2(x + (1.0f / 5), y + (1.0f / 5));

	CRenderer::GetDeviceContext()->Unmap(m_VertexBuffer, 0);

	//マトリクス設定
	CRenderer::SetWorldViewProjection2D();
	//頂点バッファ設定
	UINT stride = sizeof(VERTEX_3D);
	UINT offset = 0;
	CRenderer::GetDeviceContext()->IASetVertexBuffers(0, 1, &m_VertexBuffer, &stride, &offset);
	//マテリアル設定
	MATERIAL material;
	ZeroMemory(&material, sizeof(material));
	material.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
	CRenderer::SetMaterial(material);
	//テクスチャ設定
	CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &m_Texture);
	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//ポリゴン描画
	CRenderer::GetDeviceContext()->Draw(4, 0);
}