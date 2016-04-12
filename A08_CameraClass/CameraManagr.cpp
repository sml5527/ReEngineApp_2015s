#include "CameraManagr.h"
CameraManagr* CameraManagr::instance = nullptr;
CameraManagr* CameraManagr::GetInstance()
{
	if (instance == nullptr)
		instance = new CameraManagr();
	return instance;
}
void CameraManagr::ReleaseInstance()
{
	if (instance != nullptr)
	{
		delete instance;
		instance = nullptr;
	}
}
matrix4 CameraManagr::getView(void)
{
	return glm::lookAt(positionVec, forwardVec, upVec);
}
matrix4 CameraManagr::getProjection(bool bOrthographic)
{
	if (!bOrthographic)
	{
		return glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
	}
	else
	{
		return glm::ortho(30.0f, 30.0f, 30.0f, 30.0f);
	}
}
void CameraManagr::setPosition(vector3 v3Position)
{
	positionVec = glm::normalize(v3Position);
}
void CameraManagr::setTarget(vector3 v3Target)
{
	forwardVec = v3Target - positionVec;
	glm::normalize(forwardVec);
	targetVec = positionVec + forwardVec;

}
void CameraManagr::setUp(vector3 v3Up)
{
	upVec = glm::normalize(v3Up);
}

void CameraManagr::moveForward(float fIncriment)
{
	setPosition(vector3(positionVec.x, positionVec.y, positionVec.z + fIncriment));
	setTarget(vector3(positionVec.x, positionVec.y, positionVec.z + fIncriment));
}

void CameraManagr::moveSideways(float fIncriment)
{
	setPosition(vector3(positionVec.x + fIncriment, positionVec.y, positionVec.z));
	setTarget(vector3(positionVec.x + fIncriment, positionVec.y, positionVec.z));
}

void CameraManagr::moveVertical(float fIncriment)
{
	setPosition(vector3(positionVec.x, positionVec.y + fIncriment, positionVec.z));
	setTarget(vector3(positionVec.x, positionVec.y + fIncriment, positionVec.z));
}

void CameraManagr::ChangePitch(float fIncriment)
{
	//target = glm::rotate(target, glm::radians(fIncriment), axisX);
}

void CameraManagr::ChangeRoll(float fIncriment)
{
	//target = glm::rotate(target, glm::radians(fIncriment), axisY);
}

void CameraManagr::ChangeYaw(float fIncriment)
{
	//target = glm::rotate(target, glm::radians(fIncriment), axisZ);
}

