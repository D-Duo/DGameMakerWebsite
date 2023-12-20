#include <memory>
#include "GameObject.h"
#include "ComponentMesh.h"
#include "ComponentMaterial.h"
#include "ComponentCamera.h"
#include "ComponentTransform.h"
#include <glm/ext/matrix_transform.hpp>

GameObject::GameObject() {
	name = "";
	AddComponent(Component::TRANSFORM);
}

void GameObject::UpdateGameObj() {

	if (!this->isActive) { return; }

	// Save current position
	glPushMatrix();

	for (const auto& components : components)
	{
		if (components) components->update();
	}

	// Unbind any active shader
	glUseProgram(0);

	drawAABBox(aabb());

	// Update for tree structure
	for (const auto& child : children)
	{
		if (child) child->UpdateGameObj();
	}

	// Load last position
	glPopMatrix();
}

void GameObject::AddComponent(Component::Type component) {
	std::unique_ptr<Component> ptr;

	switch (component)
	{
	case Component::Type::TRANSFORM:
		ptr = move(std::make_unique<ComponentTransform>());
		break;
	case Component::Type::MESH:
		ptr = move(std::make_unique<ComponentMesh>());
		break;
	case Component::Type::MATERIAL:
		ptr = move(std::make_unique<ComponentMaterial>());
		break;
	case Component::Type::CAMERA:
		ptr = move(std::make_unique<ComponentCamera>());
		break;
	default:
		cout << "Can't assign wrong component type" << endl;
		break;
	}

	components.push_back(move(ptr));
}

void GameObject::MaterialAddComponent(std::unique_ptr<ComponentMaterial> component) {
	components.push_back(move(component));
}

void GameObject::MeshAddComponent(std::unique_ptr<ComponentMesh> component) {
	components.push_back(move(component));
}

void GameObject::RemoveComponent(unique_ptr<Component> comp) {
	//comp.get_deleter();
}

void GameObject::addChild(unique_ptr<GameObject> child) {
	child->parent = this;
	children.push_back(move(child));
}

static inline void glVec3(const vec3& v) { glVertex3dv(&v.x); }

void GameObject::drawAABBox(const AABBox& aabb) {
    glLineWidth(2);
    glBegin(GL_LINE_STRIP);

    glVec3(aabb.a());
    glVec3(aabb.b());
    glVec3(aabb.c());
    glVec3(aabb.d());
    glVec3(aabb.a());

    glVec3(aabb.e());
    glVec3(aabb.f());
    glVec3(aabb.g());
    glVec3(aabb.h());
    glVec3(aabb.e());
    glEnd();

    glBegin(GL_LINES);
    glVec3(aabb.h());
    glVec3(aabb.d());
    glVec3(aabb.f());
    glVec3(aabb.b());
    glVec3(aabb.g());
    glVec3(aabb.c());
    glEnd();
}

AABBox GameObject::aabb() const {
	AABBox aabbox;
	if (_graphic.get()) aabbox = _graphic->aabb;
	else if (children.empty()) {
		aabbox.min = vec3(0);
		aabbox.max = vec3(0);
	}

	for (const auto& child : children) {
		const auto child_aabb = (child->GetComponent<ComponentTransform>()->GetTransform() * child->aabb()).AABB();
		aabbox.min = glm::min(aabbox.min, child_aabb.min);
		aabbox.max = glm::max(aabbox.max, child_aabb.max);
	}

	return aabbox;
}