
#include <string>

namespace xe_config
{
    static void parseConfigFile(const char * data, ConfigData * cd)
    {
        char data_string[128];
        strcpy(data_string, data);

        while (data_string != "\n")
        {
            char *split_name = strtok(data_string, ":");
            char *result_value = strtok(NULL, "\n");

            if (strcmp(split_name, "name") == 0)
            {
                cd->name = result_value;
            }
            else if (strcmp(split_name, "windowed") == 0)
            {
                if (strcmp(result_value, "true") == 0)
                    cd->windowed = true;
                else
                    cd->windowed = false;
            }
        }

    }
}
