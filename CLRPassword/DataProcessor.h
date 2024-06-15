#pragma once

#include <vector>
#include <string>
#include <windows.h>

using namespace System;

public ref class DataProcessor
{
private:
    String^ pipeName;
    HANDLE pipe;
    array<String^>^ data;

public:
    DataProcessor(String^ pipeName);
    void ReadAndVerifyData(String^ filePath);
    void SortData();
    void WriteDataToPipe();
    array<String^>^ ReadDataFromPipe();
    void NotifyCompletion();
    array<String^>^ GetData() { return data; }
};
