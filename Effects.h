/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */

static struct
{
    MXSurface* introCityscape;
    MXSurface* introMac;
    MXSurface* introStreet;
    MXSurface* macOnStreetBg;
    MXSurface* macOnStreet;
    MXSurface* pcOnStreet;
    MXSurface* macbookOnStreet;
    MXSurface* pcCloseUp;
    MXSurface* macCloseUp;
    MXSurface* macbookCloseUp;
    MXSurface* pcScreenBg;
    MXSurface* macbookScreenBg;
    MXSurface* guysOnStreet;
    MXSurface* pedobearRunSide;
    MXSurface* pedobearRunSideMask;
    MXSurface* pedobearRunFront;
    MXSurface* pedobearRunFrontMask;
    MXSurface* macDiskLoad;
    MXSurface* macDiskFire;
    MXSurface* diskImpact;
    MXSurface* diskImpactMask;
    MXSurface* pedobearImpact;
    MXSurface* pedobearImpactMask;
    MXSurface* textTitle;
    MXSurface* textTitleMask;
} img;

static int x = 93, y = 17;
static int dx = 1, dy = 1;
static MXSurface* checkers = 0;
static MXSurface* ball = 0;

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
    int loadingX = (((steps << 8) / total) * screen->w) >> 8;
    MXRect rect;

    if (loadingX < 8)
    {
        loadingX = 8;
    }

    rect.x = 0;
    rect.y = 171 - 8;
    rect.w = loadingX;
    rect.h = 16;

    mxFill(screen, &rect, 0);
}

#define EFFECT_TITLE(NAME) drawDebugText(screen, 0, 0, NAME);

