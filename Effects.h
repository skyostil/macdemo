/**
 *  Mac Demo
 *  Copyright (C) 2009 by Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */

static struct
{
    MXSurface* introCityscape;
    MXSurface* introMac;
    MXSurface* introMacMask;
    MXSurface* introStreet;
    MXSurface* macOnStreetBg;
    MXSurface* macOnStreet;
    MXSurface* pcOnStreet;
    MXSurface* pcOnStreetMask;
    MXSurface* macbookOnStreet;
    MXSurface* macbookOnStreetMask;
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
    MXSurface* macDiskLoadMask;
    MXSurface* macDiskFire;
    MXSurface* macDiskFireMask;
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
    MXSurface* faceMacSad;
    MXSurface* faceMacTalk;
    MXSurface* faceMacIdle;
    MXSurface* theEnd;
    MXSurface* credits;
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

static MXSurface* ball = 0;

uint8_t dither(int y, int i);

void drawLoadingScreen(int steps, int total)
{
    int loadingX = (((steps << 8) / total) * (screen->w - 16)) >> 8;
    MXRect rect;

    if (loadingX < 8)
    {
        loadingX = 8;
    }

    rect.x = 2;
    rect.y = 171 - 10;
    rect.w = screen->w - 4;
    rect.h = 20;
    mxFill(screen, &rect, 0);

    rect.x = 3;
    rect.y = 171 - 9;
    rect.w = screen->w - 6;
    rect.h = 18;
    mxFill(screen, &rect, 1);

    rect.x = 4;
    rect.y = 171 - 8;
    rect.w = loadingX;
    rect.h = 16;

    mxFill(screen, &rect, 0);
}

void blitCentered(MXSurface* dest, MXSurface* src, MXSurface* mask, int x, int y, MXRect* srcRect, int flags)
{
    mxBlit(dest, src, mask, x - (src->w >> 1), y - (src->h >> 1), srcRect, flags);
}

#ifdef DEMO_STATS
#    define EFFECT_TITLE(NAME) drawDebugText(screen, 0, 0, NAME);
#else
#    define EFFECT_TITLE(NAME)
#endif

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
#elif 0
    mixer = new Mixer(mixFreq, 4);
    modPlayer = new ModPlayer(mixer);
    assert(modPlayer);
    assert(modPlayer->load(SONGFILE));
    modPlayer->play();
    audio->start(mixer);
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
    mxBlit(screen, ball, ball, 0, 0, NULL, 0);
    EFFECT_TITLE(name);
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

    mxFill(screen, NULL, 0);
    drawCity(pos);
    EFFECT_TITLE("Intro");

    mxBlit(screen, img.textTitle, img.textTitleMask, 256, 30, NULL, 0);

    mxBlit(screen, img.introMac, img.introMacMask, 88, 200 + bop, NULL, 0);
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
    int i;

    time = (time * 9) / 7;

