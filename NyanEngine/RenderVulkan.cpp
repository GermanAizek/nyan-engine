#include "stdafx.h"
#include "RenderVulkan.h"
#include "EngineFunctions_Lua.h"

#include "Parser.h"
extern Settings settings_token;
extern GameSettings game_token;
extern SceneSettings scene_token;

// Vulkan API

size_t WIDTH = 1366;
size_t HEIGHT = 768;
const char * WINDOWNAME = "Nyan Engine";

const string MODEL_PATH = "content/models/test.obj";
const string TEXTURE_PATH = "content/textures/test.jpg";

// Init callbacks and camera
Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));
float lastX = WIDTH * 0.5;
float lastY = HEIGHT * 0.5;
bool keys[1024];
bool firstMouse = true;

float dtime = 0.f;
float lastFrame = 0.0f;

void Application::initWindow() {
	glfwInit();

	glfwWindowHint(GLFW_CLIENT_API, GLFW_NO_API);

	window = glfwCreateWindow(WIDTH, HEIGHT, WINDOWNAME, nullptr, nullptr);

	glfwSetWindowUserPointer(window, this);
	glfwSetWindowSizeCallback(window, Application::onWindowResized);

	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, MouseCallback);
	glfwSetScrollCallback(window, ScrollCallback);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

	// Pre script render
	/*
	script.Create();
	script.RegisterConstant<lua_CFunction>(Write, "Write");
	script.RegisterConstant<lua_CFunction>(CreateBox, "CreateBox");
	script.RegisterConstant<lua_CFunction>(SetColorSpace, "SetColorSpace");
	script.DoFile("render.lua");
	script.Close();
	*/
}

void show_vector(vector<int>&a)
{
	for (vector<int>::iterator it = a.begin(); it != a.end(); ++it)
		cout << *it;
}

#include "Engine.h"
#include <ctime>

void Application::loadModel() {
	tinyobj::attrib_t attrib;
	std::vector<tinyobj::shape_t> shapes;
	std::vector<tinyobj::material_t> materials;
	string err;

	// Scene render script
	script.Create();
	script.RegisterConstant<lua_CFunction>(Write, "Write");
	script.RegisterConstant<lua_CFunction>(CreateBox, "CreateBox");
	script.RegisterConstant<lua_CFunction>(CreatePerson, "CreatePerson");
	script.RegisterConstant<lua_CFunction>(SetColorSpace, "SetColorSpace");
	script.DoFile("render.lua");
	script.Close();

	if (Core::debugmode) {
		cout << "TESTING LOADING MODELS: 10 models\n";
		double start_time = clock(); // начальное время

		for (size_t i = 0; i < 10; ++i) {
			if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, MODEL_PATH.c_str())) throw std::runtime_error(err);
		}

		double end_time = clock(); // конечное время
		cout << "TIME Load Object " << (double)(end_time - start_time) / (double)1000.0 << " sec\n"; // искомое время
		cout << "INFO MODEL:\n";
		for (size_t i = 0; i < 5/*attrib.vertices.size()*/; ++i) cout << "Vertices[" << i << "] = " << attrib.vertices[i] << "\n";
		//auto a = &tinyobj::attrib_t::vertices;
		//show_vector(a);
	}
	else {
		if (!tinyobj::LoadObj(&attrib, &shapes, &materials, &err, MODEL_PATH.c_str())) throw std::runtime_error(err);
	}

	std::unordered_map<Vertex, uint32_t> uniqueVertices = {};

	for (const auto& shape : shapes) {
		for (const auto& index : shape.mesh.indices) {
			Vertex vertex = {};

			vertex.pos = {
				attrib.vertices[3 * index.vertex_index + 0],
				attrib.vertices[3 * index.vertex_index + 1],
				attrib.vertices[3 * index.vertex_index + 2]
			};

			vertex.texCoord = {
				attrib.texcoords[2 * index.texcoord_index + 0],
				1.0f - attrib.texcoords[2 * index.texcoord_index + 1]
			};

			vertex.color = { 1.0f, 1.0f, 1.0f };

			if (uniqueVertices.count(vertex) == 0) {
				uniqueVertices[vertex] = static_cast<uint32_t>(vertices.size());
				vertices.push_back(vertex);
			}

			indices.push_back(uniqueVertices[vertex]);
		}
	}
}

