#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <stb_image.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

#include <shader.h>
#include <cubie.h>
#include <GLcube.h>
#include <cubetroller.h>
#include <arcballCamera.h>

#include <iostream>
#include <filesystem>

//pi constant because math imports being fucky
constexpr auto M_PI = 3.14159265358979323846;


// function prototypes
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void processInput(GLFWwindow* window);
void showFPS(GLFWwindow* window);

// settings
unsigned int screenWidth = 900;
unsigned int screenHeight = 900;


// create cube object
float dimension = 3.0f;
Cube cube = Cube(dimension);
Cubetroller cubetroller = Cubetroller();


// camera setup
// ------------------------------------
arcballCamera arcball = arcballCamera(screenWidth, screenHeight, 0.05f);

//mouse input setup (starts in the center)
float lastX = screenWidth / 2, lastY = screenHeight / 2;
bool cameraShouldMove = false;
bool firstMouse = true;
glm::vec3 clickPoint;

//timing 
float lastFrame = 0.0f;
float deltaTime = 0.0f;
double FPSlastTime = glfwGetTime();
int frameCount = 0;


int main()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    // glfw window creation
    // --------------------
   

    GLFWwindow* window = glfwCreateWindow(screenWidth, screenHeight, "Rubik's Cube Simulator", NULL, NULL);
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
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glLineWidth(5.0f);

    // build and compile our shader program
    // ------------------------------------
    Shader ourShader("C:\\Users\\Michael\\source\\repos\\rubiksCube\\rubiksCube\\openGl\\shaderSrc\\shader.vs", "C:\\Users\\Michael\\source\\repos\\rubiksCube\\rubiksCube\\openGl\\shaderSrc\\shader.fs");


    //Vertex Data for a square with face made of two triangles 
    float cubeVerticies[] = {
        //----------------- cube face infos
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

        //------------------- outline vertex infos
        //X faces
        -0.5f, -0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f, 
         0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        //Y faces
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f,  0.5f,
        -0.5f, -0.5f, -0.5f,
        -0.5f,  0.5f, -0.5f,
         0.5f, -0.5f, -0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f,  0.5f,

        //Z faces
        -0.5f, -0.5f, -0.5f,
        -0.5f, -0.5f,  0.5f,
        -0.5f,  0.5f, -0.5f,
        -0.5f,  0.5f,  0.5f,
         0.5f, -0.5f, -0.5f, 
         0.5f, -0.5f,  0.5f,
         0.5f,  0.5f, -0.5f,
         0.5f,  0.5f,  0.5f
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
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,
        0.0f, 0.0f, 1.0f,

        //right face
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        0.0f, 1.0f, 0.0f,

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

    unsigned int cubeBuffer, colorBuffer, VAO;
    glGenBuffers(1, &cubeBuffer);  //generate buffer and array objects
    glGenBuffers(1, &colorBuffer);
    glGenVertexArrays(1, &VAO);


    glBindVertexArray(VAO);     //bind to VAO to change it's contained data (VBO)

    glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer); //bind VBO as current buffer to edit
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
    cubetroller.setCube(&cube);

    

    // render loop
    // -----------

    while (!glfwWindowShouldClose(window))
    {

        // input
        // -----
        processInput(window);

        // render
        // ------
        //clear buffers
        //glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClearColor(0.066f, 0.101f, 0.13f, 0.25f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        //bind the generated buffers after clearing
        glBindVertexArray(VAO);
        glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_DYNAMIC_DRAW);

        glBindBuffer(GL_ARRAY_BUFFER, cubeBuffer); //bind VBO as current buffer to edit
        glBufferData(GL_ARRAY_BUFFER, sizeof(cubeVerticies), cubeVerticies, GL_DYNAMIC_DRAW);  //input vertex data into the vertex buffer


        //enable wireframe mode
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

        // activate shader
        ourShader.use();

        // world matricies
        glm::mat4 projection = glm::mat4(1.0f);
        projection = glm::perspective(glm::radians(45.0f), (float)screenWidth / (float)screenHeight, 0.1f, 100.0f);
        //FOV -             Aspect Ratio -      Near Distance - Far Distance
        ourShader.setMat4("projection", projection);
          

        ourShader.setMat4("view", arcball.getViewMatrix());
      
        

        //draw the cube
        cube.drawCubies(&ourShader);

        //display FPS in name bar
        showFPS(window);

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
    if (glfwGetKey(window, GLFW_KEY_Q) == GLFW_PRESS)
        cube.triggerBreakpoint();


    if (glfwGetKey(window, GLFW_KEY_F) == GLFW_PRESS)
        cube.rotateZClockwiseFrontQUATSTACK(false);

    //Y Face rotations key bindings
    if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
        cubetroller.F(false);
    if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
        cubetroller.Fp(false);
    if (glfwGetKey(window, GLFW_KEY_3) == GLFW_PRESS)
        cubetroller.U(false);
    if (glfwGetKey(window, GLFW_KEY_4) == GLFW_PRESS)
        cubetroller.Up(false);
    if (glfwGetKey(window, GLFW_KEY_5) == GLFW_PRESS)
        cubetroller.R(false);
    if (glfwGetKey(window, GLFW_KEY_6) == GLFW_PRESS)
        cubetroller.Rp(false);
    if (glfwGetKey(window, GLFW_KEY_9) == GLFW_PRESS)
        cubetroller.superFlip();
    if (glfwGetKey(window, GLFW_KEY_0) == GLFW_PRESS)
        cube.reset();
}


void mouse_callback(GLFWwindow* window, double currentX, double currentY) {
    if (firstMouse) {
        lastX = currentX;
        lastY = currentY;
        firstMouse = false;
    }
    arcball.cursorCallback(window, currentX, currentY);
 
}

//glfw : function is triggered on mouse click
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    //will return true if left click, will default to false if left unclicks
    arcball.mouseButtonCallback(window, button, action, mods);
}


// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
    ;//does nothing
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    //resize viewport to match new dimensions
    glViewport(0, 0, width, height);
    screenHeight = height;
    screenWidth = width;
}

// draws the current FPS and time per frame in the window title
void showFPS(GLFWwindow* pWindow)
{
    // Measure speed
    double currentTime = glfwGetTime();
    double delta = currentTime - FPSlastTime;
    frameCount++;
    if (delta >= 1.0) { // If last cout was more than 1 sec ago

        double fps = double(frameCount) / delta;
        double tpf = 1000.0 / double(frameCount);

        std::stringstream ss;
        ss << "RubiSim" << " " << "V1.0-beta" << " [" << fps << " FPS" << " " << tpf << "ms Per Frame]";

        glfwSetWindowTitle(pWindow, ss.str().c_str());

        frameCount = 0;
        FPSlastTime = currentTime;
    }
}
