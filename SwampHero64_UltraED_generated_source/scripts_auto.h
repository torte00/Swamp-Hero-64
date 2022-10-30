void UER_0Update(Actor *self)
{
	if(self->rotationAxis.y < 0)
	{
		self->rotationAngle = -self->rotationAngle; 
	}
		
	self->rotationAxis.x = 0;	
	self->rotationAxis.y = 1;
	self->rotationAxis.z = 0;
}

void UER_0Input(Actor *self, NUContData gamepads[4])
{
	const float rotation = self->rotationAngle * (3.14/180);
	const Vector3 forward = VECTOR3(sinf(rotation), 0.0f, cosf(rotation));
	
	self->position.x += forward.x * (gamepads[0].stick_y > 1 ? 0.05f : (gamepads[0].stick_y < -1 ? -0.05f : 0));
	self->position.z += forward.z * (gamepads[0].stick_y > 1 ? 0.05f : (gamepads[0].stick_y < -1 ? -0.05f : 0));
	self->rotationAngle += gamepads[0].stick_x > 1 ? 1.5f : (gamepads[0].stick_x < -1 ? -1.5f : 0);
}

typedef struct UER_1_Bullet
{
	Vector3 dir;
	Vector3 initPos;
} UER_1Bullet;

void UER_1Notify(Actor *self, const char *message, void *data)
{
	if(message == "Fire" && data != NULL)
	{
		Vector3 *dir = (Vector3*)data;
		if(dir != NULL && self->dynamic != NULL)
		{
			((UER_1Bullet *)self->dynamic)->dir = *dir;
			((UER_1Bullet *)self->dynamic)->initPos = self->position;
		}
	}
}

void UER_1Start(Actor *self)
{
	self->dynamic = (UER_1Bullet *)malloc(sizeof(UER_1Bullet));
	self->notify = UER_1Notify;
}

void UER_1Update(Actor *self)
{
	UER_1Bullet *bullet = (UER_1Bullet *)self->dynamic;
	if(bullet != NULL)
	{
		self->position = CMath_Vec3Add(self->position, bullet->dir);
		
		if(CMath_Vec3Dist(self->position, bullet->initPos) > 20)
			Destroy(self);
	}
}

void UER_2Fire(Actor *self)
{
	Model *bullet = (Model *)FindActorByName("Bullet");
	
	if(bullet != NULL)
	{
		Actor *clonedBullet = (Actor *)Clone(bullet);
		
		if(clonedBullet != NULL && clonedBullet->notify != NULL)
		{
			clonedBullet->position = CActor_GetPosition(self);
			
			Vector3 *direction = malloc(sizeof(Vector3));
			
			if(direction != NULL)
			{
				Vector3 forward = VECTOR3(0, 1, 0);
				forward = CMath_Vec3MulMat(forward, CActor_GetRotationMatrix(self));
	
				*direction = VECTOR3(forward.x, forward.y, forward.z);
				clonedBullet->notify(clonedBullet, "Fire", direction);	
				free(direction);
			}
		}
	}
}

void UER_2Input(Actor *self, NUContData gamepads[4])
{
	if(gamepads[0].button & L_CBUTTONS)
	{
		self->rotationAngle -= 1.0f;
	}
	
	if(gamepads[0].button & R_CBUTTONS)
	{
		self->rotationAngle += 1.0f;
	}
	
	if((gamepads[0].trigger & A_BUTTON))
	{
		UER_2Fire(self);
	}
}

void UER_3Start(Actor *self)
{
    // Called once upon start up.
}

void UER_3Update(Actor *self)
{
    // Called every frame.
}

void UER_3Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_3Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
}

void UER_3Destroy(Actor *self)
{
    // Called when actor is being destroyed.
}

void UER_4Start(Actor *self)
{
    // Called once upon start up.
}

void UER_4Update(Actor *self)
{
    // Called every frame.
}

void UER_4Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_4Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
}

void UER_4Destroy(Actor *self)
{
    // Called when actor is being destroyed.
}

void UER_5Start(Actor *self)
{

}

void UER_5Update(Actor *self)
{

}

void UER_5Input(Actor *self, NUContData gamepads[4])
{

}

void UER_5Collide(Actor *other)
{

}

void UER_6Start(Actor *self)
{
    // Called once upon start up.
}

void UER_6Update(Actor *self)
{
    // Called every frame.
}

void UER_6Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_6Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
}

void UER_6Destroy(Actor *self)
{
    // Called when actor is being destroyed.
}

void UER_7Start(Actor *self)
{
    // Called once upon start up.
}

void UER_7Update(Actor *self)
{
    // Called every frame.
self->rotationAngle = -self->rotationAngle; 

	self->rotationAxis.x = 0;	
	self->rotationAxis.y = 1;
	self->rotationAxis.z = 0;

self->position.x -= 0.02f;
}

void UER_7Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_7Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
    Destroy(self);
}

void UER_8Start(Actor *self)
{
    // Called once upon start up.
}

void UER_8Update(Actor *self)
{
    // Called every frame.
}

void UER_8Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_8Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
    Destroy(self);
}


void UER_9Start(Actor *self)
{
    // Called once upon start up.
}

void UER_9Update(Actor *self)
{
    // Called every frame.
}

void UER_9Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_9Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
    Destroy(self);
}


void UER_10Start(Actor *self)
{
    // Called once upon start up.
}

void UER_10Update(Actor *self)
{
    // Called every frame.
self->rotationAngle = -self->rotationAngle; 
	
	self->rotationAxis.x = 0;	
	self->rotationAxis.y = 1;
	self->rotationAxis.z = 0;

self->position.z -= 0.02f;
}

void UER_10Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_10Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
    Destroy(self);
}


