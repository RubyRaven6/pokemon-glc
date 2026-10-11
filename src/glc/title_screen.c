#include "global.h"
#include "config/quickstart.h"
#include "main.h"
#include "gpu_regs.h"
#include "m4a.h"
#include "sound.h"
#include "bg.h"
#include "palette.h"
#include "sprite.h"
#include "window.h"
#include "scanline_effect.h"
#include "decompress.h"
#include "menu.h"
#include "menu_helpers.h"
#include "main_menu.h"
#include "intro.h"
#include "quickstart.h"
#include "glc/title_screen.h"
#include "constants/rgb.h"
#include "constants/songs.h"

enum TitleScreenBackgrounds
{
    TS_BG_MAIN,

    NUM_TS_BACKGROUNDS,
};

enum TitleScreenSpriteTags
{
    PALTAG_TS_MAIN = 0xD00D,
    PALTAG_TS_SHINE,
};

enum TitleScreenSubspriteIds
{
    TS_SUBSPRITE_GAME_TITLE,
};

enum TitleScreenAnimatedSequences
{
    TS_ANIM_PKMN_SHINE,
    TS_ANIM_SHOW_SILHOUETTE,
    TS_ANIM_GLOW_LETTERS,
    TS_ANIM_FINISH,
};

#define tAnimatedSequence_State             data[0]

#define tAnimatedSequence_TotalShines       data[1]
#define tAnimatedSequence_ShineSpriteId     data[2]

#define tAnimatedSequence_BeginPalFade      data[1]
#define tAnimatedSequence_CurrLetter        data[2]
#define tAnimatedSequence_CurrCoeff         data[3]
#define tAnimatedSequence_Speed             data[4]
#define tAnimatedSequence_TargetCoeff       data[5]
#define tAnimatedSequence_FadeOut           data[6]
#define tAnimatedSequence_Delay             data[7]

static void CB2_TitleScreen(void);
static void VBlankCB_TitleScreen(void);

static void Task_TitleScreen_DoAnimatedSequence(u8);
static void Task_TitleScreen_WaitInput(u8);
static void Task_TitleScreen_Exit(u8);

static void SpriteCB_TitleScreen_PkmnShine(struct Sprite *);

static bool32 AnimatedSequence_ShinePkmnLogo(struct Task *);
static bool32 AnimatedSequence_ShowSilhouette(struct Task *);
static bool32 AnimatedSequence_GlowGameTitleLetters(struct Task *);

static void TitleScreenInit_Backgrounds(void);
static void TitleScreenInit_Graphics(void);
static void TitleScreenInit_Sprites(void);

static void TitleScreenHelper_TintSpecificColor(u32, u32, u32);

static const struct BgTemplate sTitleScreen_BgTemplates[NUM_TS_BACKGROUNDS] =
{
    [TS_BG_MAIN] =
    {
        .bg = TS_BG_MAIN,
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .priority = 0,
    },
};

static const u32 sTitleScreen_MainTiles[] = INCGFX_U32("graphics/glc/title_screen/tiles.png", ".4bpp.smol");
static const u16 sTitleScreen_MainPalette[] = INCGFX_U16("graphics/glc/title_screen/tiles.png", ".gbapal");
static const u32 sTitleScreen_MainTilemap[] = INCGFX_U32("graphics/glc/title_screen/tiles.bin", ".smolTM");

static const union AnimCmd *const sTitleScreen_StaticFrameAnims[] =
{
    (const union AnimCmd[]){
        ANIMCMD_FRAME(0, 1),
        ANIMCMD_END
    },
};

static const struct SpriteTemplate sTitleScreen_GameTitleSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALTAG_TS_MAIN,
    .oam = &(const struct OamData){
        .shape = SPRITE_SHAPE(64x32),
        .size = SPRITE_SIZE(64x32),
    },
    .images = &(const struct SpriteFrameImage){
        .data = (const u8[])INCGFX_U8("graphics/glc/title_screen/game_title.png", ".4bpp", "-mwidth 8 -mheight 4"),
        .relativeFrames = TRUE,
        .size = (128 * 32) / 2
    },
    .anims = sTitleScreen_StaticFrameAnims
};

