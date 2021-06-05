#pragma once
#include "Main.h"
#include <cstring>
#include <DirectXMath.h>

struct DirectionalLight
{
	D3DXVECTOR4 Ambient;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR4 Specular;
	D3DXVECTOR3 Direction;
	float Pad;
};

struct PointLight
{
	D3DXVECTOR4 Ambient;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR4 Specular;
	D3DXVECTOR3 Position;
	float Range;

	D3DXVECTOR3 Att;
	float Pad;
};

struct SpotLight
{
	D3DXVECTOR4 Ambient;
	D3DXVECTOR4 Diffuse;
	D3DXVECTOR4 Specular;

	D3DXVECTOR3 Position;
	float Range;

	D3DXVECTOR3 Direction;
	float Spot;

	D3DXVECTOR3 Att;
	float Pad;
};