void Application::createTextureImage() {
	int texWidth, texHeight, texChannels;
	stbi_uc* pixels = stbi_load(TEXTURE_PATH.c_str(), &texWidth, &texHeight, &texChannels, STBI_rgb_alpha);
	VkDeviceSize imageSize = texWidth * texHeight * 4;

	if (!pixels) {
		throw std::runtime_error("failed to load texture image!");
	}

	VkBuffer stagingBuffer;
	VkDeviceMemory stagingBufferMemory;
	createBuffer(imageSize, VK_BUFFER_USAGE_TRANSFER_SRC_BIT, VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT | VK_MEMORY_PROPERTY_HOST_COHERENT_BIT, stagingBuffer, stagingBufferMemory);

	void* data;
	vkMapMemory(device, stagingBufferMemory, 0, imageSize, 0, &data);
	memcpy(data, pixels, static_cast<size_t>(imageSize));
	vkUnmapMemory(device, stagingBufferMemory);

	stbi_image_free(pixels);

	createImage(texWidth, texHeight, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_TILING_OPTIMAL, VK_IMAGE_USAGE_TRANSFER_DST_BIT | VK_IMAGE_USAGE_SAMPLED_BIT, VK_MEMORY_PROPERTY_DEVICE_LOCAL_BIT, textureImage, textureImageMemory);

	transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_UNDEFINED, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL);
	copyBufferToImage(stagingBuffer, textureImage, static_cast<uint32_t>(texWidth), static_cast<uint32_t>(texHeight));
	transitionImageLayout(textureImage, VK_FORMAT_R8G8B8A8_UNORM, VK_IMAGE_LAYOUT_TRANSFER_DST_OPTIMAL, VK_IMAGE_LAYOUT_SHADER_READ_ONLY_OPTIMAL);

	vkDestroyBuffer(device, stagingBuffer, nullptr);
	vkFreeMemory(device, stagingBufferMemory, nullptr);
}

float look_x = 0;
float look_y = 0;
float look_z = 0;
float rot_x = 0;
float rot_y = 0;
float rot_z = 0;

