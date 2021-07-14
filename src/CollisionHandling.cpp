#include "CollisionHandling.h"

namespace 
{
//--------------------------------------------------------------------------------------------
// ���� ������ �����
	void playerMonsterStupid(Object& player, Object& regularMonster)
	{
		PlayerRegular& playerr = static_cast<PlayerRegular&>(player);
		MonsterStupid& Monster = static_cast<MonsterStupid&>(regularMonster);
		playerr.decLive();
		Monster.setFirstLocation();

	}

//--------------------------------------------------------------------------------------------
//���� ������ ����
	void playerMonsterSmart(Object& player, Object& specielMonster)
	{
		PlayerRegular& playerr = static_cast<PlayerRegular&>(player);
		MonsterSmart& Monster = static_cast<MonsterSmart&>(specielMonster);
		playerr.decLive();
		Monster.setFirstLocation();
	}
	
	//--------------------------------------------------------------------------------------------
//���� �����
	void playerWall(Object& player, Object& wall)
	{
		Player& playerr = static_cast<Player&>(player);
		Wall& walll = static_cast<Wall&>(wall);
		playerr.setPrevPosition();
	}

	//--------------------------------------------------------------------------------------------
// ���� ������
	void playerFloor(Object& player, Object& floor)
	{
		Player& playerr = static_cast<Player&>(player);
		Floor& floorr = static_cast<Floor&>(floor);
		playerr.setPrevPosition();
	}

	//--------------------------------------------------------------------------------------------
// ����� �����
	void MonsterFloor(Object& monster, Object& floor)
	{
		Monster& monsterr = static_cast<Monster&>(monster);
		Floor& floorr = static_cast<Floor&>(floor);
		monsterr.setDirection();
	}

	//--------------------------------------------------------------------------------------------
// ����� ����
	void MonsterWall(Object& monster, Object& wall)
	{
		Monster& monsterr = static_cast<Monster&>(monster);
		Wall& walll = static_cast<Wall&>(wall);
		monsterr.setDirection();
	}

	//--------------------------------------------------------------------------------------------
// ���� ����
	void playerWanted(Object& player, Object& wanted)
	{
		Player& playerr = static_cast<Player&>(player);
		Wanted& wontedd = static_cast<Wanted&>(wanted);
		playerr.NotifyObserversWanted();
	}
	
	//--------------------------------------------------------------------------------------------
// ���� ����� - ���� ������
	void playerGiftSpecialShoot(Object& player, Object& giftSpecialShoot)
	{
		Player& playerr = static_cast<Player&>(player);
		GiftSpecialShoot& gift = static_cast<GiftSpecialShoot&>(giftSpecialShoot);
		playerr.setShootSpecialOn();
	}

	//--------------------------------------------------------------------------------------------
// ���� ����� - ��� ����
	void playerGiftProtectedMode(Object& player, Object& gift)
	{
		Player& playerr = static_cast<Player&>(player);
		GiftProtectedMode& giftt = static_cast<GiftProtectedMode&>(gift);
		playerr.setProtectedMode();
	}

	//--------------------------------------------------------------------------------------------
// ���� ����� - ���� ���
	void playerGiftSpecialPlayer(Object& player, Object& gift)
	{
		Player& playerr = static_cast<Player&>(player);
		GiftSpecialPlayer& giftt = static_cast<GiftSpecialPlayer&>(gift);
		playerr.NotifyObserversSpecialPlayer();
	}

	//--------------------------------------------------------------------------------------------
	// ����� ��� �����
	void emptyPlayer(Object& player, Object& empty)
	{
		Player& playerr = static_cast<Player&>(player);
		EmptyObject& emptyy  = static_cast<EmptyObject&>(empty);
	}

	//--------------------------------------------------------------------------------------------
// ���� ����� �����
	void ShootStupidPlayer(Object& player, Object& shoot)
	{
		ShootStupid& shoott = static_cast<ShootStupid&>(shoot);
		Player& playerr = static_cast<Player&>(player);
		playerr.subShootStupidCollition();
	}

	//--------------------------------------------------------------------------------------------
// ���� ����� ������
	void ShootStupidMonster(Object& monster, Object& shoot )
	{
		ShootStupid& shoott = static_cast<ShootStupid&>(shoot);
		Monster& monsterr = static_cast<Monster&>(monster);
		monsterr.subShootCollition();
	}

