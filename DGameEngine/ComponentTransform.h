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

	void Scale(const vec3& scaleFactors);
	void Rotate(const glm::vec3& eulerAngles, Space referenceFrame = Space::LOCAL);
	void setPosition(const vec3& newPosition, Space referenceFrame = Space::GLOBAL);
	void setRotation(const glm::vec3& eulerAngles, Space referenceFrame = Space::LOCAL);

	void translate(const vec3& translation, Space referenceFrame = Space::LOCAL);
	void setScale(const vec3& newScaleFactors);

	

	//Getters
	vec3 GetRight() const { return _right; }
	vec3 GetUp() const { return _up; }
	vec3 GetForward() const { return _fw; }
	mat4 GetTransform() const { return _transform; }

	vec3 extractTranslation() {
		return vec3(_transform[3]);
	}

	vec3 extractRotation() {
		vec3 rotation;

		rotation.x = atan2(_transform[1][2], _transform[2][2]);
		rotation.y = atan2(-_transform[0][2], sqrt(_transform[1][2] * _transform[1][2] + _transform[2][2] * _transform[2][2]));
		rotation.z = atan2(_transform[0][1], _transform[0][0]);

		return rotation;  // Convert to degrees if needed
	}

	vec3 extractRotationEuler() {
		vec3 rotation;

		// Extract pitch (x-axis rotation)
		rotation.x = glm::degrees(atan2(_transform[1][2], _transform[2][2]));

		// Extract yaw (y-axis rotation)
		rotation.y = glm::degrees(atan2(-_transform[0][2], sqrt(_transform[1][2] * _transform[1][2] + _transform[2][2] * _transform[2][2])));

		// Extract roll (z-axis rotation)
		rotation.z = glm::degrees(atan2(_transform[0][1], _transform[0][0]));

		return rotation;
	}

	vec3 extractScale() {
		vec3 scale;

		scale.x = length(vec3(_transform[0]));
		scale.y = length(vec3(_transform[1]));
		scale.z = length(vec3(_transform[2]));

		return scale;
	}

	//Setters
	void RightSetter(vec3 vec) { _right = vec; }
	void UpSetter(vec3 vec) { _up = vec; }
	void ForwardSetter(vec3 vec) { _fw = vec; }
	void PosSetter(vec3 position) { _pos = position; }
	void TransformSetter(mat4 mat) { _transform = mat; }

private:
	ComponentTransform(const ComponentTransform& cpy) = delete;
	ComponentTransform& operator=(const ComponentTransform&) = delete;
};