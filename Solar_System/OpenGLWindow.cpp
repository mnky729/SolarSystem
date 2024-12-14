// GL Includes
#include "GL/glew.h"
#include "GLFW/glfw3.h"

// GLM Mathematics
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

// SOIL
#include "soil.h"

// Audio library includes
#include "audiere.h"

// Other includes
#include "OpenGLWindow.h"
#include "Shader.h"
#include "ShaderProgram.h"
#include "Camera.h"
#include "Sphere.h"
#include "Texture.h"
#include "BufferObjects.h"

// Std. Includes
#include <iostream>
#include <sstream>


//Camera
Camera camera;
GLfloat lastX = 400, lastY = 300;
bool firstMouse = true;
enum Planets {
	Mercury, Venus,  Earth,   
	Moon,    Mars, 	 Jupiter, 
	Saturn,  Uranus, Neptune,
	Space
};

Planets PlanetViewe;

// Keys buffer
bool keys[1024];

// Shader Program
ShaderProgram planetsSheProg;
ShaderProgram sunSheProg;

// Deltatime
GLfloat deltaTime = 0.0f;	  // Time between current frame and previous frame
GLfloat previousFrame = 0.0f; // Time of last frame


// Planets
Sphere sun(2);
Sphere mercury(0.06);
Sphere venus(0.16);
Sphere earth(0.18);
Sphere moon(0.08);
Sphere mars(0.1);
Sphere jupiter(0.6);
Sphere saturn(0.45);
Sphere uranus(0.225);
Sphere neptune(0.225);
Sphere skyBox(100);

// Textures
Texture sunTexture("..\\textures\\sun.jpg");
Texture mercuryTexture("..\\textures\\mercury.jpg");
Texture venusTexture("..\\textures\\venus.jpg");
Texture earthTexture("..\\textures\\earth_daymap.jpg");
Texture moonTexture("..\\textures\\moon.jpg");
Texture marsTexture("..\\textures\\mars.jpg");
Texture jupiterTexture("..\\textures\\jupiter.jpg");
Texture saturnTexture("..\\textures\\saturn.jpg");
Texture uranusTexture("..\\textures\\uranus.jpg");
Texture neptuneTexture("..\\textures\\neptune.jpg");
Texture skyBoxTexture("..\\textures\\sky_box.jpg");

bool OpenGLWindow::createWindow(int width, int height, std::string windowTitle, bool showfullScreen)
{
	// Init GLFW
	if (!glfwInit())
	{
		std::cerr << "ERROR::GLFW initialisation failed!" << std::endl;
		glfwTerminate();
		return false;
	}

	// Set all the required options for GLFW
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	//glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);


	this->width = width;
	this->height = height;
	// Create a GLFWwindow object that we can use for GLFW's functions
	this->windowTitle = windowTitle;

	fullScreen = showfullScreen;
	if (showfullScreen)
	{
		GLFWmonitor* monitor = glfwGetPrimaryMonitor();
		const GLFWvidmode* vidMode = glfwGetVideoMode(monitor);
		if (vidMode != nullptr)
		{
			window = glfwCreateWindow(vidMode->width, vidMode->height, windowTitle.c_str(), monitor, nullptr);
		}
	}
	else
	{
		this->window = glfwCreateWindow(width, height, windowTitle.c_str(), nullptr, nullptr);
	}
	


	if (window == nullptr)
	{
		std::cerr << "ERROR::Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return false;
	}

	glfwMakeContextCurrent(this->window);
	//// Set the required callback functions
	glfwSetKeyCallback(this->window, this->key_callback);
	glfwSetScrollCallback(window, this->scroll_callback);
	glfwSetCursorPosCallback(window, this->mouse_callback);
	// Set this to true so GLEW knows to use a modern approach to retrieving function pointers and extensions
	glewExperimental = GL_TRUE;
	// Initialize GLEW to setup the OpenGL Function pointers
	if (glewInit() != GLEW_OK)
	{
		std::cerr << "ERROR::Failed to initialize GLEW" << std::endl;
		return false;
	}

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	// Define the viewport dimensions
	glfwGetFramebufferSize(window, &this->width, &this->height);
	glViewport(0, 0, this->width, this->height);
	return true;
}

