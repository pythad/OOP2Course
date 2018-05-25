#ifndef Figure_h
#define Figure_h

#include <array>

class Figure {

    float distance(glm::vec2 A, glm::vec2 B) {
        return std::sqrt(std::pow(A.x - B.x, 2) + std::pow(A.y - B.y, 2));
    }

    float findAngle(glm::vec2 A, glm::vec2 B, glm::vec2 C) {
        float a = distance(B, C);
        float b = distance(A, C);
        float c = distance(A, B);
        float cos = (b * b + c * c - a * a) / (2 * b * c);
        return std::acos(cos);
    }

public:

    float * vertices;
    glm::vec3 objectColor;
    std::array<float, 7> modelData = {1.0, 1.0, 1.0, 0.0, 0.0, 0.0, 1.0};
    
    const unsigned int SCR_WIDTH = 800;
    const unsigned int SCR_HEIGHT = 600;

    bool isPointInside(glm::vec2 A, glm::vec2 B, glm::vec2 C, glm::vec2 point) {
        double PI = 3.14159265;
        float a = findAngle(point, B, C) * 180 / PI;
        float b = findAngle(point, A, C) * 180 / PI;
        float c = findAngle(point, A, B) * 180 / PI;
        float sum = a + b + c;
        return (sum > 355) && (sum < 365);
    }

//public:

    virtual int dataSize() = 0;

    virtual int getNumberOfVertices() = 0;

    const std::array<float, 7> getModelData() const {
        return this->modelData;
    }

    void setModelData(std::array<float, 7> modelData) {
        this->modelData = modelData;
    }

    float * data() {
        return vertices;
    }

    glm::vec3 getObjectColor() {
        return objectColor;
    }

    void setObjectColor(glm::vec3 newColor) {
        objectColor = newColor;
    }

    glm::mat4 matrix() {
        glm::mat4 matrix = glm::mat4();
        float scaleFactor = modelData[6];
        matrix = glm::scale(matrix, glm::vec3(scaleFactor, scaleFactor, scaleFactor));
        matrix = glm::translate(matrix, glm::vec3(modelData[0], modelData[1], modelData[2]) / scaleFactor);
        matrix = glm::rotate(matrix, modelData[3], glm::vec3(1.0, 0.0, 0.0));
        matrix = glm::rotate(matrix, modelData[4], glm::vec3(0.0, 1.0, 0.0));
        matrix = glm::rotate(matrix, modelData[5], glm::vec3(0.0, 0.0, 1.0));
        return matrix;
    }

    void translate(float x, float y, float z) {
        modelData[0] += x;
        modelData[1] += y;
        modelData[2] += z;
    }

    void rotate(float x, float y, float z) {
        modelData[3] += glm::radians(x);
        modelData[4] += glm::radians(y);
        modelData[5] += glm::radians(z);
    }

    void scale(float scale) {
        modelData[6] += scale / 10;
    }

    virtual bool hasPoint(float x, float y, glm::mat4 proj, glm::mat4 cam) = 0;
};


#endif /* Figure_h */
