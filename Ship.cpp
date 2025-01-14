#include "Ship.hpp"


Ship::Ship(const string& name, int size, int id, const Vector2i& startPos, char direction) :
	name(name), size(size), id(id), startPos(startPos), direction(direction) {


	shipSprite.setScale(0.9f, 0.9f); 
}


string Ship::getName() const
{
	return name; 
}

void Ship::setName(const string& nName)
{
	name = nName; 
}

int Ship::getSize() const
{
	return size; 
}

void Ship::setSize(int nSize)
{
	size = nSize; 
}

char Ship::getID() const
{
	return id; 
}

void Ship::setID(int nID)
{
	id = nID; 
}

Vector2i& Ship::getStartPos()
{
	return startPos; 
}

const Vector2i& Ship::getStartPos() const
{
	return startPos; 
}

void Ship::setStartPos(const Vector2i& nStartPos)
{
	startPos = nStartPos; 
}

char Ship::getDirection() const {
	return direction; 
}

void Ship::setDirection(char nDirection)
{
	direction = nDirection; 
}



void Ship::draw(RenderWindow& window)
{
	window.draw(shipSprite); 
}

void Ship::setShip(float x, float y)
{
	shipSprite.setPosition(x, y); 
}

void Ship::rotateShip()
{
	if (direction == 'V')
	{
		shipSprite.setRotation(90); 
	}

}


void Ship::loadSprite(const string& file)
{
	if (!texture.loadFromFile(file))
	{
		cout << "Coulnt load sprite for" << name << endl; 
	}
	else
	{
		shipSprite.setTexture(texture); 
		shipSprite.setScale(0.5f, 0.5f);
	}
}


const Sprite& Ship::getSprite() const
{
	return shipSprite; 
}