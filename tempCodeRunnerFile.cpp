#include<cstdio>
#include<GL/glew.h> //OpenGL is implemented by hardware drivers (NVIDIA, AMD, Intel). Because of this, new OpenGL functions aren't automatically available in C++ at compile-time.
#include<GLFW/glfw3.h> //OpenGL does not know how to create a desktop window, track a mouse, or detect a keyboard press (like pressing Space to shoot). GLFW bridges that gap. It handles cross-platform window management and OS input events.

#define GL_ERROR_CASE(glerror)\
case glerror: snprintf(error, sizeof(error), "%s", #glerror)

inline void gl_debug(const char *file,  int line){
    GLenum err; 
    while((err = glGetError()) != GL_NO_ERROR){
        char error[128]; 

        switch(err){
            GL_ERROR_CASE(GL_INVALID_ENUM); break; 
            GL_ERROR_CASE(GL_INVALID_VALUE); break;
            GL_ERROR_CASE(GL_INVALID_OPERATION); break;
            GL_ERROR_CASE(GL_INVALID_FRAMEBUFFER_OPERATION); break;
            GL_ERROR_CASE(GL_OUT_OF_MEMORY); break;
            default: snprintf(error, sizeof(error), "%s", "UNKNOWN_ERROR"); break;
        }
        fprintf(stderr, "%s - %s: %d\n", error, file, line); 
    }
}

#undef GL_ERROR_CASE

void error_Callback(int error, const char* description){
    fprintf(stderr, "Error: %s\n", description); 
}

int main(int argc, char* argv[]){
    glfwSetErrorCallback(error_Callback); 
    GLFWwindow* window; 
    if(!glfwInit()) return -1; 

    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3); 
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 

    /*Create a windowed mode window and its OpenGL context*/
    window = glfwCreateWindow(640, 480, "Space Invaders", NULL, nullptr); 
    if(!window){
        glfwTerminate(); 
        return -1; 
    }

    glfwMakeContextcurrent(window); 

    Glenum err = glewInit();
    if(err != GlEW_OK){
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err)); 
        glfwTerminate(); 
        return -1; 
    }

    int glVersion[2] = {-1, 1}; 
    glGetIntegerv(GL_MAJOR_VERSION, &glVersion[0]); 
    glGetIntegerv(GL_MINOR_VERSION, &glVersion[1]); 

    gl_debug(__FILE__, __LINE__); 
    printf("Using OpenGL %d.%d\n", glVersion[0], glVersion[1]); 
    printf("Renderer used: %s\n", glGetString(GL_RENDERER)); 
    printf("Shading Language: %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

    glClearColor(1.0, 0.0, 0.0, 1.0); 
    while(!glfwWindowShouldClose(window)){

        glClear(GL_COLOR_BUFFER_BIT); 
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    
    glfwDestroyWindow(window); 
    glfwTerminate();

    return 0; 
}