#include "mon_editor.h"

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
#include "pokemon.h"
#include "gpu_regs.h"

struct PokemonEditorState
{
    MainCallback savedCallback;
    u8 loadState;
    u8 mode;
    u8 monIconSpriteId_1;
    u8 monIconSpriteId_2;
    u8 monIconSpriteId_3;
    u8 monIconSpriteId_4;
    u8 monIconSpriteId_5;
    u8 monIconSpriteId_6;
    u8 partyId;
};

enum WindowIds
{
    WINDOW_0
};

static EWRAM_DATA struct PokemonEditorState *sPokemonEditorState = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

static const struct BgTemplate sPokemonEditorBgTemplates[] =
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

static const struct WindowTemplate sPokemonEditorWindowTemplates[] =
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

static const u32 sPokemonEditorTiles[] = INCBIN_U32("graphics/mon_editor/editor_screen_tiles.4bpp.smol");

static const u32 sPokemonEditorTilemap[] = INCBIN_U32("graphics/mon_editor/editor_screen_tiles.bin.smol");

static const u16 sPokemonEditorPalette[] = INCBIN_U16("graphics/mon_editor/editor_screen_tiles.gbapal");

enum FontColor
{
    FONT_WHITE,
    FONT_RED
};
static const u8 sPokemonEditorWindowFontColors[][3] =
{
    [FONT_WHITE]  = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]    = {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_RED,        TEXT_COLOR_LIGHT_GRAY},
};

// Callbacks for the sample UI
static void PokemonEditor_SetupCB(void);
static void PokemonEditor_MainCB(void);
static void PokemonEditor_VBlankCB(void);

// Sample UI tasks
static void Task_PokemonEditorWaitFadeIn(u8 taskId);
static void Task_PokemonEditorMainInput(u8 taskId);
static void Task_PokemonEditorWaitFadeAndBail(u8 taskId);
static void Task_PokemonEditorWaitFadeAndExitGracefully(u8 taskId);

// Sample UI helper functions
static void PokemonEditor_Init(MainCallback callback);
static void PokemonEditor_ResetGpuRegsAndBgs(void);
static bool8 PokemonEditor_InitBgs(void);
static void PokemonEditor_FadeAndBail(void);
static bool8 PokemonEditor_LoadGraphics(void);
static void PokemonEditor_InitWindows(void);
// static void PokemonEditor_PrintUiWindowText(void);
static void PokemonEditor_FreeResources(void);
static void PokemonEditor_DrawMonIcons(void);

// Declared in mon_editor.h
void Task_OpenPokemonEditor(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        PokemonEditor_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

static void PokemonEditor_Init(MainCallback callback)
{
    sPokemonEditorState = AllocZeroed(sizeof(struct PokemonEditorState));
    if (sPokemonEditorState == NULL)
    {
        SetMainCallback2(callback);
        return;
    }

    sPokemonEditorState->loadState = 0;
    sPokemonEditorState->savedCallback = callback;

    SetMainCallback2(PokemonEditor_SetupCB);
}

// Credit: Jaizu, pret
static void PokemonEditor_ResetGpuRegsAndBgs(void)
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
    // SetGpuReg(REG_OFFSET_DISPCNT, 0);
    // SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON);
    // SetGpuReg(REG_OFFSET_BG3CNT, 0);
    // SetGpuReg(REG_OFFSET_BG2CNT, 0);
    // SetGpuReg(REG_OFFSET_BG1CNT, 0);
    // SetGpuReg(REG_OFFSET_BG0CNT, 0);
    // ChangeBgX(0, 0, BG_COORD_SET);
    // ChangeBgY(0, 0, BG_COORD_SET);
    // ChangeBgX(1, 0, BG_COORD_SET);
    // ChangeBgY(1, 0, BG_COORD_SET);
    // ChangeBgX(2, 0, BG_COORD_SET);
    // ChangeBgY(2, 0, BG_COORD_SET);
    // ChangeBgX(3, 0, BG_COORD_SET);
    // ChangeBgY(3, 0, BG_COORD_SET);
    // SetGpuReg(REG_OFFSET_BLDCNT, 0);
    // SetGpuReg(REG_OFFSET_BLDY, 0);
    // SetGpuReg(REG_OFFSET_BLDALPHA, 0);
    // SetGpuReg(REG_OFFSET_WIN0H, 0);
    // SetGpuReg(REG_OFFSET_WIN0V, 0);
    // SetGpuReg(REG_OFFSET_WIN1H, 0);
    // SetGpuReg(REG_OFFSET_WIN1V, 0);
    // SetGpuReg(REG_OFFSET_WININ, 0);
    // SetGpuReg(REG_OFFSET_WINOUT, 0);
    // CpuFill16(0, (void *)VRAM, VRAM_SIZE);
    // CpuFill32(0, (void *)OAM, OAM_SIZE);
}

