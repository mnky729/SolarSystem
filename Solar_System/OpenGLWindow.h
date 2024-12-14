#ifndef GLFW_Window_H
#define GLFW_Window_H

// GL Includes
#include <GL/glew.h>
#include <GLFW/glfw3.h>

// GLM Mathematics
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>



// Std. Includes
#include <string>

class OpenGLWindow
{
	GLFWwindow* window = nullptr;
	std::string windowTitle;

	// Window params
	int width = 800, height = 600;
	bool fullScreen = true;

	// Projection Matrix, when size changes, it's recalculated.
	glm::mat4 projectionMatrix = glm::perspective(glm::radians(45.0f), float(width) / float(height), 0.5f, 1000.0f);
public:
	~OpenGLWindow();

	//----------------------------------------------------------------+
	// Initialize GLFW and OpenGL and create window.             	  |
	// param width - Set window windth								  |
	// param height - Set indow height								  |
	// param windowTitle - Set window title							  |
	//----------------------------------------------------------------+
	bool createWindow(int width, int height, std::string windowTitle, bool showfullScreen);

	//----------------------------------------------------------------+
	// Runs the whole application.                              	  |
	//----------------------------------------------------------------+
	void runApp();


	// Getters
	GLFWwindow* getWindow()         const { return window; };
	glm::mat4 getProjectionMatrix() const { return projectionMatrix; };

	// Setters
	void setProjectionMatrix(glm::mat4 proj) { projectionMatrix = proj; };

private:

	//----------------------------------------------------------------+
	// Initializes OpenGL Scene.                                	  |
	//----------------------------------------------------------------+
	void initializeScene();

	//----------------------------------------------------------------+
	// Camera movements.                          					  |
	//----------------------------------------------------------------+
	void doMovement();

	//----------------------------------------------------------------+
	// Performs rendering of OpenGL Scene. (This function have		  |
	// to be in Game loop)						                	  |
	//----------------------------------------------------------------+

	void renderScene();

	//----------------------------------------------------------------+
	// Prints FPS and Frame time in window title					  |
	//----------------------------------------------------------------+
	void showFPS();

	//----------------------------------------------------------------+
	// Is called whenever a key is pressed/released via GLFW		  |
	//----------------------------------------------------------------+
	static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

	//----------------------------------------------------------------+
	// Is called whenever a mouse key is pressed/released via GLFW	  |
	//----------------------------------------------------------------+
	static void mouse_callback(GLFWwindow* window, double xpos, double ypos);

	//----------------------------------------------------------------+
	// Is called whenever a mouse wheel is scrolled via GLFW	      |
	//----------------------------------------------------------------+
	static void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);

	//----------------------------------------------------------------+
	// Is called whenever  the size of the window changes			  |
	//----------------------------------------------------------------+
	void onWindowSizeChanged();
};

#endif // !GLFW_Window_H