#pragma once
#include "Components.h"
#include "Mesh.h"

class ComponentMesh : public Components
{
public:
	ComponentMesh(shared_ptr<Mesh>&& m);

	void Enable() override;
	void Disable() override;
	void update() override;

	const Ctype type = COMPONENT_MESH;
	vector<Mesh::Ptr> mMeshes;
	Mesh::Ptr mesh;
	//bool isActive;

private:
	ComponentMesh(const ComponentMesh& cpy) = delete;
	ComponentMesh& operator=(const ComponentMesh&) = delete;
};

