#include "player_gen.h"
#include "main_menu.h"

#include "gba/types.h"
#include "gba/defines.h"
#include "global.h"
#include "main.h"
#include "bg.h"
#include "text_window.h"
#include "window.h"
#include "constants/characters.h"
#include "palette.h"
#include "task.h"
#include "overworld.h"
#include "malloc.h"
#include "gba/macro.h"
#include "menu_helpers.h"
#include "menu.h"
#include "scanline_effect.h"
#include "sprite.h"
#include "constants/rgb.h"
#include "decompress.h"
#include "constants/songs.h"
#include "sound.h"
#include "sprite.h"
#include "string_util.h"
#include "pokemon_icon.h"
#include "graphics.h"
#include "data.h"
#include "pokedex.h"
#include "gpu_regs.h"

struct PlayerGenState
{
    MainCallback savedCallback;
    u8 loadState;
    u8 mode;
};

enum WindowIds
{
    WINDOW_0
};

static EWRAM_DATA struct PlayerGenState *sPlayerGenState = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

static const struct BgTemplate sPlayerGenBgTemplates[] =
{
    {
        .bg = 0,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    },
    {
        .bg = 1,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    }
};

static const struct WindowTemplate sPlayerGenWindowTemplates[] =
{
    [WINDOW_0] =
    {
        .bg = 0,
        .tilemapLeft = 14,
        .tilemapTop = 0,
        .width = 16,
        .height = 10,
        .paletteNum = 15,
        .baseBlock = 1
    },
    DUMMY_WIN_TEMPLATE
};

static const u32 sPlayerGenTiles[] = INCBIN_U32("graphics/sample_ui/tiles.4bpp.smol");

static const u32 sPlayerGenTilemap[] = INCBIN_U32("graphics/sample_ui/tilemap.bin.smol");

static const u16 sPlayerGenPalette[] = INCBIN_U16("graphics/sample_ui/tiles.gbapal");

enum FontColor
{
    FONT_WHITE,
    FONT_RED
};
static const u8 sPlayerGenWindowFontColors[][3] =
{
    [FONT_WHITE]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]    = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
};

// Callbacks for the sample UI
static void PlayerGen_SetupCB(void);
static void PlayerGen_MainCB(void);
static void PlayerGen_VBlankCB(void);

// Sample UI tasks
static void Task_PlayerGenWaitFadeIn(u8 taskId);
static void Task_PlayerGenMainInput(u8 taskId);
static void Task_PlayerGenWaitFadeAndBail(u8 taskId);
static void Task_PlayerGenWaitFadeAndExitGracefully(u8 taskId);

// Sample UI helper functions
static void PlayerGen_Init(MainCallback callback);
static void PlayerGen_ResetGpuRegsAndBgs(void);
static bool8 PlayerGen_InitBgs(void);
static void PlayerGen_FadeAndBail(void);
static bool8 PlayerGen_LoadGraphics(void);
static void PlayerGen_InitWindows(void);
static void PlayerGen_PrintUiSampleWindowText(void);
static void PlayerGen_FreeResources(void);

void Task_OpenPlayerGen(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        PlayerGen_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

static void PlayerGen_Init(MainCallback callback)
{
    sPlayerGenState = AllocZeroed(sizeof(struct PlayerGenState));
    if (sPlayerGenState == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sPlayerGenState->loadState = 0;
    sPlayerGenState->savedCallback = callback;

    SetMainCallback2(PlayerGen_SetupCB);
}

// Credit: Jaizu, pret
static void PlayerGen_ResetGpuRegsAndBgs(void)
{
    /*
     * TODO : these settings are overkill, and seem to be clearing some
     * important values. I need to come back and investigate this. For now, they
     * are disabled. Note: by not resetting the various BG and GPU regs, we are
     * effectively assuming that the user of this UI is entering from the
     * overworld. If this UI is entered from a different screen, it's possible
     * some regs won't be set correctly. In that case, you'll need to figure
     * out which ones you need.
     */
    SetGpuReg(REG_OFFSET_DISPCNT, 0);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    SetGpuReg(REG_OFFSET_WIN0H, 0);
    SetGpuReg(REG_OFFSET_WIN0V, 0);
    SetGpuReg(REG_OFFSET_WININ, 0);
    SetGpuReg(REG_OFFSET_WINOUT, 0);
    SetGpuReg(REG_OFFSET_BLDCNT, 0);
    SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    SetGpuReg(REG_OFFSET_BLDY, 0);
}

static void PlayerGen_SetupCB(void)
{
    switch (gMain.state)
    {
    case 0:
        PlayerGen_ResetGpuRegsAndBgs();
        SetVBlankHBlankCallbacksToNull();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (PlayerGen_InitBgs())
        {
            sPlayerGenState->loadState = 0;
            gMain.state++;
        }
        else
        {
            PlayerGen_FadeAndBail();
            return;
        }
        break;
    case 3:
        if (PlayerGen_LoadGraphics() == TRUE)
        {
            gMain.state++;
        }
        break;
    case 4:
        PlayerGen_InitWindows();
        gMain.state++;
        break;
    case 5:
        PlayerGen_PrintUiSampleWindowText();
        CreateTask(Task_PlayerGenWaitFadeIn, 0);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        SetVBlankCallback(PlayerGen_VBlankCB);
        SetMainCallback2(PlayerGen_MainCB);
        break;
    }
}

static void PlayerGen_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void PlayerGen_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_PlayerGenWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_PlayerGenMainInput;
    }
}

