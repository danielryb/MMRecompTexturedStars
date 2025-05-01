#include "global.h"
#include "modding.h"

RECOMP_IMPORT("*", void recomp_set_star_setup_dl(Gfx* g))
RECOMP_IMPORT("*", void recomp_set_star_draw_dl(Gfx* g))

u64 star_texture[] = {
#include "star.ia8.inc.c"
};

Gfx star_setup_dl[] = {
	gsDPSetCombineLERP(TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, PRIMITIVE, 0, TEXEL0, 0, ENVIRONMENT, 0),
    gsDPSetOtherMode(
                    G_AD_DISABLE | G_CD_DISABLE | G_CK_NONE | G_TC_FILT | G_TF_POINT | G_TT_NONE | G_TL_TILE |
                        G_TD_CLAMP | G_TP_NONE | G_CYC_1CYCLE | G_PM_NPRIMITIVE,
                    G_AC_NONE | G_ZS_PRIM | G_RM_AA_XLU_LINE | G_RM_AA_XLU_LINE2),
    gsSPLoadGeometryMode(0),

    gsSPTexture(0xFFFF, 0xFFFF, 0, G_TX_RENDERTILE, G_ON),
    gsDPSetTextureLUT(G_TT_NONE),
    gsDPSetTextureFilter(G_TF_BILERP),
    gsDPLoadTextureBlock(star_texture, G_IM_FMT_IA, G_IM_SIZ_8b, 64, 64, 0,
        G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMIRROR | G_TX_WRAP, G_TX_NOMASK, G_TX_NOMASK,
        G_TX_NOLOD, G_TX_NOLOD),

    gsSPEndDisplayList(),
};

static Vtx star_verts[] = {
    {{{ -2, -2, 0 }, 0, {  0 << 6,  0 << 6 }, { 0, 0, 0, 0xFF }}},
    {{{  2, -2, 0 }, 0, { 64 << 6,  0 << 6 }, { 0, 0, 0, 0xFF }}},
    {{{ -2,  2, 0 }, 0, {  0 << 6, 64 << 6 }, { 0, 0, 0, 0xFF }}},
    {{{  2,  2, 0 }, 0, { 64 << 6, 64 << 6 }, { 0, 0, 0, 0xFF }}}
};

Gfx star_draw_dl[] = {
    gsSPVertex(star_verts, ARRAY_COUNT(star_verts), 0),
    gsSP2Triangles(0, 1, 2, 0x0, 1, 3, 2, 0x0),
    gsSPEndDisplayList(),
};

RECOMP_CALLBACK("*", recomp_on_init) void on_init()
{
    recomp_set_star_setup_dl(star_setup_dl);
    recomp_set_star_draw_dl(star_draw_dl);
}