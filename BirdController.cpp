//
// Created by Morten Nobel-Jørgensen on 19/10/2017.
//

#include <SDL_events.h>
#include <iostream>
#include "BirdController.hpp"
#include "GameObject.hpp"
#include "SpriteComponent.hpp"
#include "PhysicsComponent.hpp"
#include "BirdGame.hpp"
#include "SpriteComponent.hpp"

BirdController::BirdController(GameObject *gameObject) : Component(gameObject) {
    // initiate bird physics
	auto phys = gameObject->getComponent<PhysicsComponent>();
	phys->setLinearVelocity(glm::vec2(1, 0));
}

bool BirdController::onKey(SDL_Event &event) {
	auto phys = gameObject->getComponent<PhysicsComponent>();
    if (event.type == SDL_KEYDOWN){
        std::cout << "some key pressed" << std::endl;
		switch (event.key.keysym.sym) {
			case SDLK_SPACE:
				std::cout << "space" << std::endl;
				phys->addImpulse(glm::vec2(0, 0.15));
				break;
		}
		
    } else if (event.type == SDL_KEYUP){
        std::cout << "some key released" << std::endl;
    }
    return false;
}

void BirdController::onCollisionStart(PhysicsComponent *comp) {
    
	auto gameObject = comp->getGameObject();

	if (gameObject->name.find("Wall") != std::string::npos) {
		std::cout << "bird collided with wall" << std::endl;
		BirdGame::instance->setGameState(GameState::GameOver);
	}

	if (gameObject->name == "coin") {
		std::cout << "bird collided with coin" << std::endl;
		auto spriteComponent = gameObject->getComponent<SpriteComponent>();
		gameObject->removeComponent(spriteComponent);
	}
}

void BirdController::onCollisionEnd(PhysicsComponent *comp) {

}