void OpenGLWindow::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	std::cout << key << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);

	if (key >= 0 && key < 1024)
	{
		if (action == GLFW_PRESS)
			keys[key] = true;
		else if (action == GLFW_RELEASE)
			keys[key] = false;
	}

	//if (key == GLFW_KEY_0 && action == GLFW_PRESS)
	//{
	//	glViewport(0, 0, 800, 600);
	//	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	//}
}

void OpenGLWindow::doMovement()
{
	// Camera controls
	if (keys[GLFW_KEY_W])
		camera.processKeyboard(FORWARD, deltaTime);
	if (keys[GLFW_KEY_S])
		camera.processKeyboard(BACKWARD, deltaTime);
	if (keys[GLFW_KEY_A])
		camera.processKeyboard(LEFT, deltaTime);
	if (keys[GLFW_KEY_D])
		camera.processKeyboard(RIGHT, deltaTime);

	if (keys[GLFW_KEY_1])
		PlanetViewe = Planets::Mercury;
	if (keys[GLFW_KEY_2])
		PlanetViewe = Planets::Venus;
	if (keys[GLFW_KEY_3])
		PlanetViewe = Planets::Earth;
	if (keys[GLFW_KEY_4])
		PlanetViewe = Planets::Moon;
	if (keys[GLFW_KEY_5])
		PlanetViewe = Planets::Mars;
	if (keys[GLFW_KEY_6])
		PlanetViewe = Planets::Jupiter;
	if (keys[GLFW_KEY_7])
		PlanetViewe = Planets::Saturn;
	if (keys[GLFW_KEY_8])
		PlanetViewe = Planets::Uranus;	
	if (keys[GLFW_KEY_9])
		PlanetViewe = Planets::Neptune;
	if (keys[GLFW_KEY_0])
		PlanetViewe = Planets::Space;
}

void OpenGLWindow::showFPS()
{
	static double previousSeconds = 0.0;
	static int frameCount = 0;
	double deltaSeconds;
	// return number of seconds since GLFW started 
	double currentSeconds = glfwGetTime();

	deltaSeconds = currentSeconds - previousSeconds;

	//Limit test update 4 times per second
	if (deltaSeconds > 0.25)
	{
		previousSeconds = currentSeconds;
		double fps = (double)frameCount / deltaSeconds;
		double msPerFrame = 1000.0 / fps;

		std::ostringstream outs;
		outs << std::fixed
			<< windowTitle.c_str() << "   "
			<< "FPS: " << fps << "   "
			<< "Frame time: " << msPerFrame << " (ms)";
		glfwSetWindowTitle(window, outs.str().c_str());

		frameCount = 0;
	}

	frameCount++;
}

void OpenGLWindow::onWindowSizeChanged()
{
	int width, height;
	glfwGetWindowSize(this->window, &width, &height);
	projectionMatrix = glm::perspective(glm::radians(camera.getZoom()), float(width) / float(height), 0.5f, 1000.0f);
	glViewport(0, 0, width, height);
}

