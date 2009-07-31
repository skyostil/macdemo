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
    MXSurface* pcCloseUpBluescreen;
    MXSurface* pcCloseUpBluescreenMask;
    MXSurface* macCloseUp;
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
    MXSurface* note1;
    MXSurface* note2;
    MXSurface* textHey;
    MXSurface* textHeyMask;
    MXSurface* textLook;
    MXSurface* textLookMask;
    MXSurface* textIts;
    MXSurface* textItsMask;
    MXSurface* textGramps;
    MXSurface* textGrampsMask;
    MXSurface* textRun;
    MXSurface* textRunMask;
    MXSurface* textAny;
    MXSurface* textAnyMask;
    MXSurface* textDemos;
    MXSurface* textDemosMask;
    MXSurface* textLately;
    MXSurface* textLatelyMask;
    MXSurface* textWellNo;
    MXSurface* textWellNoMask;
    MXSurface* textHa;
    MXSurface* textHaMask;
    MXSurface* textCheck;
    MXSurface* textCheckMask;
    MXSurface* textThis;
    MXSurface* textThisMask;
    MXSurface* textOut;
    MXSurface* textOutMask;
    MXSurface* textYeah;
    MXSurface* textYeahMask;
    MXSurface* textGetA;
    MXSurface* textGetAMask;
    MXSurface* textLoadOf;
    MXSurface* textLoadOfMask;
    MXSurface* textLetsSee;
    MXSurface* textLetsSeeMask;
    MXSurface* textOkay;
    MXSurface* textOkayMask;
    MXSurface* textLol;
    MXSurface* textLolMask;
    MXSurface* textHelp;
    MXSurface* textHelpMask;
    MXSurface* textQuick;
    MXSurface* textQuickMask;
    MXSurface* textCallThe;
    MXSurface* textCallTheMask;
    MXSurface* textCops;
    MXSurface* textCopsMask;
    MXSurface* textSureThing;
    MXSurface* textSureThingMask;
    MXSurface* textI;
    MXSurface* textIMask;
    MXSurface* textOhNo;
    MXSurface* textOhNoMask;
    MXSurface* textStepAside;
    MXSurface* textStepAsideMask;
    MXSurface* textKids;
    MXSurface* textKidsMask;
    MXSurface* faceMacHappy;
    MXSurface* faceMacHuh;
    MXSurface* facePcIdle;
    MXSurface* facePcNoticeMac;
    MXSurface* faceMacbookNoticeMac;
    MXSurface* faceMacbookNoticeMacTalk;
    MXSurface* faceMacbookTalk;
    MXSurface* facePcTalk;
} img;

const int sintab[256] =
{
    0,
    1608, 3215, 4821, 6423, 8022, 9616, 11204, 12785,
    14359, 15923, 17479, 19024, 20557, 22078, 23586, 25079,
    26557, 28020, 29465, 30893, 32302, 33692, 35061, 36409,
    37736, 39039, 40319, 41575, 42806, 44011, 45189, 46340,
    47464, 48558, 49624, 50660, 51665, 52639, 53581, 54491,
    55368, 56212, 57022, 57797, 58538, 59243, 59913, 60547,
    61144, 61705, 62228, 62714, 63162, 63571, 63943, 64276,
    64571, 64826, 65043, 65220, 65358, 65457, 65516, 65536,
    65516, 65457, 65358, 65220, 65043, 64826, 64571, 64276,
    63943, 63571, 63162, 62714, 62228, 61705, 61144, 60547,
    59913, 59243, 58538, 57797, 57022, 56212, 55368, 54491,
    53581, 52639, 51665, 50660, 49624, 48558, 47464, 46340,
    45189, 44011, 42806, 41575, 40319, 39039, 37736, 36409,
    35061, 33692, 32302, 30893, 29465, 28020, 26557, 25079,
    23586, 22078, 20557, 19024, 17479, 15923, 14359, 12785,
    11204, 9616, 8022, 6423, 4821, 3215, 1608, 0,
    -1608, -3215, -4821, -6423, -8022, -9616, -11204, -12785,
    -14359, -15923, -17479, -19024, -20557, -22078, -23586, -25079,
    -26557, -28020, -29465, -30893, -32302, -33692, -35061, -36409,
    -37736, -39039, -40319, -41575, -42806, -44011, -45189, -46340,
    -47464, -48558, -49624, -50660, -51665, -52639, -53581, -54491,
    -55368, -56212, -57022, -57797, -58538, -59243, -59913, -60547,
    -61144, -61705, -62228, -62714, -63162, -63571, -63943, -64276,
    -64571, -64826, -65043, -65220, -65358, -65457, -65516, -65536,
    -65516, -65457, -65358, -65220, -65043, -64826, -64571, -64276,
    -63943, -63571, -63162, -62714, -62228, -61705, -61144, -60547,
    -59913, -59243, -58538, -57797, -57022, -56212, -55368, -54491,
    -53581, -52639, -51665, -50660, -49624, -48558, -47464, -46340,
    -45189, -44011, -42806, -41575, -40319, -39039, -37736, -36409,
    -35061, -33692, -32302, -30893, -29465, -28020, -26557, -25079,
    -23586, -22078, -20557, -19024, -17479, -15923, -14359, -12785,
    -11204, -9616, -8022, -6423, -4821, -3215, -1608
};

