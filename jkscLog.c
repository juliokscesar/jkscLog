/*
MIT License

Copyright (c) 2021 juliokscesar

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "jkscLog.h"

#if defined(WIN32) || defined(_WIN32)
#include <windows.h>
#endif

static FILE *logFile;

void createLogDir()
{
    #if defined(WIN32) || defined(_WIN32)
    CreateDirectoryA("logs", NULL);
    #else
    system("mkdir -p ./logs");
    #endif
}

int jkscLogInit()
{
    if (!logFile)
    {
        createLogDir();
        logFile = fopen("logs/logfile.log", "w");
    }

    jkscLogInfo("Log Intiated");
    return !(logFile == NULL);
}

int jkscLogInitCustom(const char* fileName)
{
    char filePath[256] = "logs/";
    strncat(filePath, fileName, 255);

    if (!logFile)
    {
        createLogDir();
        logFile = fopen(filePath, "w");
    }

    jkscLogInfo("Log Initiated");
    return !(logFile == NULL);
}

void jkscLogWriteMode(int logMode, char *log)
{
    if (!logFile)
        return;

    char *dateTime = GetCurrentDateTime();
    
    char *modes[] = { "INFO", "DEBUG", "WARN", "CRITICAL" };
    char *colors[] = { ANSI_COLOR_BLUE, ANSI_COLOR_GREEN, ANSI_COLOR_YELLOW, ANSI_COLOR_RED };

    fprintf(logFile, "[%s] [%s] %s\n", dateTime, modes[logMode], log);

    printf("[%s] [%s%s%s] %s\n", dateTime, colors[logMode], modes[logMode], ANSI_COLOR_RESET, log);

    free(dateTime);
    free(log);
}

void jkscLogInfo(const char *logInfo, ...)
{
    va_list args;
    va_start(args, logInfo);

    const int logSize = (int)strlen(logInfo) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logInfo, args);

    jkscLogWriteMode(INFO, log);

    va_end(args);
}

void jkscLogDebug(const char *logDebug, ...)
{
	va_list args;
	va_start(args, logDebug);

	const int logSize = (int)strlen(logDebug) + 256;
	char *log = malloc(sizeof(char) * logSize);
	
	vsnprintf(log, logSize - 1, logDebug, args);

	jkscLogWriteMode(DEBUG, log);

	va_end(args);
}

void jkscLogWarn(const char *logWarn, ...)
{
    va_list args;
    va_start(args, logWarn);

    const int logSize = (int)strlen(logWarn) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logWarn, args);

    jkscLogWriteMode(WARN, log);

    va_end(args);
}

void jkscLogCritical(const char *logCritical, ...)
{
    va_list args;
    va_start(args, logCritical);

    const int logSize = (int)strlen(logCritical) + 256;
    char *log = malloc(sizeof(char) * logSize);

    vsnprintf(log, logSize - 1, logCritical, args);

    jkscLogWriteMode(CRITICAL, log);

    va_end(args);
}

int jkscLogFinish()
{
    jkscLogInfo("Log Finished");
    
    if (logFile)
        fclose(logFile);

    return (logFile == NULL);
}

char *GetCurrentDateTime()
{
    time_t t = time(0);
    struct tm *now = localtime(&t);

    char *dateTime = malloc(sizeof(char) * 20);
    strftime(dateTime, 20, "%Y-%m-%d %H:%M:%S", now);

    return dateTime;
}
