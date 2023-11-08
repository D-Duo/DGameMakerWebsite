#pragma once
#include "Components.h"
#include "Texture2D.h"

class ComponentMaterial : public Components
{
public:
	ComponentMaterial(shared_ptr<Texture2D>&& t);

	void Enable() override;
	void Disable() override;
	void update() override;

	const Ctype type = COMPONENT_MATERIAL;
	vector<shared_ptr<Texture2D>> mTextures;
	Texture2D::Ptr texture;
	string filepath;
	//bool isActive;

private:
	ComponentMaterial(const ComponentMaterial& cpy) = delete;
	ComponentMaterial& operator=(const ComponentMaterial&) = delete;
};