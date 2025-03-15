/*******************************************************************************
***
*** Filename         : edisasm.c
*** Purpose          : An EPOC16 disassembler
*** Author           : Matt J. Gumbley
*** Further work     : Alex Brown
*** Created          : 31/07/98
***
********************************************************************************
***
*** Modification Record
***
*******************************************************************************/

#include "dis.h"
#include "machine.h"
// #include "edisasm.rsg"
#include "EDISASM.RSG"

GLREF_D UWORD _UseFullScreen;
LOCAL_D UINT MainWid; /* ID of main window */
#define VERTICAL_LEADING 1

LOCAL_D TEXT szUnused[] = "(unused)";
LOCAL_D TEXT *isrnames[] = {
    "Divide by zero",
    "Single step",
    "Non-Masked Interrupt",
    "Break",
    "Overflow",
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    "IRQ0",
    "IRQ1",
    "IRQ2",
    "IRQ3",
    "IRQ4",
    "IRQ5",
    "IRQ6",
    "IRQ7",
    "SegManager",
    "HeapManager",
    "SemManager",
    "MessManager",
    "LibManager",
    "DevManager",
    "IoManager",
    "FilManager",
    "ProcManager",
    "TimManager",
    "ConvManager",
    "GenManager",
    "FloatManager",
    "WServOpcodes",
    "HardwareManager",
    "GenDataSegment",
    "ProcPanic",
    "ProcCopyFromById",
    "ProcCopyToById",
    "CharIsDigit",
    "CharIsHexDigit",
    "CharIsPrintable",
    "CharIsAlphabetic",
    "CharIsAlphaNumeric",
    "CharIsUpperCase",
    "CharIsLowerCase",
    "CharIsSpace",
    "CharIsPunctuation",
    "CharIsGraphic",
    "CharIsControl",
    "CharToUpperChar",
    "CharToLowerChar",
    "CharToFoldedChar",
    "BufferCopy",
    "BufferSwap",
    "BufferCompare",
    "BufferCompareFolded",
    "BufferMatch",
    "BufferMatchFolded",
    "BufferLocate",
    "BufferLocateFolded",
    "BufferSubBuffer",
    "BufferSubBufferFolded",
    "BufferJustify",
    "StringCopy",
    "StringCopyFolded",
    "StringConvertToFolded",
    "StringCompare",
    "StringCompareFolded",
    "StringMatch",
    "StringMatchFolded",
    "StringLocate",
    "StringLocateFolded",
    "StringLocateInReverse",
    "StringLocateInReverseFolded",
    "StringSubString",
    "StringSubStringFolded",
    "StringLength",
    "StringValidateName",
    "LongIntCompare",
    "LongIntMultiply",
    "LongIntDivide",
    "LongUnsignedIntCompare",
    "LongUnsignedIntMultiply",
    "LongUnsignedIntDivide",
    "FloatAdd",
    "FloatSubtract",
    "FloatMultiply",
    "FloatDivide",
    "FloatCompare",
    "FloatNegate",
    "FloatToInt",
    "FloatToUnsignedInt",
    "FloatToLong",
    "FloatToUnsignedLong",
    "IntToFloat",
    "UnsignedIntToFloat",
    "LongToFloat",
    "UnsignedLongToFloat",
    "LibSend",
    "LibSendSuper",
    "LibSendExact",
    "LibEnter",
    "LibLeave",
    "Dummy",
    "GenIntByNumber",
    "WservFunctions",
    "LibSendExit",
    "DbfManager",
    "LibEnterSend",
    "IoKeyAndMouseStatus",
    "StringCapitalise",
    "ProcIndStringCopyFromById",
    "IoNextHalfSecondStatus",
    "IoSerManager",
    "HwSetRomBank",
    "HwGetRomBank",
    "IoActivity",
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused,
    szUnused};

LOCAL_D INT text_height = 0;  /* Height of the current font */
LOCAL_D INT text_width = 0;   /* Width of the current font */
LOCAL_D INT text_ascent = 0;  /* Ascent of the current font */
LOCAL_D INT text_descent = 0; /* Descent of the current font */
LOCAL_D INT rows;             //=16; /* how many rows available, minus edit box? */
LOCAL_D INT cols;             //=79; /* how many columns available? */
LOCAL_D TEXT *maladdr = "malformed address";

/* Keyboard stuff */
LOCAL_D WORD key_stat;
LOCAL_D WMSG_KEY key;
LOCAL_D WORD key_active = FALSE;

#define EDITLEN 80
#define FONT (WS_FONT_BASE + 8)
LOCAL_D P_SCR_SET_FONT Font;
P_RECT rect;

/* Editor stuff */
LOCAL_D VOID *ebH;

/* Cursor positioning stuff */
LOCAL_D INT cx = 0, cy = 0;

/* Address holders */
LOCAL_D UWORD seg = 0, off = 0, intno = 0, bankno = 0;
LOCAL_D UWORD psel0, psel1, psel2, psel3;

/* Disassembler stuff */
INT objflg = 0;   /* Flag: output object bytes  */
INT force = 0;    /* Flag: override some checks */
INT linesout = 0; /* Num of lines displayed so far */

GLDEF_D char hexdig[] = "0123456789ABCDEF";
LOCAL_D TEXT LINE[80];

/* prototypes for assembler routines in access.asm */
GLREF_C VOID SETPSEL0(UWORD);
GLREF_C UBYTE GETPSEL0(void);
GLREF_C VOID SETPSEL1(UWORD);
GLREF_C UBYTE GETPSEL1(void);
GLREF_C VOID SETPSEL2(UWORD);
GLREF_C UBYTE GETPSEL2(void);
GLREF_C UBYTE ACCESS(UWORD, UWORD);
GLREF_C VOID MEMCPY(UWORD segdiv4, UWORD offset, UWORD count, UBYTE *buf);
GLREF_C VOID MEMCPYPSEL0(UWORD psel0, UWORD offsetseg6000, UWORD count, UBYTE *buf);
GLREF_C VOID MEMCPYPSEL1(UWORD psel1, UWORD offsetseg7000, UWORD count, UBYTE *buf);
GLREF_C VOID MEMCPYPSEL2(UWORD psel2, UWORD offsetseg8000, UWORD count, UBYTE *buf);
GLREF_C UWORD GETCS(void);
GLREF_C UWORD GETDS(void);
GLREF_C UWORD GETA9RCTRL(void);
GLREF_C UWORD GETA9RSTAT(void);
GLREF_C VOID MEMPUTPSEL0(UWORD psel0, UWORD offsetseg6000, UWORD count, UBYTE *buf);

