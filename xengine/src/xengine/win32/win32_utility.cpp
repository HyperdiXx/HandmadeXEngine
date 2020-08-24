
#define DEFAULT_BUFFER_SIZE 1024

internal std::string getCurrentDirectory()
{
    TCHAR buffer[DEFAULT_BUFFER_SIZE];
    GetCurrentDirectory(sizeof(buffer), buffer);

    std::string str = buffer;
    return str;
}

internal char* loadEntireFile(const char *name)
{
    char *result = 0;

    FILE *f = fopen(name, "r");

    if (f)
    {
        fseek(f, 0, SEEK_END);
        size_t file_size = ftell(f);
        fseek(f, 0, SEEK_SET);
        result = (char*)malloc(file_size + 1);

        fread(result, file_size, 1, f);
        result[file_size] = 0;

        fclose(f);
    }

    return result;
}