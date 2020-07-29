/*
 * GENERATED FILE - DO NOT EDIT
 * Copyright (c) 2008-2013 Code Red Technologies Ltd,
 * Copyright 2015, 2018-2019 NXP
 * (c) NXP Semiconductors 2013-2019
 * Generated linker script file for MKL03Z32xxx4
 * Created from memory.ldt by FMCreateLinkMemory
 * Using Freemarker v2.3.23
 * MCUXpresso IDE v11.0.0 [Build 2516] [2019-06-05] on Aug 5, 2019 6:13:15 PM
 */

MEMORY
{
  /* Define each memory region */
  PROGRAM_FLASH (rx) : ORIGIN = 0x0, LENGTH = 0x8000 /* 32K bytes (alias Flash) */  
  SRAM (rwx) : ORIGIN = 0x1ffffe00, LENGTH = 0x800 /* 2K bytes (alias RAM) */  
}

  /* Define a symbol for the top of each memory region */
  __base_PROGRAM_FLASH = 0x0  ; /* PROGRAM_FLASH */  
  __base_Flash = 0x0 ; /* Flash */  
  __top_PROGRAM_FLASH = 0x0 + 0x8000 ; /* 32K bytes */  
  __top_Flash = 0x0 + 0x8000 ; /* 32K bytes */  
  __base_SRAM = 0x1ffffe00  ; /* SRAM */  
  __base_RAM = 0x1ffffe00 ; /* RAM */  
  __top_SRAM = 0x1ffffe00 + 0x800 ; /* 2K bytes */  
  __top_RAM = 0x1ffffe00 + 0x800 ; /* 2K bytes */  
