/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */

static int x = 93, y = 17;
static int dx = 1, dy = 1;
static MXSurface* checkers = 0;
static MXSurface* ball = 0;

static struct
{
    MXSurface* macOnStreetBg;
    MXSurface* macOnStreet;
} img;

void moveBall()
{
    x += dx;
    y += dy;

    if (x < 0)
    {
        x = -x;
        dx = -dx;
    }

    if (x + ball->w > screen->w)
    {
        x += 2 * (screen->w - (x + ball->w));
        dx = -dx;
    }

    if (y < 0)
    {
        y = -y;
        dy = -dy;
    }

    if (y + ball->h > screen->h)
    {
        y += 2 * (screen->h - (y + ball->h));
        dy = -dy;
    }
}

void drawLoadingScreen(int steps, int total)
{
    int loadingX = (((steps << 16) / total) * screen->w) >> 16;
    MXRect rect;

    if (loadingX < 8)
    {
        loadingX = 8;
    }

    rect.x = rect.y = 0;
    rect.w = loadingX;
    rect.h = screen->h;

    mxFill(screen, &rect, 0);
    flipScreen();
}

int yesWeHaveALoadingScreen(int time, int duration)
{
    static int loadingPos = 0;
    static FILE* packFile = 0;
    MXSurface** imagesToLoad = (MXSurface**)&img;
    const int imageCount = sizeof(img) / sizeof(imagesToLoad[0]);

    if (loadingPos < imageCount)
    {
        if (!packFile)
        {
            packFile = fopen(PACKFILE, "rb");
            assert(packFile);
        }

        drawLoadingScreen(loadingPos, imageCount);

        imagesToLoad[loadingPos] = loadImage(packFile);
        assert(imagesToLoad[loadingPos]);
        loadingPos++;

        return 0;
    }

    if (packFile)
    {
        fclose(packFile);
        packFile = 0;
    }

    return 1;
}

#define DRAW_EFFECT_TITLE(NAME) drawDebugText(screen, 0, 0, NAME);

int dummyEffect(const char* name, int time, int duration)
{
    mxFill(screen, NULL, 0);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    DRAW_EFFECT_TITLE(name);
    moveBall();
    return 1;
}

#define DUMMY_EFFECT(NAME) return dummyEffect(NAME, time, duration)

int sawtooth(int t)
{
    t &= 0xff;
    if (t > 0x7f)
    {
        t = 0x7f + (0x7f - t);
    }
    return t;
}

inline int min(int a, int b)
{
    return (a < b) ? a : b;
}

inline int max(int a, int b)
{
    return (a > b) ? a : b;
}

inline int pow2(int i)
{
    return i * i;
}

int clearScreen(int time, int duration)
{
    mxFill(screen, NULL, 0);
    return 1;
}

int macOnStreet(int time, int duration)
{
    int yPos = pow2(max(0, (1500 - time) >> 3)) >> 5; 
    int pos = time >> 6;
    mxBlit(screen, img.macOnStreetBg, NULL, 0, yPos, NULL, 0);
    DRAW_EFFECT_TITLE("Mac on street");

    mxBlit(screen, img.macOnStreet, NULL, 88 + pos, yPos + 60 + (sawtooth(time >> 2) >> 4) + (pos >> 1), NULL, 0);
}

int guysSpotMac(int time, int duration)
{
    DUMMY_EFFECT("Guys spot mac");
}

int pcRidicule(int time, int duration)
{
    DUMMY_EFFECT("PC ridicule");
}

int modernMacRidicule(int time, int duration)
{
    DUMMY_EFFECT("Modern Mac ridicule");
}

int sadMac(int time, int duration)
{
    DUMMY_EFFECT("Sad Mac");
}

int modernMacFxIntro(int time, int duration)
{
    DUMMY_EFFECT("Modern Mac Fx Intro");
}

int modernMacFx(int time, int duration)
{
    DUMMY_EFFECT("Modern Mac Fx");
}

int pcFxIntro(int time, int duration)
{
    DUMMY_EFFECT("PC Fx Intro");
}

int pcFx(int time, int duration)
{
    DUMMY_EFFECT("PC Fx");
}

int modernMacDare(int time, int duration)
{
    DUMMY_EFFECT("Modern Mac Dare");
}

