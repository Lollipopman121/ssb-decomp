#include "article.h"
#include "item.h"
#include "fighter.h"

void func_ovl3_80180630(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (ap->article_vars.kamex.hydro_spawn_wait <= 0)
    {
        Vec3f pos = joint->translate;

        if (ap->at_kind == At_Kind_Kamex)
        {
            pos.x += ATKAMEX_KAMEX_HYDRO_SPAWN_OFF_X * ap->lr;
            pos.y += ATKAMEX_KAMEX_HYDRO_SPAWN_OFF_Y;
        }
        else pos.x += ATKAMEX_OTHER_HYDRO_SPAWN_OFF_X * ap->lr;

        func_ovl3_80180F9C(article_gobj, &pos);
        func_ovl2_801001A8(&pos, ap->lr);
        func_800269C0(0x87U);

        ap->article_vars.kamex.hydro_spawn_wait = rand_u16_range(ATKAMEX_HYDRO_SPAWN_WAIT_RANDOM) + ATKAMEX_HYDRO_SPAWN_WAIT_CONST;

        pos = joint->translate;

        pos.y += ap->attributes->objectcoll_bottom;

        if (ap->at_kind == At_Kind_Kamex)
        {
            pos.x += (ap->attributes->objectcoll_width + ATKAMEX_DUST_SPAWN_OFF_X) * -ap->lr;
        }
        ap->article_vars.kamex.is_apply_push = TRUE;

        ap->phys_info.vel.x = -ap->lr * ATKAMEX_CONST_VEL_X;

        func_ovl2_800FF278(&pos, -ap->lr);
    }
}

bool32 jtgt_ovl3_801807DC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATKAMEX_GRAVITY, ATKAMEX_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80180808(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_801737B8(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL));

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        func_ovl3_80180A58(article_gobj, TRUE);
        func_ovl3_80180AF4(article_gobj);
    }
    return FALSE;
}

void func_ovl3_80180860(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80173F78(ap);

    ap->phys_info.vel.y = 0.0F;
    ap->phys_info.vel.x = 0.0F;

    ap->is_show_indicator = FALSE;

    ap->article_vars.kamex.hydro_push_vel_x = 0.0F;
}

extern ArticleStatusDesc Article_Kamex_Status[];

void func_ovl3_801808A4(GObj *article_gobj)
{
    func_ovl3_80180860(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Kamex_Status, 0);
}

bool32 jtgt_ovl3_801808D8(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATKAMEX_GRAVITY, ATKAMEX_T_VEL);

    return FALSE;
}

bool32 jtgt_ovl3_80180904(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_801737B8(article_gobj, (MPCOLL_MASK_CEIL | MPCOLL_MASK_LWALL | MPCOLL_MASK_RWALL));

    if (ap->coll_data.coll_mask & MPCOLL_MASK_GROUND)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_80180A58(article_gobj, FALSE);
        func_ovl3_80180AF4(article_gobj);
    }
    return FALSE;
}

void func_ovl3_80180964(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->at_multi = ATKAMEX_LIFETIME;

    if (ap->at_kind == At_Kind_Kamex)
    {
        func_800269C0(0x139U);
    }
    func_ovl3_80172EC8(article_gobj, Article_Kamex_Status, 1);
}

bool32 jtgt_ovl3_801809BC(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        return TRUE;
    }
    func_ovl3_80180630(article_gobj);

    if (ap->article_vars.kamex.is_apply_push != FALSE)
    {
        ap->phys_info.vel.x += ap->article_vars.kamex.hydro_push_vel_x;
    }
    ap->article_vars.kamex.hydro_spawn_wait--;

    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80180A30(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_801808A4);

    return FALSE;
}

extern intptr_t D_NF_0000EA60;
extern intptr_t D_NF_0000ED60;

void func_ovl3_80180A58(GObj *article_gobj, bool32 is_setup_vars)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);

    if (is_setup_vars == FALSE)
    {
        ap->at_multi = ATKAMEX_LIFETIME;

        if (ap->at_kind == At_Kind_Kamex)
        {
            void *dl = ArticleGetPData(ap, D_NF_0000EA60, D_NF_0000ED60); // Linker thing

            joint->display_list = dl;

            ap->coll_data.object_coll.top = ATKAMEX_COLL_SIZE;
            ap->coll_data.object_coll.center = 0.0F;
            ap->coll_data.object_coll.bottom = -ATKAMEX_COLL_SIZE;
            ap->coll_data.object_coll.width = ATKAMEX_COLL_SIZE;
        }
    }
    ap->phys_info.vel.y = 0;
    ap->phys_info.vel.x = 0;

    ap->article_vars.kamex.hydro_push_vel_x = ap->lr * ATKAMEX_PUSH_VEL_X;
    ap->article_vars.kamex.hydro_spawn_wait = 0;
    ap->article_vars.kamex.is_apply_push = FALSE;
}

void func_ovl3_80180AF4(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Kamex_Status, 2);
}

bool32 jtgt_ovl3_80180B1C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (ap->at_multi == 0)
    {
        ap->phys_info.vel.y = 0.0F;

        func_ovl3_80180964(article_gobj);
    }
    ap->at_multi--;

    return FALSE;
}