    mxBlit(screen, img.macOnStreetBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("Mac on street");

    pos = min(time, 72 << 6);
    pos2 = pos >> 3;
    pos >>= 6;
    notePos = ((time >> 3) & 0x7f);

    int x = 50 - pos2;
    int y = 200 - (pos2 >> 1);
    for (i = 0; i < 8; i++)
    {
        mxDrawClippedLine(screen, max(0, x), y, min(511, x + 240), y);
        x += 200;
        y += 100;
    }

    mxBlit(screen, img.pcOnStreet, img.pcOnStreetMask, 800 - pos2, 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.macOnStreet, NULL, 10 + pos, 20 + bop + (pos >> 1), NULL, 0);
    if (time > (72 << 6))
    {
        mxBlit(screen, img.faceMacHuh, NULL, 10 + 52 + pos, 20 + 37 + bop + (pos >> 1), NULL, 0);
        mxBlit(screen, img.facePcNoticeMac, NULL, 52 + 800 - pos2, 20 + 300 - (pos2 >> 1) + bop2, NULL, 0);
    }
    else
    {
        mxBlit(screen, img.faceMacHappy, NULL, 10 + 52 + pos, 20 + 37 + bop + (pos >> 1), NULL, 0);
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
    int i;
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

    int x = 50 - pos2 + camPos;
    int y = 200 - (pos2 >> 1);
    for (i = 0; i < 8; i++)
    {
        mxDrawClippedLine(screen, max(0, x), y, min(511, x + 240), y);
        x += 200;
        y += 100;
    }

    mxBlit(screen, img.pcOnStreet, img.pcOnStreetMask, camPos + 800 - pos2, 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.facePcNoticeMac, NULL, camPos + 52 + 800 - pos2, 20 + 300 - (pos2 >> 1) + bop2, NULL, 0);
    mxBlit(screen, img.macOnStreet, NULL, camPos + 10 + pos, 20 + bop + (pos >> 1), NULL, 0);
    mxBlit(screen, img.faceMacHuh, NULL, camPos + 10 + 52 + pos, 20 + 37 + bop + (pos >> 1), NULL, 0);
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

    blitCentered(screen, img.textHey, img.textHeyMask, 100 + pos1, 40, NULL, 0);
    blitCentered(screen, img.textLook, img.textLookMask, 200 + pos2, 100, NULL, 0);
    blitCentered(screen, img.textIts, img.textItsMask, 256 + pos3, 180, NULL, 0);
    blitCentered(screen, img.textGramps, img.textGrampsMask, 256, 250 + pos4, NULL, 0);
    return 1;
}

inline uint32_t ror(uint32_t value, uint32_t n)
{
    return (value >> n) | (value << (sizeof(uint32_t) * 8) - n);
}

inline uint32_t rol(uint32_t value, uint32_t n)
{
    return (value << n) | (value >> (sizeof(uint32_t) * 8) - n);
}

void drawBackgroundPattern(int time)
{
    int t = time >> 5;
    int x, y;
    uint32_t* dest = (uint32_t*)screen->pixels;
    uint32_t color = ror(0x88880000, t & 31);

#if !defined(BIG_ENDIAN)
    color = swapEndian(color);
#endif

    assert(!(screen->stride & 4));

    for (y = 0; y < screen->h; y++)
    {
        uint32_t c = color;
        if ((y + t & 0x3) == 0)
        {
            c = rol(c, (y + t) & 0x10);
            for (x = 0; x < screen->w; x += 32)
            {
                *dest++ = c;
            }
        }
        else
        {
            for (x = 0; x < screen->w; x += 32)
            {
                *dest++ = 0;
            }
        }
    }
}

void drawBackgroundPattern2(int time)
{
    int t = time >> 5;
    int x, y;
    uint32_t* dest = (uint32_t*)screen->pixels;
    uint32_t color = rol(0x88880000, t & 31);

    assert(!(screen->stride & 4));

    for (y = 0; y < (screen->h & ~3); y += 4)
    {
        uint32_t c = color;
        c = ror(c, y & 0x1f);
#if !defined(BIG_ENDIAN)
        c = swapEndian(c);
#endif

        for (x = 0; x < screen->w; x += 32)
        {
            *dest++ = c;
        }
        for (x = 0; x < screen->w * 3; x += 32)
        {
            *dest++ = 0;
        }
    }
    for (; y < screen->h; y++)
    {
        for (x = 0; x < screen->w; x += 32)
        {
            *dest++ = 0;
        }
    }
}

void drawBackgroundPattern3(int time)
{
    int t = time >> 5;
    int x, y;
    uint32_t* dest = (uint32_t*)screen->pixels;
    uint32_t color = rol(0x88880000, t & 31);

    assert(!(screen->stride & 4));

    for (y = 0; y < screen->h; y++)
    {
        if ((y + t & 0x3) == 0)
        {
            uint32_t c = color;
            int s = (sini((y + t) << 2) >> 13);

            if (s < 0)
            {
                c = ror(c, -s);
            }
            else
            {
                c = rol(c, s);
            }
#if !defined(BIG_ENDIAN)
            c = swapEndian(c);
#endif

            for (x = 0; x < screen->w; x += 32)
            {
                *dest++ = c;
            }
        }
        else
        {
            for (x = 0; x < screen->w; x += 32)
            {
                *dest++ = 0;
            }
        }
    }
}

void drawBackgroundPattern4(int time)
{
    int t = -time >> 5;
    int x, y;
    uint32_t* dest = (uint32_t*)screen->pixels;
    uint32_t color = rol(0x88880000, t & 31);

    assert(!(screen->stride & 4));

    for (y = 0; y < screen->h; y++)
    {
        if ((y + t & 0x3) == 0)
        {
            uint32_t c = color;
            int s = sawtooth((y + t) << 3) >> 3;

            if (s < 0)
            {
                c = ror(c, -s);
            }
            else
            {
                c = rol(c, s);
            }
#if !defined(BIG_ENDIAN)
            c = swapEndian(c);
#endif

            for (x = 0; x < screen->w; x += 32)
            {
                *dest++ = c;
            }
        }
        else
        {
            for (x = 0; x < screen->w; x += 32)
            {
                *dest++ = 0;
            }
        }
    }
}

void drawBackgroundPattern5(int time)
{
    int t = time >> 3;
    int t2 = time >> 5;
    int x, y;
    uint32_t* dest = (uint32_t*)screen->pixels;
    uint32_t color = (0xffffffff << (t & 0x3f));

    assert(!(screen->stride & 4));

    if (t & 0x20)
    {
        color = ~color;
    }

    for (y = 0; y < screen->h; y++)
    {
        uint32_t c1 = color;
        uint32_t c2;
        //c1 = (c1 << (y & 0x1f)) | (0xffffffff >> (64 - (y & 0x1f)));
#if !defined(BIG_ENDIAN)
        c1 = swapEndian(c1);
#endif
        c2 = ~c1;

        int d = dither(y, sawtooth((t2 << 4) + (y >> 2)));
        d  |= (d << 8) | (d << 16) | (d << 24);
        c1 |= d;
        c2 |= d;

        for (x = 0; x < screen->w; x += 64)
        {
            *dest++ = c1;
            *dest++ = c2;
        }

        color <<= 1;
        if ((t + y) & 0x20)
        {
            color |= 1;
        }
    }
}

int pcRidicule(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;

    drawBackgroundPattern(time);
    EFFECT_TITLE("PC Ridicule");

    blitCentered(screen, img.pcOnStreet, img.pcOnStreetMask, 128, 256 + bop, NULL, 0);

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

    blitCentered(screen, img.textRun, img.textRunMask, 256 - 64, 40 + pos1, NULL, 0);
    blitCentered(screen, img.textAny, img.textAnyMask, 256 + 64, 100 + pos2, NULL, 0);
    blitCentered(screen, img.textDemos, img.textDemosMask, 256, 180 + pos3, NULL, 0);
    blitCentered(screen, img.textLately, img.textLatelyMask, 256, 260 + pos4, NULL, 0);

    return 1;
}

int sadMac(int time, int duration)
{
    int bop = time >> 6;
    int shift = sawtooth(time >> 2) >> 2;
    MXRect rect;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Sad Mac");

    blitCentered(screen, img.macCloseUp, NULL, 256 + shift, 100 + 150 + bop, NULL, 0);
    if (time & 0x80 && time < 1500)
    {
        blitCentered(screen, img.faceMacTalk, NULL, 256 + shift + 28, 100 + 140 + bop - 40, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.faceMacIdle, NULL, 256 + shift + 28, 100 + 140 + bop - 40, NULL, 0);
    }

    rect.x = 0;
    rect.y = 0;
    rect.w = 8 + (time >> 2);
    rect.h = img.textWellNo->h;

    blitCentered(screen, img.textWellNo, img.textWellNoMask, 256, 60, &rect, 0);
    
    return 1;
}

int macbookFxIntro(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time) >> 3;

    drawBackgroundPattern2(time);
    EFFECT_TITLE("Macbook Fx Intro");

    blitCentered(screen, img.macbookOnStreet, img.macbookOnStreetMask, 384, 256 + bop, NULL, 0);
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

    blitCentered(screen, img.textHa, img.textHaMask, -128 + 352 + bop2, 60 + pos1, NULL, 0);
    blitCentered(screen, img.textCheck, img.textCheckMask, -128 + 320, 120 + pos2, NULL, 0);
    blitCentered(screen, img.textThis, img.textThisMask, -128 + 288, 200 + pos3, NULL, 0);
    blitCentered(screen, img.textOut, img.textOutMask, -128 + 256, 280 + pos4, NULL, 0);

    return 1;
}

int macbookFx(int time, int duration)
{
    MXRect origClipRect = screen->clipRect;
    mxBlit(screen, img.pcScreenBg, NULL, 0, 0, NULL, 0);

    screen->clipRect.x = 104;
    screen->clipRect.y = 75;
    screen->clipRect.w = 320;
    screen->clipRect.h = 200;

    int t1 = time + 7234;
    int t2 = time + 7234;
    int t3 = time - 3607;
    int x1 = (sini(t1 >> 4) + cosi(t1 >> 3)) >> 10;
    int y1 = (cosi(t1 >> 3) + sini(t3 >> 4)) >> 11;
    int x2 = (sini(t1 >> 3) + cosi(t2 >> 4)) >> 10;
    int y2 = (cosi(t1 >> 4) + sini(t1 >> 3)) >> 11;

    blitCentered(screen, ball, NULL, 256 + x1, 171 + y1, NULL, MX_BLIT_FLAG_INVERT);
    blitCentered(screen, ball, NULL, 256 + x2, 171 + y2, NULL, MX_BLIT_FLAG_INVERT);

    screen->clipRect = origClipRect;

    EFFECT_TITLE("PC Fx");
    return 1;
}

int pcFxIntro(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time) >> 3;

