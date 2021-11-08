#pragma once

#include "./Spline.h"

#include <algorithm>
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
		Pen^ penLine, ^penCurrentPoint, ^penFunction, ^penSpline, ^eraser;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ textBox1;
	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::DataGridView^ dataGridView1;


	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;


	private: System::Windows::Forms::TextBox^ textBox3;
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->gr = CreateGraphics();
			this->penLine = gcnew Pen(Color::Black);
			this->penCurrentPoint = gcnew Pen(Color::Red);
			this->penFunction = gcnew Pen(Color::DarkBlue);
			this->penSpline = gcnew Pen(Color::Yellow);
			this->eraser = gcnew Pen(Color::White);
			this->penFunction->Width = 2.0;
			this->penCurrentPoint->Width = 2.0;
			this->penSpline->Width = 2.0;
			this->eraser->Width = 900.0;
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
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   this->label6 = (gcnew System::Windows::Forms::Label());
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
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
			   this->textBox1->Text = L"sin(t)-cos(t)*sin(t)";
			   // 
			   // textBox2
			   // 
			   this->textBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox2->Location = System::Drawing::Point(450, 330);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(120, 27);
			   this->textBox2->TabIndex = 6;
			   this->textBox2->Text = L"cos(t)+sin(t)*sin(t)-cos(t)*cos(t)";
			   // 
			   // textBox3
			   // 
			   this->textBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox3->Location = System::Drawing::Point(450, 364);
			   this->textBox3->Name = L"textBox3";
			   this->textBox3->Size = System::Drawing::Size(120, 27);
			   this->textBox3->TabIndex = 5;
			   this->textBox3->Text = L"-6 -4 -2 -1.5 -1 -0.5 0 0.5 1 1.5 2 4 6";
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
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Location = System::Drawing::Point(770, 573);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(48, 13);
			   this->label5->TabIndex = 8;
			   this->label5->Text = L"Function";
			   this->label5->Visible = false;
			   // 
			   // label6
			   // 
			   this->label6->AutoSize = true;
			   this->label6->Location = System::Drawing::Point(770, 593);
			   this->label6->Name = L"label6";
			   this->label6->Size = System::Drawing::Size(36, 13);
			   this->label6->TabIndex = 9;
			   this->label6->Text = L"Spline";
			   this->label6->Visible = false;
			   // 
			   // dataGridView1
			   // 
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(2) {
				   this->Column1,
					   this->Column2
			   });
			   this->dataGridView1->Location = System::Drawing::Point(3, 508);
			   this->dataGridView1->Name = L"dataGridView1";
			   this->dataGridView1->Size = System::Drawing::Size(377, 150);
			   this->dataGridView1->TabIndex = 10;
			   this->dataGridView1->Visible = false;
			   // 
			   // button2
			   // 
			   this->button2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			   this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->button2->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->button2->Location = System::Drawing::Point(400, 619);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(100, 30);
			   this->button2->TabIndex = 11;
			   this->button2->Text = L"NewFuction";
			   this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button2->UseVisualStyleBackColor = false;
			   this->button2->Visible = false;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // Column1
			   // 
			   this->Column1->HeaderText = L"Interval";
			   this->Column1->Name = L"Column1";
			   this->Column1->ReadOnly = true;
			   this->Column1->Width = 84;
			   // 
			   // Column2
			   // 
			   this->Column2->HeaderText = L"Function";
			   this->Column2->Name = L"Column2";
			   this->Column2->ReadOnly = true;
			   this->Column2->Width = 250;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::Window;
			   this->ClientSize = System::Drawing::Size(884, 661);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->dataGridView1);
			   this->Controls->Add(this->label6);
			   this->Controls->Add(this->label5);
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
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->EndInit();
			   this->ResumeLayout(false);
			   this->PerformLayout();

		   }
#pragma endregion

