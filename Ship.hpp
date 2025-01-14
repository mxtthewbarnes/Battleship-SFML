#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <iostream> 

using std::string; 
using std::cout; 
using std::endl; 

using sf::Vector2i; 
using sf::RectangleShape; 
using sf::RenderWindow; 
using sf::Vector2f; 
using sf::Color; 
using sf::Sprite; 
using sf::Texture; 

class Ship {
private:
	string name; 
	
	int size; 
	int id; 
	char direction;

	Vector2i startPos; 

	Texture texture; 
	Sprite shipSprite; 


public: 

//								Constructor
//--------------------------------------------------------------------------------------------
	Ship(const string& name, int size, int id, const Vector2i& startPos, char direction); 


//							Getters & Setters
//-------------------------------------------------------------
	string getName() const; 
	void setName(const string& nName); 

	int getSize() const; 
	void setSize(int nSize); 

	char getID() const; 
	void setID(int nID); 

	const Vector2i& getStartPos() const; 
	Vector2i& getStartPos(); 
	
	void setStartPos(const Vector2i& newStartPos); 
	char getDirection() const; 
	void setDirection(char nDirection); 


//							SFML implementation
//------------------------------------------------------------------
	void draw(RenderWindow& window); 
	void setShip(float x, float y); 
	void rotateShip();



//							Loading sprites
//------------------------------------------------------------------
	void loadSprite(const string& file); 

	const Sprite& getSprite() const; 





	









};