	//--------------------------------------------------------------------------------------------
// ���� ��� ������ 
	void smartPlayerMonster(Object& player, Object& regularMonster)
	{
		PlayerSmart& playerr = static_cast<PlayerSmart&>(player);
		Monster& monster = static_cast<Monster&>(regularMonster);
		monster.removeThisMonster();

	}








	
	using HitFunctionPtr = void (*)(Object&, Object&);

	using Key = std::pair<std::type_index, std::type_index>;
	using HitMap = std::map<Key, HitFunctionPtr>;

	HitMap initializeCollisionMap()
	{
		HitMap phm;
		//����� ������� �� ���� ����
		phm[Key(typeid(PlayerRegular), typeid(MonsterStupid))] = &playerMonsterStupid;
		phm[Key(typeid(PlayerRegular), typeid(MonsterSmart))] = &playerMonsterSmart;
		phm[Key(typeid(PlayerRegular), typeid(EmptyObject))] = &emptyPlayer;
		phm[Key(typeid(PlayerRegular), typeid(Floor))] = &playerFloor;
		phm[Key(typeid(PlayerRegular), typeid(Wall))] = &playerWall;
		phm[Key(typeid(PlayerRegular), typeid(Wanted))] = &playerWanted;
		phm[Key(typeid(PlayerRegular), typeid(GiftSpecialShoot))] = &playerGiftSpecialShoot;
		phm[Key(typeid(PlayerRegular), typeid(GiftProtectedMode))] = &playerGiftProtectedMode;
		phm[Key(typeid(PlayerRegular), typeid(GiftSpecialPlayer))] = &playerGiftSpecialPlayer;
		phm[Key(typeid(PlayerRegular), typeid(ShootStupid))] = &ShootStupidPlayer;

		//����� ������� �� ���� ���
		phm[Key(typeid(PlayerSmart), typeid(MonsterStupid))] = &smartPlayerMonster;
		phm[Key(typeid(PlayerSmart), typeid(MonsterSmart))] = &smartPlayerMonster;
		phm[Key(typeid(PlayerSmart), typeid(EmptyObject))] = &emptyPlayer;
		phm[Key(typeid(PlayerSmart), typeid(Floor))] = &playerFloor;
		phm[Key(typeid(PlayerSmart), typeid(Wall))] = &playerWall;
		phm[Key(typeid(PlayerSmart), typeid(Wanted))] = &playerWanted;
		phm[Key(typeid(PlayerSmart), typeid(GiftSpecialShoot))] = &playerGiftSpecialShoot;
		phm[Key(typeid(PlayerSmart), typeid(GiftProtectedMode))] = &playerGiftProtectedMode;
		phm[Key(typeid(PlayerSmart), typeid(GiftSpecialPlayer))] = &playerGiftSpecialPlayer;
		phm[Key(typeid(PlayerSmart), typeid(ShootStupid))] = &ShootStupidPlayer;

		//����� ������� �� ������
		phm[Key(typeid(MonsterStupid), typeid(ShootStupid))] = &ShootStupidMonster;
		phm[Key(typeid(MonsterSmart), typeid(ShootStupid))] = &ShootStupidMonster;
		phm[Key(typeid(MonsterStupid), typeid(ShootSpecial))] = &ShootStupidMonster;
		phm[Key(typeid(MonsterSmart), typeid(ShootSpecial))] = &ShootStupidMonster;
		phm[Key(typeid(MonsterSmart), typeid(Floor))] = &MonsterFloor;
		phm[Key(typeid(MonsterStupid), typeid(Floor))] = &MonsterFloor;
		phm[Key(typeid(MonsterSmart), typeid(Wall))] = &MonsterWall;
		phm[Key(typeid(MonsterStupid), typeid(Wall))] = &MonsterWall;


	

		return phm;
	}



	HitFunctionPtr lookup(const std::type_index& class1, const std::type_index& class2)
	{
		static HitMap collisionMap = initializeCollisionMap();
		auto mapEntry = collisionMap.find(std::make_pair(class1, class2));
		if (mapEntry == collisionMap.end())
		{
			return nullptr;
		}
		return mapEntry->second;
	}

} // end namespace
//���� �� '���� ������� �� �������
void processCollision(Object& object1, Object& object2)
{
	auto phf = lookup(typeid(object1), typeid(object2));
	if (!phf)
	{
		throw UnknownCollision(object1, object2);
	}
	phf(object1, object2);
}


