#include "Player.h"
#include "Level.h"
//--------------------------------------------------------------------------------------------
// c-tor
Player::Player(const std::string & name)
    :DynamicObject(name, { 0,0 } ),m_live(PLAYER_LIVE), m_shootSpecialOn(false),m_time(LEVEL_TIME),
    m_timeProtectedMode(PRITECTED_TIME),m_playerChangeMode(false), m_shootStupid(COLLISION_SHOOT_PLAYER), m_protectedMode(false)
{
    m_sprite.setTextureRect(sf::IntRect{ 0, 0, SIZE_OF_IMAGE, SIZE_OF_IMAGE });
}

//--------------------------------------------------------------------------------------------
// ����� �� ���� ����
int Player::getTime() const
{
    return m_time;
}

//--------------------------------------------------------------------------------------------
// ����� �� ������ ��� ���� �������
//������ ����� �� ���� �����
//����� ����� �� ��� �����
void Player::setDirection(sf::Keyboard::Key key, Level& level)
{
    switch (key)
    {
    case sf::Keyboard::Right:
        m_sprite.setScale(1, 1);
        m_direction = Direction::RIGHT;
        break;

    case sf::Keyboard::Left:
        m_sprite.setScale(-1, 1);
        m_direction = Direction::LEFT;
        break;

    case sf::Keyboard::Up:
        m_direction = Direction::UP;
        break;

    case sf::Keyboard::Down:
        m_direction = Direction::DOWN;
        break;

    case sf::Keyboard::Space:
        m_direction = Direction::STAY;
        break;

    case sf::Keyboard::W://����� �����
        level.isWall({ m_sprite.getPosition().x ,m_sprite.getPosition().y-SIZE_OF_IMAGE- EPSILON });
        break;

    case sf::Keyboard::S:// ���� �����
        level.isWall({ m_sprite.getPosition().x ,m_sprite.getPosition().y + SIZE_OF_IMAGE+ EPSILON });
            break;
    case sf::Keyboard::A://���� �����
        level.isWall({ m_sprite.getPosition().x - SIZE_OF_IMAGE - EPSILON,m_sprite.getPosition().y });
        break;
    case sf::Keyboard::D://���� �����
        level.isWall({ m_sprite.getPosition().x + SIZE_OF_IMAGE + EPSILON,m_sprite.getPosition().y });
        break;

    case sf::Keyboard::Key::Enter:
       if (m_direction != STAY)
        {
            if (!m_shootSpecialOn)
                m_shoot.emplace_back(Factory::createShoot("ShootStupid", { m_sprite.getPosition().x + EPSILON, m_sprite.getPosition().y + SIZE_OF_IMAGE / 2 - EPSILON }, dirToVector(m_direction)));
            else
                m_shoot.emplace_back(Factory::createShoot("ShootSpecial", { m_sprite.getPosition().x + EPSILON, m_sprite.getPosition().y + SIZE_OF_IMAGE / 2 - EPSILON }, dirToVector(m_direction)));
        }
        break;


    }
}

//--------------------------------------------------------------------------------------------
// ������� �� ����� ���� ����� ������� ����
void Player::setPrevPosition()
{
    m_sprite.setPosition(m_prevPosition);
    m_direction = Direction::STAY;
}

//--------------------------------------------------------------------------------------------
// ����� �� �����
sf::Vector2f Player::getDirection()
{
    return dirToVector(m_direction);
}

//--------------------------------------------------------------------------------------------
// ����� �� ���� �����
int Player::getLive()const
{
    return m_live;
}

//--------------------------------------------------------------------------------------------
// ����� ����
void Player::decLive()
{
    m_live--;
	m_sound.setBuffer(ResourcesManage::instance().getSound("boom2"));
	m_sound.play();
}

//--------------------------------------------------------------------------------------------
// ���� �� �� ����������
void Player::RemoveAllObserver()
{
    for (auto* obs: vec_pObserver_)
        RemoveObserver(obs);
}

//--------------------------------------------------------------------------------------------
// ���� �� ���������� ������
void Player::RegisterObserver(Observer* pObserver)
{
	vec_pObserver_.push_back(pObserver);
}

//--------------------------------------------------------------------------------------------
// ���� ������� ������
void Player::RemoveObserver(Observer* pObserver)
{
	vec_pObserver_.erase(remove(vec_pObserver_.begin(), vec_pObserver_.end(), pObserver), vec_pObserver_.end());
}

//--------------------------------------------------------------------------------------------
// �������� ������� �� ������ ����������
void Player::NotifyObserversWanted()
{
	vector<Observer*>::iterator iter;
	for (iter = vec_pObserver_.begin(); iter != vec_pObserver_.end(); ++iter)
	{
		(*iter)->Update();
	}
}