void OpenGLWindow::initializeScene()
{
	// Setup OpenGL options
	glEnable(GL_DEPTH_TEST);

	Shader vShader, fShader;
	vShader.loadShaderFromFile("..\\Shaders\\planet.vert", GL_VERTEX_SHADER);
	fShader.loadShaderFromFile("..\\Shaders\\planet.frag", GL_FRAGMENT_SHADER);

	if (!vShader.isShaderLoaded() || !fShader.isShaderLoaded())
	{
		return;
	}

	planetsSheProg.createProgram();
	planetsSheProg.addShaderToProgram(vShader);
	planetsSheProg.addShaderToProgram(fShader);
	vShader.deleteShader();
	fShader.deleteShader();

	if (!planetsSheProg.linkProgram())
	{
		return;
	}

	Shader vSunShader, fSunShader;
	vSunShader.loadShaderFromFile("..\\Shaders\\sun.vert", GL_VERTEX_SHADER);
	fSunShader.loadShaderFromFile("..\\Shaders\\sun.frag", GL_FRAGMENT_SHADER);

	if (!vSunShader.isShaderLoaded() || !fSunShader.isShaderLoaded())
	{
		std::cout << "==========" << std::endl;

		return;
	}

	sunSheProg.createProgram();
	sunSheProg.addShaderToProgram(vSunShader);
	sunSheProg.addShaderToProgram(fSunShader);
	vSunShader.deleteShader();
	fSunShader.deleteShader();

	if (!sunSheProg.linkProgram())
	{
		return;
	}


	// Create Buffers
	sun.generateBuffers();
	mercury.generateBuffers();
	venus.generateBuffers();
	earth.generateBuffers();
	moon.generateBuffers();
	mars.generateBuffers();
	jupiter.generateBuffers();
	saturn.generateBuffers();
	uranus.generateBuffers();
	neptune.generateBuffers();
	skyBox.generateBuffers();

	// Load textures
	sunTexture.fastLoad();
	mercuryTexture.fastLoad();
	venusTexture.fastLoad();
	earthTexture.fastLoad();
	moonTexture.fastLoad();
	marsTexture.fastLoad();
	jupiterTexture.fastLoad();
	saturnTexture.fastLoad();
	uranusTexture.fastLoad();
	neptuneTexture.fastLoad();
	skyBoxTexture.fastLoad();
}

void OpenGLWindow::renderScene()
{
	// Check if any events have been activiated (key pressed, mouse moved etc.) and call corresponding response functions
	glfwPollEvents();
	doMovement();
	showFPS();
	onWindowSizeChanged();

	// Clear the buffer
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glm::vec3 offset = glm::vec3(1.0f, 1.0f, 1.0f);
	switch (PlanetViewe)
	{
	case(Planets::Mercury):
		camera.setPosition(mercury.getOrigin() + offset);
		break;
	case(Planets::Venus):
		camera.setPosition(venus.getOrigin() + offset);
		break;	
	case(Planets::Earth):
		camera.setPosition(earth.getOrigin() + offset);
		break;	
	case(Planets::Moon):
		camera.setPosition(moon.getOrigin() + offset);
		break;	
	case(Planets::Mars):
		camera.setPosition(mars.getOrigin() + offset);
		break;
	case(Planets::Jupiter):
		camera.setPosition(jupiter.getOrigin() + offset);
		break;
	case(Planets::Saturn):
		camera.setPosition(saturn.getOrigin() + offset);
		break;
	case(Planets::Uranus):
		camera.setPosition(uranus.getOrigin() + offset);
		break;
	case(Planets::Neptune):
		camera.setPosition(neptune.getOrigin() + offset);
		break;
	case(Planets::Space):
	default:
		break;
	}

	sunSheProg.useProgram();
	GLint PVM_p = glGetUniformLocation(sunSheProg.getShaderProgramID(), "PVM");

	// SKY BOX
	glBindVertexArray(skyBox.getVAO());
	glm::mat4 PVM = getProjectionMatrix();
	glUniformMatrix4fv(PVM_p, 1, GL_FALSE, glm::value_ptr(PVM));
	skyBoxTexture.useTexture();
	skyBox.draw();
	glBindVertexArray(0);

	// SUN
	glBindVertexArray(sun.getVAO());
	sun.addRotation();
	PVM = getProjectionMatrix() * camera.getViewMatrix() * sun.getModelMatrix();
	glUniformMatrix4fv(PVM_p, 1, GL_FALSE, glm::value_ptr(PVM));
	sunTexture.useTexture();
	sun.draw();
	glBindVertexArray(0);

	planetsSheProg.useProgram();
	GLint PV_p = glGetUniformLocation(planetsSheProg.getShaderProgramID(), "PV");
	GLint model_p = glGetUniformLocation(planetsSheProg.getShaderProgramID(), "model");

	// MERCURY
	glBindVertexArray(mercury.getVAO());
	mercury.addRotation(2.5f, 0.8, 25);
	glm::mat4 PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(mercury.getModelMatrix()));
	mercuryTexture.useTexture();
	mercury.draw();
	glBindVertexArray(0);

	// VENUS
	glBindVertexArray(venus.getVAO());
	venus.addRotation(3.5f, 0.9, 28);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(venus.getModelMatrix()));
	venusTexture.useTexture();
	venus.draw();
	glBindVertexArray(0);

	// EARTH
	glBindVertexArray(earth.getVAO());
	earth.addRotation(4.5f, 0.8, 30);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(earth.getModelMatrix()));
	earthTexture.useTexture();
	earth.draw();
	glBindVertexArray(0);

	// MOON
	glBindVertexArray(moon.getVAO());
	moon.addRotation(0.5f, 4, 30, earth.getOrigin());
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(moon.getModelMatrix()));
	moonTexture.useTexture();
	moon.draw();
	glBindVertexArray(0);

	// MARS
	glBindVertexArray(mars.getVAO());
	mars.addRotation(5.5f, 0.7, 34);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(mars.getModelMatrix()));
	marsTexture.useTexture();
	mars.draw();
	glBindVertexArray(0);

	// JUPITER
	glBindVertexArray(jupiter.getVAO());
	jupiter.addRotation(7.0f, 0.6, 40);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(jupiter.getModelMatrix()));
	jupiterTexture.useTexture();
	jupiter.draw();
	glBindVertexArray(0);

	// SATURN
	glBindVertexArray(saturn.getVAO());
	saturn.addRotation(8.5f, 0.5, 35);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(saturn.getModelMatrix()));
	saturnTexture.useTexture();
	saturn.draw();
	glBindVertexArray(0);

	// URANUS
	glBindVertexArray(uranus.getVAO());
	uranus.addRotation(9.5f, 0.7, 40);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(uranus.getModelMatrix()));
	uranusTexture.useTexture();
	uranus.draw();
	glBindVertexArray(0);

	// NEPTUNE
	glBindVertexArray(neptune.getVAO());
	neptune.addRotation(10.0f, 0.85f, 40);
	PV = getProjectionMatrix() * camera.getViewMatrix();
	glUniformMatrix4fv(PV_p, 1, GL_FALSE, glm::value_ptr(PV));
	glUniformMatrix4fv(model_p, 1, GL_FALSE, glm::value_ptr(neptune.getModelMatrix()));
	neptuneTexture.useTexture();
	neptune.draw();
	glBindVertexArray(0);


	// Swap the screen buffers
	glfwSwapBuffers(this->window);
}

