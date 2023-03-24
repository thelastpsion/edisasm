/*******************************************************************************
***
*** Filename         : machine.c
*** Purpose          : Machine detection for Psion Computers
*** Author           : Matt J. Gumbley
*** Created          : 23/07/97
*** Last updated     : 10/07/98
***
********************************************************************************
***
*** Modification Record
***
*******************************************************************************/

#include <epoc.h>
#include <p_std.h>
#include <p_serial.h>

#include "machine.h"

GLDEF_D BYTE  machine_type=MACH_UNKNOWN;      /* One of the MACH_ codes above */
GLDEF_D UWORD machine_fullscreenwidth;    /* Width of entire screen in pixels */
GLDEF_D UWORD machine_fullscreenheight;  /* Height of entire screen in pixels */
GLDEF_D UWORD machine_fullscreencols;                     /* Width in columns */
GLDEF_D UWORD machine_fullscreenrows;                       /* Height in rows */
GLDEF_D UWORD machine_maxbaud;                 /* Highest baud rate supported */
GLDEF_D BYTE  machine_hasIrDA;                     /* Have we an IrDA device? */
GLDEF_D BYTE  machine_canreturntickcount;         /* Can we do hi-res timing? */
GLDEF_D TEXT *machine_name;                     /* Model Name of this machine */

GLDEF_C VOID machine_check()
{
UINT lcdtype, osversion;
UINT port;

  /* Determine machine type */
  lcdtype=p_getlcd();
  if (lcdtype == E_LCD_480_160) {
    /* S3a or S3c */
    osversion=p_version();
    if (osversion>=0x390F) {
      /* It is safe to call p_returnexpansionportinfo */
      port = p_returnexpansionportinfo();
      if ((port & 0x0700) == 0x0300) {
        /* Must be S3c */
        machine_type = MACH_S3c;
      }
      else { 
        /* Must be S3a */
        machine_type = MACH_S3a;
      }
    }
    else {
      /* EPOC < 3.90 so must be S3a */
      machine_type = MACH_S3a;
    }
  }
  else {
    /* Machine determined by LCD type */
    switch (lcdtype) {
      case E_LCD_640_400       : machine_type = MACH_MC400; break;
      case E_LCD_640_200_SMALL : machine_type = MACH_MC200; break;
      case E_LCD_160_80        : machine_type = MACH_HC; break;
      case E_LCD_240_80        : machine_type = MACH_S3; break;
      case E_LCD_240_100       : machine_type = MACH_WORKABOUT; break;
      case E_LCD_240_160       : machine_type = MACH_SIENA; break;
      default : 
        /* Assume we're running on a PC emulator: need to check ROM
           version to determine whether we're running on the Siena
           or 3a emulator. */
        switch (p_romversion()) {
          case 0x325F : machine_type = MACH_EM_S3a; break;
          case 0x421A : machine_type = MACH_EM_SIENA; break;
          case 0x200F : machine_type = MACH_EM_WORKABOUT; break;
          default     : machine_type = MACH_UNKNOWN; break;
        }
        break;
    }
  }

  /* Set the other machine_ variables above */
  machine_canreturntickcount = FALSE;
  machine_maxbaud = P_BAUD_19200;
  machine_hasIrDA = FALSE;
  switch (machine_type) {
    case MACH_SIENA:
      machine_fullscreenwidth = 240;
      machine_fullscreenheight = 160;
      machine_maxbaud = P_BAUD_56000;
      machine_hasIrDA = TRUE;
      machine_name = "Siena";
      machine_fullscreencols = 40;
      machine_fullscreenrows = 18;
      machine_canreturntickcount = TRUE;
      break;
    case MACH_EM_SIENA:
      machine_fullscreenwidth = 240;
      machine_fullscreenheight = 160;
      machine_maxbaud = P_BAUD_56000;
      machine_hasIrDA = TRUE;
      machine_name = "Siena Emulator";
      machine_fullscreencols = 40;
      machine_fullscreenrows = 18;
      break;
    case MACH_S3a:
      machine_fullscreenwidth = 480;
      machine_fullscreenheight = 160;
      machine_name = "Series 3a";
      machine_fullscreencols = 80;
      machine_fullscreenrows = 18;
      break;
    case MACH_EM_S3a:
      machine_fullscreenwidth = 480;
      machine_fullscreenheight = 160;
      machine_name = "3a Emulator";
      machine_fullscreencols = 80;
      machine_fullscreenrows = 18;
      break;
    case MACH_S3c:
      machine_fullscreenwidth = 480;
      machine_fullscreenheight = 160;
      machine_maxbaud = P_BAUD_56000;
      machine_hasIrDA = TRUE;
      machine_name = "Series 3c";
      machine_fullscreencols = 80;
      machine_fullscreenrows = 18;
      machine_canreturntickcount = TRUE;
      break;
    case MACH_S3:
      machine_fullscreenwidth = 240;
      machine_fullscreenheight = 80;
      machine_maxbaud = P_BAUD_19200; /* FIXME: Check */
      machine_name = "Series 3";
      machine_fullscreencols = 80;
      machine_fullscreenrows = 18;
      break;
    case MACH_MC400:
      machine_fullscreenwidth = 640;
      machine_fullscreenheight = 400;
      machine_maxbaud = P_BAUD_19200; /* FIXME: Check */
      machine_name = "MC400";
      break;
    case MACH_MC200:
      machine_fullscreenwidth = 640;
      machine_fullscreenheight = 200;
      machine_maxbaud = P_BAUD_19200; /* FIXME: Check */
      machine_name = "MC200";
      break;
    case MACH_HC:
      machine_fullscreenwidth = 160;
      machine_fullscreenheight = 80;
      machine_maxbaud = P_BAUD_19200; /* FIXME: CHECK */
      machine_name = "HC";
      break;
    case MACH_WORKABOUT:
      machine_fullscreenwidth = 240;
      machine_fullscreenheight = 100;
      machine_maxbaud = P_BAUD_19200; /* FIXME: Check */
      machine_name = "Workabout";
      machine_fullscreencols = 40;
      machine_fullscreenrows = 10;
      break;
    case MACH_EM_WORKABOUT:
      machine_fullscreenwidth = 240;
      machine_fullscreenheight = 100;
      machine_maxbaud = P_BAUD_19200; /* FIXME: Check */
      machine_name = "Workabout Emulator";
      machine_fullscreencols = 40;
      machine_fullscreenrows = 10;
      break;
  }
}

