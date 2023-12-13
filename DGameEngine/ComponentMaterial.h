#pragma once
#include "Components.h"
#include "Texture2D.h"
#include "GameObject.h"

class ComponentMaterial : public Component
{
public:
	ComponentMaterial(shared_ptr<Texture2D> texture = nullptr);

	void update() override;

	shared_ptr<Texture2D> texture;

	Type getType() const override {
		return Type::MATERIAL;
	}

private:
	ComponentMaterial(const ComponentMaterial& cpy) = delete;
	ComponentMaterial& operator=(const ComponentMaterial&) = delete;
};