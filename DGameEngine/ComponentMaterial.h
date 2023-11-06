#pragma once
#include "Components.h"
#include "Texture2D.h"

class ComponentMaterial : public Components
{
public:
	ComponentMaterial(const string path);

	void Enable() override;
	void Disable() override;
	void update() override;

	const Ctype type = COMPONENT_MATERIAL;
	vector<shared_ptr<Texture2D>> mTextures;

private:
	ComponentMaterial(const ComponentMaterial& cpy);
	ComponentMaterial& operator=(const ComponentMaterial&);
};