    drawBackgroundPattern(time);
    EFFECT_TITLE("PC Fx Intro");

    blitCentered(screen, img.pcOnStreet, img.pcOnStreetMask, 128, 256 + bop, NULL, 0);
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

    blitCentered(screen, img.textYeah, img.textYeahMask, 128 + 160 + bop2, 60 + pos1, NULL, 0);
    blitCentered(screen, img.textGetA, img.textGetAMask, 128 + 192, 120 + pos2, NULL, 0);
    blitCentered(screen, img.textLoadOf, img.textLoadOfMask, 128 + 224, 200 + pos3, NULL, 0);
    blitCentered(screen, img.textThis, img.textThisMask, 128 + 256, 280 + pos4, NULL, 0);

    return 1;
}

uint8_t dither(int y, int v)
{
#if 0
    static uint32_t const dither4x4[] =
    {
        0x008020a0,
        0xc040e060,
        0x30b01090,
        0xf070d050
    };
#endif
    static const uint32_t dither8x8[] =
    {
        0x008020a0 >> 1, 0x088828a8 >> 1,
        0xc040e060 >> 1, 0xc848e868 >> 1,
        0x30b01090 >> 1, 0x38b81898 >> 1,
        0xf070d050 >> 1, 0xf878d858 >> 1,
        0x0c8c2cac >> 1, 0x048424a4 >> 1,
        0xcc4cec6c >> 1, 0xc444e464 >> 1,
        0x3cbc1c9c >> 1, 0x34b41494 >> 1,
        0xfc7cdc5c >> 1, 0xf474d454 >> 1
    };

    char p = (y & 7) << 1;
    uint8_t ha = v >> 1;
    uint32_t c32 = ha | (ha << 8) | (ha << 16) | (ha << 24);
    uint32_t d32 = c32;
    uint8_t c;

    c32 -= dither8x8[p    ] >> 1;
    d32 -= dither8x8[p + 1] >> 1;
    c32 &= 0x80808080;
    d32 &= 0x80808080;

    c = (d32 >> 28) | (d32 >> 21) | (d32 >> 14) | (d32 >> 7);
    c = (c32 >> 28) | (c32 >> 21) | (c32 >> 14) | (c32 >> 7) | (c << 4);

    return c;
}

