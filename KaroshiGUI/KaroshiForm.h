#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "bricklet_can_v2.h"
#include "functions.h"
#include <chrono>

#define HOST "localhost"
#define PORT 4223
#define UID "QAd" 

/*
* Global Variables
*/
CANV2 can;
IPConnection ipcon;
bool success;
uint32_t writeIdSpd;
uint32_t writeIdCur;
uint32_t writeIdTrq;
uint32_t writeIdBraCur;
bool connectState = false;
bool pp = false;
int actSpdDta = 0;
int actTrqDta = 0;
float rads = 0.42;
int32_t retData[] = { 0,0 }; // Speed and Torque come in 1 Frame. getCanData is used to get the Information

namespace KaroshiGUI {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Zusammenfassung für KaroshiForm
	/// </summary>
	public ref class KaroshiForm : public System::Windows::Forms::Form
	{
	public:
		KaroshiForm(void)
		{
			InitializeComponent();
			//
			//TODO: Konstruktorcode hier hinzufügen.
			//
		}

	protected:
		/// <summary>
		/// Verwendete Ressourcen bereinigen.
		/// </summary>
		~KaroshiForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ connectBt;
	protected:
	private: System::Windows::Forms::Button^ disconnectBt;
	private: System::Windows::Forms::NumericUpDown^ idSpd;
	private: System::Windows::Forms::NumericUpDown^ baudrate;
	private: System::Windows::Forms::TextBox^ SpdBox;
	private: System::Windows::Forms::TrackBar^ trackBar1;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ spdChart;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ debugBox;
	private: System::Windows::Forms::Timer^ chartTimer;
	private: System::Windows::Forms::ComboBox^ ControlMode;
	private: System::Windows::Forms::Button^ cntrlApplyBtn;
	private: System::Windows::Forms::TextBox^ curBox;
	private: System::Windows::Forms::TrackBar^ curBar;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::NumericUpDown^ idDebug;
	private: System::Windows::Forms::NumericUpDown^ dtaDebug;
	private: System::Windows::Forms::Button^ sendDebug;
	private: System::Windows::Forms::Label^ label5;


	private: System::Windows::Forms::TextBox^ ActSpdBox;

	private: System::Windows::Forms::TextBox^ ActTrqBox;
	private: System::Windows::Forms::DataVisualization::Charting::Chart^ trqChart;
	private: System::Windows::Forms::Label^ MotConTex;
	private: System::Windows::Forms::Label^ BraConTex;
	private: System::Windows::Forms::TextBox^ BraTrqBox;
	private: System::Windows::Forms::TextBox^ BraCurBox;
	private: System::Windows::Forms::Label^ CtrlTrq;
	private: System::Windows::Forms::Label^ CtrlCur;
	private: System::Windows::Forms::ComboBox^ ctrlModBra;
	private: System::Windows::Forms::Button^ AplyBraMod;
	private: System::Windows::Forms::TrackBar^ trqBraBar;
	private: System::Windows::Forms::TrackBar^ curBraBar;
	private: System::Windows::Forms::Label^ Info;






	private: System::ComponentModel::IContainer^ components;

	private:
		/// <summary>
		/// Erforderliche Designervariable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Erforderliche Methode für die Designerunterstützung.
		/// Der Inhalt der Methode darf nicht mit dem Code-Editor geändert werden.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea3 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series3 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea4 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series4 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
			this->connectBt = (gcnew System::Windows::Forms::Button());
			this->disconnectBt = (gcnew System::Windows::Forms::Button());
			this->idSpd = (gcnew System::Windows::Forms::NumericUpDown());
			this->baudrate = (gcnew System::Windows::Forms::NumericUpDown());
			this->SpdBox = (gcnew System::Windows::Forms::TextBox());
			this->trackBar1 = (gcnew System::Windows::Forms::TrackBar());
			this->spdChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->debugBox = (gcnew System::Windows::Forms::TextBox());
			this->chartTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->ControlMode = (gcnew System::Windows::Forms::ComboBox());
			this->cntrlApplyBtn = (gcnew System::Windows::Forms::Button());
			this->curBox = (gcnew System::Windows::Forms::TextBox());
			this->curBar = (gcnew System::Windows::Forms::TrackBar());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->idDebug = (gcnew System::Windows::Forms::NumericUpDown());
			this->dtaDebug = (gcnew System::Windows::Forms::NumericUpDown());
			this->sendDebug = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->ActSpdBox = (gcnew System::Windows::Forms::TextBox());
			this->ActTrqBox = (gcnew System::Windows::Forms::TextBox());
			this->trqChart = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->MotConTex = (gcnew System::Windows::Forms::Label());
			this->BraConTex = (gcnew System::Windows::Forms::Label());
			this->BraTrqBox = (gcnew System::Windows::Forms::TextBox());
			this->BraCurBox = (gcnew System::Windows::Forms::TextBox());
			this->CtrlTrq = (gcnew System::Windows::Forms::Label());
			this->CtrlCur = (gcnew System::Windows::Forms::Label());
			this->ctrlModBra = (gcnew System::Windows::Forms::ComboBox());
			this->AplyBraMod = (gcnew System::Windows::Forms::Button());
			this->trqBraBar = (gcnew System::Windows::Forms::TrackBar());
			this->curBraBar = (gcnew System::Windows::Forms::TrackBar());
			this->Info = (gcnew System::Windows::Forms::Label());
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->idSpd))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->baudrate))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spdChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->curBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->idDebug))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtaDebug))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trqChart))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trqBraBar))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->curBraBar))->BeginInit();
			this->SuspendLayout();
			// 
			// connectBt
			// 
			this->connectBt->Location = System::Drawing::Point(21, 753);
			this->connectBt->Name = L"connectBt";
			this->connectBt->Size = System::Drawing::Size(75, 23);
			this->connectBt->TabIndex = 0;
			this->connectBt->Text = L"Connect";
			this->connectBt->UseVisualStyleBackColor = true;
			this->connectBt->Click += gcnew System::EventHandler(this, &KaroshiForm::connectBt_Click);
			// 
			// disconnectBt
			// 
			this->disconnectBt->Location = System::Drawing::Point(124, 753);
			this->disconnectBt->Name = L"disconnectBt";
			this->disconnectBt->Size = System::Drawing::Size(75, 23);
			this->disconnectBt->TabIndex = 1;
			this->disconnectBt->Text = L"Disconnect";
			this->disconnectBt->UseVisualStyleBackColor = true;
			this->disconnectBt->Click += gcnew System::EventHandler(this, &KaroshiForm::disconnectBt_Click);
			// 
			// idSpd
			// 
			this->idSpd->Hexadecimal = true;
			this->idSpd->Location = System::Drawing::Point(21, 687);
			this->idSpd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->idSpd->Name = L"idSpd";
			this->idSpd->Size = System::Drawing::Size(178, 20);
			this->idSpd->TabIndex = 2;
			// 
			// baudrate
			// 
			this->baudrate->Location = System::Drawing::Point(21, 727);
			this->baudrate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->baudrate->Name = L"baudrate";
			this->baudrate->Size = System::Drawing::Size(178, 20);
			this->baudrate->TabIndex = 3;
			// 
			// SpdBox
			// 
			this->SpdBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->SpdBox->Location = System::Drawing::Point(12, 56);
			this->SpdBox->Multiline = true;
			this->SpdBox->Name = L"SpdBox";
			this->SpdBox->Size = System::Drawing::Size(120, 26);
			this->SpdBox->TabIndex = 4;
			this->SpdBox->TextAlign = System::Windows::Forms::HorizontalAlignment::Center;
			// 
			// trackBar1
			// 
			this->trackBar1->LargeChange = 1;
			this->trackBar1->Location = System::Drawing::Point(147, 56);
			this->trackBar1->Maximum = 3500;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(415, 45);
			this->trackBar1->TabIndex = 1;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &KaroshiForm::trackBar1_ValueChanged);
			this->trackBar1->MouseCaptureChanged += gcnew System::EventHandler(this, &KaroshiForm::trackBar1_MouseCaptureChanged);
			// 
			// spdChart
			// 
			chartArea3->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea3->AxisX->ScaleView->Size = 700;
			chartArea3->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea3->AxisY->Maximum = 3500;
			chartArea3->AxisY->Minimum = -50;
			chartArea3->AxisY->ScrollBar->ButtonColor = System::Drawing::Color::Red;
			chartArea3->Name = L"ChartArea1";
			this->spdChart->ChartAreas->Add(chartArea3);
			legend3->Name = L"Legend1";
			this->spdChart->Legends->Add(legend3);
			this->spdChart->Location = System::Drawing::Point(568, 12);
			this->spdChart->Name = L"spdChart";
			series3->ChartArea = L"ChartArea1";
			series3->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series3->Legend = L"Legend1";
			series3->Name = L"Drehzahl";
			this->spdChart->Series->Add(series3);
			this->spdChart->Size = System::Drawing::Size(630, 409);
			this->spdChart->TabIndex = 6;
			this->spdChart->Text = L"chart1";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(12, 40);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(69, 13);
			this->label1->TabIndex = 7;
			this->label1->Text = L"CTRL Speed";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(18, 671);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(112, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Identifier CTRL Speed";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(18, 711);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Baudrate";
			// 
			// debugBox
			// 
			this->debugBox->Location = System::Drawing::Point(228, 687);
			this->debugBox->Multiline = true;
			this->debugBox->Name = L"debugBox";
			this->debugBox->Size = System::Drawing::Size(318, 89);
			this->debugBox->TabIndex = 10;
			// 
			// chartTimer
			// 
			this->chartTimer->Interval = 20;
			this->chartTimer->Tick += gcnew System::EventHandler(this, &KaroshiForm::chartTimer_Tick);
			// 
			// ControlMode
			// 
			this->ControlMode->FormattingEnabled = true;
			this->ControlMode->Items->AddRange(gcnew cli::array< System::Object^  >(7) {
				L"Idle", L"InitSys", L"ManMode", L"FocWithSnsr",
					L"FocSnsrlss", L"Shutdown", L"RstStMac"
			});
			this->ControlMode->Location = System::Drawing::Point(12, 169);
			this->ControlMode->Name = L"ControlMode";
			this->ControlMode->Size = System::Drawing::Size(120, 21);
			this->ControlMode->TabIndex = 11;
			this->ControlMode->SelectedIndexChanged += gcnew System::EventHandler(this, &KaroshiForm::ControlMode_SelectedIndexChanged);
			// 
			// cntrlApplyBtn
			// 
			this->cntrlApplyBtn->Location = System::Drawing::Point(147, 169);
			this->cntrlApplyBtn->Name = L"cntrlApplyBtn";
			this->cntrlApplyBtn->Size = System::Drawing::Size(83, 23);
			this->cntrlApplyBtn->TabIndex = 12;
			this->cntrlApplyBtn->Text = L"Apply";
			this->cntrlApplyBtn->UseVisualStyleBackColor = true;
			this->cntrlApplyBtn->Click += gcnew System::EventHandler(this, &KaroshiForm::cntrlApplyBtn_Click);
			// 
			// curBox
			// 
			this->curBox->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->curBox->Location = System::Drawing::Point(12, 113);
			this->curBox->Multiline = true;
			this->curBox->Name = L"curBox";
			this->curBox->Size = System::Drawing::Size(120, 26);
			this->curBox->TabIndex = 26;
			// 
			// curBar
			// 
			this->curBar->Location = System::Drawing::Point(147, 113);
			this->curBar->Name = L"curBar";
			this->curBar->Size = System::Drawing::Size(415, 45);
			this->curBar->TabIndex = 27;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(12, 94);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(72, 13);
			this->label4->TabIndex = 28;
			this->label4->Text = L"CTRL Current";
			// 
			// idDebug
			// 
			this->idDebug->Location = System::Drawing::Point(21, 620);
			this->idDebug->Name = L"idDebug";
			this->idDebug->Size = System::Drawing::Size(120, 20);
			this->idDebug->TabIndex = 29;
			// 
			// dtaDebug
			// 
			this->dtaDebug->Location = System::Drawing::Point(147, 620);
			this->dtaDebug->Name = L"dtaDebug";
			this->dtaDebug->Size = System::Drawing::Size(120, 20);
			this->dtaDebug->TabIndex = 30;
			// 
			// sendDebug
			// 
			this->sendDebug->Location = System::Drawing::Point(273, 620);
			this->sendDebug->Name = L"sendDebug";
			this->sendDebug->Size = System::Drawing::Size(75, 20);
			this->sendDebug->TabIndex = 31;
			this->sendDebug->Text = L"Send";
			this->sendDebug->UseVisualStyleBackColor = true;
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(18, 604);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(193, 13);
			this->label5->TabIndex = 32;
			this->label5->Text = L"ID (HEX)                            Data   (HEX)";
			// 
			// ActSpdBox
			// 
			this->ActSpdBox->Location = System::Drawing::Point(1093, 56);
			this->ActSpdBox->Multiline = true;
			this->ActSpdBox->Name = L"ActSpdBox";
			this->ActSpdBox->Size = System::Drawing::Size(73, 25);
			this->ActSpdBox->TabIndex = 34;
			// 
			// ActTrqBox
			// 
			this->ActTrqBox->Location = System::Drawing::Point(1093, 462);
			this->ActTrqBox->Multiline = true;
			this->ActTrqBox->Name = L"ActTrqBox";
			this->ActTrqBox->Size = System::Drawing::Size(73, 25);
			this->ActTrqBox->TabIndex = 36;
			// 
			// trqChart
			// 
			chartArea4->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea4->AxisX->ScaleView->Size = 700;
			chartArea4->AxisY->IntervalAutoMode = System::Windows::Forms::DataVisualization::Charting::IntervalAutoMode::VariableCount;
			chartArea4->AxisY->Maximum = 200;
			chartArea4->AxisY->Minimum = -20;
			chartArea4->Name = L"ChartArea1";
			this->trqChart->ChartAreas->Add(chartArea4);
			legend4->Name = L"Legend1";
			this->trqChart->Legends->Add(legend4);
			this->trqChart->Location = System::Drawing::Point(568, 415);
			this->trqChart->Name = L"trqChart";
			series4->ChartArea = L"ChartArea1";
			series4->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::Spline;
			series4->Legend = L"Legend1";
			series4->Name = L"Torque";
			this->trqChart->Series->Add(series4);
			this->trqChart->Size = System::Drawing::Size(630, 362);
			this->trqChart->TabIndex = 6;
			this->trqChart->Text = L"chart1";
			// 
			// MotConTex
			// 
			this->MotConTex->AutoSize = true;
			this->MotConTex->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->MotConTex->Location = System::Drawing::Point(8, 9);
			this->MotConTex->Name = L"MotConTex";
			this->MotConTex->Size = System::Drawing::Size(144, 24);
			this->MotConTex->TabIndex = 37;
			this->MotConTex->Text = L"Motor Controller";
			// 
			// BraConTex
			// 
			this->BraConTex->AutoSize = true;
			this->BraConTex->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->BraConTex->Location = System::Drawing::Point(8, 232);
			this->BraConTex->Name = L"BraConTex";
			this->BraConTex->Size = System::Drawing::Size(144, 24);
			this->BraConTex->TabIndex = 38;
			this->BraConTex->Text = L"Brake Controller";
			// 
			// BraTrqBox
			// 
			this->BraTrqBox->Location = System::Drawing::Point(12, 281);
			this->BraTrqBox->Multiline = true;
			this->BraTrqBox->Name = L"BraTrqBox";
			this->BraTrqBox->Size = System::Drawing::Size(120, 26);
			this->BraTrqBox->TabIndex = 39;
			// 
			// BraCurBox
			// 
			this->BraCurBox->Location = System::Drawing::Point(12, 339);
			this->BraCurBox->Multiline = true;
			this->BraCurBox->Name = L"BraCurBox";
			this->BraCurBox->Size = System::Drawing::Size(120, 26);
			this->BraCurBox->TabIndex = 40;
			// 
			// CtrlTrq
			// 
			this->CtrlTrq->AutoSize = true;
			this->CtrlTrq->Location = System::Drawing::Point(12, 265);
			this->CtrlTrq->Name = L"CtrlTrq";
			this->CtrlTrq->Size = System::Drawing::Size(72, 13);
			this->CtrlTrq->TabIndex = 41;
			this->CtrlTrq->Text = L"CTRL Torque";
			// 
			// CtrlCur
			// 
			this->CtrlCur->AutoSize = true;
			this->CtrlCur->Location = System::Drawing::Point(12, 323);
			this->CtrlCur->Name = L"CtrlCur";
			this->CtrlCur->Size = System::Drawing::Size(72, 13);
			this->CtrlCur->TabIndex = 42;
			this->CtrlCur->Text = L"CTRL Current";
			// 
			// ctrlModBra
			// 
			this->ctrlModBra->FormattingEnabled = true;
			this->ctrlModBra->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"Idle", L"Init", L"Control" });
			this->ctrlModBra->Location = System::Drawing::Point(12, 400);
			this->ctrlModBra->Name = L"ctrlModBra";
			this->ctrlModBra->Size = System::Drawing::Size(120, 21);
			this->ctrlModBra->TabIndex = 43;
			// 
			// AplyBraMod
			// 
			this->AplyBraMod->Location = System::Drawing::Point(147, 400);
			this->AplyBraMod->Name = L"AplyBraMod";
			this->AplyBraMod->Size = System::Drawing::Size(75, 23);
			this->AplyBraMod->TabIndex = 44;
			this->AplyBraMod->Text = L"Apply";
			this->AplyBraMod->UseVisualStyleBackColor = true;
			this->AplyBraMod->Click += gcnew System::EventHandler(this, &KaroshiForm::AplyBraMod_Click);
			// 
			// trqBraBar
			// 
			this->trqBraBar->Location = System::Drawing::Point(147, 281);
			this->trqBraBar->Maximum = 200;
			this->trqBraBar->Name = L"trqBraBar";
			this->trqBraBar->Size = System::Drawing::Size(415, 45);
			this->trqBraBar->TabIndex = 45;
			this->trqBraBar->ValueChanged += gcnew System::EventHandler(this, &KaroshiForm::trqBraBar_ValueChanged);
			this->trqBraBar->MouseCaptureChanged += gcnew System::EventHandler(this, &KaroshiForm::trqBraBar_MouseCaptureChanged);
			// 
			// curBraBar
			// 
			this->curBraBar->Location = System::Drawing::Point(147, 339);
			this->curBraBar->Maximum = 330;
			this->curBraBar->Name = L"curBraBar";
			this->curBraBar->Size = System::Drawing::Size(415, 45);
			this->curBraBar->TabIndex = 46;
			this->curBraBar->ValueChanged += gcnew System::EventHandler(this, &KaroshiForm::curBraBar_ValueChanged);
			this->curBraBar->MouseCaptureChanged += gcnew System::EventHandler(this, &KaroshiForm::curBraBar_MouseCaptureChanged);
			// 
			// Info
			// 
			this->Info->AutoSize = true;
			this->Info->Location = System::Drawing::Point(249, 323);
			this->Info->Name = L"Info";
			this->Info->Size = System::Drawing::Size(196, 13);
			this->Info->TabIndex = 47;
			this->Info->Text = L"Set Torque to zero to control the current";
			// 
			// KaroshiForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::SystemColors::AppWorkspace;
			this->ClientSize = System::Drawing::Size(1210, 789);
			this->Controls->Add(this->Info);
			this->Controls->Add(this->curBraBar);
			this->Controls->Add(this->trqBraBar);
			this->Controls->Add(this->AplyBraMod);
			this->Controls->Add(this->ctrlModBra);
			this->Controls->Add(this->CtrlCur);
			this->Controls->Add(this->CtrlTrq);
			this->Controls->Add(this->BraCurBox);
			this->Controls->Add(this->BraTrqBox);
			this->Controls->Add(this->BraConTex);
			this->Controls->Add(this->MotConTex);
			this->Controls->Add(this->ActTrqBox);
			this->Controls->Add(this->ActSpdBox);
			this->Controls->Add(this->trqChart);
			this->Controls->Add(this->label5);
			this->Controls->Add(this->sendDebug);
			this->Controls->Add(this->dtaDebug);
			this->Controls->Add(this->idDebug);
			this->Controls->Add(this->label4);
			this->Controls->Add(this->curBar);
			this->Controls->Add(this->curBox);
			this->Controls->Add(this->cntrlApplyBtn);
			this->Controls->Add(this->ControlMode);
			this->Controls->Add(this->debugBox);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->spdChart);
			this->Controls->Add(this->trackBar1);
			this->Controls->Add(this->SpdBox);
			this->Controls->Add(this->baudrate);
			this->Controls->Add(this->idSpd);
			this->Controls->Add(this->disconnectBt);
			this->Controls->Add(this->connectBt);
			this->Name = L"KaroshiForm";
			this->Text = L"Karoshi";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->idSpd))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->baudrate))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spdChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->curBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->idDebug))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->dtaDebug))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trqChart))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trqBraBar))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->curBraBar))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void trackBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		SpdBox->Text = trackBar1->Value.ToString();
	}

