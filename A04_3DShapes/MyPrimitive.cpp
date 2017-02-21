#include "MyPrimitive.h"
MyPrimitive::MyPrimitive() { }
MyPrimitive::MyPrimitive(const MyPrimitive& other) { }
MyPrimitive& MyPrimitive::operator=(const MyPrimitive& other) { return *this; }
MyPrimitive::~MyPrimitive(void) { super::Release(); }
void MyPrimitive::CompileObject(vector3 a_v3Color)
{
	m_uVertexCount = static_cast<int> (m_lVertexPos.size());
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		AddVertexColor(a_v3Color);
	}
	
	CompleteTriangleInfo(true);
	CompileOpenGL3X();

}
//C--D
//|\ |
//| \|
//A--B
//This will make the triang A->B->C and then the triang C->B->D
void MyPrimitive::AddQuad(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft, vector3 a_vTopRight)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);

	AddVertexPosition(a_vTopLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopRight);
}
//Added in class, 2/13
void MyPrimitive::AddTri(vector3 a_vBottomLeft, vector3 a_vBottomRight, vector3 a_vTopLeft)
{
	AddVertexPosition(a_vBottomLeft);
	AddVertexPosition(a_vBottomRight);
	AddVertexPosition(a_vTopLeft);
}
void MyPrimitive::GeneratePlane(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;

	vector3 pointA(-fValue, -fValue, 0.0f); //0
	vector3 pointB(fValue, -fValue, 0.0f); //1
	vector3 pointC(fValue, fValue, 0.0f); //2
	vector3 pointD(-fValue, fValue, 0.0f); //3

	vector3 pointE(fValue, -fValue, -0.001f); //1
	vector3 pointF(-fValue, -fValue, -0.001f); //0
	vector3 pointG(fValue, fValue, -0.001f); //2
	vector3 pointH(-fValue, fValue, -0.001f); //3

											  //F
	AddQuad(pointA, pointB, pointD, pointC);
	//Double sided
	AddQuad(pointE, pointF, pointG, pointH);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCube(float a_fSize, vector3 a_v3Color)
{
	if (a_fSize < 0.01f)
		a_fSize = 0.01f;

	Release();
	Init();

	float fValue = 0.5f * a_fSize;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	vector3 point4(-fValue, -fValue, -fValue); //4
	vector3 point5(fValue, -fValue, -fValue); //5
	vector3 point6(fValue, fValue, -fValue); //6
	vector3 point7(-fValue, fValue, -fValue); //7

											  //F
	AddQuad(point0, point1, point3, point2);

	//B
	AddQuad(point5, point4, point6, point7);

	//L
	AddQuad(point4, point0, point7, point3);

	//R
	AddQuad(point1, point5, point2, point6);

	//U
	AddQuad(point3, point2, point7, point6);

	//D
	AddQuad(point4, point5, point0, point1);

	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCone(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	float theta = 0;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//Keeps the second for from going out of bounds.
	point.push_back(vector3(0.0f));

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point.push_back(vector3(cos(theta), sin(theta), 0));
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point[i + 1], point[i], point[0]); // Base
		AddTri(vector3(0,0,a_fHeight), point[i], point[i + 1]); //Cone Part Thing
	}
	//Last point
	AddTri(point[1], point[a_nSubdivisions], point[0]); // Base
	AddTri(vector3(0, 0, a_fHeight), point[a_nSubdivisions], point[1]); // Cone Part Thing

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateCylinder(float a_fRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	std::vector<vector3> point2;
	float theta = a_fRadius;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//Keeps the second for from going out of bounds.
	point.push_back(vector3(0.0f));
	point2.push_back(vector3(0,0,a_fHeight));

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point.push_back(vector3(cos(theta), sin(theta), 0)); // Base 1
		point2.push_back(vector3(cos(theta), sin(theta), a_fHeight)); // Base 2
		theta += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddTri(point[i + 1], point[i], point[0]); // Base 1
		AddTri(point2[0], point2[i], point2[i + 1]); // Base 2
		AddQuad(point[i], point[i + 1], point2[i], point2[i + 1]);
	}
	//Last point
	AddTri(point[1], point[a_nSubdivisions], point[0]); // Base 1
	AddTri(point2[0], point2[a_nSubdivisions], point2[1]); // Base 2
	AddQuad(point2[1], point2[a_nSubdivisions], point[1], point[a_nSubdivisions]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTube(float a_fOuterRadius, float a_fInnerRadius, float a_fHeight, int a_nSubdivisions, vector3 a_v3Color)
{
	if (a_nSubdivisions < 3)
		a_nSubdivisions = 3;
	if (a_nSubdivisions > 360)
		a_nSubdivisions = 360;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	std::vector<vector3> point;
	std::vector<vector3> point2;
	std::vector<vector3> point3;
	std::vector<vector3> point4;
	float thetaInner = a_fInnerRadius;
	float thetaOuter = a_fOuterRadius;
	float steps = 2 * PI / static_cast<float>(a_nSubdivisions);

	//Keeps the second for from going out of bounds.
	point.push_back(vector3(0.0f));
	point2.push_back(vector3(0.0f));
	point3.push_back(vector3(0.0f));
	point4.push_back(vector3(0.0f));

	for (int i = 0; i < a_nSubdivisions; i++)
	{
		point.push_back(vector3(cos(thetaOuter), sin(thetaOuter), 0)); // Outside Rim 1
		point2.push_back(vector3(cos(thetaOuter), sin(thetaOuter), a_fHeight)); // Outside Rim 2
		point3.push_back(vector3(cos(thetaInner)/2, sin(thetaInner)/2, 0)); // Inside Rim 1
		point4.push_back(vector3(cos(thetaInner)/2, sin(thetaInner)/2, a_fHeight)); // Inside Rim 2
		thetaInner += steps;
		thetaOuter += steps;
	}

	for (int i = 1; i < a_nSubdivisions; i++)
	{
		AddQuad(point[i], point[i + 1], point2[i], point2[i + 1]); // Outer Faces
		AddQuad(point4[i], point4[i + 1], point3[i], point3[i + 1]); // Inner Faces

		//Top Faces
		AddQuad(point3[i], point3[i + 1], point[i], point[i + 1]);

		//Bottom Faces
		AddQuad(point2[i], point2[i + 1], point4[i], point4[i + 1]);

	}

	//Last Quads Outside
	AddQuad(point2[1], point2[a_nSubdivisions], point[1], point[a_nSubdivisions]);
	AddQuad(point3[1], point3[a_nSubdivisions], point4[1], point4[a_nSubdivisions]);

	//Last Quads Top/Bottom
	AddQuad(point[1], point[a_nSubdivisions], point3[1], point3[a_nSubdivisions]);
	AddQuad(point4[1], point4[a_nSubdivisions], point2[1], point2[a_nSubdivisions]);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateTorus(float a_fOuterRadius, float a_fInnerRadius, int a_nSubdivisionsA, int a_nSubdivisionsB, vector3 a_v3Color)
{
	if (a_fOuterRadius <= a_fInnerRadius + 0.1f)
		return;

	if (a_nSubdivisionsA < 3)
		a_nSubdivisionsA = 3;
	if (a_nSubdivisionsA > 25)
		a_nSubdivisionsA = 25;

	if (a_nSubdivisionsB < 3)
		a_nSubdivisionsB = 3;
	if (a_nSubdivisionsB > 25)
		a_nSubdivisionsB = 25;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	vector3 point0(-fValue, -fValue, fValue); //0
	vector3 point1(fValue, -fValue, fValue); //1
	vector3 point2(fValue, fValue, fValue); //2
	vector3 point3(-fValue, fValue, fValue); //3

	AddQuad(point0, point1, point3, point2);

	//Your code ends here
	CompileObject(a_v3Color);
}
void MyPrimitive::GenerateSphere(float a_fRadius, int a_nSubdivisions, vector3 a_v3Color)
{
	//Sets minimum and maximum of subdivisions
	if (a_nSubdivisions < 1)
	{
		GenerateCube(a_fRadius * 2, a_v3Color);
		return;
	}
	if (a_nSubdivisions > 6)
		a_nSubdivisions = 6;

	Release();
	Init();

	//Your code starts here
	float fValue = 0.5f;
	//3--2
	//|  |
	//0--1
	//Solution from class:

	vector3 pointA(-fValue, -fValue, fValue); //0
	vector3 pointB(fValue, -fValue, fValue); //1
	vector3 pointC(-fValue, fValue, fValue); //2

											 //left to right List of vector3
	std::vector<vector3> vectorAB;
	vectorAB.push_back(pointA);
	for (int i = 0; i < a_nSubdivisions; i++)
	{
		vector3 temp(pointB - pointA);
		temp /= a_nSubdivisions + 1;
		temp *= (i + 1);
		vectorAB.push_back(temp + pointA);
	}
	vectorAB.push_back(pointB);

	//height increments
	float fHeight = pointC.y - pointA.y;
	fHeight /= a_nSubdivisions + 1;

	//List of Lists
	std::vector<std::vector<vector3>> list;
	list.push_back(vectorAB);
	for (int j = 0; j < a_nSubdivisions + 1; j++)
	{
		std::vector<vector3> temp = list[0];
		float increment = fHeight * (j + 1);
		for (int i = 0; i < a_nSubdivisions + 2; i++)
		{
			temp[i].y += increment;
		}
		list.push_back(temp);
	}

	//Creating the patch of quads
	for (int j = 0; j < a_nSubdivisions + 1; j++)
	{
		for (int i = 0; i < a_nSubdivisions + 1; i++)
		{
			AddQuad(list[j][i], list[j][i + 1], list[j + 1][i], list[j + 1][i + 1]);
		}
	}

	//normalizing the vectors to make them round
	for (uint i = 0; i < m_uVertexCount; i++)
	{
		m_lVertexPos[i] = glm::normalize(m_lVertexPos[i]);
		m_lVertexPos[i] *= a_fRadius;
	}

	//RightSideFace
	int nVert = m_uVertexCount;
	std::vector<vector3> right;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 90.0f, vector3(0.0f, 1.0f, 0.0f));
		right.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}


	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(right[i]);
	}

	//LeftSideFace
	std::vector<vector3> left;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), -90.0f, vector3(0.0f, 1.0f, 0.0f));
		left.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(left[i]);
	}

	//BackSideFace
	std::vector<vector3> back;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 180.0f, vector3(0.0f, 1.0f, 0.0f));
		back.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(back[i]);
	}

	//TopSideFace
	std::vector<vector3> top;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), -90.0f, vector3(1.0f, 0.0f, 0.0f));
		top.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(top[i]);
	}

	//BottomSideFace
	std::vector<vector3> bottom;
	for (int i = 0; i < nVert; i++)
	{
		matrix4 rotation;
		rotation = glm::rotate(matrix4(1.0f), 90.0f, vector3(1.0f, 0.0f, 0.0f));
		bottom.push_back(static_cast <vector3>(rotation * glm::vec4(m_lVertexPos[i], 1.0f)));
	}

	for (int i = 0; i < nVert; i++)
	{
		AddVertexPosition(bottom[i]);
	}

	//Your code ends here
	CompileObject(a_v3Color);
}