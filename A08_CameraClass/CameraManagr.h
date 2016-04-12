#pragma once
#include "AppClass.h"
#include "RE\ReEngAppClass.h"
using namespace ReEng;
using namespace std;

class CameraManagr
{

	static CameraManagr* instance;
public:
	static CameraManagr* GetInstance();
	static void ReleaseInstance();

	matrix4 getView(void);
	matrix4 getProjection(bool bOrthographic);
	void setPosition(vector3 v3Position);
	void setTarget(vector3 v3Target);
	void setUp(vector3 v3Up);
	void moveForward(float fIncriment);
	void moveSideways(float fIncriment);
	void moveVertical(float fIncriment);
	void ChangePitch(float fIncriment);
	void ChangeRoll(float fIncriment);
	void ChangeYaw(float fIncriment);


private:
	CameraManagr() {};
	CameraManagr(CameraManagr const& other) {};
	vector3 forwardVec;
	vector3 positionVec;
	vector3 upVec;
	vector3 targetVec;
};