int macFxLoading(int time, int duration)
{
    DUMMY_EFFECT("Mac Fx Loading");
}

int macFx(int time, int duration)
{
    DUMMY_EFFECT("Mac Fx");
}

int guysLol(int time, int duration)
{
    DUMMY_EFFECT("Guys LOL");
}

int sadMac2(int time, int duration)
{
    DUMMY_EFFECT("Sad Mac 2");
}

int kidHelp(int time, int duration)
{
    DUMMY_EFFECT("Kid Help");
}

int pedobearRun(int time, int duration)
{
    DUMMY_EFFECT("Pedobear Run");
}

int pcPanic(int time, int duration)
{
    DUMMY_EFFECT("PC Panic");
}

int modernMacPanic(int time, int duration)
{
    DUMMY_EFFECT("Modern Mac Panic");
}

int guysPanic(int time, int duration)
{
    DUMMY_EFFECT("Guys Panic");
}

int macHasPlan(int time, int duration)
{
    DUMMY_EFFECT("Mac Has Plan");
}

int macPlanLoading(int time, int duration)
{
    DUMMY_EFFECT("Mac Plan Loading");
}

int macGotDisk(int time, int duration)
{
    DUMMY_EFFECT("Mac Got Disk");
}

int diskTwirl(int time, int duration)
{
    DUMMY_EFFECT("Disk Twirl");
}

int diskImpact(int time, int duration)
{
    DUMMY_EFFECT("Disk Impact");
}

int theEnd(int time, int duration)
{
    DUMMY_EFFECT("The End");
}

int effect1(int time, int duration)
{
    mxFill(screen, NULL, 0);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
    return 1;
}

int effect2(int time, int duration)
{
    mxFillCirclePattern(screen, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, SCREEN_HEIGHT / 2);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
    return 1;
}

int effect3(int time, int duration)
{
    mxFillSierpinskiPattern(screen);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
    return 1;
}

int effect4(int time, int duration)
{
    mxFillCheckerPattern(screen, 4, 4);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    moveBall();
    flipScreen();
    return 1;
}

void setupEffects()
{
    mxFill(screen, NULL, 1);
    flipScreen();

    checkers = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);
    ball = mxCreateSurface(256, 256, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);

    mxFillCheckerPattern(checkers, 4, 4);
    mxFlushSurface(checkers);

    mxFillCirclePattern(ball, 128, 128, 100);
    mxFlushSurface(ball);
}

void teardownEffects()
{
    MXSurface** imagesToDestroy = (MXSurface**)&img;
    const int imageCount = sizeof(img) / sizeof(imagesToDestroy[0]);
    int i;

    for (i = 0; i < imageCount; i++)
    {
        mxDestroySurface(imagesToDestroy[i]);
    }

    mxDestroySurface(ball);
    mxDestroySurface(checkers);
}

EffectEntry effects[] =
{
    {yesWeHaveALoadingScreen, 0, EFFECT_FLAG_DYNAMIC},
    {clearScreen,             0, EFFECT_FLAG_DYNAMIC},
    {macOnStreet,             4000, 0},
    {guysSpotMac,             1000, 0},
    {pcRidicule,              1000, 0},
    {modernMacRidicule,       1000, 0},
    {sadMac,                  1000, 0},
    {modernMacFxIntro,        1000, 0},
    {modernMacFx,             1000, 0},
    {pcFxIntro,               1000, 0},
    {pcFx,                    1000, 0},
    {modernMacDare,           1000, 0},
    {macFxLoading,            1000, 0},
    {macFx,                   1000, 0},
    {guysLol,                 1000, 0},
    {sadMac2,                 1000, 0},
    {kidHelp,                 1000, 0},
    {pedobearRun,             1000, 0},
    {pcPanic,                 1000, 0},
    {modernMacPanic,          1000, 0},
    {guysPanic,               1000, 0},
    {macHasPlan,              1000, 0},
    {macPlanLoading,          1000, 0},
    {macGotDisk,              1000, 0},
    {diskTwirl,               1000, 0},
    {diskImpact,              1000, 0},
    {theEnd,                  1000, 0},
    /*
    {effect1, 0x10000, 0},
    {effect2, 0x10000, 0},
    {effect3, 0x10000, 0},
    {effect4, 0x10000, 0},
    */
    {NULL, 0, 0}
};
