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

#ifndef LOG_H
#define LOG_H

#include <iostream>
#include <fstream>
#include <string>
#include <cstdarg>
#include <cstdio>
#include <exception>

enum class LogMode
{
    Info     = 0,
    Warning  = 1,
    Error    = 2,
    Critical = 3
};

class jkscLog
{
public:
    jkscLog();
    jkscLog(const std::string& fileName);

    bool Init();
    bool Init(const std::string& fileName);

    void Write(const std::string& logInfo);
    void WriteLine(const std::string& logInfo);
    void WriteF(const std::string& formatLogInfo, ...);

    bool Finish();

    ~jkscLog()
    {
        this->Finish();
    }

private:
    std::ofstream m_logFile;
    std::string m_logFileName;
    const std::string GetDateTimeNow();
};

#endif // LOG_H