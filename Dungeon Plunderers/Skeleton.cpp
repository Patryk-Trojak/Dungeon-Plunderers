#include "pch.h"
#include "Skeleton.h"

Skeleton::Skeleton(const sf::Vector2f& Position, const sf::Vector2f ChangeDirectionDistance, const Resources& resources, const sf::Vector2f& initialScale)
	:Enemy(Position, resources[TextureID::Skeleton2], resources,
	Animation(1, 1, sf::Vector2i(139.f, 200.f), 11, 0.1f), sf::Vector2f(-25.f, -30.f),
	300, 10,
	false)
{
	movingEnemyComponent = std::make_unique<MovingEnemyComponent>(enemy, initialScale, sf::Vector2f(200.f, 0.f), ChangeDirectionDistance);
	name = EnemyType::skeleton;
	enemy.setOrigin(45.f, 0.f);
	this->initialScale = initialScale;

	enemy.setScale(initialScale);
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(47.9774, 9.04529), sf::Vector2f(-17.9265, -0.0626068)));

	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(57.9231, 17.9768), sf::Vector2f(-19.9577, 8.90253))); 
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(59.8842, 10.7862), sf::Vector2f(-18.0666, 26.7782)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(52.9503, 8.26472), sf::Vector2f(-10.8525, 37.1441)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(40.343, 11.0663), sf::Vector2f(-2.65782, 45)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(15.2687, 9.66551), sf::Vector2f(-5.10922, 55.5718))); //5
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(51.7262, 48.5999), sf::Vector2f(-32.0736, 61.3896)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(18.5684, 10.5157), sf::Vector2f(-44.7683, 93.7895)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(5.02104, 29.3683), sf::Vector2f(-35.57894, 64.8001)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(6.57366, 16.2947), sf::Vector2f(-41.39466, 77.779)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(36.4736, 25.8631), sf::Vector2f(-15.7578, 109.579)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(11.1789, 12.6947), sf::Vector2f(19.4738, 61.8737)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.43155, 11.5579), sf::Vector2f(30.179, 69.6421)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(11.2737, 14.7789), sf::Vector2f(38.6105, 75.4211)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(20.4631, 7.29471), sf::Vector2f(49.1263, 79.021)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.6947, 7.19995), sf::Vector2f(68.9263, 74.4737)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.222f, 2.92059f), sf::Vector2f(-9.97723f, 138.139f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(9.87848f, 3.86548f), sf::Vector2f(-6.71307f, 140.888f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.41815f, 3.26419f), sf::Vector2f(-1.81677f, 144.582f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.07452f, 3.60779f), sf::Vector2f(0.502502f, 147.417f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.222f, 3.60776f), sf::Vector2f(3.4231f, 150.681f))); //20
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.799f, 3.95135f), sf::Vector2f(7.20264f, 153.43f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.1361f, 5.92706f), sf::Vector2f(10.5527f, 156.866f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(10.9951f, 3.43597f), sf::Vector2f(12.9579f, 162.191f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(9.19122f, 4.38089f), sf::Vector2f(18.9709f, 165.541f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(9.36304f, 4.03729f), sf::Vector2f(23.4587f, 170.079f))); //25
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(9.79254f, 4.29498f), sf::Vector2f(27.2383f, 173.945f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.93353f, 4.55267f), sf::Vector2f(31.791f, 178.154f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(8.76178f, 4.38089f), sf::Vector2f(36.3436f, 182.535f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(12.0259f, 6.44247f), sf::Vector2f(39.0924f, 186.572f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(16.9221f, 4.12317f), sf::Vector2f(39.0924f, 195.677f)));
	hitboxComponent.addHitbox(Hitbox(Position, sf::Vector2f(21.6947, 7.19995), sf::Vector2f(68.9263, 74.4737)));
	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(8.76178f, 3.26419f), sf::Vector2f(42.9578f, 192.843f)));

	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(7.96484f, 20.8413f), sf::Vector2f(11.1587f, 133.928f)));

	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(7.97089f, 39.2037f), sf::Vector2f(12.0771f, 154.494f)));

	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(26.4341f, 5.69348f), sf::Vector2f(7.60361f, 194.43f)));

	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f)));

	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f)));
	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f)));
	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f)));
	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f)));
	hitboxComponent.addHitbox(Hitbox(sf::Vector2f(), sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f)));

	base.addHitbox(Hitbox(Position, sf::Vector2f(54.0173f, 4), sf::Vector2f(-12.9769f, 199.982f)));

	//animation.play();
}

