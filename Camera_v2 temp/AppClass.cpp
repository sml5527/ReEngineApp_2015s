#include "AppClass.h"

CameraManager* CameraManager::instance = nullptr;
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("Sandbox"); // Window Name

	// Set the clear color based on Microsoft's CornflowerBlue (default in XNA)
	//if this line is in Init Application it will depend on the .cfg file, if it
	//is on the InitVariables it will always force it regardless of the .cfg
	m_v4ClearColor = vector4(0.4f, 0.6f, 0.9f, 0.0f);
}

void AppClass::InitVariables(void)
{
	//Creates the camera
	oCameraManager = CameraManager::GetInstance();
	
	//Reset the selection to -1, -1
	m_selection = std::pair<int, int>(-1, -1);

	
	//Set the camera position
	oCameraManager->setPosition(vector3(0.0f, 2.5f, 15.0f));
	oCameraManager->setTarget(vector3(0.0f, 2.5f, 0.0f));
	oCameraManager->setUp(REAXISY);
	
	m_pCube = new PrimitiveClass();
	m_pCube->GenerateCube(10.0f, REGREEN);

}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");
}

void AppClass::Display(void)
{
	m_m4Cube = IDENTITY_M4;
	//Clear the window
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	//Render the cylinder
	m_pCube->Render(oCameraManager->getProjection(false), oCameraManager->getView(), m_m4Cube);

	//Render the rest of the meshes
	//m_pMeshMngr->Render();

	//Swaps the OpenGL buffers
	m_pGLSystem->GLSwapBuffers();
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}