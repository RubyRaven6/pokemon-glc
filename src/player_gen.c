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
#include "random.h"
#include "naming_screen.h"
#include "field_weather.h"

struct PlayerGenState
{
    MainCallback savedCallback;
    u8 loadState;
    u8 mode;
};

enum BgIds
{
    BG_TEXT = 0,
    BG_ONE,
    BG_COUNT,
};

enum WindowIds
{
    WINDOW_TEXT = 0,
    WINDOW_COUNT,
};

static EWRAM_DATA struct PlayerGenState *sPlayerGenState = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

static const struct BgTemplate sPlayerGenBgTemplates[] =
{
    {
        .bg = BG_TEXT,
        .charBaseIndex = 0,
        .mapBaseIndex = 31,
        .priority = 1
    },
    {
        .bg = BG_ONE,
        .charBaseIndex = 3,
        .mapBaseIndex = 30,
        .priority = 2
    }
};

static const struct WindowTemplate sPlayerGenWindowTemplates[] =
{
    [WINDOW_TEXT] =
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


static const struct WindowTemplate sPlayerGenTextWindows[] =
{
    {
        .bg = 0,
        .tilemapLeft = 2,
        .tilemapTop = 15,
        .width = 27,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 1
    },
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 5,
        .width = 6,
        .height = 4,
        .paletteNum = 15,
        .baseBlock = 0x6D
    },
    {
        .bg = 0,
        .tilemapLeft = 3,
        .tilemapTop = 2,
        .width = 9,
        .height = 10,
        .paletteNum = 15,
        .baseBlock = 0x85
    },
    DUMMY_WIN_TEMPLATE
};

static const u32 sPlayerGenTiles[] = INCBIN_U32("graphics/player_gen/tiles.4bpp.smol");

static const u32 sPlayerGenTilemap[] = INCBIN_U32("graphics/player_gen/tilemap.bin.smol");

static const u16 sPlayerGenPalette[] = INCBIN_U16("graphics/player_gen/tiles.gbapal");

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

static const struct MenuAction sMenuActions_Gender[] = {
    {COMPOUND_STRING("Masculine"), {NULL}},
    {COMPOUND_STRING("Feminine"), {NULL}},
    {COMPOUND_STRING("Androgynous"), {NULL}},
};

static const u8 *const sMascPresetNames[] = {
    COMPOUND_STRING("Brendan"),
    COMPOUND_STRING("Damien"),
};

static const u8 *const sFemmePresetNames[] = {
    COMPOUND_STRING("May"),
    COMPOUND_STRING("Bridget"),
};

static const u8 *const sAndroPresetNames[] = {
    COMPOUND_STRING("Kris"),
    COMPOUND_STRING("Nimona")
};

// The number of male vs. female names is assumed to be the same.
// If they aren't, the smaller of the two sizes will be used and any extra names will be ignored.
#define NUM_PRESET_NAMES_MF min(ARRAY_COUNT(sMascPresetNames), ARRAY_COUNT(sFemmePresetNames))
#define NUM_PRESET_NAMES min(NUM_PRESET_NAMES_MF, ARRAY_COUNT(sAndroPresetNames))

// Callbacks for the sample UI
static void PlayerGen_SetupCB(void);
static void PlayerGen_MainCB(void);
static void PlayerGen_VBlankCB(void);
static void PlayerGen_Init(MainCallback callback);
static void PlayerGen_ResetGpuRegsAndBgs(void);
static void PlayerGen_FadeAndBail(void);
static void PlayerGen_InitWindows(void);
static void PlayerGen_PrintUiSampleWindowText(void);
static void PlayerGen_FreeResources(void);
static inline void PlayerGen_PrintMessageBox(const u8 *str);
static void PlayerGen_Init(MainCallback callback);
static void PlayerGen_ResetGpuRegsAndBgs(void);
static void PlayerGen_SetupCB(void);
static void PlayerGen_MainCB(void);
static void PlayerGen_VBlankCB(void);
static void PlayerGen_FadeAndBail(void);
static void PlayerGen_InitWindows(void);
static void PlayerGen_PrintUiSampleWindowText(void);
static inline void PlayerGen_PrintMessageBox(const u8 *str);
static void PlayerGen_FreeResources(void);
static void PlayerGen_ShowGenderMenu(void);
static void PlayerGen_ClearGenderWindowTilemap(u8 bg, u8 x, u8 y, u8 width, u8 height, u8 unused);
static void PlayerGen_ClearGenderWindow(u8 windowId, bool8 copyToVram);
static void PlayerGen_StartFadeInTarget1OutTarget2(u8 taskId, u8 delay);
static void PlayerGen_ClearWindow(u8 windowId);
static s8 PlayerGen_ProcessGenderMenuInput(void);
static void DrawMainMenuWindowBorder(const struct WindowTemplate *, u16);

