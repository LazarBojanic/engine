#include "Game.hpp"



Game* Game::instance;

Game::Game() {
	this->workingDirectory = std::filesystem::current_path().generic_string();
	this->width = (float)Application::getInstance()->getWindow()->getWidth();
	this->height = (float)Application::getInstance()->getWindow()->getHeight();
	this->centerX = width / 2;
	this->centerY = height / 2;
	this->keysSize = 1024;
	this->keys = new bool[this->keysSize];
	this->initKeys();
	this->camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 25.0f), this->width, this->height, 0.1f, 500.0f);
	this->soundEngine = std::make_shared<ma_engine>();
	if (ma_engine_init(nullptr, this->soundEngine.get()) != MA_SUCCESS) {
		std::cerr << "Failed to initialize audio engine." << std::endl;
	}
}

Game::~Game() {
	delete[] this->keys;
}

void Game::initKeys() {
	for (int i = 0; i < this->keysSize; i++) {
		this->keys[i] = false;
	}
}

void Game::generateCubeGrid(unsigned int gridSizeX, unsigned int gridSizeY, unsigned int gridSizeZ, float cubeSizeX, float cubeSizeY, float cubeSizeZ, float spacing) {
	auto cubeDrawData = ResourceManager::getInstance()->getDrawDataByName("cubeDrawData");
	for (unsigned int x = 0; x < gridSizeX; x++) {
		for (unsigned int y = 0; y < gridSizeY; y++) {
			for (unsigned int z = 0; z < gridSizeZ; z++) {
				unsigned int posX = x * static_cast<unsigned int>(cubeSizeX + spacing);
				unsigned int posY = y * static_cast<unsigned int>(cubeSizeY + spacing);
				unsigned int posZ = z * static_cast<unsigned int>(cubeSizeZ + spacing);
				std::string cubeName = "cube" + std::to_string(posX) + std::to_string(posY) + std::to_string(posZ);
				GameObjectManager::getInstance()->addGameObject("cubeGameObject", "cube", cubeDrawData,
													posX, posY, posZ,
													1.0f, 1.0f, 1.0f,
													10.0f, 10.0f, 10.0f,
													0.0f, 0.0f, 0.0f,
													0.0f, 0.0f,
													0.0f, false);
			}
		}
	}
}


Game* Game::getInstance() {
	if (!instance) {
		instance = new Game();
	}
	return instance;
}

void Game::initVariables() {
}

