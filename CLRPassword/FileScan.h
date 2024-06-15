// MainForm.h
#pragma once

namespace CLRPassword {

    using namespace System;
    using namespace System::ComponentModel;
    using namespace System::Collections;
    using namespace System::Windows::Forms;
    using namespace System::Data;
    using namespace System::Drawing;
    using namespace System::Threading;
    using namespace System::IO;
    using namespace System::Collections::Generic;
    using namespace System::Text;

    public ref class FileScan : public System::Windows::Forms::Form
    {
    public:
        FileScan(void)
        {
            InitializeComponent();
            worker1 = gcnew Thread(gcnew ThreadStart(this, &FileScan::Thread1Function));
            worker2 = gcnew Thread(gcnew ThreadStart(this, &FileScan::Thread2Function));
            startEvent = gcnew ManualResetEvent(false);
            stopEvent = gcnew ManualResetEvent(false);
            pipeStream = gcnew MemoryStream();
            components = gcnew System::ComponentModel::Container();  
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
        System::Windows::Forms::Button^ startButton;
        System::Windows::Forms::TextBox^ resultTextBox;
        System::Windows::Forms::TextBox^ filePathTextBox;
        Thread^ worker1;
        Thread^ worker2;
        ManualResetEvent^ startEvent;
        ManualResetEvent^ stopEvent;
        List<Tuple<int, int>^>^ coordinates;
        MemoryStream^ pipeStream;
    private: System::Windows::Forms::Panel^ panel1;
    private: System::Windows::Forms::Label^ label1;
           System::ComponentModel::Container^ components;

        void InitializeComponent(void)
        {
            this->startButton = (gcnew System::Windows::Forms::Button());
            this->resultTextBox = (gcnew System::Windows::Forms::TextBox());
            this->filePathTextBox = (gcnew System::Windows::Forms::TextBox());
            this->panel1 = (gcnew System::Windows::Forms::Panel());
            this->label1 = (gcnew System::Windows::Forms::Label());
            this->panel1->SuspendLayout();
            this->SuspendLayout();
            // 
            // startButton
            // 
            this->startButton->BackColor = System::Drawing::Color::LightSkyBlue;
            this->startButton->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
            this->startButton->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 11.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->startButton->Location = System::Drawing::Point(363, 225);
            this->startButton->Name = L"startButton";
            this->startButton->Size = System::Drawing::Size(98, 31);
            this->startButton->TabIndex = 0;
            this->startButton->Text = L"Начать";
            this->startButton->UseVisualStyleBackColor = false;
            this->startButton->Click += gcnew System::EventHandler(this, &FileScan::startButton_Click);
            // 
            // resultTextBox
            // 
            this->resultTextBox->Location = System::Drawing::Point(12, 138);
            this->resultTextBox->Multiline = true;
            this->resultTextBox->Name = L"resultTextBox";
            this->resultTextBox->Size = System::Drawing::Size(259, 176);
            this->resultTextBox->TabIndex = 2;
            // 
            // filePathTextBox
            // 
            this->filePathTextBox->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->filePathTextBox->Location = System::Drawing::Point(284, 184);
            this->filePathTextBox->Name = L"filePathTextBox";
            this->filePathTextBox->Size = System::Drawing::Size(259, 23);
            this->filePathTextBox->TabIndex = 1;
            this->filePathTextBox->Text = L"coordinates.txt";
            // 
            // panel1
            // 
            this->panel1->BackColor = System::Drawing::Color::LightSkyBlue;
            this->panel1->Controls->Add(this->label1);
            this->panel1->Location = System::Drawing::Point(0, 0);
            this->panel1->Name = L"panel1";
            this->panel1->Size = System::Drawing::Size(555, 100);
            this->panel1->TabIndex = 3;
            // 
            // label1
            // 
            this->label1->AutoSize = true;
            this->label1->Font = (gcnew System::Drawing::Font(L"Microsoft YaHei", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
                static_cast<System::Byte>(0)));
            this->label1->Location = System::Drawing::Point(169, 33);
            this->label1->Name = L"label1";
            this->label1->Size = System::Drawing::Size(219, 28);
            this->label1->TabIndex = 0;
            this->label1->Text = L"Сортировка данных";
            // 
            // FileScan
            // 
            this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
            this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
            this->ClientSize = System::Drawing::Size(555, 351);
            this->Controls->Add(this->panel1);
            this->Controls->Add(this->resultTextBox);
            this->Controls->Add(this->filePathTextBox);
            this->Controls->Add(this->startButton);
            this->Name = L"FileScan";
            this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
            this->Text = L"FileScan";
            this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &FileScan::FileScan_FormClosing);
            this->panel1->ResumeLayout(false);
            this->panel1->PerformLayout();
            this->ResumeLayout(false);
            this->PerformLayout();

        }

        void startButton_Click(System::Object^ sender, System::EventArgs^ e)
        {
            try {
                if (!worker1->IsAlive)
                {
                    worker1->Start();
                    worker2->Start();
                }
                startEvent->Set();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void Thread1Function()
        {
            try {
                startEvent->WaitOne();

                String^ filePath = filePathTextBox->Text;  // Получение пути из текстового поля
                coordinates = gcnew List<Tuple<int, int>^>();
                StreamReader^ reader = gcnew StreamReader(filePath);

                String^ line;
                while ((line = reader->ReadLine()) != nullptr)
                {
                    array<String^>^ parts = line->Split(' ');
                    if (parts->Length == 2)
                    {
                        int x = Int32::Parse(parts[0]);
                        int y = Int32::Parse(parts[1]);

                        if (IsValidCoordinate(x, y))
                        {
                            coordinates->Add(Tuple::Create(x, y));
                        }
                    }
                }

                reader->Close();

                StreamWriter^ writer = gcnew StreamWriter(pipeStream);
                for each (auto coord in coordinates)
                {
                    writer->WriteLine(coord->Item1.ToString() + " " + coord->Item2.ToString());
                }
                writer->Flush();
                pipeStream->Seek(0, SeekOrigin::Begin);

                stopEvent->WaitOne();

                coordinates->Clear();
                StreamReader^ pipeReader = gcnew StreamReader(pipeStream);
                while ((line = pipeReader->ReadLine()) != nullptr)
                {
                    array<String^>^ parts = line->Split(' ');
                    int x = Int32::Parse(parts[0]);
                    int y = Int32::Parse(parts[1]);
                    coordinates->Add(Tuple::Create(x, y));
                }

                DisplayResults();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        void Thread2Function()
        {
            try {
                startEvent->WaitOne();

                List<Tuple<int, int>^>^ receivedCoordinates = gcnew List<Tuple<int, int>^>();

                StreamReader^ pipeReader = gcnew StreamReader(pipeStream);
                String^ line;
                while ((line = pipeReader->ReadLine()) != nullptr)
                {
                    array<String^>^ parts = line->Split(' ');
                    int x = Int32::Parse(parts[0]);
                    int y = Int32::Parse(parts[1]);
                    receivedCoordinates->Add(Tuple::Create(x, y));
                }

                receivedCoordinates->Sort(gcnew Comparison<Tuple<int, int>^>(this, &FileScan::CompareCoordinates));

                pipeStream->SetLength(0);
                StreamWriter^ writer = gcnew StreamWriter(pipeStream);
                for each (auto coord in receivedCoordinates)
                {
                    writer->WriteLine(coord->Item1.ToString() + " " + coord->Item2.ToString());
                }
                writer->Flush();
                pipeStream->Seek(0, SeekOrigin::Begin);

                stopEvent->Set();
            }
            catch (Exception^ ex) {
                MessageBox::Show("Ошибка: " + ex->Message, "Error", MessageBoxButtons::OK, MessageBoxIcon::Error);
            }
        }

        int CompareCoordinates(Tuple<int, int>^ a, Tuple<int, int>^ b)
        {
            if (a->Item1 == b->Item1)
                return a->Item2.CompareTo(b->Item2);
            return a->Item1.CompareTo(b->Item1);
        }

        bool IsValidCoordinate(int x, int y)
        {
            return x >= 0 && x <= 100 && y >= 0 && y <= 100;
        }

        void DisplayResults()
        {
            this->Invoke(gcnew MethodInvoker(this, &FileScan::UpdateResults));
        }

        void UpdateResults()
        {
            resultTextBox->Clear();
            for each (auto coord in coordinates)
            {
                resultTextBox->AppendText(coord->Item1 + ", " + coord->Item2 + "\r\n");
            }
        }
    private: System::Void FileScan_FormClosing(System::Object^ sender, System::Windows::Forms::FormClosingEventArgs^ e) {
        Application::Exit();
    }
};
}