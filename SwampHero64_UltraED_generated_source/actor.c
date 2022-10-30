#include <nusys.h>
#include <malloc.h>
#include <string.h>
#include <stdio.h>
#include "upng.h"
#include "actor.h"
#include "util.h"
#include "vector.h"
#include "math.h"

Actor *CActor_CreateModel(int id, const char *name, void *modelStart, void *modelEnd, double positionX, double positionY, double positionZ,
    double rotX, double rotY, double rotZ, double angle, double scaleX, double scaleY, double scaleZ,
    double centerX, double centerY, double centerZ, double radius,
    double extentX, double extentY, double extentZ, enum ColliderType collider)
{
    return CActor_CreateTexturedModel(id, name, modelStart, modelEnd,
        NULL, NULL, 0, 0, positionX, positionY, positionZ, rotX, rotY, rotZ, angle, scaleX, scaleY, scaleZ,
        centerX, centerY, centerZ, radius, extentX, extentY, extentZ, collider);
}

Actor *CActor_CreateTexturedModel(int id, const char *name, void *modelStart, void *modelEnd, void *textureStart, void *textureEnd,
    int textureWidth, int textureHeight, double positionX, double positionY, double positionZ, double rotX,
    double rotY, double rotZ, double angle, double scaleX, double scaleY, double scaleZ,
    double centerX, double centerY, double centerZ, double radius,
    double extentX, double extentY, double extentZ, enum ColliderType collider)
{
    const int modelSize = modelEnd - modelStart;
    const int textureSize = textureEnd - textureStart;

    void *modelBuffer = malloc(modelSize);
    void *textureBuffer = malloc(textureSize);

    // Transfer from ROM the model mesh data and texture.
    CUtil_Rom2Ram(modelStart, modelBuffer, modelSize);
    CUtil_Rom2Ram(textureStart, textureBuffer, textureSize);

    Model *model = (Model *)malloc(sizeof(Model));
    model->texture = NULL;
    model->textureWidth = textureWidth;
    model->textureHeight = textureHeight;

    Actor *actor = (Actor *)model;
    CActor_Init(actor, id, name, TModel, positionX, positionY, positionZ, rotX, rotY, rotZ,
        angle, scaleX, scaleY, scaleZ, centerX, centerY, centerZ, radius, extentX, extentY, extentZ, collider);

    // Read how many vertices for this mesh.
    int vertexCount = 0;
    char *line = (char *)strtok(modelBuffer, "\n");
    sscanf(line, "%i", &vertexCount);
    model->mesh.vertices = (Vtx *)malloc(vertexCount * sizeof(Vtx));
    model->mesh.vertexCount = vertexCount;

    // Gather all of the X, Y, and Z vertex info.
    for (int i = 0; i < vertexCount; i++)
    {
        double x, y, z, r, g, b, a, s, t;
        line = (char *)strtok(NULL, "\n");
        sscanf(line, "%lf %lf %lf %lf %lf %lf %lf %lf %lf", &x, &y, &z, &r, &g, &b, &a, &s, &t);

        model->mesh.vertices[i].v.ob[0] = x * SCALE_FACTOR;
        model->mesh.vertices[i].v.ob[1] = y * SCALE_FACTOR;
        model->mesh.vertices[i].v.ob[2] = -z * SCALE_FACTOR;
        model->mesh.vertices[i].v.flag = 0;
        model->mesh.vertices[i].v.tc[0] = (int)(s * textureWidth) << 5;
        model->mesh.vertices[i].v.tc[1] = (int)(t * textureHeight) << 5;
        model->mesh.vertices[i].v.cn[0] = r * 255;
        model->mesh.vertices[i].v.cn[1] = g * 255;
        model->mesh.vertices[i].v.cn[2] = b * 255;
        model->mesh.vertices[i].v.cn[3] = a * 255;
    }

    free(modelBuffer);

    // Load in the png texture data.
    upng_t *png = upng_new_from_bytes(textureBuffer, textureSize);

    if (png != NULL)
    {
        upng_decode(png);

        if (upng_get_error(png) == UPNG_EOK)
        {
            // Convert texture data from 24bpp to 16bpp in RGB5551 format.
            model->texture = CUtil_Image24To16(upng_get_buffer(png), textureWidth, textureHeight);
        }

        upng_free(png);
    }

    return actor;
}

