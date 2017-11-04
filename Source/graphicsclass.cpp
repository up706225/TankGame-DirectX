////////////////////////////////////////////////////////////////////////////////
// Filename: graphicsclass.cpp
////////////////////////////////////////////////////////////////////////////////
#include "graphicsclass.h"


GraphicsClass::GraphicsClass()
{
	m_Direct3D = 0;
	m_Camera = 0;
	m_Model = 0;
	m_TextureShader = 0;
	m_ColorShader = 0;
	m_Game = new GameClass;
}


GraphicsClass::GraphicsClass(const GraphicsClass& other)
{
}


GraphicsClass::~GraphicsClass()
{
}


bool GraphicsClass::Initialize(int screenWidth, int screenHeight, HWND hwnd, GameClass* m_Game)
{
	bool result;

	m_Game->Initialize();
	// Create the Direct3D object.
	m_Direct3D = new D3DClass;
	if(!m_Direct3D)
	{
		return false;
	}

	// Initialize the Direct3D object.
	result = m_Direct3D->Initialize(screenWidth, screenHeight, VSYNC_ENABLED, hwnd, FULL_SCREEN, SCREEN_DEPTH, SCREEN_NEAR);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize Direct3D.", L"Error", MB_OK);
		return false;
	}
	// Create the camera object.
	m_Camera = new CameraClass;
	if (!m_Camera)
	{
		return false;
	}

	// Set the initial position of the camera.
	m_Camera->SetPosition(0.0f, 0.0f, -15.0f);

	// Create the model object.
	m_Model = new ModelClass;
	if (!m_Model)
	{
		return false;
	}
	//colour
	// Initialize the model object.
	result = m_Model->Initialize(m_Direct3D->GetDevice(), m_Direct3D->GetDeviceContext(), "../Source/Data/stone01.tga", m_Game);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the model object.", L"Error", MB_OK);
		return false;
	}

	// Create the texture shader object.
	m_TextureShader = new TextureShaderClass;
	if (!m_TextureShader)
	{
		return false;
	}

	// Create the color shader object.
	m_ColorShader = new ColorShaderClass;
	if (!m_ColorShader)
	{
		return false;
	}
	// Initialize the color shader object.
	result = m_ColorShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the color shader object.", L"Error", MB_OK);
		return false;
	}
	// Initialize the color shader object.
	result = m_TextureShader->Initialize(m_Direct3D->GetDevice(), hwnd);
	if (!result)
	{
		MessageBox(hwnd, L"Could not initialize the texture shader object.", L"Error", MB_OK);
		return false;
	}

	return true;
}


void GraphicsClass::Shutdown()
{
	// Release the color shader object.
	if (m_ColorShader)
	{
		m_ColorShader->Shutdown();
		delete m_ColorShader;
		m_ColorShader = 0;
	}
	// Release the texture shader object.
	if (m_TextureShader)
	{
		m_TextureShader->Shutdown();
		delete m_TextureShader;
		m_TextureShader = 0;
	}

	// Release the model object.
	if (m_Model)
	{
		m_Model->Shutdown();
		delete m_Model;
		m_Model = 0;
	}

	// Release the camera object.
	if (m_Camera)
	{
		delete m_Camera;
		m_Camera = 0;
	}
	// Release the D3D object.
	if(m_Direct3D)
	{
		m_Direct3D->Shutdown();
		delete m_Direct3D;
		m_Direct3D = 0;
	}

	return;
}


bool GraphicsClass::Frame()
{
	bool result;


	// Render the graphics scene.
	result = Render();
	if(!result)
	{
		return false;
	}

	return true;
}


bool GraphicsClass::Render()
{
	XMMATRIX worldMatrix, viewMatrix, projectionMatrix, orthographicMatrix;
	bool result;


	// Clear the buffers to begin the scene.
	m_Direct3D->BeginScene(0.0f, 0.0f, 0.0f, 1.0f);

	// Generate the view matrix based on the camera's position.
	m_Camera->Render();

	

	// Get the world, view, and projection matrices from the camera and d3d objects.
	//m_Direct3D->GetWorldMatrix(worldMatrix);
	m_Camera->GetViewMatrix(viewMatrix);
	//m_Direct3D->GetProjectionMatrix(projectionMatrix);
	m_Direct3D->GetOrthoMatrix(orthographicMatrix); //used to test switching to orographic matrix
	//
	for (int i = 0; i < NUMBER_OF_PLAYERS; i++)
	{
		for (unsigned j = 0; j < m_Game->playerArray[i]->bulletArray.size(); j++) // for loop so the following translations/rotations apply to all bullets
		{
			XMMATRIX translationBulletMat = XMMatrixTranslation(m_Game->playerArray[i]->bulletArray[j].xPos, m_Game->playerArray[i]->bulletArray[j].yPos, 0.0f);
			XMMATRIX rotationBulletMat = XMMatrixRotationZ(m_Game->playerArray[i]->bulletArray[j].bulletRotation);
			worldMatrix = rotationBulletMat * translationBulletMat;
			m_Model->RenderBullet(m_Direct3D->GetDeviceContext(), m_Game);

			result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, orthographicMatrix, m_Model->GetTexture());
			if (!result)
			{
				return false;
			}
		}
		XMMATRIX translationMat = XMMatrixTranslation(m_Game->playerArray[i]->xPos, m_Game->playerArray[i]->yPos, 0.0f);
		XMMATRIX rotationMat = XMMatrixRotationZ(m_Game->playerArray[i]->rotation);
		worldMatrix = rotationMat * translationMat;
		
		m_Model->RenderTank(m_Direct3D->GetDeviceContext(), m_Game);

		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, orthographicMatrix, m_Model->GetTexture());
		if (!result)
		{
			return false;
		}
		XMMATRIX rotationTurretMat = XMMatrixRotationZ(m_Game->playerArray[i]->turretRotation);
		worldMatrix = (rotationTurretMat * rotationMat)* translationMat;
		m_Model->RenderTurret(m_Direct3D->GetDeviceContext(), m_Game);
		result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, orthographicMatrix, m_Model->GetTexture());
		if (!result)
		{
			return false;
		}

		
	}
	// Put the model vertex and index buffers on the graphics pipeline to prepare them for drawing.
	
	


	

	//colour
	// Render the model using the color shader.
	//result = m_ColorShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, orthographicMatrix);
	//texture
	// Render the model using the texture shader.
	//result = m_TextureShader->Render(m_Direct3D->GetDeviceContext(), m_Model->GetVertexCount(), m_Model->GetInstanceCount(), worldMatrix, viewMatrix, orthographicMatrix, m_Model->GetTexture());
	//if (!result)
	//{
	//	return false;
	//}
	// Present the rendered scene to the screen.
	m_Direct3D->EndScene();
	
	return true;
}