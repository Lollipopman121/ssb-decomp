#include "article.h"

bool32 jtgt_ovl3_801746F0(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    func_ovl3_80172558(ap, ATHEART_GRAVITY, ATHEART_T_VEL);
    func_ovl3_801713F4(article_gobj);

    return FALSE;
}

bool32 func_ovl3_80174728(GObj *article_gobj)
{
    func_ovl3_801735A0(article_gobj, func_ovl3_801747B4);

    return FALSE;
}

bool32 jtgt_ovl3_80174750(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.1F, 0.0F, func_ovl3_80174780);
}

extern ArticleStatusDesc Article_Heart_Status[];

void func_ovl3_80174780(GObj *article_gobj)
{
    func_ovl3_80172E74(article_gobj);
    func_ovl3_80172EC8(article_gobj, Article_Heart_Status, 0);
}

void func_ovl3_801747B4(GObj *article_gobj)
{
    Article_Struct *ap = ArticleGetStruct(article_gobj);

    ap->is_show_indicator = FALSE;

    func_ovl3_80173F78(ap);
    func_ovl3_80172EC8(article_gobj, Article_Heart_Status, 1);
}

bool32 jtgt_ovl3_801747F8(GObj *article_gobj)
{
    return func_ovl3_80173B24(article_gobj, 0.1F, 0.0F, func_ovl3_80174780);
}

void jtgt_ovl3_80174828(GObj *article_gobj)
{
    func_ovl3_80172EC8(article_gobj, Article_Heart_Status, 2);
}

extern ArticleSpawnData Article_Heart_Data;

GObj *jtgt_ovl3_80174850(GObj *article_gobj, Vec3f *pos, Vec3f *vel, u32 flags)
{
    GObj *spawn_gobj = func_ovl3_8016E174(article_gobj, &Article_Heart_Data, pos, vel, flags);
    DObj *joint;
    Vec3f translate;
    Article_Struct *ap;

    if (spawn_gobj != NULL)
    {
        joint = DObjGetStruct(spawn_gobj);
        ap = ArticleGetStruct(spawn_gobj);
        translate = joint->translate;

        func_80008CC0(joint, 0x2E, 0);

        joint->translate = translate;

        joint->rotate.z = 0.0F;

        ap->x2D3_flag_b5 = TRUE;

        ap->unk_0x348 = func_ovl2_80111EC0(ap);
    }
    return spawn_gobj;
}