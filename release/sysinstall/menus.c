/*
 * The new sysinstall program.
 *
 * This is probably the last program in the `sysinstall' line - the next
 * generation being essentially a complete rewrite.
 *
 * $Id: menus.c,v 1.2 1995/04/27 18:03:54 jkh Exp $
 *
 * Copyright (c) 1995
 *	Jordan Hubbard.  All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer, 
 *    verbatim and that no modifications are made prior to this 
 *    point in the file.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. All advertising materials mentioning features or use of this software
 *    must display the following acknowledgement:
 *	This product includes software developed by Jordan Hubbard
 *	for the FreeBSD Project.
 * 4. The name of Jordan Hubbard or the FreeBSD project may not be used to
 *    endorse or promote products derived from this software without specific
 *    prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY JORDAN HUBBARD ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL JORDAN HUBBARD OR HIS PETS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, LIFE OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 *
 */

#include "sysinstall.h"

/* All the system menus go here.
 *
 * Hardcoded things like version number strings will disappear from
 * these menus just as soon as I add the code for doing inline variable
 * expansion.
 */

extern DMenu MenuDocumentation;
extern DMenu MenuMedia;
extern DMenu MenuInstallType;
extern DMenu MenuInstallOptions;

/* The initial installation menu */
DMenu MenuInitial = {
    DMENU_NORMAL_TYPE,
    "Welcome to FreeBSD 2.0.5!",	/* title */
    "This is the main menu of the FreeBSD installation system.  Please\n\
select one of the options below by using the arrow keys or typing the\n\
first character of the option name you're interested in.  Invoke an\n\
option by pressing enter.",		/* prompt */
    "Press F1 for further help",	/* help line */
    "help/initial.hlp",			/* help file */
    { { "Usage", "Quick start - How to use this menu system.",	/* U */
	  DMENU_DISPLAY_FILE, (void *)"help/initial.hlp", 0 },
    { "Doc", "More detailed documentation on FreeBSD.",		/* D */
	  DMENU_SUBMENU, (void *)&MenuDocumentation, 0 },
    { "Lang", "Select natural language options.",		/* L */
	  DMENU_SUBMENU, (void *)&MenuLanguage, 0 },
    { "Express", "Express installation (don't ask)",		/* E */
	  DMENU_CALL, (void *)installExpress, 0 },
    { "Custom", "Custom installation (please ask)",		/* C */
	  DMENU_CALL, (void *)installCustom, 0 },
    { "Maint", "Go into maintainance mode (`fix it').",		/* M */
	  DMENU_CALL, (void *)installMaint, 0 },
    { NULL } },
};

/* The main documentation menu */
DMenu MenuDocumentation = {
    DMENU_NORMAL_TYPE,
    "Documentation for FreeBSD 2.0.5",	/* Title */
    "If you are at all unsure about the configuration of your hardware\n\
or are looking to build a system specifically for FreeBSD, read the\n\
Hardware guide!  New users should also read the Install document for\n\
a step-by-step tutorial on installing FreeBSD.  For general information,\n\
consult the README file.  If you're having other problems, you may find\n\
answers in the FAQ.",
    "Having trouble?  Press F1 for help!", /* help line */
    "help/usage.hlp",			/* help file */
   { { "README", "Read this for a general description of FreeBSD", /* R */
	 DMENU_DISPLAY_FILE, (void *)"help/readme.hlp", 0 },
   { "Hardware", "The FreeBSD survival guide for PC hardware.",    /* H */
	 DMENU_DISPLAY_FILE, (void *)"help/hardware.hlp", 0 },
   { "Install", "A step-by-step guide to installing FreeBSD.",     /* I */
	 DMENU_DISPLAY_FILE, (void *)"help/install.hlp", 0 },
   { "FAQ", "Frequently Asked Questions about FreeBSD.",           /* F */
	 DMENU_DISPLAY_FILE, (void *)"help/faq.hlp", 0 },
   { NULL } },
};

/* The language selection menu */
/*
 * Note:  The RADIO menus use a slightly different syntax.  If an item
 * name starts with `*', it's considered to be "ON" by default,
 * otherwise off.
 */
