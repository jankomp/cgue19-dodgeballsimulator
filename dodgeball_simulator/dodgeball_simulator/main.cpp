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
#include "CollisionCallback.h"

using namespace physx;
using namespace std;


//window settings
extern int SCR_WIDTH = 1920;
extern int SCR_HEIGHT = 1800;

//ball
Ball ball(glm::vec3(2.0f, 2.0f, 2.0f));
bool ballcaught = false;
bool firstCollision = false;
int countBallIdle = 0;

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

	//modelle laden
	Model ballModel("modells/ball/ball.obj");
	Model turnhalle("modells/turnhalle/turnhalle.obj");
	Model spieler("modells/junge_rot/Lt_boy.obj");
	Model gegner("modells/junge_blau/Lt_boy.obj");
	
	//glEnable(GL_CULL_FACE);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	initPhysics();
	
	//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	//Physx
	static PxDefaultErrorCallback gDefaultErrorCallback;
	static PxDefaultAllocator gDefaultAllocatorCallback;
	static PxFoundation* gFoundation = NULL;

	//Creating foundation for PhysX - vorl. ausgeklammert, weil foundation anscheinend schon existiert
	/*gFoundation = PxCreateFoundation(PX_PHYSICS_VERSION, gDefaultAllocatorCallback, gDefaultErrorCallback);
	if (!gFoundation)
		printf("PxCreateFoundation failed!");*/

	static PxPhysics* gPhysicsSDK = NULL;
	//Creating instance of PhysX SDK
	gPhysicsSDK = PxCreatePhysics(PX_PHYSICS_VERSION, *gFoundation, PxTolerancesScale());
	if (gPhysicsSDK == NULL)
	{
		cerr << "Error creating PhysX3 device, Exiting..." << endl;
		exit(1);
	}

	PxScene* gScene = NULL;
	//Creating scene
	PxSceneDesc sceneDesc(gPhysicsSDK->getTolerancesScale());
	sceneDesc.gravity = PxVec3(0.0f, -9.8f, 0.0f);
	sceneDesc.cpuDispatcher = PxDefaultCpuDispatcherCreate(1);
	sceneDesc.filterShader = PxDefaultSimulationFilterShader;
	// Set Instance of CollisionCallback as SimulationEventCallback of Scene
	CollisionCallback gContactReportCallback(&player, &enemy_character, &enemy2_character, &enemy3_character);
	sceneDesc.simulationEventCallback = &gContactReportCallback;
	//create the scene with the corresponding scene description
	gScene = gPhysicsSDK->createScene(sceneDesc);
		
	//Creating material
	PxMaterial* mMaterial =
		//static friction, dynamic friction, restitution
		gPhysicsSDK->createMaterial(0.5, 0.5, 0.5);

	//1-Creating static plane (floor)
	PxTransform floorPos = PxTransform(PxVec3(0.0f, 0.0f, 0.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* gymActor = gPhysicsSDK->createRigidStatic(floorPos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	//Creating walls
	PxTransform wall1Pos = PxTransform(PxVec3(0.0f, 0.0f, 27.0f), PxQuat(PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	gymActor = gPhysicsSDK->createRigidStatic(wall1Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	PxTransform wall2Pos = PxTransform(PxVec3(0.0f, 0.0f, -27.0f), PxQuat(-PxHalfPi, PxVec3(0.0f, 1.0f, 0.0f)));
	gymActor = gPhysicsSDK->createRigidStatic(wall2Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);
	
	PxTransform wall3Pos = PxTransform(PxVec3(-13.5f, 0.0f, 0.0f));
	gymActor = gPhysicsSDK->createRigidStatic(wall3Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	PxTransform wall4Pos = PxTransform(PxVec3(13.5f, 0.0f, 0.0f), PxQuat(-PxPi, PxVec3(0.0f, 1.0f, 0.0f)));
	gymActor = gPhysicsSDK->createRigidStatic(wall4Pos);
	gymActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*gymActor);

	//1-Creating static plane (roof)
	PxTransform roofPos = PxTransform(PxVec3(0.0f,  12.0f, 0.0f), PxQuat(-PxHalfPi, PxVec3(0.0f, 0.0f, 1.0f)));
	PxRigidStatic* roofActor = gPhysicsSDK->createRigidStatic(roofPos);
	roofActor->attachShape(*gPhysicsSDK->createShape(PxPlaneGeometry(), *mMaterial));
	gScene->addActor(*roofActor);

	//creating sphere (ball)
	PxTransform ballPos = PxTransform(PxVec3(2.0f, 2.0f, -1.0f));
	PxRigidDynamic* ballActor = gPhysicsSDK->createRigidDynamic(ballPos);
	PxShape* ballShape = gPhysicsSDK->createShape(PxSphereGeometry(0.2), *mMaterial);
		//set filter data for collision detection (to detect what object is hit)
	PxFilterData filterData; filterData.word0 = 0;	filterData.word1 = 0; ballShape->setSimulationFilterData(filterData);
	ballActor->attachShape(*ballShape);
	gScene->addActor(*ballActor);

	//creating box (player)
	PxVec3 playerPos = PxVec3(0.0);
	playerPos.x = player.getPosition().x;	playerPos.y = player.getPosition().y;	playerPos.z = player.getPosition().z;
	PxTransform playerPosition = PxTransform(playerPos);
	PxRigidDynamic* playerActor = gPhysicsSDK->createRigidDynamic(playerPosition);
	PxShape* playerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(2.0f, 4.0f, 2.0f)), *mMaterial);
	filterData.word0 = 2;	filterData.word1 = 0; playerShape->setSimulationFilterData(filterData);
	playerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	playerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	playerActor->attachShape(*playerShape);
	gScene->addActor(*playerActor);

	//creating boxes (enemys)
	PxVec3 enemy_characterPos = PxVec3(0.0);
	enemy_characterPos.x = enemy_character.getPosition().x;	enemy_characterPos.y = enemy_character.getPosition().y;	enemy_characterPos.z = enemy_character.getPosition().z;
	PxTransform enemy_characterPosition = PxTransform(enemy_characterPos);
	PxRigidDynamic* enemy_characterActor = gPhysicsSDK->createRigidDynamic(enemy_characterPosition);
	PxShape* triggerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(1.0f, 2.3f, 0.5f)), *mMaterial);
	filterData.word0 = 1;	filterData.word1 = 0; triggerShape->setSimulationFilterData(filterData);
	triggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	triggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	enemy_characterActor->attachShape(*triggerShape);
	gScene->addActor(*enemy_characterActor);

	PxVec3 enemy2_characterPos = PxVec3(0.0);
	enemy2_characterPos.x = enemy2_character.getPosition().x;	enemy2_characterPos.y = enemy2_character.getPosition().y;	enemy2_characterPos.z = enemy2_character.getPosition().z;
	PxTransform enemy2_characterPosition = PxTransform(enemy2_characterPos);
	PxRigidDynamic* enemy2_characterActor = gPhysicsSDK->createRigidDynamic(enemy2_characterPosition);
	triggerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(1.0f, 2.3f, 0.5f)), *mMaterial);
	filterData.word0 = 1;	filterData.word1 = 1; triggerShape->setSimulationFilterData(filterData);
	triggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	triggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	enemy2_characterActor->attachShape(*triggerShape);
	gScene->addActor(*enemy2_characterActor);

	PxVec3 enemy3_characterPos = PxVec3(0.0);
	enemy3_characterPos.x = enemy3_character.getPosition().x;	enemy3_characterPos.y = enemy3_character.getPosition().y;	enemy3_characterPos.z = enemy3_character.getPosition().z;
	PxTransform enemy3_characterPosition = PxTransform(enemy3_characterPos);
	PxRigidDynamic* enemy3_characterActor = gPhysicsSDK->createRigidDynamic(enemy3_characterPosition);
	triggerShape = gPhysicsSDK->createShape(PxBoxGeometry(PxVec3(1.0f, 2.3f, 0.5f)), *mMaterial);
	filterData.word0 = 1;	filterData.word1 = 2; triggerShape->setSimulationFilterData(filterData);
	triggerShape->setFlag(PxShapeFlag::eSIMULATION_SHAPE, false);
	triggerShape->setFlag(PxShapeFlag::eTRIGGER_SHAPE, true);
	enemy3_characterActor->attachShape(*triggerShape);
	gScene->addActor(*enemy3_characterActor);

	///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

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

		//advance the PhysX simulation by one step
		gScene->simulate(s.getDeltaTime());
		gScene->fetchResults(true);

		//if the ball is idle it goes to a player in whos field it currently is
		if (ballActor->isSleeping() && !ballcaught) {
			ballcaught = true;
			//detect in which field the ball is
			if (ballActor->getGlobalPose().p.z <= 0) {
				player.sethasball(true);
			}
			else {
				//give the ball to a randomly selected enemy
				bool enemyfound = false;
				ball.shot = true;
				while (!enemyfound) {
					int random = rand() % 3;
					if (random == 0 && enemy_character.getActive()) {
						enemy_character.sethasball(true); enemyfound = true;
					}
					else if (random == 1 && enemy2_character.getActive()) {
						enemy2_character.sethasball(true); enemyfound = true;
					}
					else if (random == 2 && enemy3_character.getActive()) {
						enemy3_character.sethasball(true); enemyfound = true;
					}
				}
			}
		}

		//ball is shot, when the player presses the left mouse-button or immediatly when an enemy gets the ball
		if (ball.isShot()) {
			if (player.gethasball()) {
				//start the ball a little bit in front of the player, so it doesn't collide with itself
				glm::vec3 playerPos = player.getPosition() + camera.getViewDirection();
				playerPos.y += 2.0;	
				ballActor->setGlobalPose(PxTransform(PxVec3(playerPos.x, playerPos.y, playerPos.z)));
				ballcaught = false;
				player.sethasball(false);
			}
			else if (enemy_character.getActive() && enemy_character.gethasball()) {
				//start the ball a little bit in front of the enemy, so it doesn't collide with itself
				glm::vec3 playerPos = player.getPosition(); playerPos.y += 2.0;
				glm::vec3 enemyPos = enemy_character.getPosition();	enemyPos.y += 2.0;
				glm::vec3 shotdirection = glm::normalize(playerPos - enemyPos); shotdirection *= 2.5;
				enemyPos += shotdirection;
				ballActor->setGlobalPose(PxTransform(PxVec3(enemyPos.x, enemyPos.y, enemyPos.z)));
				ballcaught = false;
				enemy_character.shootBall();
			}
			else if (enemy2_character.getActive() && enemy2_character.gethasball()) {
				//start the ball a little bit in front of the enemy, so it doesn't collide with itself
				glm::vec3 playerPos = player.getPosition(); playerPos.y += 2.0;
				glm::vec3 enemyPos = enemy2_character.getPosition();	enemyPos.y += 2.0;
				glm::vec3 shotdirection = glm::normalize(playerPos - enemyPos); shotdirection *= 2.5;
				enemyPos += shotdirection;
				ballActor->setGlobalPose(PxTransform(PxVec3(enemyPos.x, enemyPos.y, enemyPos.z)));
				ballcaught = false;
				enemy2_character.shootBall();
			}
			else if (enemy3_character.getActive() && enemy3_character.gethasball()) {
				//start the ball a little bit in front of the enemy, so it doesn't collide with itself
				glm::vec3 playerPos = player.getPosition(); playerPos.y += 2.0;
				glm::vec3 enemyPos = enemy3_character.getPosition();	enemyPos.y += 2.0;
				glm::vec3 shotdirection = glm::normalize(playerPos - enemyPos); shotdirection *= 2.5;
				enemyPos += shotdirection;
				ballActor->setGlobalPose(PxTransform(PxVec3(enemyPos.x, enemyPos.y, enemyPos.z)));
				ballcaught = false;
				enemy3_character.shootBall();
			}
			//selt first collision (global variable) to true -> next collision counts
			firstCollision = true;
		}

		//get from where ball i shot and add force to the ball as long as the character is shooting (120 loop iterations)
		if (player.shootingBall(s.getDeltaTime())) {
			glm::vec3 grafic = camera.getViewDirection();
			PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + 0.75; direction.z = grafic.z;
			direction *= 14.0;
			ballActor->addForce(direction);
		}else if (enemy_character.shootingBall(s.getDeltaTime())) {
			glm::vec3 playerPos = player.getPosition(); playerPos.y += 2.0;
			glm::vec3 enemyPos = enemy_character.getPosition();	enemyPos.y += 2.0;	enemyPos.z -= 2.0;
			glm::vec3 grafic = glm::normalize(playerPos - enemyPos);
			float aimCorrection = glm::length(playerPos - enemyPos) / 65.0;
			PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + aimCorrection; direction.z = grafic.z;			
			direction *= 26.5;
			ballActor->addForce(direction);
		}else if (enemy2_character.shootingBall(s.getDeltaTime())) {
			glm::vec3 playerPos = player.getPosition(); playerPos.y += 2.0;
			glm::vec3 enemyPos = enemy2_character.getPosition();
			enemyPos.y += 2.0;	enemyPos.z -= 2.0;
			glm::vec3 grafic = glm::normalize(playerPos - enemyPos);
			float aimCorrection = glm::length(playerPos - enemyPos) / 65.0;
			PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + aimCorrection; direction.z = grafic.z;			
			direction *= 26.5;
			ballActor->addForce(direction);
		} else if (enemy3_character.shootingBall(s.getDeltaTime())) {
			glm::vec3 playerPos = player.getPosition(); playerPos.y += 2.0;
			glm::vec3 enemyPos = enemy3_character.getPosition();
			enemyPos.y += 2.0;	enemyPos.z -= 2.0;
			glm::vec3 grafic = glm::normalize(playerPos - enemyPos);
			float aimCorrection = glm::length(playerPos - enemyPos) / 65.0;
			PxVec3 direction; direction.x = grafic.x; direction.y = grafic.y + aimCorrection; direction.z = grafic.z;
			direction *= 26.5;
			ballActor->addForce(direction);
		} else{
			//if nobody is shooting anymore clear the forces acting on the ball
			ballActor->clearForce();
			//if the ball is hardly moving it gets send to sleep so that it goes to a character
			if (ballActor->getLinearVelocity().magnitude() < 0.5) {
				if (countBallIdle++ > 60) {
					ballActor->putToSleep();
					countBallIdle = 0;
				}
			}
		}

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
		
			//ball
			if (!ballcaught) {
				glm::mat4 model_ball = glm::mat4(1.0f);
				PxVec3 ballPhysixPosition = ballActor->getGlobalPose().p;
				glm::vec3 ballRenderPosition = glm::vec3(2.0f, 2.0f, 0.0f);
				ballRenderPosition.x = ballPhysixPosition.x; ballRenderPosition.y = ballPhysixPosition.y; ballRenderPosition.z = ballPhysixPosition.z;
				model_ball = glm::translate(model_ball, ballRenderPosition);
				model_ball = glm::scale(model_ball, glm::vec3(0.2f, 0.2f, 0.2f));
				gameShader.setMat4("model", model_ball);
				ballModel.Draw(gameShader);
			}

			/* update the PysX positions to the new model positions*/
			//spieler
			playerPos.x = player.getPosition().x;	playerPos.y = player.getPosition().y;	playerPos.z = player.getPosition().z;
			playerActor->setGlobalPose(PxTransform(playerPos));
			//enemies
			enemy_characterActor->setGlobalPose(PxTransform(PxVec3(enemy_character.getPosition().x, enemy_character.getPosition().y, enemy_character.getPosition().z)));
			enemy2_characterActor->setGlobalPose(PxTransform(PxVec3(enemy2_character.getPosition().x, enemy2_character.getPosition().y, enemy2_character.getPosition().z)));
			enemy3_characterActor->setGlobalPose(PxTransform(PxVec3(enemy3_character.getPosition().x, enemy3_character.getPosition().y, enemy3_character.getPosition().z)));
			
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

	gScene->release();
	gPhysicsSDK->release();

	glfwTerminate();
	return 0;
}