static const struct SpriteTemplate sTitleScreen_PkmnShineSpriteTemplate =
{
    .tileTag = TAG_NONE,
    .paletteTag = PALTAG_TS_SHINE,
    .oam = &(const struct OamData){
        .shape = SPRITE_SHAPE(64x64),
        .size = SPRITE_SIZE(64x64),
        .objMode = ST_OAM_OBJ_WINDOW
    },
    .images = &(const struct SpriteFrameImage){
        .data = (const u8[])INCGFX_U8("graphics/glc/title_screen/logo_shine.png", ".4bpp"),
        .relativeFrames = TRUE,
        .size = (64 * 64) / 2
    },
    .anims = sTitleScreen_StaticFrameAnims,
    .callback = SpriteCB_TitleScreen_PkmnShine
};

#define SUBSPRITE_ENTRY(_x, _y, _dim, _tile, ...) { _x, _y, SPRITE_SHAPE(_dim), SPRITE_SIZE(_dim), _tile, __VA_ARGS__ }
#define SUBSPRITE_TABLE(subsprite) { ARRAY_COUNT(subsprite), subsprite }

static const struct Subsprite sTitleScreen_GameTitleSubsprites[] =
{
    SUBSPRITE_ENTRY(0, 0, 64x32, 0), SUBSPRITE_ENTRY(64, 0, 64x32, 32)
};

static const struct SubspriteTable sTitleScreen_SubspritesTable[] =
{
    [TS_SUBSPRITE_GAME_TITLE] = SUBSPRITE_TABLE(sTitleScreen_GameTitleSubsprites),
};

static bool32 (*const sTitleScreen_AnimatedSequenceFunctions[])(struct Task *) =
{
    [TS_ANIM_PKMN_SHINE]            = AnimatedSequence_ShinePkmnLogo,
    [TS_ANIM_SHOW_SILHOUETTE]       = AnimatedSequence_ShowSilhouette,
    [TS_ANIM_GLOW_LETTERS]          = AnimatedSequence_GlowGameTitleLetters,
};

void CB2_InitGLCTitleScreen(void)
{
    enum InitStates
    {
        STATE_RESET,
        STATE_INIT_BG,
        STATE_INIT_GFX,
        STATE_INIT_SPRITE,
        STATE_FINISH
    };

    switch ((enum InitStates)gMain.state)
    {
    case STATE_RESET:
        FillPalette(RGB_BLACK, 0, PLTT_SIZEOF(512));
        ResetVramOamAndBgCntRegs();
        ResetAllBgsCoordinates();
        SetGpuReg(REG_OFFSET_BLDCNT, 0);
        SetGpuReg(REG_OFFSET_BLDALPHA, 0);
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        FreeAllWindowBuffers();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case STATE_INIT_BG:
        TitleScreenInit_Backgrounds();
        gMain.state++;
        break;
    case STATE_INIT_GFX:
        TitleScreenInit_Graphics();
        gMain.state++;
        break;
    case STATE_INIT_SPRITE:
        TitleScreenInit_Sprites();
        gMain.state++;
        break;
    default:
        m4aSongNumStart(MUS_TITLE);
        CreateTask(Task_TitleScreen_DoAnimatedSequence, 0);
        SetMainCallback2(CB2_TitleScreen);
        SetVBlankCallback(VBlankCB_TitleScreen);
        break;
    }
}

