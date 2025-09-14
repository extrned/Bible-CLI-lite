#include "config_manager.h"

int initConfig(ConfigParams *vals, const char *configPath) {
    if (!vals || !configPath || strlen(configPath) == 0) {
        return makeError("Your config path and config parameters must be real values.");
    }

    char line[256];
    const char *fileMode = "r";
    FILE *f = fopen(configPath, fileMode);

    while (fgets(line, sizeof(line), f) != NULL) {
        line[strcspn(line, "\n")] = 0;
        if (strlen(line) == 0 || line[0] == '*') continue; // * is a symbol for comments
        char *delimiter = strchr(line, '=');
        if (delimiter == NULL) {
            makeError("Invalid line is found in bible.conf. For comments you should use an asterisk '*' symbol.");
            continue;
        }
        *delimiter = 0;
        char *key = trim(line);
        char *val = trim(delimiter + 1);

        if (strlen(key) == 0 || strlen(val) == 0) {
            makeError("Error: Empty key or value. Check the file bible.conf for errors.");
            continue;
        }
        // VALUES
        if (strcmp(key, "language") == 0) {
            strncpy(vals->language, val, sizeof(vals->language) - 1);
            vals->language[sizeof(vals->language) - 1] = '\0';
        } else if (strcmp(key, "translation") == 0) {
            strncpy(vals->translation, val, sizeof(vals->translation) - 1);
            vals->translation[sizeof(vals->translation) - 1] = '\0';
        }
    }

    fclose(f);
    return 1;
}
