#include "engine/include/app.hpp"
#include "engine/include/entity.hpp"
#include "engine/include/camera.hpp"
using namespace Firesteel;

// Entities are basicly 3d models,
// that will be rendered in update function.
Entity box{glm::vec3(0, 0, -5), glm::vec3(-45, 0, 45)};
// Shader that will define how the box is drawn.
// Learn more: https://learnopengl.com/Getting-started/Shaders
Shader shader;
// Camera that will help with displaying box in perspective.
Camera camera{glm::vec3(0), glm::vec3(0, 0, -90)};

class ExampleApp : public App {
	// Runs after window and renderer initialization.
	virtual void onInitialize() override {
		// Loads model for entity from file.
		box.loadFromFile("res\\box.obj");
		// Initializes shader from vertex and fragment ones.
		shader = Shader("res/shader.vs", "res/shader.fs");
		// Get current camera vectors;
		camera.update();
	}
	
	// Runs each frame.
	virtual void onUpdate() override {
		// General routine (update window size and camera aspect).
		camera.aspect = window.aspect();
		glViewport(0, 0, static_cast<GLsizei>(window.getWidth()), static_cast<GLsizei>(window.getHeight()));
		window.clearBuffers();
		// Store camera's view and projection.
		// Learn more: https://learnopengl.com/Getting-started/Camera
		glm::mat4 projection = camera.getProjection(),
			view = camera.getView();
		// Enables and sets parameters of shader for box.
		shader.enable();
		shader.setMat4("projection", projection);
		shader.setMat4("view", view);
		// Draw the box itself.
		box.draw(&shader);
	}
	
	// Runs after window.close() is called or on window closing.
	virtual void onShutdown() override {
		// Clean up leftover resources.
		box.clearMeshes();
		shader.remove();
	}
};

int main() {
	// Initializes your application.
	return ExampleApp{}.start();
}