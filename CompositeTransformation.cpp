#include "CompositeTransformation.h"

void CompositeTransformation::addTransformation(std::shared_ptr<Transformation> transformation) {
    transformations.push_back(transformation);
}

void CompositeTransformation::clear() {
    transformations.clear();
}

glm::mat4 CompositeTransformation::getMatrix() const {
    glm::mat4 result = glm::mat4(1.0f);
    for (const auto& transformation : transformations) {
        result *= transformation->getMatrix();
        return result;
    }
}