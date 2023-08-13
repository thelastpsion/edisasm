# EDisAsm - EPOC 16 Disassembler/Dumper

&copy;1998 Matt Gumbley, updated 2023 Alex Brown. Released under the Apache2 License.

This utility is an exploratory tool developed for the investigation into
porting Linux to the SIBO architecture.

## Warning

**THIS UTILITY IS PROVIDED AS-IS WITH NO WARRANTY.**

It might crash your Psion - you have been warned. We accept no responsibility
for any data loss that might occur as a result of you running this on your
Psion.

**Please back up your data before using EDisAsm!**

## Getting Started

You will need...

- The appropriate serial cable for your Psion (i.e. 3Link, Honda cable, Workabout dongle)
- A computer with a serial port (or compatible USB to RS232 adapter - see below)
- Software to transfer data between your Psion and your computer (PsiWin, McLink, SDBG)

### USB to RS232 Adapters

This is more of a general note on using USB to RS232 adapters. People have had varying success with transferring files using different adapters. It very much depends on the chipset. Here are some examples:

- **PL2303**: The best USB-RS232 chipset for the job. This is known to work with DOSBox and DOSBox Staging, so McLink and SDBG will work fine. It also works with PsiWin in Windows XP under VirtualBox.
- **CH340**: I have had success with using a CH340-based adapter with PsiWin in Windows XP under VirtualBox. However, DOSBox doesn't like the CH340, so reliability with McLink and SDBG has been limited.

### Using PLPTOOLS

PLPTOOLS is a set of libraries and utilities that allow file transfers to be made directly on Linux.

The disadvantage of PLPTOOLS is that it does not allow Psion devices to initiate file transfers. While this is probably better for security, it does mean that commands like `sendbanks9000` and `sendssd` won't work.

As a workaround for SSD dumping, you can use `savessd`, which saves SSD images to local storage, such as another SSD or the ramdrive. This will allow you to pull the images from the Psion. The disadvantage of this is a lack of storage space on the machine, so you will either need a RAM SSD bigger than the one you're going to dump, or a Psion with a relatively large/clean ramdrive.

## Compatibility

### Hardware

EDisAsm is designed to run on the following machines:

- **Psion**
  - Series 3a (both the 256K/512K model and the 1MB/2MB model)
  - Series 3c
  - Series 3mx
  - Siena
  - Workabout (1MB)
  - Workabout mx
- **Acorn**
  - Pocket Book II (3a clone)
- **Xemplar**
  - Pocket Book III (3mx clone)

It will not run on the original Psion Series 3 (or 3s), or the original Acorn Pocket Book (as it's an S3 clone). It also won't run on the MC or HC ranges.

### DOS Emulator (`s3aemul`, `s3cemul`, etc)

EDisAsm will run on Psion's old DOS emulators, but things do not work as expected. This is because the old emulators are really just runtime environments. They run EPOC16, but they emulate almost none of the SIBO hardware. Expect strange results and crashes.

### MAME Emulator

Current tests show that EDisAsm will run on the fledgling SIBO emulator. This might not be useful for dumping ROMs or SSDs, but it may help with exploratory work into EPOC16's architecture, or to look at your own programs' RAM usage.

## Command List

This list is incomplete, but should help you with the basics.

### `db`

Shows a hex view of the current address, 16 bytes per line. **Enter** shows the next block.

### `dw`

Shows a hex view of the current block, 8 words per line. **Enter** shows the next block.

### `savessd`

```
savessd src_drive_letter dest_drive_letter
```

Saves an image of an SSD to the root of a local drive on the Psion. For example, to copy the SSD in A: to the ramdrive, type:

```
savessd a m
```

### `sendbanks6000`, `sendbanks7000`, `sendbanks8000`, `sendbanks9000`

```
sendbanks6000 [firstblock [lastblock]]
sendbanks7000
sendbanks8000
sendbanks9000 [firstblock [lastblock]]
```

Sends the contents of memory in 64K blocks over a PLP serial link.

By default, `sendbanks9000` sends blocks 0x80 to 0x9F.

`sendbanks6000` and `sendbanks9000` also have the ability to select which banks you want to dump. `firstblock` and `lastblock` are block numbers in hex. For example, if you want to dump blocks 0x8C to 0x92, you would type:

```
sendblocks9000 8c 92
```

### `sendrom384`

```
sendrom384
```

Sends the fixed ROM memory area over a PLP link. This is mapped to the last 6 blocks of the EPOC16 ROM. On a 1MB ROM machine such as the 256k/512k 3a, this is blocks 0x8A to 0x8F. On 2MB ROM machines, this is blocks 0x9A to 0x9F.

### `sendram384`

```
sendrom384
```

Sends the fixed RAM memory area over a PLP link. This is mapped to the first 6 blocks of RAM (0x00 to 0x05).

### `sendssd`

```
sendssd driveletter
```

Sends an image of an SSD over a PLP link.

## Quick instructions to generate a commented ROM listing

Copy `EDISASM.APP` to the `\APP\` folder on your Psion (this can be on any drive, including an SSD).

Install on the System Screen using **Psion-I**, and run EDisAsm on your Psion.

Run MCLINK/RCOM/PsiWin on your PC. Keep your Psion Link active.

Type `help` in EDisAsm.

Various commands shown there will enable you to save a ROM image file on your
PC. (try `sendrom384`, which will save ROM384.MEM on your PC - it's 384KB in
size, and holds the fixed ROM memory area image.)

Type `exit` in EDisAsm. Close MCLINK.

You'll be able to generate a listing of `ROM384.MEM` using your favourite
disassembler. (SID, DEBUG, NDISASM, IDA, etc)