LOCAL_C VOID cls(VOID)
{
  cx = cy = 0;
  gClrRect(&rect, G_TRMODE_CLR);
}

GLDEF_C UBYTE getchar(VOID)
{
  UWORD seg, off;
  seg = (PC & 0xf0000L) >> 4;
  off = (PC & 0x0ffffL);
  return ACCESS(seg, off);
}

GLDEF_C VOID disassemble(VOID)
{
  // char *c;
  UBYTE b;
  register void (*f)();

  segflg = 0;
  linesout = 0;
  for (PC = (seg << 4) + off; linesout < rows; ++PC)
  {
    b = getchar();
    f = optab[b].func;
    (*f)(b);
  }
}

GLDEF_C UBYTE Fetch(VOID)
{
  UBYTE b;

  ++PC;
  b = getchar();
  objbuf[objptr++] = b;
  return b;
}

LOCAL_C INT printAt(INT x, INT y, TEXT *str, INT len)
{
  gPrintText(x * text_width + 2, y * text_height + 2 + text_ascent, str, len);
  return len;
}

LOCAL_C VOID rackup(VOID)
{
  P_RECT p;
  P_POINT pp;

  p.tl.x = 2;
  p.tl.y = 2 + text_height;
  p.br.x = rect.br.x;
  p.br.y = rect.br.y;
  pp.x = 0;
  pp.y = -text_height;
  wScrollRect(MainWid, &p, &pp);
  p.tl.y = p.br.y - text_height;
  gClrRect(&p, G_TRMODE_CLR);
}

LOCAL_C VOID println(TEXT *str)
{
  if (cy == rows)
  {
    rackup();
    cy--;
  }

  cx = 0; // just in case
  printAt(cx, cy, str, p_slen(str));

  if (cy < rows)
  {
    cy++;
  }
}

LOCAL_C VOID printlnc(TEXT *str)
{
  if (cy == rows)
  {
    rackup();
    cy--;
  }

  cx = (cols / 2) - (p_slen(str) / 2); // roughly centre?
  printAt(cx, cy, str, p_slen(str));
  cx = 0; // clean things up

  if (cy < rows)
  {
    cy++;
  }
}

LOCAL_C VOID niceerror_E_FILE(INT err)
{
  switch (err)
  {
  case E_FILE_DEVICE:
    println("E_FILE_DEVICE: Invalid or non-existent device specified.");
    return;
  case E_FILE_NOTREADY:
    println("E_FILE_NOTREADY: Nothing in drive.");
    return;
  case E_FILE_CORRUPT:
    println("E_FILE_CORRUPT: No valid boot record found - unformatted?");
    return;
  case E_FILE_UNKNOWN:
    println("E_FILE_UNKNOWN: No idea what the medium is!");
    return;
  }
}

LOCAL_C VOID gotoxy(INT x, INT y)
{
  cx = x;
  cy = y;
}

LOCAL_C INT parse_bankno(TEXT *addr)
{
  UWORD tbankno;

  /* Skip WS until hex digit */
  while (*addr && !p_isxdigit(*addr))
    addr++;
  /* EOL? Use last address */
  if (!*addr)
    return TRUE;
  if (p_stog(&addr, &tbankno, 16) != 0)
  {
    wInfoMsg(maladdr);
    return FALSE;
  }
  bankno = tbankno;
  return TRUE;
}

LOCAL_C INT parse_intno(TEXT *addr)
{
  UWORD tintno;

  /* Skip WS until hex digit */
  while (*addr && !p_isxdigit(*addr))
    addr++;
  /* EOL? Use last address */
  if (!*addr)
    return TRUE;
  if (p_stog(&addr, &tintno, 16) != 0)
  {
    wInfoMsg(maladdr);
    return FALSE;
  }
  intno = tintno;
  return TRUE;
}

LOCAL_C INT parse_address(TEXT *addr)
{
  UWORD tseg, toff;

  /* Skip WS until hex digit */
  while (*addr && !p_isxdigit(*addr))
    addr++;
  /* EOL? Use last address */
  if (!*addr)
    return TRUE;
  if (p_stog(&addr, &tseg, 16) != 0)
  {
    wInfoMsg(maladdr);
    return FALSE;
  }
  if (*addr == ':')
  {
    addr++;
    if (p_stog(&addr, &toff, 16) != 0)
    {
      wInfoMsg(maladdr);
      return FALSE;
    }
    seg = tseg;
    off = toff;
  }
  else
  {
    off = tseg;
  }
  return TRUE;
}

LOCAL_C VOID dump_bytes(VOID)
{
  INT y, x;
  UBYTE b[16];
  UWORD prevbank = p_getrombank();

  cls();
  for (y = 0; y < rows; y++)
  {
    p_bfil(LINE, 79, ' ');
    p_atos(LINE, "%04x:%04x", seg, off);
    LINE[9] = ' ';
    LINE[10] = LINE[60] = '\263';
    p_setrombank(bankno);
    MEMCPY(seg >> 4, off, 16, b);
    p_setrombank(prevbank);
    for (x = 0; x < 16; x++)
    {
      off++;
      if (!off)
        seg += 0x1000;
      LINE[12 + (3 * x)] = hexdig[(b[x] & 0xf0) >> 4];
      LINE[13 + (3 * x)] = hexdig[b[x] & 0x0f];
      LINE[62 + x] = b[x];
    }
    printAt(0, y, LINE, 78);
  }
  cy = rows; // otherwise any regular println() will start at the top of the screen
}

LOCAL_C VOID dump_words(VOID)
{
  INT y, x;
  UBYTE h, l;
  UWORD prevbank = p_getrombank();

  cls();
  for (y = 0; y < rows; y++)
  {
    p_bfil(LINE, 79, ' ');
    p_atos(LINE, "%04x:%04x", seg, off);
    LINE[9] = ' ';
    LINE[10] = LINE[60] = '\263';

    for (x = 0; x < 8; x++)
    {
      p_setrombank(bankno);
      l = ACCESS(seg, off);
      p_setrombank(prevbank);
      LINE[62 + (x << 1)] = l;
      off++;
      if (!off)
        seg += 0x1000;
      p_setrombank(bankno);
      h = ACCESS(seg, off);
      p_setrombank(prevbank);
      LINE[63 + (x << 1)] = h;
      off++;
      if (!off)
        seg += 0x1000;
      LINE[12 + (5 * x)] = hexdig[(h & 0xf0) >> 4];
      LINE[13 + (5 * x)] = hexdig[h & 0x0f];
      LINE[14 + (5 * x)] = hexdig[(l & 0xf0) >> 4];
      LINE[15 + (5 * x)] = hexdig[l & 0x0f];
    }
    printAt(0, y, LINE, 78);
  }
  cy = rows; // otherwise any regular println() will start at the top of the screen
}

