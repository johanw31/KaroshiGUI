#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "bricklet_can_v2.h"
#include "functions.h"
#include <chrono>

#define HOST "localhost"
#define PORT 4223
#define UID "QAd" 

CANV2 can;
IPConnection ipcon;
bool success;
uint32_t identSpd;
uint32_t identCur;
bool connectState = false;
int last = 0;

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
			System::Windows::Forms::DataVisualization::Charting::ChartArea^ chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^ legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Series^ series1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Series());
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
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->idSpd))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->baudrate))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spdChart))->BeginInit();
			this->SuspendLayout();
			// 
			// connectBt
			// 
			this->connectBt->Location = System::Drawing::Point(12, 522);
			this->connectBt->Name = L"connectBt";
			this->connectBt->Size = System::Drawing::Size(75, 23);
			this->connectBt->TabIndex = 0;
			this->connectBt->Text = L"Connect";
			this->connectBt->UseVisualStyleBackColor = true;
			this->connectBt->Click += gcnew System::EventHandler(this, &KaroshiForm::connectBt_Click);
			// 
			// disconnectBt
			// 
			this->disconnectBt->Location = System::Drawing::Point(115, 522);
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
			this->idSpd->Location = System::Drawing::Point(12, 457);
			this->idSpd->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->idSpd->Name = L"idSpd";
			this->idSpd->Size = System::Drawing::Size(178, 20);
			this->idSpd->TabIndex = 2;
			// 
			// baudrate
			// 
			this->baudrate->Location = System::Drawing::Point(12, 496);
			this->baudrate->Maximum = System::Decimal(gcnew cli::array< System::Int32 >(4) { 1000000, 0, 0, 0 });
			this->baudrate->Name = L"baudrate";
			this->baudrate->Size = System::Drawing::Size(178, 20);
			this->baudrate->TabIndex = 3;
			// 
			// SpdBox
			// 
			this->SpdBox->Location = System::Drawing::Point(12, 56);
			this->SpdBox->Multiline = true;
			this->SpdBox->Name = L"SpdBox";
			this->SpdBox->Size = System::Drawing::Size(120, 26);
			this->SpdBox->TabIndex = 4;
			// 
			// trackBar1
			// 
			this->trackBar1->Location = System::Drawing::Point(147, 56);
			this->trackBar1->Maximum = 1000;
			this->trackBar1->Name = L"trackBar1";
			this->trackBar1->Size = System::Drawing::Size(415, 45);
			this->trackBar1->TabIndex = 25;
			this->trackBar1->ValueChanged += gcnew System::EventHandler(this, &KaroshiForm::trackBar1_ValueChanged);
			this->trackBar1->MouseCaptureChanged += gcnew System::EventHandler(this, &KaroshiForm::trackBar1_MouseCaptureChanged);
			// 
			// spdChart
			// 
			chartArea1->AxisX->Enabled = System::Windows::Forms::DataVisualization::Charting::AxisEnabled::False;
			chartArea1->AxisX->ScaleView->Size = 700;
			chartArea1->Name = L"ChartArea1";
			this->spdChart->ChartAreas->Add(chartArea1);
			legend1->Name = L"Legend1";
			this->spdChart->Legends->Add(legend1);
			this->spdChart->Location = System::Drawing::Point(568, 12);
			this->spdChart->Name = L"spdChart";
			series1->ChartArea = L"ChartArea1";
			series1->ChartType = System::Windows::Forms::DataVisualization::Charting::SeriesChartType::FastLine;
			series1->Legend = L"Legend1";
			series1->Name = L"Drehzahl";
			this->spdChart->Series->Add(series1);
			this->spdChart->Size = System::Drawing::Size(630, 504);
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
			this->label2->Location = System::Drawing::Point(9, 441);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(47, 13);
			this->label2->TabIndex = 8;
			this->label2->Text = L"Identifier";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(9, 480);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(50, 13);
			this->label3->TabIndex = 9;
			this->label3->Text = L"Baudrate";
			// 
			// debugBox
			// 
			this->debugBox->Location = System::Drawing::Point(218, 456);
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
			this->ControlMode->Location = System::Drawing::Point(12, 215);
			this->ControlMode->Name = L"ControlMode";
			this->ControlMode->Size = System::Drawing::Size(120, 21);
			this->ControlMode->TabIndex = 11;
			// 
			// cntrlApplyBtn
			// 
			this->cntrlApplyBtn->Location = System::Drawing::Point(147, 215);
			this->cntrlApplyBtn->Name = L"cntrlApplyBtn";
			this->cntrlApplyBtn->Size = System::Drawing::Size(83, 23);
			this->cntrlApplyBtn->TabIndex = 12;
			this->cntrlApplyBtn->Text = L"Apply";
			this->cntrlApplyBtn->UseVisualStyleBackColor = true;
			this->cntrlApplyBtn->Click += gcnew System::EventHandler(this, &KaroshiForm::cntrlApplyBtn_Click);
			// 
			// KaroshiForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(1210, 550);
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
			this->Text = L"KaroshiForm";
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->idSpd))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->baudrate))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->trackBar1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->spdChart))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void trackBar1_ValueChanged(System::Object^ sender, System::EventArgs^ e) {
		SpdBox->Text = trackBar1->Value.ToString();
	}
