#pragma once

using namespace System;
using namespace System::ComponentModel;
using namespace System::Collections;
using namespace System::Windows::Forms;
using namespace System::Data;
using namespace System::Drawing;

String^ GeneratePassword(String^ word1, String^ word2, String^ word3) {
    String^ alphabet = "abcdefghijklmnopqrstuvwxyz";
    String^ password = "";

    // Сумма количеств символов в первом и третьем словах
    int sum = word1->Length + word3->Length;
    int index1 = (sum - 1) % 26;
    password += alphabet[index1];

    // Буква, предшествующая последней букве второго слова
    char lastChar = word2[word2->Length - 1];
    char previousChar = (lastChar == 'a') ? 'z' : lastChar - 1;
    password += Convert::ToChar(previousChar);

    // Средняя буква третьего слова
    char middleChar;
    if (word3->Length % 2 == 1) {
        middleChar = word3[word3->Length / 2];
        middleChar = (middleChar == 'z') ? 'a' : middleChar + 1;
    }
    else {
        middleChar = word3[(word3->Length / 2) - 1];
        middleChar = (middleChar == 'a') ? 'z' : middleChar - 1;
    }
    password += Convert::ToChar(middleChar);

    // Буква, следующая за первой буквой первого слова
    char firstChar = word1[0];
    char nextChar = (firstChar == 'z') ? 'a' : firstChar + 1;
    password += Convert::ToChar(nextChar);

    return password;
}

/*String^ HashPassword(String^ password) {
	array<Byte>^ data = Encoding::UTF8->GetBytes(password);
	array<Byte>^ hashedData;

	using (SHA256^ sha256 = SHA256::Create()) {
		hashedData = sha256->ComputeHash(data);
	}

	return BitConverter::ToString(hashedData);
}*/