#define sini(X) (sintab[(X) & 0xff])
#define cosi(X) (sintab[((X) + 64) & 0xff])

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

void blitCentered(MXSurface* dest, MXSurface* src, MXSurface* mask, int x, int y, MXRect* srcRect, int flags)
{
    mxBlit(dest, src, mask, x - (src->w >> 1), y - (src->h >> 1), srcRect, flags);
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
    int notePos;

    mxBlit(screen, img.macOnStreetBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("Mac on street");

    pos = min(time, 72 << 6);
    pos2 = pos >> 3;
    pos >>= 6;
    notePos = ((time >> 3) & 0x7f);

    mxBlit(screen, img.pcOnStreet, NULL, 800 - pos2, 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.macOnStreet, NULL, 10 + pos, 20 + bop + (pos >> 1), NULL, 0);
    if (time > (72 << 6))
    {
        mxBlit(screen, img.faceMacHuh, NULL, 10 + 52 + pos, 20 + 35 + bop + (pos >> 1), NULL, 0);
        mxBlit(screen, img.facePcNoticeMac, NULL, 52 + 800 - pos2, 20 + 300 - (pos2 >> 1) + bop2, NULL, 0);
    }
    else
    {
        mxBlit(screen, img.faceMacHappy, NULL, 10 + 52 + pos, 20 + 35 + bop + (pos >> 1), NULL, 0);
        mxBlit(screen, img.facePcIdle, NULL, 52 + 800 - pos2, 20 + 300 - (pos2 >> 1) + bop2, NULL, 0);
    }

    if (time > 300)
    {
        mxBlit(screen, img.note1, NULL, pos + 32 - (notePos >> 2), 97 - (notePos >> 3) - bop, NULL, 0);
    }
    if (time > 500)
    {
        mxBlit(screen, img.note2, NULL, pos - 5 - (notePos >> 2), 64 - (notePos >> 2) + bop2, NULL, 0);
    }
    if (time > 800)
    {
        mxBlit(screen, img.note1, NULL, pos + 12 - (notePos >> 3), 36 - (notePos >> 1) + bop, NULL, 0);
    }

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
    mxBlit(screen, img.facePcNoticeMac, NULL, camPos + 52 + 800 - pos2, 20 + 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.macOnStreet, NULL, camPos + 10 + pos, 20 + bop + (pos >> 1), NULL, 0);
    mxBlit(screen, img.faceMacHuh, NULL, camPos + 10 + 52 + pos, 20 + 35 + bop + (pos >> 1), NULL, 0);
    mxBlit(screen, img.macbookOnStreet, NULL, camPos + 1050 - pos2, 400 - (pos2 >> 1) + bop3, NULL, 0);
    mxBlit(screen, img.faceMacbookNoticeMac, NULL, 104 + camPos + 1050 - pos2, 20 + 400 - (pos2 >> 1) + bop3, NULL, 0);
    return 1;
}

int macbookRidiculePrep(int time, int duration)
{
    mxBlit(img.macOnStreetBg, screen, NULL, 0, 0, NULL, 0);
    return 1;
}

int macbookRidicule(int time, int duration)
{
    int pos1 = pow2(max(0,  400 - time)) >> 8;
    int pos2 = pow2(max(0,  500 - time)) >> 8;
    int pos3 = pow2(max(0, 1200 - time)) >> 8;
    int pos4 = pow2(max(0, 1400 - time)) >> 8;

    mxBlit(screen, img.macOnStreetBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("Macbook Ridicule");

    if (time & 0x80 && time < 1600)
    {
        mxBlit(screen, img.faceMacbookNoticeMacTalk, NULL, 104 - 200 + 1050 - (72 << 3) + 32, 20 + 400 - (72 << 2) + 50, NULL, 0);
    }

    blitCentered(screen, img.textHey, NULL, 100 + pos1, 40, NULL, 0);
    blitCentered(screen, img.textLook, NULL, 200 + pos2, 100, NULL, 0);
    blitCentered(screen, img.textIts, NULL, 256 + pos3, 180, NULL, 0);
    blitCentered(screen, img.textGramps, NULL, 256, 250 + pos4, NULL, 0);
    return 1;
}

int pcRidicule(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC Ridicule");

    blitCentered(screen, img.pcOnStreet, NULL, 128, 256 + bop, NULL, 0);

    if (time & 0x80 && time < 1700)
    {
        blitCentered(screen, img.facePcTalk, NULL, 128 - 24, 256 - 16 + bop, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.facePcIdle, NULL, 128 - 24, 256 - 16 + bop, NULL, 0);
    }

    int pos1 = pow2(max(0,  600 - time)) >> 8;
    int pos2 = pow2(max(0,  900 - time)) >> 8;
    int pos3 = pow2(max(0, 1200 - time)) >> 8;
    int pos4 = pow2(max(0, 1500 - time)) >> 8;

    blitCentered(screen, img.textRun, NULL, 256 - 64, 40 + pos1, NULL, 0);
    blitCentered(screen, img.textAny, NULL, 256 + 64, 100 + pos2, NULL, 0);
    blitCentered(screen, img.textDemos, img.textDemosMask, 256, 180 + pos3, NULL, 0);
    blitCentered(screen, img.textLately, img.textLatelyMask, 256, 260 + pos4, NULL, 0);

    return 1;
}

int sadMac(int time, int duration)
{
    int bop = time >> 6;
    int shift = sawtooth(time >> 2) >> 2;
    MXRect rect;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Sad Mac");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128 + shift, 100 + bop, NULL, 0);

    rect.x = 0;
    rect.y = 0;
    rect.w = 8 + (time >> 2);
    rect.h = img.textWellNo->h;

    blitCentered(screen, img.textWellNo, NULL, 256, 60, &rect, 0);
    
    return 1;
}

int macbookFxIntro(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Macbook Fx Intro");

    blitCentered(screen, img.macbookOnStreet, NULL, 384, 256 + bop, NULL, 0);
    if (time & 0x80 && time < 1700)
    {
        blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16 + bop, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.faceMacbookTalk, NULL, 384 + 40, 256 - 16 + bop, NULL, 0);
    }

    int pos1 = pow2(max(0,  600 - time)) >> 8;
    int pos2 = pow2(max(0,  900 - time)) >> 8;
    int pos3 = pow2(max(0, 1200 - time)) >> 8;
    int pos4 = pow2(max(0, 1500 - time)) >> 8;

    blitCentered(screen, img.textHa, NULL, -128 + 352 + bop2, 60 + pos1, NULL, 0);
    blitCentered(screen, img.textCheck, NULL, -128 + 320, 120 + pos2, NULL, 0);
    blitCentered(screen, img.textThis, NULL, -128 + 288, 200 + pos3, NULL, 0);
    blitCentered(screen, img.textOut, NULL, -128 + 256, 280 + pos4, NULL, 0);

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
    int bop2 = sawtooth(time) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC Fx Intro");

    blitCentered(screen, img.pcOnStreet, NULL, 128, 256 + bop, NULL, 0);
    if (time & 0x80 && time < 1700)
    {
        blitCentered(screen, img.facePcTalk, NULL, 128 - 24, 256 - 16 + bop, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.facePcIdle, NULL, 128 - 24, 256 - 16 + bop, NULL, 0);
    }

    int pos1 = pow2(max(0,  600 - time)) >> 8;
    int pos2 = pow2(max(0,  900 - time)) >> 8;
    int pos3 = pow2(max(0, 1200 - time)) >> 8;
    int pos4 = pow2(max(0, 1500 - time)) >> 8;

    blitCentered(screen, img.textYeah, NULL, 128 + 160 + bop2, 60 + pos1, NULL, 0);
    blitCentered(screen, img.textGetA, NULL, 128 + 192, 120 + pos2, NULL, 0);
    blitCentered(screen, img.textLoadOf, NULL, 128 + 224, 200 + pos3, NULL, 0);
    blitCentered(screen, img.textThis, NULL, 128 + 256, 280 + pos4, NULL, 0);

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
    MXRect rect;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Macbook Dare");

    blitCentered(screen, img.macbookOnStreet, NULL, 384, 256 + bop, NULL, 0);
    blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16 + bop, NULL, 0);
    if (time & 0x80)
    {
        blitCentered(screen, img.faceMacbookNoticeMacTalk, NULL, 384 + 40, 256 + 16 + bop, NULL, 0);
    }

    rect.x = 0;
    rect.y = 0;
    rect.w = img.textLetsSee->w;
    rect.h = (time >> 3);

    blitCentered(screen, img.textLetsSee, img.textLetsSeeMask, 192, 342 / 3, &rect, 0);

    return 1;
}