int pcFx(int time, int duration)
{
    int angle = time << 12;
    int x, y;
    int center = 256;
    int angle2 = sini((time + 12345) >> 4) >> 2;
    uint8_t* d = screen->pixels + screen->stride * 75;

    mxBlit(screen, img.macbookScreenBg, NULL, 0, 0, NULL, 0);
    EFFECT_TITLE("Macbook Fx");
   
    for (y = 0; y < 200; y++)
    {
        int w1, w2;
        uint8_t a = angle >> 16;

        if (a & 0x40)
        {
            w1 = absi((sini(a))) >> 9;
            w2 = absi((cosi(a))) >> 9;
        }
        else
        {
            w2 = absi((sini(a))) >> 9;
            w1 = absi((cosi(a))) >> 9;
        }

        int w = w1 + w2;
        uint8_t c1 = dither(y, w1 >> 1);
        uint8_t c2 = dither(y, w2 >> 1);
        uint8_t leftMask  = (0x1 << ((w >> 1) & 7)) - 1;
        uint8_t rightMask = ~((0xff >> ((w >> 1) & 7)));

        int left  = center - ((w + 2) >> 1);
        int subW  = w + (left & 0x7);
        int right = center + ((subW) >> 1) - 8;
        uint8_t* dest = &d[left >> 3];

        *dest++ = leftMask & c1;

        for (x = left & ~7; x < left + w1 - 8; x += 8)
        {
            *dest++ = c1;
        }

        uint8_t middleMask = (0xff >> (((left + w1 + 7) & 7)));
        
        *dest++ = c1 ^ ((c1 ^ c2) & middleMask);

        for (; x < right; x += 8)
        {
            *dest++ = c2;
        }
        *dest++ = rightMask & c2;

        d += screen->stride;
        angle += angle2;
    }

    return 1;
}

