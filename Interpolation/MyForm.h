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
		Pen^ penLine, ^penCurrentPoint, ^penSpline, ^eraser;

	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;

	private: System::Windows::Forms::TextBox^ textBox2;
	private: System::Windows::Forms::Label^ label4;


	private: System::Windows::Forms::DataGridView^ dataGridView1;


	private: System::Windows::Forms::Button^ button2;


	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column1;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column2;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column3;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column4;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^ Column5;







	private: System::Windows::Forms::TextBox^ textBox3;
	public:
		MyForm(void)
		{
			InitializeComponent();
			this->gr = CreateGraphics();
			this->penLine = gcnew Pen(Color::Black);
			this->penCurrentPoint = gcnew Pen(Color::Red);
			this->penSpline = gcnew Pen(Color::LightBlue);
			this->eraser = gcnew Pen(Color::White);
			this->penCurrentPoint->Width = 4.0;
			this->penSpline->Width = 4.0;
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
			   this->textBox2 = (gcnew System::Windows::Forms::TextBox());
			   this->textBox3 = (gcnew System::Windows::Forms::TextBox());
			   this->label4 = (gcnew System::Windows::Forms::Label());
			   this->dataGridView1 = (gcnew System::Windows::Forms::DataGridView());
			   this->Column1 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Column2 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Column3 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Column4 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->Column5 = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			   this->button2 = (gcnew System::Windows::Forms::Button());
			   this->label7 = (gcnew System::Windows::Forms::Label());
			   this->label5 = (gcnew System::Windows::Forms::Label());
			   (cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dataGridView1))->BeginInit();
			   this->SuspendLayout();
			   // 
			   // button1
			   // 
			   this->button1->BackColor = System::Drawing::SystemColors::ActiveCaption;
			   this->button1->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->button1->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->button1->Location = System::Drawing::Point(467, 535);
			   this->button1->Margin = System::Windows::Forms::Padding(4);
			   this->button1->Name = L"button1";
			   this->button1->Size = System::Drawing::Size(267, 37);
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
			   this->label1->Location = System::Drawing::Point(353, 369);
			   this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label1->Name = L"label1";
			   this->label1->Size = System::Drawing::Size(0, 24);
			   this->label1->TabIndex = 1;
			   // 
			   // label2
			   // 
			   this->label2->AutoSize = true;
			   this->label2->BackColor = System::Drawing::SystemColors::Window;
			   this->label2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label2->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->label2->Location = System::Drawing::Point(397, 451);
			   this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label2->Name = L"label2";
			   this->label2->Size = System::Drawing::Size(61, 24);
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
			   this->label3->Location = System::Drawing::Point(395, 387);
			   this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label3->Name = L"label3";
			   this->label3->Size = System::Drawing::Size(63, 24);
			   this->label3->TabIndex = 3;
			   this->label3->Text = L"Value:";
			   // 
			   // textBox2
			   // 
			   this->textBox2->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox2->Location = System::Drawing::Point(513, 384);
			   this->textBox2->Margin = System::Windows::Forms::Padding(4);
			   this->textBox2->Name = L"textBox2";
			   this->textBox2->Size = System::Drawing::Size(332, 32);
			   this->textBox2->TabIndex = 6;
			   this->textBox2->Text = L"0 3 -2 4 1 3 -4 5 6 1 0 2";
			   // 
			   // textBox3
			   // 
			   this->textBox3->Font = (gcnew System::Drawing::Font(L"Calibri", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->textBox3->Location = System::Drawing::Point(513, 448);
			   this->textBox3->Margin = System::Windows::Forms::Padding(4);
			   this->textBox3->Name = L"textBox3";
			   this->textBox3->Size = System::Drawing::Size(332, 32);
			   this->textBox3->TabIndex = 5;
			   this->textBox3->Text = L"1 4 6 0.5 -2 -3 1.5 8 -1 0 -5 5";
			   // 
			   // label4
			   // 
			   this->label4->AutoSize = true;
			   this->label4->Font = (gcnew System::Drawing::Font(L"Calibri", 9.75F, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point,
				   static_cast<System::Byte>(204)));
			   this->label4->ForeColor = System::Drawing::SystemColors::ControlDark;
			   this->label4->Location = System::Drawing::Point(853, 463);
			   this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			   this->label4->Name = L"label4";
			   this->label4->Size = System::Drawing::Size(159, 21);
			   this->label4->TabIndex = 7;
			   this->label4->Text = L"separated by a space";
			   // 
			   // dataGridView1
			   // 
			   this->dataGridView1->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			   this->dataGridView1->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(5) {
				   this->Column1,
					   this->Column2, this->Column3, this->Column4, this->Column5
			   });
			   this->dataGridView1->Location = System::Drawing::Point(13, 615);
			   this->dataGridView1->Margin = System::Windows::Forms::Padding(4);
			   this->dataGridView1->Name = L"dataGridView1";
			   this->dataGridView1->RowHeadersWidth = 51;
			   this->dataGridView1->Size = System::Drawing::Size(470, 186);
			   this->dataGridView1->TabIndex = 10;
			   this->dataGridView1->Visible = false;
			   // 
			   // Column1
			   // 
			   this->Column1->Frozen = true;
			   this->Column1->HeaderText = L"Interval";
			   this->Column1->MinimumWidth = 6;
			   this->Column1->Name = L"Column1";
			   this->Column1->ReadOnly = true;
			   this->Column1->Width = 84;
			   // 
			   // Column2
			   // 
			   this->Column2->Frozen = true;
			   this->Column2->HeaderText = L"A";
			   this->Column2->MinimumWidth = 6;
			   this->Column2->Name = L"Column2";
			   this->Column2->ReadOnly = true;
			   this->Column2->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->Column2->Width = 50;
			   // 
			   // Column3
			   // 
			   this->Column3->Frozen = true;
			   this->Column3->HeaderText = L"B";
			   this->Column3->MinimumWidth = 6;
			   this->Column3->Name = L"Column3";
			   this->Column3->ReadOnly = true;
			   this->Column3->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->Column3->Width = 50;
			   // 
			   // Column4
			   // 
			   this->Column4->Frozen = true;
			   this->Column4->HeaderText = L"C";
			   this->Column4->MinimumWidth = 6;
			   this->Column4->Name = L"Column4";
			   this->Column4->ReadOnly = true;
			   this->Column4->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->Column4->Width = 50;
			   // 
			   // Column5
			   // 
			   this->Column5->Frozen = true;
			   this->Column5->HeaderText = L"D";
			   this->Column5->MinimumWidth = 6;
			   this->Column5->Name = L"Column5";
			   this->Column5->ReadOnly = true;
			   this->Column5->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			   this->Column5->Width = 50;
			   // 
			   // button2
			   // 
			   this->button2->BackColor = System::Drawing::SystemColors::ActiveCaption;
			   this->button2->Cursor = System::Windows::Forms::Cursors::Hand;
			   this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Popup;
			   this->button2->ForeColor = System::Drawing::SystemColors::WindowText;
			   this->button2->Location = System::Drawing::Point(533, 762);
			   this->button2->Margin = System::Windows::Forms::Padding(4);
			   this->button2->Name = L"button2";
			   this->button2->Size = System::Drawing::Size(133, 37);
			   this->button2->TabIndex = 11;
			   this->button2->Text = L"NewFuction";
			   this->button2->TextImageRelation = System::Windows::Forms::TextImageRelation::TextBeforeImage;
			   this->button2->UseVisualStyleBackColor = false;
			   this->button2->Visible = false;
			   this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			   // 
			   // label7
			   // 
			   this->label7->AutoSize = true;
			   this->label7->Font = (gcnew System::Drawing::Font(L"Calibri", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label7->Location = System::Drawing::Point(404, 484);
			   this->label7->Name = L"label7";
			   this->label7->Size = System::Drawing::Size(441, 35);
			   this->label7->TabIndex = 12;
			   this->label7->Text = L"Enter sets of points of the same size!";
			   this->label7->Visible = false;
			   // 
			   // label5
			   // 
			   this->label5->AutoSize = true;
			   this->label5->Font = (gcnew System::Drawing::Font(L"Calibri", 16.2F, static_cast<System::Drawing::FontStyle>((System::Drawing::FontStyle::Bold | System::Drawing::FontStyle::Italic)),
				   System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(204)));
			   this->label5->Location = System::Drawing::Point(423, 576);
			   this->label5->Name = L"label5";
			   this->label5->Size = System::Drawing::Size(402, 35);
			   this->label5->TabIndex = 13;
			   this->label5->Text = L"Ñlick on the button at the bottom";
			   this->label5->Visible = false;
			   // 
			   // MyForm
			   // 
			   this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			   this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			   this->BackColor = System::Drawing::SystemColors::Window;
			   this->ClientSize = System::Drawing::Size(1182, 823);
			   this->Controls->Add(this->label5);
			   this->Controls->Add(this->label7);
			   this->Controls->Add(this->button2);
			   this->Controls->Add(this->dataGridView1);
			   this->Controls->Add(this->label4);
			   this->Controls->Add(this->textBox3);
			   this->Controls->Add(this->textBox2);
			   this->Controls->Add(this->label3);
			   this->Controls->Add(this->label2);
			   this->Controls->Add(this->label1);
			   this->Controls->Add(this->button1);
			   this->Margin = System::Windows::Forms::Padding(4);
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
	std::string valueVector = msclr::interop::marshal_as<std::string>(this->textBox2->Text);
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

	std::vector<double> valueContainer;
	std::string valueStr;
	for (const auto& value : valueVector)
	{
		if (value != ' ')
		{
			valueStr += value;
		}
		else
		{
			if (!valueStr.empty())
				valueContainer.push_back(atof(valueStr.c_str()));
			valueStr.clear();
		}
	}

	if (!valueStr.empty())
		valueContainer.push_back(atof(valueStr.c_str()));

	this->button1->Visible = false;
	this->button2->Visible = true;
	this->label1->Visible = false;
	this->label2->Visible = false;
	this->label3->Visible = false;
	this->label4->Visible = false;
	this->textBox2->Visible = false;
	this->textBox3->Visible = false;

	try 
	{
		Spline spline(valueContainer, pointContainer);
		std::vector<std::pair<Function, SplineCoeffs>> resultInterpolation = spline.startInterpolation();

		for (std::vector<Function>::size_type dataGridSize = 1; dataGridSize < resultInterpolation.size(); dataGridSize++)
			dataGridView1->Rows->Add();

		//draw a coordinate system
		this->dataGridView1->Visible = true;

		gr->DrawLine(penLine, 147, 350, 750, 350);
		gr->DrawLine(penLine, 450, 100, 450, 603);
		gr->DrawLine(penLine, 450, 100, 455, 105);
		gr->DrawLine(penLine, 450, 100, 445, 105);
		gr->DrawLine(penLine, 750, 350, 745, 345);
		gr->DrawLine(penLine, 750, 350, 745, 355);

		//sorting and find max
		int valueMinAbs = static_cast<int>(fabs(valueContainer[0]));
		int valueMaxAbs = valueMinAbs;
		for (const auto& value : valueContainer)
		{
			if (static_cast<int>(fabs(value)) < valueMinAbs)
				valueMinAbs = value;

			else if (static_cast<int>(fabs(value)) > valueMaxAbs)
				valueMaxAbs = value;
		}

		for (std::vector<double>::size_type i = 0; i < pointContainer.size(); i++)
		{			
			for (std::vector<double>::size_type j = i + 1; j < pointContainer.size(); j++)
			{
				if (pointContainer[j] < pointContainer[i])
				{
					std::swap(pointContainer[i], pointContainer[j]);
					std::swap(valueContainer[i], valueContainer[j]);
				}
			}
		}

		int pointMinAbs = static_cast<int>(fabs(pointContainer[0]));
		int pointMaxAbs = static_cast<int>(fabs(pointContainer[pointContainer.size() - 1]));

		int unit_segment = max(max(valueMinAbs, valueMaxAbs), max(pointMinAbs, pointMaxAbs));
		unit_segment = unit_segment / 10 + 1;

		int step = 30 / unit_segment;

		for (int i = 450; i < 750; i += step)
		{
			gr->DrawLine(penLine, i, 345, i, 355);
		}

		for (int i = 450; i > 150; i -= step)
		{
			gr->DrawLine(penLine, i, 345, i, 355);
		}

		for (int i = 350; i < 600; i += step)
		{
			gr->DrawLine(penLine, 448, i, 452, i);
		}

		for (int i = 350; i > 100; i -= step)
		{
			gr->DrawLine(penLine, 448, i, 452, i);
		}

		//draw a point
		float stepFunction = step;

		for (std::vector<double>::size_type i = 0; i < pointContainer.size(); i++)
		{
			float coordinateX = 450. + pointContainer[i] * stepFunction;
			float coordinateY = 350. - valueContainer[i] * stepFunction;

			gr->DrawEllipse(penCurrentPoint, static_cast<float>(coordinateX - 2.),
				static_cast<float>(coordinateY - 2.),
				4., 4.);
		}

		//draw a spline
		float lastValue = static_cast<float>(resultInterpolation[0].first.getValue(pointContainer[0]));
		int currentIndex = 0;
		for (float x = pointContainer[0] + 0.01; x <= pointContainer[pointContainer.size() - 1]; x += 0.01)
		{
			if (x > pointContainer[currentIndex + 1])
				currentIndex++;

			float startX = static_cast<float>(450. + (x - 0.01) * stepFunction);
			float startY = static_cast<float>(350. - lastValue * stepFunction);
			float finishX = static_cast<float>(450. + x * stepFunction);
			float finishY = static_cast<float>(350. - resultInterpolation[currentIndex].first.getValue(x) * stepFunction);

			gr->DrawLine(penSpline, startX, startY, finishX, finishY);

			lastValue = resultInterpolation[currentIndex].first.getValue(x);
		}

		//print coeffs 
		for (int i = 0; i < resultInterpolation.size(); i++)
		{
			std::string interval = convertFunction::valueToString(pointContainer[i]) + " ... " + convertFunction::valueToString(pointContainer[i + 1]);
			dataGridView1->Rows[i]->Cells[0]->Value = gcnew System::String(interval.c_str());

			dataGridView1->Rows[i]->Cells[1]->Value = gcnew System::String(convertFunction::valueToString(resultInterpolation[i].second.aCoeff).c_str());
			dataGridView1->Rows[i]->Cells[2]->Value = gcnew System::String(convertFunction::valueToString(resultInterpolation[i].second.bCoeff).c_str());
			dataGridView1->Rows[i]->Cells[3]->Value = gcnew System::String(convertFunction::valueToString(resultInterpolation[i].second.cCoeff).c_str());
			dataGridView1->Rows[i]->Cells[4]->Value = gcnew System::String(convertFunction::valueToString(resultInterpolation[i].second.dCoeff).c_str());
		}
	}
	
	catch (int)
	{
		this->label5->Visible = true;
		this->label7->Visible = true;
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
	this->label7->Visible = false;
	this->textBox2->Visible = true;
	this->textBox3->Visible = true;
	this->dataGridView1->Visible = false;
}
};
}
