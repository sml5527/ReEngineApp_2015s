#include "CameraManager.h"

	vector3 target;
	vector3 axisX = vector3(1.0f, 0.0f, 0.0f);
	vector3 axisY = vector3(0.0f, 1.0f, 0.0f);
	vector3 axisZ = vector3(0.0f, 0.0f, 1.0f);
	
	CameraManager* CameraManager::GetInstance()
	{
		if (instance == nullptr)
			instance = new CameraManager();
		return instance;
	}
	void CameraManager::ReleaseInstance()
	{
		if (instance != nullptr)
		{
			delete instance;
			instance = nullptr;
		}
	}
	matrix4 CameraManager::getView(void)
	{
		return glm::lookAt(positionVec, forwardVec, upVec);
	}
	matrix4 CameraManager::getProjection(bool bOrthographic)
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
	void CameraManager::setPosition(vector3 v3Position)
	{
		positionVec = glm::normalize(v3Position);
	}
	void CameraManager::setTarget(vector3 v3Target)
	{
		forwardVec = v3Target - positionVec;
		glm::normalize(forwardVec);
		target = positionVec + forwardVec;

	}
	void CameraManager::setUp(vector3 v3Up)
	{
		upVec = glm::normalize(v3Up);
	}

	void CameraManager::moveForward(float fIncriment)
	{
		setPosition(vector3(positionVec.x, positionVec.y, positionVec.z+ fIncriment));
		setTarget(vector3(positionVec.x, positionVec.y, positionVec.z + fIncriment));
	}

	void CameraManager::moveSideways(float fIncriment)
	{
		setPosition(vector3(positionVec.x + fIncriment, positionVec.y, positionVec.z));
		setTarget(vector3(positionVec.x + fIncriment, positionVec.y, positionVec.z));
	}

	void CameraManager::moveVertical(float fIncriment)
	{
		setPosition(vector3(positionVec.x, positionVec.y + fIncriment, positionVec.z));
		setTarget(vector3(positionVec.x, positionVec.y + fIncriment, positionVec.z));
	}

	void CameraManager::ChangePitch(float fIncriment)
	{
		//target = glm::rotate(target, glm::radians(fIncriment), axisX);
	}

	void CameraManager::ChangeRoll(float fIncriment)
	{
		//target = glm::rotate(target, glm::radians(fIncriment), axisY);
	}

	void CameraManager::ChangeYaw(float fIncriment)
	{
		//target = glm::rotate(target, glm::radians(fIncriment), axisZ);
	}