Actor *CActor_CreateCamera(int id, const char *name, double positionX, double positionY, double positionZ,
    double rotX, double rotY, double rotZ, double angle,
    double centerX, double centerY, double centerZ, double radius,
    double extentX, double extentY, double extentZ, double fov, enum ColliderType collider)
{
    Camera *camera = (Camera *)malloc(sizeof(Camera));
    camera->fov = fov;

    Actor *actor = (Actor *)camera;
    CActor_Init(actor, id, name, TCamera, positionX, positionY, positionZ, rotX, rotY, rotZ,
        angle, 1.0, 1.0, 1.0, centerX, centerY, centerZ, radius, extentX, extentY, extentZ, collider);

    return actor;
}

void CActor_Init(Actor *actor, int id, const char *name, enum ActorType actorType, double positionX, double positionY,
    double positionZ, double rotX, double rotY, double rotZ, double angle, double scaleX,
    double scaleY, double scaleZ, double centerX, double centerY, double centerZ, double radius,
    double extentX, double extentY, double extentZ, enum ColliderType colliderType)
{
    actor->id = id;
    actor->name = name;
    actor->visible = 1;
    actor->type = actorType;
    actor->collider = colliderType;
    actor->parent = NULL;
    actor->children = NULL;
    actor->start = NULL;
    actor->update = NULL;
    actor->input = NULL;
    actor->collide = NULL;
    actor->notify = NULL;
    actor->destroy = NULL;
    actor->dynamic = NULL;

    actor->originalCenter.x = actor->center.x = centerX;
    actor->originalCenter.y = actor->center.y = centerY;
    actor->originalCenter.z = actor->center.z = -centerZ;
    actor->originalRadius = actor->radius = radius;

    actor->originalExtents.x = actor->extents.x = extentX;
    actor->originalExtents.y = actor->extents.y = extentY;
    actor->originalExtents.z = actor->extents.z = extentZ;

    // Entire axis can't be zero or it won't render.
    if (rotX == 0.0 && rotY == 0.0 && rotZ == 0.0) rotZ = 1;

    const int invertScalar = (actorType == TModel ? -1 : 1);

    actor->position.x = positionX;
    actor->position.y = positionY;
    actor->position.z = invertScalar * positionZ;
    actor->scale.x = scaleX;
    actor->scale.y = scaleY;
    actor->scale.z = scaleZ;
    actor->rotationAxis.x = rotX;
    actor->rotationAxis.y = rotY;
    actor->rotationAxis.z = invertScalar * rotZ;
    actor->rotationAngle = invertScalar * angle;
}

