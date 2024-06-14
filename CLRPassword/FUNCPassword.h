#pragma once

#include <cliext/vector>

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Security::Cryptography;


public ref class funcpassword {
public:
    String^ GeneratePassword(String^ word1, String^ word2, String^ word3);

    String^ HashPassword(String^ password);
};