int yesWeHaveALoadingScreen(int time, int duration)
{
    static int loadingPos = 0;
    static int musicLoadingPos = 0;
    static FILE* packFile = 0;
    static FILE* rawMusicFile = 0;
    static SampleChunk* sampleChunk = 0;
    static Mixer* mixer;
    static ModPlayer* modPlayer;
    MXSurface** imagesToLoad = (MXSurface**)&img;
    const int imageCount = sizeof(img) / sizeof(imagesToLoad[0]);
    int musicLength;
    int mixFreq;

    /* Load images */
    if (loadingPos < imageCount)
    {
        if (!packFile)
        {
            packFile = fopen(PACKFILE, "rb");
            assert(packFile);
        }

        drawLoadingScreen(loadingPos / 2, imageCount);
        EFFECT_TITLE("Loading screen (graphics)");
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
    
    if (!audio)
    {
    	return 1;
    }

    mixFreq = audio->mixFreq();
    musicLength = mixFreq * MUSIC_LENGTH;
    
    /* Load music */
#if 1
    if (musicLoadingPos < musicLength)
    {
        if (!rawMusicFile)
        {
            rawMusicFile = fopen(RAWMUSICFILE, "wb");
            assert(rawMusicFile);
        }

        if (!sampleChunk)
        {
            SampleFormat format(8, 1);
            sampleChunk = new SampleChunk(&format, mixFreq * 4, mixFreq);
            assert(sampleChunk);
        }

        if (!mixer)
        {
            mixer = new Mixer(mixFreq, 4);
            assert(mixer);
        }

        if (!modPlayer)
        {
            modPlayer = new ModPlayer(mixer);
            assert(modPlayer);
            assert(modPlayer->load(SONGFILE));
            modPlayer->play();
        }

        mixer->render(sampleChunk);
        assert(fwrite(sampleChunk->data, sampleChunk->bytes, 1, rawMusicFile) == 1);
        musicLoadingPos += sampleChunk->length;
        drawLoadingScreen(musicLoadingPos / 2 + musicLength / 2, musicLength);
        EFFECT_TITLE("Loading screen (music)    ");
        return 0;
    }

    if (modPlayer)
    {
        delete modPlayer;
        modPlayer = 0;
    }

    if (mixer)
    {
        delete mixer;
        mixer = 0;
    }

    if (sampleChunk)
    {
        delete sampleChunk;
        sampleChunk = 0;
    }

    if (rawMusicFile)
    {
        fclose(rawMusicFile);
        rawMusicFile = 0;

        if (musicRenderer)
        {
            audio->stop();
            delete musicRenderer;
        }
        musicRenderer = new MusicRenderer(mixFreq);
        assert(musicRenderer);
        audio->start(musicRenderer);
    }
#else
    musicRenderer = new MusicRenderer(mixFreq);
    assert(musicRenderer);
    audio->start(musicRenderer);
#endif

    return 1;
}

int preloadMusic(int steps, int total)
{
	if (musicRenderer)
	{
		musicRenderer->preload();
	}
	return 1;
}

int dummyEffect(const char* name, int time, int duration)
{
    mxFill(screen, NULL, 0);
    mxBlit(screen, checkers, ball, x, y, NULL, 0);
    EFFECT_TITLE(name);
    moveBall();
    return 1;
}

#define DUMMY_EFFECT(NAME) return dummyEffect(NAME, time, duration)

int clearScreen(int time, int duration)
{
    mxFill(screen, NULL, 0);
    return 1;
}

void drawCity(int pos)
{
    int i;

    /* city skyline */
    mxBlit(screen, img.introCityscape, NULL, pos, 60, NULL, 0);
    mxBlit(screen, img.introCityscape, NULL, pos + 512, 60, NULL, 0);

    /* street */
    for (i = -128; i < 512; i += 128)
    {
        mxBlit(screen, img.introStreet, NULL, ((pos << 1) & 127) + i, 240, NULL, 0);
    }
}

int intro(int time, int duration)
{
    int pos = -time >> 5;
    int bop = (time & 0x100) >> 6;
    MXRect rect;

    drawCity(pos);
    EFFECT_TITLE("Intro");

    mxBlit(screen, img.textTitle, img.textTitleMask, 256, 30, NULL, 0);

    rect.x = 88;
    rect.y = 200;
    rect.w = img.introMac->w;
    rect.h = 20;
    mxFill(screen, &rect, 0);
    mxBlit(screen, img.introMac, NULL, 88, 200 + bop, NULL, 0);
    return 1;
}

void scrollHoriz(MXSurface *s, int amount, int fillValue)
{
    int x, y;
    int w = s->w / 8;
    uint8_t* d = s->pixels;

    if (amount > 0)
    {
        for (y = 0; y < s->h; y++)
        {
            for (x = 0; x < amount; x++)
            {
                d[x] = fillValue;
            }
            for (x = w - amount - 1; x >= 0; x--)
            {
                d[x] = d[x - amount];
            }
            d += s->stride;
        }
    }
    else
    {
        amount = -amount;
        for (y = 0; y < s->h; y++)
        {
            for (x = w - amount; x < w; x++)
            {
                d[x] = fillValue;
            }
            for (x = 0; x < w - amount; x++)
            {
                d[x] = d[x + amount];
            }
            d += s->stride;
        }
    }
}

int macOnStreet(int time, int duration)
{
    int pos, pos2;
    int bop2 = ((time + 177) & 0x100) >> 6;
    int bop = (time & 0x100) >> 6;

    mxBlit(screen, img.macOnStreetBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("Mac on street");

    pos = min(time, 72 << 6);
    pos2 = pos >> 3;
    pos >>= 6;

    mxBlit(screen, img.pcOnStreet, NULL, 800 - pos2, 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.macOnStreet, NULL, 10 + pos, 20 + bop + (pos >> 1), NULL, 0);
    return 1;
}

int guysSpotMac(int time, int duration)
{
    int pos, pos2;
    int bop = (time & 0x100) >> 6;
    int bop2 = ((time + 177) & 0x100) >> 6;
    int bop3 = ((time + 61) & 0x100) >> 6;
    int camPos = max(-time >> 2, -200);
    MXRect rect;

    mxBlit(screen, img.macOnStreetBg, NULL, camPos, 0, NULL, 0);
    EFFECT_TITLE("Guys spot mac");

    rect.x = 512 + (camPos & ~0x7);
    rect.y = 0;
    rect.w = screen->w;
    rect.h = screen->h;
    mxFill(screen, &rect, 0);

    pos = 72 << 6;
    pos2 = pos >> 3;
    pos >>= 6;

    mxBlit(screen, img.pcOnStreet, NULL, camPos + 800 - pos2, 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.macOnStreet, NULL, camPos + 10 + pos, 20 + bop + (pos >> 1), NULL, 0);
    mxBlit(screen, img.macbookOnStreet, NULL, camPos + 1050 - pos2, 400 - (pos2 >> 1) + bop3, NULL, 0);
    return 1;
}

int macbookRidicule(int time, int duration)
{
    /* Some text here */
    return 1;
}

int pcRidicule(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC ridicule");

    mxBlit(screen, img.pcCloseUp, NULL, -64, 120 + bop, NULL, 0);
    return 1;
}

int sadMac(int time, int duration)
{
    int bop = time >> 4;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Sad Mac");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 60 + bop, NULL, 0);
    return 1;
}

int macbookFxIntro(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Macbook Fx Intro");

    mxBlit(screen, img.macbookCloseUp, NULL, 64, 100 + bop, NULL, 0);
    return 1;
}

int macbookFx(int time, int duration)
{
    mxBlit(screen, img.macbookScreenBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("Macbook Fx");
    return 1;
}

int pcFxIntro(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC Fx Intro");

    mxBlit(screen, img.pcCloseUp, NULL, -64, 120 + bop, NULL, 0);
    return 1;
}

int pcFx(int time, int duration)
{
    mxBlit(screen, img.pcScreenBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("PC Fx");
    return 1;
}

int macbookDare(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Macbook Dare");

    mxBlit(screen, img.macbookCloseUp, NULL, 64, 100 + bop, NULL, 0);
    return 1;
}

int macFxLoading(int time, int duration)
{
    int bop = -time >> 5;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Fx Loading");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 120 + bop, NULL, 0);
    return 1;
}

int macFx(int time, int duration)
{
    int bop = 0;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Fx");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 60 + bop, NULL, 0);
    return 1;
}

void drawGuys(int time)
{
    int bop = (time & 0x100) >> 6;
    int bop2 = ((time + 177) & 0x100) >> 6;

    mxBlit(screen, img.pcOnStreet, NULL, 0, 100 + bop, NULL, 0);
    mxBlit(screen, img.macbookOnStreet, NULL, 256, 160 + bop2, NULL, 0);
}

int guysLol(int time, int duration)
{
    mxFill(screen, NULL, 0);
    drawGuys(time);
    EFFECT_TITLE("Guys LOL");
    return 1;
}

int sadMac2(int time, int duration)
{
    int bop = time >> 4;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Sad Mac #2");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 60 + bop, NULL, 0);
    return 1;
}

int kidHelp(int time, int duration)
{
    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Kid Help");
    drawGuys(time);
    return 1;
}

int pedobearRunSide(int time, int duration)
{
    int pos = -128 + (time >> 2);
    int bop = sawtooth(time >> 1) >> 2;

    mxFill(screen, NULL, 0);
    drawCity(0);
    mxBlit(screen, img.guysOnStreet, NULL, 0, 200, NULL, 0);
    mxBlit(screen, img.pedobearRunSide, img.pedobearRunSideMask, pos, 170 + bop, NULL, 0);
    EFFECT_TITLE("Pedobear Run");
    return 1;
}

int pedobearRunFront(int time, int duration)
{
    int bop = (time & 0x100) >> 6;

    mxFill(screen, NULL, 0);
    mxBlit(screen, img.pedobearRunFront, img.pedobearRunFrontMask, 256 - 128, 171 - 128 + bop, NULL, 0);
    EFFECT_TITLE("Pedobear Run");
    return 1;
}

int pcPanic(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC Panic");

    mxBlit(screen, img.pcCloseUp, NULL, -64, 120 + bop, NULL, 0);
    return 1;
}

int macbookPanic(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC Panic");

    mxBlit(screen, img.pcCloseUp, NULL, -64, 120 + bop, NULL, 0);
    return 1;
}

int guysPanic(int time, int duration)
{
    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Guys Panic");
    drawGuys(time);
    return 1;
}
    
int macHasPlan(int time, int duration)
{
    int bop = -time >> 4;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Has Plan");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 120 + bop, NULL, 0);
    return 1;
}

int macLoadDisk(int time, int duration)
{
    int bop = time >> 4;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Load Disk");

    mxBlit(screen, img.macDiskLoad, NULL, 256 - 128 - bop, 50, NULL, 0);
    return 1;
}

int macFireDisk(int time, int duration)
{
    int bop = -time >> 5;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Fire Disk");

    mxBlit(screen, img.macDiskFire, NULL, 256 - 128 - bop, 50, NULL, 0);
    return 1;
}

int diskTwirl(int time, int duration)
{
    DUMMY_EFFECT("Disk Twirl");
    return 1;
}

int diskImpact(int time, int duration)
{
    int bop = (time & 0x100) >> 6;
    int pos = time >> 6;

    mxFill(screen, NULL, time & 0x40);
    EFFECT_TITLE("Disk Impact");

    mxBlit(screen, img.pedobearImpact, img.pedobearImpactMask, 192 - 128 + (pos << 2), 60 + pos, NULL, 0);
    mxBlit(screen, img.diskImpact, img.diskImpactMask, 192 - pos, 60 - pos, NULL, 0);
    return 1;
}

int theEnd(int time, int duration)
{
    DUMMY_EFFECT("The End");
    return 1;
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

    audio->stop();
    delete musicRenderer;
    musicRenderer = 0;

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
    {clearScreen,             0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {intro,                   4000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macOnStreet,             6000, 0},
    {guysSpotMac,             2000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookRidicule,         2000, 0},
    {pcRidicule,              2000, 0},
    {sadMac,                  1000, 0},
    {macbookFxIntro,          2000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookFx,               4000, 0},
    {pcFxIntro,               2000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {pcFx,                    4000, 0},
    {macbookDare,             2000, 0},
    {macFxLoading,            2000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macFx,                   4000, 0},
    {guysLol,                 2000, 0},
    {sadMac2,                 1000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {kidHelp,                 2000, 0},
    {pedobearRunSide,         3000, 0},
    {pedobearRunFront,        2000, 0},
    {pcPanic,                 1000, 0},
    {macbookPanic,            1000, 0},
    {guysPanic,               1000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macLoadDisk,             1500, 0},
    {macFireDisk,             1500, 0},
    {diskTwirl,               3000, 0},
    {diskImpact,              3000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {theEnd,                  5000, 0},
    /*
    {effect1, 0x10000, 0},
    {effect2, 0x10000, 0},
    {effect3, 0x10000, 0},
    {effect4, 0x10000, 0},
    */
    {NULL, 0, 0}
};
