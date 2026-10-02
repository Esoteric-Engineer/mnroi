typedef unsigned int u32;

// Scanned by dvd.c's IsImmCommandWithResult (all -1, never matching) through a plain extern.
// Defining them in dvd.c hoists a .data pool base into cbForStateBusy.
u32 lbl_804D21F8[3] = { -1, -1, -1 };

// DVDChangeDiskAsync's company-name diagnostic; dead-stripped, so nothing reads it.
#pragma force_active on
char lbl_804D2204[0x44] = "DVDChangeDiskAsync(): You can't specify NULL to company name.  \n";
#pragma force_active reset
