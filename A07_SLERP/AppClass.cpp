#include "AppClass.h"
void AppClass::InitWindow(String a_sWindowName)
{
	super::InitWindow("SLERP - Lewis"); // Window Name

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);
}

void AppClass::InitVariables(void)
{
	//Setting the position in which the camera is looking and its interest point
	m_pCameraMngr->SetPositionTargetAndView(vector3(12.12f, 28.52f, 11.34f), ZERO_V3, REAXISY);

	//Setting the color to black
	m_v4ClearColor = vector4(0.0f);

	//Loading the models
	m_pMeshMngr->LoadModel("Planets\\00_Sun.obj", "Sun");
	m_pMeshMngr->LoadModel("Planets\\03_Earth.obj", "Earth");
	m_pMeshMngr->LoadModel("Planets\\03A_Moon.obj", "Moon");

	//Setting the days duration
	m_fDay = 1.0f;
}

void AppClass::Update(void)
{
	//Update the system's time
	m_pSystem->UpdateTime();

	//Update the mesh manager's time without updating for collision detection
	m_pMeshMngr->Update();

	//First person camera movement
	if (m_bFPC == true)
		CameraRotation();

	//Getting the time between calls
	double fCallTime = m_pSystem->LapClock();
	//Counting the cumulative time
	static double fRunTime = 0.0f;
	fRunTime += fCallTime;
	static double fRunTime2 = 0.0f;
	fRunTime2 += fCallTime;

	//Earth Orbit
	double fEarthHalfOrbTime = 182.5f * m_fDay; //Earths orbit around the sun lasts 365 days / half the time for 2 stops
	float fEarthHalfRevTime = 0.5f * m_fDay; // Move for Half a day
	float fMoonHalfOrbTime = 14.0f * m_fDay; //Moon's orbit is 28 earth days, so half the time for half a route

	//A05 Rev/Rot code
	//Calculate the position of the Earth
	//m_m4Earth = glm::rotate(IDENTITY_M4, m_fEarthTimer, vector3(0.0f, 1.0f, 0.0f))*glm::translate(11.0f, 0.0f, 0.0f);

	//Calculate the position of the Moon
	//m_m4Moon = glm::rotate(m_m4Earth, -m_fMoonTimer, vector3(0.0f, 1.0f, 0.0f))*matrix4 distanceMoon = glm::translate(2.0f, 0.0f, 0.0f)* glm::rotate(IDENTITY_M4, 90.0f, vector3(0.0f, 0.0f, 1.0f));

	//m_m4Earth *= glm::rotate(IDENTITY_M4, 90.0f, vector3(1.0f, 0.0f, 0.0f)) * glm::rotate(IDENTITY_M4, -m_fMoonTimer, vector3(0.0f, 0.0f, 1.0f));
	m_m4Sun = IDENTITY_M4*glm::scale(vector3(5.936f));
	float fStartTime = 0.0f; //start of simulation
	static float fStartAngle = 0.0f;
	static float fEndAngle = 360.0f;
	
	float fPercent = MapValue(static_cast<float>(fRunTime), fStartTime, static_cast<float>(fEarthHalfOrbTime/2), 0.0f, 1.0f);

	//Quaternion Rotatiomn
	glm::quat qQuaternion1;
	glm::quat qQuaternion2 = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
	m_m4Earth = IDENTITY_M4*glm::scale(vector3(0.524f));
	m_m4Earth *= glm::mat4_cast(glm::mix(qQuaternion1, qQuaternion2,fPercent))*glm::translate(17.0f, 0.0f, 0.0f);

	float fMoonPercent = MapValue(static_cast<float>(fRunTime), fStartTime, static_cast<float>(fMoonHalfOrbTime/2) , 0.0f, 1.0f);

	glm::quat qQuaternion3 = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
	m_m4Moon = m_m4Earth*glm::scale(vector3(0.27f));
	m_m4Moon *= glm::mat4_cast(glm::mix(qQuaternion1, qQuaternion3, fMoonPercent))*glm::translate(8.0f, 0.0f, 0.0f);

	float fRotatePercent = MapValue(static_cast<float>(fRunTime), fStartTime, static_cast<float>(fEarthHalfRevTime* 2) , 0.0f, 1.0f);
	glm::quat qQuaternion4 = glm::angleAxis(90.0f, vector3(0.0f, 1.0f, 0.0f));
	m_m4Earth *= glm::mat4_cast(glm::mix(qQuaternion1, qQuaternion4, fRotatePercent));

	//Setting the matrices
	m_pMeshMngr->SetModelMatrix(m_m4Sun, "Sun");
	m_pMeshMngr->SetModelMatrix(m_m4Earth, "Earth");
	m_pMeshMngr->SetModelMatrix(m_m4Moon, "Moon");

	//Adds all loaded instance to the render list
	m_pMeshMngr->AddInstanceToRenderList("ALL");

	static int nEarthOrbits = 0;
	static int nEarthRevolutions = 0;
	static int nMoonOrbits = 0;
	static int yearCounter = 0;
	static int moonCounter = 0;

	//Check Revolutions and Orbits
	nEarthRevolutions = static_cast<int>(fRunTime);
	if (fRunTime2 > m_fDay)
	{
		fRunTime2 = 0;
		moonCounter++;
		yearCounter++;
	}
	if (moonCounter == 28)
	{
		moonCounter = 0;
		nMoonOrbits++;
	}
	if (yearCounter ==365)
	{
		yearCounter = 0;
		nEarthOrbits++;
	}

	//Indicate the FPS
	int nFPS = m_pSystem->GetFPS();

	//Print info on the screen
	m_pMeshMngr->PrintLine(m_pSystem->GetAppName(), REYELLOW);
	
	m_pMeshMngr->Print("Time:");
	m_pMeshMngr->PrintLine(std::to_string(fRunTime));

	m_pMeshMngr->Print("Day:");
	m_pMeshMngr->PrintLine(std::to_string(m_fDay));

	m_pMeshMngr->Print("E_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthOrbits));

	m_pMeshMngr->Print("E_Revolutions:");
	m_pMeshMngr->PrintLine(std::to_string(nEarthRevolutions));

	m_pMeshMngr->Print("M_Orbits:");
	m_pMeshMngr->PrintLine(std::to_string(nMoonOrbits));

	m_pMeshMngr->Print("FPS:");
	m_pMeshMngr->Print(std::to_string(nFPS), RERED);

}

void AppClass::Display(void)
{
	//clear the screen
	ClearScreen();

	//Render the grid based on the camera's mode:
	switch (m_pCameraMngr->GetCameraMode())
	{
	default:
		break;
	case CAMERAMODE::CAMROTHOX:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::YZ, RERED * 0.75f); //renders the YZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOY:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XZ, REGREEN * 0.75f); //renders the XZ grid with a 100% scale
		break;
	case CAMERAMODE::CAMROTHOZ:
		m_pMeshMngr->AddGridToRenderList(1.0f, REAXIS::XY, REBLUE * 0.75f); //renders the XY grid with a 100% scale
		break;
	}
	
	m_pMeshMngr->Render(); //renders the render list

	m_pGLSystem->GLSwapBuffers(); //Swaps the OpenGL buffers
}

void AppClass::Release(void)
{
	super::Release(); //release the memory of the inherited fields
}