bool32 jtgt_ovl3_80180B6C(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    if (func_ovl3_801737B8(article_gobj, MPCOLL_MASK_GROUND) != FALSE)
    {
        ap->phys_info.vel.y = 0.0F;
    }
    return FALSE;
}

void func_ovl3_80180BAC(GObj *article_gobj)
{
    GObj *fighter_gobj = gOMObjCommonLinks[GObjLinkIndex_Fighter];
    s32 unused1;
    GObj *victim_gobj;
    s32 unused2[3];
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    DObj *joint = DObjGetStruct(article_gobj);
    f32 dist_xy;
    f32 dist_x;
    Vec3f dist;
    f32 square_xy;
    s32 ft_count = 0;

    if (fighter_gobj != NULL)
    {
        do
        {
            Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

            if ((fighter_gobj != ap->owner_gobj) && (fp->team != ap->team))
            {
                vec3f_sub(&dist, &DObjGetStruct(fighter_gobj)->translate, &joint->translate);

                if (ft_count == 0)
                {
                    dist_xy = SQUARE(dist.x) + SQUARE(dist.y);
                }
                ft_count++;

                square_xy = SQUARE(dist.x) + SQUARE(dist.y);

                if (square_xy <= dist_xy)
                {
                    dist_xy = square_xy;

                    victim_gobj = fighter_gobj;
                }
            }
            fighter_gobj = fighter_gobj->group_gobj_next;
        } 
        while (fighter_gobj != NULL);
    }
    dist_x = DObjGetStruct(victim_gobj)->translate.x - joint->translate.x;

    ap->lr = (dist_x < 0.0F) ? LEFT : RIGHT;
}

extern intptr_t D_NF_00013624;
extern ArticleSpawnData Article_Kamex_Data;

GObj *jtgt_ovl3_80180CDC(GObj *spawn_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *article_gobj = func_ovl3_8016E174(spawn_gobj, &Article_Kamex_Data, pos, vel, flags);
    DObj *joint;
    Article_Struct *kamex_ap;
    Article_Struct *m_ball_ap;

    if (article_gobj != NULL)
    {
        joint = DObjGetStruct(article_gobj);

        func_80008CC0(joint, 0x48U, 0U);

        joint->translate = *pos;

        kamex_ap = ArticleGetStruct(article_gobj);

        kamex_ap->at_multi = ATMONSTER_RISE_STOP_WAIT;

        kamex_ap->phys_info.vel.z = 0.0F;
        kamex_ap->phys_info.vel.x = 0.0F;
        kamex_ap->phys_info.vel.y = ATMONSTER_RISE_VEL_Y;

        m_ball_ap = ArticleGetStruct(spawn_gobj);

        kamex_ap->owner_gobj = m_ball_ap->owner_gobj;
        kamex_ap->team = m_ball_ap->team;

        func_ovl3_80180BAC(article_gobj);

        if (kamex_ap->lr == LEFT)
        {
            joint->rotate.y = PI32;
        }
        joint->translate.y -= kamex_ap->attributes->objectcoll_bottom;

        func_8000BD1C(joint, ArticleGetPData(kamex_ap, D_NF_0000EA60, D_NF_00013624), 0.0F); // Linker thing
    }
    return article_gobj;
}

bool32 func_ovl3_80180E10(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    DObj *joint = DObjGetStruct(item_gobj);

    ip->item_hit.offset[0].x = joint->next->translate.x * ip->lr;

    if (func_ovl3_80167FE8(ip) != FALSE)
    {
        return TRUE;
    }
    else return FALSE;
}

bool32 jtgt_ovl3_80180E60(GObj *item_gobj)
{
    return FALSE;
}

bool32 jtgt_ovl3_80180E6C(GObj *item_gobj)
{
    Item_Struct *ip = ItemGetStruct(item_gobj);
    Fighter_Struct *fp = FighterGetStruct(ip->owner_gobj);

    func_ovl3_801680EC(ip, fp);

    DObjGetStruct(item_gobj)->rotate.z = atan2f(ip->phys_info.vel.y, ip->phys_info.vel.x);
    DObjGetStruct(item_gobj)->scale.x = 1.0F;

    ip->lr = -ip->lr;

    return FALSE;
}

extern ItemSpawnData Item_Hydro_Data;

GObj *func_ovl3_80180EDC(GObj *article_gobj, Vec3f *pos)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);
    GObj *item_gobj = func_ovl3_801655C8(article_gobj, &Item_Hydro_Data, pos, ITEM_MASK_SPAWN_ARTICLE);
    DObj *joint;
    s32 unused;
    Item_Struct *ip;
    Vec3f translate;

    if (item_gobj == NULL)
    {
        return NULL;
    }
    ip = ItemGetStruct(item_gobj);

    ip->lr = ap->lr;

    joint = DObjGetStruct(item_gobj);

    translate = joint->translate;

    func_ovl2_8010066C(&translate, 1.0F);

    if (ip->lr == LEFT)
    {
        joint->rotate.y = PI32;
    }
    ip->item_vars.hydro.unk_0x0 = 0; // Set but never used?
    ip->item_vars.hydro.unk_0x4 = 0; // Set but never used?

    ip->lifetime = ATKAMEX_HYDRO_LIFETIME;

    return item_gobj;
}

void func_ovl3_80180F9C(GObj *article_gobj, Vec3f *pos)
{
    func_ovl3_80180EDC(article_gobj, pos);
}