#include "Level.h"
Level::Level(sf::RenderWindow* hwnd, Input* in, GameState* gs,sf::View* v, World* w, TileManager* tm)
{
	window = hwnd;
	input = in;
	gameState = gs;
	view = v;
	world = w;	
	tileManager = tm;
	audioManager = new AudioManager();
	world->AddGameObject(zomb);

	world->AddGameObject(mario);

	mario.setInput(in);
	zomb.setInput(in);
	audioManager->addMusic("sfx/Cantina.ogg", "cantina");
	//audioManager.addMusic("sfx/hyrulefield.ogg", "hyrule");
	audioManager->addSound("sfx/smb_jump-super.wav", "jump");
	//audioManager.addSound("sfx/SMB_1-up.ogg", "up");
	//audioManager.addSound("sfx/getover.ogg", "getover");
	//audioManager.addSound("sfx/TP_Secret.ogg", "secret");

	audioManager->playMusicbyName("cantina");


	mario.setAudio(audioManager);

}

Level::~Level()
{
	//Making pointers null
	window = nullptr;
	input = nullptr;
	gameState = nullptr;
	view = nullptr;
	world = nullptr;
	tileManager = nullptr;
	if (audioManager != nullptr) {
		delete audioManager;
		audioManager = nullptr;
	}
}
	

void Level::handleInput(float dt)
{
	if (input->isKeyDown(sf::Keyboard::Escape))
	{
		exit(0);
	}
	if (input->isKeyDown(sf::Keyboard::Tab))
	{
		input->setKeyUp(sf::Keyboard::Tab);
		gameState->setCurrentState(State::TILEEDITOR);
	}

	zomb.handleInput(dt);
	mario.handleInput(dt);
}

// Update game objects
void Level::update(float dt)
{
	bg.update(dt);
	zomb.update(dt);
	mario.update(dt);
	//Move the view to follow the player
	view->setCenter(view->getCenter().x, 510);
	
	sf::Vector2f playerPosition = mario.getPosition();
	float newX = std::max(playerPosition.x, view->getSize().x / 2.0f);
	view->setCenter(newX, view->getCenter().y);
	window->setView(*view);


	if (mario.CollisionWithTag("Collectable"))
	{
		tileManager->RemoveCollectable();


	}
}

// Render level
void Level::render()
{
	window->draw(bg);

	if (gameState->getCurrentState() == State::LEVEL)
	{
		tileManager->render(false);
	}
	window->draw(zomb);

	window->draw(mario);


}


void Level::adjustViewToWindowSize(unsigned int width, unsigned int height) 
{
	sf::FloatRect visibleArea(0, 0, static_cast<float>(width), static_cast<float>(height));
	view->setSize(static_cast<float>(width), static_cast<float>(height));
	view->setCenter(static_cast<float>(width) / 2, static_cast<float>(height) / 2);
}