#pragma once
#include "Components.h"
#include "Mesh.h"

class Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(GameObject& owner, shared_ptr<Mesh> mesh = nullptr);

	void update() override;

	shared_ptr<Mesh> mesh;

	Type getType() const override {
		return Type::MESH;
	}

private:
	ComponentMesh(const ComponentMesh& cpy);
	ComponentMesh& operator=(const ComponentMesh&);
};