// Sample UI tasks
static void Task_PlayerGen_WaitFadeIn(u8 taskId);
static void Task_PlayerGen_StartPlayerFadeIn(u8 taskId);
static void Task_PlayerGen_WaitForPlayerFadeIn(u8 taskId);
static void Task_PlayerGen_BoyOrGirl(u8 taskId);
static void Task_PlayerGen_WaitToShowGenderMenu(u8 taskId);
static void Task_PlayerGen_ChooseGender(u8 taskId);
static void Task_PlayerGen_SlideOutOldGenderSprite(u8 taskId);
static void Task_PlayerGen_SlideInNewGenderSprite(u8 taskId);
static void Task_PlayerGen_MainInput(u8 taskId);
static void Task_PlayerGen_WaitFadeAndBail(u8 taskId);
static void Task_PlayerGen_WaitFadeAndExitGracefully(u8 taskId);
static void Task_PlayerGen_FadeInTarget1OutTarget2(u8 taskId);

// Sample UI helper functions
static void PlayerGen_Init(MainCallback callback);;
static void PlayerGen_ResetGpuRegsAndBgs(void);;
static bool8 PlayerGen_InitBgs(void);
static void PlayerGen_FadeAndBail(void);;
static bool8 PlayerGen_LoadGraphics(void);
static void PlayerGen_InitWindows(void);;
static void PlayerGen_PrintUiSampleWindowText(void);;
static void PlayerGen_FreeResources(void);;
static inline void PlayerGen_PrintMessageBox(const u8 *str);;

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
        CreateTask(Task_PlayerGen_WaitFadeIn, 0);
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

#define tPlayerSpriteId data[2]
#define tTimer data[3]
#define tIsDoneFadingSprites data[4]
#define tPlayerGender data[5]
#define tBrendanSpriteId data[6]
#define tMaySpriteId data[7]
#define tKrisSpriteId data[8]

static void Task_PlayerGen_WaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        gTasks[taskId].func = Task_PlayerGen_MainInput;
    }
}

static void Task_PlayerGen_MainInput(u8 taskId)
{
    if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_PC_OFF);
        BeginNormalPaletteFade(PALETTES_ALL, 0, 0, 16, RGB_BLACK);
        gTasks[taskId].func = Task_PlayerGen_StartPlayerFadeIn;
    }
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
    }
}

static void Task_PlayerGen_StartPlayerFadeIn(u8 taskId)
{
    if (gTasks[taskId].tTimer)
    {
        gTasks[taskId].tTimer--;
    }
    else
    {
        u8 spriteId = gTasks[taskId].tKrisSpriteId;

        gSprites[spriteId].x = 180;
        gSprites[spriteId].y = 60;
        gSprites[spriteId].invisible = FALSE;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        gTasks[taskId].tPlayerSpriteId = spriteId;
        gTasks[taskId].tPlayerGender = GENDER_FEMININE;
        PlayerGen_StartFadeInTarget1OutTarget2(taskId, 2);
        gTasks[taskId].func = Task_PlayerGen_WaitForPlayerFadeIn;
    }
}

static void Task_PlayerGen_WaitForPlayerFadeIn(u8 taskId)
{
    if (gTasks[taskId].tIsDoneFadingSprites)
    {
        gSprites[gTasks[taskId].tPlayerSpriteId].oam.objMode = ST_OAM_OBJ_NORMAL;
        gTasks[taskId].func = Task_PlayerGen_BoyOrGirl;
    }
}

static void Task_PlayerGen_BoyOrGirl(u8 taskId)
{
    PlayerGen_ClearWindow(0);
    StringExpandPlaceholders(gStringVar4, COMPOUND_STRING("Choose your presentation."));
    AddTextPrinterForMessage(TRUE);
    gTasks[taskId].func = Task_PlayerGen_WaitToShowGenderMenu;
}

static void Task_PlayerGen_WaitToShowGenderMenu(u8 taskId)
{
    if (!RunTextPrintersAndIsPrinter0Active())
    {
        PlayerGen_ShowGenderMenu();
        gTasks[taskId].func = Task_PlayerGen_ChooseGender;
    }
}

