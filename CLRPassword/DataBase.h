#pragma once

using namespace System;
using namespace System::Windows::Forms;
using namespace System::Drawing;
using namespace System::Data;
using namespace System::Data::SqlClient;

public ref class DataBase
{
private:
    String^ connectionString = "Data Source=(LocalDB)\\MSSQLLocalDB;Initial Catalog=AppDataScan;Integrated Security=True";
    SqlConnection^ connection;

public:
    void RegisterUser(String^ login, String^ hashedpassword);

    bool LoginUser(String^ login, String^ hashedpassword);

    DataBase() {
        connection = gcnew SqlConnection(connectionString);
    }
};



