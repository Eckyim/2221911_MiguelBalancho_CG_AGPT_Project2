#include "Explosion.h"

Explosion::Explosion(MyGameEngine* engine, SpriteSheet* sheet, float x, float y, float width, float height)
	:Entity(engine, sheet, x, y, width, height)
{
	engineRef->PlaySound("explosion");
	PlayAnimation("boom");
	dying = true;
}