int macbookDare(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    MXRect rect;

    drawBackgroundPattern2(time);
    EFFECT_TITLE("Macbook Dare");

    blitCentered(screen, img.macbookOnStreet, img.macbookOnStreetMask, 384, 256 + bop, NULL, 0);
    blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16 + bop, NULL, 0);
    if ((time < 1500 && time & 0x80) || time > 1500)
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
    int bop = (-time >> 9) - 10;
    MXRect rect;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Mac Fx Loading");

    rect.x = 0;
    rect.y = 0;
    rect.w = 8 + (time >> 2);
    rect.h = img.textOkay->h;

    blitCentered(screen, img.macCloseUp, NULL, 256, 100 + 160 + bop, NULL, 0);
    if (time < 2000)
    {
        blitCentered(screen, img.textOkay, img.textOkayMask, 256, 60, &rect, 0);

        if (time & 0x80 && time < 1500)
        {
            blitCentered(screen, img.faceMacTalk, NULL, 256 + 28, 100 + 150 + bop - 40, NULL, 0);
        }
        else
        {
            blitCentered(screen, img.faceMacIdle, NULL, 256 + 28, 100 + 150 + bop - 40, NULL, 0);
        }
    }
    else
    {
        rect.x = 256 - 44;
        rect.y = 120 + bop + 80;
        rect.w = 8 + (min(132, max(0, (time - 2000)) >> 5) & ~7);
        rect.h = 16;
        mxFill(screen, &rect, 1);
    }

    return 1;
}

int macFx(int time, int duration)
{
    static int bx = 4;
    static int by = 7;
    static int dx = 1;
    static int dy = 1;
    static int p1 = 6;
    static int p2 = 2;
    static int t = 0;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Mac Fx");

    blitCentered(screen, img.macCloseUp, NULL, 256, 100 + 135, NULL, 0);
    
    MXRect rect;
    rect.x = 256 - 42 + (bx << 3);
    rect.y = 150 + (by << 3);
    rect.w = 8;
    rect.h = 8;
    mxFill(screen, &rect, 1);

    rect.x = 256 - 42;
    rect.y = 150 + (p1 << 3);
    rect.w = 8;
    rect.h = 32;
    mxFill(screen, &rect, 1);

    rect.x = 256 - 42 + (15 << 3);
    rect.y = 150 + (p2 << 3);
    rect.w = 8;
    rect.h = 32;
    mxFill(screen, &rect, 1);

    while (t < time)
    {
        bx += dx;
        by += dy;

        if (bx < 2 || bx > 13)
        {
            dx = -dx;
        }

        if (by < 2 || by > 7)
        {
            dy = -dy;
        }

        if (dx < 0)
        {
            if (p1 < by - 2)
            {
                p1++;
            }
            else if (p1 > by - 2)
            {
                p1--;
            }
        }
        else
        {
            if (p2 < by - 2)
            {
                p2++;
            }
            else if (p2 > by - 2)
            {
                p2--;
            }
        }

        t += 100;
    }

    return 1;
}

