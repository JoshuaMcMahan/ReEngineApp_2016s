#include "AppClass.h"
void AppClass::ProcessKeyboard(void)
{
	bool bModifier = false;
	float fSpeed = 0.01f;

#pragma region ON_KEY_PRESS_RELEASE
	static bool	bLastF1 = false, bLastF2 = false, bLastF3 = false, bLastF4 = false, bLastF5 = false,
		bLastF6 = false, bLastF7 = false, bLastF8 = false, bLastF9 = false, bLastF10 = false,
		bLastEscape = false, bLastF = false;
#define ON_KEY_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Keyboard::isKeyPressed(sf::Keyboard::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion

#pragma region Modifiers
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::LShift) || sf::Keyboard::isKeyPressed(sf::Keyboard::RShift))
		bModifier = true;
#pragma endregion

#pragma region Camera Positioning
	if (bModifier)
		fSpeed *= 10.0f;
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		m_pCameraMngr->MoveForward(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		m_pCameraMngr->MoveForward(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		m_pCameraMngr->MoveSideways(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		m_pCameraMngr->MoveSideways(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
		m_pCameraMngr->MoveVertical(-fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
		m_pCameraMngr->MoveVertical(fSpeed);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		m_v3Position += vector3(-0.1f, 0.0f, 0.0f);
		m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		m_v3Position += vector3(0.1f, 0.0f, 0.0f);
		m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
	}
	//if the camera is orthographic, move in the negative z axis, if not, move in the positive y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
	{
		if (m_pCameraMngr->GetCameraMode() == CAMROTHOY)
		{
			if (!bModifier)
			{
				m_v3Position += vector3(0.0f, 0.0f, -0.1f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
			else
			{
				m_v3Position += vector3(0.0f, 0.1f, 0.0f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
		}
		else
		{
			if (!bModifier)
			{
				m_v3Position += vector3(0.0f, 0.1f, 0.0f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
			else
			{
				m_v3Position += vector3(0.0f, 0.0f, -0.1f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
		}
	}
	//if the camera is orthographic, move in the positive z axis, if not, move in the negative y axis
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
	{
		if (m_pCameraMngr->GetCameraMode() == CAMROTHOY)
		{
			if (!bModifier)
			{
				m_v3Position += vector3(0.0f, 0.0f, 0.1f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
			else
			{
				m_v3Position += vector3(0.0f, -0.1f, 0.0f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
		}
		else
		{
			if (!bModifier)
			{
				m_v3Position += vector3(0.0f, -0.1f, 0.0f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
			else
			{
				m_v3Position += vector3(0.0f, 0.0f, 0.1f);
				m_pBS0->SetModelMatrix(glm::translate(m_v3Position));
			}
		}
	}
#pragma endregion

#pragma region Other Actions
	ON_KEY_PRESS_RELEASE(Escape, NULL, PostMessage(m_pWindow->GetHandler(), WM_QUIT, NULL, NULL));
	ON_KEY_PRESS_RELEASE(F1, NULL, m_pCameraMngr->SetCameraMode(CAMROTHOY));
	ON_KEY_PRESS_RELEASE(F2, NULL, m_pCameraMngr->SetCameraMode(CAMPERSP));
	static bool bFPSControll = false;
	ON_KEY_PRESS_RELEASE(F, bFPSControll = !bFPSControll, m_pCameraMngr->SetFPS(bFPSControll));

	//toggle visibility of box
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::V))
		if (renderBox)
			renderBox = false;
		else
			renderBox = true;
#pragma endregion

#pragma region Load Models
	//if you press Num 1, it will select the current model as the Master Sword
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num1))
		currentModel = "Sword";

	//if you press Num 2, it will select the current model as the Hylian Shield
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Num2))
		currentModel = "Shield";
#pragma endregion

}
void AppClass::ProcessMouse(void)
{
	m_bArcBall = false;
	m_bFPC = false;
#pragma region ON_MOUSE_PRESS_RELEASE
	static bool	bLastLeft = false, bLastMiddle = false, bLastRight = false;
#define ON_MOUSE_PRESS_RELEASE(key, pressed_action, released_action){  \
			bool pressed = sf::Mouse::isButtonPressed(sf::Mouse::Button::key);			\
			if(pressed){											\
				if(!bLast##key) pressed_action;}/*Just pressed? */\
			else if(bLast##key) released_action;/*Just released?*/\
			bLast##key = pressed; } //remember the state
#pragma endregion
	bool bLeft = false;
	ON_MOUSE_PRESS_RELEASE(Left, NULL, bLeft = true)
		if (bLeft)
		{
			//Turn off the visibility of all BOs for all instances
			m_pMeshMngr->SetVisibleBO(BD_NONE, "ALL", -1);
			//Get the Position and direction of the click on the screen
			std::pair<vector3, vector3> pair =
				m_pCameraMngr->GetClickAndDirectionOnWorldSpace(sf::Mouse::getPosition().x, sf::Mouse::getPosition().y);
			float fDistance = 0;//Stores the distance to the first colliding object
			m_selection = m_pMeshMngr->IsColliding(pair.first, pair.second, fDistance);

			//If there is a collision
			if (m_selection.first >= 0)
			{
				//Turn on the BO of the group
				m_pMeshMngr->SetVisibleBO(BD_OB, m_selection.first, m_selection.second);

				//Turn of the BO of the instance but not the group
				m_pMeshMngr->SetVisibleBO(BD_NONE, m_selection.first, -2);
			}
		}

	//added functionality to rotate with the r button for those without a middle mouse button
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Middle) || sf::Keyboard::isKeyPressed(sf::Keyboard::R))
		m_bArcBall = true;

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right))
		m_bFPC = true;
}