static void CB2_TitleScreen(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void VBlankCB_TitleScreen(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_TitleScreen_DoAnimatedSequence(u8 taskId)
{
    struct Task *task = &gTasks[taskId];

    if (task->tAnimatedSequence_State == TS_ANIM_FINISH
     || JOY_NEW(A_BUTTON))
    {
        if (QUICKSTART && QUICKSTART_HUD)
            CreateQuickstartHud();

        BlendPalettes(PALETTES_ALL, 16, RGB_BLACK);
        ResetPaletteFadeControl();
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_WHITEALPHA);
        task->func = Task_TitleScreen_WaitInput;
        return;
    }
    else if (sTitleScreen_AnimatedSequenceFunctions[task->tAnimatedSequence_State]
          && sTitleScreen_AnimatedSequenceFunctions[task->tAnimatedSequence_State](task))
    {
        enum TitleScreenAnimatedSequences state = ++task->tAnimatedSequence_State;
        memset(task->data, 0, sizeof(task->data));
        task->tAnimatedSequence_State = state;
    }
}

static void Task_TitleScreen_WaitInput(u8 taskId)
{
    if (gPaletteFade.active) return;

    if (QUICKSTART && JOY_NEW(SELECT_BUTTON))
    {
        Quickstart();
        return;
    }

    if (JOY_NEW(A_BUTTON | START_BUTTON))
    {
        FadeOutBGM(4);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITE);
        gTasks[taskId].func = Task_TitleScreen_Exit;
        return;
    }

    if ((gMPlayInfo_BGM.status & 0xFFFF) == 0)
    {
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_WHITEALPHA);
        SetMainCallback2(CB2_InitCopyrightScreenAfterTitleScreen);
        DestroyTask(taskId);
        return;
    }
}

static void Task_TitleScreen_Exit(u8 taskId)
{
    if (gPaletteFade.active) return;

    SetMainCallback2(CB2_InitMainMenu);
    DestroyTask(taskId);
}

static void SpriteCB_TitleScreen_PkmnShine(struct Sprite *sprite)
{
    if (sprite->x2 >= (DISPLAY_WIDTH + 32))
    {
        DestroySprite(sprite);
        return;
    }

    sprite->x2 += 16;
}

static bool32 AnimatedSequence_ShinePkmnLogo(struct Task *task)
{
    if (!task->tAnimatedSequence_TotalShines)
    {
        task->tAnimatedSequence_ShineSpriteId = SPRITE_NONE;
        task->tAnimatedSequence_TotalShines++;
    }

    u32 spriteId = task->tAnimatedSequence_ShineSpriteId;
    if (spriteId == SPRITE_NONE)
    {
        spriteId = CreateSprite(&sTitleScreen_PkmnShineSpriteTemplate, -24 + 32, 0 + 32, 0);
        task->tAnimatedSequence_ShineSpriteId = spriteId;
    }

    return !gSprites[spriteId].inUse;
}

static bool32 AnimatedSequence_ShowSilhouette(struct Task *task)
{
    if (!task->tAnimatedSequence_BeginPalFade)
    {
        BeginNormalPaletteFade(PALETTES_ALL ^ ((1 << 1) | (0x10000 << IndexOfSpritePaletteTag(PALTAG_TS_MAIN))), 16, 16, 13, RGB_BLACK);
        task->tAnimatedSequence_BeginPalFade = TRUE;
    }

    return !gPaletteFade.active;
}

static bool32 AnimatedSequence_GlowGameTitleLetters(struct Task *task)
{
    if (task->tAnimatedSequence_CurrLetter > 3)
        return TRUE;

    if (--task->tAnimatedSequence_Delay > 0)
        return FALSE;

    if (!task->tAnimatedSequence_BeginPalFade)
    {
        task->tAnimatedSequence_CurrCoeff = 16 * !task->tAnimatedSequence_FadeOut;
        task->tAnimatedSequence_TargetCoeff = 16 * task->tAnimatedSequence_FadeOut;
        task->tAnimatedSequence_Speed = -1 + (task->tAnimatedSequence_FadeOut * 2);
        task->tAnimatedSequence_BeginPalFade = TRUE;
    }

    u32 palOffset = OBJ_PLTT_ID(IndexOfSpritePaletteTag(PALTAG_TS_MAIN));
    TitleScreenHelper_TintSpecificColor(palOffset + 12 + task->tAnimatedSequence_CurrLetter, task->tAnimatedSequence_CurrCoeff, RGB_BLACK);

    task->tAnimatedSequence_CurrCoeff += task->tAnimatedSequence_Speed;
    if (task->tAnimatedSequence_CurrCoeff == task->tAnimatedSequence_TargetCoeff)
    {
        task->tAnimatedSequence_CurrLetter += task->tAnimatedSequence_FadeOut;
        task->tAnimatedSequence_FadeOut ^= 1;
        task->tAnimatedSequence_Delay = task->tAnimatedSequence_FadeOut * 8;
        task->tAnimatedSequence_BeginPalFade = FALSE;
    }

    return FALSE;
}