void drawGuys(int time, bool laugh)
{
    int bop = (time & 0x100) >> 6;
    int bop2 = ((time + 177) & 0x100) >> 6;

    blitCentered(screen, img.pcOnStreet, img.pcOnStreetMask, 128, 140 + 64 + bop, NULL, 0);
    blitCentered(screen, img.macbookOnStreet, img.macbookOnStreetMask, 384, 200 + 64 + bop2, NULL, 0);
    
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
        blitCentered(screen, img.faceMacbookTalk, NULL, 384 + 40, 256 + bop, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 + bop, NULL, 0);
    }
}

int guysLol(int time, int duration)
{
    int bop = sawtooth(time << 1) >> 3;

    drawBackgroundPattern4(time);
    drawGuys(time, true);
    blitCentered(screen, img.textLol, img.textLolMask, 256, 60 + bop, NULL, 0);

    EFFECT_TITLE("Guys LOL");
    return 1;
}

int sadMac2(int time, int duration)
{
    int bop = time >> 6;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Sad Mac #2");

    blitCentered(screen, img.macCloseUp, NULL, 256, 100 + 150 + bop, NULL, 0);
    blitCentered(screen, img.faceMacSad, NULL, 256 + 28, 100 + 140 + bop - 40, NULL, 0);

    return 1;
}

int kidHelp(int time, int duration)
{
    int bop = sawtooth(time << 1) >> 3;
    int pos = pow2(max(0,  500 - time)) >> 8;

    drawBackgroundPattern4(time);
    EFFECT_TITLE("Kid Help");
    drawGuys(time, false);

    blitCentered(screen, img.textHelp, img.textHelpMask, 256 - pos, 60 + bop, NULL, 0);

    if ((time < 700) && (time & 0x40))
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
    int bop = sawtooth(time >> 1) >> 3;

    drawBackgroundPattern5(time);
    mxBlit(screen, img.pedobearRunFront, img.pedobearRunFrontMask, 256 - 128, 171 - 128 + bop, NULL, 0);
    EFFECT_TITLE("Pedobear Run");
    return 1;
}

int macbookPanic(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time << 1) >> 3;
    int bop3 = sawtooth(time) >> 3;

    drawBackgroundPattern2(time);
    EFFECT_TITLE("Macbook Panic");

    blitCentered(screen, img.macbookOnStreet, img.macbookOnStreetMask, 384, 256 + bop, NULL, 0);
    blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16 + bop, NULL, 0);
    if (time & 0x80 && time < 1400)
    {
        blitCentered(screen, img.faceMacbookNoticeMacTalk, NULL, 384 + 40, 256 + 16 + bop, NULL, 0);
    }

    int pos1 = pow2(max(0,  600 - time)) >> 8;
    int pos2 = pow2(max(0,  900 - time)) >> 8;
    int pos3 = pow2(max(0, 1200 - time)) >> 8;

    blitCentered(screen, img.textQuick, img.textQuickMask, 128, 60 + pos1 + bop2, NULL, 0);
    blitCentered(screen, img.textCallThe, img.textCallTheMask, 128, 120 + pos2 + bop3, NULL, 0);
    blitCentered(screen, img.textCops, img.textCopsMask, 128, 200 + pos3 + bop2, NULL, 0);

    return 1;
}