static void Task_PlayerGenMainInput(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_PlayerGenWaitFadeAndExitGracefully;
    }
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
    }
}

static void Task_PlayerGenWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sPlayerGenState->savedCallback);
        PlayerGen_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_PlayerGenWaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        // SetMainCallback2(sPlayerGenState->savedCallback);
        PlayerGen_FreeResources();
        // DestroyTask(taskId);
    }
    gTasks[taskId].data[0] = 0;
    gTasks[taskId].func = Task_NewGameNoBirchSpeech;
}
#define TILEMAP_BUFFER_SIZE (1024 * 2)
static bool8 PlayerGen_InitBgs(void)
{
    ResetAllBgsCoordinates();

    sBg1TilemapBuffer = AllocZeroed(TILEMAP_BUFFER_SIZE);
    if (sBg1TilemapBuffer == NULL)
    {
        return FALSE;
    }

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sPlayerGenBgTemplates, NELEMS(sPlayerGenBgTemplates));

    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);

    ShowBg(0);
    ShowBg(1);

    return TRUE;
}
#undef TILEMAP_BUFFER_SIZE

static void PlayerGen_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_PlayerGenWaitFadeAndBail, 0);
    SetVBlankCallback(PlayerGen_VBlankCB);
    SetMainCallback2(PlayerGen_MainCB);
}

static bool8 PlayerGen_LoadGraphics(void)
{
    switch (sPlayerGenState->loadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sPlayerGenTiles, 0, 0, 0);
        sPlayerGenState->loadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sPlayerGenTilemap, sBg1TilemapBuffer);
            sPlayerGenState->loadState++;
        }
        break;
    case 2:
        LoadPalette(sPlayerGenPalette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadPalette(gMessageBox_Pal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        sPlayerGenState->loadState++;
    default:
        sPlayerGenState->loadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void PlayerGen_InitWindows(void)
{
    InitWindows(sPlayerGenWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    FillWindowPixelBuffer(WINDOW_0, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    PutWindowTilemap(WINDOW_0);
    CopyWindowToVram(WINDOW_0, 3);
}

static const u8 sText_Text1[] = _("Hello, world!");
static const u8 sText_Text2[] = _("Press {A_BUTTON} to make a sound!");
static void PlayerGen_PrintUiSampleWindowText(void)
{
    FillWindowPixelBuffer(WINDOW_0, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    AddTextPrinterParameterized4(WINDOW_0, FONT_NORMAL, 0, 3, 0, 0,
        sPlayerGenWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_Text1);
    AddTextPrinterParameterized4(WINDOW_0, FONT_SMALL, 0, 15, 0, 0,
        sPlayerGenWindowFontColors[FONT_RED], TEXT_SKIP_DRAW, sText_Text2);

    CopyWindowToVram(WINDOW_0, COPYWIN_GFX);
}

static void PlayerGen_FreeResources(void)
{
    if (sPlayerGenState != NULL)
    {
        Free(sPlayerGenState);
    }
    if (sBg1TilemapBuffer != NULL)
    {
        Free(sBg1TilemapBuffer);
    }
    FreeAllWindowBuffers();
    ResetSpriteData();
}
