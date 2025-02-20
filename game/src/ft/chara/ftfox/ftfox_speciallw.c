#include <game/src/ft/chara/ftfox/ftfox.h>
#include <game/src/it/item/item.h>




void func_ovl3_8015CB80(Fighter_Struct *fp)
{
    if ((fp->input.button_hold & fp->input.button_mask_b) == FALSE)
    {
        fp->status_vars.fox.speciallw.is_release = TRUE;
    }
}

void func_ovl3_8015CBA4(Fighter_Struct *fp)
{
    if (fp->cmd_flags.flag2 != 4)
    {
        if (fp->status_vars.fox.speciallw.reflect_gobj != NULL)
        {
            Item_Struct *ip = ItemGetStruct(fp->status_vars.fox.speciallw.reflect_gobj);

            ip->unk_x1C = fp->cmd_flags.flag2;
        }
        fp->cmd_flags.flag2 = 4;
    }
}

void func_ovl3_8015CBD4(Fighter_Struct *fp)
{
    if (fp->status_vars.fox.speciallw.release_lag != 0)
    {
        fp->status_vars.fox.speciallw.release_lag--;
    }
}

void func_ovl3_8015CBEC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8015CBA4(fp);
    func_ovl3_8015CB80(fp);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        if (fp->ground_or_air == FALSE)
        {
            func_ovl3_8015CD90(fighter_gobj);
        }
        else func_ovl3_8015CDCC(fighter_gobj);
    }
}

void func_ovl3_8015CC64(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    ftCommonAttributes *common_attrs = fp->attributes;
    s32 var;

    var = fp->status_vars.fox.speciallw.gravity_delay;

    if (fp->status_vars.fox.speciallw.gravity_delay != 0)
    {
        fp->status_vars.fox.speciallw.gravity_delay--;
    }
    else
    {
        func_ovl2_800D8D68(fp, 0.8F, common_attrs->fall_speed_max);
    }

    if (func_ovl2_800D8FA8(fp, common_attrs) == FALSE)
    {
        func_ovl2_800D9074(fp, common_attrs);
    }
}

void func_ovl3_8015CCE0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8015CBA4(fp);
    func_ovl3_8015CB80(fp);
    func_ovl3_8015CBD4(fp);

    if ((fp->status_vars.fox.speciallw.release_lag <= 0) && (fp->status_vars.fox.speciallw.is_release != FALSE))
    {
        if (fp->ground_or_air == FALSE)
        {
            func_ovl3_8015D180(fighter_gobj);
        }
        else func_ovl3_8015D1B0(fighter_gobj);
    }
}

void func_ovl3_8015CD5C(GObj *fighter_gobj)
{
    func_ovl3_8015D0CC(fighter_gobj);
}

void func_ovl3_8015CD7C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->is_reflect = TRUE;
}

void func_ovl3_8015CD90(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialLwLoop, 0.0F, 1.0F, 6U);
    func_ovl3_8015CD7C(fighter_gobj);
}

void func_ovl3_8015CDCC(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialAirLwLoop, 0.0F, 1.0F, 6U);
    func_ovl3_8015CD7C(fighter_gobj);
}

void func_ovl3_8015CE08(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if ((fp->status_vars.fox.speciallw.release_lag <= 0) && (fp->status_vars.fox.speciallw.is_release != FALSE))
    {
        if (fp->ground_or_air == ground)
        {
            func_ovl3_8015D180(fighter_gobj);
        }
        else func_ovl3_8015D1B0(fighter_gobj);
    }

    else if (fp->ground_or_air == ground)
    {
        func_ovl3_8015CD90(fighter_gobj);
    }
    else func_ovl3_8015CDCC(fighter_gobj);
}

void func_ovl3_8015CE8C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8015CBA4(fp);
    func_ovl3_8015CB80(fp);
    func_ovl3_8015CBD4(fp);

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl3_8015CE08(fighter_gobj);
    }
}

void func_ovl3_8015CEE8(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->lr = fp->lr_reflect;

    func_ovl2_800E6F24(fighter_gobj, ((fp->ground_or_air == ground) ? ftStatus_Fox_SpecialLwHit : ftStatus_Fox_SpecialAirLwHit), 0.0F, 1.0F, 6U);

    fp->is_reflect = TRUE;
}

