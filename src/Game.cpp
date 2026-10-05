#include "Game.hpp"

Game* Game::instance;

Game::Game() {
	this->workingDirectory = std::filesystem::current_path().generic_string();
	this->width = static_cast<float>(Application::getInstance()->getWindow()->getWidth());
	this->height = static_cast<float>(Application::getInstance()->getWindow()->getHeight());
	this->centerX = width / 2.0f;
	this->centerY = height / 2.0f;
	this->initKeys();
	this->camera = std::make_shared<Camera>(glm::vec3(0.0f, 0.0f, 25.0f), this->width, this->height, 0.1f, 500.0f);
	this->soundEngine = std::make_shared<ma_engine>();
	if (ma_engine_init(nullptr, this->soundEngine.get()) != MA_SUCCESS) {
		std::cerr << "Failed to initialize audio engine." << std::endl;
	}
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& io = ImGui::GetIO();
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;
	io.ConfigFlags |= ImGuiConfigFlags_NavEnableGamepad;
	io.ConfigFlags |= ImGuiConfigFlags_DockingEnable;

	ImGui_ImplGlfw_InitForOpenGL(Application::getInstance()->getWindow()->getGlfwWindow(), true);
	ImGui_ImplOpenGL3_Init();
}

Game::~Game() {
	ma_engine_uninit(this->soundEngine.get());
	ImGui_ImplOpenGL3_Shutdown();
	ImGui_ImplGlfw_Shutdown();
	ImGui::DestroyContext();
}

void Game::initKeys() {
	this->keys.fill(false);
}

