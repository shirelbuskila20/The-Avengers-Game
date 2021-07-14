#include "Object.h"

//--------------------------------------------------------------------------------------------
// c-tor
Object::Object(const std::string& name,const sf::Vector2f& location) :m_location(location)
{
	m_sprite.setTexture(ResourcesManage::instance().getImgBoard(name));
	m_sprite.setPosition(m_location);
}

//--------------------------------------------------------------------------------------------
//����� �����
void Object::setPosition(sf::Vector2f location)
{
	m_firstLocation = location;
	m_sprite.setPosition(location);
}

//--------------------------------------------------------------------------------------------
// ����� �����
sf::Vector2f Object::getLocation()
{
	return m_sprite.getPosition();
}

//--------------------------------------------------------------------------------------------
//���� ����� ������
void Object::setFirstLocation()
{
	m_sprite.setPosition(m_firstLocation);
}

//--------------------------------------------------------------------------------------------
//���� ����
void Object::drawOnWindow(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

//--------------------------------------------------------------------------------------------
//���� ������
sf::FloatRect Object::getGlobalBoundsOfSprite()
{
	return m_sprite.getGlobalBounds();
}
