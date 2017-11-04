////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.h
////////////////////////////////////////////////////////////////////////////////
#ifndef _MODELCLASS_H_
#define _MODELCLASS_H_


//////////////
// INCLUDES //
//////////////
#include <vector> 
#include <d3d11.h>
#include <directxmath.h>
using namespace DirectX;
float distanceMath(float a, float b, float x, float y);
///////////////////////
// MY CLASS INCLUDES //
///////////////////////
#include "textureclass.h"
#include "gameclass.h"

////////////////////////////////////////////////////////////////////////////////
// Class name: ModelClass
////////////////////////////////////////////////////////////////////////////////
class ModelClass
{
private:
	struct VertexType
	{
		XMFLOAT3 position;
		XMFLOAT2 texture;
		XMFLOAT4 color;
		XMFLOAT3 normal;
	};

	struct InstanceTypeSize
	{
		XMFLOAT3 position;
		XMFLOAT4 color;
	};
public:

	ModelClass();
	ModelClass(const ModelClass&);
	~ModelClass();

	VertexType* tank, *turret, *vertexList, *bullet;
	unsigned long* index;
	//InstanceType* instances;
	D3D11_BUFFER_DESC vertexBufferDesc, instanceBufferDesc, tankVertexBufferDesc, turretVertexBufferDesc, bulletVertexBufferDesc, indexBufferDesc;
	D3D11_SUBRESOURCE_DATA vertexData, instanceData, tankVertexData, turretVertexData, bulletVertexData, indexData;
	HRESULT result;

	bool Initialize(ID3D11Device*, ID3D11DeviceContext*, char*, GameClass *);
	void Shutdown();
	void Render(ID3D11DeviceContext*, GameClass*);
	void RenderTank(ID3D11DeviceContext*, GameClass*);
	void RenderTurret(ID3D11DeviceContext*, GameClass*);
	void RenderBullet(ID3D11DeviceContext*, GameClass*);
	int GetVertexCount();
	int GetInstanceCount();
	ID3D11ShaderResourceView* GetTexture();
	
private:
	bool InitializeBuffers(ID3D11Device*, GameClass *);
	void ShutdownBuffers();
	void RenderBuffers(ID3D11DeviceContext*, GameClass*);
	void RenderTurretBuffers(ID3D11DeviceContext*, GameClass*);
	void RenderTankBuffers(ID3D11DeviceContext*, GameClass*);
	void RenderBulletBuffers(ID3D11DeviceContext*, GameClass*);
	bool LoadTexture(ID3D11Device*, ID3D11DeviceContext*, char*);
	void ReleaseTexture();

private:
	ID3D11Buffer *m_vertexBuffer, *m_instanceBuffer, *tankBuffer, *turretBuffer, *bulletBuffer, *m_indexBuffer;
	int m_vertexCount, tankVertexCount, turretVertexCount, m_indexCount, bulletVertexCount;

	TextureClass* m_Texture;
};

#endif