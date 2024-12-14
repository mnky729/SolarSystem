#ifndef CAMERA_H
#define CAMERA_H

// GL Includes
#include <GL/glew.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

// Std. Includes
#include <vector>


// Default camera values
const GLfloat YAW = -90.0f;
const GLfloat PITCH = 0.0f;
const GLfloat SPEED = 8.0f;
const GLfloat SENSITIVTY = 0.05f;
const GLfloat ZOOM = 45.0f;

// Defines several possible options for camera movement. Used as 
// abstraction to stay away from window-system specific input methods
enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

// An abstract camera class that processes input and calculates the
// corresponding Eular Angles, Vectors and Matrices for use in OpenGL
class Camera
{
    // Camera Attributes
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;
    // Eular Angles
    GLfloat Yaw;
    GLfloat Pitch;
    // Camera options
    GLfloat MovementSpeed;
    GLfloat MouseSensitivity;
    GLfloat Zoom;

public:
    //----------------------------------------------------------------+
    // Constructor with vectors					     	              |
    // param position - Camera position.							  |
    // param up - UP vector.    									  |
    // param yaw - yaw angle.    									  |
    // param pitch - pitch angle.    								  |
    //----------------------------------------------------------------+
    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f), GLfloat yaw = YAW, GLfloat pitch = PITCH);

    //----------------------------------------------------------------+
    // Constructor with scalar values.   		     	              |
    //----------------------------------------------------------------+
    Camera(GLfloat posX, GLfloat posY, GLfloat posZ, GLfloat upX, GLfloat upY, GLfloat upZ, GLfloat yaw, GLfloat pitch);

    //-----------------------------------------------------------------+
    // Processes input received from any keyboard-like input system.   |
    // Accepts input parameter in the form of camera defined ENUM      |
    // (to abstract it from windowing systems).                        |
    // param dirextion - Camera direction.                             |
    // param deltaTime - Time between current frame and previous frame.|
    //-----------------------------------------------------------------+
    void processKeyboard(Camera_Movement direction, GLfloat deltaTime);

    //-----------------------------------------------------------------+
    // Processes input received from a mouse input system.             |
    // Expects the offset value in both the x and y direction.         |
    // param (x \ y)offset - The offset movement between the last      |
    // and current frame.                                              |
    // param deltaTime - Time between current frame and previous frame.|
    // param constrainPitch - Camera won't flip if true.               |
    //-----------------------------------------------------------------+    
    void processMouseMovement(GLfloat xoffset, GLfloat yoffset, GLboolean constrainPitch = true);

    //-----------------------------------------------------------------+
    // Processes input received from a mouse scroll-wheel event.       |
    // Only requires input on the vertical wheel-axis                  |
    // param yoffset - The offset movement between the last and        |
    // current frame.                                                  |
    //-----------------------------------------------------------------+    
    void processMouseScroll(GLfloat yoffset);

    // Getters
    GLfloat getZoom() const { return Zoom; }
    glm::mat4 getViewMatrix() const;

    // Setters
    void setPosition(glm::vec3 position);
private:

    // Calculates the front vector from the Camera's (updated) Eular Angles
    void updateCameraVectors();
};

#endif // !CAMERA_H