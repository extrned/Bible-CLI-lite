#include "tool.h"

int main(void) {
    int LAUNCHED = 1;
    ConfigParams pars = {0};
    LanguagePack pack = {0};
    char mainPath[PATH_SIZE], packPath[PATH_SIZE];

    if (getcwd(mainPath, PATH_SIZE) == NULL || getcwd(packPath, PATH_SIZE) == NULL) {
        makeError("Got an error with getting the working directory.");
        exit(1);
    }
    strcat(mainPath, "/bible.conf");
    strcat(packPath, "/languages.lconf");

    if (initConfig(&pars, mainPath) == 0) exit(1);
    if (initLanguagePack(&pack, pars.language) == 0) exit(1);
    if (processLanguagePack(&pack, packPath) == 0) exit(1);
    if (DEBUG_MODE) {
        makeLog("Debug mode is turned on. You can turn it off in tool.h.");
        makeLog("Main config path is %s.", mainPath);
        makeLog("Language pack config path is %s.", packPath);
makeLog("ConfigParams: language is '%s' and translation is '%s'.", pars.language, pars.translation);
        makeLog("Selected language pack is '%s'.", pack.langCode);
    }

    cliInit();
    cliLoop(&LAUNCHED);
    
    freeLanguagePack(&pack);
    if (DEBUG_MODE) makeLog("Language Pack memory was freed.");
    return 0;
}
