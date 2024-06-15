#pragma once

#include "DataProcessor.h"

namespace CLRPassword {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Threading;

    public ref class FileScan : public System::Windows::Forms::Form
    {
    public:
        FileScan(void)
        {
            InitializeComponent();
        }

    protected:
        ~FileScan()
        {
            if (components)
            {
                delete components;
            }
        }

    private:
        System::Windows::Forms::Button^ btnStart;
        System::Windows::Forms::TextBox^ txtFilePath;
        System::Windows::Forms::ListBox^ lstResults;
        System::ComponentModel::Container^ components;
        DataProcessor^ processor1;
        DataProcessor^ processor2;

        void InitializeComponent(void)
        {
            this->btnStart = (gcnew System::Windows::Forms::Button());
            this->txtFilePath = (gcnew System::Windows::Forms::TextBox());
            this->lstResults = (gcnew System::Windows::Forms::ListBox());
            this->SuspendLayout();

            // 
            // btnStart
            // 
            this->btnStart->Location = System::Drawing::Point(100, 150);
            this->btnStart->Name = L"btnStart";
            this->btnStart->Size = System::Drawing::Size(100, 50);
            this->btnStart->TabIndex = 0;
            this->btnStart->Text = L"Start";
            this->btnStart->UseVisualStyleBackColor = true;
            this->btnStart->Click += gcnew System::EventHandler(this, &FileScan::btnStart_Click);

            // 
            // txtFilePath
            // 
            this->txtFilePath->Location = System::Drawing::Point(100, 50);
            this->txtFilePath->Name = L"txtFilePath";
            this->txtFilePath->Size = System::Drawing::Size(200, 20);
            this->txtFilePath->TabIndex = 1;

            // 
            // lstResults
            // 
            this->lstResults->FormattingEnabled = true;
            this->lstResults->Location = System::Drawing::Point(100, 200);
            this->lstResults->Name = L"lstResults";
            this->lstResults->Size = System::Drawing::Size(200, 150);
            this->lstResults->TabIndex = 2;

            // 
            // MainForm
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(400, 400);
            this->Controls->Add(this->btnStart);
            this->Controls->Add(this->txtFilePath);
            this->Controls->Add(this->lstResults);
            this->Name = L"MainForm";
            this->Text = L"Coordinate Sorter";
            this->ResumeLayout(false);
            this->PerformLayout();
        }

        void btnStart_Click(System::Object^ sender, System::EventArgs^ e)
        {
            String^ filePath = txtFilePath->Text;

            processor1 = gcnew DataProcessor(L"\\\\.\\pipe\\Pipe1");
            processor2 = gcnew DataProcessor(L"\\\\.\\pipe\\Pipe2");

            Thread^ thread1 = gcnew Thread(gcnew ThreadStart(this, &FileScan::Thread1Function));
            Thread^ thread2 = gcnew Thread(gcnew ThreadStart(this, &FileScan::Thread2Function));

            thread1->Start();
            thread2->Start();

            thread1->Join();
            thread2->Join();

            array<String^>^ sortedData = processor1->ReadDataFromPipe();
            for each (String ^ item in sortedData)
            {
                lstResults->Items->Add(item);
            }
        }

        void Thread1Function()
        {
            try
            {
                processor1->ReadAndVerifyData(txtFilePath->Text);
                processor1->SortData();
                processor1->WriteDataToPipe();
                processor1->NotifyCompletion();
            }
            catch (Exception^ ex)
            {
                MessageBox::Show(ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void Thread2Function()
        {
            array<String^>^ data = processor2->ReadDataFromPipe();
            // Process and sort data if needed, then notify completion
            processor2->NotifyCompletion();
        }
    };
}

