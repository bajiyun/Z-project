#pragma once

#include <map>
#include<vector>

#include "assimp/cimport.h"
#include "assimp/scene.h"
#include "assimp/postprocess.h"
#include "assimp/matrix4x4.h"
#pragma comment (lib,"assimp.lib")

struct DEFORM_VERTEX
{
	aiVector3D Position;
	aiVector3D Normal;

	int BoneNum;
	std::string BoneName[4];
	float BoneWeight[4];
};

struct BONE
{
	aiMatrix4x4 Matrix;
	aiMatrix4x4 AnimationMatrix;
	aiMatrix4x4 OffsetMatrix;
};

class CAnimationModel
{
private:
	const aiScene* m_Scene = NULL;
	std::map<std::string, const aiScene*> m_Animation;
	std::map<std::string, const aiScene*> m_Animation1;
	ID3D11Buffer** m_VertexBuffer;
	ID3D11Buffer** m_IndexBuffer;

	D3DXMATRIX bone_position;

	std::map<std::string, ID3D11ShaderResourceView*> m_Texture;

	std::vector<DEFORM_VERTEX>* m_DeformVertex;
	std::map<const std::string, BONE> m_Bone;

	void CreateBone(aiNode* node);
	void UpdateBoneMatrix(aiNode* node, aiMatrix4x4 matrix);

	std::string m_CurAnimationName;

	float m_t;

public:

	void Load(const char *FileName);
	void LoadAnimation(const char *FileName, const char *Name);
	void Unload();
	//void Update(int Frame);
	void Update(const char*AnimationName, int Frame);
	void Update(const char*AnimationName1, const char*AnimationName2, float BlendRate, int Frame);
	void Draw();

	D3DXMATRIX GetHandBonePosition() { return bone_position; }
};