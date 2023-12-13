#pragma once
#include "Components.h"
#include "Mesh.h"

class Mesh;

class ComponentMesh : public Component
{
public:
	ComponentMesh(shared_ptr<Mesh> mesh_ = nullptr);

	void update() override;

	shared_ptr<Mesh> mesh;

	Type getType() const override {
		return Type::MESH;
	}

private:
	ComponentMesh(const ComponentMesh& cpy) = delete;
	ComponentMesh& operator=(const ComponentMesh&) = delete;
};

