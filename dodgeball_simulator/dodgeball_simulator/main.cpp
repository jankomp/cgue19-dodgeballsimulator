#include <GL/glew.h>
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
#include "bloom.h"

using namespace physx;
using namespace std;



	unsigned int pingpongFBO[2];
	unsigned int pingpongColorbuffers[2];
	unsigned int colorBuffers[2];
	bool horizontal = true;
	bool first_iteration = true;
	unsigned int hdrFBO;
	bool bloom = true;
	bool bloomKeyPressed = false;
	float exposure = 1.0f;


//window settings
extern int SCR_WIDTH = 1920;
extern int SCR_HEIGHT = 1800;

//ball
Ball ball(glm::vec3(2.0f, 2.0f, 2.0f));
//bool ballcaught = false;
//bool firstCollision = false;

//player & camera
PlayerCharacter player(glm::vec3(0.0, 0.0, -4.5), &ball);
glm::vec3 camPos = glm::vec3(0.0f, 2.0f, -6.5f);
Camera camera(&player, camPos);

//enemies
enemy enemy_character(glm::vec3(0.0, 0.0, 6.0), &ball);
enemy enemy2_character(glm::vec3(-3.0, 0.0, 3.5), &ball);
enemy enemy3_character(glm::vec3(3.0, 0.0, 3.5), &ball);

//scores
int scoreEnemy = 0, scorePlayer = 0;

// timing
float lastFrame = 0.0f;


