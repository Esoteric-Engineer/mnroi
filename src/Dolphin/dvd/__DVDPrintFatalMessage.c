static void (*FatalFunc)(void) = 0;

// dvdFatal.c's fatal-error message strings. 
// ShowMessage() (the only reader) and its Europe[] table are dead-stripped, so these survive only via force_active.
#pragma force_active on
char lbl_804D2460[0x6e] = "\n\n\n\x83G\x83\x89\x81[\x82\xaa\x94\xad\x90\xb6\x82\xb5\x82\xdc\x82\xb5\x82\xbd\x81" "B\n\n\x96{\x91\xcc\x82\xcc\x83p\x83\x8f\x81[\x83{\x83^\x83\x93\x82\xf0\x89\x9f\x82\xb5\x82\xc4\x93" "d\x8c\xb9\x82\xf0OFF\x82\xc9\x82\xb5\x81" "A\n\x96{\x91\xcc\x82\xcc\x8e\xe6\x88\xb5\x90\xe0\x96\xbe\x8f\x91\x82\xcc\x8ew\x8e\xa6\x82\xc9\x8f]\x82\xc1\x82\xc4\x82\xad\x82\xbe\x82\xb3\x82\xa2\x81" "B";
char lbl_804D24D0[0x7e] = "\n\n\nAn error has occurred.\nTurn the power off and refer to the\nNintendo GameCube Instruction Booklet\nfor further instructions.";
char lbl_804D2550[0x99] = "\n\n\nEin Fehler ist aufgetreten.\nBitte schalten Sie den Nintendo GameCube\naus und lesen Sie die Bedienungsanleitung,\num weitere Informationen zu erhalten.";
char lbl_804D25EC[0x8d] = "\n\n\nUne erreur est survenue.\nEteignez la console et r\xe9" "f\xe9rez-vous au\nmanuel d'instructions Nintendo GameCube\npour de plus amples informations.";
char lbl_804D267C[0x87] = "\n\n\nSe ha producido un error.\nApaga la consola y consulta el manual\nde instrucciones de Nintendo GameCube\npara obtener m\xe1s informaci\xf3n.";
char lbl_804D2704[0x80] = "\n\n\nSi \xe8 verificato un errore.\nSpegni (OFF) e controlla il manuale\nd'istruzioni del Nintendo GameCube\nper ulteriori indicazioni.";
char lbl_804D2784[0x89] = "\n\n\nEr is een fout opgetreden.\nZet de Nintendo GameCube uit en\nraadpleeg de handleiding van de\nNintendo GameCube voor nadere\ninstructies.";
#pragma force_active reset

void __DVDPrintFatalMessage(void) {
    if (FatalFunc != 0) {
        FatalFunc();
    }
}