//--------------------------------------------------------------------------------------------
// �������� ������� �� ������ ����������
void Player::NotifyObserversSpecialPlayer()
{
	vector<Observer*>::iterator iter;
	for (iter = vec_pObserver_.begin(); iter != vec_pObserver_.end(); ++iter)
	{
		(*iter)->UpdateSpecialPlayr();
	}
}

//--------------------------------------------------------------------------------------------
//����� �� �����
void Player::move(float deltaTime)
{
    m_prevPosition = m_sprite.getPosition();
	checkPlayerMode();
	changeAnimation();
    m_sprite.move(dirToVector(m_direction) * 150.f * deltaTime);
}

//--------------------------------------------------------------------------------------------
//����� �� ������ �� �����
void Player::shoot(float deltaTime)
{
    for (int i=0;i<m_shoot.size();i++)
    {
        m_shoot[i]->move(deltaTime);
    }
}

//--------------------------------------------------------------------------------------------
//
void Player::drawShoot(sf::RenderWindow& window)
{
    for ( auto& shoot : m_shoot)
    {
        shoot->drawOnWindow(window);
    }
}

//--------------------------------------------------------------------------------------------
//����� ����� ��� ���� ����
bool Player::getShootOn()const
{
    return m_shootSpecialOn;
}

//--------------------------------------------------------------------------------------------
//���� ����
void Player::removeShoot()
{
    m_shoot.erase(m_shoot.begin() + m_indexShoot);
}

//--------------------------------------------------------------------------------------------
//����� ����� ����
void Player::restart()
{
    RemoveAllObserver();
    m_indexShoot = 0;
    m_live = 3;
}

//--------------------------------------------------------------------------------------------
//����� �� ������ ������� �� �����
sf::Vector2f Player::getFirstPosition()
{
    return m_firstLocation;
}

//--------------------------------------------------------------------------------------------
//����� ���� ����
void Player::setProtectedMode()
{
    m_clockProtectedMode.restart();
    m_protectedMode = true;
    m_sprite.setTexture(ResourcesManage::instance().getImgBoard("playerProtected"));
}

//--------------------------------------------------------------------------------------------
//����� ���� ���� ������
void Player::setShootSpecialOn()
{
    m_shootSpecialOn = true;
   m_clockProtectedMode.restart();
}

//--------------------------------------------------------------------------------------------
//����� �� ����� ���� ���� ��� 
bool Player::getPlayerChangeMode()const
{
    return m_playerChangeMode;
}

//--------------------------------------------------------------------------------------------
//����� �� ����� ���� ���� 
bool Player::getPlayerProtectedMode()const
{
    return m_protectedMode;
}

//--------------------------------------------------------------------------------------------
//����� �� ��� �����
void Player::setPlayerChangeMode(bool flag)
{
    m_playerChangeMode = flag;
}

//--------------------------------------------------------------------------------------------
//����� ������� ������
Observer* Player::getObserver(int i)
{
    return vec_pObserver_[i];
}

//--------------------------------------------------------------------------------------------
//����� ����� - �� ����� ����� ���� ����
void Player::subShootStupidCollition()
{
    if (!m_protectedMode)
    {
        m_sound.setBuffer(ResourcesManage::instance().getSound("boom2"));
        m_sound.play();
        m_shootStupid--;
        if (m_shootStupid <= 0)
        {
			decLive();
            m_shootStupid = COLLISION_SHOOT_PLAYER;
        }
    }
}

//--------------------------------------------------------------------------------------------
//���� �� ����� ���� ���� �� ���� ����
void Player::checkPlayerMode()
{
	if (!m_playerChangeMode)
	{
		if ((m_protectedMode || m_shootSpecialOn) && m_timeProtectedMode - m_clockProtectedMode.getElapsedTime().asSeconds() <= 0) {
			m_shootSpecialOn = false;
			m_protectedMode = false;
			m_sprite.setTexture(ResourcesManage::instance().getImgBoard("regularPlayer"));
		}
	}
}

//--------------------------------------------------------------------------------------------
//���� �� ��������
void Player::changeAnimation()
{
	static int x = 0;
	if (m_direction == RIGHT || m_direction == LEFT)
	{
		if (!x % 2 == 0)
			m_sprite.setTextureRect(sf::IntRect({ SIZE_OF_IMAGE * x,0,SIZE_OF_IMAGE - EPSILON ,SIZE_OF_IMAGE }));
		else
			m_sprite.setTextureRect(sf::IntRect({ SIZE_OF_IMAGE * x,0,SIZE_OF_IMAGE ,SIZE_OF_IMAGE }));
		x = (x + 1) % SIZE_IMAGE_ANIMATION;
	}
	else
		x = 0;
}

int Player::getShootNum() const
{
	return m_shootStupid;
}