int macFxLoading(int time, int duration)
{
    int bop = -time >> 8;
    MXRect rect;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Fx Loading");

    rect.x = 0;
    rect.y = 0;
    rect.w = 8 + (time >> 2);
    rect.h = img.textOkay->h;

    blitCentered(screen, img.textOkay, NULL, 256, 60, &rect, 0);

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 120 + bop, NULL, 0);

    rect.x = 256 - 44;
    rect.y = 120 + bop + 110;
    rect.w = 8 + min(144, max(0, (time - 2000)) >> 5);
    rect.h = 16;
    mxFill(screen, &rect, 1);

    return 1;
}

int macFx(int time, int duration)
{
    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Fx");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 100, NULL, 0);
    return 1;
}

void drawGuys(int time, bool laugh)
{
    int bop = (time & 0x100) >> 6;
    int bop2 = ((time + 177) & 0x100) >> 6;

    blitCentered(screen, img.pcOnStreet, NULL, 128, 140 + 64 + bop, NULL, 0);
    blitCentered(screen, img.macbookOnStreet, NULL, 384, 200 + 64 + bop2, NULL, 0);
    
    if (laugh && time & 0x80)
    {
        blitCentered(screen, img.facePcIdle, NULL, 128 - 24, 210 - 16 + bop2, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.facePcTalk, NULL, 128 - 24, 210 - 16 + bop2, NULL, 0);
    }

    if (laugh && (time + 59) & 0x80)
    {
        blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 + bop, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.faceMacbookTalk, NULL, 384 + 40, 256 + bop, NULL, 0);
    }
}

