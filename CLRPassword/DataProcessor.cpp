#include "DataProcessor.h"
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <msclr\marshal_cppstd.h>

using namespace System;
using namespace msclr::interop;
using namespace std;

DataProcessor::DataProcessor(String^ pipeName)
{
    this->pipeName = pipeName;
    pipe = CreateNamedPipe(
        marshal_as<wstring>(pipeName).c_str(),
        PIPE_ACCESS_DUPLEX,
        PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
        1,
        4096,
        4096,
        NMPWAIT_USE_DEFAULT_WAIT,
        NULL);
}

void DataProcessor::ReadAndVerifyData(String^ filePath)
{
    ifstream file(marshal_as<string>(filePath));
    vector<pair<int, int>> coordinates;
    string line;
    while (getline(file, line))
    {
        istringstream iss(line);
        int x, y;
        if (!(iss >> x >> y))
        {
            throw gcnew Exception("Invalid data format");
        }
        if (x < 0 || x > 100 || y < 0 || y > 100)  // Assuming range is 0-100 for both x and y
        {
            throw gcnew Exception("Coordinates out of range");
        }
        coordinates.push_back(make_pair(x, y));
    }

    // Convert coordinates to managed array
    data = gcnew array<String^>(coordinates.size());
    for (size_t i = 0; i < coordinates.size(); ++i)
    {
        data[i] = String::Format("{0} {1}", coordinates[i].first, coordinates[i].second);
    }
}

void DataProcessor::SortData()
{
    vector<string> sortedData;
    for each (String ^ entry in data)
    {
        sortedData.push_back(marshal_as<string>(entry));
    }

    sort(sortedData.begin(), sortedData.end());

    for (size_t i = 0; i < sortedData.size(); ++i)
    {
        data[i] = marshal_as<String^>(sortedData[i]);
    }
}

void DataProcessor::WriteDataToPipe()
{
    ConnectNamedPipe(pipe, NULL);

    for each (String ^ entry in data)
    {
        string str = marshal_as<string>(entry);
        DWORD written;
        WriteFile(pipe, str.c_str(), str.length(), &written, NULL);
    }

    FlushFileBuffers(pipe);
    DisconnectNamedPipe(pipe);
}

array<String^>^ DataProcessor::ReadDataFromPipe()
{
    ConnectNamedPipe(pipe, NULL);

    vector<string> receivedData;
    char buffer[128];
    DWORD read;
    while (ReadFile(pipe, buffer, sizeof(buffer) - 1, &read, NULL) && read > 0)
    {
        buffer[read] = '\0';
        receivedData.push_back(string(buffer));
    }

    DisconnectNamedPipe(pipe);

    array<String^>^ managedData = gcnew array<String^>(receivedData.size());
    for (size_t i = 0; i < receivedData.size(); ++i)
    {
        managedData[i] = marshal_as<String^>(receivedData[i]);
    }
    return managedData;
}

void DataProcessor::NotifyCompletion()
{
    // Implementation for notifying the completion (e.g., using an event or another pipe message)
}

