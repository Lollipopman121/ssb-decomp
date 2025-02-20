#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <ssb_types.h>
#include <macros.h>
#include <PR/ultratypes.h>
#include <game/src/sys/obj.h>

typedef struct Effect_Info
{
    u8 filler_0x0[0x4];
    Vec3f translate;
    u8 filler_0x10[0x1C - 0x10];
    Vec3f scale;
    u16 unk_effect_0x28;
    u16 unk_effect_0x2A;
    u8 filler_0x2C[0xB8 - 0x2C];
    u16 unk_effect_0xB8;

} Effect_Info;

typedef struct Effect_Unk
{
    u8 filler_0x0[0x5C];
    Effect_Info *effect_info;

} Effect_Unk;

typedef struct Effect_Struct
{
    s32 unk_0x0;
    GObj *fgobj;
    u8 filler_0x8[0x18 - 0x8];
    s32 lifetime;

} Effect_Struct;

#define EffectGetStruct(effect_gobj) \
((Effect_Struct*)effect_gobj->user_data) \

#endif