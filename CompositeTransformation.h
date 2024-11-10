#ifndef COMPOSITETRANSFORMATION_H
#define COMPOSITETRANSFORMATION_H

#include "Transformation.h"
#include <vector>
#include <memory>
#include <glm/glm.hpp>

class CompositeTransformation : public Transformation {
public:
    void addTransformation(std::shared_ptr<Transformation> transformation);

    glm::mat4 getMatrix() const override;

private:
    std::vector<std::shared_ptr<Transformation>> transformations;
};

#endif
