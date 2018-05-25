#ifndef Prizma_h
#define Prizma_h

#include "glm/glm.hpp"
#include <vector>

class Prizma : public Figure {

    const int numberOfElements = 360;
    int VBO = -1;
    int VAO = -1;

public:

    Prizma() {

        vertices = new float[numberOfElements] {
            // front
            -1.0f, 0.0f, 0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
            -0.5f, 0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
            -0.5f, -0.5f, 0.5f,  0.0f,  0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
            0.5f, 0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
            0.5f, -0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
            1.0f, 0.0f, 0.5f, 0.0f,  0.0f, 1.0f,
            // back
            -1.0f, 0.0f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            -0.5f, 0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
            -0.5f, -0.5f, -0.5f,  0.0f,  0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.5f, 0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
            0.5f, -0.5f, -0.5f, 0.0f,  0.0f, -1.0f,
            1.0f, 0.0f, -0.5f, 0.0f,  0.0f, -1.0f,
            // left, down
            -1.0f, 0.0f, -0.5f, -0.71f, -0.71f, 0.0f,
            -0.5f, -0.5f, -0.5f, -0.71f, -0.71f, 0.0f,
            -0.5f, -0.5f, 0.5f, -0.71f, -0.71f, 0.0f,
            -0.5f, -0.5f, 0.5f, -0.71f, -0.71f, 0.0f,
            -1.0f, 0.0f, 0.5f, -0.71f, -0.71f, 0.0f,
            -1.0f, 0.0f, -0.5f, -0.71f, -0.71f, 0.0f,
            // left, up
            -1.0f, 0.0f, -0.5f, -0.71f, 0.71f, 0.0f,
            -0.5f, 0.5f, -0.5f, -0.71f, 0.71f, 0.0f,
            -0.5f, 0.5f, 0.5f, -0.71f, 0.71f, 0.0f,
            -0.5f, 0.5f, 0.5f, -0.71f, 0.71f, 0.0f,
            -1.0f, 0.0f, 0.5f, -0.71f, 0.71f, 0.0f,
            -1.0f, 0.0f, -0.5f, -0.71f, 0.71f, 0.0f,
            // right, down
            1.0f, 0.0f, -0.5f, 0.71f, -0.71f, 0.0f,
            0.5f, -0.5f, -0.5f, 0.71f, -0.71f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.71f, -0.71f, 0.0f,
            0.5f, -0.5f, 0.5f, 0.71f, -0.71f, 0.0f,
            1.0f, 0.0f, 0.5f, 0.71f, -0.71f, 0.0f,
            1.0f, 0.0f, -0.5f, 0.71f, -0.71f, 0.0f,
            // right, up
            1.0f, 0.0f, -0.5f, 0.71f, 0.71f, 0.0f,
            0.5f, 0.5f, -0.5f, 0.71f, 0.71f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.71f, 0.71f, 0.0f,
            0.5f, 0.5f, 0.5f, 0.71f, 0.71f, 0.0f,
            1.0f, 0.0f, 0.5f, 0.71f, 0.71f, 0.0f,
            1.0f, 0.0f, -0.5f, 0.71f, 0.71f, 0.0f,
            // bottom
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f,  0.5f,  0.0f, -1.0f,  0.0f,
            -0.5f, -0.5f, -0.5f,  0.0f, -1.0f,  0.0f,
            // top
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f,  0.5f,  0.0f,  1.0f,  0.0f,
            -0.5f,  0.5f, -0.5f,  0.0f,  1.0f,  0.0f
        };
        objectColor = glm::vec3(1.0f, 0.5f, 0.31f);
    }

    ~Prizma() {
        delete [] vertices;
    }

    int dataSize() {
        return numberOfElements * sizeof(float);
    }

    int getVBO() {
        return VBO;
    }

    int getVAO() {
        return VAO;
    }

    void setVBO(int newValue) {
        VBO = newValue;
    }

    void setVAO(int newValue) {
        VAO = newValue;
    }

    int getNumberOfVertices() {
        return numberOfElements / 6;
    }

    bool hasPoint(float x, float y, glm::mat4 proj, glm::mat4 cam) {
        glm::vec2 point = glm::vec2(x, y);
        for (int i = 0; i < numberOfElements / 18; i++) {
            glm::vec3 Amodel = matrix() * glm::vec4(vertices[i * 18], vertices[1 + i * 18], vertices[2 + i * 18], 1.0);
            glm::vec3 Bmodel = matrix() * glm::vec4(vertices[6 + i * 18], vertices[7 + i * 18], vertices[8 + i * 18], 1.0);
            glm::vec3 Cmodel = matrix() * glm::vec4(vertices[12 * 18], vertices[13 + i * 18], vertices[14 + i * 18], 1.0);
            glm::vec4 Aw = proj * cam * glm::vec4(Amodel, 1.0);
            glm::vec4 Bw = proj * cam * glm::vec4(Bmodel, 1.0);
            glm::vec4 Cw = proj * cam * glm::vec4(Cmodel, 1.0);
            glm::vec2 A2 = glm::vec2((Aw.x + Aw.w) / (2 * Aw.w) * SCR_WIDTH, (-Aw.y + Aw.w) / (2 * Aw.w) * SCR_HEIGHT);
            glm::vec2 B2 = glm::vec2((Bw.x + Bw.w) / (2 * Bw.w) * SCR_WIDTH, (-Bw.y + Bw.w) / (2 * Bw.w) * SCR_HEIGHT);
            glm::vec2 C2 = glm::vec2((Cw.x + Cw.w) / (2 * Cw.w) * SCR_WIDTH, (-Cw.y + Cw.w) / (2 * Cw.w) * SCR_HEIGHT);
            if (isPointInside(A2, B2, C2, point)) {
                return true;
            }
        }
        return false;
    }

};

#endif /* Prizma_h */