Skeleton::~Skeleton()
{
}

void Skeleton::matchHitboxesToAnimation()
{

		switch (animation.getNumberOfCurrentFrame())
		{
		case 1:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(10.222f, 2.92059f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-9.97723f, 138.139f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(9.87848f, 3.86548f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-6.71307f, 140.888f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(8.41815f, 3.26419f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-1.81677f, 144.582f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(8.07452f, 3.60779f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(0.502502f, 147.417f));
			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(10.222f, 3.60776f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(3.4231f, 150.681f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(12.799f, 3.95135f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(7.20264f, 153.43f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(10.1361f, 5.92706f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(10.5527f, 156.866f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(10.9951f, 3.43597f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(12.9579f, 162.191f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(9.19122f, 4.38089f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(18.9709f, 165.541f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(9.36304f, 4.03729f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(23.4587f, 170.079f));

			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(9.79254f, 4.29498f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(27.2383f, 173.945f));

			hitboxComponent.setHitbox(27, sf::Vector2f(8.93353f, 4.55267f), sf::Vector2f(31.791f, 178.154f));

			hitboxComponent.setHitbox(28, sf::Vector2f(8.76178f, 4.38089f), sf::Vector2f(36.3436f, 182.535f));
			hitboxComponent.setHitbox(29, sf::Vector2f(12.0259f, 6.44247f), sf::Vector2f(39.0924f, 186.572f));
			hitboxComponent.setHitbox(30, sf::Vector2f(16.9221f, 4.12317f), sf::Vector2f(39.0924f, 195.677f));
			hitboxComponent.setHitbox(31, sf::Vector2f(21.6947, 7.19995), sf::Vector2f(68.9263, 74.4737));
			hitboxComponent.setHitbox(32, sf::Vector2f(8.76178f, 3.26419f), sf::Vector2f(42.9578f, 192.843f));
			hitboxComponent.setHitbox(33, sf::Vector2f(7.96484f, 20.8413f), sf::Vector2f(11.1587f, 133.928f));
			hitboxComponent.setHitbox(34, sf::Vector2f(7.97089f, 39.2037f), sf::Vector2f(12.0771f, 154.494f));
			hitboxComponent.setHitbox(35, sf::Vector2f(26.4341f, 5.69348f), sf::Vector2f(7.60361f, 194.43f));
			hitboxComponent.setHitbox(36, sf::Vector2f(2.11473f, 8.62155f), sf::Vector2f(18.9092f, 152.024f));

			
			break;
		case 2:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(10.222f, 2.92059f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-9.97723f, 138.139f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(9.87848f, 3.86548f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-6.71307f, 140.888f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(8.41815f, 3.26419f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-1.81677f, 144.582f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(8.07452f, 3.60779f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(0.502502f, 147.417f));
			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(10.222f, 3.60776f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(3.4231f, 150.681f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(12.799f, 3.95135f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(7.20264f, 153.43f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(10.1361f, 5.92706f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(10.5527f, 156.866f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(10.9951f, 3.43597f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(12.9579f, 162.191f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(9.19122f, 4.38089f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(18.9709f, 165.541f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(9.36304f, 4.03729f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(23.4587f, 170.079f));

			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(9.79254f, 4.29498f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(27.2383f, 173.945f));

			hitboxComponent.setHitbox(27, sf::Vector2f(8.93353f, 4.55267f), sf::Vector2f(31.791f, 178.154f));

			hitboxComponent.setHitbox(28, sf::Vector2f(8.76178f, 4.38089f), sf::Vector2f(36.3436f, 182.535f));
			hitboxComponent.setHitbox(29, sf::Vector2f(12.0259f, 6.44247f), sf::Vector2f(39.0924f, 186.572f));
			hitboxComponent.setHitbox(30, sf::Vector2f(16.9221f, 4.12317f), sf::Vector2f(39.0924f, 195.677f));
			hitboxComponent.setHitbox(31, sf::Vector2f(21.6947, 7.19995), sf::Vector2f(68.9263, 74.4737));


			hitboxComponent.setSizeOfHitbox(32, sf::Vector2f(7.72736f, 6.53018f));
			hitboxComponent.setOffsetOfHitbox(32, sf::Vector2f(11.2802f, 133.512f));
			hitboxComponent.setSizeOfHitbox(33, sf::Vector2f(6.42139f, 5.11533f));
			hitboxComponent.setOffsetOfHitbox(33, sf::Vector2f(10.4094f, 139.933f));
			hitboxComponent.setSizeOfHitbox(34, sf::Vector2f(7.5097f, 7.07437f));
			hitboxComponent.setOffsetOfHitbox(34, sf::Vector2f(8.1239f, 144.613f));
			hitboxComponent.setSizeOfHitbox(35, sf::Vector2f(6.09485f, 15.6724f));
			hitboxComponent.setOffsetOfHitbox(35, sf::Vector2f(3.9881f, 160.83f));

			hitboxComponent.setHitbox(37, sf::Vector2f(5.22412f, 16.6519f), sf::Vector2f(2.02905f, 171.06f));
			hitboxComponent.setHitbox(38, sf::Vector2f(6.85675f, 17.5226f), sf::Vector2f(-0.147705f, 176.829f));
			hitboxComponent.setHitbox(39, sf::Vector2f(3.04736f, 9.25107f), sf::Vector2f(-3.195065, 186.08f));
			hitboxComponent.setHitbox(40, sf::Vector2f(25.5765f, 5.87717f), sf::Vector2f(-5.1347f, 194.223f));
			hitboxComponent.setHitbox(41, sf::Vector2f(5.65948f, 11.319f), sf::Vector2f(5.83832f, 154.511f));

			break;
		case 3:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(10.222f, 2.92059f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-9.97723f, 138.139f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(9.87848f, 3.86548f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-6.71307f, 140.888f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(8.41815f, 3.26419f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-1.81677f, 144.582f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(8.07452f, 3.60779f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(0.502502f, 147.417f));
			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(10.222f, 3.60776f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(3.4231f, 150.681f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(12.799f, 3.95135f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(7.20264f, 153.43f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(10.1361f, 5.92706f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(10.5527f, 156.866f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(10.9951f, 3.43597f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(12.9579f, 162.191f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(9.19122f, 4.38089f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(18.9709f, 165.541f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(9.36304f, 4.03729f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(23.4587f, 170.079f));

			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(9.79254f, 4.29498f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(27.2383f, 173.945f));

			hitboxComponent.setHitbox(27, sf::Vector2f(8.93353f, 4.55267f), sf::Vector2f(31.791f, 178.154f));

			hitboxComponent.setHitbox(28, sf::Vector2f(8.76178f, 4.38089f), sf::Vector2f(36.3436f, 182.535f));
			hitboxComponent.setHitbox(29, sf::Vector2f(12.0259f, 6.44247f), sf::Vector2f(39.0924f, 186.572f));
			hitboxComponent.setHitbox(30, sf::Vector2f(16.9221f, 4.12317f), sf::Vector2f(39.0924f, 195.677f));
			hitboxComponent.setHitbox(31, sf::Vector2f(21.6947, 7.19995), sf::Vector2f(68.9263, 74.4737));

			hitboxComponent.setSizeOfHitbox(32, sf::Vector2f(7.76532f, 5.90988f));
			hitboxComponent.setOffsetOfHitbox(32, sf::Vector2f(11.1896f, 134.066f));
			hitboxComponent.setSizeOfHitbox(33,sf::Vector2f(6.66583f, 5.29141f));
			hitboxComponent.setOffsetOfHitbox(33, sf::Vector2f(10.1588f, 139.839f));
			hitboxComponent.setSizeOfHitbox(34, sf::Vector2f(7.69659f, 19.104f));
			hitboxComponent.setOffsetOfHitbox(34, sf::Vector2f(8.16589f, 144.855f));


			hitboxComponent.setSizeOfHitbox(35, sf::Vector2f(6.74866f, 26.569f));
			hitboxComponent.setOffsetOfHitbox(35, sf::Vector2f(-30.6588f, 148.165f));
			hitboxComponent.setSizeOfHitbox(36, sf::Vector2f(36.7831f, 7.17426f));
			hitboxComponent.setOffsetOfHitbox(36, sf::Vector2f(-23.8493f, 154.975f));


			for (int i = 37; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;

		case 4:

			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(7.89929f, 30.8464f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(11.0581f, 133.936f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(37.5518f, 7.12894f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-25.542f, 155.048f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(5.79285f, 26.3223f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-30.9398f, 148.742f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(8.29431f, 5.34671f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-13.4297f, 133.936f));
			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(8.95251f, 6.16928f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(-10.9282f, 138.871f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(8.29431f, 5.4838f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(-8.29517f, 144.355f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(7.7677f, 6.16928f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(-5.26709f, 149.153f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(12.5072f, 3.83865f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(-1.58069f, 161.629f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(9.08423f, 6.16928f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(2.10559f, 165.468f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(7.50439f, 4.38705f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(5.00195f, 171.363f));
			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(7.76758f, 4.11285f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(7.37183f, 175.201f));
			hitboxComponent.setSizeOfHitbox(27, sf::Vector2f(7.50427f, 4.28705f));
			hitboxComponent.setOffsetOfHitbox(27, sf::Vector2f(8.95166f, 179.04f));
			hitboxComponent.setSizeOfHitbox(28, sf::Vector2f(8.4259f, 4.84997f));
			hitboxComponent.setOffsetOfHitbox(28, sf::Vector2f(10.7949f, 183.153f));

			hitboxComponent.setSizeOfHitbox(29, sf::Vector2f(11.5856f, 6.0322f));
			hitboxComponent.setOffsetOfHitbox(29, sf::Vector2f(11.4531f, 187.951f));

			hitboxComponent.setSizeOfHitbox(30, sf::Vector2f(17.2467f, 5.4838f));
			hitboxComponent.setOffsetOfHitbox(30, sf::Vector2f(10.9265f, 194.532f));

			for (int i = 31; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;

		case 5:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(7.68848f, 7.68591f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-12.5842f, 133.145f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(8.14978f, 53.9616f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-10.5852f, 140.35f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(16.7845f, 5.12393f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-13.8143f, 194.952f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(11.8403f, 5.12396f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-13.0455f, 154.921f));

			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(8.46399f, 29.5379f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(10.8762f, 133.946f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(10.2939f, 10.243f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(6.75867f, 154.67f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(8.52661f, 3.31738f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(-2.32446f, 170.366f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(8.99512f, 3.90283f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(2.54785f, 165.78f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(9.08875f, 2.53683f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(3.85962f, 163.731f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(8.15173f, 3.21982f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(-0.0756836f, 167.926f));
			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(6.09045f, 3.61011f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(-2.23083f, 173.39f));

			hitboxComponent.setSizeOfHitbox(27, sf::Vector2f(4.02893f, 2.34171f));
			hitboxComponent.setOffsetOfHitbox(27, sf::Vector2f(-2.04333f, 176.708f));

			hitboxComponent.setSizeOfHitbox(28, sf::Vector2f(5.5282f, 24.4902f));
			hitboxComponent.setOffsetOfHitbox(28, sf::Vector2f(-15.2549f, 171.341f));

			for (int i = 29; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
			break;

		case 6:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(7.68848f, 7.68591f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-12.5842f, 133.145f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(8.14978f, 53.9616f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-10.5852f, 140.35f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(16.7845f, 5.12393f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-13.8143f, 194.952f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(11.8403f, 5.12396f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-13.0455f, 154.921f));

			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(8.76123f, 4.23914f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(11.3889f, 134.753f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(8.23035f, 3.77835f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(12.9818f, 138.716f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(8.49573f, 4.3313f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(15.3713f, 142.494f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(8.14185f, 5.25284f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(16.7872f, 146.549f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(11.5933f, 8.58614f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(17.2297f, 151.433f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(7.78784f, 34.3738f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(20.017f, 160.006f));
			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(26.2839f, 5.16071f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(15.946f, 194.656f));

			for (int i = 27; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));
			break;
		case 7:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(7.68848f, 7.68591f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-12.5842f, 133.145f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(8.14978f, 53.9616f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-10.5852f, 140.35f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(16.7845f, 5.12393f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-13.8143f, 194.952f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(11.8403f, 5.12396f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-13.0455f, 154.921f));

			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(8.3446f, 4.92468f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(11.5048f, 134.108f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(8.20776f, 3.28311f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(12.3256f, 138.759f));
			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(10.2598f, 4.10388f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(13.1464f, 141.906f));
			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(8.61816f, 5.88229f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(15.7455f, 145.326f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(10.123f, 3.9671f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(18.6182f, 150.934f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(11.9014f, 10.3966f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(20.2598f, 153.123f));
			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(9.57581f, 7.5238f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(24.2546f, 162.453f));

			hitboxComponent.setHitbox(27, sf::Vector2f(8.61816f, 7.52383f), sf::Vector2f(29.0426f, 169.566f));
			hitboxComponent.setHitbox(28, sf::Vector2f(9.43896f, 7.11343f), sf::Vector2f(31.6417f, 176.953f));
			hitboxComponent.setHitbox(29, sf::Vector2f(9.30212f, 8.07101f), sf::Vector2f(35.0616f, 183.793f));
			hitboxComponent.setHitbox(30, sf::Vector2f(25.1705f, 5.47186f), sf::Vector2f(33.5569f, 194.737f));
			hitboxComponent.setHitbox(31, sf::Vector2f(7.5238f, 3.9671f), sf::Vector2f(37.2504f, 191.043f));
			
			for (int i = 32; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;
		case 8:
			//first leg
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(7.91895f, 31.407f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-13.1343f, 133.236f));

			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(5.77124f, 18.2536f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-18.63724f, 176.588f));

			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(6.30835f, 31.1385f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-16.3555f, 160.885f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(16.5088f, 5.77136f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-23.6033f, 193.972f));

			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(3.89233f, 9.26102f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(-16.08683f, 152.23f));

			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(3.08716f, 8.45572f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(-18.77146f, 168.336f));

			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(3.75806f, 12.348f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(-21.58986, 182.295f));
			


			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(8.3446f, 4.92468f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(11.5048f, 134.108f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(8.20776f, 3.28311f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(12.3256f, 138.759f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(10.2598f, 4.10388f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(13.1464f, 141.906f));
			hitboxComponent.setSizeOfHitbox(26, sf::Vector2f(8.61816f, 5.88229f));
			hitboxComponent.setOffsetOfHitbox(26, sf::Vector2f(15.7455f, 145.326f));
			hitboxComponent.setSizeOfHitbox(27, sf::Vector2f(10.123f, 3.9671f));
			hitboxComponent.setOffsetOfHitbox(27, sf::Vector2f(18.6182f, 150.934f));
			hitboxComponent.setSizeOfHitbox(28, sf::Vector2f(11.9014f, 10.3966f));
			hitboxComponent.setOffsetOfHitbox(28, sf::Vector2f(20.2598f, 153.123f));
			hitboxComponent.setSizeOfHitbox(29, sf::Vector2f(9.57581f, 7.5238f));
			hitboxComponent.setOffsetOfHitbox(29, sf::Vector2f(24.2546f, 162.453f));
			hitboxComponent.setSizeOfHitbox(30, sf::Vector2f(9.57581f, 7.5238f));
			hitboxComponent.setOffsetOfHitbox(30, sf::Vector2f(24.2546f, 162.453f));

			hitboxComponent.setSizeOfHitbox(31, sf::Vector2f(8.61816f, 7.52383f));
			hitboxComponent.setOffsetOfHitbox(31, sf::Vector2f(29.0426f, 169.566f));
			
			hitboxComponent.setHitbox(32, sf::Vector2f(9.43896f, 7.11343f), sf::Vector2f(31.6417f, 176.953f));
			hitboxComponent.setHitbox(33, sf::Vector2f(9.30212f, 8.07101f), sf::Vector2f(35.0616f, 183.793f));
			hitboxComponent.setHitbox(34, sf::Vector2f(25.1705f, 5.47186f), sf::Vector2f(33.5569f, 194.737f));
			hitboxComponent.setHitbox(35, sf::Vector2f(7.5238f, 3.9671f), sf::Vector2f(37.2504f, 191.043f));

			for (int i = 36; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));


			break;
		case 9:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(7.91895f, 31.407f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(-13.1343f, 133.236f));

			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(5.77124f, 18.2536f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(-18.63724f, 176.588f));

			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(6.30835f, 31.1385f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(-16.3555f, 160.885f));
			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(16.5088f, 5.77136f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-23.6033f, 193.972f));

			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(3.89233f, 9.26102f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(-16.08683f, 152.23f));

			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(3.08716f, 8.45572f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(-18.77146f, 168.336f));

			hitboxComponent.setSizeOfHitbox(22, sf::Vector2f(3.75806f, 12.348f));
			hitboxComponent.setOffsetOfHitbox(22, sf::Vector2f(-21.58986, 182.295f));


			hitboxComponent.setSizeOfHitbox(23, sf::Vector2f(8.05298f, 67.3773f));
			hitboxComponent.setOffsetOfHitbox(23, sf::Vector2f(11.1252f, 131.561f));
			hitboxComponent.setSizeOfHitbox(24, sf::Vector2f(26.7095f, 5.50293f));
			hitboxComponent.setOffsetOfHitbox(24, sf::Vector2f(6.69604f, 193.569f));
			hitboxComponent.setSizeOfHitbox(25, sf::Vector2f(11.1401f, 10.7374f));
			hitboxComponent.setOffsetOfHitbox(25, sf::Vector2f(10.3198f, 152.901f));

			for (int i = 26; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;
		case 10:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(8.05298f, 67.3773f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(11.1252f, 131.561f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(26.7095f, 5.50293f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(6.69604f, 193.569f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(11.1401f, 10.7374f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(10.3198f, 152.901f));

			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(7.79646f, 32.433f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-12.6131f, 131.223f));
			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(4.7186f, 16.5151f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(-44.3325f, 150.884f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(37.2651f, 7.60217f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(-39.6139f, 154.291f));

			for (int i = 22; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;
		case 11:
			hitboxComponent.setSizeOfHitbox(16, sf::Vector2f(8.05298f, 67.3773f));
			hitboxComponent.setOffsetOfHitbox(16, sf::Vector2f(11.1252f, 131.561f));
			hitboxComponent.setSizeOfHitbox(17, sf::Vector2f(26.7095f, 5.50293f));
			hitboxComponent.setOffsetOfHitbox(17, sf::Vector2f(6.69604f, 193.569f));
			hitboxComponent.setSizeOfHitbox(18, sf::Vector2f(11.1401f, 10.7374f));
			hitboxComponent.setOffsetOfHitbox(18, sf::Vector2f(10.3198f, 152.901f));

			hitboxComponent.setSizeOfHitbox(19, sf::Vector2f(9.98578f, 5.90558f));
			hitboxComponent.setOffsetOfHitbox(19, sf::Vector2f(-13.0117f, 133.906f));
			hitboxComponent.setSizeOfHitbox(20, sf::Vector2f(8.69733f, 4.5097f));
			hitboxComponent.setOffsetOfHitbox(20, sf::Vector2f(-9.68311f, 139.811f));
			hitboxComponent.setSizeOfHitbox(21, sf::Vector2f(6.97931f, 4.08023f));
			hitboxComponent.setOffsetOfHitbox(21, sf::Vector2f(-6.56927f, 144.321f));

			hitboxComponent.setHitbox(22, sf::Vector2f(8.80463f, 6.6572f), sf::Vector2f(-4.95862f, 147.972f));
			hitboxComponent.setHitbox(23, sf::Vector2f(42.4128f, 7.08673f), sf::Vector2f(-36.3119f, 154.951f));
			hitboxComponent.setHitbox(24, sf::Vector2f(6.1203f, 17.2872f), sf::Vector2f(-37.1709f, 150.441f));
			hitboxComponent.setHitbox(25, sf::Vector2f(8.91205f, 9.5563f), sf::Vector2f(-4.85126f, 154.521f));

			for (int i = 26; i <= 41; i++)
				hitboxComponent.hitboxes[i].setHitbox(sf::Vector2f(0.f, 0.f), sf::Vector2f(-10000.f, -1000.f));

			break;
		}
	

}