DMenu MenuLanguage = {
    DMENU_RADIO_TYPE | DMENU_SELECTION_RETURNS,
    "Natural language selection",	/* title */
    "Please specify the language you'd like to use by default.\n\n\
While almost all of the system's documentation is still\n\
written in english (and may never be translated), there are a few\n\
guides and types of system documentation that may be written in your\n\
preferred language.  When such are found, they will be used instead\n\
of the english versions.",		/* prompt */
    "Press F1 for more information",	/* help line */
    "help/language.hlp",		/* help file */
   { { "Danish", "Danish language and character set (ISO-8859-1)", /* D */
	 DMENU_SET_VARIABLE, (void *)"LANG=en", 0 },
   { "*English", "English language (system default)",              /* E */
	 DMENU_SET_VARIABLE, (void *)"LANG=en", 0 },
   { "French", "French language and character set (ISO-8859-1)",   /* F */
	 DMENU_SET_VARIABLE, (void *)"LANG=fr", 0 },
   { "German", "German language and character set (ISO-8859-1)",   /* G */
	 DMENU_SET_VARIABLE, (void *)"LANG=de", 0 },
   { "Japanese", "Japanese language and character set (JIS?)",     /* J */
	 DMENU_SET_VARIABLE, (void *)"LANG=jp", 0 },
   { "Russian", "Russian language and character set (cp866-8x14)", /* R */
	 DMENU_SET_VARIABLE, (void *)"LANG=ru", 0 },
   { NULL } },
};

/* The media selection menu */
DMenu MenuMedia = {
    DMENU_NORMAL_TYPE,
    "Choose Installation Media",
    "FreeBSD can be installed from a variety of different installation\n\
media, from floppies to the Internet.  If you're installing FreeBSD from\n\
a supported CDROM drive then this is generally the best method to\n\
use unless you have some overriding reason for using another method.",
    "Press F1 for more information on the various media types",
    "help/media.hlp",
    { { "CDROM", "Install from a FreeBSD CDROM",
	  DMENU_CALL, (void *)mediaSetCDROM, 0 },
    { "FLOPPY", "Install from a floppy disk set",
	  DMENU_CALL, (void *)mediaSetFloppy, 0 },
    { "DOS", "Install from a DOS partition",
	  DMENU_CALL, (void *)mediaSetDOS, 0 },
    { "TAPE", "Install from SCSI or QIC tape",
	  DMENU_CALL, (void *)mediaSetTape, 0 },
    { "FTP", "Install from an Internet FTP server",
	  DMENU_CALL, (void *)mediaSetFTP, 0 },
    { "FILESYSTEM", "Install from a UFS or NFS mounted distribution",
	  DMENU_CALL, (void *)mediaSetFS, 0 },
    { NULL } },
};

/* The installation type menu */
DMenu MenuInstallType = {
    DMENU_NORMAL_TYPE,
    "Choose Installation Type",
    "blah blah",
    NULL,
    NULL,
    { { NULL } },
};

/* The installation options menu */
DMenu MenuInstallOptions = {
    DMENU_NORMAL_TYPE,
    "Choose Installation Options",
    "blah blah",
    NULL,
    NULL,
    { { NULL } },
};

/* The main installation menu */
DMenu MenuInstall = {
    DMENU_NORMAL_TYPE,
    "Choose Installation Options",		/* title */
    "Before installation can continue, you need to specify a few items\n\
of information regarding the location of the distribution and the kind\n\
of installation you want to have (and where).  There are also a number\n\
of options you can specify in the Options menu.  If you do not wish to\n\
install FreeBSD at this time, you may select Cancel to leave this menu",
    "You may wish to read the install guide - press F1 to do so",
    "help/install.hlp",
    { { "Media", "Choose Installation media type",		/* M */
	  DMENU_SUBMENU, (void *)&MenuMedia, 0 },
    { "Type", "Choose the type of installation you want",	/* T */
	  DMENU_SUBMENU, (void *)&MenuInstallType, 0 },
    { "Options", "Specify installation options",		/* O */
	  DMENU_SUBMENU, (void *)&MenuInstallOptions, 0 },
    { "Proceed", "Proceed with installation",			/* P */
	  DMENU_CANCEL, (void *)NULL, 0 },
    { NULL } },
};

