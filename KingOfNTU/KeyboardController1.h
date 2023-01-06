#pragma once
#include "Game.h"
#include "ECS.h"
#include "Components.h"
#include "SDL_mixer.h"
#include <iostream>
using namespace std;


class KeyboardController1 :public Component
{
public:
	TransformComponent* transform;
	SpriteComponent* sprite;
	Mix_Chunk* gSound = NULL;
	void init() override
	{
		transform = &entity->getComponent<TransformComponent>();
		sprite = &entity->getComponent<SpriteComponent>();

		//if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
		//{
		//	printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
		//}
		////cout << gSound << endl;
		//gSound = Mix_LoadWAV("sound/laser-gun-81720.wav");
		//cout << gSound << endl;
		/*if (!gShoot) {
			cout << "Failed to load music or sound: " << Mix_GetError() << endl;
		}
		else cout << "music check" << endl;*/
	}

	void update() override
	{
		if (Game::event.type == SDL_KEYDOWN)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = -10;
				transform->up = true;
				sprite->animated = true;
				break;
			case SDLK_a:
				transform->velocity.x = -5;
				sprite->isright = false;
				sprite->animated = true;
				sprite->Play("Left");
				break;
			case SDLK_s:
				transform->velocity.y = 10;
				sprite->animated = true;
				break;
			case SDLK_d:
				transform->velocity.x = 5;
				sprite->isright = true;
				sprite->animated = true;
				sprite->Play("Right");
				break;
			case SDLK_t:
				/*if (!Mix_PlayChannel(-1, gSound, 0)) {
					cout << "Failed to load music or sound: " << Mix_GetError() << endl;
				}*/
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
				}
				//cout << gSound << endl;
				gSound = Mix_LoadWAV("./sound/laser-gun-81720.wav");
				if (!Mix_PlayChannel(-1, gSound, 0)) {
					cout << "Failed to load music or sound: " << Mix_GetError() << endl;
				}
				Mix_FreeChunk(gSound);
				gSound = NULL;
				Game::p1shoot = true;
				break;
			case SDLK_f:
				if(sprite->isright)transform->position.x += 300;
			else transform->position.x -= 300;
				break;
			default:
				break;
			}
		}

		if (Game::event.type == SDL_KEYUP)
		{
			switch (Game::event.key.keysym.sym)
			{
			case SDLK_w:
				transform->velocity.y = 3;
				transform->up = false;
				sprite->animated = false;
				break;
			case SDLK_a:
				transform->velocity.x = 0;
				sprite->animated = false;
				break;
			case SDLK_s:
				transform->velocity.y = 3;
				sprite->animated = false;
				break;
			case SDLK_d:
				transform->velocity.x = 0;
				sprite->animated = false;
				break;
			default:
				break;
			}
		}
	}



};