void UER_12Start(Actor *self)
{
    // Called once upon start up.
}

void UER_12Update(Actor *self)
{
    // Called every frame.
self->rotationAngle = -self->rotationAngle; 
	
	self->rotationAxis.x = 0;	
	self->rotationAxis.y = 1;
	self->rotationAxis.z = 0;

self->position.x += 0.02f;
}

void UER_12Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_12Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
    Destroy(self);
}

void UER_13Start(Actor *self)
{
    // Called once upon start up.
}

void UER_13Update(Actor *self)
{
    // Called every frame.
}

void UER_13Input(Actor *self, NUContData gamepads[4])
{
    // Called upon any player input.
}

void UER_13Collide(Actor *self, Actor *other)
{
    // Called upon collision with another actor.
    Destroy(self);
}


void _UER_Start() {
	CVector_Get(_UER_Actors, 0)->update = UER_0Update;
	CVector_Get(_UER_Actors, 0)->input = UER_0Input;
	
	CVector_Get(_UER_Actors, 1)->start = UER_1Start;
	CVector_Get(_UER_Actors, 1)->start(CVector_Get(_UER_Actors, 1));
	CVector_Get(_UER_Actors, 1)->update = UER_1Update;
	
	CVector_Get(_UER_Actors, 2)->input = UER_2Input;
	
	CVector_Get(_UER_Actors, 3)->start = UER_3Start;
	CVector_Get(_UER_Actors, 3)->start(CVector_Get(_UER_Actors, 3));
	CVector_Get(_UER_Actors, 3)->update = UER_3Update;
	CVector_Get(_UER_Actors, 3)->input = UER_3Input;
	CVector_Get(_UER_Actors, 3)->collide = UER_3Collide;
CVector_Get(_UER_Actors, 3)->destroy = UER_3Destroy;

	CVector_Get(_UER_Actors, 4)->start = UER_4Start;
	CVector_Get(_UER_Actors, 4)->start(CVector_Get(_UER_Actors, 4));
	CVector_Get(_UER_Actors, 4)->update = UER_4Update;
	CVector_Get(_UER_Actors, 4)->input = UER_4Input;
	CVector_Get(_UER_Actors, 4)->collide = UER_4Collide;
CVector_Get(_UER_Actors, 4)->destroy = UER_4Destroy;

	CVector_Get(_UER_Actors, 5)->start = UER_5Start;
	CVector_Get(_UER_Actors, 5)->start(CVector_Get(_UER_Actors, 5));
	CVector_Get(_UER_Actors, 5)->update = UER_5Update;
	CVector_Get(_UER_Actors, 5)->input = UER_5Input;
	CVector_Get(_UER_Actors, 5)->collide = UER_5Collide;

	CVector_Get(_UER_Actors, 6)->start = UER_6Start;
	CVector_Get(_UER_Actors, 6)->start(CVector_Get(_UER_Actors, 6));
	CVector_Get(_UER_Actors, 6)->update = UER_6Update;
	CVector_Get(_UER_Actors, 6)->input = UER_6Input;
	CVector_Get(_UER_Actors, 6)->collide = UER_6Collide;
CVector_Get(_UER_Actors, 6)->destroy = UER_6Destroy;

	CVector_Get(_UER_Actors, 7)->start = UER_7Start;
	CVector_Get(_UER_Actors, 7)->start(CVector_Get(_UER_Actors, 7));
	CVector_Get(_UER_Actors, 7)->update = UER_7Update;
	CVector_Get(_UER_Actors, 7)->input = UER_7Input;
	CVector_Get(_UER_Actors, 7)->collide = UER_7Collide;

	CVector_Get(_UER_Actors, 8)->start = UER_8Start;
	CVector_Get(_UER_Actors, 8)->start(CVector_Get(_UER_Actors, 8));
	CVector_Get(_UER_Actors, 8)->update = UER_8Update;
	CVector_Get(_UER_Actors, 8)->input = UER_8Input;
	CVector_Get(_UER_Actors, 8)->collide = UER_8Collide;

	CVector_Get(_UER_Actors, 9)->start = UER_9Start;
	CVector_Get(_UER_Actors, 9)->start(CVector_Get(_UER_Actors, 9));
	CVector_Get(_UER_Actors, 9)->update = UER_9Update;
	CVector_Get(_UER_Actors, 9)->input = UER_9Input;
	CVector_Get(_UER_Actors, 9)->collide = UER_9Collide;

	CVector_Get(_UER_Actors, 10)->start = UER_10Start;
	CVector_Get(_UER_Actors, 10)->start(CVector_Get(_UER_Actors, 10));
	CVector_Get(_UER_Actors, 10)->update = UER_10Update;
	CVector_Get(_UER_Actors, 10)->input = UER_10Input;
	CVector_Get(_UER_Actors, 10)->collide = UER_10Collide;

	
	CVector_Get(_UER_Actors, 12)->start = UER_12Start;
	CVector_Get(_UER_Actors, 12)->start(CVector_Get(_UER_Actors, 12));
	CVector_Get(_UER_Actors, 12)->update = UER_12Update;
	CVector_Get(_UER_Actors, 12)->input = UER_12Input;
	CVector_Get(_UER_Actors, 12)->collide = UER_12Collide;

	CVector_Get(_UER_Actors, 13)->start = UER_13Start;
	CVector_Get(_UER_Actors, 13)->start(CVector_Get(_UER_Actors, 13));
	CVector_Get(_UER_Actors, 13)->update = UER_13Update;
	CVector_Get(_UER_Actors, 13)->input = UER_13Input;
	CVector_Get(_UER_Actors, 13)->collide = UER_13Collide;
}