static void PokemonEditor_SetupCB(void)
{
    switch (gMain.state)
    {
    case 0:
        PokemonEditor_ResetGpuRegsAndBgs();
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
        if (PokemonEditor_InitBgs())
        {
            sPokemonEditorState->loadState = 0;
            gMain.state++;
        }
        else
        {
            PokemonEditor_FadeAndBail();
            return;
        }
        break;
    case 3:
        if (PokemonEditor_LoadGraphics() == TRUE)
        {
            gMain.state++;
        }
        break;
    case 4:
        PokemonEditor_InitWindows();
        gMain.state++;
        break;
    case 5:
        FreeMonIconPalettes();
        LoadMonIconPalettes();
        
        PokemonEditor_DrawMonIcons();
        CreateTask(Task_PokemonEditorWaitFadeIn, 0);
        gMain.state++;
        break;
    case 6:
        BeginNormalPaletteFade(PALETTES_ALL, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        SetVBlankCallback(PokemonEditor_VBlankCB);
        SetMainCallback2(PokemonEditor_MainCB);
        break;
    }
}

static void PokemonEditor_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void PokemonEditor_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static void Task_PokemonEditorWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_PokemonEditorMainInput;
    }
}

static void Task_PokemonEditorMainInput(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_PokemonEditorWaitFadeAndExitGracefully;
    }
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
    }
}

static void Task_PokemonEditorWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sPokemonEditorState->savedCallback);
        PokemonEditor_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_PokemonEditorWaitFadeAndExitGracefully(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sPokemonEditorState->savedCallback);
        PokemonEditor_FreeResources();
        DestroyTask(taskId);
    }
}
#define TILEMAP_BUFFER_SIZE (1024 * 2)
static bool8 PokemonEditor_InitBgs(void)
{
    ResetAllBgsCoordinates();

    sBg1TilemapBuffer = AllocZeroed(TILEMAP_BUFFER_SIZE);
    if (sBg1TilemapBuffer == NULL)
    {
        return FALSE;
    }

    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sPokemonEditorBgTemplates, NELEMS(sPokemonEditorBgTemplates));

    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);

    ShowBg(0);
    ShowBg(1);

    return TRUE;
}
#undef TILEMAP_BUFFER_SIZE

static void PokemonEditor_FadeAndBail(void)
{
    BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_PokemonEditorWaitFadeAndBail, 0);
    SetVBlankCallback(PokemonEditor_VBlankCB);
    SetMainCallback2(PokemonEditor_MainCB);
}

static bool8 PokemonEditor_LoadGraphics(void)
{
    switch (sPokemonEditorState->loadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sPokemonEditorTiles, 0, 0, 0);
        sPokemonEditorState->loadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            DecompressDataWithHeaderWram(sPokemonEditorTilemap, sBg1TilemapBuffer);
            sPokemonEditorState->loadState++;
        }
        break;
    case 2:
        LoadPalette(sPokemonEditorPalette, BG_PLTT_ID(0), PLTT_SIZE_4BPP);
        LoadPalette(gMessageBox_Pal, BG_PLTT_ID(15), PLTT_SIZE_4BPP);
        sPokemonEditorState->loadState++;
    default:
        sPokemonEditorState->loadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void PokemonEditor_InitWindows(void)
{
    InitWindows(sPokemonEditorWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    FillWindowPixelBuffer(WINDOW_0, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    PutWindowTilemap(WINDOW_0);
    CopyWindowToVram(WINDOW_0, 3);
}

// static const u8 sText_Text1[] = _("Hello, world!");
// static const u8 sText_Text2[] = _("Press {A_BUTTON} to make sounds!");
// static void PokemonEditor_PrintUiWindowText(void)
// {
//     FillWindowPixelBuffer(WINDOW_0, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

//     AddTextPrinterParameterized4(WINDOW_0, FONT_NORMAL, 0, 3, 0, 0,
//         sPokemonEditorWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_Text1);
//     AddTextPrinterParameterized4(WINDOW_0, FONT_SMALL, 0, 15, 0, 0,
//         sPokemonEditorWindowFontColors[FONT_RED], TEXT_SKIP_DRAW, sText_Text2);

//     CopyWindowToVram(WINDOW_0, COPYWIN_GFX);
// }

static void PokemonEditor_FreeResources(void)
{
    if (sPokemonEditorState != NULL)
    {
        Free(sPokemonEditorState);
    }
    if (sBg1TilemapBuffer != NULL)
    {
        Free(sBg1TilemapBuffer);
    }
    FreeAllWindowBuffers();
    ResetSpriteData();
}

static struct Pokemon *ReturnPartyMon()
{
    return &gParties[B_TRAINER_PLAYER][sPokemonEditorState->partyId];
}

static void PokemonEditor_DrawMonIcons(void)
{    
    for (u32 i = 0; i < PARTY_SIZE; i++)
    {
        sPokemonEditorState->partyId = i;
        u32 spriteId = CreateMonIcon(GetMonData(ReturnPartyMon(), MON_DATA_SPECIES), SpriteCB_MonIcon, 20 + 40 * i, 20, 4, 0);
        gSprites[spriteId].oam.priority = 0;
    }
        
}