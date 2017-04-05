#ifndef __CAMERAQUAT_H_
#define __CAMERAQUAT_H_

#include "RE\ReEngAppClass.h"
#include <SFML\Graphics.hpp>

using namespace ReEng; //Using ReEng namespace to use all the classes in the dll
class CameraQuat
{
public:
	float fFOV;
	glm::vec3 v3CameraPos;
	glm::vec3 v3CameraFront;
	glm::vec3 v3CameraUp;
	glm::quat qCamera;
	glm::mat4 m4ViewMatrix;

	CameraQuat();
	
	glm::mat4 GetView(void); //Gets the View Matrix
	glm::mat4 GetProjection(bool bOrthographic); //Gets the prohection matrix
	void SetPosition(glm::vec3 v3Position); //Set position of Camera
	void SetTarget(glm::vec3 v3Target); //Set target of Camera
	void SetUp(glm::vec3 v3Up); //Sets the up vector of Camera
	void SetFront(glm::vec3 v3Front);
	void MoveForward(float fIncrement); //Move the Camera forward or backwars depending on view vector
	void MoveSideways(float fIncrement); //Move the Camera side to side based on the right vector depending on the view vector
	void MoveVertical(float fIncrement); //Move the Camera up and down depending on the up vector
	void ChangePitch(float fIncrement); //Orient your camera changing its angle in x
	void ChangeRoll(float fIncrement); //Orient your camera changing its angle in z
	void ChangeYaw(float fIncrement); //Orient your camera changing its angle in y
	void KeyPressed(const unsigned char key);
	~CameraQuat();
};

#endif //__CAMERAQUAT_H_