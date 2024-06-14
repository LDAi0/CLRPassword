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
		/// Элементы на форме НЕ ИЗМЕНЯТЬ!!!!!!!!!!!!!!
		System::Windows::Forms::Button^ generateBtn;
		System::Windows::Forms::Button^ registerBtn;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ loginTextBox;
	private: System::Windows::Forms::TextBox^ passwordTextBox;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Panel^ panel1;
		   System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		   /// Элементы на форме НЕ ИЗМЕНЯТЬ!!!!!!!!!!!!!!
		   void InitializeComponent(void)
		   {
			   this->registerBtn = (gcnew System::Windows::Forms::Button());
			   this->generateBtn = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->loginTextBox = (gcnew System::Windows::Forms::TextBox());
			   this->passwordTextBox = (gcnew System::Windows::Forms::TextBox());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->panel1 = (gcnew System::Windows::Forms::Panel());
			   this->panel1->SuspendLayout();
			   this->SuspendLayout();
			   // 
			   // registerBtn
			   // 
			   this->registerBtn->BackColor = System::Drawing::Color::LightSkyBlue;
			   this->registerBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->registerBtn->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->registerBtn->Location = System::Drawing::Point(164, 303);
			   this->registerBtn->Name = L"registerBtn";
			   this->registerBtn->Size = System::Drawing::Size(141, 35);
			   this->registerBtn->TabIndex = 0;
			   this->registerBtn->Text = L"Зарегестрироваться";
			   this->registerBtn->UseVisualStyleBackColor = false;
			   // 
			   // generateBtn
			   // 
			   this->generateBtn->BackColor = System::Drawing::Color::LightSkyBlue;
			   this->generateBtn->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->generateBtn->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->generateBtn->Location = System::Drawing::Point(330, 303);
			   this->generateBtn->Name = L"generateBtn";
			   this->generateBtn->Size = System::Drawing::Size(143, 35);
			   this->generateBtn->TabIndex = 1;
			   this->generateBtn->Text = L"Сгенерировать";
			   this->generateBtn->UseVisualStyleBackColor = false;
			   this->generateBtn->Click += gcnew System::EventHandler(this, &MainForm::generateBtn_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 18, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label1->Location = System::Drawing::Point(239, 42);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(173, 31);
			   this->label1->TabIndex = 2;
			   this->label1->Text = L"Регистрация";
			   // 
			   // loginTextBox
			   // 
			   this->loginTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->loginTextBox->Location = System::Drawing::Point(229, 150);
			   this->loginTextBox->Name = L"loginTextBox";
			   this->loginTextBox->Size = System::Drawing::Size(186, 25);
			   this->loginTextBox->TabIndex = 3;
			   // 
			   // passwordTextBox
			   // 
			   this->passwordTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->passwordTextBox->Location = System::Drawing::Point(229, 224);
			   this->passwordTextBox->Name = L"passwordTextBox";
			   this->passwordTextBox->Size = System::Drawing::Size(186, 25);
			   this->passwordTextBox->TabIndex = 4;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label2->Location = System::Drawing::Point(160, 151);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(63, 21);
			   this->label2->TabIndex = 5;
			   this->label2->Text = L"Логин:";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(0)));
			   this->label3->Location = System::Drawing::Point(150, 225);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(73, 21);
			   this->label3->TabIndex = 6;
			   this->label3->Text = L"Пароль:";
			   // 
			   // panel1
			   // 
			   this->panel1->BackColor = System::Drawing::Color::LightSkyBlue;
			   this->panel1->Controls->Add(this->label1);
			   this->panel1->Location = System::Drawing::Point(-7, -12);
			   this->panel1->Name = L"panel1";
			   this->panel1->Size = System::Drawing::Size(647, 104);
			   this->panel1->TabIndex = 7;
			   // 
			   // MainForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->ClientSize = System::Drawing::Size(625, 411);
			   this->Controls->Add(this->panel1);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->passwordTextBox);
			   this->Controls->Add(this->loginTextBox);
			   this->Controls->Add(this->generateBtn);
			   this->Controls->Add(this->registerBtn);
			   this->Name = L"MainForm";
			   this->Text = L"MainForm";
			   this->panel1->ResumeLayout(false);
			   this->panel1->PerformLayout();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion
	private:
		System::Void registerBtn_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ login = loginTextBox->Text;
			String^ password = passwordTextBox->Text;

			// Hash the password and save it with the login
			String^ hashedPassword = HashPassword(password);
		}
		System::Void generateBtn_Click(System::Object^ sender, System::EventArgs^ e) {
			String^ generatedPassword = GeneratePassword("Sony", "Hewlett", "Packard");
			passwordTextBox->Text = generatedPassword;
		}
	};
};