void CActor_Draw(Actor *actor, Gfx **displayList)
{
    if (!actor->visible) return;

    const int invertScalar = actor->type == TCamera ? -1 : 1;

    guTranslate(&actor->transform.translation, actor->position.x * SCALE_FACTOR, actor->position.y * SCALE_FACTOR, invertScalar * actor->position.z * SCALE_FACTOR);

    guRotate(&actor->transform.rotation, actor->rotationAngle, invertScalar * actor->rotationAxis.x, invertScalar * actor->rotationAxis.y, actor->rotationAxis.z);

    guScale(&actor->transform.scale, actor->scale.x, actor->scale.y, actor->scale.z);

    gSPMatrix((*displayList)++, OS_K0_TO_PHYSICAL(&actor->transform.translation),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_PUSH);

    gSPMatrix((*displayList)++, OS_K0_TO_PHYSICAL(&actor->transform.rotation),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gSPMatrix((*displayList)++, OS_K0_TO_PHYSICAL(&actor->transform.scale),
        G_MTX_MODELVIEW | G_MTX_MUL | G_MTX_NOPUSH);

    gDPPipeSync((*displayList)++);

    if (actor->type == TModel)
    {
        Model *model = (Model *)actor;

        gDPSetCycleType((*displayList)++, G_CYC_1CYCLE);
        gDPSetRenderMode((*displayList)++, G_RM_AA_ZB_OPA_SURF, G_RM_AA_ZB_OPA_SURF2);
        gSPClearGeometryMode((*displayList)++, 0xFFFFFFFF);
        gSPSetGeometryMode((*displayList)++, G_SHADE | G_SHADING_SMOOTH | G_ZBUFFER | G_CULL_FRONT);

        if (model->texture != NULL)
        {
            gSPTexture((*displayList)++, 0xffff, 0xffff, 0, G_TX_RENDERTILE, G_ON);
            gDPSetTextureFilter((*displayList)++, G_TF_BILERP);
            gDPSetTexturePersp((*displayList)++, G_TP_PERSP);
            gDPSetCombineMode((*displayList)++, G_CC_MODULATERGB, G_CC_MODULATERGB);
            gDPLoadTextureBlock((*displayList)++, model->texture, G_IM_FMT_RGBA, G_IM_SIZ_16b,
                model->textureWidth, model->textureHeight, 0,
                G_TX_WRAP, G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK, G_TX_NOLOD, G_TX_NOLOD);
        }
        else
        {
            gDPSetCombineMode((*displayList)++, G_CC_SHADE, G_CC_SHADE);
        }

        int skip = 0;
        int remainingVertices = model->mesh.vertexCount;
        const int size = 30;

        // Send vertex data in batches.
        while (remainingVertices > 0)
        {
            int take = remainingVertices >= size ? size : remainingVertices;
            gSPVertex((*displayList)++, &(model->mesh.vertices[skip]), take, 0);
            gDPPipeSync((*displayList)++);

            for (int i = 0; i < take / 3; i++)
            {
                gSP1Triangle((*displayList)++, i * 3, i * 3 + 1, i * 3 + 2, 0);
            }

            remainingVertices -= take;
            skip += take;
        }
    }

    if (actor->children != NULL)
    {
        for (int i = 0; i < CVector_Size(actor->children); i++)
        {
            CActor_Draw(CVector_Get(actor->children, i), displayList);
        }
    }

    gSPPopMatrix((*displayList)++, G_MTX_MODELVIEW);
}

void CActor_LinkChildToParent(Vector actors, Actor *child, Actor *parent)
{
    if (parent && child)
    {
        if (parent->children == NULL)
        {
            parent->children = CVector_Create();
        }

        CVector_Add(parent->children, child);

        child->parent = parent;
    }
}

Vector3 CActor_GetPosition(Actor *Actor)
{
    if (Actor == NULL)
        return (Vector3) { 0, 0, 0 };

    if (Actor->parent == NULL)
    {
        const int invertScalar = Actor->type == TCamera ? -1 : 1;

        return (Vector3) { Actor->position.x, Actor->position.y, invertScalar * Actor->position.z };
    }

    return CMath_Vec3MulMat(Actor->position, CActor_GetMatrix(Actor->parent));
}

Mtx CActor_GetMatrix(Actor *Actor)
{
    if (Actor == NULL)
    {
        Mtx mat;
        guMtxIdent(&mat);
        return mat;
    }

    Mtx combined;
    guMtxCatL(&Actor->transform.scale, &Actor->transform.rotation, &combined);

    // Need to rebuild translation matrix since the actor's stored one is scaled up.
    Mtx translation;
    const int invertScalar = Actor->type == TCamera ? -1 : 1;

    guTranslate(&translation, Actor->position.x, Actor->position.y, invertScalar * Actor->position.z);
    guMtxCatL(&combined, &translation, &combined);

    if (Actor->parent == NULL)
    {
        return combined;
    }

    return CMath_MatMulMat(combined, CActor_GetMatrix(Actor->parent));
}

Mtx CActor_GetRotationMatrix(Actor *Actor)
{
    if (Actor == NULL)
    {
        Mtx mat;
        guMtxIdent(&mat);
        return mat;
    }

    if (Actor->parent == NULL)
    {
        return Actor->transform.rotation;
    }

    return CMath_MatMulMat(Actor->transform.rotation, CActor_GetRotationMatrix(Actor->parent));
}

void CActor_UpdateAABB(Actor *Actor)
{
    float center[3] = { Actor->center.x, Actor->center.y, Actor->center.z };
    const float originalCenter[3] = { Actor->originalCenter.x, Actor->originalCenter.y, Actor->originalCenter.z };

    float extents[3] = { Actor->extents.x, Actor->extents.y, Actor->extents.z };
    const float originalExtents[3] = { Actor->originalExtents.x, Actor->originalExtents.y, Actor->originalExtents.z };

    float mat[4][4];
    Mtx fixedMat = CActor_GetMatrix(Actor);
    guMtxL2F(mat, &fixedMat);

    for (int i = 0; i < 3; i++)
    {
        center[i] = 0.0f;
        extents[i] = 0.0f;

        for (int j = 0; j < 3; j++)
        {
            center[i] += mat[j][i] * originalCenter[j];
            extents[i] += fabs(mat[j][i]) * originalExtents[j];
        }
    }

    Actor->center = (Vector3) { center[0], center[1], center[2] };
    Actor->extents = (Vector3) { extents[0], extents[1], extents[2] };
}

void CActor_UpdateSphere(Actor *Actor)
{
    Actor->center = CMath_Vec3MulMat(Actor->originalCenter, Actor->transform.rotation);

    // Scale the calculated radius using the largest scale value of the actor.
    float scaleComps[3] = { fabs(Actor->scale.x), fabs(Actor->scale.y), fabs(Actor->scale.z) };
    float largestScale = 0;

    for (int i = 0; i < 3; i++)
    {
        if (scaleComps[i] > largestScale)
            largestScale = scaleComps[i];
    }

    Actor->radius = largestScale * Actor->originalRadius;
}
