////////////////////////////////////////////////////////////////////////////////
// Filename: modelclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "modelclass.h"

ModelClass::ModelClass()
{
	m_vertexBuffer = 0;
	m_instanceBuffer = 0;
	m_Texture = 0;
}


ModelClass::ModelClass(const ModelClass& other)
{
}


ModelClass::~ModelClass()
{
}
bool  ModelClass::Initialize(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* textureFilename, GameClass *m_Game)
{
	bool result;
	// Initialize the vertex and index buffers.
	result = InitializeBuffers(device, m_Game);
	if (!result)
	{
		return false;
	}
	// Load the texture for this model.
	result = LoadTexture(device, deviceContext, textureFilename);
	if (!result)
	{
		return false;
	}
	return true;
}
void ModelClass::Shutdown()
{

	// Release the model texture.
	ReleaseTexture();
	// Shutdown the vertex and index buffers.
	ShutdownBuffers();

	return;
}

void ModelClass::Render(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	RenderBuffers(deviceContext, m_Game);

	return;
}
void ModelClass::RenderTank(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//RenderBuffers(deviceContext, m_Game);
	
	RenderTankBuffers(deviceContext, m_Game);
	return;
}
void ModelClass::RenderTurret(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//RenderBuffers(deviceContext, m_Game);
	
	RenderTurretBuffers(deviceContext, m_Game);
	return;
}
void ModelClass::RenderBullet(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{
	// Put the vertex and index buffers on the graphics pipeline to prepare them for drawing.
	//RenderBuffers(deviceContext, m_Game);

	RenderBulletBuffers(deviceContext, m_Game);
	return;
}

int ModelClass::GetVertexCount()
{
	return m_vertexCount;
}
int ModelClass::GetInstanceCount()
{
	return NUMBER_OF_PLAYERS;// m_instanceCount;
}

ID3D11ShaderResourceView* ModelClass::GetTexture()
{
	return m_Texture->GetTexture();
}

bool ModelClass::InitializeBuffers(ID3D11Device* device, GameClass* m_Game)
{

	unsigned long* indices;
	//number of vertexes in for array
	bulletVertexCount = 6;
	tankVertexCount = 6;
	turretVertexCount = 12;
	m_vertexCount = tankVertexCount + turretVertexCount;
	// Set the number of vertices in the vertex array.
	//m_vertexCount = 6;
	////////////////
	//both tank and turret, old and unused
	m_indexCount = 3;
	vertexList = new VertexType[m_vertexCount];
	if (!vertexList)
	{
		return false;
	}
	//bullet 
	// Create the vertex array.
	bullet = new VertexType[bulletVertexCount];
	if (!bullet)
	{
		return false;
	}
	////////////////
	// Triangle 1 //
	////////////////
	// Load the vertex array with data.
	bullet[0].position = XMFLOAT3(-5.0f, -5.0f, 0.0f);  // Bottom left.
	bullet[0].texture = XMFLOAT2(-0.5f, -0.5f);
	bullet[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bullet[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	bullet[1].position = XMFLOAT3(-5.0f, 5.0f, 0.0f);  // Top left.
	bullet[1].texture = XMFLOAT2(-0.5f, 0.5f);
	bullet[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bullet[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	bullet[2].position = XMFLOAT3(5.0f, 5.0f, 0.0f);  // top right.
	bullet[2].texture = XMFLOAT2(0.5f, 0.5f);
	bullet[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	bullet[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	////////////////
	// Triangle 2 //
	////////////////
	bullet[3].position = XMFLOAT3(5.0f, -5.0f, 0.0f);  // Bottom right.
	bullet[3].texture = XMFLOAT2(0.5f, -0.5f);
	bullet[3].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	bullet[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	bullet[4].position = XMFLOAT3(-5.0f, -5.0f, 0.0f);  // Bottom left.
	bullet[4].texture = XMFLOAT2(-0.5f, -0.5f);
	bullet[4].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	bullet[4].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	bullet[5].position = XMFLOAT3(5.0f, 5.0f, 0.0f);  // top right.
	bullet[5].texture = XMFLOAT2(0.5f, 0.5f);
	bullet[5].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	bullet[5].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{

		for (unsigned j = 0; j < m_Game->playerArray[i]->bulletArray.size(); j++) // for loop so the following translations/rotations apply to all bullets
		{
			m_Game->playerArray[i]->bulletArray[j].bulletHeight = distanceMath(bullet[2].position.x, bullet[2].position.y, bullet[1].position.x, bullet[1].position.y);//Topleft x/y and top right x/y
			m_Game->playerArray[i]->bulletArray[j].bulletWidth = distanceMath(bullet[0].position.x, bullet[0].position.y, bullet[1].position.x, bullet[1].position.y); //bottom left x/y and top left x/y
		}
	}
	// sets up the tank vertex buffer
	bulletVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	bulletVertexBufferDesc.ByteWidth = sizeof(VertexType)* bulletVertexCount;
	bulletVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	bulletVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	bulletVertexBufferDesc.MiscFlags = 0;
	bulletVertexBufferDesc.StructureByteStride = 0;

	bulletVertexData.pSysMem = bullet;
	bulletVertexData.SysMemPitch = 0;
	bulletVertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&bulletVertexBufferDesc, &bulletVertexData, &bulletBuffer);
	if (FAILED(result))
	{
		return false;
	}
	//Tank
	// Create the vertex array.
	tank = new VertexType[tankVertexCount];
	if (!tank)
	{
		return false;
	}
	////////////////
	// Triangle 1 //
	////////////////
	// Load the vertex array with data.
	tank[0].position = XMFLOAT3(-50.0f, -40.0f, 0.0f);  // Bottom left.
	tank[0].texture = XMFLOAT2(-0.5f, -0.5f);
	tank[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	tank[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	tank[1].position = XMFLOAT3(-50.0f, 40.0f, 0.0f);  // Top left.
	tank[1].texture = XMFLOAT2(-0.5f, 0.5f);
	tank[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	tank[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	tank[2].position = XMFLOAT3(50.0f, 40.0f, 0.0f);  // top right.
	tank[2].texture = XMFLOAT2(0.5f, 0.5f);
	tank[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	tank[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	////////////////
	// Triangle 2 //
	////////////////
	tank[3].position = XMFLOAT3(50.0f, -40.0f, 0.0f);  // Bottom right.
	tank[3].texture = XMFLOAT2(0.5f, -0.5f);
	tank[3].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	tank[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	tank[4].position = XMFLOAT3(-50.0f, -40.0f, 0.0f);  // Bottom left.
	tank[4].texture = XMFLOAT2(-0.5f, -0.5f);
	tank[4].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	tank[4].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	tank[5].position = XMFLOAT3(50.0f, 40.0f, 0.0f);  // top right.
	tank[5].texture = XMFLOAT2(0.5f, 0.5f);
	tank[5].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	tank[5].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		m_Game->playerArray[i]->tankHeight = distanceMath(tank[2].position.x, tank[2].position.y, tank[1].position.x, tank[1].position.y);//Topleft x/y and top right x/y
		m_Game->playerArray[i]->tankWidth = distanceMath(tank[0].position.x, tank[0].position.y, tank[1].position.x, tank[1].position.y); //bottom left x/y and top left x/y
		
	}

	//Turret
	// Create the vertex array.
	turret = new VertexType[turretVertexCount];
	if (!turret)
	{
		return false;
	}
	////////////////
	// Triangle 3 //
	////////////////
	// Load the vertex array with data.
	turret[0].position = XMFLOAT3(-25.0f, -25.0f, -1.0f);  // Bottom left.
	//turret[0].texture = XMFLOAT2(-0.5f, -0.5f);
	turret[0].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	turret[0].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[1].position = XMFLOAT3(-25.0f, 25.0f, -1.0f);  // Top left.
	//turret[1].texture = XMFLOAT2(-0.5f, 0.5f);
	turret[1].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	turret[1].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[2].position = XMFLOAT3(25.0f, 25.0f, -1.0f);  // top right.
	//turret[2].texture = XMFLOAT2(0.5f, 0.5f);
	turret[2].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	turret[2].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	////////////////
	// Triangle 4 //
	////////////////
	turret[3].position = XMFLOAT3(25.0f, -25.0f, -1.0f);  // Bottom right.
	//turret[3].texture = XMFLOAT2(0.5f, -0.5f);
	turret[3].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	turret[3].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[4].position = XMFLOAT3(-25.0f, -25.0f, -1.0f);  // Bottom left.
	//turret[4].texture = XMFLOAT2(-0.5f, -0.5f);
	turret[4].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	turret[4].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[5].position = XMFLOAT3(25.0f, 25.0f, -1.0f);  // top right.
	//turret[5].texture = XMFLOAT2(0.5f, 0.5f);
	turret[5].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	turret[5].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);


	////////////////
	// Triangle 5 //
	////////////////
	// Load the vertex array with data.
	turret[6].position = XMFLOAT3(25.0f, -5.0f, -1.0f);  // Bottom left.
	//turret[6].texture = XMFLOAT2(-0.5f, -0.5f);
	turret[6].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	turret[6].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[7].position = XMFLOAT3(25.0f, 5.0f, -1.0f);  // Top left.
	//turret[7].texture = XMFLOAT2(-0.5f, 0.5f);
	turret[7].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	turret[7].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[8].position = XMFLOAT3(75.0f, 5.0f, -1.0f);  // top right.
	//turret[8].texture = XMFLOAT2(0.5f, 0.5f);
	turret[8].color = XMFLOAT4(0.0f, 1.0f, 0.0f, 1.0f);
	turret[8].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	////////////////
	// Triangle 6 //
	////////////////
	turret[9].position = XMFLOAT3(75.0f, -5.0f, -1.0f);  // Bottom right.
	//turret[9].texture = XMFLOAT2(0.5f, -0.5f);
	turret[9].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	turret[9].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[10].position = XMFLOAT3(-25.0f, -5.0f, -1.0f);  // Bottom left.
	//turret[10].texture = XMFLOAT2(-0.5f, -0.5f);
	turret[10].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	turret[10].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	turret[11].position = XMFLOAT3(75.0f, 5.0f, -1.0f);  // top right.
	//turret[11].texture = XMFLOAT2(0.5f, 0.5f);
	turret[11].color = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	turret[11].normal = XMFLOAT3(0.0f, 0.0f, -1.0f);

	//this copies both arrays into a single array so that they can be loaded into the vertex buffer together - unused now I load turret and tank seperately
	copy(tank, tank + tankVertexCount, vertexList);
	copy(turret, turret + turretVertexCount, vertexList + tankVertexCount);

	//sets up the tank vertex buffer
	tankVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	tankVertexBufferDesc.ByteWidth = sizeof(VertexType)* tankVertexCount;
	tankVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	tankVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	tankVertexBufferDesc.MiscFlags = 0;
	tankVertexBufferDesc.StructureByteStride = 0;

	tankVertexData.pSysMem = tank;
	tankVertexData.SysMemPitch = 0;
	tankVertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&tankVertexBufferDesc, &tankVertexData, &tankBuffer);
	if (FAILED(result))
	{
		return false;
	}
	
	//turret vertex buffer
	turretVertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	turretVertexBufferDesc.ByteWidth = (sizeof(VertexType) + sizeof(VertexType))* turretVertexCount;
	turretVertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	turretVertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	turretVertexBufferDesc.MiscFlags = 0;
	turretVertexBufferDesc.StructureByteStride = 0;

	turretVertexData.pSysMem = turret;
	turretVertexData.SysMemPitch = 0;
	turretVertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&turretVertexBufferDesc, &turretVertexData, &turretBuffer);
	if (FAILED(result))
	{
		return false;
	}

	//old buffer, used to load both tank and turret into one array, but I was unable to rotate the turret seperately this way
	//// Set up the description of the static vertex buffer.
	vertexBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	vertexBufferDesc.ByteWidth = sizeof(VertexType) * m_vertexCount;
	vertexBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vertexBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	vertexBufferDesc.MiscFlags = 0;
	vertexBufferDesc.StructureByteStride = 0;
	
	// Give the subresource structure a pointer to the vertex data.
	vertexData.pSysMem = vertexList;
	vertexData.SysMemPitch = 0;
	vertexData.SysMemSlicePitch = 0;

	// Now create the vertex buffer.
	result = device->CreateBuffer(&vertexBufferDesc, &vertexData, &m_vertexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	// Release the arrays now that the vertex buffer have been created and loaded.
	delete[] tank, turret, vertexList;
	tank, turret = 0;

	//set initial positons
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		m_Game->instances[i].position = XMFLOAT3(m_Game->playerArray[i]->xPos, m_Game->playerArray[i]->yPos, 5.0f);
	
	}
	// Set up the description of the instance buffer.
	instanceBufferDesc.Usage = D3D11_USAGE_DYNAMIC;
	instanceBufferDesc.ByteWidth = sizeof(InstanceTypeSize)* m_Game->m_instanceCount;
	instanceBufferDesc.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	instanceBufferDesc.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	instanceBufferDesc.MiscFlags = 0;
	instanceBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the instance data.
	instanceData.pSysMem = m_Game->instances;
	instanceData.SysMemPitch = 0;
	instanceData.SysMemSlicePitch = 0;

	// Create the instance buffer.
	result = device->CreateBuffer(&instanceBufferDesc, &instanceData, &m_instanceBuffer);
	if (FAILED(result))
	{
		return false;
	}

	// Release the instance array now that the instance buffer has been created and loaded.
	delete[] m_Game->instances;
	m_Game->instances = 0;
	// Set up the description of the static index buffer.
	// Create the index array.
	indices = new unsigned long[m_indexCount];
	if (!indices)
	{
		return false;
	}
	indexBufferDesc.Usage = D3D11_USAGE_DEFAULT;
	indexBufferDesc.ByteWidth = sizeof(unsigned long) * m_indexCount;
	indexBufferDesc.BindFlags = D3D11_BIND_INDEX_BUFFER;
	indexBufferDesc.CPUAccessFlags = 0;
	indexBufferDesc.MiscFlags = 0;
	indexBufferDesc.StructureByteStride = 0;

	// Give the subresource structure a pointer to the index data.
	indexData.pSysMem = indices;
	indexData.SysMemPitch = 0;
	indexData.SysMemSlicePitch = 0;

	// Create the index buffer.
	result = device->CreateBuffer(&indexBufferDesc, &indexData, &m_indexBuffer);
	if (FAILED(result))
	{
		return false;
	}
	return true;
}

void ModelClass::ShutdownBuffers()
{

	// Release the instance buffer.
	if (m_instanceBuffer)
	{
		m_instanceBuffer->Release();
		m_instanceBuffer = 0;
	}

	// Release the vertex buffer.
	if (m_vertexBuffer)
	{
		m_vertexBuffer->Release();
		m_vertexBuffer = 0;
	}

	return;
}
//renders the vertex buffer - old method
void ModelClass::RenderBuffers(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];
	
	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(VertexType) + sizeof(VertexType);
	//strides[1] = sizeof(InstanceTypeSize);
	
	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;
	//offsets[2] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = m_vertexBuffer;
	bufferPointers[1] = turretBuffer;
	//bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, bufferPointers, strides, offsets);

	
	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	
	return;
}
//renders the tank buffer
void ModelClass::RenderTankBuffers(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(VertexType) + sizeof(VertexType);
	//strides[1] = sizeof(InstanceTypeSize);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;
	//offsets[2] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = tankBuffer;
	//bufferPointers[1] = turretBuffer;
	//bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, bufferPointers, strides, offsets);


	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	return;
}
//renders the turret buffer
void ModelClass::RenderTurretBuffers(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(VertexType);
	//strides[1] = sizeof(InstanceTypeSize);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;
	//offsets[2] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = turretBuffer;
	//bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, bufferPointers, strides, offsets);
	//deviceContext->IASetIndexBuffer(m_indexBuffer, DXGI_FORMAT_R32_UINT, 0);

	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	return;
}
//renders the bullet buffer
void ModelClass::RenderBulletBuffers(ID3D11DeviceContext* deviceContext, GameClass* m_Game)
{

	unsigned int strides[2];
	unsigned int offsets[2];
	ID3D11Buffer* bufferPointers[2];

	// Set the buffer strides.
	strides[0] = sizeof(VertexType);
	strides[1] = sizeof(VertexType);
	//strides[1] = sizeof(InstanceTypeSize);

	// Set the buffer offsets.
	offsets[0] = 0;
	offsets[1] = 0;
	//offsets[2] = 0;

	// Set the array of pointers to the vertex and instance buffers.
	bufferPointers[0] = bulletBuffer;
	//bufferPointers[1] = m_instanceBuffer;

	// Set the vertex buffer to active in the input assembler so it can be rendered.
	deviceContext->IASetVertexBuffers(0, 1, bufferPointers, strides, offsets);


	// Set the type of primitive that should be rendered from this vertex buffer, in this case triangles.
	deviceContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);


	return;
}
bool ModelClass::LoadTexture(ID3D11Device* device, ID3D11DeviceContext* deviceContext, char* filename)
{
	bool result;


	// Create the texture object.
	m_Texture = new TextureClass;
	if (!m_Texture)
	{
		return false;
	}

	// Initialize the texture object.
	result = m_Texture->Initialize(device, deviceContext, filename);
	if (!result)
	{
		return false;
	}

	return true;
}

void ModelClass::ReleaseTexture()
{
	// Release the texture object.
	if (m_Texture)
	{
		m_Texture->Shutdown();
		delete m_Texture;
		m_Texture = 0;
	}

	return;
}

void testfunction(int direction)
{

}