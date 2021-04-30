#include "KaroshiForm.h"
#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include "bricklet_can_v2.h"

#define HOST "localhost"
#define PORT 4223
#define UID "QAd" 




using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]

void main(array<String^>^ args) {
	Application::SetCompatibleTextRenderingDefault(false);
	Application::EnableVisualStyles();
	KaroshiGUI::KaroshiForm frm;
	Application::Run(% frm);
}