#pragma once

// 頂点構造体
struct VERTEX_3D
{
	D3DXVECTOR3 Position;
	D3DXVECTOR3 Normal;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR2 TexCoord;
	D3DXVECTOR3 Binormal;
	D3DXVECTOR3 Tangent;
};

// マテリアル構造体
struct MATERIAL
{
	D3DXCOLOR	Ambient;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Specular;
	D3DXCOLOR	Emission;
	float		Shininess;
	float		Dummy[3];//16byte境界用
};

struct ZBUFFER
{
	D3DXVECTOR4 weight1;
	D3DXVECTOR4 weight2;
	D3DXVECTOR2 texsize;
};

// マテリアル構造体
struct DX11_MODEL_MATERIAL
{
	MATERIAL		Material;
	class CTexture*	Texture;
};

// 描画サブセット構造体
struct DX11_SUBSET
{
	unsigned int	StartIndex;
	unsigned int	IndexNum;
	DX11_MODEL_MATERIAL	Material;
};

struct LIGHT
{
	BOOL		Enable;
	BOOL		Dummy[3];//16byte境界用
	D3DXVECTOR4	Direction;
	D3DXCOLOR	Diffuse;
	D3DXCOLOR	Ambient;

	D3DXMATRIX ViewMatrix;
	D3DXMATRIX ProjectionMatrix;
};

class CVertexBuffer;
class CIndexBuffer;
class CTexture;

class CRenderer
{
private:

	static D3D_FEATURE_LEVEL       m_FeatureLevel;

	static ID3D11Device*           m_D3DDevice;
	static ID3D11DeviceContext*    m_ImmediateContext;
	static IDXGISwapChain*         m_SwapChain;
	static ID3D11RenderTargetView* m_RenderTargetView;
	static ID3D11DepthStencilView* m_DepthStencilView;

	static ID3D11DepthStencilView* m_ShadowDepthStencilView;
	static ID3D11ShaderResourceView* m_ShadowDepthShaderResourceView;

	static ID3D11RenderTargetView* m_PPRenderTargetView;
	static ID3D11ShaderResourceView* m_PPShaderResourceView;

	static ID3D11RenderTargetView* m_GeometryRenderTargetView[2];
	static ID3D11ShaderResourceView* m_GeometryShaderResourceView[2];

	static ID3D11Buffer*			m_WorldBuffer;
	static ID3D11Buffer*			m_ViewBuffer;
	static ID3D11Buffer*			m_ProjectionBuffer;
	static ID3D11Buffer*			m_MaterialBuffer;
	static ID3D11Buffer*			m_LightBuffer;
	static ID3D11Buffer*			m_CameraBuffer;
	static ID3D11Buffer*			m_ParameterBuffer;
	static ID3D11Buffer*			m_TimerBuffer;
	static ID3D11Buffer*			m_ZBuffer;

	static ID3D11DepthStencilState* m_DepthStateEnable;
	static ID3D11DepthStencilState* m_DepthStateDisable;

public:
	static void Init();
	static void Uninit();
	static void BeginDepth();
	static void BeginPP();
	static void BeginGeometry();
	static void Begin();
	static void End();

	static void SetDepthEnable(bool Enable);
	static void SetWorldViewProjection2D();
	static void SetWorldMatrix(D3DXMATRIX * WorldMatrix);
	static void SetViewMatrix(D3DXMATRIX * ViewMatrix);
	static void SetProjectionMatrix(D3DXMATRIX * ProjectionMatrix);
	static void SetMaterial(MATERIAL Material);
	static void SetLight(LIGHT Light);
	static void SetTimer(float Timer);
	static void SetZBuffer(ZBUFFER zbuffer);
	static void SetViewPort(int mode);

	static void SetCameraPosition(D3DXVECTOR3 CameraPosition);
	static void SetParameter(D3DXVECTOR4 Parameter);

	static ID3D11Device* GetDevice(void) { return m_D3DDevice; }
	static ID3D11DeviceContext* GetDeviceContext(void) { return m_ImmediateContext; }
	static ID3D11ShaderResourceView* GetShadowDepthTexture() { return m_ShadowDepthShaderResourceView; }
	static ID3D11ShaderResourceView* GetPPTexture() { return m_PPShaderResourceView; }
	static ID3D11ShaderResourceView** GetGeometryTexture() { return m_GeometryShaderResourceView; }

	static void CreateVertexShader(ID3D11VertexShader** VertexShader, ID3D11InputLayout** VertexLayout, const char* FileName);
	static void CreatePixelShader(ID3D11PixelShader** PixelShader, const char* FileName);
};
