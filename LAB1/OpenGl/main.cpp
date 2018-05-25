#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

#include "shader_m.h"
#include "camera.h"
#include "Cube.hpp"
#include "Prizma.hpp"
#include "Wall.hpp"

#include <iostream>
#include <fstream>
#include <vector>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow *window);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

template<typename T>
std::ostream& binary_write(std::ostream& stream, const T& value){
    return stream.write(reinterpret_cast<const char*>(&value), sizeof(T));
}

template<typename T>
std::istream & binary_read(std::istream& stream, T& value){
    return stream.read(reinterpret_cast<char*>(&value), sizeof(T));
}

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera(glm::vec3(3.0f, 3.0f, 10.0f));
float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;
bool createCube = true;
bool createPrizma = false;

// matrices
glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
glm::mat4 view = camera.GetViewMatrix();

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

// lighting
glm::vec3 lightPos(5.0f, 10.0f, 20.0f);

//chosen figure
int changedColor = 0;

std::vector<bool> activeFigures = { };
std::vector<Figure *> figures = { };

int main(int argc, char **argv)
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // uncomment this statement to fix compilation on OS X
#endif

    // glfw window creation
    // --------------------
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile our shader zprogram
    // ------------------------------------
    Shader lightingShader("/Users/vladyslavovchynnykov/Downloads/OpenGl/OpenGl/shaders/lighting.vs", "/Users/vladyslavovchynnykov/Downloads/OpenGl/OpenGl/shaders/lighting.fs");
    Shader lampShader("/Users/vladyslavovchynnykov/Downloads/OpenGl/OpenGl/shaders/lamp.vs", "/Users/vladyslavovchynnykov/Downloads/OpenGl/OpenGl/shaders/lamp.fs");

    std::ifstream inStream("data", std::ios::binary);
    int count;
    binary_read(inStream, count);
    figures = std::vector<Figure *>(count);
    for (int i = 0; i < count; i++) {
        int type;
        binary_read(inStream, type);
        Figure * figure = nullptr;
        if (type == 1) {
            figure = new Cube();
        } else {
            figure = new Prizma();
        }
        std::array<float, 7> data = std::array<float, 7>();
        for (int j = 0; j < 7; j++) {
            float property;
            binary_read(inStream, property);
            data[j] = property;
        }
        figure->setModelData(data);
        figures[i] = figure;
        activeFigures.push_back(false);
    }

    // set up vertex data (and buffer(s)) and configure vertex attributes
    // ------------------------------------------------------------------