private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {
	//generate spline
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

	if (!pointStr.empty())
		pointContainer.push_back(atof(pointStr.c_str()));

	Function currentFunction(functionExpression);
	Spline spline(functionExpression, secondDerivativeExpression, pointContainer);
	std::vector<Function> resultInterpolation = spline.startInterpolation();

	for (int dataGridSize = 1; dataGridSize < resultInterpolation.size(); dataGridSize++)
		dataGridView1->Rows->Add();

	//draw a coordinate system
	this->button1->Visible = false;
	this->button2->Visible = true;
	this->label1->Visible = false;
	this->label2->Visible = false;
	this->label3->Visible = false;
	this->label4->Visible = false;
	this->label5->Visible = true;
	this->label6->Visible = true;
	this->textBox1->Visible = false;
	this->textBox2->Visible = false;
	this->textBox3->Visible = false;
	this->dataGridView1->Visible = true;

	gr->DrawLine(penLine, 147, 350, 750, 350);
	gr->DrawLine(penLine, 450, 100, 450, 603);
	gr->DrawLine(penLine, 450, 100, 455, 105);
	gr->DrawLine(penLine, 450, 100, 445, 105);
	gr->DrawLine(penLine, 750, 350, 745, 345);
	gr->DrawLine(penLine, 750, 350, 745, 355);
	gr->DrawLine(penFunction, 730, 580, 765, 580);
	gr->DrawLine(penSpline, 730, 600, 765, 600);

	int step = 30, currentIteration = -10;

	for (int i = 150; i < 750; i += step)
	{
		if (i != 0)
		{
			if (std::find(pointContainer.begin(), pointContainer.end(), currentIteration) == pointContainer.end())
				gr->DrawLine(penLine, i, 348, i, 352);
			else
				gr->DrawLine(penCurrentPoint, i, 345, i, 355);
		}
		currentIteration++;
	}

	for (int i = 600; i > 100; i -= step)
	{
		if (i != 0)
			gr->DrawLine(penLine, 448, i, 452, i);
	}

	//draw a point
	float stepFunction = step;
	std::sort(pointContainer.begin(), pointContainer.end());

	for (const auto& pointX : pointContainer)
	{
		float coordinateX = 450. + pointX * stepFunction;
		if (pointX != 0)
			gr->DrawLine(penCurrentPoint, coordinateX, 345., coordinateX, 355.);

		double pointY = 350 - step * currentFunction.getValue(pointX);
		if (pointY > 1 && pointY < 651)
			gr->DrawEllipse(penFunction, 450 + pointX * step - 1, pointY - 1, 3, 3);
	}

	this->penLine->Width = 4.0;
	this->penCurrentPoint->Width = 4.0;

	if (std::find(pointContainer.begin(), pointContainer.end(), 0) == pointContainer.end())
		gr->DrawEllipse(penLine, 448, 348, 4, 4);
	else
		gr->DrawEllipse(penCurrentPoint, 448, 348, 4, 4);

	this->penLine->Width = 1.0;
	this->penCurrentPoint->Width = 2.0;

	//draw a function 
	float lastValue = static_cast<float>(currentFunction.getValue(pointContainer[0]));
	for (float x = pointContainer[0] + 0.01; x <= pointContainer[pointContainer.size() - 1]; x += 0.01)
	{
		float startX = static_cast<float>(450. + (x - 0.01) * stepFunction);
		float startY = static_cast<float>(350. - lastValue * stepFunction);
		float finishX = static_cast<float>(450. + x * stepFunction);
		float finishY = static_cast<float>(350. - currentFunction.getValue(x) * stepFunction);

		gr->DrawLine(penFunction, startX, startY, finishX, finishY);

		lastValue = currentFunction.getValue(x);
	}

	//draw a spline
	lastValue = static_cast<float>(resultInterpolation[0].getValue(pointContainer[0]));
	int currentIndex = 0;
	for (float x = pointContainer[0] + 0.01; x <= pointContainer[pointContainer.size() - 1]; x += 0.01)
	{
		if (x > pointContainer[currentIndex + 1])
			currentIndex++;

		if (currentIndex == 3)
			float a;

		float startX = static_cast<float>(450. + (x - 0.01) * stepFunction);
		float startY = static_cast<float>(350. - lastValue * stepFunction);
		float finishX = static_cast<float>(450. + x * stepFunction);
		float finishY = static_cast<float>(350. - resultInterpolation[currentIndex].getValue(x) * stepFunction);

		gr->DrawLine(penSpline, startX, startY, finishX, finishY);

		lastValue = resultInterpolation[currentIndex].getValue(x);
	}

	for (int i = 0; i < resultInterpolation.size(); i++)
	{
		std::string interval = convertFunction::valueToString(pointContainer[i]) + " ... " + convertFunction::valueToString(pointContainer[i + 1]);
		dataGridView1->Rows[i]->Cells[0]->Value = gcnew System::String(interval.c_str());

		dataGridView1->Rows[i]->Cells[1]->Value = gcnew System::String(resultInterpolation[i].getExpression().c_str());
	}
}
private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {
	dataGridView1->Rows->Clear();
	gr->DrawEllipse(eraser, 0, 0, 900, 700);

	this->button1->Visible = true;
	this->button2->Visible = false;
	this->label1->Visible = true;
	this->label2->Visible = true;
	this->label3->Visible = true;
	this->label4->Visible = true;
	this->label5->Visible = false;
	this->label6->Visible = false;
	this->textBox1->Visible = true;
	this->textBox2->Visible = true;
	this->textBox3->Visible = true;
	this->dataGridView1->Visible = false;
}
};
}
