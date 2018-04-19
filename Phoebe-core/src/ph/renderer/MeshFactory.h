#pragma once

#include "Mesh.h"

namespace ph { namespace renderer { namespace MeshFactory {

	Mesh* CreatePlane(float width, float height, const math::Vec3& normal, Material* material);
	Mesh* CreateCube(float size, Material* material);
	Mesh* CreateSkybox(Material* material);

}}}