#pragma once

#include "./Spline.h"

#include <msclr/marshal_cppstd.h>
#include <string>
#include <vector>

namespace CppWinForm1 {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Diagnostics;

	/// <summary>
	/// Summary for MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
		Graphics^ gr;
		Pen^ pen, ^penScheduleKruskal, ^penSchedulePrim;
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ textBox3;
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->gr = CreateGraphics();
			this->pen = gcnew Pen(Color::Black);
			this->penScheduleKruskal = gcnew Pen(Color::Purple);
			this->penSchedulePrim = gcnew Pen(Color::Red);
			this->penScheduleKruskal->Width = 3.0;
			this->penSchedulePrim->Width = 3.0;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
			}
		}


	private: System::ComponentModel::IContainer^ components;

#pragma region Windows Form Designer generated code
		   /// <summary>
		   /// Required method for Designer support - do not modify
		   /// the contents of this method with the code editor.
		   /// </summary>
		   void InitializeComponent(void)
		   {
			   this->button1 = (gcnew System::Windows::Forms::Button());
			   this->label1 = (gcnew System::Windows::Forms::Label());
			   this->label2 = (gcnew System::Windows::Forms::Label());
			   this->label3 = (gcnew System::Windows::Forms::Label());
			   this->textBox1 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->SuspendLayout();
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			   this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->button1->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->button1->Location = System::Drawing::Point(400, 435);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(100, 30);
			   this->button1->TabIndex = 0;
			   this->button1->Text = L"StartInterpolation";
			   this->button1->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button1->UseVisualStyleBackColor = false;
			   this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			   // 
			   // label1
			   // 
			   this->label1->AutoSize = true;
			   this->label1->BackColor = System::Drawing::SystemColors::Window;
			   this->label1->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label1->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->label1->Location = System::Drawing::Point(330, 300);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(92, 19);
			   this->label1->TabIndex = 1;
			   this->label1->Text = L"Function (t):";
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->BackColor = System::Drawing::SystemColors::Window;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label2->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->label2->Location = System::Drawing::Point(330, 368);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(50, 19);
			   this->label2->TabIndex = 2;
			   this->label2->Text = L"Point:";
			   // 
			   // label3
			   // 
			   this->label3->AutoSize = true;
			   this->label3->BackColor = System::Drawing::SystemColors::Window;
			   this->label3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label3->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->label3->Location = System::Drawing::Point(330, 334);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(100, 19);
			   this->label3->TabIndex = 3;
			   this->label3->Text = L"Function\'\' (t):";
			   // 
			   // textBox1
			   // 
			   this->textBox1->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox1->Location = System::Drawing::Point(450, 296);
			   this->textBox1->Name = L"textBox1";
			   this->textBox1->Size = System::Drawing::Size(120, 27);
			   this->textBox1->TabIndex = 4;
			   // 
			   // textBox2
			   // 
			   this->textBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox2->Location = System::Drawing::Point(450, 330);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(120, 27);
			   this->textBox2->TabIndex = 6;
			   // 
			   // textBox3
			   // 
			   this->textBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox3->Location = System::Drawing::Point(450, 364);
			   this->textBox3->Name = L"textBox3";
			   this->textBox3->Size = System::Drawing::Size(120, 27);
			   this->textBox3->TabIndex = 5;
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label4->ForeColor = System::Drawing::SystemColors::ControlDark;
			   this->label4->Location = System::Drawing::Point(576, 376);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(119, 15);
			   this->label4->TabIndex = 7;
			   this->label4->Text = L"separated by a space";
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::Window;
			   this->ClientSize = System::Drawing::Size(884, 661);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->textBox3);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->textBox1);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->button1);
			   this->Name = L"MyForm";
			   this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			   this->Text = L"SplineInterpolation";
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	std::string functionExpression = msclr::interop::marshal_as<std::string>(this->textBox1->Text);
	std::string secondDerivativeExpression = msclr::interop::marshal_as<std::string>(this->textBox2->Text);
	std::string pointVector = msclr::interop::marshal_as<std::string>(this->textBox3->Text);

	std::vector<double> pointContainer;
	std::string pointStr;
	for (const auto& point : pointVector)
	{
		if (point != ' ')
		{
			pointStr += point;
		}
		else 
		{
			if (!pointStr.empty())
				pointContainer.push_back(atof(pointStr.c_str()));
			pointStr.clear();
		}
	}

	Spline spline(functionExpression, secondDerivativeExpression, pointContainer);
	spline.startInterpolation();
	/* */
}
};
}
