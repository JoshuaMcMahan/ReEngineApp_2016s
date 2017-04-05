#include "CameraQuat.h"

CameraQuat::CameraQuat()
{
	SetPosition(glm::vec3(0.0f, 0.0f, 3.0f));
	SetFront(glm::vec3(0.0f, 0.0f, -1.0f));
	SetUp(glm::vec3(0.0f, 1.0f, 0.0f));
}

glm::mat4 CameraQuat::GetView(void)
{
	glm::mat4 t_m4View = glm::lookAt(v3CameraPos, v3CameraPos + v3CameraFront, v3CameraUp);
	return t_m4View;
}

glm::mat4 CameraQuat::GetProjection(bool bOrthographic)
{
	glm::mat4 t_m4Mat;
	if (bOrthographic == false) //Return Perspective
		t_m4Mat = glm::perspective(fFOV, 20.0f, 0.1f, 100.0f);
	else //Return Ortho
		t_m4Mat = glm::translate(IDENTITY_M4, glm::vec3(0));

	return t_m4Mat;
}

void CameraQuat::SetPosition(glm::vec3 v3Position)
{
	//Move the camera to a set position
	v3CameraPos = v3Position;
	m4ViewMatrix = glm::translate(IDENTITY_M4, v3Position);
}

void CameraQuat::SetTarget(glm::vec3 v3Target)
{
}

void CameraQuat::SetUp(glm::vec3 v3Up)
{
	v3CameraUp = v3Up;
}

void CameraQuat::SetFront(glm::vec3 v3Front)
{
	v3CameraFront = v3Front;
}

void CameraQuat::MoveForward(float fIncrement)
{
	SetPosition(v3CameraPos + glm::vec3(0.0f, 0.0f, fIncrement));
}

void CameraQuat::MoveSideways(float fIncrement)
{
	SetPosition(v3CameraPos + glm::vec3(fIncrement, 0.0f, 0.0f));
}

void CameraQuat::MoveVertical(float fIncrement)
{
	SetPosition(v3CameraPos + glm::vec3(0.0f, fIncrement, 0.0f));
}

void CameraQuat::ChangePitch(float fIncrement)
{
	glm::quat t_qPitch = glm::quat(glm::vec3(fIncrement, 0.0f, 0.0f));
	qCamera = t_qPitch * qCamera;
	glm::mat4 t_m4Rotate = glm::mat4_cast(qCamera);
	glm::mat4 t_m4Translante = glm::translate(IDENTITY_M4, v3CameraFront);

	m4ViewMatrix = t_m4Rotate * t_m4Translante;
}

void CameraQuat::ChangeRoll(float fIncrement)
{
	glm::quat t_qRoll = glm::quat(glm::vec3(0.0f, 0.0f, fIncrement));
	qCamera = t_qRoll * qCamera;
	glm::mat4 t_m4Rotate = glm::mat4_cast(qCamera);
	glm::mat4 t_m4Translante = glm::translate(IDENTITY_M4, v3CameraFront);

	m4ViewMatrix = t_m4Rotate * t_m4Translante;
}

void CameraQuat::ChangeYaw(float fIncrement)
{
	glm::quat t_qYaw = glm::quat(glm::vec3(0.0f, fIncrement, 0.0f));
	qCamera = t_qYaw * qCamera;
	glm::mat4 t_m4Rotate = glm::mat4_cast(qCamera);
	glm::mat4 t_m4Translante = glm::translate(IDENTITY_M4, v3CameraFront);

	m4ViewMatrix = t_m4Rotate * t_m4Translante;
}

//Key Controls
void CameraQuat::KeyPressed(const unsigned char key)
{
	switch (key)
	{
		case 'w':
		{
			MoveForward(2);
			break;
		}
		case 's':
		{
			MoveForward(-2);
			break;
		}
		case 'a':
		{
			MoveSideways(-2);
			break;
		}
		case 'd':
		{
			MoveSideways(2);
			break;
		}
		case 'q':
		{
			MoveVertical(2);
			break;
		}
		case 'e':
		{
			MoveVertical(-2);
			break;
		}
		default:
			break;
	}
}

CameraQuat::~CameraQuat()
{
}