int guysLol(int time, int duration)
{
    int bop = sawtooth(time << 1) >> 3;

    mxFill(screen, NULL, 0);
    drawGuys(time, true);
    blitCentered(screen, img.textLol, NULL, 256, 60 + bop, NULL, 0);

    EFFECT_TITLE("Guys LOL");
    return 1;
}

int sadMac2(int time, int duration)
{
    int bop = time >> 6;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Sad Mac #2");

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 60 + bop, NULL, 0);
    return 1;
}

int kidHelp(int time, int duration)
{
    int bop = sawtooth(time << 1) >> 3;
    int pos = pow2(max(0,  500 - time)) >> 8;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Kid Help");
    drawGuys(time, false);

    blitCentered(screen, img.textHelp, NULL, 256 - pos, 60 + bop, NULL, 0);

    if ((time < 500) && (time & 0x40))
    {
        mxInvert(screen, NULL);
    }

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

int macbookPanic(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time << 1) >> 3;
    int bop3 = sawtooth(time) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Macbook Panic");

    blitCentered(screen, img.macbookOnStreet, NULL, 384, 256 + bop, NULL, 0);
    blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16 + bop, NULL, 0);
    if (time & 0x80 && time < 1400)
    {
        blitCentered(screen, img.faceMacbookNoticeMacTalk, NULL, 384 + 40, 256 + 16 + bop, NULL, 0);
    }

    int pos1 = pow2(max(0,  600 - time)) >> 8;
    int pos2 = pow2(max(0,  900 - time)) >> 8;
    int pos3 = pow2(max(0, 1200 - time)) >> 8;

    blitCentered(screen, img.textQuick, NULL, 128, 60 + pos1 + bop2, NULL, 0);
    blitCentered(screen, img.textCallThe, NULL, 128, 120 + pos2 + bop3, NULL, 0);
    blitCentered(screen, img.textCops, NULL, 128, 200 + pos3 + bop2, NULL, 0);

    return 1;
}

