#include "DataBase.h"


void DataBase::RegisterUser(String^ login, String^ hashedpassword) {
    try {
        connection->Open();

        String^ query = "INSERT INTO USERS (userLogin, userPassword) VALUES (@login, @passwordHash)";
        SqlCommand^ command = gcnew SqlCommand(query, connection);
        command->Parameters->AddWithValue("@login", login);
        command->Parameters->AddWithValue("@passwordHash", hashedpassword);

        int result = command->ExecuteNonQuery();

        if (result > 0) {
            MessageBox::Show("Вы успешно зарегестрировались.", "Успешно", MessageBoxButtons::OK, MessageBoxIcon::Information);
        }
        else {
            MessageBox::Show("Регистрация провалилась.", "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        }

        connection->Close();
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
    }
}

bool  DataBase::LoginUser(String^ login, String^ hashedpassword) {
    try {
        connection->Open();

        SqlDataAdapter^ adapter = gcnew SqlDataAdapter();
        DataTable^ table = gcnew DataTable();

        String^ querystring = "select ID, userLogin, userPassword from USERS where userLogin = '"+ login +"' and userPassword = '"+ hashedpassword +"'";
        SqlCommand^ _logincheck = gcnew SqlCommand(querystring, connection);

        adapter->SelectCommand = _logincheck;
        adapter->Fill(table);

        if (table->Rows->Count == 1)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    catch (Exception^ ex) {
        MessageBox::Show("Ошибка: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
        return false;
    }
}