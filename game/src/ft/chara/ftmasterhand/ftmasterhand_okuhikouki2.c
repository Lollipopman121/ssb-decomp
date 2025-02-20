#include "ftmasterhand.h"

void func_ovl3_801595A0(GObj *fighter_gobj)
{
    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_8010CF20();
        func_ovl3_801597A4(fighter_gobj);
        func_ovl3_80158620(fighter_gobj);
    }
}

void func_ovl3_801595F0(GObj *fighter_gobj)
{
    Fighter_Struct *fp;
    f32 dist_x;
    f32 vel_x;

    func_ovl2_800D938C(fighter_gobj);

    fp = FighterGetStruct(fighter_gobj);

    dist_x = DObjGetStruct(fp->fighter_vars.masterhand.p_masterhand->target_gobj)->translate.x - DObjGetStruct(fighter_gobj)->translate.x;

    if (ABSF(dist_x) > FTMASTERHAND_OKUHIKOUKI_VEL_ADD)
    {
        vel_x = (dist_x > 0.0F) ? FTMASTERHAND_OKUHIKOUKI_VEL_ADD : -FTMASTERHAND_OKUHIKOUKI_VEL_ADD;

        fp->phys_info.vel_normal.x += vel_x;
    }
    else
    {
        fp->phys_info.vel_normal.x += dist_x;
    }
    func_ovl3_80158528(fighter_gobj);
}

void func_ovl3_801596B0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    Vec3f *translate;
    Vec3f sp34;
    Vec3f sp28;

    fp->lr = CENTER;    // Sets LR to zero? ILLEGAL

    func_ovl2_800E6F24(fighter_gobj, ftStatus_MasterHand_Okuhikouki2, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);

    translate = &DObjGetStruct(fighter_gobj)->translate;

    translate->x = fp->status_vars.masterhand.okuhikouki.pos.x + (-9000.0F);
    translate->y = fp->status_vars.masterhand.okuhikouki.pos.y + 6000.0F;
    translate->z = -15000.0F;

    sp34.x = 0.0F;
    sp34.y = 0.0F;
    sp34.z = 0.0F;

    sp28.x = 0.0F;
    sp28.y = 1000.0F;
    sp28.z = 7000.0F;

    func_ovl2_8010D0A4(&sp34, &sp28);
    func_ovl3_80158604(fighter_gobj);
}
