#include "main.h"
#include "manager.h"
#include "renderer.h"
#include "input.h"
#include "scene.h"
#include "title.h"
#include "game.h"
#include "light.h"

//CScene* g_Scene = NULL;

CScene* CManager::m_Scene = NULL;

void CManager::Init()
{
	CRenderer::Init();

	CInput::Init();

	CLight::InitResource();
	//CAudioClip::Init();

	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	ImGui_ImplWin32_Init(GetWindow());
	ImGui_ImplDX11_Init(CRenderer::GetDevice(), CRenderer::GetDeviceContext());
	ImGui::StyleColorsDark();

	SetScene<CTitle>();
}

void CManager::Uninit()
{
	m_Scene->Uninit();
	delete m_Scene;

	CInput::Uninit();
	CRenderer::Uninit();
}

void CManager::Update()
{
	CInput::Update();

	ImGui_ImplDX11_NewFrame();
	ImGui_ImplWin32_NewFrame();
	ImGui::NewFrame();

	m_Scene->Update();
}

void CManager::Draw()
{
	LIGHT light;
	light.Enable = true;
	light.Direction = D3DXVECTOR4(1.0f, -1.0f, 1.0f, 0.0f);
	D3DXVec4Normalize(&light.Direction, &light.Direction);
	light.Ambient = D3DXCOLOR(0.1f, 0.1f, 0.1f, 1.0f);
	light.Diffuse = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXMatrixLookAtLH(&light.ViewMatrix, &D3DXVECTOR3(-100.0f, 100.0f, -100.0f),
		&D3DXVECTOR3(0.0f, 0.0f, 0.0f),
		&D3DXVECTOR3(0.0f, 1.0f, 0.0f));
	D3DXMatrixPerspectiveFovLH(&light.ProjectionMatrix, 1.0f, (float)SCREEN_WIDTH / SCREEN_HEIGHT, 5.0f, 30.0f);

	CRenderer::SetLight(light);

	CRenderer::SetViewMatrix(&light.ViewMatrix);
	CRenderer::SetProjectionMatrix(&light.ProjectionMatrix);

	CLight::UpdateLightConstantBuffer();
	//CRenderer::BeginPP();
	//m_Scene->DepthDraw();

	CRenderer::Begin();

	m_Scene->Draw();

	ImGui::Render();
	ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());

	CRenderer::End();
}