void Game::generateCubeGrid(unsigned int gridSizeX, unsigned int gridSizeY, unsigned int gridSizeZ, float cubeSizeX, float cubeSizeY, float cubeSizeZ, float spacing) {
	const std::shared_ptr<DrawData> cubeDrawData = ResourceManager::getInstance()->getDrawDataByName("cubeDrawData");
	if (cubeDrawData == nullptr) {
		return;
	}
	for (unsigned int x = 0; x < gridSizeX; x++) {
		for (unsigned int y = 0; y < gridSizeY; y++) {
			for (unsigned int z = 0; z < gridSizeZ; z++) {
				const float posX = static_cast<float>(x) * (cubeSizeX + spacing);
				const float posY = static_cast<float>(y) * (cubeSizeY + spacing);
				const float posZ = static_cast<float>(z) * (cubeSizeZ + spacing);
				GameObjectManager::getInstance()->addGameObject("cubeGameObject", "cube", cubeDrawData,
					posX, posY, posZ,
					1.0f, 1.0f, 1.0f,
					10.0f, 10.0f, 10.0f,
					0.0f, 0.0f, 0.0f,
					0.0f, 0.0f, 0.0f,
					false);
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

	std::shared_ptr<Light> light2 = std::make_shared<Light>("light2", glm::vec4(0.3f, 0.6f, 1.0f, 1.0f), glm::vec3(0.15f), glm::vec3(0.5f), glm::vec3(0.5f));
	std::shared_ptr<LightDrawData> lightDrawData2 = ResourceManager::getInstance()->addLightDrawData("lightDrawData2", light2, lightMesh, lightShader);
	GameObjectManager::getInstance()->addLightGameObject("lightGameObject2", "light2", lightDrawData2,
														 -25.0f, 30.0f, 30.0f,
														 1.0f, 1.0f, 1.0f,
														 6.0f, 6.0f, 6.0f,
														 0.0f, 0.0f, 0.0f,
														 0.0f, 0.0f, 0.0f,
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
		SHADING_TYPE::PBR
		);

	GameObjectManager::getInstance()->addGameObject("cubeGameObject", "cube", cubeDrawData,
	                                                0.0f, 0.0f, 0.0f,
	                                                1.0f, 1.0f, 1.0f,
	                                                10.0f, 10.0f, 10.0f,
	                                                0.0f, 0.0f, 0.0f,
	                                                0.0f, 0.0f, 0.0f,
	                                                false);
	this->generateCubeGrid(20, 2, 20, 10.0f, 10.0f, 10.0f, 5.0f);

	std::shared_ptr<ModelDrawData> backpackModelDrawData = ResourceManager::getInstance()->addModelDrawData("backpackModelDrawData", "models/backpack/backpack.obj", cubeMaterial, cubeShaderPhong, cubeShaderPbr, SHADING_TYPE::PBR);
	std::shared_ptr<ModelGameObject> backpackModelGameObject = GameObjectManager::getInstance()->addModelGameObject("backpackGameObject", "backpack", backpackModelDrawData,
		this->backpackInitialPosition.x, this->backpackInitialPosition.y, this->backpackInitialPosition.z,
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
	if (ImGui::GetCurrentContext() != nullptr) {
		ImGuiIO& io = ImGui::GetIO();
		if (io.WantCaptureKeyboard) {
			glfwPollEvents();
			return;
		}
	}
	if (!Application::getInstance()->getWindow()->isCursorCaptured()) {
		glfwPollEvents();
		return;
	}
	if (this->keys[GLFW_KEY_W]) {
		this->camera->processKeyboard(FORWARD, dt);
	}
	if (this->keys[GLFW_KEY_A]) {
		this->camera->processKeyboard(LEFT, dt);
	}
	if (this->keys[GLFW_KEY_S]) {
		this->camera->processKeyboard(BACKWARD, dt);
	}
	if (this->keys[GLFW_KEY_D]) {
		this->camera->processKeyboard(RIGHT, dt);
	}
	if (this->keys[GLFW_KEY_SPACE]) {
		this->camera->processKeyboard(UP, dt);
	}
	if (this->keys[GLFW_KEY_LEFT_SHIFT]) {
		this->camera->processKeyboard(DOWN, dt);
	}
	if (this->keys[GLFW_KEY_F]) {
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	else {
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	}
	glfwPollEvents();
}

void Game::update(float dt) {
	this->orbit(dt);

	this->t += dt;
}

void Game::orbit(float dt) {
	float r = 20.0f;


	std::shared_ptr<LightGameObject> light = GameObjectManager::getInstance()->getLightGameObjectByName("lightGameObject");
	if (light == nullptr) {
		return;
	}

	const glm::vec2 velXZ{ light->getSpeedX(), light->getSpeedZ() };
	const float tangentialSpeed = glm::length(velXZ);
	constexpr float orbitSpeed = 0.125f;
	const float omega = (tangentialSpeed / r) * orbitSpeed;

	orbitAngle += omega * dt;

	const float orbitX = orbitCenter.x + r * glm::cos(orbitAngle);
	const float orbitZ = orbitCenter.z + r * glm::sin(orbitAngle);
	const float orbitY = orbitCenter.y;

	light->getTransform().setPositionX(orbitX);
	light->getTransform().setPositionY(orbitY);
	light->getTransform().setPositionZ(orbitZ);
}

void Game::render() {
	ImGui_ImplOpenGL3_NewFrame();
	ImGui_ImplGlfw_NewFrame();
	ImGui::NewFrame();

	ImGuiDockNodeFlags dockspaceFlags = ImGuiDockNodeFlags_PassthruCentralNode;
	ImGui::DockSpaceOverViewport(0, ImGui::GetMainViewport(), dockspaceFlags);

	if (ImGui::Begin("Backpack Properties")) {
		if (ImGui::CollapsingHeader("Backpack", ImGuiTreeNodeFlags_DefaultOpen)) {
			std::shared_ptr<ModelGameObject> backpack = GameObjectManager::getInstance()->getModelGameObjectByTag("backpack");
			if (backpack) {
				float posX = backpack->getTransform().getPositionX();
				float posY = backpack->getTransform().getPositionY();
				float posZ = backpack->getTransform().getPositionZ();

				if (ImGui::SliderFloat("Position X", &posX, -100.0f, 100.0f, "%.2f")) {
					backpack->getTransform().setPositionX(posX);
				}
				if (ImGui::SliderFloat("Position Y", &posY, -100.0f, 100.0f, "%.2f")) {
					backpack->getTransform().setPositionY(posY);
				}
				if (ImGui::SliderFloat("Position Z", &posZ, -100.0f, 100.0f, "%.2f")) {
					backpack->getTransform().setPositionZ(posZ);
				}

				if (ImGui::Button("Reset Position")) {
					backpack->getTransform().setPosition(this->backpackInitialPosition);
				}

				std::shared_ptr<ModelDrawData> backpackDrawData = backpack->getModelDrawData();
				if (backpackDrawData != nullptr) {
					ImGui::SeparatorText("Shader");

					bool usePbr = backpackDrawData->getShadingType() == SHADING_TYPE::PBR;
					if (ImGui::Checkbox("PBR shader", &usePbr)) {
						backpackDrawData->setShadingType(usePbr ? SHADING_TYPE::PBR : SHADING_TYPE::PHONG);
					}

					std::shared_ptr<Material> material = backpackDrawData->getMaterial();
					if (material != nullptr) {
						ImGui::ColorEdit4("Base color", glm::value_ptr(material->albedo));
						ImGui::SliderFloat("Metallic", &material->metallic, 0.0f, 1.0f, "%.3f");
						ImGui::SliderFloat("Roughness", &material->roughness, 0.0f, 1.0f, "%.3f");
						ImGui::SliderFloat("AO", &material->ao, 0.0f, 1.0f, "%.3f");

						bool useMetalTex = backpackDrawData->getUseTextureMetalness();
						if (ImGui::Checkbox("Metalness texture", &useMetalTex)) {
							backpackDrawData->setUseTextureMetalness(useMetalTex);
						}
						bool useRoughTex = backpackDrawData->getUseTextureRoughness();
						if (ImGui::Checkbox("Roughness texture", &useRoughTex)) {
							backpackDrawData->setUseTextureRoughness(useRoughTex);
						}
						bool useAoTex = backpackDrawData->getUseTextureAmbientOcclusion();
						if (ImGui::Checkbox("AO texture", &useAoTex)) {
							backpackDrawData->setUseTextureAmbientOcclusion(useAoTex);
						}
						bool useNormalTex = backpackDrawData->getUseTextureNormal();
						if (ImGui::Checkbox("Normal map", &useNormalTex)) {
							backpackDrawData->setUseTextureNormal(useNormalTex);
						}
					}

					float exposure = Renderer::getInstance()->getExposure();
					if (ImGui::SliderFloat("Exposure", &exposure, 0.1f, 4.0f, "%.2f")) {
						Renderer::getInstance()->setExposure(exposure);
					}
				}
			} else {
				ImGui::TextDisabled("Backpack model object not found.");
			}
		}
	}
	ImGui::End();

	const Renderer::Stats& stats = Renderer::getInstance()->getStats();
	if (ImGui::Begin("Performance")) {
		ImGui::Text("Draw calls: %d", stats.drawCalls);
		ImGui::Text("Instances:  %d", stats.instances);
		ImGui::Text("Drawn:      %d", stats.drawn);
		ImGui::Text("Culled:     %d", stats.culled);
	}
	ImGui::End();

	Renderer::getInstance()->beginFrame(*this->camera);
	Renderer::getInstance()->colorBackground(glm::vec4(0.1f, 0.1f, 0.1f, 1.0f));
	Renderer::getInstance()->drawAll(*this->camera);
	Renderer::getInstance()->drawAllModels(*this->camera);
	Renderer::getInstance()->drawAllLights(*this->camera);
	Renderer::getInstance()->drawSkybox(*this->camera);
	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

	ImGuiIO& io = ImGui::GetIO();
	if (io.ConfigFlags & ImGuiConfigFlags_ViewportsEnable) {
		GLFWwindow* backupCurrentContext = glfwGetCurrentContext();
		ImGui::UpdatePlatformWindows();
		ImGui::RenderPlatformWindowsDefault();
		glfwMakeContextCurrent(backupCurrentContext);
	}

	glfwSwapBuffers(Application::getInstance()->getWindow()->getGlfwWindow());
}

void Game::clear() {
}