void OpenGLWindow::runApp()
{
	initializeScene();
	// Background sound
	audiere::AudioDevicePtr device = audiere::OpenDevice();
	audiere::OutputStreamPtr sound(OpenSound(device, "..\\sounds\\space.wav", false));
	sound->play();
	sound->setRepeat(true);
	sound->setVolume(1.0f);

	// Set window icon
	GLFWimage icons[1];
	icons[0].pixels = SOIL_load_image("..\\textures\\logo.jpg", &icons[0].width, &icons[0].height, 0, SOIL_LOAD_RGBA);
	glfwSetWindowIcon(window, 1, icons);
	SOIL_free_image_data(icons[0].pixels);

	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	// Game loop
	while (!glfwWindowShouldClose(this->window))
	{
		GLfloat currentFrame = glfwGetTime();
		deltaTime = currentFrame - previousFrame;
		previousFrame = currentFrame;
		renderScene();
	}

}

OpenGLWindow::~OpenGLWindow()
{
	// Terminate GLFW, clearing any resources allocated by GLFW.
	glfwTerminate();
}

void OpenGLWindow::mouse_callback(GLFWwindow* window, double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	GLfloat xoffset = xpos - lastX;
	GLfloat yoffset = lastY - ypos;  // Reversed since y-coordinates go from bottom to left

	lastX = xpos;
	lastY = ypos;

	camera.processMouseMovement(xoffset, yoffset);
}

void OpenGLWindow::scroll_callback(GLFWwindow* window, double xoffset, double yoffset)
{
	camera.processMouseScroll(yoffset);
}