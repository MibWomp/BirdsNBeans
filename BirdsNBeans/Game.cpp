#include "Game.h"
#include "Sprite.h"
#include "TextureManager.h"
#include "Transform.h"
#include "Player.h"
#include "Timer.h"
#include "Tile.h"
#include "Seed.h"

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;
enum eventType {keyUp, keyDown, null};

//entities
Player player;
std::vector<Tile> tiles;
std::vector<std::unique_ptr<Seed>> seeds;

Game::Game() {}
Game::~Game() {}

Timer timer = Timer();
float seedSpawnTime;

SDL_Texture* backDrop;
SDL_Rect backDropSrc, backDropDest;

int score;

void Game::init(const char* title, int xPos, int yPos, int width, int height, bool fullScreen) {
	int flag = 0;
	std::cout << "Starting initilization" << std::endl;
	if (fullScreen) {
		flag = SDL_WINDOW_FULLSCREEN;
	}
	if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
		std::cout << "initialized." << std::endl;
		window = SDL_CreateWindow(title, xPos, yPos, width, height, false);
		if (window) {
			std::cout << "Window Created" << std::endl;
		}
		renderer = SDL_CreateRenderer(window, -1, 0); //SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
		if (renderer) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
			std::cout << "Renderer created" << std::endl;
		}
		isRunning = true;
	}
	else {
		std::cout << "entering isrunning false" << std::endl;
		isRunning = false;
	}

	player = Player("Assets/BirdsNBeans_BirdSpriteSheet.png");
	for (int i = 0; i < 15; i++) {
		tiles.emplace_back(Tile(i));
	}
	timer.start();
	seedSpawnTime = getRng(1, 2);
	backDrop = TextureManager::LoadTexture("Assets/BirdsNBeans_Background.png");
	backDropSrc.x = backDropSrc.y = backDropDest.x = backDropDest.y = 0;
	backDropSrc.w = backDropDest.w = 960;
	backDropSrc.h = backDropDest.h = 640;
	score = 0;
}

void Game::handleEvents() {
	SDL_PollEvent(&event);
	switch (event.type) {
	case SDL_QUIT:
		isRunning = false;
		break;
	default:
		break;

	}
	player.handleControls();

}

void Game::update() {
	if (seedSpawnTime <= timer.getTicks()/1000.f) { //SEED SPAWN
		seedSpawnTime = getRng(0, 5) + timer.getTicks()/1000.f;
		Seed *newSeed = new Seed(getIntRng(0,14)*64);
		std::unique_ptr<Seed> ptrSeed{ newSeed };
		seeds.emplace_back(std::move(ptrSeed));
	}
	for (auto& seed : seeds) { //SEEDS ITERATION
		seed->update();
		if (seed->spritePosition->position.y >= 576) { //OFF SCREEN CHECK
			seed->setInactive();
		}
		if (seed->spritePosition->position.y >= 512) { //COLLISION CHECK
			int tileIndex = seed->spritePosition->position.x / 64;
			if (!tiles[tileIndex].getDestroyed() && seed->checkCollision(tiles[tileIndex].destRect)) {
				seed->setInactive();
				tiles[tileIndex].setDestroyed();
			}
		}
	}
	seeds.erase(std::remove_if(std::begin(seeds), std::end(seeds), //ERASE INACTIVE SEEDS
		[](const std::unique_ptr<Seed>& mSeed) {
			return !mSeed->getActive();
		}),
		std::end(seeds));

	for (auto& tile : tiles) { //UPDATE TILES AND PLAYER
		tile.update();
	}

	player.update();
	if (player.wallCollision()) {
		player.spritePosition->position.x -= player.spritePosition->velocity.x;
		player.spritePosition->position.y -= player.spritePosition->velocity.y;
		player.spritePosition->position.y = 512;
		player.spritePosition->velocity.x = 0;
		player.spritePosition->velocity.y = 0;
		player.setIdle();
	}
	for (auto& tile : tiles) { //CHECK TILE COLLISION WITH THE PLAYER
		if (player.checkCollision(tile.collision)) {
			std::cout << "colliding" << std::endl;
			player.spritePosition->position.x -= player.spritePosition->velocity.x*2;
			player.spritePosition->position.y -= player.spritePosition->velocity.y;
			player.spritePosition->position.y = 512;
			player.spritePosition->velocity.x = 0;
			player.spritePosition->velocity.y = 0;
			player.setIdle();
			player.setAnimationReady(false);
		}
	}
	if (player.tongue.getActive()) { //CHECK TONGUE COLLISION WITH SEEDS
		for (auto& seed : seeds) {
			if (player.tongue.checkCollision(seed->collision)) {
				seed->setInactive();
				player.tongue.setHit(true);
				score++;
				std::cout << score << std::endl;
			}
		}
	}

}
void Game::render() { //call draw function
	SDL_RenderClear(renderer);
	TextureManager::Draw(backDrop, backDropSrc, backDropDest, 0, SDL_FLIP_NONE);
	player.tongue.draw();
	player.draw();
	for (Tile tile : tiles) {
		tile.draw();
	}
	for (auto& seed : seeds) {
		seed->draw();
	}
	SDL_RenderPresent(renderer);
	//std::cout<<"end render" << std::endl;
	player.setAnimationReady(true);
}
void Game::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);

	std::cout << "Cleaned." << std::endl;
	SDL_Quit();
}
Tile* getTile(int tileNum) {
	return &tiles[tileNum];
};

