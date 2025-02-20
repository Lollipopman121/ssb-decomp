#include "article.h"
#include "item.h"
#include "fighter.h"

extern intptr_t Fushigibana_Event;
extern ArticleSpawnData Article_Fushigibana_Data;

void func_ovl3_80184440(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    ArticleHitDesc *hit_desc = (ArticleHitDesc *)((uintptr_t)*Article_Fushigibana_Data.p_file + (intptr_t)&Fushigibana_Event); // Linker thing

    if (ap->at_multi == hit_desc[ap->x340_flag_b0123].timer)
    {
        ap->article_hit.angle = hit_desc[ap->x340_flag_b0123].angle;
        ap->article_hit.damage = hit_desc[ap->x340_flag_b0123].damage;
        ap->article_hit.size = hit_desc[ap->x340_flag_b0123].size;
        ap->article_hit.knockback_scale = hit_desc[ap->x340_flag_b0123].knockback_scale;
        ap->article_hit.knockback_weight = hit_desc[ap->x340_flag_b0123].knockback_weight;
        ap->article_hit.knockback_base = hit_desc[ap->x340_flag_b0123].knockback_base;
        ap->article_hit.element = hit_desc[ap->x340_flag_b0123].element;
        ap->article_hit.clang = hit_desc[ap->x340_flag_b0123].clang;
        ap->article_hit.shield_damage = hit_desc[ap->x340_flag_b0123].shield_damage;
        ap->article_hit.hit_sfx = hit_desc[ap->x340_flag_b0123].hit_sfx;

        ap->x340_flag_b0123++;

        if (ap->x340_flag_b0123 == 2)
        {
            ap->x340_flag_b0123 = 1;
        }
    }
    ap->at_multi++;

    if (ap->at_multi == ATFUSHIGIBANA_RETURN_WAIT)
    {
        Vec3f pos = DObjGetStruct(article_gobj)->translate;

        pos.y = 0.0F;

        func_ovl2_800FF048(&pos, LEFT, 1.0F);
    }
}

bool32 func_ovl3_801845B4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    Vec3f pos;

    joint->translate.x += ap->article_vars.fushigibana.offset.x;
    joint->translate.y += ap->article_vars.fushigibana.offset.y;

    func_ovl3_80184440(article_gobj);

    pos = joint->translate;

    pos.x += ATFUSHIGIBANA_RAZOR_SPAWN_OFF_X;

    if ((ap->article_vars.fushigibana.flags == 2) ||
        ((ap->article_vars.fushigibana.flags & 1) && (joint->unk_dobj_0x7C >= ATFUSHIGIBANA_RAZOR_SPAWN_BEGIN)) &&
        (joint->unk_dobj_0x7C <= ATFUSHIGIBANA_RAZOR_SPAWN_END))
    {
        joint->mobj->index = 1;

        if (!ap->article_vars.fushigibana.razor_spawn_wait)
        {
            func_ovl3_801849EC(article_gobj, &pos);

            ap->article_vars.fushigibana.razor_spawn_wait = ATFUSHIGIBANA_RAZOR_SPAWN_WAIT;

            func_800269C0(0x8CU);

            func_ovl2_800FECBC(&pos);
        }
        if (ap->article_vars.fushigibana.razor_spawn_wait > 0)
        {
            ap->article_vars.fushigibana.razor_spawn_wait--;
        }
    }
    else joint->mobj->index = 0;

    if ((f32)FLOAT_NEG_MAX == joint->unk_dobj_0x74)
    {
        func_ovl2_8010B0B8();

        return TRUE;
    }
    return FALSE;
}

extern ArticleSpawnData Article_Fushigibana_Data;
extern s32 D_ovl2_8012EB60;

GObj *jtgt_ovl3_8018470C(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Fushigibana_Data, pos, vel, flags);
    s32 unused;
    DObj *joint;
    Article_Struct *ap;

    if (article_gobj != NULL)
    {
        ap = ArticleGetStruct(article_gobj);
        joint = DObjGetStruct(article_gobj);

        ap->x340_flag_b0123 = 0;

        ap->at_multi = 0;

        ap->article_vars.fushigibana.razor_spawn_wait = 0;
        ap->article_vars.fushigibana.offset = *pos;

        ap->x2D3_flag_b4 = TRUE;

        ap->article_vars.hitokage.flags = rand_u16_range(4);

        if ((D_ovl2_8012EB60 == ap->article_vars.fushigibana.flags) || (ap->article_vars.fushigibana.flags & D_ovl2_8012EB60))
        {
            ap->article_vars.fushigibana.flags++;

            ap->article_vars.fushigibana.flags &= 3;
        }
        if (ap->article_vars.fushigibana.flags == 2)
        {
            joint->mobj->index = 1;
        }
        D_ovl2_8012EB60 = ap->article_vars.fushigibana.flags;

        func_800269C0(0x228U);
    }
    return article_gobj;
}

bool32 func_ovl3_80184820(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    ip->phys_info.vel.x += ATFUSHIGIBANA_RAZOR_ADD_VEL_X * ip->lr;

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80184874(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_ovl2_800FE6E4(&DObjGetStruct(item_gobj)->translate, ip->item_hit.damage, ip->lr);

    return TRUE;
}

bool32 jtgt_ovl3_801848BC(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);

    func_80019438(&ip->phys_info.vel, &ip->shield_collide_vec, ip->shield_collide_angle * 2);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x) + PI32;
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    if (ip->phys_info.vel.x > 0.0F)
    {
        ip->lr = RIGHT;
    }
    else ip->lr = LEFT;

    return FALSE;
}

bool32 jtgt_ovl3_80184970(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x) + PI32;
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern ItemSpawnData Item_Razor_Data;

GObj *func_ovl3_801849EC(GObj *article_gobj, Vec3f *pos)
{
    GObj *item_gobj = func_ovl3_801655C8(article_gobj, &Item_Razor_Data, pos, ITEM_MASK_SPAWN_ARTICLE);
    DObj *joint;
    Item_Struct *ip;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lr = LEFT;

    ip->phys_info.vel.x = ATFUSHIGIBANA_RAZOR_VEL_X;

    joint = DObjGetStruct(item_gobj);

    joint->translate = *pos;

    ip->lifetime = ATFUSHIGIBANA_RAZOR_LIFETIME;

    return item_gobj;
}
