#include "ComponentTransform.h"

#include <glm/gtc/quaternion.hpp>

ComponentTransform::ComponentTransform() : _transform(glm::identity<mat4>()) {}

void ComponentTransform::Scale(const vec3& scaleFactors) {
    _transform = glm::scale(_transform, scaleFactors);
}

void ComponentTransform::setScale(const vec3& newScaleFactors) {
    // Extract existing translation and rotation in degrees
    glm::vec3 existingTranslation = extractTranslation();
    glm::vec3 existingRotation = extractRotation();  // Ensure it's in degrees

    // Create a new scaling matrix
    glm::mat4 newScaleMatrix = glm::scale(glm::mat4(1.0f), glm::vec3(newScaleFactors.x, newScaleFactors.y, newScaleFactors.z));

    // Construct the new transformation matrix with updated scale, existing rotation (in radians), and translation
    _transform = glm::translate(glm::mat4(1.0f), existingTranslation) *
        glm::mat4_cast(glm::quat(existingRotation)) *
        newScaleMatrix;
}

void ComponentTransform::Rotate(const glm::vec3& eulerAngles, Space referenceFrame) {
    
    //Translate the axis to the local refernce frame to apply the rotation

    glm::mat3x3 referenceFrameMat = glm::mat3x3(_right, _up, _fw);

    glm::vec3 vecInRefFrame = eulerAngles;
    if (referenceFrame == Space::LOCAL)
        vecInRefFrame = referenceFrameMat * eulerAngles;

    //Generate the rotation matrix that corresponds to the rotation
    glm::mat3x3 rotX = glm::mat3x3(1, 0, 0,
        0, glm::cos(glm::radians(vecInRefFrame.x)), -glm::sin(glm::radians(vecInRefFrame.x)),
        0, glm::sin(glm::radians(vecInRefFrame.x)), glm::cos(glm::radians(vecInRefFrame.x)));

    glm::mat3x3 rotY = glm::mat3x3(glm::cos(glm::radians(vecInRefFrame.y)), 0, glm::sin(glm::radians(vecInRefFrame.y)),
        0, 1, 0,
        -glm::sin(glm::radians(vecInRefFrame.y)), 0, glm::cos(glm::radians(vecInRefFrame.y)));

    glm::mat3x3 rotZ = glm::mat3x3(glm::cos(glm::radians(vecInRefFrame.z)), -glm::sin(glm::radians(vecInRefFrame.z)), 0,
        glm::sin(glm::radians(vecInRefFrame.z)), glm::cos(glm::radians(vecInRefFrame.z)), 0,
        0, 0, 1);

    glm::mat3x3 rotMatrix = rotZ * rotY * rotX;

    //Apply the generated rotation matrix to the existing director vectors
    _fw = rotMatrix * _fw;
    _right = rotMatrix * _right;
    _up = rotMatrix * _up;
}

void ComponentTransform::setRotation(const glm::vec3& eulerAngles, Space referenceFrame) {
    // Convert Euler angles to radians
    glm::vec3 radians = glm::radians(eulerAngles);

    // Create rotation matrices for each axis
    glm::mat4 rotationX = glm::rotate(glm::mat4(1.0), radians.x, glm::vec3(1.0, 0.0, 0.0));
    glm::mat4 rotationY = glm::rotate(glm::mat4(1.0), radians.y, glm::vec3(0.0, 1.0, 0.0));
    glm::mat4 rotationZ = glm::rotate(glm::mat4(1.0), radians.z, glm::vec3(0.0, 0.0, 1.0));

    // Combine the rotations
    glm::mat4 rotationMatrix = rotationZ * rotationY * rotationX;

    // Set the rotation part of the transformation matrix
    if (referenceFrame == Space::LOCAL) {
        // Apply rotation in the local reference frame
        _transform = rotationMatrix;
    }
    else {
        // Apply rotation in the global reference frame
        // Extract translation matrix from _transform
        glm::mat4 translationMatrix(1.0f);
        translationMatrix[3] = glm::vec4(_pos, 1.0f);

        // Multiply the rotation part and the translation part separately
        _transform = translationMatrix * rotationMatrix;
    }
}

void ComponentTransform::setPosition(const vec3& newPosition, Space referenceFrame) {
    if (referenceFrame == Space::LOCAL) {
        // Translate in the local reference frame
        _transform = glm::translate(_transform, newPosition);
    }
    else {
        // Set absolute position in the global reference frame
        _transform[3] = glm::vec4(newPosition, 1.0f);
    }
}

void ComponentTransform::translate(const vec3& translation, Space referenceFrame) {
    if (referenceFrame == Space::LOCAL) {
        // Translate in the local reference frame
        _transform = glm::translate(_transform, translation);
    }
    else {
        // Extract translation matrix from _transform
        glm::mat4 currentTranslationMatrix(1.0f);
        currentTranslationMatrix[3] = glm::vec4(_pos, 1.0f);
        // Translate in the global reference frame
        glm::mat4 translationMatrix = glm::translate(mat4(1.0), translation);
        _transform = translationMatrix * currentTranslationMatrix;
    }
}

void ComponentTransform::update() {
    glMultMatrixd(&_transform[0].x);
}