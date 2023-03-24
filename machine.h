/*******************************************************************************
***
*** Filename         : machine.h
*** Purpose          : Machine detection for Psion computers
*** Author           : Matt J. Gumbley
*** Created          : 23/07/97
*** Last updated     : 26/07/97
***
********************************************************************************
***
*** Modification Record
***
*******************************************************************************/

#ifndef MACHINE_H
#define MACHINE_H

#define MACH_UNKNOWN      0
#define MACH_SIENA        1
#define MACH_EM_SIENA     2
#define MACH_S3a          3
#define MACH_EM_S3a       4
#define MACH_S3c          5
#define MACH_S3           6
#define MACH_MC400        7
#define MACH_MC200        8
#define MACH_HC           9
#define MACH_WORKABOUT    10
#define MACH_EM_WORKABOUT 11

GLREF_D BYTE  machine_type;                   /* One of the MACH_ codes above */
GLREF_D UWORD machine_fullscreenwidth;    /* Width of entire screen in pixels */
GLREF_D UWORD machine_fullscreenheight;  /* Height of entire screen in pixels */
GLREF_D UWORD machine_fullscreencols;                     /* Width in columns */
GLREF_D UWORD machine_fullscreenrows;                       /* Height in rows */
GLREF_D UWORD machine_maxbaud;                 /* Highest baud rate supported */
GLREF_D BYTE  machine_hasIrDA;                     /* Have we an IrDA device? */
GLREF_D BYTE  machine_canreturntickcount;         /* Can we do hi-res timing? */
GLREF_D TEXT *machine_name;                     /* Model Name of this machine */

/* You'll need to call this before all the above variables are initialised */
GLREF_C VOID machine_check(void);

#endif /* MACHINE_H */

