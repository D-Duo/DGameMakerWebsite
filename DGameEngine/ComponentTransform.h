#pragma once
#include "EngineGlobals.h"
#include "Components.h"

class ComponentTransform : public Component
{
public:

	enum class Space
	{
		LOCAL,
		GLOBAL,
	};

	ComponentTransform();

	void update() override;

	Type getType() const override {
		return Type::TRANSFORM;
	}

private:

	union {
		mat4 _transform;
		struct {
			vec3 _right; double __rightw;
			vec3 _up; double __upw;
			vec3 _fw; double __fww;
			vec3 _pos;
		};
	};

public:

	void setScale(const vec3& scaleFactors);
	void setRotation(const glm::vec3& eulerAngles, Space referenceFrame = Space::LOCAL);
	void setPosition(const vec3& newPosition, Space referenceFrame = Space::GLOBAL);

	void translate(const vec3& translation, Space referenceFrame = Space::LOCAL);

	//Getters
	vec3 GetRight() const { return _right; }
	vec3 GetUp() const { return _up; }
	vec3 GetForward() const { return _fw; }

	vec3 GetPosition() const { return _pos; }
	mat4 GetTransform() const { return _transform; }

	//Setters
	void RightSetter(vec3 vec) { _right = vec; }
	void UpSetter(vec3 vec) { _up = vec; }
	void ForwardSetter(vec3 vec) { _fw = vec; }
	void PositionSetter(vec3 vec) { _pos = vec; }
	void TransformSetter(mat4 mat) { _transform = mat; }

private:
	ComponentTransform(const ComponentTransform& cpy) = delete;
	ComponentTransform& operator=(const ComponentTransform&) = delete;
};