int pcPanic(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time << 1) >> 3;
    int bop3 = sawtooth(time) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("PC Panic");

    if (time > 1500)
    {
        bop = 0;
    }

    blitCentered(screen, img.pcOnStreet, NULL, 128, 256 + bop, NULL, 0);

    if (time > 1500)
    {
        blitCentered(screen, img.pcCloseUpBluescreen, img.pcCloseUpBluescreenMask, 128, 256 + bop, NULL, 0);
        bop2 = bop3 = 0;
    }
    else
    {
        if (time & 0x80)
        {
            blitCentered(screen, img.facePcTalk, NULL, 128 - 24, 256 - 16 + bop, NULL, 0);
        }
        else
        {
            blitCentered(screen, img.facePcIdle, NULL, 128 - 24, 256 - 16 + bop, NULL, 0);
        }
    }

    int pos1 = pow2(max(0,  600 - time)) >> 8;
    int pos2 = pow2(max(0,  900 - time)) >> 8;

    blitCentered(screen, img.textSureThing, NULL, 256, 60 + pos1 + bop2, NULL, 0);
    blitCentered(screen, img.textI, NULL, 256, 120 + pos2 + bop3, NULL, 0);

    if ((time > 1200 && time < 1500) && (time & 0x40))
    {
        mxInvert(screen, NULL);
    }

    return 1;
}

int macbookPanic2(int time, int duration)
{
    int bop = sawtooth(time << 1) >> 3;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Macbook Panic");

    blitCentered(screen, img.macbookOnStreet, NULL, 384, 256, NULL, 0);
    blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16, NULL, 0);
    if (time & 0x80 && (time > 2300 && time < 2700))
    {
        blitCentered(screen, img.faceMacbookNoticeMacTalk, NULL, 384 + 40, 256 + 16, NULL, 0);
    }

    int pos1 = pow2(max(0, 2500 - time)) >> 8;

    blitCentered(screen, img.textOhNo, NULL, 256, 60 + pos1 + bop, NULL, 0);

    return 1;
}
    
int macHasPlan(int time, int duration)
{
    int bop = -time >> 8;
    MXRect rect;
    int pos1 = pow2(max(0, 1500 - time)) >> 8;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Mac Has Plan");

    rect.x = 0;
    rect.y = 0;
    rect.w = 8 + (time >> 2);
    rect.h = img.textStepAside->h;

    blitCentered(screen, img.textStepAside, NULL, 192, 60, &rect, 0);
    blitCentered(screen, img.textKids, NULL, 350, 55 - pos1, NULL, 0);

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

    if (time & 0x40)
    {
        mxInvert(screen, NULL);
    }
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
#if 0
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macOnStreet,             6000, 0},
    {guysSpotMac,             2000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookRidiculePrep,     0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookRidicule,         2500, 0},
    {pcRidicule,              3000, 0},
    {sadMac,                  3000, 0},
    {macbookFxIntro,          3000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookFx,               4000, 0},
    {pcFxIntro,               3000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {pcFx,                    4000, 0},
    {macbookDare,             3000, 0},
    {macFxLoading,            6000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macFx,                   4000, 0},
#endif
    {guysLol,                 2000, 0},
    {sadMac2,                 2000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {kidHelp,                 2000, 0},
    {pedobearRunSide,         3000, 0},
    {pedobearRunFront,        2000, 0},
    {macbookPanic,            3000, 0},
    {pcPanic,                 3000, 0},
    {macbookPanic2,           4000, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macHasPlan,              3000, 0},
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
