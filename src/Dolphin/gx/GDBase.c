typedef unsigned char u8;

// Nothing in the dol references this (the GD* functions that read it were dead-stripped), so it needs the config.yml force_active entry to survive the link.
u8* __GDCurrentDL;
