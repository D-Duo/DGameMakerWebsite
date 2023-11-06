#pragma once
#include "Components.h"
#include "Mesh.h"

class ComponentMesh : public Components
{
public:
	ComponentMesh(const string path);

	void Enable() override;
	void Disable() override;
	void update() override;

	const Ctype type = COMPONENT_MESTH;
	vector<Mesh::Ptr> mMeshes;

private:
	ComponentMesh(const ComponentMesh& cpy);
	ComponentMesh& operator=(const ComponentMesh&);
};

