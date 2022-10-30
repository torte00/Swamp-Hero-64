Vector _UER_Actors = NULL;
Vector _UER_ActorsPendingRemoval = NULL;
Actor *_UER_ActiveCamera = NULL;

void _UER_Load() {
	_UER_Actors = CVector_Create();
	_UER_ActorsPendingRemoval = CVector_Create();

	CVector_Add(_UER_Actors, CActor_CreateCamera(0, "Main Camera", 1.981367, 1.695547, -2.826313, 0.000000, 0.000000, 0.000000, 0.039565, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 75.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(1, "Bullet", _UER_1_MSegmentRomStart, _UER_1_MSegmentRomEnd, _UER_1_TSegmentRomStart, _UER_1_TSegmentRomEnd, 32, 32, 0.000000, -0.549876, 0.000000, 0.707096, 0.000000, 0.000000, 89.998224, 0.080000, 0.080000, 0.080000, 0.000000, 0.000000, 0.000000, 0.921005, 0.000000, 0.000000, 0.000000, TSphere));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(2, "Turret", _UER_1_MSegmentRomStart, _UER_1_MSegmentRomEnd, _UER_2_TSegmentRomStart, _UER_2_TSegmentRomEnd, 32, 32, 0.000000, 0.000004, -0.747781, 0.000000, 0.000000, 0.000000, 0.039565, 0.506156, 0.400000, 0.400000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateModel(3, "Actor 16", _UER_3_MSegmentRomStart, _UER_3_MSegmentRomEnd, 14.812867, 0.000000, 14.346478, 0.000000, 0.000000, 0.000000, 0.039565, 0.500000, 0.500000, 0.500000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(4, "Actor 17-56ac2", _UER_4_MSegmentRomStart, _UER_4_MSegmentRomEnd, _UER_4_TSegmentRomStart, _UER_4_TSegmentRomEnd, 32, 32, -2.913104, 3.259984, 14.236299, -0.707106, 0.000000, 0.000000, 89.999911, 12.133286, 1.000000, 3.477132, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(5, "Boden", _UER_4_MSegmentRomStart, _UER_4_MSegmentRomEnd, _UER_5_TSegmentRomStart, _UER_5_TSegmentRomEnd, 32, 32, 0.000000, 0.000000, 4.991906, 0.000000, 0.000000, 0.000000, 0.039565, 25.456205, 1.000000, 10.228972, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(6, "Actor 17-97e3a", _UER_4_MSegmentRomStart, _UER_4_MSegmentRomEnd, _UER_6_TSegmentRomStart, _UER_6_TSegmentRomEnd, 32, 32, -2.913104, 8.774500, 15.742676, -0.457059, 0.000000, 0.000000, 54.394942, 12.133286, 1.000000, 2.588391, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(7, "Geist", _UER_7_MSegmentRomStart, _UER_7_MSegmentRomEnd, _UER_7_TSegmentRomStart, _UER_7_TSegmentRomEnd, 32, 32, -1.288734, 0.714825, 8.560961, -0.233120, 0.967286, 0.095865, 183.285130, -1.029074, 1.000000, 1.039447, -0.564049, 1.863029, 0.015450, 0.000000, 1.286292, 1.863029, 0.714020, TBox));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(8, "Gesicht-8eea5", _UER_4_MSegmentRomStart, _UER_4_MSegmentRomEnd, _UER_7_TSegmentRomStart, _UER_7_TSegmentRomEnd, 32, 32, -0.513000, 2.346543, 0.270377, 0.707002, -0.019190, 0.012238, 90.042354, -0.485873, 0.500000, 0.481025, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(9, "Gesicht", _UER_4_MSegmentRomStart, _UER_4_MSegmentRomEnd, _UER_7_TSegmentRomStart, _UER_7_TSegmentRomEnd, 32, 32, -0.513000, 2.346544, 0.270377, 0.707002, -0.019190, 0.012238, 90.042368, -0.485874, 0.500000, 0.481025, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(10, "Geist-34a37", _UER_7_MSegmentRomStart, _UER_7_MSegmentRomEnd, _UER_7_TSegmentRomStart, _UER_7_TSegmentRomEnd, 32, 32, 0.200864, 0.023234, 1.987357, 0.000000, 0.999753, -0.000000, 182.546773, -1.029074, 1.000000, 1.039447, -0.564049, 1.863029, 0.015450, 0.000000, 1.286292, 1.863029, 0.714020, TBox));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(11, "Tank", _UER_1_MSegmentRomStart, _UER_1_MSegmentRomEnd, _UER_2_TSegmentRomStart, _UER_2_TSegmentRomEnd, 32, 32, 0.027624, -1.693200, 2.982915, 0.707104, 0.000000, 0.000000, 89.999542, 1.000000, 1.000000, 1.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(12, "Geist-ee8ee", _UER_7_MSegmentRomStart, _UER_7_MSegmentRomEnd, _UER_7_TSegmentRomStart, _UER_7_TSegmentRomEnd, 32, 32, 4.863650, 0.023234, 9.925661, 0.062004, 0.997497, 0.004856, 176.145123, -1.029074, 1.000000, 1.039447, -0.564049, 1.863029, 0.015450, 0.000000, 1.286292, 1.863029, 0.714020, TBox));

	CVector_Add(_UER_Actors, CActor_CreateTexturedModel(13, "Gesicht-796c2", _UER_4_MSegmentRomStart, _UER_4_MSegmentRomEnd, _UER_7_TSegmentRomStart, _UER_7_TSegmentRomEnd, 32, 32, -0.513000, 2.346542, 0.270377, 0.707002, -0.019190, 0.012238, 90.042354, -0.485873, 0.500000, 0.481025, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, 0.000000, TNone));

	CActor_LinkChildToParent(_UER_Actors, CVector_Get(_UER_Actors, 11), CVector_Get(_UER_Actors, 0));

	CActor_LinkChildToParent(_UER_Actors, CVector_Get(_UER_Actors, 9), CVector_Get(_UER_Actors, 7));

	CActor_LinkChildToParent(_UER_Actors, CVector_Get(_UER_Actors, 8), CVector_Get(_UER_Actors, 10));

	CActor_LinkChildToParent(_UER_Actors, CVector_Get(_UER_Actors, 2), CVector_Get(_UER_Actors, 11));

	CActor_LinkChildToParent(_UER_Actors, CVector_Get(_UER_Actors, 13), CVector_Get(_UER_Actors, 12));
}

void _UER_ActorUpdate(Gfx **display_list, NUContData gamepads[4])
{
    for (int i = 0; i < CVector_Size(_UER_Actors); i++)
    {
        Actor *actor = CVector_Get(_UER_Actors, i);

        if (actor->parent == NULL) 
            CActor_Draw(actor, display_list);

        if (actor->update != NULL) 
            actor->update(actor);

        if (actor->input != NULL) 
            actor->input(actor, gamepads);
    }

    // Handle removal of actors marked as destroyed.
    for (int i = 0; i < CVector_Size(_UER_ActorsPendingRemoval); i++)
    {
        Actor *actorToRemove = CVector_Get(_UER_ActorsPendingRemoval, i);

        for (int j = 0; j < CVector_Size(_UER_Actors); j++)
        {
            Actor *actor = CVector_Get(_UER_Actors, j);

            if (actor->id != actorToRemove->id)
                continue;

            CVector_RemoveAt(_UER_Actors, j);

            // Remove link from parent if any.
            if (actor->parent != NULL)
            {
                for (int k = 0; k < CVector_Size(actor->parent->children); k++)
                {
                    Actor *child = CVector_Get(actor->parent->children, k);

                    if (child->id == actor->id)
                    {
                        CVector_RemoveAt(actor->parent->children, k);
                    }
                }
            }

            break;
        }

        if (actorToRemove->destroy != NULL) 
            actorToRemove->destroy(actorToRemove);

        if (actorToRemove->dynamic != NULL)
            free(actorToRemove->dynamic);

        free(actorToRemove);
    }

    // Clear out vector of actors needing to be removed.
    while (!CVector_IsEmpty(_UER_ActorsPendingRemoval))
    {
        CVector_RemoveAt(_UER_ActorsPendingRemoval, CVector_Size(_UER_ActorsPendingRemoval) - 1);
    }
}