void Application::updateUniformBuffer() {


	static auto startTime = std::chrono::high_resolution_clock::now();

	auto currentTime = std::chrono::high_resolution_clock::now();
	float time = std::chrono::duration<float, std::chrono::seconds::period>(currentTime - startTime).count();
	
	if (glfwGetKey(window, GLFW_KEY_A)) look_x += 0.01;
	if (glfwGetKey(window, GLFW_KEY_D)) look_x -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_S)) look_y += 0.01;
	if (glfwGetKey(window, GLFW_KEY_W)) look_y -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_R)) look_z += 0.01;
	if (glfwGetKey(window, GLFW_KEY_F)) look_z -= 0.01;
	if (glfwGetKey(window, GLFW_KEY_UP)) rot_x += 2;
	if (glfwGetKey(window, GLFW_KEY_DOWN)) rot_x -= 2;
	if (glfwGetKey(window, GLFW_KEY_LEFT)) rot_y += 2;
	if (glfwGetKey(window, GLFW_KEY_RIGHT)) rot_y -= 2;
	

	float curFrame = glfwGetTime();
	dtime = curFrame - lastFrame;
	lastFrame = curFrame;

	DoMovement();
	//if (glfwGetKey(window, GLFW_KEY_W) || keys[GLFW_KEY_UP]) camera.ProcessKeyboard(FORWARD, dtime);

	glm::mat4 projection = glm::perspective(camera.GetZoom(), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 1000.0f);
	glm::mat4 view = camera.GetViewMatrix();

	//for (int i = 0; i < 10)

	//double xpos, ypos;

	//glfwGetCursorPos(window, &xpos, &ypos);
	//if (xpos > 0) rot_x += 0.001;
	//if (xpos < 0) rot_x -= 0.001;

	UniformBufferObject* ubo = new UniformBufferObject[10];
	//UniformBufferObject* ubo[/*scene_token.count_obj*/] = new UniformBufferObject{};

	for (size_t i = 0; i < scene_token.count_obj; i++) {
		//ubo[i].model = glm::rotate(glm::mat4(1.0f), glm::radians(10.0f), glm::vec3(rot_x + 1.0f, rot_y, rot_z));
		//ubo[i].view = glm::lookAt(glm::vec3(look_x + 0.0f, look_y + 10.0f, look_z + 0.0f), glm::vec3(0.0f, 10.0f, 0.0f), glm::vec3(0.0f, 5.0f, 0.0f));
		//ubo.view = glm::rotate(glm::mat4(1.0f), time * glm::radians(10.0f), glm::vec3(0.0f, 1.0f, 0.0f));

		ubo[i].model = glm::translate(glm::mat4(), scene_token.coordinatesObj[i]);
		ubo[i].proj = glm::perspective(glm::radians(45.0f), swapChainExtent.width / (float)swapChainExtent.height, 0.1f, 1000.0f); // 4 parametr - lenght draw
		ubo[i].proj[1][1] *= -1;
	}

	void* data;

	for (size_t i = 0; i < scene_token.count_obj; i++) {
		vkMapMemory(device, uniformBufferMemory, 0, sizeof(ubo[i]), 0, &data);
		memcpy(data, &ubo[i], sizeof(ubo[i]));
	}
	vkUnmapMemory(device, uniformBufferMemory);
}

size_t createApp(size_t WIDTH, size_t HEIGHT, const char * WINDOWNAME) {
	::WIDTH = WIDTH;
	::HEIGHT = HEIGHT;
	::WINDOWNAME = WINDOWNAME;

	Application app;
	cout << "Application created!\n";

	try {
		app.run();
	}
	catch (const runtime_error& e) {
		cerr << e.what() << "\n";
		return EXIT_FAILURE;
	}

	return EXIT_SUCCESS;
}

void DoMovement() {
	if (keys[GLFW_KEY_W] || keys[GLFW_KEY_UP]) camera.ProcessKeyboard(FORWARD, dtime);
	if (keys[GLFW_KEY_S] || keys[GLFW_KEY_DOWN]) camera.ProcessKeyboard(BACKWARD, dtime);
	if (keys[GLFW_KEY_A] || keys[GLFW_KEY_LEFT]) camera.ProcessKeyboard(LEFT, dtime);
	if (keys[GLFW_KEY_D] || keys[GLFW_KEY_RIGHT]) camera.ProcessKeyboard(RIGHT, dtime);
}

void KeyCallback(GLFWwindow *window, int key, int scancode, int action, int mode) {
	if (GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		//glfwSetWindow
	}

	if (key >= 0 && key < 1024) {
		if (GLFW_PRESS == action) keys[key] = true;
		else if (GLFW_RELEASE == action) keys[key] = false;
	}
}

void MouseCallback(GLFWwindow *window, double xPos, double yPos) {
	if (firstMouse) {
		lastX = xPos;
		lastY = yPos;
		firstMouse = false;
	}

	float xOffset = xPos - lastX;
	float yOffset = lastY - yPos;

	lastX = xPos;
	lastY = yPos;

	camera.ProcessMouseMovement(xOffset, yOffset);
}

void ScrollCallback(GLFWwindow *window, double xOffset, double yOffset) {
	camera.ProcessMouseScroll(yOffset);
}