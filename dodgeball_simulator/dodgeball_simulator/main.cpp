//Quelle bloom: https://learnopengl.com/Advanced-Lighting/Bloom

#include <GL/glew.h>
#include <glm/glm.hpp>
#include <GLFW/glfw3.h>
#include <iostream>
#include <GL/GL.h>
#include <ft2build.h>

#include "window.h"
#include "settings.h"
#include "PlayerCharacter.h"
#include "physics.h"
#include "shader.h"
#include "model.h"
#include "Camera.h"
#include "text_renderer.h"
#include "enemy.h"
#include "ParticleGenerator.h"

static void APIENTRY DebugCallbackDefault(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam);
static std::string FormatDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, const char* msg);
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
unsigned int loadTexture(const char *path, bool gammaCorrection);
void renderQuad();
void renderCube();

using namespace physx;
using namespace std;


//window settings
extern int SCR_WIDTH;
extern int SCR_HEIGHT;


//bloom 
bool bloom = true;
bool bloomKeyPressed = false;
float exposure = 1.0f;

//scores
int scoreEnemy = 0, scorePlayer = 0;

// timing
float lastFrame = 0.0f;


//ball
Ball ball(glm::vec3(2.0f, 2.0f, 2.0f));
//bool ballcaught = false;
//bool firstCollision = false;

//player & camera
PlayerCharacter player(glm::vec3(0.0, 0.0, -4.5), &ball);
glm::vec3 camPos = glm::vec3(0.0f, 2.0f, -6.5f);
Camera camera(&player, camPos);

////enemies
enemy enemy_character(glm::vec3(0.0, 0.0, 6.0), &ball);
enemy enemy2_character(glm::vec3(-3.0, 0.0, 3.5), &ball);
enemy enemy3_character(glm::vec3(3.0, 0.0, 3.5), &ball);

//video texture
std::vector<glm::vec3> canvasVertices;
std::vector <GLushort> canvasIndices;
std::vector<glm::vec2> canvasUVcoords;

