#ifndef Wall_h
#define Wall_h

#include "glm/glm.hpp"

class Wall {
    float * vertices;
    int numberOfElements = 36;
    glm::mat4 model;

public:

    Wall(float normal[3]) {
        vertices = new float[numberOfElements] {
            0.0f, 0.0f, 0.0f, normal[0], normal[1], normal[2],
            100.0f, 0.0f, 0.0f, normal[0], normal[1], normal[2],
            100.0f, 100.0f, 0.0f, normal[0], normal[1], normal[2],
            0.0f, 0.0f, 0.0f, normal[0], normal[1], normal[2],
            100.0f, 100.0f, 0.0f,normal[0], normal[1], normal[2],
            0.0f, 100.0f, 0.0f, normal[0], normal[1], normal[2],
        };
        model = glm::mat4();
    }

    ~Wall() {
        delete [] vertices;
    }

    int dataSize() {
        return numberOfElements * sizeof(float);
    }

    float * data() {
        return vertices;
    }

    glm::mat4 matrix() {
        return model;
    }

    void translate(float x, float y, float z) {
        model = glm::translate(model, glm::vec3(x, y, z));
    }

    void rotate(float x, float y, float z) {
        model = glm::rotate(model, glm::radians(x), glm::vec3(1.0, 0.0, 0.0));
        model = glm::rotate(model, glm::radians(y), glm::vec3(0.0, 1.0, 0.0));
        model = glm::rotate(model, glm::radians(z), glm::vec3(0.0, 0.0, 1.0));
    }

    void scale(float scale) {
        model = glm::scale(model, glm::vec3(scale, scale, scale));
    }
};

#endif /* Wall_h */