LOCAL_C VOID ivt(VOID)
{
  INT y, x;
  UBYTE b[4];

  /*
  0         1         2         3         4         5         6         7
  01234567890123456789012345678901234567890123456789012345678901234567890
  INT 00=0000:0000  INT 01=0000:0000  INT 02=0000:0000  INT 03=0000:0000
  */

  cls();
  for (y = 0; y < rows; y++)
  {
    p_bfil(LINE, 70, ' ');
    LINE[0] = '\0';
    for (x = 0; x < 4; x++)
    {
      MEMCPY(0, (intno << 2), 4, b);
      p_atos(LINE + (x * 18), "INT %02x=%c%c%c%c:%c%c%c%c  ", intno,
             hexdig[(b[3] & 0xf0) >> 4],
             hexdig[b[3] & 0x0f],
             hexdig[(b[2] & 0xf0) >> 4],
             hexdig[b[2] & 0x0f],
             hexdig[(b[1] & 0xf0) >> 4],
             hexdig[b[1] & 0x0f],
             hexdig[(b[0] & 0xf0) >> 4],
             hexdig[b[0] & 0x0f]);
      intno++;
      if (intno == 0x100)
        intno = 0;
    }
    printAt(0, y, LINE, 70);
  }
}

LOCAL_C VOID ivtlong(VOID)
{
  INT y; //, x;
  UBYTE b[4];

  cls();
  for (y = 0; y < rows; y++)
  {
    p_bfil(LINE, 70, ' ');
    LINE[0] = '\0';
    MEMCPY(0, (intno << 2), 4, b);
    p_atos(LINE, "INT %02x=%c%c%c%c:%c%c%c%c %s\0", intno,
           hexdig[(b[3] & 0xf0) >> 4],
           hexdig[b[3] & 0x0f],
           hexdig[(b[2] & 0xf0) >> 4],
           hexdig[b[2] & 0x0f],
           hexdig[(b[1] & 0xf0) >> 4],
           hexdig[b[1] & 0x0f],
           hexdig[(b[0] & 0xf0) >> 4],
           hexdig[b[0] & 0x0f],
           isrnames[intno]);
    intno++;
    if (intno == 0x100)
      intno = 0;
    printAt(0, y, LINE, 70);
  }
}

LOCAL_C VOID send_ivt(VOID)
{
  VOID *fd;
  INT i;
  static TEXT *head = "Listing of interrupts";
  UBYTE b[4];
  static TEXT LINE[80];
  static TEXT *fname = "REM::C:\\IVT.LST";

  if (p_open(&fd, fname, P_FTEXT | P_FREPLACE | P_FUPDATE) != 0)
    println("Can't create interrupt listing file");
  else
  {
    println("Creating...");
    println(fname);
    p_write(fd, head, p_slen(head));
    for (i = 0; i < 0x100; i++)
    {
      MEMCPY(0, (i << 2), 4, b);
      p_atos(LINE, "INT %02x=%c%c%c%c:%c%c%c%c %s", i,
             hexdig[(b[3] & 0xf0) >> 4],
             hexdig[b[3] & 0x0f],
             hexdig[(b[2] & 0xf0) >> 4],
             hexdig[b[2] & 0x0f],
             hexdig[(b[1] & 0xf0) >> 4],
             hexdig[b[1] & 0x0f],
             hexdig[(b[0] & 0xf0) >> 4],
             hexdig[b[0] & 0x0f],
             isrnames[i]);
      p_write(fd, LINE, p_slen(LINE));
    }
    println("done.");
    p_close(fd);
  }
}

/* I noted on the mailing list that:
   EPOC p_setrombank() and p_getrombank() set and get the value
   of PSEL3. The parameter of p_setrombank() ranges from 0x00 to 0xff. Values
   < 0x80 cause the address decoder to select no memory, and so nothing is
   accessible, apart from a series of increasing numbers in the
   0x9000:0000-FFFF bank. Values of 0x80 to 0x9F cause one of the 0x20 64KB
   banks to be selected. Values from 0xA0 to 0xBF and 0xC0 to 0xFF produce
   identical banks to those selected for values 0x80 to 0x9F.
*/