/*
* Send Speedbar Data to Controller if value changed
*/
private: System::Void trackBar1_MouseCaptureChanged(System::Object^ sender, System::EventArgs^ e) {
	if (connectState) {
		uint8_t data[2]; 
		writeIdSpd = (uint32_t)0x400;//(uint32_t)idSpd->Value;
		getSpeedData((uint16_t)(trackBar1->Value * rads), data);
		can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, writeIdSpd, data, 2, &success);
	}
	else {
		trackBar1->Value = 0;
		trackBar1->Text = "Not connected";
	}
}
/*
* Initiate connection to MasterBrick if button clicked
*/
private: System::Void connectBt_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!connectState) {
		debugBox->Clear();
		// Create IP connection
		ipcon_create(&ipcon);
		// Create device object
		can_v2_create(&can, UID, &ipcon);
		if (ipcon_connect(&ipcon, HOST, PORT) < 0) {
			debugBox->Text += "Could not connect to brickd\r\n";
		}
		else {
			Sleep(20);
			can_v2_set_transceiver_configuration(&can, (uint32_t)956250/*(uint32_t)baudrate->Value*/, 625, CAN_V2_TRANSCEIVER_MODE_NORMAL);
			int8_t rbs[] = { 16,-8 };
			can_v2_set_queue_configuration(&can, 8, 0, 383, rbs, 2, 1);
			debugBox->Text += "Connected\r\n";
			debugBox->Text += "\r\nBaudrate: ";
			debugBox->Text += baudrate->Value;
			debugBox->Text += "\r\n";
			connectState = true;
			chartTimer->Start();
		}
	}
}
/*
* destroy connection to MasterBrick if button clicked
*/
private: System::Void disconnectBt_Click(System::Object^ sender, System::EventArgs^ e) {
	chartTimer->Stop();
	uint8_t data[2];
	getSpeedData((uint16_t)0, data);
	can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, writeIdSpd, data, 2, &success);
	can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, writeIdCur, data, 2, &success);
	can_v2_set_frame_read_callback_configuration(&can, false);
	can_v2_destroy(&can);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	debugBox->Text = "Disconnected";
	connectState = false;
}
/*
* Timer for reading and printing CAN Data
*/
private: System::Void chartTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
	uint8_t data[15];
	uint8_t dataLength;
	//identifiers
	uint32_t readIdent1;
	uint32_t readIdent2;
	uint32_t spdIdent = 0x3E8;
	uint32_t trqIdent = 0x2E0;
	//Read filter
	uint32_t filterMask = 0x7FF;
	uint32_t filterIdent1;
	uint32_t filterIdent2;
	uint8_t type = CAN_V2_FRAME_TYPE_STANDARD_DATA;

	if (connectState) {
		pp = !pp;
		filterIdent1 = trqIdent;
		filterIdent2 = trqIdent;

		can_v2_set_read_filter_configuration(&can, (uint8_t)0, CAN_V2_FILTER_MODE_MATCH_STANDARD_ONLY, filterMask, filterIdent2);
		can_v2_read_frame(&can, &success, &type, &readIdent1, data, &dataLength);

		if (success && readIdent1 == trqIdent) {
			getCanData(data,retData);
		};
		/*if (success && readIdent2 == trqIdent) {
			actTrqDta = getCanData(data,retData);
		};*/
		
	}
	spdChart->Series["Drehzahl"]->Points->AddY(retData[1]);
	if (spdChart->Series["Drehzahl"]->Points->Count == 700) {
		spdChart->Series["Drehzahl"]->Points->RemoveAt(0);
		ActSpdBox->Text = actSpdDta.ToString();
	}
	trqChart->Series["Torque"]->Points->AddY(retData[0]);
	if (trqChart->Series["Torque"]->Points->Count == 700) {
		trqChart->Series["Torque"]->Points->RemoveAt(0);
		ActTrqBox->Text = actTrqDta.ToString();
	}
}
/*
*Sends the selected Mode via CAN to the Moduleaddress 0x600
*/
private: System::Void cntrlApplyBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	uint8_t data[2];
	uint32_t CntrlMode = 0x600;
	getSpeedData((uint16_t)ControlMode->SelectedIndex, data);
	if (connectState) {
		can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, CntrlMode, data, 2, &success);
	}
}
/*
*Action when changing the Cntrl Mode in the Box
*/
private: System::Void ControlMode_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
}