static void Task_PlayerGen_ChooseGender(u8 taskId)
{
    enum PlayerGender gender = PlayerGen_ProcessGenderMenuInput();
    enum PlayerGender gender2;

    switch (gender)
    {
    case GENDER_MASCULINE:
        PlaySE(SE_SELECT);
        gSaveBlock2Ptr->playerGender = gender;
        PlayerGen_ClearGenderWindow(1, 1);
        gTasks[taskId].func = Task_PlayerGen_WaitFadeAndExitGracefully;
        break;
    case GENDER_FEMININE:
        PlaySE(SE_SELECT);
        gSaveBlock2Ptr->playerGender = gender;
        PlayerGen_ClearGenderWindow(1, 1);
        gTasks[taskId].func = Task_PlayerGen_WaitFadeAndExitGracefully;
        break;
    case GENDER_ANDROGYNOUS:
        PlaySE(SE_SELECT);
        gSaveBlock2Ptr->playerGender = gender;
        PlayerGen_ClearGenderWindow(1, 1);
        gTasks[taskId].func = Task_PlayerGen_WaitFadeAndExitGracefully;
        break;
    default: //repeat task if nothing is selected
        break;
    }
    gender2 = Menu_GetCursorPos();
    if (gender2 != gTasks[taskId].tPlayerGender)
    {
        gTasks[taskId].tPlayerGender = gender2;
        gSprites[gTasks[taskId].tPlayerSpriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        PlayerGen_StartFadeInTarget1OutTarget2(taskId, 0);
        gTasks[taskId].func = Task_PlayerGen_SlideOutOldGenderSprite;
    }
}

static void Task_PlayerGen_SlideOutOldGenderSprite(u8 taskId)
{
    u8 spriteId = gTasks[taskId].tPlayerSpriteId;
    if (gTasks[taskId].tIsDoneFadingSprites == 0)
    {
        gSprites[spriteId].x += 4;
    }
    else
    {
        gSprites[spriteId].invisible = TRUE;
        switch(gTasks[taskId].tPlayerGender)
        {
            case GENDER_MASCULINE:
        }
        
        if (gTasks[taskId].tPlayerGender != MALE)
            spriteId = gTasks[taskId].tMaySpriteId;
        else
            spriteId = gTasks[taskId].tBrendanSpriteId;
        gSprites[spriteId].x = DISPLAY_WIDTH;
        gSprites[spriteId].y = 60;
        gSprites[spriteId].invisible = FALSE;
        gTasks[taskId].tPlayerSpriteId = spriteId;
        gSprites[spriteId].oam.objMode = ST_OAM_OBJ_BLEND;
        PlayerGen_StartFadeInTarget1OutTarget2(taskId, 0);
        gTasks[taskId].func = Task_PlayerGen_SlideInNewGenderSprite;
    }
}

static void Task_PlayerGen_SlideInNewGenderSprite(u8 taskId)
{
    u8 spriteId = gTasks[taskId].tPlayerSpriteId;

    if (gSprites[spriteId].x > 180)
    {
        gSprites[spriteId].x -= 4;
    }
    else
    {
        gSprites[spriteId].x = 180;
        if (gTasks[taskId].tIsDoneFadingSprites)
        {
            gSprites[spriteId].oam.objMode = ST_OAM_OBJ_NORMAL;
            gTasks[taskId].func = Task_PlayerGen_ChooseGender;
        }
    }
}

static void Task_PlayerGen_WaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sPlayerGenState->savedCallback);
        PlayerGen_FreeResources();
        DestroyTask(taskId);
    }
}

static void Task_PlayerGen_WaitFadeAndExitGracefully(u8 taskId)
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
    CreateTask(Task_PlayerGen_WaitFadeAndBail, 0);
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
    FillWindowPixelBuffer(WINDOW_TEXT, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    PutWindowTilemap(WINDOW_TEXT);
    CopyWindowToVram(WINDOW_TEXT, 3);
}

static const u8 sText_Text1[] = _("Hello, world!");
static const u8 sText_Text2[] = _("Press {A_BUTTON} to make a sound!");