//    Figure * cube = new Cube();
//    cube->translate(7, 4, 3);
//    figures.push_back(cube);
//    activeFigures.push_back(false);
//    Figure * prizma = new Prizma();
//    prizma->translate(2, 2, 2);
//    figures.push_back(prizma);
//    activeFigures.push_back(false);

    float xy[3] = { 0.0f,  0.0f,  1.0f };
    float xz[3] = { 1.0f,  0.0f,  0.0f };
    float yz[3] = { 0.0f,  1.0f,  0.0f };
    std::vector<Wall *> walls = {
        new Wall(xy), new Wall(xz), new Wall(yz)
    };
    walls[1]->rotate(0, 90, 0);
    walls[1]->translate(-100, 0, 0);
    walls[2]->rotate(-90, 0, 0);
    walls[2]->translate(0, -100, 0);

    // first, configure the cube's VAO (and VBO)
    unsigned int cubeVBO, cubeVAO;
    glGenVertexArrays(1, &cubeVAO);
    glGenBuffers(1, &cubeVBO);

    Figure * cube = new Cube();
    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    glBufferData(GL_ARRAY_BUFFER, cube->dataSize(), cube->data(), GL_STATIC_DRAW);
    delete cube;

    glBindVertexArray(cubeVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);


    unsigned int prizmaVBO, prizmaVAO;
    glGenVertexArrays(1, &prizmaVAO);
    glGenBuffers(1, &prizmaVBO);

    Figure * prizma = new Prizma();
    glBindBuffer(GL_ARRAY_BUFFER, prizmaVBO);
    glBufferData(GL_ARRAY_BUFFER, prizma->dataSize(), prizma->data(), GL_STATIC_DRAW);
    delete prizma;

    glBindVertexArray(prizmaVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    unsigned int wallVBO, wallVAO;
    glGenVertexArrays(1, &wallVAO);
    glGenBuffers(1, &wallVBO);

    glBindBuffer(GL_ARRAY_BUFFER, wallVBO);
    glBufferData(GL_ARRAY_BUFFER, walls[0]->dataSize(), walls[0]->data(), GL_STATIC_DRAW);

    glBindVertexArray(wallVAO);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // normal attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // second, configure the light's VAO (VBO stays the same; the vertices are the same for the light object which is also a 3D cube)
    unsigned int lightVAO;
    glGenVertexArrays(1, &lightVAO);
    glBindVertexArray(lightVAO);

    glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
    // note that we update the lamp's position attribute's stride to reflect the updated buffer data
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);


    // render loop
    // -----------
    while (!glfwWindowShouldClose(window))
    {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        // input
        // -----
        processInput(window);

        // render
        // ------
        glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        view = camera.GetViewMatrix();

        for (auto &&figure : figures) {
            for (int i = 0; i < 4; i++) {
                // be sure to activate shader when setting uniforms/drawing objects
                lightingShader.use();
                lightingShader.setVec3("objectColor", figure->getObjectColor());
                lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
                lightingShader.setVec3("lightPos", lightPos);
                lightingShader.setVec3("viewPos", camera.Position);

                // view/projection transformations
                lightingShader.setMat4("projection", projection);
                lightingShader.setMat4("view", view);
                lightingShader.setInt("axis", i);

                // world transformation
                glm::mat4 mat = figure->matrix();
                lightingShader.setMat4("model", mat);

                // render the cube
                if (figure->getNumberOfVertices() == 36) {
                    glBindVertexArray(cubeVAO);
                } else {
                    glBindVertexArray(prizmaVAO);
                }
                glDrawArrays(GL_TRIANGLES, 0, figure->getNumberOfVertices());
            }
        }

        for (auto &&wall : walls) {
            // be sure to activate shader when setting uniforms/drawing objects
            lightingShader.use();
            lightingShader.setVec3("objectColor", 0.5f, 0.31f, 1.0f);
            lightingShader.setVec3("lightColor", 1.0f, 1.0f, 1.0f);
            lightingShader.setVec3("lightPos", lightPos);
            lightingShader.setVec3("viewPos", camera.Position);

            // view/projection transformations
            lightingShader.setMat4("projection", projection);
            lightingShader.setMat4("view", view);
            lightingShader.setInt("axis", 0);

            // world transformation
            lightingShader.setMat4("model", wall->matrix());

            // render the cube
            glBindVertexArray(wallVAO);
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        // also draw the lamp object
        lampShader.use();
        lampShader.setMat4("projection", projection);
        lampShader.setMat4("view", view);
        glm::mat4 model;
        model = glm::mat4();
        model = glm::translate(model, lightPos);
        model = glm::scale(model, glm::vec3(0.2f)); // a smaller cube
        lampShader.setMat4("model", model);

        glBindVertexArray(lightVAO);
        glDrawArrays(GL_TRIANGLES, 0, 36);


        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    std::ofstream stream("data", std::ios::binary);
    count = figures.size();
    binary_write(stream, count);
    for (int i = 0; i < count; i++) {
        if (figures[i]->getNumberOfVertices() == 36) {
            int type = 1;
            binary_write(stream, type);
        } else {
            int type = 2;
            binary_write(stream, type);
        }

        std::array<float, 7> data = figures[i]->getModelData();

        for (int j = 0; j < 7; j++) {
            binary_write(stream, data[j]);
        }
    }
    stream.close();

    for (auto &&figure : figures) {
        delete figure;
    }

    // optional: de-allocate all resources once they've outlived their purpose:
    // ------------------------------------------------------------------------
    glDeleteVertexArrays(1, &cubeVAO);
    glDeleteVertexArrays(1, &lightVAO);
    glDeleteBuffers(1, &cubeVBO);

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    bool cameraActive = true;
    for (int i = 0; i < figures.size(); i++) {
        if (activeFigures[i]) cameraActive = false;
    }

    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_PRESS) {
        if (changedColor == 0) {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) {
                    glm::vec3 newColor = glm::vec3(rand() / float(INT_MAX), rand() / float(INT_MAX), rand() / float(INT_MAX));
                    figures[i]->setObjectColor(newColor);
                }
            }
            changedColor = 1;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_C) == GLFW_RELEASE) {
        changedColor = 0;
    }

    if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessMouseMovement(-5, 0);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->rotate(0, -1, 0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessMouseMovement(5, 0);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->rotate(0, 1, 0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessMouseMovement(0, 5);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->rotate(-1, 0, 0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessMouseMovement(0, -5);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->rotate(1, 0, 0);
            }
        }
    }


    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessKeyboard(FORWARD, deltaTime);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->translate(0.0, 0.03, 0.0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessKeyboard(BACKWARD, deltaTime);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->translate(0.0, -0.03, 0.0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessKeyboard(LEFT, deltaTime);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->translate(-0.03, 0.0, 0.0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        if (cameraActive) {
            camera.ProcessKeyboard(RIGHT, deltaTime);
        } else {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->translate(0.03, 0.0, 0.0);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_R) == GLFW_PRESS) {
        if (!cameraActive) {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->translate(0.0, 0.0, -0.03);
            }
        }
    }
    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS) {
        if (!cameraActive) {
            for (int i = 0; i < figures.size(); i++) {
                if (activeFigures[i]) figures[i]->translate(0.0, 0.0, 0.03);
            }
        }
    }

    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_PRESS && !createCube) {
        Figure * figure = new Cube();
        figures.push_back(figure);
        createCube = true;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_RELEASE) {
        createCube = false;
    }
    if (glfwGetKey(window, GLFW_KEY_M) == GLFW_PRESS && !createPrizma) {
        Figure * figure = new Prizma();
        figures.push_back(figure);
        createPrizma = true;
    }
    if (glfwGetKey(window, GLFW_KEY_N) == GLFW_RELEASE) {
        createPrizma = false;
    }
    if (glfwGetKey(window, GLFW_KEY_U) == GLFW_PRESS) {
        for (int i = figures.size() - 1; i >= 0 ; i--) {
            if (activeFigures[i]) {
                figures.erase(figures.begin() + i);
                activeFigures.erase(activeFigures.begin() + i);
            }
        }
    }
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        for (int i = 0; i < figures.size(); i++) {
            if (figures[i]->hasPoint(xpos, ypos, projection, view)) {
                activeFigures[i] = !activeFigures[i];
            }
        }
    }
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    bool cameraActive = true;
    for (int i = 0; i < figures.size(); i++) {
        if (activeFigures[i]) cameraActive = false;
    }

    if (cameraActive) {
        camera.ProcessMouseScroll(yoffset);
    } else {
        for (int i = 0; i < figures.size(); i++) {
            if (activeFigures[i]) figures[i]->scale(-yoffset);
        }
    }
}
