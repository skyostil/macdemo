/**
 * Copyright (C) 2009 Sami Kyostila <sami.kyostila@unrealvoodoo.org>
 */
#ifndef CONFIG_H
#define CONFIG_H

#if defined(__GNUC__)
#   define PACKED __attribute__((packed)) 
#else
#   define BIG_ENDIAN
#   define CODEWARRIOR
#   define PACKED
#   define GENERATING68K 1
#endif

#define CT_ASSERT(expr) switch(0){case 0: case expr:;}

#if defined(CODEWARRIOR)
typedef int bool;
#endif

#endif