LOCAL_C VOID banktest(VOID)
{
  VOID *fd;
  INT i, x;
  static TEXT *head = "Which banks get switched?\r\n";
#define BTLEN 2048
  UBYTE b[BTLEN];
  UWORD tot6000, tot7000, tot8000, tot9000;
  static TEXT buf[80];
  static TEXT LINE[80];
  static TEXT *fname = "REM::C:\\BANKS.LST";
  UWORD prevbank = p_getrombank();

  if (p_open(&fd, fname, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
    println("Can't create bank listing file");
  else
  {
    println("Creating...");
    println(fname);
    p_write(fd, head, p_slen(head));

    for (i = 0; i < 0x100; i++)
    {
      p_atos(buf, "Checksumming bank %02x", i);
      wInfoMsg(buf);

      /* Do banks at 6000 */
      MEMCPYPSEL0(i, 0x0000, BTLEN, b);
      tot6000 = 0;
      p_crc(&tot6000, b, BTLEN);
      p_atos(LINE, "Seg 6000 Bank %02x:\r\n", i);
      p_write(fd, LINE, p_slen(LINE));
      for (x = 0; x < 16; x++)
      {
        p_atos(LINE, "%02x ", b[x]);
        p_write(fd, LINE, p_slen(LINE));
      }
      p_write(fd, ": ", 2);
      for (x = 0; x < 16; x++)
      {
        LINE[0] = p_isprint(b[x]) ? b[x] : '.';
        p_write(fd, LINE, 1);
      }
      p_write(fd, "\r\n", 2);

      /* Do banks at 7000 */
      MEMCPYPSEL1(i, 0x0000, BTLEN, b);
      tot7000 = 0;
      p_crc(&tot7000, b, BTLEN);
      p_atos(LINE, "Seg 7000 Bank %02x:\r\n", i);
      p_write(fd, LINE, p_slen(LINE));
      for (x = 0; x < 16; x++)
      {
        p_atos(LINE, "%02x ", b[x]);
        p_write(fd, LINE, p_slen(LINE));
      }
      p_write(fd, ": ", 2);
      for (x = 0; x < 16; x++)
      {
        LINE[0] = p_isprint(b[x]) ? b[x] : '.';
        p_write(fd, LINE, 1);
      }
      p_write(fd, "\r\n", 2);

      /* Do banks at 8000 */
      MEMCPYPSEL2(i, 0x0000, BTLEN, b);
      tot8000 = 0;
      p_crc(&tot8000, b, BTLEN);

      p_atos(LINE, "Seg 8000 Bank %02x:\r\n", i);
      p_write(fd, LINE, p_slen(LINE));
      for (x = 0; x < 16; x++)
      {
        p_atos(LINE, "%02x ", b[x]);
        p_write(fd, LINE, p_slen(LINE));
      }
      p_write(fd, ": ", 2);
      for (x = 0; x < 16; x++)
      {
        LINE[0] = p_isprint(b[x]) ? b[x] : '.';
        p_write(fd, LINE, 1);
      }
      p_write(fd, "\r\n", 2);

      /* Do banks at 9000 */
      p_setrombank(i);
      MEMCPY(0x0900, 0x0000, BTLEN, b);
      p_setrombank(prevbank);
      tot9000 = 0;
      p_crc(&tot9000, b, BTLEN);

      p_atos(LINE, "Seg 9000 Bank %02x:\r\n", i);
      p_write(fd, LINE, p_slen(LINE));
      for (x = 0; x < 16; x++)
      {
        p_atos(LINE, "%02x ", b[x]);
        p_write(fd, LINE, p_slen(LINE));
      }
      p_write(fd, ": ", 2);
      for (x = 0; x < 16; x++)
      {
        LINE[0] = p_isprint(b[x]) ? b[x] : '.';
        p_write(fd, LINE, 1);
      }
      p_write(fd, "\r\n", 2);

      p_atos(LINE, "BANK %02x 6000=%04x 7000=%04x 8000=%04x 9000=%04x\r\n", i, tot6000, tot7000, tot8000, tot9000);
      p_write(fd, LINE, p_slen(LINE));
    }
    println("done.");
    p_close(fd);
  }
}

LOCAL_C VOID send(UINT seg, UINT off, UINT lastseg, TEXT *fname)
{
  VOID *fd;
#define BUFFERSIZE 1024
  static UBYTE buf[BUFFERSIZE];
  UINT tseg;
  TEXT szbuf[40];
  UWORD prevbank = p_getrombank();

  p_atos(szbuf, "REM::C:\\%s.MEM", fname);
  if (p_open(&fd, szbuf, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
  {
    println("Can't create output file");
    println(szbuf);
  }
  else
  {
    println("Creating...");
    println(szbuf);
    println("To stop, kill EDisAsm from System Screen");
    while (seg < lastseg)
    {
      tseg = seg << 4;
      p_atos(szbuf, "Writing data from %04x:%04x", tseg, off);
      wInfoMsg(szbuf);
      p_setrombank(bankno);
      MEMCPY(seg, off, BUFFERSIZE, buf);
      p_setrombank(prevbank);
      p_write(fd, buf, BUFFERSIZE);
      off += BUFFERSIZE;
      if (off == 0)
        seg += 0x100;
    }
    println("done.");
    p_close(fd);
  }
}

LOCAL_C VOID sendbank(UWORD bank)
{
  TEXT buf[40];

  p_atos(buf, "ROM2%02x", bank);
  bankno = bank;
  send(0x0900, 0x0000, 0x0A00, buf);
}

LOCAL_C VOID sendbanks9000()
{
  INT b;

  for (b = 0x80; b < 0xA0; b++)
    sendbank(b);
}

/**
  Extracts two hex numbers from a string, separated by spaces.
  It's used with the sendbanksX000() functions to pick which banks to send
  across a PLP link. It calls p_stoa() to extract the two numbers, then does
  some processing. Returns a status as an INT.
*/
LOCAL_C INT banknums(TEXT **bankargsptr, UINT *firstbankptr, UINT *lastbankptr)
{
  INT ret;

  ret = p_stoa(bankargsptr, "%x %x", firstbankptr, lastbankptr);

  switch (ret)
  {
  case 0:         // Got two arguments, everything's fine
    break;
  case E_GEN_ARG: // Not enough arguments, so there's only one
    *lastbankptr = *firstbankptr;
    break;
  default:        // Any other error, we leave now
    return -1; // miscellaneous bad arguments from p_stoa()
  }

  if (*firstbankptr > *lastbankptr)
  {
    return -2; // First bank can't be bigger than the last bank
  }

  if (*firstbankptr > 0xFF || *lastbankptr > 0xFF || *firstbankptr < 0 || *lastbankptr < 0)
  {
    return -3; // invalid number
  }

  return 0;
}

LOCAL_C VOID sendbanks9000selection(TEXT *bankargs)
{
  UINT firstbank = 0, lastbank = 0;
  INT ret;
  TEXT szbuf[80];
  INT b;

  ret = banknums(&bankargs, &firstbank, &lastbank);

  switch (ret)
  {
  case 0:
    break;
  case -1:
    println("Bad arguments.");
    return;
  case -2:
    p_atos(szbuf, "First bank can't be bigger than the last bank! (%02x>%02x)", firstbank, lastbank);
    println(szbuf);
    return;
  case -3:
    println("Bank must be between 00 and FF!");
    return;
  default:
    println("Unhandled error from banknums()");
    return;
  }

  if (firstbank == lastbank)
  {
    p_atos(szbuf, "Sending bank %02x...", firstbank);
  }
  else
  {
    p_atos(szbuf, "Sending banks %02x to %02x...", firstbank, lastbank);
  }
  println(szbuf);

  for (b = firstbank; b <= lastbank; b++)
    sendbank(b);
}

/* Versions of the above that use direct OUTs to PSEL2 to access the banks at
 * 80000
 */
LOCAL_C VOID sendPSEL2(UINT seg, UINT off, UINT lastseg, TEXT *fname)
{
  VOID *fd;
#define BUFFERSIZE 1024
  static UBYTE buf[BUFFERSIZE];
  UINT tseg;
  TEXT szbuf[80];
  UBYTE prevbank = GETPSEL2();


#if 0
  p_atos(szbuf,"PSEL2=0x%02x", prevbank);
  println(szbuf);
  p_atos(szbuf,"bankno=0x%02x", bankno);
  println(szbuf);
  return;
#endif

  p_atos(szbuf, "REM::C:\\%s.MEM", fname);
  if (p_open(&fd, szbuf, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
  {
    println("Can't create output file");
    println(szbuf);
  }
  else
  {
    println("Creating...");
    println(szbuf);
    println("To stop, kill EDisAsm from System Screen");
    while (seg < lastseg)
    {
      tseg = seg << 4;
      p_atos(szbuf, "Writing data from %04x:%04x", tseg, off);
      wInfoMsg(szbuf);
      SETPSEL2(bankno);
      MEMCPY(seg, off, BUFFERSIZE, buf);
      SETPSEL2(prevbank);
      p_write(fd, buf, BUFFERSIZE);
      off += BUFFERSIZE;
      if (off == 0)
        seg += 0x100;
    }
    println("done.");
    p_close(fd);
  }
}

LOCAL_C VOID sendbankPSEL2(UWORD bank)
{
  TEXT buf[40];

  p_atos(buf, "ROM1%02x", bank);
  bankno = bank;
  sendPSEL2(0x0800, 0x0000, 0x0900, buf);
}

/* Similar to sendbanks9000, but uses direct OUTs to PSEL2:
   out al, 0x28 - page select 6000 (first RAM bank) (PSEL0)
   out al, 0x29 - page select 7000 (second RAM bank) (PSEL1)
   out al, 0x2A - page select 8000 (first ROM bank) (PSEL2)
   out al, 0x2B - page select 9000 (second ROM bank) (PSEL3)
   (i.e. what you get from p_setrombank() )
   Kudos to Simon Wood!
*/
LOCAL_C VOID sendbanks8000()
{
  INT b;
  for (b = 0x80; b < 0xA0; b++)
    sendbankPSEL2(b);
}

/* RAM bank-switching routines */
LOCAL_C VOID sendPSEL0(UINT seg, UINT off, UINT lastseg, TEXT *fname)
{
  VOID *fd;
#define BUFFERSIZE 1024
  static UBYTE buf[BUFFERSIZE];
  UINT tseg;
  TEXT szbuf[80];
  UBYTE prevbank = GETPSEL0();

  p_atos(szbuf, "REM::C:\\%s.MEM", fname);
  if (p_open(&fd, szbuf, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
  {
    println("Can't create output file");
    println(szbuf);
  }
  else
  {
    println("Creating...");
    println(szbuf);
    println("To stop, kill EDisAsm from System Screen");
    while (seg < lastseg)
    {
      tseg = seg << 4;
      p_atos(szbuf, "Writing data from %04x:%04x", tseg, off);
      wInfoMsg(szbuf);
      SETPSEL0(bankno);
      MEMCPY(seg, off, BUFFERSIZE, buf);
      SETPSEL0(prevbank);
      p_write(fd, buf, BUFFERSIZE);
      off += BUFFERSIZE;
      if (off == 0)
        seg += 0x100;
    }
    println("done.");
    p_close(fd);
  }
}

LOCAL_C VOID sendPSEL1(UINT seg, UINT off, UINT lastseg, TEXT *fname)
{
  VOID *fd;
#define BUFFERSIZE 1024
  static UBYTE buf[BUFFERSIZE];
  UINT tseg;
  TEXT szbuf[80];
  UBYTE prevbank = GETPSEL1();

  p_atos(szbuf, "REM::C:\\%s.MEM", fname);
  if (p_open(&fd, szbuf, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
  {
    println("Can't create output file");
    println(szbuf);
  }
  else
  {
    println("Creating...");
    println(szbuf);
    println("To stop, kill EDisAsm from System Screen");
    while (seg < lastseg)
    {
      tseg = seg << 4;
      p_atos(szbuf, "Writing data from %04x:%04x", tseg, off);
      wInfoMsg(szbuf);
      SETPSEL1(bankno);
      MEMCPY(seg, off, BUFFERSIZE, buf);
      SETPSEL1(prevbank);
      p_write(fd, buf, BUFFERSIZE);
      off += BUFFERSIZE;
      if (off == 0)
        seg += 0x100;
    }
    println("done.");
    p_close(fd);
  }
}

LOCAL_C VOID sendbankPSEL0(UWORD bank)
{
  TEXT buf[40];

  p_atos(buf, "RAM1%02x", bank);
  bankno = bank;
  sendPSEL0(0x0600, 0x0000, 0x0700, buf);
}

LOCAL_C VOID sendbankPSEL1(UWORD bank)
{
  TEXT buf[40];

  p_atos(buf, "RAM2%02x", bank);
  bankno = bank;
  sendPSEL1(0x0700, 0x0000, 0x0800, buf);
}

LOCAL_C VOID sendbanks6000()
{
  INT b;

  if (GETCS() == 0x6000 || GETDS() == 0x6000)
  {
    println("Can't dump 0x60000-0x6FFFF: CS or DS in that range!");
  }
  else
  {
    for (b = 0x00; b <= 0xFF; b++)
      sendbankPSEL0(b);
  }
}

LOCAL_C VOID sendbanks6000selection(TEXT *bankargs)
{
  UINT firstbank = 0, lastbank = 0;
  INT ret;
  TEXT szbuf[80];
  INT b;

  if (GETCS() == 0x6000 || GETDS() == 0x6000)
  {
    println("Can't dump 0x60000-0x6FFFF: CS or DS in that range!");
    return;
  }

  ret = banknums(&bankargs, &firstbank, &lastbank);

  switch (ret)
  {
  case 0:
    break;
  case -1:
    println("Bad arguments.");
    return;
  case -2:
    p_atos(szbuf, "First bank can't be bigger than the last bank! (%02x>%02x)", firstbank, lastbank);
    println(szbuf);
    return;
  case -3:
    println("Bank must be between 00 and FF!");
    return;
  default:
    println("Unhandled error from banknums()");
    return;
  }

  if (firstbank == lastbank)
  {
    p_atos(szbuf, "Sending bank %02x...", firstbank);
  }
  else
  {
    p_atos(szbuf, "Sending banks %02x to %02x...", firstbank, lastbank);
  }
  println(szbuf);

  for (b = firstbank; b <= lastbank; b++)
    sendbankPSEL0(b);
}

LOCAL_C VOID sendbanks7000()
{
  INT b;

  if (GETCS() == 0x7000 || GETDS() == 0x7000)
  {
    println("Can't dump 0x70000-0x7FFFF: CS or DS in that range!");
  }
  else
  {
    for (b = 0x00; b <= 0xFF; b++)
      sendbankPSEL1(b);
  }
}

LOCAL_C VOID sysver()
{
  TEXT szbuf[40], szromver[6], szosver[6];

  p_atos(szromver, "%05x", p_romversion());
  szromver[0] = szromver[1];
  szromver[1] = '.';

  p_atos(szosver, "%05x", p_version());
  szosver[0] = szosver[1];
  szosver[1] = '.';

  p_atos(szbuf, "EPOC16: %s   ROM: %s", szosver, szromver);
  println(szbuf);
}

/** Memory Testing Routines
 * 
 */
LOCAL_C VOID memtest6000()
{
#define MINIBUFFERSIZE 16
  static TEXT buf_send[MINIBUFFERSIZE];
  // static TEXT buf_rcv[BUFFERSIZE];

  println("Writing to 0600:0000, page 20h");
  p_atos(buf_send, "ThisIsSomeText!");
  println(buf_send);
  MEMPUTPSEL0(0x20, 0x0000, MINIBUFFERSIZE, buf_send);
  println(buf_send);
}

LOCAL_C VOID format4()
{
  static TEXT header[32];

  p_atos(header, "RAMDRIVE   ");
  header[11] = 8;
  header[24] = '!';
  MEMPUTPSEL0(0x08, 0x4200, 32, header);
  println("Done!");
}

/** SSD Routines
 * 
 * Functions for getting information about SSDs and dumping them. 
*/

/**
 * Grabs basic information about an SSD and prints it to the console.
 */
LOCAL_C VOID ssdinfo(TEXT *devname)
{
  P_DINFO dinfo;
  INT ret;
  TEXT szbuf[40];
  TEXT fulldevname[8];

  p_atos(fulldevname, "LOC::%c:", p_toupper(devname[0]));
  // println(fulldevname);

  ret = p_dinfo(fulldevname, &dinfo);
  if (ret < 0)
  {
    println("Failed.");
    return;
  }

  p_atos(szbuf, "Device: %s, Name: %s, Size: %ld", fulldevname, dinfo.name, dinfo.size);
  println(szbuf);
}

/**
 * Sends a dump of an SSD or peripheral ROM over a PLP link to the C: drive of the remote machine (REM::C:).
 */
LOCAL_C VOID sendssd(TEXT *devname)
{
#define BLOCKSIZE 256
  P_DINFO dinfo;
  INT ret;
  TEXT szbuf[40];
  TEXT fulldevname[8];
  TEXT tinydevname;
  UWORD curblock;

  LONG i;

  static UBYTE buf[BLOCKSIZE];

  VOID *fd;

  p_atos(fulldevname, "LOC::%c:", p_toupper(devname[0]));

  ret = p_dinfo(fulldevname, &dinfo);
  if (ret < 0)
  {
    println("ERROR: Can't open source device");
    niceerror_E_FILE(ret);
    return;
  }

  tinydevname = fulldevname[5]; // just get the drive letter

  p_atos(szbuf, "REM::C:\\%s.SSD", dinfo.name);
  if (p_open(&fd, szbuf, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
  {
    println("Can't create output file");
    println(szbuf);
    return;
  }

  println("Creating...");
  println(szbuf);
  println("To stop, kill EDisAsm from System Screen");
  for (i = 0; i < dinfo.size; i = i + BLOCKSIZE)
  {
    curblock = i / 256;
    p_atos(szbuf, "Writing block %d", curblock);
    wInfoMsg(szbuf);
    ret = p_locreadpdd(tinydevname, &i, buf, BLOCKSIZE);
    if (ret < 0)
    {
      switch (ret)
      {
      case E_GEN_OS:
        println("ERROR: Medium not mounted");
        break;
      case E_FILE_CORRUPT:
        println("ERROR: E_FILE_CORRUPT (Offset greater than SSD)");
        break;
      default:
        p_atos(szbuf, "ERROR: Unknown (%d)", ret);
        println(szbuf);
      }
      p_close(fd);
      return;
    }
    p_write(fd, buf, BLOCKSIZE);
  }
  println("Done.");
  p_close(fd);
}

/**
 * Saves a dump of an SSD or peripheral ROM to a local device, such as the RAMDRIVE or another SSD.
 */
LOCAL_C VOID savessd(TEXT *devargs)
{
#define BLOCKSIZE 256
  TEXT szbuf[40];
  P_DINFO dinfo;
  INT ret;

  TEXT fulldevsrcname[8], fulldevdestname[8];
  TEXT smalldevsrcname[2], smalldevdestname[2];

  UWORD curblock;
  UBYTE buf[BLOCKSIZE];
  ULONG devdestfree = 0;

  LONG i;

  VOID *fd;
  TEXT *devargsptr;

  if (p_slen(devargs) != 3 || devargs[1] != ' ')
  {
    println("ERROR: Invalid argument(s)");
    return;
  }

  devargsptr = devargs;

  ret = p_stoa(&devargsptr, "%c %c", smalldevsrcname, smalldevdestname);
  if (ret < 0)
  {
    switch (ret)
    {
    case E_GEN_OVER:
      println("ERROR: E_GEN_OVER");
      break;
    case E_GEN_FAIL:
      println("ERROR: E_GEN_FAIL");
      break;
    case E_GEN_ARG:
      println("ERROR: E_GEN_ARG");
      break;
    default:
      p_atos(szbuf, "ERROR: Unknown (%d)", ret);
      println(szbuf);
    }
    return;
  }

  smalldevsrcname[0] = p_toupper(smalldevsrcname[0]);
  smalldevdestname[0] = p_toupper(smalldevdestname[0]);

  if (smalldevsrcname[0] == smalldevdestname[0])
  {
    println("ERROR: Source and destination can't be the same");
    return;
  }

  p_atos(fulldevsrcname, "LOC::%c:", smalldevsrcname[0]);
  p_atos(fulldevdestname, "LOC::%c:", smalldevdestname[0]); // TODO: this needs to be a proper path in the future

  ret = p_dinfo(fulldevdestname, &dinfo);
  if (ret < 0)
  {
    println("ERROR: Can't open destination device");
    niceerror_E_FILE(ret);
    return;
  }
  if ((dinfo.mediatype % 256) == P_FMEDIA_ROM || (dinfo.mediatype % 256) == P_FMEDIA_WRITEPROTECTED)
  {
    println("ERROR: Destination device is read-only");
    return;
  }

  devdestfree = dinfo.free;

  ret = p_dinfo(fulldevsrcname, &dinfo);
  if (ret < 0)
  {
    println("ERROR: Can't open source device");
    niceerror_E_FILE(ret);
    return;
  }

#if 0
  p_atos(szbuf, "Source: %s (Name: %s)  Destination: %s", fulldevsrcname, dinfo.name, fulldevdestname);
  p_atos(szbuf, "Source: %s  Destination: %s", fulldevsrcname, fulldevdestname);
  println(szbuf);
#endif

  // TODO: Check that the file doesn't already exist

  if (dinfo.size > devdestfree)
  {
    println("Not enough free space on destination.");
    return;
  }

  p_atos(szbuf, "%s\\%s.SSD", fulldevdestname, dinfo.name);

  if (p_open(&fd, szbuf, P_FSTREAM | P_FREPLACE | P_FUPDATE) != 0)
  {
    println("ERROR: Can't create output file");
    println(szbuf);
    return;
  }

  println("Creating...");
  println(szbuf);
  println("To stop, kill EDisAsm from System Screen");

  for (i = 0; i < dinfo.size; i = i + BLOCKSIZE)
  {
    curblock = i / 256;
    p_atos(szbuf, "Writing block %d", curblock);
    wInfoMsg(szbuf);
    ret = p_locreadpdd(smalldevsrcname[0], &i, buf, BLOCKSIZE);
    if (ret < 0)
    {
      switch (ret)
      {
      case E_GEN_OS:
        println("ERROR: Medium not mounted");
        break;
      case E_FILE_CORRUPT:
        println("ERROR: E_FILE_CORRUPT (Offset greater than SSD)");
        break;
      default:
        p_atos(szbuf, "ERROR: Unknown (%d)", ret);
        println(szbuf);
      }
      p_close(fd);
      return;
    }
    p_write(fd, buf, BLOCKSIZE);
  }
  println("Done.");
  p_close(fd);
}

LOCAL_C VOID help(VOID)
{
#define HELPSTRINGS 14
  static TEXT *helpstr[HELPSTRINGS] = {
      "ADDRESS: (addr) are hex pairs SSSS:OOOO segment:offset, OOOO to keep segment",
      "         (nn) is a byte, e.g. f5",
      "DUMP:    db dw (addr) dump a page of bytes, words. \000 for next page",
      "VECTORS: ivt (nn) shows Vector Table, sendivt writes to REM::C:\\\IVT.LST",
      "         ivtlong (nn) shows vectors and functions.",
      "XMIT:    sendram384, sendram1, sendram2, sendrom1, sendrom2, sendrom384",
      "         send the relevant banks of memory over the NCP link. Files will be",
      "         created on your PC called RAM384.MEM, RAM1xx.MEM, RAM2xx.MEM,",
      "         ROM1xx.MEM, ROM2xx.MEM, ROM384.MEM. xx is replaced by the currently",
      "         selected bank no. Send all RAM/ROM banks: sendbanksX000. X=6,7,8,9.",
      "         Send an image of an SSD: sendssd X, where X is the drive letter.",
      "BANKS:   bank (nn) sets ROM bank, or on its own shows current ROM bank no.",
      "",
      "NB: sendrom384, sendram384, sendbanksX000 work, others might not",
  };
  UINT i;

  cls();
  for (i = 0; i < HELPSTRINGS; i++)
    println(helpstr[i]);
}

LOCAL_C VOID command_process(TEXT *cmd)
{
  static TEXT lastcmd[EDITLEN];
  TEXT *s, *d;
  TEXT buf[40];

  if (!*cmd)
    cmd = lastcmd;
  if (p_scmp("exit", cmd) == 0)
    p_exit(0);
  else if (p_scmp("help", cmd) == 0)
    help();
  else if (p_bcmpi("db", 2, cmd, 2) == 0)
  {
    if (parse_address(cmd + 2))
      dump_bytes();
  }
  else if (p_bcmpi("dw", 2, cmd, 2) == 0)
  {
    if (parse_address(cmd + 2))
      dump_words();
  }
  else if (p_bcmpi("ivtlong", 7, cmd, 7) == 0)
  {
    if (parse_intno(cmd + 3))
      ivtlong();
  }
  else if (p_bcmpi("ivt", 3, cmd, 3) == 0)
  {
    if (parse_intno(cmd + 3))
      ivt();
  }
  else if (p_scmp("sendram384", cmd) == 0)
    send(0x0000, 0x0000, 0x0600, "RAM384");
  else if (p_scmp("sendram1", cmd) == 0)
  {
    /* Need to iterate over all banks here */
    p_atos(buf, "RAM1%02x", psel0);
    send(0x0600, 0x0000, 0x0700, buf);
  }
  else if (p_scmp("sendram2", cmd) == 0)
  {
    /* Need to iterate over all banks here */
    p_atos(buf, "RAM2%02x", psel1);
    send(0x0700, 0x0000, 0x0800, buf);
  }
  else if (p_scmp("sendrom1", cmd) == 0)
  {
    /* Seems to be the same as 0x90000-0x9FFFF */
    p_atos(buf, "ROM1%02x", psel2);
    send(0x0800, 0x0000, 0x0900, buf);
  }
  else if (p_scmp("sendrom2", cmd) == 0)
  {
    p_atos(buf, "ROM2%02x", psel3);
    send(0x0900, 0x0000, 0x0A00, buf);
  }
  else if (p_scmp("sendrom384", cmd) == 0)
    send(0x0A00, 0x0000, 0x1000, "ROM384");
  else if (p_scmp("sendivt", cmd) == 0)
    send_ivt();
  else if (p_scmp("sendbanks6000", cmd) == 0)
  {
    sendbanks6000();
  }
  else if (p_bcmpi("sendbanks6000 ", 14, cmd, 14) == 0)
  {
    sendbanks6000selection(cmd + 14);
  }
  else if (p_scmp("sendbanks7000", cmd) == 0)
  {
    sendbanks7000();
  }
  else if (p_scmp("sendbanks8000", cmd) == 0)
  {
    sendbanks8000();
  }
  else if (p_scmp("sendbanks9000", cmd) == 0)
  {
    sendbanks9000();
  }
  else if (p_bcmpi("sendbanks9000 ", 14, cmd, 14) == 0)
  {
    sendbanks9000selection(cmd + 14);
  }
  else if (p_scmp("sendallrom", cmd) == 0)
  {
    sendbanks9000();
    send(0x0A00, 0x0000, 0x1000, "ROM384");
  }
  else if (p_scmp("banktest", cmd) == 0)
  {
    banktest();
  }
  else if (p_scmp("memtest6000", cmd) == 0)
  {
    memtest6000();
  }
    else if (p_scmp("bank", cmd) == 0)
  {
    p_atos(buf, "Current ROM bank is %02x", bankno);
    wInfoMsg(buf);
  }
  else if (p_scmp("a9rctrl", cmd) == 0)
  {
    p_atos(buf, "A9RControl: 0x%04x", GETA9RCTRL());
    println(buf);
    wInfoMsg(buf);
  }
  else if (p_scmp("a9rstat", cmd) == 0)
  {
    p_atos(buf, "A9RStatus: 0x%04x", GETA9RSTAT());
    println(buf);
    wInfoMsg(buf);
  }
  else if (p_bcmpi("bank", 4, cmd, 4) == 0)
  {
    if (parse_bankno(cmd + 4))
    {
      p_atos(buf, "ROM bank %02x selected", bankno);
      wInfoMsg(buf);
    }
  }
  else if (p_bcmpi("ssdinfo ", 8, cmd, 8) == 0)
  {
    ssdinfo(cmd + 8);
  }
  else if (p_bcmpi("sendssd ", 8, cmd, 8) == 0)
  {
    sendssd(cmd + 8);
  }
  else if (p_bcmpi("savessd ", 8, cmd, 8) == 0)
  {
    savessd(cmd + 8);
  }
  else if (p_scmp("sysver", cmd) == 0)
  {
    sysver();
  }
    else if (p_scmp("format4", cmd) == 0)
  {
    format4();
  }
  else if (p_scmp("cls", cmd) == 0)
  {
    cls();
  }
  else if (p_scmp("pixels", cmd) == 0)
  {
    p_atos(buf, "Screen size (x,y): %dx%d", machine_fullscreenwidth, machine_fullscreenheight);
    println(buf);
    wInfoMsg(buf);
  }
  for (s = cmd, d = lastcmd; *s && !p_isspace(*s); s++, d++)
    *d = *s;
  *d = '\0';
}

LOCAL_C VOID key_process(VOID)
{
  // INT ret, code;
  TEXT *t;

  /* Do something with key.keycode */
  if (key.keycode == W_KEY_HELP)
    hHelpSubSystem(EDISASM_HELP, 0);
  else if (key.keycode != W_KEY_RETURN)
    hEBHandleKey(ebH, key.keycode, key.modifiers);
  else
  {
    t = hEBSenseText(ebH);
    if (t)
      command_process(t);
    hEBSetText(ebH, "", 0);
    hEBEmphasise(ebH, TRUE);
  }
}

LOCAL_C VOID *CreateEditor(VOID)
{
  H_EDIT_BOX heb;
  // P_RECT p;

  heb.maxchars = EDITLEN;
  heb.vulen = machine_fullscreenwidth - text_width;
  heb.pos.x = 0;
  heb.pos.y = machine_fullscreenheight - text_height - text_descent;
  heb.win = MainWid;
  heb.font = FONT;
  heb.style = G_STY_MONO;
  return (hEBOpen(H_EDIT_BOX_FONT | H_EDIT_BOX_LEFT_CURSOR, &heb));
}

LOCAL_C VOID MainLoop(VOID)
{
  FOREVER
  {
    if (key_active)
      wFlush();
    else
    {
      uGetKeyA(&key_stat, &key);
      key_active = TRUE;
    }

    p_iowait();

    /* Keyboard? */
    if (key_stat != E_FILE_PENDING)
    {
      key_process();
      key_active = FALSE;
    }
  }
}

LOCAL_C VOID SpecificInit(VOID)
{
  LOCAL_D INT gci;
  // P_EXTENT pextent;
  G_FONT_INFO gfi;
  G_GC gc;

  p_unmarka();

  /* To hell with portability. *YOU WILL* run this on a Series 3a/c ! */
  uEnableGrey();
  gci = gCreateGC0(uFindMainWid());

  uEscape(FALSE);              // disable Psion-Esc
  MainWid = uFindMainWid();    // find id of main display window
  gCreateGC0(MainWid);

  Font.style = G_STY_MONO;
  Font.id = FONT;

  hInitAppRcb();

  gFontInfo(Font.id, Font.style, &gfi);
  text_height = gfi.ascent + gfi.descent + VERTICAL_LEADING;
  text_width = gfi.max_width;
  text_ascent = gfi.ascent;
  text_descent = gfi.descent;

  /* Set this into the graphics context */
  gc.font = Font.id;
  gc.style = Font.style;
  gSetGC(0, G_GC_MASK_FONT | G_GC_MASK_STYLE, &gc);

  if (machine_fullscreenrows)
  {
    rows = machine_fullscreenrows - 1;
    cols = machine_fullscreencols - 1;
  }
  else
  {
    rows = ((machine_fullscreenheight - (text_height * 2) - 4) / text_height);
    cols = 40;
  }

  rect.tl.x = 0;
  rect.tl.y = 0;
  rect.br.x = machine_fullscreenwidth;
  rect.br.y = rows * text_height + 4;
  gBorderRect(&rect, W_BORD_CORNER_1);
  rect.tl.x += 2;
  rect.tl.y += 2;
  rect.br.x = 2 + (cols * text_width);
  rect.br.y = 2 + (rows * text_height);

  ebH = CreateEditor();
  if (!ebH)
  {
    p_exit(-1);
  }

  printlnc("EDisAsm - SIBO/EPOC16 Exploratory Tool");
  printlnc("v0.0.5 (2023-03-24)"); // TODO: there must be a better way to set this at build time
  printlnc("Original version by Matt Gumbley,");
  printlnc("updated 2023 by Alex Brown.");
  println("");
  println("Type 'help' for help, 'exit' to exit.");
  hEBEmphasise(ebH, TRUE);
  bankno = p_getrombank();
}

GLDEF_C VOID main(VOID)
{
  machine_check();

  _UseFullScreen = TRUE;
  uCommonInit();
  SpecificInit();
  MainLoop();
}