private: System::Void trackBar1_MouseCaptureChanged(System::Object^ sender, System::EventArgs^ e) {
	if (connectState) {
		identSpd = (uint32_t)idSpd->Value;
		uint8_t data[2];
		getSpeedData((uint16_t)trackBar1->Value, data);
		can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, identSpd, data, 2, &success);
	}
	else {
		trackBar1->Value = 0;
		trackBar1->Text = "Not connected";
	}
}
private: System::Void connectBt_Click(System::Object^ sender, System::EventArgs^ e) {
	if (!connectState) {
		debugBox->Clear();
		// Create IP connection
		ipcon_create(&ipcon);

		// Create device object
		can_v2_create(&can, UID, &ipcon);

		// Connect to brickd
		if (ipcon_connect(&ipcon, HOST, PORT) < 0) {
			debugBox->Text += "Brickdaemon not connected\r\n";
		}
		else {
			can_v2_set_transceiver_configuration(&can, (uint32_t)baudrate->Value, 625, CAN_V2_TRANSCEIVER_MODE_NORMAL);
			debugBox->Text += "Connected\r\n";
			debugBox->Text += "\r\nBaudrate: ";
			debugBox->Text += baudrate->Value;
			debugBox->Text += "\r\n";
			int8_t rbs[] = { 16,-8 };
			can_v2_set_queue_configuration(&can, 8, 0, 383, rbs, 2, 1);
			//can_v2_set_read_filter_configuration(&can, 8, CAN_V2_FILTER_MODE_ACCEPT_ALL, 0x7ff, 0x500);
			connectState = true;
			chartTimer->Start();
		}
	}
}
private: System::Void disconnectBt_Click(System::Object^ sender, System::EventArgs^ e) {
	uint8_t data[2];
	getSpeedData((uint16_t)0, data);
	can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, identSpd, data, 2, &success);
	can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, identCur, data, 2, &success);
	can_v2_set_frame_read_callback_configuration(&can, false);
	can_v2_destroy(&can);
	ipcon_destroy(&ipcon); // Calls ipcon_disconnect internally
	debugBox->Text = "Disconnected";
	connectState = false;
	chartTimer->Stop();
}

private: System::Void chartTimer_Tick(System::Object^ sender, System::EventArgs^ e) {
	uint8_t data[15];
	uint8_t dataLength;
	uint32_t ident = 0x3ea;
	uint8_t type = CAN_V2_FRAME_TYPE_STANDARD_DATA;

	if (connectState) {
		can_v2_read_frame(&can, &success, &type, &ident, data, &dataLength);
		if (success && ident == 0x3e8) { last = getCanData(data); };
	}
	spdChart->Series["Drehzahl"]->Points->AddY(last);
	if (spdChart->Series["Drehzahl"]->Points->Count == 700) {
		spdChart->Series["Drehzahl"]->Points->RemoveAt(0);
	}
}
private: System::Void cntrlApplyBtn_Click(System::Object^ sender, System::EventArgs^ e) {
	uint8_t data[2];
	uint32_t CntrlMode = 0x600;
	getSpeedData((uint16_t)ControlMode->SelectedIndex, data);
	can_v2_write_frame(&can, CAN_V2_FRAME_TYPE_STANDARD_DATA, CntrlMode, data, 2, &success);
}

};
}