static void PlayerGen_PrintUiSampleWindowText(void)
{
    FillWindowPixelBuffer(WINDOW_TEXT, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    AddTextPrinterParameterized4(WINDOW_TEXT, FONT_NORMAL, 0, 3, 0, 0,
        sPlayerGenWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_Text1);
    AddTextPrinterParameterized4(WINDOW_TEXT, FONT_SMALL, 0, 15, 0, 0,
        sPlayerGenWindowFontColors[FONT_RED], TEXT_SKIP_DRAW, sText_Text2);

    CopyWindowToVram(WINDOW_TEXT, COPYWIN_GFX);
}

static inline void PlayerGen_PrintMessageBox(const u8 *str)
{
    DrawDialogueFrame(WINDOW_TEXT, FALSE);
    if (str != gStringVar4)
    {
        StringExpandPlaceholders(gStringVar4, str);
        AddTextPrinterParameterized2(WINDOW_TEXT, FONT_NORMAL, gStringVar4, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
    }
    else
    {
        AddTextPrinterParameterized2(WINDOW_TEXT, FONT_NORMAL, str, GetPlayerTextSpeedDelay(), NULL, TEXT_COLOR_DARK_GRAY, TEXT_COLOR_WHITE, TEXT_COLOR_LIGHT_GRAY);
    }
    CopyWindowToVram(WINDOW_TEXT, COPYWIN_FULL);
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

void PlayerGen_SetDefaultPlayerName(u8 nameId)
{
    const u8 *name = 0;
    u8 i;

    switch(gSaveBlock2Ptr->playerGender)
    {
        case GENDER_MASCULINE:
            name = sMascPresetNames[nameId];
            break;
        case GENDER_FEMININE:
            name = sFemmePresetNames[nameId];
            break;
        case GENDER_ANDROGYNOUS:
            name = sAndroPresetNames[nameId];
            break;
    }
        
    for (i = 0; i < PLAYER_NAME_LENGTH; i++)
        gSaveBlock2Ptr->playerName[i] = name[i];

    gSaveBlock2Ptr->playerName[PLAYER_NAME_LENGTH] = EOS;
}

static void Task_StartRenamingScreen(u8 taskId)
{
    if (gPaletteFade.active) return;

    CleanupOverworldWindowsAndTilemaps();
    PlayerGen_SetDefaultPlayerName(Random() % NUM_PRESET_NAMES);
    DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->playerGender, 0, 0, CB2_ReturnToFieldContinueScript);
    DestroyTask(taskId);
}

void PlayerGen_StartNamingScreen(void)
{
    FadeScreen(FADE_TO_BLACK, 0);
    CreateTask(Task_StartRenamingScreen, 1);
}

static void PlayerGen_ShowGenderMenu(void)
{
    DrawMainMenuWindowBorder(&sPlayerGenTextWindows[1], 0xF3);
    FillWindowPixelBuffer(1, PIXEL_FILL(1));
    PrintMenuTable(1, ARRAY_COUNT(sMenuActions_Gender), sMenuActions_Gender);
    InitMenuInUpperLeftCornerNormal(1, ARRAY_COUNT(sMenuActions_Gender), 0);
    PutWindowTilemap(1);
    CopyWindowToVram(1, COPYWIN_FULL);
}

static s8 PlayerGen_ProcessGenderMenuInput(void)
{
    return Menu_ProcessInputNoWrap();
}

static void PlayerGen_ClearGenderWindowTilemap(u8 bg, u8 x, u8 y, u8 width, u8 height, u8 unused)
{
    FillBgTilemapBufferRect(bg, 0, x + 255, y + 255, width + 2, height + 2, 2);
}

static void PlayerGen_ClearGenderWindow(u8 windowId, bool8 copyToVram)
{
    CallWindowFunction(windowId, PlayerGen_ClearGenderWindowTilemap);
    FillWindowPixelBuffer(windowId, PIXEL_FILL(1));
    ClearWindowTilemap(windowId);
    if (copyToVram == TRUE)
        CopyWindowToVram(windowId, COPYWIN_FULL);
}

#undef tPlayerSpriteId
#undef tTimer
#undef tPlayerGender
#undef tBrendanSpriteId
#undef tMaySpriteId
#undef tKrisSpriteId

#define tMainTask data[0]
#define tAlphaCoeff1 data[1]
#define tAlphaCoeff2 data[2]
#define tDelay data[3]
#define tDelayTimer data[4]

static void PlayerGen_StartFadeInTarget1OutTarget2(u8 taskId, u8 delay)
{
    u8 taskId2;

    SetGpuReg(REG_OFFSET_BLDCNT, BLDCNT_TGT2_BG1 | BLDCNT_EFFECT_BLEND | BLDCNT_TGT1_OBJ);
    SetGpuReg(REG_OFFSET_BLDALPHA, BLDALPHA_BLEND(0, 16));
    SetGpuReg(REG_OFFSET_BLDY, 0);
    gTasks[taskId].tIsDoneFadingSprites = 0;
    taskId2 = CreateTask(Task_PlayerGen_FadeInTarget1OutTarget2, 0);
    gTasks[taskId2].tMainTask = taskId;
    gTasks[taskId2].tAlphaCoeff1 = 0;
    gTasks[taskId2].tAlphaCoeff2 = 16;
    gTasks[taskId2].tDelay = delay;
    gTasks[taskId2].tDelayTimer = delay;
}

static void Task_PlayerGen_FadeInTarget1OutTarget2(u8 taskId)
{
    int alphaCoeff2;

    if (gTasks[taskId].tAlphaCoeff1 == 16)
    {
        gTasks[gTasks[taskId].tMainTask].tIsDoneFadingSprites = TRUE;
        DestroyTask(taskId);
    }
    else if (gTasks[taskId].tDelayTimer)
    {
        gTasks[taskId].tDelayTimer--;
    }
    else
    {
        gTasks[taskId].tDelayTimer = gTasks[taskId].tDelay;
        gTasks[taskId].tAlphaCoeff1++;
        gTasks[taskId].tAlphaCoeff2--;
        alphaCoeff2 = gTasks[taskId].tAlphaCoeff2 << 8;
        SetGpuReg(REG_OFFSET_BLDALPHA, gTasks[taskId].tAlphaCoeff1 + alphaCoeff2);
    }
}

#undef tMainTask
#undef tAlphaCoeff1
#undef tAlphaCoeff2
#undef tDelay
#undef tDelayTimer

#undef tIsDoneFadingSprites

static void PlayerGen_ClearWindow(u8 windowId)
{
    u8 bgColor = GetFontAttribute(FONT_NORMAL, FONTATTR_COLOR_BACKGROUND);
    u8 maxCharWidth = GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_WIDTH);
    u8 maxCharHeight = GetFontAttribute(FONT_NORMAL, FONTATTR_MAX_LETTER_HEIGHT);
    u8 winWidth = GetWindowAttribute(windowId, WINDOW_WIDTH);
    u8 winHeight = GetWindowAttribute(windowId, WINDOW_HEIGHT);

    FillWindowPixelRect(windowId, bgColor, 0, 0, maxCharWidth * winWidth, maxCharHeight * winHeight);
    CopyWindowToVram(windowId, COPYWIN_GFX);
}

static void DrawMainMenuWindowBorder(const struct WindowTemplate *template, u16 baseTileNum)
{
    u16 r9 = 1 + baseTileNum;
    u16 r10 = 2 + baseTileNum;
    u16 sp18 = 3 + baseTileNum;
    u16 spC = 5 + baseTileNum;
    u16 sp10 = 6 + baseTileNum;
    u16 sp14 = 7 + baseTileNum;
    u16 r6 = 8 + baseTileNum;

    FillBgTilemapBufferRect(template->bg, baseTileNum, template->tilemapLeft - 1, template->tilemapTop - 1, 1, 1, 2);
    FillBgTilemapBufferRect(template->bg, r9, template->tilemapLeft, template->tilemapTop - 1, template->width, 1, 2);
    FillBgTilemapBufferRect(template->bg, r10, template->tilemapLeft + template->width, template->tilemapTop - 1, 1, 1, 2);
    FillBgTilemapBufferRect(template->bg, sp18, template->tilemapLeft - 1, template->tilemapTop, 1, template->height, 2);
    FillBgTilemapBufferRect(template->bg, spC, template->tilemapLeft + template->width, template->tilemapTop, 1, template->height, 2);
    FillBgTilemapBufferRect(template->bg, sp10, template->tilemapLeft - 1, template->tilemapTop + template->height, 1, 1, 2);
    FillBgTilemapBufferRect(template->bg, sp14, template->tilemapLeft, template->tilemapTop + template->height, template->width, 1, 2);
    FillBgTilemapBufferRect(template->bg, r6, template->tilemapLeft + template->width, template->tilemapTop + template->height, 1, 1, 2);
    CopyBgTilemapBufferToVram(template->bg);
}