int main(void)
{



	window gameWindow;
	gameWindow.genWindow();
	
	//modelle laden
	Shader gameShader("shaders/model.vert", "shaders/model.frag");
	Shader textShader("shaders/text.vert", "shaders/text.frag");
	Shader bloomShader("shaders/bloom.vert", "shaders/bloom.frag");
	Shader bloom2Shader("shaders/bloom2.vert", "shaders/bloom2.frag");
	Shader blurShader("shaders/blur.vert", "shaders/blur.frag");
	Shader lightShader("shaders/bloom.vert", "shaders/light.frag");

	//modelle laden
	Model ballModel("modells/ball/ball.obj");
	Model turnhalle("modells/turnhalle/turnhalle.obj");
	Model spieler("modells/junge_rot/Lt_boy.obj");
	Model gegner("modells/junge_blau/Lt_boy.obj");
	
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	physics p(&player, &enemy_character, &enemy2_character, &enemy3_character);
	//p.initPhysics();
	p.setupScene();

	
	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


	/*glGenFramebuffers(1, &hdrFBO);
	glBindFramebuffer(GL_FRAMEBUFFER, hdrFBO);*/

	//load fonts
	TextRenderer title, text, spielstand, herzSchrift, ballSchrift;
	title.Load("fonts/arial.ttf", 140);
	text.Load("fonts/arial.ttf", 80);
	spielstand.Load("fonts/arial.ttf", 150);
	herzSchrift.Load("fonts/BonusHearts.ttf", 400);
	ballSchrift.Load("fonts/Balls.ttf", 68);

	//projection matrix
	glm::mat4 projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);

	//turnhalle
	glm::mat4 model_turnhalle = glm::mat4(1.0f);
	model_turnhalle = glm::rotate(model_turnhalle, glm::radians(-90.0f), glm::vec3(0.0f, 1.0f, 0.0f));

	Bloom toShine;
	//toShine.framebuffer();

	toShine.setLight();


	bloomShader.use();
	bloomShader.setInt("diffuseTexture", 0);
	blurShader.use();
	blurShader.setInt("image", 0);
	bloom2Shader.use();
	bloom2Shader.setInt("scene", 0);
	bloom2Shader.setInt("bloomBlur", 1);
	
	/* Loop until the user closes the window */
	while (gameWindow.run())
	{
		//settings = all the callbacks of mouse and keyboard
		settings s(&player, &camera);

		//gamewon, gamelost screens
		if (scoreEnemy == 3)
			s.setScreen(3);
		if (scorePlayer == 3)
			s.setScreen(4);

		// per-frame time logic
		// --------------------
		float currentFrame = glfwGetTime();
		float helpFloat = currentFrame - lastFrame;
		lastFrame = currentFrame;
		s.setDeltaTime(helpFloat);
		float fps = 1.0f / s.getDeltaTime();
		//cout << "fps: " << fps << endl;

		//advance the physx simulkation by one step
		p.stepPhysicSimulation(s.getDeltaTime());

		//if the ball is idle give it to whichever team deserves it
		p.dealBall(&player, &ball, &enemy_character, &enemy2_character, &enemy3_character);

		//simulate the shooting of the ball
		p.simulateBallShot(s.getDeltaTime(), &player, &ball, &enemy_character, &enemy2_character, &enemy3_character, &camera);

		// input
		s.processInput(gameWindow.getWindow());

		/* Render here */
		glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// view/projection transformations
		glm::mat4 view = camera.getWorldToViewMat();

		//startscreen
		if (s.getScreen() == 1) {
			
			glm::mat4 proj2 = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));
			textShader.use();
			textShader.setMat4("projection", proj2);

			title.RenderText(textShader, "DODGEBALLSIMULATOR", 120, ((float)SCR_HEIGHT / 2) + 100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
			text.RenderText(textShader, "press ENTER to start", ((float)SCR_WIDTH / 2) - 400, ((float)SCR_HEIGHT / 2) - 100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));

		}

		//gamescreen
		if (s.getScreen() == 2) {
			
			gameShader.use();
		
			glm::mat4 proj2 = glm::ortho(0.0f, static_cast<GLfloat>(SCR_WIDTH), 0.0f, static_cast<GLfloat>(SCR_HEIGHT));
			textShader.use();
			textShader.setMat4("projection", proj2);

			gameShader.use();
			gameShader.setMat4("projection", projection);
			gameShader.setMat4("view", view);

			// render the loaded model

			//turnhalle
			gameShader.setMat4("model", model_turnhalle);
			turnhalle.Draw(gameShader);


			//bloom element

			//toShine.render(&blurShader, &bloomShader, &lightShader, &bloom2Shader, projection, view);
			//bloomShader.setVec3("viewPos", camera.getPosition());
			//toShine.render2(&blurShader, &bloomShader, &lightShader, &bloom2Shader, projection, view);

			//glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
			//bloom2Shader.use();
			//glActiveTexture(GL_TEXTURE0);
			//toShine.bind1();
			//glActiveTexture(GL_TEXTURE1);
			//toShine.bind2();
			//bloom2Shader.setInt("bloom", bloom);
			//bloom2Shader.setFloat("exposure", exposure);
			//toShine.renderQuad();
		
		
			//ball
			if (!ball.caught) {
				glm::mat4 model_ball = glm::mat4(1.0f);
				PxVec3 ballPhysixPosition = p.getBallPos();
				glm::vec3 ballRenderPosition = glm::vec3(2.0f, 2.0f, 0.0f);
				ballRenderPosition.x = ballPhysixPosition.x; ballRenderPosition.y = ballPhysixPosition.y; ballRenderPosition.z = ballPhysixPosition.z;
				model_ball = glm::translate(model_ball, ballRenderPosition);
				model_ball = glm::scale(model_ball, glm::vec3(0.2f, 0.2f, 0.2f));
				gameShader.setMat4("model", model_ball);
				ballModel.Draw(gameShader);
			}

			/* update the PysX positions to the new model positions*/
			//spieler
			PxVec3 playerPos = PxVec3();
			playerPos.x = player.getPosition().x;	playerPos.y = player.getPosition().y;	playerPos.z = player.getPosition().z;
			p.setPlayerPos(playerPos);
			
			p.setEnemyPositions(PxVec3(enemy_character.getPosition().x, enemy_character.getPosition().y, enemy_character.getPosition().z),
								PxVec3(enemy2_character.getPosition().x, enemy2_character.getPosition().y, enemy2_character.getPosition().z),
								PxVec3(enemy3_character.getPosition().x, enemy3_character.getPosition().y, enemy3_character.getPosition().z));

			//draw player
			glm::mat4 model_spieler = glm::mat4(1.0f);
			model_spieler = glm::translate(model_spieler, player.getPosition());
			model_spieler = glm::scale(model_spieler, glm::vec3(0.3f, 0.3f, 0.3f));
			gameShader.setMat4("model", model_spieler);
			spieler.Draw(gameShader);

			//draw the enemies (if active)
			if (enemy_character.getActive()) {
				glm::mat4 model_gegner = glm::mat4(1.0f);
				enemy_character.move(s.getDeltaTime());
				model_gegner = glm::translate(model_gegner, enemy_character.getPosition());
				model_gegner = glm::rotate(model_gegner, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model_gegner = glm::scale(model_gegner, glm::vec3(0.3f, 0.3f, 0.3f));
				gameShader.setMat4("model", model_gegner);
				gegner.Draw(gameShader);
			}
			if (enemy2_character.getActive())
			{
				glm::mat4 model_gegner2 = glm::mat4(1.0f);
				enemy2_character.move(s.getDeltaTime());
				model_gegner2 = glm::translate(model_gegner2, enemy2_character.getPosition());
				model_gegner2 = glm::rotate(model_gegner2, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model_gegner2 = glm::scale(model_gegner2, glm::vec3(0.3f, 0.3f, 0.3f));
				gameShader.setMat4("model", model_gegner2);
				gegner.Draw(gameShader);
			}
			if (enemy3_character.getActive())
			{
				glm::mat4 model_gegner3 = glm::mat4(1.0f);
				enemy3_character.move(s.getDeltaTime());
				model_gegner3 = glm::translate(model_gegner3, enemy3_character.getPosition());
				model_gegner3 = glm::rotate(model_gegner3, glm::radians(180.0f), glm::vec3(0.0f, 1.0f, 0.0f));
				model_gegner3 = glm::scale(model_gegner3, glm::vec3(0.3f, 0.3f, 0.3f));
				gameShader.setMat4("model", model_gegner3);
				gegner.Draw(gameShader);

			}

			//draw hud
			if (s.headUpDisplay()) {

				switch (player.getLifes())
				{
				case 3:
					herzSchrift.RenderText(textShader, "o", 260, (float)SCR_HEIGHT - 240, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
				case 2:
					herzSchrift.RenderText(textShader, "o", 130, (float)SCR_HEIGHT - 240, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
				case 1:
					herzSchrift.RenderText(textShader, "o", 0, (float)SCR_HEIGHT - 240, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
				}

				std::string strScoreEnemy = std::to_string(scoreEnemy);
				std::string strScorePlayer = std::to_string(scorePlayer);

				spielstand.RenderText(textShader, strScorePlayer + ":" + strScoreEnemy, ((float)SCR_WIDTH / 2) - 100, (float)SCR_HEIGHT - 162, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
				if(player.gethasball())
					ballSchrift.RenderText(textShader, "Ball", (float)SCR_WIDTH - 150, (float)SCR_HEIGHT - 140, 1.0f, glm::vec3(1.0f, 1.0f, 1.0f));
			}

		}

		//lost screen
		if (s.getScreen() == 3) {
			title.RenderText(textShader, "YOU LOST!", 120, ((float)SCR_HEIGHT / 2) + 100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		//won screen
		if (s.getScreen() == 4) {
			title.RenderText(textShader, "YOU WON!", 120, ((float)SCR_HEIGHT / 2) + 100, 1.0f, glm::vec3(1.0f, 0.0f, 0.0f));
		}

		glEnable(GL_DEPTH_TEST);
		glDisable(GL_CULL_FACE);

		/* Swap front and back buffers */
		glfwSwapBuffers(gameWindow.getWindow());

		/* Poll for and process events */
		glfwPollEvents();
	}

	p.releaseScene();

	glfwTerminate();
	return 0;
}