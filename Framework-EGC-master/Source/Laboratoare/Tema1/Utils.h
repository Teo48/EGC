#pragma once
#ifndef __UTILS_H__
#define __UTILS_H__
#include <vector>
#include <Component/SimpleScene.h>
#include <Core/Engine.h>

class Utils : public SimpleScene{
	public:
		Utils();
		~Utils();
		Mesh* CreateMesh(const char* name, const std::vector<VertexFormat>& vertices, const std::vector<unsigned short>& indices);
};

#endif // __UTILS_H__
