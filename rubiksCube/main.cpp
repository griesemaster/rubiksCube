#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <shader.h>
#include <cubie.h>
#include <cube.h>

#include <iostream>
#include <filesystem>

// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 900;

// camera setup
// ------------------------------------
glm::vec3 cameraPos = glm::vec3(-5.0f, 4.0f, 6.0f);
glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
glm::vec3 cameraTarget = glm::vec3(0.0f, 0.0f, 0.0f);
glm::vec3 cameraDirection = glm::normalize(cameraPos - cameraTarget);
glm::vec3 cameraUp = glm::vec3(0.0f, 1.0f, 0.0f);

bool firstMouse = true;
float yaw = -90.0f;
float pitch = 0.0f;
float fov = 45.0f;
//mouse cords (starts in the center)
float lastX = SCR_WIDTH / 2, lastY = SCR_HEIGHT / 2;




//timing 
float lastFrame = 0.0f;
float deltaTime = 0.0f;

// create cube object
Cube cube = Cube();

int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


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
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  //this line associates the function framebuffer_size_callback with the resize event

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }


    //set one time enables for openGL
    glEnable(GL_DEPTH_TEST);
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);


    // build and compile our shader program
    // ------------------------------------


    Shader ourShader("C:\\Users\\Michael\\source\\repos\\rubiksCube\\rubiksCube\\shader.vs", "C:\\Users\\Michael\\source\\repos\\rubiksCube\\rubiksCube\\shader.fs");


    //Vertex Data for a square with face made of two triangles 
    float cubeVerticies[] = {
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,

        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,

         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,

        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
    };

    float colors[] = {
        //back face
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,

        //front face
        1.0f, 0.65f, 0.0f,
        1.0f, 0.65f, 0.0f,
        1.0f, 0.65f, 0.0f,

        1.0f, 0.65f, 0.0f,
        1.0f, 0.65f, 0.0f,
        1.0f, 0.65f, 0.0f,


        //left face
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        //right face
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        //bottom face
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,
        1.0f, 1.0f, 0.0f,

        //top face
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,

        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
        1.0f, 1.0f, 1.0f,
    };

    //used to place the cubes in the environment
    glm::vec3 cubePositions[] = {
        glm::vec3(0.0f,  0.0f,  -4.0f),
    };



    unsigned int vertexBuffer, colorBuffer, VAO;
    glGenBuffers(1, &vertexBuffer);  //generate buffer and array objects
    glGenBuffers(1, &colorBuffer);
    glGenVertexArrays(1, &VAO);


    glBindVertexArray(VAO);     //bind to VAO to change it's contained data (VBO)

    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //bind VBO as current buffer to edit
    glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_DYNAMIC_DRAW);  //input vertex data into the vertex buffer
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);   //explain how to read the new data in buffer
    glEnableVertexAttribArray(0);   //enable the location attribute on current VAO - hence the array in func. call 
    //enables color attribute

    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0);   //remove VAO and VBO from the edit pointers to prevent accidental changes - we are set up to draw! 
    glBindVertexArray(0);


    cube.generateCubies();


    // render loop
    // -----------

    while (!glfwWindowShouldClose(window))
    {
        //timing tracking
        float currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;


        // input
        // -----
        processInput(window);

        // render
        // ------
        //clear buffers
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //enable wireframe mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);


        // activate shader
        ourShader.use();

        // create transformations
        glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
        //FOV -             Aspect Ratio -      Near Distance - Far Distance
        ourShader.setMat4("projection", projection);
        view = glm::lookAt(cameraPos, cameraPos + cameraFront, cameraUp);

        ourShader.setMat4("view", view);

        // render control box
        glBindVertexArray(VAO);
        for (unsigned int i = 0; i < sizeof(cubePositions) / sizeof(glm::vec3); i++)
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[i]);
            if (i % 2 == 1) {
                // model = glm::rotate(model, glm::radians(45.0f), glm::vec3(0, 1, 0));
                float newColors[] = {
                    //first triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),
                     //second triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),

                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),
                     //second triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),

                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),
                     //second triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),

                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),
                     //second triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),

                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),
                     //second triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),

                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime()),
                     //second triangle
                     (float)sin(glfwGetTime()), 0.0f, 0.0f,
                     0.0f, (float)cos(glfwGetTime()), 0.0f,
                     0.0f, 0.0f, (float)tan(glfwGetTime())
                };
                glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(newColors), newColors, GL_DYNAMIC_DRAW);
            }
            else {
                glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
                glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);
            }


            glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer); //bind VBO as current buffer to edit
            glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_DYNAMIC_DRAW);  //input vertex data into the vertex buffer
            ourShader.setMat4("model", model);
            glDrawArrays(GL_TRIANGLES, 0, 36);
        }


        //draw the cube
        cube.draw(ourShader);



        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow* window)
{
    //termination
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    //camera controls
    const float cameraSpeed = 2.5f * deltaTime;
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        cameraPos += cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        cameraPos -= cameraSpeed * cameraFront;
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        cameraPos -= glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        cameraPos += glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed;

    //Y Face rotations key bindings
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        cube.rotateZPositiveClockwise(false);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        cube.rotateZPositiveCounterwise(false);

    //fun keybinds
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        cube.reset();
}


// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //resize viewport to match new dimensions
    glViewport(0, 0, width, height);
}


void mouse_callback(GLFWwindow* window, double xpos, double ypos) {

    if (firstMouse) {   //prevents large jump/jitter on first movement
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float deltaX = xpos - lastX;
    float deltaY = lastY - ypos;
    lastX = xpos;
    lastY = ypos;

    const float senstivity = 0.1f;
    deltaX *= senstivity;
    deltaY *= senstivity;

    yaw += deltaX;
    pitch += deltaY;

    if (pitch > 89.0f) { pitch = 89.0f; };  //prevent flipping when looking at extreme angles (this code causes gimbal lock but cannot be avoided)
    if (pitch < -89.0f) { pitch = -89.0f; };

    glm::vec3 direction;
    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
}
// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    fov -= (float)yoffset;
    if (fov < 1.0f)
        fov = 1.0f;
    if (fov > 45.0f)
        fov = 45.0f;
}