void Game::initResources() {
	std::shared_ptr<SkyboxGeometry> skyboxGeometry = std::make_shared<SkyboxGeometry>(true);
	std::shared_ptr<CubeGeometry> cubeGeometry = std::make_shared<CubeGeometry>(true);

	std::shared_ptr<Mesh> lightMesh = ResourceManager::getInstance()->addMesh("lightMesh", cubeGeometry);
	std::shared_ptr<Mesh> skyboxMesh = ResourceManager::getInstance()->addMesh("skyboxMesh", skyboxGeometry);
	std::shared_ptr<Mesh> cubeMesh = ResourceManager::getInstance()->addMesh("cubeMesh", cubeGeometry);

	std::vector<std::string> skyboxFacePaths;
	skyboxFacePaths.emplace_back("textures/skybox/right.jpg");
	skyboxFacePaths.emplace_back("textures/skybox/left.jpg");
	skyboxFacePaths.emplace_back("textures/skybox/top.jpg");
	skyboxFacePaths.emplace_back("textures/skybox/bottom.jpg");
	skyboxFacePaths.emplace_back("textures/skybox/front.jpg");
	skyboxFacePaths.emplace_back("textures/skybox/back.jpg");


	std::shared_ptr<CubeMap> skyboxCubeMap = ResourceManager::getInstance()->addCubeMap("skyboxCubeMap", skyboxFacePaths);

	std::shared_ptr<Shader> lightShader = ResourceManager::getInstance()->addShader("lightShader", "shaders/genericVertexShader.glsl", "shaders/lightFragmentShader.glsl", SHADING_TYPE::PHONG);
	std::shared_ptr<Shader> skyboxShader = ResourceManager::getInstance()->addShader("skyboxShader", "shaders/skyboxVertexShader.glsl", "shaders/skyboxFragmentShader.glsl", SHADING_TYPE::PHONG);
	

	std::shared_ptr<Light> light = std::make_shared<Light>("light", glm::vec4(1.0f), glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(0.5f));
	std::shared_ptr<LightDrawData> lightDrawData = ResourceManager::getInstance()->addLightDrawData("lightDrawData", light, lightMesh, lightShader);


	GameObjectManager::getInstance()->addLightGameObject("lightGameObject", "light", lightDrawData,
														 50.0f, 50.0f, 50.0f,
														 1.0f, 1.0f, 1.0f,
														 10.0f, 10.0f, 10.0f,
														 0.0f, 0.0f, 0.0f,
														 50.0f, 0.0f, 50.0f,
														 false);

	ResourceManager::getInstance()->addSkybox("skybox", 1.0, 1.0f, 1.0f, skyboxMesh, skyboxShader, skyboxCubeMap);

	std::shared_ptr<Material> cubeMaterial = ResourceManager::getInstance()->addMaterial("cubeMaterial", glm::vec4(0.0f, 1.0f, 1.0f, 1.0f), glm::vec3(0.5f), glm::vec3(0.5f), glm::vec3(0.5f), 32);

	std::shared_ptr<Shader> cubeShaderPhong = ResourceManager::getInstance()->addShader("cubeShader", "shaders/genericVertexShader.glsl", "shaders/genericPhongFragmentShader.glsl", SHADING_TYPE::PHONG);
	std::shared_ptr<Shader> cubeShaderPbr = ResourceManager::getInstance()->addShader("cubeShader", "shaders/genericVertexShader.glsl", "shaders/genericPbrFragmentShader.glsl", SHADING_TYPE::PBR);


	std::shared_ptr<Texture> cubeAlbedoTexture = std::make_shared<Texture>("cubeAlbedoTexture", "textures/granite/granite_albedo.png", TEXTURE_ALBEDO);
	std::shared_ptr<Texture> cubeDiffuseTexture = std::make_shared<Texture>("cubeDiffuseTexture", "textures/granite/granite_diffuse.png", TEXTURE_DIFFUSE);
	std::shared_ptr<Texture> cubeSpecularTexture = std::make_shared<Texture>("cubeSpecularTexture", "textures/granite/granite_specular.png", TEXTURE_SPECULAR);
	std::shared_ptr<Texture> cubeNormalTexture = std::make_shared<Texture>("cubeNormalTexture", "textures/granite/granite_normal.png", TEXTURE_NORMAL);
	std::shared_ptr<Texture> cubeHeightTexture = std::make_shared<Texture>("cubeHeightTexture", "textures/granite/granite_height.png", TEXTURE_HEIGHT);
	std::shared_ptr<Texture> cubeRoughnessTexture = std::make_shared<Texture>("cubeRoughnessTexture", "textures/granite/granite_roughness.png", TEXTURE_ROUGHNESS);
	std::shared_ptr<Texture> cubeShininessTexture = std::make_shared<Texture>("cubeShininessTexture", "textures/granite/granite_shininess.png", TEXTURE_SHININESS);
	std::shared_ptr<Texture> cubeMetalnessTexture = std::make_shared<Texture>("cubeMetalnessTexture", "textures/granite/granite_metalness.png", TEXTURE_METALNESS);
	std::shared_ptr<Texture> cubeAmbientOcclusionTexture = std::make_shared<Texture>("cubeAmbientOcclusionTexture", "textures/granite/granite_ao.png", TEXTURE_AMBIENT_OCCLUSION);


	std::shared_ptr<DrawData> cubeDrawData = ResourceManager::getInstance()->addDrawData(
		"cubeDrawData",
		cubeMesh,
		cubeMaterial,
		cubeAlbedoTexture,
		cubeDiffuseTexture,
		cubeSpecularTexture,
		cubeNormalTexture,
		cubeHeightTexture,
		cubeRoughnessTexture,
		cubeShininessTexture,
		cubeMetalnessTexture,
		cubeAmbientOcclusionTexture,
		cubeShaderPhong,
		cubeShaderPbr,
		true, true, true, true, true, true, true, true, true,
		SHADING_TYPE::PHONG
		);

	GameObjectManager::getInstance()->addGameObject("cubeGameObject", "cube", cubeDrawData,
	                                                0.0f, 0.0f, 0.0f,
	                                                1.0f, 1.0f, 1.0f,
	                                                10.0f, 10.0f, 10.0f,
	                                                0.0f, 0.0f, 0.0f,
	                                                0.0f, 0.0f,
	                                                0.0f, false);
	//this->generateCubeGrid(25, 2, 25, 10, 10, 10, 5);

	std::shared_ptr<ModelDrawData> backpackModelDrawData = ResourceManager::getInstance()->addModelDrawData("backpackModelDrawData", "models/backpack/backpack.obj", cubeMaterial,  cubeShaderPhong, cubeShaderPbr, SHADING_TYPE::PHONG );
	std::shared_ptr<ModelGameObject> backpackModelGameObject = GameObjectManager::getInstance()->addModelGameObject("backpackGameObject", "backpack", backpackModelDrawData,
		30, 30, 30,
		1, 1, 1,
		5, 5, 5,
		0, 180, 0,
		0, 0, 0,
		false
	);
}