/*
* Send Torquebar Data to Controller if value changed
*/
private: System::Void trqBraBar_MouseCaptureChanged(System::Object^ sender, System::EventArgs^ e) {
	if (connectState) {
		uint8_t data[2];
		writeIdTrq = (uint32_t)0x401;//(uint32_t)idSpd->Value;
		getSpeedData((uint16_t)(trqBraBar->Value), data);
		can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, writeIdTrq, data, 2, &success);
	}
	else {
		trqBraBar->Value = 0;
		trqBraBar->Text = "Not connected";
	}
}
/*
* Display Torquebar Data in Textbox
*/
private: System::Void trqBraBar_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	BraTrqBox->Text = trqBraBar->Value.ToString();
}
/*
* Send BrakeCurrentBar Data to Controller if value changed
*/
private: System::Void curBraBar_MouseCaptureChanged(System::Object^ sender, System::EventArgs^ e) {
	if (connectState) {
		uint8_t data[2];
		writeIdBraCur = (uint32_t)0x501;//(uint32_t)idSpd->Value;
		getSpeedData((uint16_t)(curBraBar->Value) * magnetCount, data);
		can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, writeIdBraCur, data, 2, &success);
	}
	else {
		curBraBar->Value = 0;
		curBraBar->Text = "Not connected";
	}
}
/*
* Display BrakeCurrentBar Data in Textbox
*/
private: System::Void curBraBar_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
	BraCurBox->Text = curBraBar->Value.ToString();
}
private: System::Void AplyBraMod_Click(System::Object^ sender, System::EventArgs^ e) {
	uint8_t data[2];
	uint32_t CntrlMode = 0x601;
	getSpeedData((uint16_t)(ctrlModBra->SelectedIndex + 1), data);
	if (connectState) {
		can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, CntrlMode, data, 2, &success);
	}
}
};
}
