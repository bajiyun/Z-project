#include "main.h"
#include "renderer.h"
#include "manager.h"
#include "titleenter.h"
#include "titlemoji.h"
//順番が大事

void CTEnter::Init()
{
	VERTEX_3D vertex[4];

	vertex[0].Position = D3DXVECTOR3(200.0f, 340.0f, 0.0f);
	vertex[0].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[0].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.4f);
	vertex[0].TexCoord = D3DXVECTOR2(0.0f, 0.0f);

	vertex[1].Position = D3DXVECTOR3(200.0f + 728.0f, 340.0f, 0.0f);
	vertex[1].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[1].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.4f);
	vertex[1].TexCoord = D3DXVECTOR2(1.0f, 0.0f);

	vertex[2].Position = D3DXVECTOR3(200.0f, 340.0f + 172.0f, 0.0f);
	vertex[2].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[2].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.4f);
	vertex[2].TexCoord = D3DXVECTOR2(0.0f, 1.0f);

	vertex[3].Position = D3DXVECTOR3(200.0f + 728.0f, 340.0f + 172.0f, 0.0f);
	vertex[3].Normal = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
	vertex[3].Diffuse = D3DXVECTOR4(0.4f, 0.8f, 0.0f, 0.4f);
	vertex[3].TexCoord = D3DXVECTOR2(1.0f, 1.0f);

	D3D11_BUFFER_DESC bd;
	ZeroMemory(&bd, sizeof(bd));
	bd.Usage = D3D11_USAGE_DEFAULT;
	bd.ByteWidth = sizeof(VERTEX_3D) * 4;
	bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bd.CPUAccessFlags = 0;

	D3D11_SUBRESOURCE_DATA sd;
	ZeroMemory(&sd, sizeof(sd));
	sd.pSysMem = vertex;

	CRenderer::GetDevice()->CreateBuffer(&bd, &sd, &m_VertexBuffer);

	D3DX11CreateShaderResourceViewFromFile(CRenderer::GetDevice(),
		"asset/texture/enter.png",
		NULL,
		NULL,
		&m_Texture,
		NULL);
	assert(m_Texture);

	CRenderer::CreateVertexShader(&m_VertexShader, &m_VertexLayout, "vertexShader.cso");
	CRenderer::CreatePixelShader(&m_PixelShader, "pixelShader.cso");
	key = false;
}

void CTEnter::Uninit()
{
	m_VertexBuffer->Release();
	m_Texture->Release();
}

void CTEnter::Update()
{
	CTMoji* moji = CManager::GetScene()->GetGameObject<CTMoji>(2);
	float alf = moji->getalf();
	if (alf >= 0.9f)
	{
		frame++;
		if (frame >= 3000)
			frame = 0;

		if (frame % 30 == 0)
			key = !key;
	}
}

void CTEnter::Draw()
{
	LIGHT light;
	light.Enable = false;
	CRenderer::SetLight(light);

	//入力レイアウト設定
	CRenderer::GetDeviceContext()->IASetInputLayout(m_VertexLayout);
	//シェーダー設定
	CRenderer::GetDeviceContext()->VSSetShader(m_VertexShader, NULL, 0);
	CRenderer::GetDeviceContext()->PSSetShader(m_PixelShader, NULL, 0);

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
	//ID3D11ShaderResourceView* shadowDepthTexture = CRenderer::GetShadowDepthTexture();
	//CRenderer::GetDeviceContext()->PSSetShaderResources(0, 1, &shadowDepthTexture);

	//プリミティブトポロジ設定
	CRenderer::GetDeviceContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLESTRIP);
	//ポリゴン描画
	if (key)
		CRenderer::GetDeviceContext()->Draw(4, 0);
}