int pcPanic(int time, int duration)
{
    int bop = sawtooth(time >> 1) >> 3;
    int bop2 = sawtooth(time << 1) >> 3;
    int bop3 = sawtooth(time) >> 3;

    drawBackgroundPattern(time);
    EFFECT_TITLE("PC Panic");

    if (time > 1500)
    {
        bop = 0;
    }

    blitCentered(screen, img.pcOnStreet, img.pcOnStreetMask, 128, 256 + bop, NULL, 0);

    if (time > 1500)
    {
        blitCentered(screen, img.pcCloseUpBluescreen, img.pcCloseUpBluescreenMask, 128 - 20, 256 - 12 + bop, NULL, 0);
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

    blitCentered(screen, img.textSureThing, img.textSureThingMask, 256, 60 + pos1 + bop2, NULL, 0);
    blitCentered(screen, img.textI, img.textIMask, 256, 120 + pos2 + bop3, NULL, 0);

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
    drawBackgroundPattern2(time);
    EFFECT_TITLE("Macbook Panic");

    blitCentered(screen, img.macbookOnStreet, img.macbookOnStreetMask, 384, 256, NULL, 0);
    blitCentered(screen, img.faceMacbookNoticeMac, NULL, 384 + 40, 256 - 16, NULL, 0);
    if (time & 0x80 && (time > 2300 && time < 2700))
    {
        blitCentered(screen, img.faceMacbookNoticeMacTalk, NULL, 384 + 40, 256 + 16, NULL, 0);
    }

    int pos1 = pow2(max(0, 2500 - time)) >> 8;

    blitCentered(screen, img.textOhNo, img.textOhNoMask, 256, 60 + pos1 + bop, NULL, 0);

    return 1;
}
    
int macHasPlan(int time, int duration)
{
    int bop = -time >> 8;
    MXRect rect;
    int pos1 = pow2(max(0, 1300 - time)) >> 8;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Mac Has Plan");

    rect.x = 0;
    rect.y = 0;
    rect.w = 8 + (time >> 2);
    rect.h = img.textStepAside->h;

    blitCentered(screen, img.textStepAside, img.textStepAsideMask, 192, 60, &rect, 0);
    blitCentered(screen, img.textKids, img.textKidsMask, 380, 55 - pos1, NULL, 0);

    mxBlit(screen, img.macCloseUp, NULL, 256 - 128, 120 + bop, NULL, 0);
    if (time & 0x80 && time < 1300)
    {
        blitCentered(screen, img.faceMacTalk, NULL, 256 + 28, 100 + 160 + bop - 40, NULL, 0);
    }
    else
    {
        blitCentered(screen, img.faceMacIdle, NULL, 256 + 28, 100 + 160 + bop - 40, NULL, 0);
    }

    return 1;
}

int macLoadDisk(int time, int duration)
{
    int bop = time >> 4;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Mac Load Disk");

    mxBlit(screen, img.macDiskLoad, img.macDiskLoadMask, 256 - 128 - bop, 50, NULL, 0);
    return 1;
}

int macFireDisk(int time, int duration)
{
    int bop = -time >> 5;

    drawBackgroundPattern3(time);
    EFFECT_TITLE("Mac Fire Disk");

    mxBlit(screen, img.macDiskFire, img.macDiskFireMask, 256 - 128 - bop, 50, NULL, 0);

    if (time & 0x40)
    {
        mxInvert(screen, NULL);
    }
    return 1;
}

#define F(X) ((X) << 8)
static const int diskVertices[] =
{
    F(-10), F(-10), F(0),
      F(8), F(-10), F(0),
     F(10),  F(-8), F(0),
     F(10),  F(10), F(0),
     F(10),  F(10), F(0),
    F(-10),  F(10), F(0),
    F(-10), F(-10), F(0),

     F(-6), F(-10), F(0),
     F(-6), F(-3),  F(0),
     F( 6), F(-3),  F(0),
     F( 6), F(-10), F(0),

     F( 2), F(-9), F(0),
     F( 2), F(-4), F(0),
     F( 5), F(-4), F(0),
     F( 5), F(-9), F(0),
     F( 2), F(-9), F(0),

     F(-7),  F(10), F(0),
     F(-7),  F(-1), F(0),
     F( 7),  F(-1), F(0),
     F( 7),  F(10), F(0),

     F(-2),  F(-1), F(0),
     F( 0),  F(-2), F(0),
     F( 2),  F(-1), F(0),
     F( 2),  F( 1), F(0),
     F( 0),  F( 2), F(0),
     F(-2),  F( 1), F(0),
     F(-2),  F(-1), F(0),
};
#undef F

static const int diskSpans[] =
{
    7,
    4,
    5,
    4,
    0
};

static const int diskSpans2[] =
{
    7,
    4,
    5,
    -4,
    7,
    0
};

void drawStreak(int y, int v)
{
    uint32_t* d = (uint32_t*)(screen->pixels + y * screen->stride);
    int x;
    int w = screen->w / 32;

    for (x = 0; x < w; x++)
    {
        *d++ = v;
    }
}

static uint32_t _randSeed;

void brokenRandSeed(int seed)
{
    _randSeed = seed;
}

uint32_t brokenRand()
{
    _randSeed = 16807 * _randSeed;
    return _randSeed;
}

int diskTwirl(int time, int duration)
{
    int i, x, y, j;
    int angle = time >> 3;
    int angle2 = time >> 5;
    int camPos = -64 + ((time >> 6) & 127);
    const int *vertex = diskVertices;
    int sinA = sini(angle);
    int cosA = cosi(angle);
    int sinB = sini(angle2);
    int cosB = cosi(angle2);
    int oldPx, oldPy;

    mxFill(screen, NULL, 0);
    EFFECT_TITLE("Disk Twirl");

    const int* spans = ((angle2 + 0x3f) & 0x80) ? diskSpans2 : diskSpans;

    while (*spans)
    {
        int n = *spans++;
        if (n < 0)
        {
            vertex -= 3 * n;
            continue;
        }
        for (j = 0; j < n; j++)
        {
            int px = (vertex[0] * cosA - vertex[1] * sinA) >> 16;
            int py = (vertex[0] * sinA + vertex[1] * cosA) >> 16;
            int pz = vertex[2];

            py = (py * cosB - pz * sinB) >> 16;
            pz = (py * sinB + pz * cosB) >> 16;
#if 1
            pz *= 16;
            pz = (1 << 31) / (pz + (1 << 17));
            px *= pz;
            py *= pz;
            px >>= 14;
            py >>= 14;
#endif
            px = (px >> 5) + 256 + camPos;
            py = (py >> 5) + 171;
            if (j > 0)
            {
                mxDrawLine(screen, px, py, oldPx, oldPy);
            }
            oldPx = px;
            oldPy = py;
            vertex += 3;
        }
    }

    brokenRandSeed(715517);
    
    for (i = 0; i < 32; i++)
    {
        int y = brokenRand() % 342;
        int x = (brokenRand() - (((brokenRand() & 0x7fff) + 0x7fff) * time) >> 18) & (512 / 8 - 1);
        uint8_t* dest = screen->pixels + y * screen->stride + x;
        const uint8_t colors[] = 
        {
            0xff,
            0xaa,
            0x88,
            0x80
        };
        uint8_t c = colors[i & 3];

        j = min(brokenRand() & 0xf, 512 / 8 - x - 1);
        while (j--)
        {
            *dest++ = c;
            x++;
        }
    }

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
    int scroll = max(time - 3000, 0) >> 3;
    mxFill(screen, NULL, 1);

    blitCentered(screen, img.theEnd, NULL, 256, 171 - scroll, NULL, 0);
    blitCentered(screen, img.credits, NULL, 256, 800 - scroll, NULL, 0);

    return 1;
}

void setupEffects()
{
    mxFill(screen, NULL, 1);
    flipScreen();

    ball = mxCreateSurface(512, 300, MX_PIXELFORMAT_I1, MX_SURFACE_FLAG_PRESHIFT);

    mxFillConcentricCirclePattern(ball, ball->w / 2, ball->h / 2, 4);
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
}

#define P (20 * SONG_SPEED * 64)
EffectEntry effects[] =
{
    {yesWeHaveALoadingScreen, 0, EFFECT_FLAG_DYNAMIC},
    {clearScreen,             0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {intro,                   P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macOnStreet,             P / 2, 0},
    {guysSpotMac,             P / 4, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookRidiculePrep,     0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookRidicule,         P / 4, 0},
    {pcRidicule,              P / 2, 0},
    {sadMac,                  P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookFxIntro,          P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookFx,               P, 0},
    {pcFxIntro,               P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {pcFx,                    P, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookDare,             P / 2, 0},
    {macFxLoading,            P, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macFx,                   P, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {guysLol,                 P / 2, 0},
    {sadMac2,                 P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {kidHelp,                 P / 4, 0},
    {pedobearRunSide,         P / 4, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {pedobearRunFront,        P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookPanic,            P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {pcPanic,                 P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macbookPanic2,           P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macHasPlan,              P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macLoadDisk,             P / 4, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {macFireDisk,             P / 4, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {diskTwirl,               P, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {diskImpact,              P / 2, 0},
    {preloadMusic,            0, EFFECT_FLAG_DYNAMIC | EFFECT_FLAG_INFINITESIMAL},
    {theEnd,                  15000, 0},
    {NULL, 0, 0}
};
#undef P