int width, height, nrChannels;
unsigned char *crowdData_00 = stbi_load("modells/crowd/crowd_0.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_01 = stbi_load("modells/crowd/crowd_b_1.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_02 = stbi_load("modells/crowd/crowd_b_2.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_03 = stbi_load("modells/crowd/crowd_b_3.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_04 = stbi_load("modells/crowd/crowd_b_4.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_05 = stbi_load("modells/crowd/crowd_b_5.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_06 = stbi_load("modells/crowd/crowd_b_6.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_07 = stbi_load("modells/crowd/crowd_r_1.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_08 = stbi_load("modells/crowd/crowd_r_2.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_09 = stbi_load("modells/crowd/crowd_r_3.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_10 = stbi_load("modells/crowd/crowd_r_4.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_11 = stbi_load("modells/crowd/crowd_r_5.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_12 = stbi_load("modells/crowd/crowd_r_6.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_13 = stbi_load("modells/crowd/crowd_r_7.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_14 = stbi_load("modells/crowd/crowd_r_8.jpg", &width, &height, &nrChannels, 0);
unsigned char *crowdData_15 = stbi_load("modells/crowd/crowd_r_9.jpg", &width, &height, &nrChannels, 0);
float frameCounter = 0;


unsigned char *getCrowdFrame(int score, float deltaTime) {
	if (score < 0) {
		frameCounter += deltaTime;
		if (frameCounter <= 0.08) {
			return crowdData_01;
		}else if (frameCounter <= 0.16) {
			return crowdData_02;
		}else if (frameCounter <= 0.24) {
			return crowdData_03;
		}else if (frameCounter <= 0.32) {
			return crowdData_04;
		}else if (frameCounter <= 0.4) {
			return crowdData_05;
		}else if (frameCounter <= 0.48) {
			return crowdData_06;
		}else if (frameCounter > 0.48) {
			frameCounter = 0.0;
			return crowdData_06;
		}
	}
	else if (score > 0) {
		frameCounter += deltaTime;
		if (frameCounter <= 0.08) {
			return crowdData_07;
		}else if (frameCounter <= 0.16) {
			return crowdData_08;
		}else if (frameCounter <= 0.24) {
			return crowdData_09;
		}else if (frameCounter <= 0.32) {
			return crowdData_10;
		}else if (frameCounter <= 0.4) {
			return crowdData_11;
		}else if (frameCounter <= 0.48) {
			return crowdData_12;
		}else if (frameCounter <= 0.56) {
			return crowdData_13;
		}else if (frameCounter <= 0.64) {
			return crowdData_14;
		}else if (frameCounter <= 0.72) {
			return crowdData_15;
		}else if (frameCounter > 0.72) {
			frameCounter = 0.0;
			return crowdData_15;
		}
	}
	else {
		return crowdData_00;
	}
}



int main(void)
{

	window gameWindow;
	gameWindow.genWindow(SCR_WIDTH,SCR_HEIGHT);

	glfwSetFramebufferSizeCallback(gameWindow.getWindow(), framebuffer_size_callback);


	// Debug callback
	if (glDebugMessageCallback != NULL) {
		glDebugMessageCallback(DebugCallbackDefault, NULL);
		glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
	}

	glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//load shader
	Shader gameShader("shaders/model.vert", "shaders/model.frag");
	Shader textShader("shaders/text.vert", "shaders/text.frag");
	Shader bloomShader("shaders/bloom.vert", "shaders/bloom.frag");
	Shader blurShader("shaders/blur.vert", "shaders/blur.frag");
	Shader bloom2Shader("shaders/bloom2.vert", "shaders/bloom2.frag");
	Shader particleShader("shaders/particle.vert", "shaders/particle.frag");

	//load modells
	Model ballModel("modells/ball/ball.obj");
	Model turnhalle("modells/turnhallemitloch/turnhalle.obj");
	Model spieler("modells/junge_rot/Lt_boy.obj");
	Model gegner("modells/junge_blau/Lt_boy.obj");

	//load texture
	unsigned int woodTexture = loadTexture("modells/turnhalle/wood.jpg", true); // note that we're loading the texture as an SRGB texture
	//loadLightmap
	int lmWidth, lmHeight, lmNrChannels;
	unsigned char *lightMap = stbi_load("modells/turnhallemitloch/lightmap.jpg", &lmWidth, &lmHeight, &lmNrChannels, 0);

	unsigned int lightMapTexture;
	glGenTextures(1, &lightMapTexture);
	
	//load fonts
	TextRenderer title, text, spielstand, herzSchrift, ballSchrift;
	title.Load("fonts/arial.ttf", SCR_WIDTH/ 15);
	text.Load("fonts/arial.ttf", SCR_WIDTH / 24);
	spielstand.Load("fonts/arial.ttf", SCR_WIDTH / 12);
	herzSchrift.Load("fonts/BonusHearts.ttf", SCR_WIDTH / 5);
	ballSchrift.Load("fonts/Balls.ttf", SCR_WIDTH / 25);

	//projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
	glm::mat4 proj2 = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));

	//turnhalle
	glm::mat4 model_turnhalle = glm::mat4(1.0f);
	model_turnhalle = glm::rotate(model_turnhalle, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	//settings = all the callbacks of mouse and keyboard
	settings s(&player, &camera);
	float helligkeit = s.getBrightness();
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	physics p(&player, &enemy_character, &enemy2_character, &enemy3_character);
	//p.initPhysics();
	p.setupScene();

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	unsigned int crowdTexture;
	glGenTextures(1, &crowdTexture);
	
	glm::mat4 videomodel = glm::mat4(1.0f);
	videomodel = glm::translate(videomodel, glm::vec3(-13.5f, 3.5f, 0.0));
	videomodel = glm::rotate(videomodel, glm::radians(-90.0f), glm::normalize(glm::vec3(1.0, 0.0, 0.0)));
	videomodel = glm::scale(videomodel, glm::vec3(0.01f, 5.0f, 2.5f));

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	// configure (floating point) framebuffers
	// ---------------------------------------
	unsigned int hdrFBO;
	glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
	// create 2 floating point color buffers (1 for normal rendering, other for brightness treshold values)
	unsigned int colorBuffers[2];
	glGenTextures(2, colorBuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindTexture(GL_TEXTURE_2D, colorBuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);  // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		// attach texture to framebuffer
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, GL_TEXTURE_2D, colorBuffers[i], 0);
	}
	// create and attach depth buffer (renderbuffer)
	unsigned int rboDepth;
	glGenRenderbuffers(1, &rboDepth);
	glBindRenderbuffer(GL_RENDERBUFFER, rboDepth);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, SCR_WIDTH, SCR_HEIGHT);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, rboDepth);
	// tell OpenGL which color attachments we'll use (of this framebuffer) for rendering 
	unsigned int attachments[2] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, attachments);
	// finally check if framebuffer is complete
	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
		std::cout << "Framebuffer not complete!" << std::endl;
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	// ping-pong-framebuffer for blurring
	unsigned int pingpongFBO[2];
	unsigned int pingpongColorbuffers[2];
	glGenFramebuffers(2, pingpongFBO);
	glGenTextures(2, pingpongColorbuffers);
	for (unsigned int i = 0; i < 2; i++)
	{
		glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[i]);
		glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[i]);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB16F, SCR_WIDTH, SCR_HEIGHT, 0, GL_RGB, GL_FLOAT, NULL);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE); // we clamp to the edge as the blur filter would otherwise sample repeated texture values!
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, pingpongColorbuffers[i], 0);
		// also check if framebuffers are complete (no need for depth buffer)
		if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE)
			std::cout << "Framebuffer not complete!" << std::endl;
	}

	// shader configuration
	// --------------------
	bloomShader.use();
	bloomShader.setInt("diffuseTexture", 0);
	bloomShader.setInt("lightMap", 1);
	bloomShader.setFloat("settingsBrightness", helligkeit);
	blurShader.use();
	blurShader.setInt("image", 0);
	bloom2Shader.use();
	bloom2Shader.setInt("scene", 0);
	bloom2Shader.setInt("bloomBlur", 1);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	glm::mat4 view;
	float helpFloat;

	ParticleGenerator particles;
	particles.setParticleSettings(particleShader, projection);
	
	/* Loop until the user closes the window */
	while (gameWindow.run())
	{
		//gamewon, gamelost screens
		if (scoreEnemy == 3)
			s.setScreen(3);
		if (scorePlayer == 3)
			s.setScreen(4);

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		helpFloat = currentFrame - lastFrame;
		lastFrame = currentFrame;
		s.setDeltaTime(helpFloat);
		float fps = 1.0f / s.getDeltaTime();
		//cout << "fps: " << fps << endl;

		// input
		s.processInput(gameWindow.getWindow());

		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view/projection transformations
		view = camera.getWorldToViewMat();
		textShader.use();
		textShader.setMat4("projection", proj2);

		//start and gamescreen
		if (s.getScreen() == 1 || s.getScreen() == 2) {

			//advance the physx simulkation by one step
			p.stepPhysicSimulation(s.getDeltaTime());

			//if the ball is idle give it to whichever team deserves it
			p.dealBall(&player, &ball, &enemy_character, &enemy2_character, &enemy3_character);

			//simulate the shooting of the ball
			p.simulateBallShot(s.getDeltaTime(), &player, &ball, &enemy_character, &enemy2_character, &enemy3_character, &camera);

			/* update the PysX positions to the new model positions*/
			//spieler
			PxVec3 playerPos = PxVec3();
			playerPos.x = player.getPosition().x;	playerPos.y = player.getPosition().y;	playerPos.z = player.getPosition().z;
			p.setPlayerPos(playerPos);

			p.setEnemyPositions(PxVec3(enemy_character.getPosition().x, enemy_character.getPosition().y, enemy_character.getPosition().z),
				PxVec3(enemy2_character.getPosition().x, enemy2_character.getPosition().y, enemy2_character.getPosition().z),
				PxVec3(enemy3_character.getPosition().x, enemy3_character.getPosition().y, enemy3_character.getPosition().z));

			// 1. render scene into floating point framebuffer
			// -----------------------------------------------
			glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			glm::mat4 model = glm::mat4(1.0f);
			bloomShader.use();
			bloomShader.setMat4("projection", projection);
			bloomShader.setMat4("view", view);
			glActiveTexture(GL_TEXTURE0);
			bloomShader.setVec3("viewPos", camera.getPosition());

			//turnhalle
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, lightMapTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lmWidth, lmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, lightMap);
			glGenerateMipmap(GL_TEXTURE_2D);
			bloomShader.setMat4("model", model_turnhalle);
			turnhalle.Draw(bloomShader);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);

			//draw the crowd
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, crowdTexture);
			
			unsigned char *crowdData = stbi_load("modells/crowd/crowd_0.jpg", &width, &height, &nrChannels, 0);
			crowdData = getCrowdFrame(scorePlayer - scoreEnemy, helpFloat);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_RGB, GL_UNSIGNED_BYTE, crowdData);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			bloomShader.setMat4("model", videomodel);
			bloomShader.setMat4("model", videomodel);
			renderCube();

			//ball
			if (!ball.caught) {
				glm::mat4 model_ball = glm::mat4(1.0f);
				PxVec3 ballPhysixPosition = p.getBallPos();
				glm::vec3 ballRenderPosition = glm::vec3(2.0f, 2.0f, 0.0f);
				ballRenderPosition.x = ballPhysixPosition.x; ballRenderPosition.y = ballPhysixPosition.y; ballRenderPosition.z = ballPhysixPosition.z;
				model_ball = glm::translate(model_ball, ballRenderPosition);
				model_ball = glm::scale(model_ball, glm::vec3(0.2f, 0.2f, 0.2f));
				bloomShader.setMat4("model", model_ball);
				ballModel.Draw(bloomShader);
			}

			//player
			glm::mat4 model_spieler = glm::mat4(1.0f);
			model_spieler = glm::translate(model_spieler, player.getPosition());
			model_spieler = glm::scale(model_spieler, glm::vec3(0.3f, 0.3f, 0.3f));
			bloomShader.setMat4("model", model_spieler);
			spieler.Draw(bloomShader);

			//draw the enemies (if active)
			if (enemy_character.getActive()) {
				glm::mat4 model_gegner = glm::mat4(1.0f);
				enemy_character.move(s.getDeltaTime());
				model_gegner = glm::translate(model_gegner, enemy_character.getPosition());
				model_gegner = glm::rotate(model_gegner, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model_gegner = glm::scale(model_gegner, glm::vec3(0.3f, 0.3f, 0.3f));
				bloomShader.setMat4("model", model_gegner);
				gegner.Draw(bloomShader);
			}
			if (enemy2_character.getActive())
			{
				glm::mat4 model_gegner2 = glm::mat4(1.0f);
				enemy2_character.move(s.getDeltaTime());
				model_gegner2 = glm::translate(model_gegner2, enemy2_character.getPosition());
				model_gegner2 = glm::rotate(model_gegner2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model_gegner2 = glm::scale(model_gegner2, glm::vec3(0.3f, 0.3f, 0.3f));
				bloomShader.setMat4("model", model_gegner2);
				gegner.Draw(bloomShader);
			}
			if (enemy3_character.getActive())
			{
				glm::mat4 model_gegner3 = glm::mat4(1.0f);
				enemy3_character.move(s.getDeltaTime());
				model_gegner3 = glm::translate(model_gegner3, enemy3_character.getPosition());
				model_gegner3 = glm::rotate(model_gegner3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model_gegner3 = glm::scale(model_gegner3, glm::vec3(0.3f, 0.3f, 0.3f));
				bloomShader.setMat4("model", model_gegner3);
				gegner.Draw(bloomShader);
			}

			if (s.getScreen() == 1) 
			{
				title.RenderText(textShader, "DODGEBALLSIMULATOR", (SCR_WIDTH / 8), ((float)SCR_HEIGHT / 2) + (SCR_WIDTH / 8), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
				text.RenderText(textShader, "press ENTER to start", ((float)SCR_WIDTH * 2 / 7), ((float)SCR_HEIGHT / 4) , 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			}

			//draw hud
			if (s.getScreen() == 2 && s.headUpDisplay())
			{

				switch (player.getLifes())
				{
				case 3:
					herzSchrift.RenderText(textShader, "o", SCR_WIDTH /5, (float)SCR_HEIGHT - (SCR_WIDTH/ 10), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
				case 2:
					herzSchrift.RenderText(textShader, "o", SCR_WIDTH / 10, (float)SCR_HEIGHT - (SCR_WIDTH / 10), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
				case 1:
					herzSchrift.RenderText(textShader, "o", 0, (float)SCR_HEIGHT - (SCR_WIDTH / 10), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
				}

				std::string strScoreEnemy = std::to_string(scoreEnemy);
				std::string strScorePlayer = std::to_string(scorePlayer);

				spielstand.RenderText(textShader, strScorePlayer + ":" + strScoreEnemy, ((float)SCR_WIDTH / 2) - (SCR_WIDTH / 16), (float)SCR_HEIGHT - (SCR_HEIGHT / 8), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
				if(player.gethasball())
					ballSchrift.RenderText(textShader, "Ball", (float)SCR_WIDTH - (SCR_WIDTH / 10), (float)SCR_HEIGHT - (SCR_HEIGHT / 8), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			}

			// 2. blur bright fragments with two-pass Gaussian Blur 
			// --------------------------------------------------
			bool horizontal = true, first_iteration = true;
			unsigned int amount = 10; 
			blurShader.use();
			for (unsigned int i = 0; i < amount; i++)
			{
				glBindFramebuffer(GL_FRAMEBUFFER, pingpongFBO[horizontal]);
				blurShader.setInt("horizontal", horizontal);
				glBindTexture(GL_TEXTURE_2D, first_iteration ? colorBuffers[1] : pingpongColorbuffers[!horizontal]);  // bind texture of other framebuffer (or scene if first iteration)
				renderQuad();
				horizontal = !horizontal;
				if (first_iteration)
					first_iteration = false;
			}
			glBindFramebuffer(GL_FRAMEBUFFER, 0);

			// 3. now render floating point color buffer to 2D quad and tonemap HDR colors to default framebuffer's (clamped) color range
			// --------------------------------------------------------------------------------------------------------------------------
			glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			bloom2Shader.use();
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, colorBuffers[0]);
			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, pingpongColorbuffers[!horizontal]);
			bloom2Shader.setInt("bloom", bloom);
			bloom2Shader.setFloat("exposure", exposure);
			renderQuad();
			
			glBindFramebuffer(GL_FRAMEBUFFER, 0);
		}

		//won screen
		if (s.getScreen() == 4 || s.getScreen() == 3) {

			gameShader.use();
			gameShader.setMat4("projection", projection);
			gameShader.setMat4("view", view);
			gameShader.setFloat("settingsBrightness", helligkeit);
			gameShader.setInt("lightMap", 1);

			gameShader.setMat4("model", model_turnhalle);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, lightMapTexture);
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, lmWidth, lmHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, lightMap);
			glGenerateMipmap(GL_TEXTURE_2D);
			
			turnhalle.Draw(gameShader);

			glActiveTexture(GL_TEXTURE1);
			glBindTexture(GL_TEXTURE_2D, 0);

			glm::mat4 model_spieler = glm::mat4(1.0f);
			model_spieler = glm::translate(model_spieler, player.getPosition());
			model_spieler = glm::rotate(model_spieler, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
			model_spieler = glm::scale(model_spieler, glm::vec3(0.3f, 0.3f, 0.3f));
			gameShader.setMat4("model", model_spieler);
			spieler.Draw(gameShader);

			//won
			if (s.getScreen() == 4) {
				//particle
				particles.render(helpFloat, particleShader, projection, view);

				//text
				title.RenderText(textShader, "YOU WON!", (SCR_WIDTH / 3), ((float)SCR_HEIGHT*4/5), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			}

			//lost
			if (s.getScreen() == 3) {
				title.RenderText(textShader, "YOU LOST!", (SCR_WIDTH / 3), ((float)SCR_HEIGHT * 4 / 5), 1.0f, glm::vec3(0.0f, 0.0f, 0.0f));
			}
		}

		glEnable(GL_DEPTH_TEST);
		glDepthFunc(GL_LESS);
		glDisable(GL_CULL_FACE);

		/* Swap front and back buffers */
		glfwSwapBuffers(gameWindow.getWindow());

		/* Poll for and process events */
		glfwPollEvents();

	}

	
	particles.del();

	p.releaseScene();

	glfwTerminate();
	return 0;
}

unsigned int loadTexture(char const * path, bool gammaCorrection)
{
	unsigned int textureID;
	glGenTextures(1, &textureID);

	int width, height, nrComponents;
	unsigned char *data = stbi_load(path, &width, &height, &nrComponents, 0);
	if (data)
	{
		GLenum internalFormat;
		GLenum dataFormat;
		if (nrComponents == 1)
		{
			internalFormat = dataFormat = GL_RED;
		}
		else if (nrComponents == 3)
		{
			internalFormat = gammaCorrection ? GL_SRGB : GL_RGB;
			dataFormat = GL_RGB;
		}
		else if (nrComponents == 4)
		{
			internalFormat = gammaCorrection ? GL_SRGB_ALPHA : GL_RGBA;
			dataFormat = GL_RGBA;
		}

		glBindTexture(GL_TEXTURE_2D, textureID);
		glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, dataFormat, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

		stbi_image_free(data);
	}
	else
	{
		std::cout << "Texture failed to load at path: " << path << std::endl;
		stbi_image_free(data);
	}

	return textureID;
}


static std::string FormatDebugOutput(GLenum source, GLenum type, GLuint id, GLenum severity, const char* msg) {
	std::stringstream stringStream;
	std::string sourceString;
	std::string typeString;
	std::string severityString;

	switch (source) {
	case GL_DEBUG_CATEGORY_API_ERROR_AMD:
	case GL_DEBUG_SOURCE_API: {
		sourceString = "API";
		break;
	}
	case GL_DEBUG_CATEGORY_APPLICATION_AMD:
	case GL_DEBUG_SOURCE_APPLICATION: {
		sourceString = "Application";
		break;
	}
	case GL_DEBUG_CATEGORY_WINDOW_SYSTEM_AMD:
	case GL_DEBUG_SOURCE_WINDOW_SYSTEM: {
		sourceString = "Window System";
		break;
	}
	case GL_DEBUG_CATEGORY_SHADER_COMPILER_AMD:
	case GL_DEBUG_SOURCE_SHADER_COMPILER: {
		sourceString = "Shader Compiler";
		break;
	}
	case GL_DEBUG_SOURCE_THIRD_PARTY: {
		sourceString = "Third Party";
		break;
	}
	case GL_DEBUG_CATEGORY_OTHER_AMD:
	case GL_DEBUG_SOURCE_OTHER: {
		sourceString = "Other";
		break;
	}
	default: {
		sourceString = "Unknown";
		break;
	}
	}

	switch (type) {
	case GL_DEBUG_TYPE_ERROR: {
		typeString = "Error";
		break;
	}
	case GL_DEBUG_CATEGORY_DEPRECATION_AMD:
	case GL_DEBUG_TYPE_DEPRECATED_BEHAVIOR: {
		typeString = "Deprecated Behavior";
		break;
	}
	case GL_DEBUG_CATEGORY_UNDEFINED_BEHAVIOR_AMD:
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR: {
		typeString = "Undefined Behavior";
		break;
	}
	case GL_DEBUG_TYPE_PORTABILITY_ARB: {
		typeString = "Portability";
		break;
	}
	case GL_DEBUG_CATEGORY_PERFORMANCE_AMD:
	case GL_DEBUG_TYPE_PERFORMANCE: {
		typeString = "Performance";
		break;
	}
	case GL_DEBUG_CATEGORY_OTHER_AMD:
	case GL_DEBUG_TYPE_OTHER: {
		typeString = "Other";
		break;
	}
	default: {
		typeString = "Unknown";
		break;
	}
	}

	switch (severity) {
	case GL_DEBUG_SEVERITY_HIGH: {
		severityString = "High";
		break;
	}
	case GL_DEBUG_SEVERITY_MEDIUM: {
		severityString = "Medium";
		break;
	}
	case GL_DEBUG_SEVERITY_LOW: {
		severityString = "Low";
		break;
	}
	default: {
		severityString = "Unknown";
		break;
	}
	}

	stringStream << "OpenGL Error: " << msg;
	stringStream << " [Source = " << sourceString;
	stringStream << ", Type = " << typeString;
	stringStream << ", Severity = " << severityString;
	stringStream << ", ID = " << id << "]";

	return stringStream.str();
}

static void APIENTRY DebugCallbackDefault(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const GLvoid* userParam) {
	if (id == 131185 || id == 131218) return; // ignore performance warnings from nvidia
	std::string error = FormatDebugOutput(source, type, id, severity, message);
	std::cout << error << std::endl;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}



// renderQuad() renders a 1x1 XY quad in NDC
// -----------------------------------------
unsigned int quadVAO = 0;
unsigned int quadVBO;
void renderQuad()
{
	if (quadVAO == 0)
	{
		float quadVertices[] = {
			// positions        // texture Coords
			-1.0f,  1.0f, 0.0f, 0.0f, 1.0f,
			-1.0f, -1.0f, 0.0f, 0.0f, 0.0f,
			 1.0f,  1.0f, 0.0f, 1.0f, 1.0f,
			 1.0f, -1.0f, 0.0f, 1.0f, 0.0f,
		};
		// setup plane VAO
		glGenVertexArrays(1, &quadVAO);
		glGenBuffers(1, &quadVBO);
		glBindVertexArray(quadVAO);
		glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(quadVertices), &quadVertices, GL_STATIC_DRAW);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
	}
	glBindVertexArray(quadVAO);
	glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	glBindVertexArray(0);
}

// renderCube() renders a 1x1 3D cube in NDC.
// -------------------------------------------------
unsigned int cubeVAO = 0;
unsigned int cubeVBO = 0;
void renderCube()
{
	// initialize (if necessary)
	if (cubeVAO == 0)
	{
		float vertices[] = {
			// back face
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 0.0f, // bottom-right         
			 1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 1.0f, 1.0f, // top-right
			-1.0f, -1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 0.0f, // bottom-left
			-1.0f,  1.0f, -1.0f,  0.0f,  0.0f, -1.0f, 0.0f, 1.0f, // top-left
			// front face
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			 1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 1.0f, 1.0f, // top-right
			-1.0f,  1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 1.0f, // top-left
			-1.0f, -1.0f,  1.0f,  0.0f,  0.0f,  1.0f, 0.0f, 0.0f, // bottom-left
			// left face
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			-1.0f,  1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f, -1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-left
			-1.0f, -1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f,  1.0f,  1.0f, -1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-right
			// right face
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 1.0f, // top-right         
			 1.0f, -1.0f, -1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 1.0f, // bottom-right
			 1.0f,  1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 1.0f, 0.0f, // top-left
			 1.0f, -1.0f,  1.0f,  1.0f,  0.0f,  0.0f, 0.0f, 0.0f, // bottom-left     
			// bottom face
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			 1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 1.0f, // top-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			 1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 1.0f, 0.0f, // bottom-left
			-1.0f, -1.0f,  1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 0.0f, // bottom-right
			-1.0f, -1.0f, -1.0f,  0.0f, -1.0f,  0.0f, 0.0f, 1.0f, // top-right
			// top face
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			 1.0f,  1.0f , 1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			 1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 1.0f, // top-right     
			 1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 1.0f, 0.0f, // bottom-right
			-1.0f,  1.0f, -1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 1.0f, // top-left
			-1.0f,  1.0f,  1.0f,  0.0f,  1.0f,  0.0f, 0.0f, 0.0f  // bottom-left        
		};
		glGenVertexArrays(1, &cubeVAO);
		glGenBuffers(1, &cubeVBO);
		// fill buffer
		glBindBuffer(GL_ARRAY_BUFFER, cubeVBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		// link vertex attributes
		glBindVertexArray(cubeVAO);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
		glBindBuffer(GL_ARRAY_BUFFER, 0);
		glBindVertexArray(0);
	}
	// render Cube
	glBindVertexArray(cubeVAO);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	glBindVertexArray(0);
}