void func_ovl3_8015CF50(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    DObj* joint;

    fp->status_vars.fox.speciallw.turn_frames--;

    if ((fp->cmd_flags.flag1 == FALSE) && (fp->status_vars.fox.speciallw.turn_frames < (FTFOX_REFLECTOR_TURN_FRAMES + 1)))
    {
        fp->cmd_flags.flag1 = TRUE;
        fp->lr = (s32)-fp->lr;
    }

    joint = fp->joint[0];
    joint->rotate.y += (-QUART_PI32);

    func_ovl2_800EB528(fp->joint[0]);
}

void func_ovl3_8015CFC0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl3_8015CBA4(fp);
    func_ovl3_8015CB80(fp);
    func_ovl3_8015CBD4(fp);
    func_ovl3_8015CF50(fighter_gobj);

    if (fp->status_vars.fox.speciallw.turn_frames <= 0)
    {
        func_ovl3_8015CE08(fighter_gobj);
    }
}

void func_ovl3_8015D01C(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    fp->is_reflect = TRUE;
    fp->status_vars.fox.speciallw.turn_frames = FTFOX_REFLECTOR_TURN_FRAMES;
    fp->cmd_flags.flag1 = 0;

    func_ovl3_8015CF50(fighter_gobj);
}

void func_ovl3_8015D054(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialLwTurn, 0.0F, 1.0F, 6U);
    func_ovl3_8015D01C(fighter_gobj);
}

void func_ovl3_8015D090(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialAirLwTurn, 0.0F, 1.0F, 6U);
    func_ovl3_8015D01C(fighter_gobj);
}

bool32 func_ovl3_8015D0CC(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    if (func_ovl3_8013E9D0(fighter_gobj) != FALSE)
    {
        if (fp->ground_or_air == ground)
        {
            func_ovl3_8015D054(fighter_gobj);
            return TRUE;
        }
        else func_ovl3_8015D090(fighter_gobj);

        return TRUE;
    }
    else return FALSE;
}

void func_ovl3_8015D130(GObj *fighter_gobj)
{
    func_ovl3_8015CBA4(FighterGetStruct(fighter_gobj));

    if (fighter_gobj->anim_frame <= 0.0F)
    {
        func_ovl2_800E9C3C(fighter_gobj);
        func_ovl2_800DEE54(fighter_gobj);
    }
}

void func_ovl3_8015D180(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialLwEnd, 0.0F, 1.0F, 6U);
}

void func_ovl3_8015D1B0(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialAirLwEnd, 0.0F, 1.0F, 6U);
}

extern u8 ftFox_LoadedFiles_SpecialLwData;
extern void *D_ovl2_80130E94;

void func_ovl3_8015D1E0(GObj *fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);
    GObj *reflect_gobj;

    fp->status_vars.fox.speciallw.release_lag = FTFOX_REFLECTOR_RELEASE_LAG;
    fp->status_vars.fox.speciallw.is_release = FALSE;
    fp->cmd_flags.flag2 = 4;
    fp->status_vars.fox.speciallw.gravity_delay = FTFOX_REFLECTOR_GRAVITY_DELAY;

    reflect_gobj = func_ovl2_80100FA4(fighter_gobj);

    fp->status_vars.fox.speciallw.reflect_gobj = reflect_gobj;

    if (reflect_gobj != NULL)
    {
        fp->x18F_flag_b3 = TRUE;
    }
    fp->special_hit = (SpecialHit *)((uintptr_t)D_ovl2_80130E94 + &ftFox_LoadedFiles_SpecialLwData); // Another linker thing
}

void jtgt_ovl3_8015D250(GObj *fighter_gobj)
{
    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialLwStart, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015D1E0(fighter_gobj);
}

void jtgt_ovl3_8015D290(GObj* fighter_gobj)
{
    Fighter_Struct *fp = FighterGetStruct(fighter_gobj);

    func_ovl2_800E6F24(fighter_gobj, ftStatus_Fox_SpecialAirLwStart, 0.0F, 1.0F, 0U);
    func_ovl2_800E0830(fighter_gobj);
    func_ovl3_8015D1E0(fighter_gobj);

    fp->phys_info.vel_normal.y = 0.0F;
    fp->phys_info.vel_normal.x /= 2;
}