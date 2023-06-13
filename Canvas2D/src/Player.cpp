#include "Player.h"
#include "Bullet.h"
#include <cmath>
#include "GameManager.h"

Player::Player() : MovableObject("figures/spaceship.gr"), ICollidable(new CircleCollider(position, 15))
{
	figure.SetScale(Vector2(0.4, 0.4));
	maxAcceleration = 700;
	maxSpeed = 200;
	position = Vector2(310, 310);
	figure.SetPosition(position);
	collider = (CircleCollider*)ICollidable::collider;
	collider->SetTag("Player");
	lifeBar = new LifeBar(Vector2(35, 35), 50);
	lifeBar->SetHearts(5);
}

Player::~Player()
{
	delete collider;
	delete lifeBar;
}

void Player::OnCollision(OnCollisionEvent* args)
{
	if (args->collider->GetTag() == "EnemyBullet")
	{
		args->collider->SetTag("hittedBullet");

		lifeBar->RemoveHeart();
		if (lifeBar->GetHearts() <= 0)
		{
			GameManager::Instance()->GameOver();
		}

		return;
	}

	if (args->collider->GetTag() == "tripleBulletPowerUp")
	{
		this->powerUp = "tripleBullet";
		args->collider->SetTag("hittedBullet");
		powerUpTimer = 0;
		printf("powerUP!! \n");
		return;
	}

	if (args->collider->GetTag() == "curvedBulletPowerUp")
	{
		this->powerUp = "curvedBullet";
		args->collider->SetTag("hittedBullet");
		powerUpTimer = 0;
		printf("powerUP!! \n");
		return;
	}

	Vector2 normal = args->collisionPoint - position;
	normal.normalize();

	Vector2 projection = normal * maxSpeed * 1.5;
	speed -= projection;

}

void Player::OnClick(OnClickEvent* args)
{
	if(args->state != 0)
		return;

	Vector2 direction = mousePosition - position;
	direction.normalize();
	Vector2 speed = direction * 500;
	Vector2 acceleration = direction * 5;

	if (powerUp == "default")
	{
		new PlayerBullet(position, speed, acceleration);
	}
	else if (powerUp == "curvedBullet")
	{
		//instance 4 curvedBullets with small difference in constructors paramenter
		Vector2 leftSpeed = speed;
		Vector2 leftAcceleration = acceleration;
		leftSpeed.rotate(30);
		leftAcceleration.rotate(30);
		Vector2 rightSpeed = speed;
		Vector2 rightAcceleration = acceleration;
		rightSpeed.rotate(-30);
		rightAcceleration.rotate(-30);

		new CurvedBullet(position, leftSpeed, leftAcceleration);
		new CurvedBullet(position, speed, acceleration);
		new CurvedBullet(position, rightSpeed, rightAcceleration);
		new CurvedBullet(position, rightSpeed, rightAcceleration);

	}
	else if (powerUp == "tripleBullet")
	{
		Vector2 leftSpeed = speed;
		Vector2 leftAcceleration = acceleration;
		leftSpeed.rotate(30);
		leftAcceleration.rotate(30);
		Vector2 rightSpeed = speed;
		Vector2 rightAcceleration = acceleration;
		rightSpeed.rotate(-30);
		rightAcceleration.rotate(-30);

		new TripleBullet(position, leftSpeed, leftAcceleration);
		new TripleBullet(position, speed, acceleration);
		new TripleBullet(position, rightSpeed, rightAcceleration);
	}
}

void Player::OnUpdate(OnUpdateEvent* args)
{
	MovableObject::OnUpdate(args);
	collider->position = position;
	figure.AlignWith(mousePosition);

	if (powerUp != "default")
	{
		powerUpTimer += args->deltaTime;
		if (powerUpTimer >= 6)
		{
			powerUp = "default";
			powerUpTimer = 0;
		}
	}
}

void Player::OnKey(OnKeyEvent* args)
{
	bool isAccelerating = args->state == 0;

	switch (args->key)
	{
		case 119: //w
			acceleration.y = isAccelerating ? 1 : 0;
			break;

		case 115: //s
			acceleration.y = isAccelerating ? -1 : 0;
			break;

		case 97: //a
			acceleration.x = isAccelerating ? -1 : 0;
			break;

		case 100: //d
			acceleration.x = isAccelerating ? 1 : 0;
			break;

	default:
		break;
	}
}

void Player::OnMouseOver(OnMouseOverEvent* args)
{
	mousePosition = Vector2(args->x, args->y);
}

bool Player::IsDestroyed()
{
	return isDestroyed;
}

void Player::SetRender(bool state)
{
	figure.SetRender(state);
}