void Game::start() {
	this->initVariables();
	this->initResources();
}

void Game::processInput(float dt) {
	if (this->keys[GLFW_KEY_W]) {
		//std::cout << "Pressed W" << std::endl;
		this->camera->processKeyboard(FORWARD, dt);
	}
	if (this->keys[GLFW_KEY_A]) {
		//std::cout << "Pressed A" << std::endl;
		this->camera->processKeyboard(LEFT, dt);
	}
	if (this->keys[GLFW_KEY_S]) {
		//std::cout << "Pressed S" << std::endl;
		this->camera->processKeyboard(BACKWARD, dt);
	}
	if (this->keys[GLFW_KEY_D]) {
		//std::cout << "Pressed D" << std::endl;
		this->camera->processKeyboard(RIGHT, dt);
	}
	if (this->keys[GLFW_KEY_SPACE]) {
		//std::cout << "Pressed SPACE" << std::endl;
		this->camera->processKeyboard(UP, dt);
	}
	if (this->keys[GLFW_KEY_LEFT_SHIFT]) {
		//std::cout << "Pressed LSHIFT" << std::endl;
		this->camera->processKeyboard(DOWN, dt);
	}
	if (this->keys[GLFW_KEY_F]) {
		//std::cout << "Pressed F" << std::endl;
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	if (this->keys[GLFW_KEY_B]) {
		glEnable(GL_CULL_FACE);
	}
	else {
		glDisable(GL_CULL_FACE);
	}
	glfwPollEvents();
}

void Game::update(float dt) {
	this->orbit(dt);

	this->t += dt;
}

void Game::orbit(float dt) {
	float r = 20.0f;

	auto light = GameObjectManager::getInstance()->getLightGameObjectByTag("light");

	// 1) Compute tangential speed in XZ plane
	glm::vec2 velXZ{ light->getSpeedX(), light->getSpeedZ() };
	float tangentialSpeed = glm::length(velXZ); // sqrt(vx^2 + vz^2)

	// 2) Derive angular speed
	float omega = tangentialSpeed / r;

	// 3) Advance orbit angle
	orbitAngle += omega * dt;

	// 4) Compute new position relative to orbit center
	float orbitX = orbitCenter.x + r * glm::cos(orbitAngle);
	float orbitZ = orbitCenter.z + r * glm::sin(orbitAngle);
	float orbitY = orbitCenter.y;  // Keep Y fixed, or modify if needed

	// 5) Apply position
	light->setPositionX(orbitX);
	light->setPositionY(orbitY);
	light->setPositionZ(orbitZ);
}

void Game::render() {
	Renderer::getInstance()->colorBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Renderer::getInstance()->drawAll(this->camera, true);
	Renderer::getInstance()->drawAllModels(this->camera, true);
	Renderer::getInstance()->drawAllLights(this->camera, true);
	Renderer::getInstance()->drawSkybox(this->camera);
	glfwSwapBuffers(Application::getInstance()->getWindow()->getGlfwWindow());
}

void Game::clear() {
}