static void TitleScreenInit_Backgrounds(void)
{
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sTitleScreen_BgTemplates, NUM_TS_BACKGROUNDS);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WIN1H, 0);
    SetGpuReg(REG_OFFSET_WIN1V, 0);
    SetGpuReg(REG_OFFSET_WININ, WININ_WIN0_BG_ALL | WININ_WIN1_BG_ALL | WININ_WIN1_OBJ);
    SetGpuReg(REG_OFFSET_WINOUT, WINOUT_WIN01_BG_ALL | WINOUT_WIN01_OBJ | WINOUT_WINOBJ_ALL);
    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT1_BG0 | BLDCNT_EFFECT_LIGHTEN);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 12);
    SetGpuRegBits(REG_OFFSET_DISPCNT, DISPCNT_OBJ_1D_MAP
                                | DISPCNT_OBJ_ON
                                | DISPCNT_WIN0_ON
                                | DISPCNT_OBJWIN_ON);

    for (enum TitleScreenBackgrounds bg = 0; bg < NUM_TS_BACKGROUNDS; bg++)
    {
        ScheduleBgCopyTilemapToVram(bg);
        ShowBg(bg);
    }
}

static void TitleScreenInit_Graphics(void)
{
    FreeTempTileDataBuffersIfPossible();
    ResetTempTileDataBuffers();

    DecompressAndLoadBgGfxUsingHeap(TS_BG_MAIN, sTitleScreen_MainTiles, 0, 0, 0);
    SetBackdropFromColor(RGB_WHITE);
    LoadPalette(sTitleScreen_MainPalette, BG_PLTT_ID(1), PLTT_SIZE_4BPP);
    DecompressDataWithHeaderVram(sTitleScreen_MainTilemap, (void *)BG_SCREEN_ADDR(sTitleScreen_BgTemplates[TS_BG_MAIN].mapBaseIndex));

    LoadSpritePalettes(
        (const struct SpritePalette[]){
            { sTitleScreen_MainPalette, PALTAG_TS_MAIN },
            { sTitleScreen_MainPalette, PALTAG_TS_SHINE },
            { NULL, TAG_NONE },
        });

    BlendPalettes(PALETTES_ALL ^ (0x10000 << IndexOfSpritePaletteTag(PALTAG_TS_SHINE)), 16, RGB_BLACK);
}

static void TitleScreenInit_Sprites(void)
{
    u32 spriteId = CreateSprite(&sTitleScreen_GameTitleSpriteTemplate, 112, 58, 0);
    if (spriteId == SPRITE_NONE)
        return;

    SetSubspriteTables(&gSprites[spriteId], &sTitleScreen_SubspritesTable[TS_SUBSPRITE_GAME_TITLE]);
}

static void TitleScreenHelper_TintSpecificColor(u32 palOffset, u32 coeff, u32 color)
{
    coeff *= 2;

    s32 newR = (color << 27) >> 27;
    s32 newG = (color << 22) >> 27;
    s32 newB = (color << 17) >> 27;

    u32 srcColor = gPlttBufferUnfaded[palOffset];
    s32 r = (srcColor << 27) >> 27;
    s32 g = (srcColor << 22) >> 27;
    s32 b = (srcColor << 16) >> 26;

    gPlttBufferFaded[palOffset] = ((r + (((newR - r) * (s32)coeff) >> 5)) << 0)
                                | ((g + (((newG - g) * (s32)coeff) >> 5)) << 5)
                                | ((b + (((newB - (b & 31)) * (s32)coeff) >> 5)) << 10);
}
