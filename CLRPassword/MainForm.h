#pragma once
#include "FUNCPassword.h"
namespace CLRPassword {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;



	/// <summary>
	/// Summary for MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private:
		System::Windows::Forms::Button^ generateBtn;
		System::Windows::Forms::Button^ registerBtn;
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->registerBtn = (gcnew System::Windows::Forms::Button());
			this->generateBtn = (gcnew System::Windows::Forms::Button());
			this->SuspendLayout();
			// 
			// registerBtn
			// 
			this->registerBtn->Location = System::Drawing::Point(136, 274);
			this->registerBtn->Name = L"registerBtn";
			this->registerBtn->Size = System::Drawing::Size(75, 23);
			this->registerBtn->TabIndex = 0;
			this->registerBtn->Text = L"button1";
			this->registerBtn->UseVisualStyleBackColor = true;
			//this->registerBtn->Click += gcnew System::EventHandler(this, &MainForm::registerBtn_Click);
			// 
			// generateBtn
			// 
			this->generateBtn->Location = System::Drawing::Point(461, 274);
			this->generateBtn->Name = L"generateBtn";
			this->generateBtn->Size = System::Drawing::Size(75, 23);
			this->generateBtn->TabIndex = 1;
			this->generateBtn->Text = L"button2";
			this->generateBtn->UseVisualStyleBackColor = true;
			this->generateBtn->Click += gcnew System::EventHandler(this, &MainForm::generateBtn_Click);
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(715, 433);
			this->Controls->Add(this->generateBtn);
			this->Controls->Add(this->registerBtn);
			this->Name = L"MainForm";
			this->Text = L"MainForm";
			this->ResumeLayout(false);

		}
#pragma endregion
	private: 
	/*System::Void registerBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ login = txtLogin->Text;
		String^ password = txtPassword->Text;

		// Hash the password and save it with the login
		String^ hashedPassword = HashPassword(password);
		SaveUser(login, hashedPassword);
	}*/
	System::Void generateBtn_Click(System::Object^ sender, System::EventArgs^ e) {
		String^ generatedPassword = GeneratePassword("Sony","Hewlett","Packard");
		//txtPassword->Text = generatedPassword;
	}
};
}
