//#pragma once
//#include "struct.h"
//#include <fstream>
//#include <sstream>
//
//class ShapeManager :public Singleton<ShapeManager>
//{
//public:
//	ShapeManager();
//	friend Singleton<ShapeManager>;
//
//	vector<ObjectData> objectData;
//
//	void LoadObject(int dataID, Object3D& objectBuff, const char* fileName = 0);
//
//	void CreateObject(const char* fileName, Object3D& objectBuff);
//
//	void CreateCone(Object3D& objectBuff);
//
//	void CreateCylinder(Object3D& objectBuff);
//
//	void CreateSphere(Object3D& objectBuff);
//};