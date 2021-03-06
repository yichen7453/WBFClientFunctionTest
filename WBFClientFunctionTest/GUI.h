#pragma once

#include "winbio_api_ctl.h"
#include "winbio_api_means.h"
#include "winbio_return_code.h"

namespace WBFClientFunctionTest {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing::Imaging;
	using namespace System::Runtime::InteropServices;

	PWINBIO_UNIT_SCHEMA unitSchema = NULL;

	static WINBIO_UNIT_ID unitId = NULL;
	static PWINBIO_BIR sample = NULL;
	static SIZE_T sampleSize = 0;
	static WINBIO_REJECT_DETAIL rejectDetail = 0;

	static HRESULT hr = S_OK;
	//static HRESULT enroll_hr = S_OK;
	//static HRESULT identify_hr = S_OK;
	//static HRESULT verify_hr = S_OK;


	static WINBIO_BIOMETRIC_SUBTYPE identify_SubFactor;
	static BOOLEAN verify_match = FALSE;

	static WINBIO_BIOMETRIC_SUBTYPE subFactor = WINBIO_ANSI_381_POS_RH_THUMB;

	int touchCount = 0;

	/// <summary>
	/// GUI 的摘要
	/// </summary>
	public ref class GUI : public System::Windows::Forms::Form
	{
	public:
		GUI(void)
		{
			InitializeComponent();
			//
			//TODO:  在此加入建構函式程式碼
			//
		}

	protected:
		/// <summary>
		/// 清除任何使用中的資源。
		/// </summary>
		~GUI()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnCapture;
	protected:

	protected:
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::ComboBox^  comboBox1;
	private: System::Windows::Forms::GroupBox^  groupBox_title;
	private: System::Windows::Forms::PictureBox^  pb_image;
	private: System::Windows::Forms::GroupBox^  groupBox_ReturnValue;
	private: System::Windows::Forms::Label^  lbMessage;
	private: System::Windows::Forms::Button^  btnEnroll;
	private: System::Windows::Forms::Button^  btnVerify;
	private: System::Windows::Forms::Button^  btnIndentify;
	private: System::Windows::Forms::ComboBox^  comboBox2;



	private: System::Windows::Forms::Label^  lbMean;
	private: System::ComponentModel::BackgroundWorker^  capture_work;
	private: System::Windows::Forms::ComboBox^  comboBox3;
	private: System::ComponentModel::BackgroundWorker^  enroll_work;
	private: System::ComponentModel::BackgroundWorker^  identify_work;
	private: System::ComponentModel::BackgroundWorker^  verify_work;


	private:
		/// <summary>
		/// 設計工具所需的變數。
		/// </summary>
		System::ComponentModel::Container ^components;
	private: System::Windows::Forms::Label^  lbFingerSite;
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::Button^  btnDelete;
	private: System::ComponentModel::BackgroundWorker^  locateSensor_work;
	private: System::ComponentModel::BackgroundWorker^  logonIdentifiedUser_work;
	private: System::ComponentModel::BackgroundWorker^  delete_work;

		String^ subType_string = "RH_THUMB";

#pragma region Windows Form Designer generated code
		/// <summary>
		/// 此為設計工具支援所需的方法 - 請勿使用程式碼編輯器
		/// 修改這個方法的內容。
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnCapture = (gcnew System::Windows::Forms::Button());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox_title = (gcnew System::Windows::Forms::GroupBox());
			this->lbMean = (gcnew System::Windows::Forms::Label());
			this->groupBox_ReturnValue = (gcnew System::Windows::Forms::GroupBox());
			this->lbFingerSite = (gcnew System::Windows::Forms::Label());
			this->lbMessage = (gcnew System::Windows::Forms::Label());
			this->pb_image = (gcnew System::Windows::Forms::PictureBox());
			this->btnEnroll = (gcnew System::Windows::Forms::Button());
			this->btnVerify = (gcnew System::Windows::Forms::Button());
			this->btnIndentify = (gcnew System::Windows::Forms::Button());
			this->comboBox2 = (gcnew System::Windows::Forms::ComboBox());
			this->capture_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->comboBox3 = (gcnew System::Windows::Forms::ComboBox());
			this->enroll_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->identify_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->verify_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnDelete = (gcnew System::Windows::Forms::Button());
			this->locateSensor_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->logonIdentifiedUser_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->delete_work = (gcnew System::ComponentModel::BackgroundWorker());
			this->groupBox_title->SuspendLayout();
			this->groupBox_ReturnValue->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_image))->BeginInit();
			this->SuspendLayout();
			// 
			// btnCapture
			// 
			this->btnCapture->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCapture->Location = System::Drawing::Point(657, 290);
			this->btnCapture->Name = L"btnCapture";
			this->btnCapture->Size = System::Drawing::Size(130, 45);
			this->btnCapture->TabIndex = 14;
			this->btnCapture->Text = L"Capture";
			this->btnCapture->UseVisualStyleBackColor = true;
			this->btnCapture->Click += gcnew System::EventHandler(this, &GUI::btnCapture_Click);
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"PMingLiU", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(136)));
			this->label3->Location = System::Drawing::Point(12, 308);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(0, 16);
			this->label3->TabIndex = 13;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(146, 308);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(0, 12);
			this->label2->TabIndex = 12;
			// 
			// comboBox1
			// 
			this->comboBox1->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->ItemHeight = 21;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(23) {
				L"CloseSession", L"EnrollBegin", L"EnrollCapture",
					L"EnrollCommit", L"EnrollDiscard", L"EnumBiometricUnits", L"EnumDatabases", L"EnumEnrollments", L"EnumServiceProviders", L"Free",
					L"GetCredentialState", L"GetDomainLogonSetting", L"GetEnabledSetting", L"GetLogonSetting", L"LocateSensor", L"LockUnit", L"LogonIdentifiedUser",
					L"OpenSession", L"RemoveAllCredentials", L"RemoveAllDomainCredentials", L"RemoveCredential", L"UnlockUnit", L"Wait"
			});
			this->comboBox1->Location = System::Drawing::Point(668, 185);
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->comboBox1->Size = System::Drawing::Size(260, 29);
			this->comboBox1->TabIndex = 11;
			this->comboBox1->Text = L"CloseSession";
			this->comboBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &GUI::selectedIndex);
			// 
			// groupBox_title
			// 
			this->groupBox_title->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox_title->Controls->Add(this->lbMean);
			this->groupBox_title->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox_title->ForeColor = System::Drawing::Color::Red;
			this->groupBox_title->Location = System::Drawing::Point(8, 4);
			this->groupBox_title->Name = L"groupBox_title";
			this->groupBox_title->Size = System::Drawing::Size(639, 109);
			this->groupBox_title->TabIndex = 10;
			this->groupBox_title->TabStop = false;
			this->groupBox_title->Text = L"Client Application Functions";
			// 
			// lbMean
			// 
			this->lbMean->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbMean->ForeColor = System::Drawing::Color::Blue;
			this->lbMean->Location = System::Drawing::Point(5, 32);
			this->lbMean->Name = L"lbMean";
			this->lbMean->Size = System::Drawing::Size(626, 66);
			this->lbMean->TabIndex = 0;
			this->lbMean->Text = L"label1";
			// 
			// groupBox_ReturnValue
			// 
			this->groupBox_ReturnValue->BackColor = System::Drawing::SystemColors::Control;
			this->groupBox_ReturnValue->Controls->Add(this->lbFingerSite);
			this->groupBox_ReturnValue->Controls->Add(this->lbMessage);
			this->groupBox_ReturnValue->Font = (gcnew System::Drawing::Font(L"Consolas", 15.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox_ReturnValue->Location = System::Drawing::Point(8, 119);
			this->groupBox_ReturnValue->Name = L"groupBox_ReturnValue";
			this->groupBox_ReturnValue->Size = System::Drawing::Size(639, 292);
			this->groupBox_ReturnValue->TabIndex = 12;
			this->groupBox_ReturnValue->TabStop = false;
			this->groupBox_ReturnValue->Text = L"Message";
			// 
			// lbFingerSite
			// 
			this->lbFingerSite->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbFingerSite->ForeColor = System::Drawing::Color::Red;
			this->lbFingerSite->Location = System::Drawing::Point(6, 176);
			this->lbFingerSite->Name = L"lbFingerSite";
			this->lbFingerSite->Size = System::Drawing::Size(621, 24);
			this->lbFingerSite->TabIndex = 16;
			this->lbFingerSite->Text = L"label1";
			this->lbFingerSite->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			this->lbFingerSite->Visible = false;
			// 
			// lbMessage
			// 
			this->lbMessage->Font = (gcnew System::Drawing::Font(L"Consolas", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbMessage->Location = System::Drawing::Point(8, 28);
			this->lbMessage->Name = L"lbMessage";
			this->lbMessage->Size = System::Drawing::Size(623, 255);
			this->lbMessage->TabIndex = 15;
			this->lbMessage->Text = L"This tool for WBF Client Function Test";
			this->lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
			// 
			// pb_image
			// 
			this->pb_image->BackColor = System::Drawing::SystemColors::Control;
			this->pb_image->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->pb_image->Location = System::Drawing::Point(717, 15);
			this->pb_image->Name = L"pb_image";
			this->pb_image->Size = System::Drawing::Size(150, 150);
			this->pb_image->SizeMode = System::Windows::Forms::PictureBoxSizeMode::StretchImage;
			this->pb_image->TabIndex = 9;
			this->pb_image->TabStop = false;
			// 
			// btnEnroll
			// 
			this->btnEnroll->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnEnroll->Location = System::Drawing::Point(657, 345);
			this->btnEnroll->Name = L"btnEnroll";
			this->btnEnroll->Size = System::Drawing::Size(130, 45);
			this->btnEnroll->TabIndex = 15;
			this->btnEnroll->Text = L"Enroll";
			this->btnEnroll->UseVisualStyleBackColor = true;
			this->btnEnroll->Click += gcnew System::EventHandler(this, &GUI::btnEnroll_Click);
			// 
			// btnVerify
			// 
			this->btnVerify->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnVerify->Location = System::Drawing::Point(803, 346);
			this->btnVerify->Name = L"btnVerify";
			this->btnVerify->Size = System::Drawing::Size(130, 45);
			this->btnVerify->TabIndex = 16;
			this->btnVerify->Text = L"Verify";
			this->btnVerify->UseVisualStyleBackColor = true;
			this->btnVerify->Click += gcnew System::EventHandler(this, &GUI::btnVerify_Click);
			// 
			// btnIndentify
			// 
			this->btnIndentify->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnIndentify->Location = System::Drawing::Point(803, 290);
			this->btnIndentify->Name = L"btnIndentify";
			this->btnIndentify->Size = System::Drawing::Size(130, 45);
			this->btnIndentify->TabIndex = 17;
			this->btnIndentify->Text = L"Identify";
			this->btnIndentify->UseVisualStyleBackColor = true;
			this->btnIndentify->Click += gcnew System::EventHandler(this, &GUI::btnIndentify_Click);
			// 
			// comboBox2
			// 
			this->comboBox2->Font = (gcnew System::Drawing::Font(L"Courier New", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->comboBox2->FormattingEnabled = true;
			this->comboBox2->Items->AddRange(gcnew cli::array< System::Object^  >(10) {
				L"RH_THUMB", L"RH_INDEX_FINGER", L"RH_MIDDLE_FINGER",
					L"RH_RING_FINGER", L"RH_LITTLE_FINGER", L"LH_THUMB", L"LH_INDEX_FINGER", L"LH_MIDDLE_FINGER", L"LH_RING_FINGER", L"LH_LITTLE_FINGER"
			});
			this->comboBox2->Location = System::Drawing::Point(668, 232);
			this->comboBox2->Name = L"comboBox2";
			this->comboBox2->Size = System::Drawing::Size(260, 29);
			this->comboBox2->TabIndex = 18;
			this->comboBox2->Text = L"RH_THUMB";
			this->comboBox2->SelectedIndexChanged += gcnew System::EventHandler(this, &GUI::subType_selected);
			// 
			// capture_work
			// 
			this->capture_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::capture_DoWork);
			this->capture_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::capture_Completed);
			// 
			// comboBox3
			// 
			this->comboBox3->FormattingEnabled = true;
			this->comboBox3->Location = System::Drawing::Point(1181, 540);
			this->comboBox3->Name = L"comboBox3";
			this->comboBox3->Size = System::Drawing::Size(121, 20);
			this->comboBox3->TabIndex = 19;
			// 
			// enroll_work
			// 
			this->enroll_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::enroll_DoWork);
			this->enroll_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::enroll_Completed);
			// 
			// identify_work
			// 
			this->identify_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::identify_DoWork);
			this->identify_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::identify_Completed);
			// 
			// verify_work
			// 
			this->verify_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::verify_DoWork);
			this->verify_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::verify_Completed);
			// 
			// btnCancel
			// 
			this->btnCancel->Enabled = false;
			this->btnCancel->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnCancel->Location = System::Drawing::Point(803, 402);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(130, 45);
			this->btnCancel->TabIndex = 20;
			this->btnCancel->Text = L"Cancel";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &GUI::btnCancel_Click);
			// 
			// btnDelete
			// 
			this->btnDelete->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnDelete->Location = System::Drawing::Point(657, 402);
			this->btnDelete->Name = L"btnDelete";
			this->btnDelete->Size = System::Drawing::Size(130, 45);
			this->btnDelete->TabIndex = 21;
			this->btnDelete->Text = L"Delete";
			this->btnDelete->UseVisualStyleBackColor = true;
			this->btnDelete->Click += gcnew System::EventHandler(this, &GUI::btnDelete_Click);
			// 
			// locateSensor_work
			// 
			this->locateSensor_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::locateSensor_DoWork);
			this->locateSensor_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::locateSensor_Completed);
			// 
			// logonIdentifiedUser_work
			// 
			this->logonIdentifiedUser_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::logonIdentifiedUser_Dowork);
			this->logonIdentifiedUser_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::logonIdentifiedUser_Completed);
			// 
			// delete_work
			// 
			this->delete_work->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &GUI::delete_Dowork);
			this->delete_work->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &GUI::delete_Completed);
			// 
			// GUI
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 12);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(952, 453);
			this->Controls->Add(this->btnDelete);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->comboBox3);
			this->Controls->Add(this->comboBox2);
			this->Controls->Add(this->comboBox1);
			this->Controls->Add(this->btnIndentify);
			this->Controls->Add(this->btnVerify);
			this->Controls->Add(this->btnEnroll);
			this->Controls->Add(this->groupBox_ReturnValue);
			this->Controls->Add(this->btnCapture);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->pb_image);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->groupBox_title);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"GUI";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"WBFClientFunctionsTest (1.0)";
			this->FormClosed += gcnew System::Windows::Forms::FormClosedEventHandler(this, &GUI::GUI_Closed);
			this->Load += gcnew System::EventHandler(this, &GUI::GUI_Load);
			this->groupBox_title->ResumeLayout(false);
			this->groupBox_ReturnValue->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^>(this->pb_image))->EndInit();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

	private: System::Void selectedIndex(System::Object^  sender, System::EventArgs^  e) {
				 int selectedIndex = comboBox1->SelectedIndex;
				 Object^ selectedItem = comboBox1->SelectedItem;
				 String^ itemString = selectedItem->ToString();

				 lbFingerSite->Visible = FALSE;

				 groupBox_title->Text = "WinBio" + selectedItem->ToString() + " Function";

				 HRESULT hr = NULL;

				 hr = openSession(WINBIO_FLAG_RAW);

				 if (itemString == "CloseSession") {
					 lbMean->Text = str_closeSession;
					 hr = closeSession();

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));

					 if (SUCCEEDED(hr)) {						
						 openSession(WINBIO_FLAG_RAW);
					 }					 
				 }				
				 else if (itemString == "EnrollBegin") {
					 lbMean->Text = str_enrollBegin;

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopCenter;
					 lbMessage->Text = "\n\nEnroll function flowcharts\r\n";
					 lbMessage->Text += "\n\n EnrollBegin -->\t";
					 lbMessage->Text += "\t EnrollCapture -->\t";
					 lbMessage->Text += "\t\t EnrollCommit";
				 }
				 else if (itemString == "EnrollCapture") {
					 lbMean->Text = str_enrollCapture;

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopCenter;
					 lbMessage->Text = "\n\nEnroll function flowcharts\r\n";
					 lbMessage->Text += "\n\n EnrollBegin -->\t";
					 lbMessage->Text += "\t EnrollCapture -->\t";
					 lbMessage->Text += "\t\t EnrollCommit";
				 }
				 else if (itemString == "EnrollCommit") {
					 lbMean->Text = str_enrollCommit;

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopCenter;
					 lbMessage->Text = "\n\nEnroll function flowcharts\r\n";
					 lbMessage->Text += "\n\n EnrollBegin -->\t";
					 lbMessage->Text += "\t EnrollCapture -->\t";
					 lbMessage->Text += "\t\t EnrollCommit";
				 }
				 else if (itemString == "EnrollDiscard") {
					 lbMean->Text = str_enrollDiscard;

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopCenter;
					 lbMessage->Text = "\n\nEnroll function flowcharts\r\n";
					 lbMessage->Text += "\n\n EnrollBegin -->\t";
					 lbMessage->Text += "\t EnrollCapture -->\t";
					 lbMessage->Text += "\t\t EnrollDiscard";
				 }
				 else if (itemString == "EnumBiometricUnits") {
					 lbMean->Text = str_enumBiometricUnits;

					 SIZE_T unitCount = 0;
					 SIZE_T index = 0;

					 hr = enumBiometricUnits(&unitSchema, &unitCount);
					 if (SUCCEEDED(hr)) {
						 for (index = 0; index < unitCount; ++index) {
							 //printf("\n[%d]: \tUnitID: %d\n", (int)index, unitSchema[index].UnitId);
							 //printf("\tDevice instance ID: %ls\n", unitSchema[index].DeviceInstanceId);
							 //printf("\tPool type: %d\n", unitSchema[index].PoolType);
							 //printf("\tBiometric factor: %d\n", unitSchema[index].BiometricFactor);
							 //printf("\tSensor subtype: %d\n", unitSchema[index].SensorSubType);
							 //printf("\tSensor capabilities: 0x%08x\n", unitSchema[index].Capabilities);
							 //printf("\tDescription: %ls\n", unitSchema[index].Description);
							 //printf("\tManufacturer: %ls\n", unitSchema[index].Manufacturer);
							 //printf("\tModel: %ls\n", unitSchema[index].Model);
							 //printf("\tSerial no: %ls\n", unitSchema[index].SerialNumber);
							 //printf("\tFirmware version: [%d.%d]\n", unitSchema[index].FirmwareVersion.MajorVersion, unitSchema[index].FirmwareVersion.MinorVersion);

							 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopLeft;
							 lbMessage->Text  = " Unit ID: " + unitSchema[index].UnitId + "\r\n";
							 lbMessage->Text += " Device instance ID: " + gcnew String(unitSchema[index].DeviceInstanceId) + "\r\n";
							 lbMessage->Text += " Pool type: " + unitSchema[index].PoolType + "\r\n";
							 lbMessage->Text += " Biometric factor: " + unitSchema[index].BiometricFactor + "\r\n";
							 lbMessage->Text += " Sensor subtype: " + unitSchema[index].SensorSubType + "\r\n";
							 lbMessage->Text += " Sensor capabilities: " + String::Format("0x{0:X8}", unitSchema[index].Capabilities) + "\r\n";
							 lbMessage->Text += " Description: " + gcnew String(unitSchema[index].Description) + "\r\n";
							 lbMessage->Text += " Manufacturer: " + gcnew String(unitSchema[index].Manufacturer) + "\r\n";
							 lbMessage->Text += " Model: " + gcnew String(unitSchema[index].Model) + "\r\n";
							 lbMessage->Text += " Serial no: " + gcnew String(unitSchema[index].SerialNumber) + "\r\n";
							 lbMessage->Text += " Firmware version: [" + unitSchema[index].FirmwareVersion.MajorVersion + "." + unitSchema[index].FirmwareVersion.MinorVersion + "]";
						 }
					 }
				 }
				 else if (itemString == "EnumDatabases") {
					 lbMean->Text = str_enumDatabases;
					 PWINBIO_STORAGE_SCHEMA storageSchemaArray = NULL;
					 SIZE_T storageCount = 0;
					 SIZE_T index = 0;

					 hr = enumDatabases(&storageSchemaArray, &storageCount);

					 if (SUCCEEDED(hr)) {
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopLeft;
						 lbMessage->Text = "";
						 for (index = 0; index < storageCount; ++index) {
							 //printf("\n [%d]: \tBiometric factor: 0x%08x\n", index, storageSchemaArray[index].BiometricFactor);
							 //printf("\tDatabase ID: ");
							 //DisplayGuid(&storageSchemaArray[index].DatabaseId);
							 //printf("\n");
							 //printf("\tData format: ");
							 //DisplayGuid(&storageSchemaArray[index].DataFormat);
							 //printf("\n");
							 //printf("\tAttributes: 0x%08x\n", storageSchemaArray[index].Attributes);
							 //printf("\tFile path: %ws\n", storageSchemaArray[index].FilePath);
							 //printf("\tCnx string: %ws\n", storageSchemaArray[index].ConnectionString);

							 lbMessage->Text += "Biometric factor: " + storageSchemaArray[index].BiometricFactor + "\r\n";
							 lbMessage->Text += "Database ID: " + String::Format("{0:X8}-{1:X4}-{2:X4}-{3:X2}{4:X2}-{5:X2}{6:X2}{7:X2}{8:X2}{9:X2}{10:X2}",
																		storageSchemaArray[index].DatabaseId.Data1,
																		storageSchemaArray[index].DatabaseId.Data2,
																		storageSchemaArray[index].DatabaseId.Data3,
																		storageSchemaArray[index].DatabaseId.Data4[0],
																		storageSchemaArray[index].DatabaseId.Data4[1],
																		storageSchemaArray[index].DatabaseId.Data4[2],
																		storageSchemaArray[index].DatabaseId.Data4[3],
																		storageSchemaArray[index].DatabaseId.Data4[4],
																		storageSchemaArray[index].DatabaseId.Data4[5],
																		storageSchemaArray[index].DatabaseId.Data4[6],
																		storageSchemaArray[index].DatabaseId.Data4[7] + "\r\n");

							 lbMessage->Text += "\r\n";
						 }						 
					 }
				 }
				 else if (itemString == "EnumEnrollments") {
					 lbMean->Text = str_enumEnrollments;

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(S_OK));
					 /*
					 PWINBIO_BIOMETRIC_SUBTYPE subFactorArray = NULL;
					 SIZE_T subFactorCount = 0;
					 SIZE_T index;
					 WINBIO_BIOMETRIC_SUBTYPE SubFactor = 0;

					 hr = enumEnrollments(&subFactorArray, &subFactorCount);

					 if (SUCCEEDED(hr)) {
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 for (index = 0; index < subFactorCount; ++index) {
							 SubFactor = subFactorArray[index];
							 switch (SubFactor)
							 {
								case WINBIO_ANSI_381_POS_RH_THUMB:
									printf("\n RH thumb\n");
									lbMessage->Text = "RH thumb";
									break;
								case WINBIO_ANSI_381_POS_RH_INDEX_FINGER:
									printf("\n RH index finger\n");
									lbMessage->Text = "RH index finger";
									break;
								case WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER:
									printf("\n RH middle finger\n");
									lbMessage->Text = "RH middle finger";
									break;
								case WINBIO_ANSI_381_POS_RH_RING_FINGER:
									printf("\n RH ring finger\n");
									lbMessage->Text = "RH ring finger";
									break;
								case WINBIO_ANSI_381_POS_RH_LITTLE_FINGER:
									printf("\n RH little finger\n");
									lbMessage->Text = "RH little finger";
									break;
								case WINBIO_ANSI_381_POS_LH_THUMB:
									printf("\n LH thumb\n");
									lbMessage->Text = "LH thumb";
									break;
								case WINBIO_ANSI_381_POS_LH_INDEX_FINGER:
									printf("\n LH index finger\n");
									lbMessage->Text = "LH index finger";
									break;
								case WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER:
									printf("\n LH middle finger\n");
									lbMessage->Text = "LH middle finger";
									break;
								case WINBIO_ANSI_381_POS_LH_RING_FINGER:
									printf("\n LH ring finger\n");
									lbMessage->Text = "LH ring finger";
									break;
								case WINBIO_ANSI_381_POS_LH_LITTLE_FINGER:
									printf("\n LH little finger\n");
									lbMessage->Text = "LH little finger";
									break;
								default:
									printf("\n The sub-factor is not correct\n");
									lbMessage->Text = "The sub-factor is not correct";
									break;
							 }
						 }
					 }
					 */
				 }
				 else if (itemString == "EnumServiceProviders") {
					 lbMean->Text = str_enumServiceProviders;
					 PWINBIO_BSP_SCHEMA bspSchemaArray = NULL;
					 SIZE_T bspCount = 0;
					 SIZE_T index = 0;

					 hr = enumServiceProviders(&bspSchemaArray, &bspCount);

					 if (SUCCEEDED(hr)) {
						 for (index = 0; index < bspCount; ++index) {
							 //printf("\n [%d]: \tBiometric factor: 0x%08x\n", index, bspSchemaArray[index].BiometricFactor);
							 //printf("\tBspId: ");
							 //DisplayGuid(&bspSchemaArray[index].BspId);
							 //printf("\n");
							 //printf("\tDescription: %ws\n", bspSchemaArray[index].Description);
							 //printf("\tVendor: %ws\n", bspSchemaArray[index].Vendor);
							 //printf("\tVersion: %d.%d\n", bspSchemaArray[index].Version.MajorVersion, bspSchemaArray[index].Version.MinorVersion);

							 lbMessage->TextAlign = System::Drawing::ContentAlignment::TopLeft;
							 lbMessage->Text = "Biometric factor: " + bspSchemaArray[index].BiometricFactor + "\r\n";
							 lbMessage->Text += "Bsp ID: " + String::Format("{0:X8}-{1:X4}-{2:X4}-{3:X2}{4:X2}-{5:X2}{6:X2}{7:X2}{8:X2}{9:X2}{10:X2}",
																	bspSchemaArray[index].BspId.Data1,
																	bspSchemaArray[index].BspId.Data2,
																	bspSchemaArray[index].BspId.Data3,
																	bspSchemaArray[index].BspId.Data4[0],
																	bspSchemaArray[index].BspId.Data4[1],
																    bspSchemaArray[index].BspId.Data4[2],
																	bspSchemaArray[index].BspId.Data4[3],
																	bspSchemaArray[index].BspId.Data4[4],
																	bspSchemaArray[index].BspId.Data4[5],
																	bspSchemaArray[index].BspId.Data4[6],
																	bspSchemaArray[index].BspId.Data4[7] + "\r\n");
							 lbMessage->Text += "Vendor: " + gcnew String(bspSchemaArray[index].Vendor) + "\r\n";
							 lbMessage->Text += "Version: [" + bspSchemaArray[index].Version.MajorVersion + "." + bspSchemaArray[index].Version.MinorVersion + "]\r\n";
							 lbMessage->Text += "Description: " + gcnew String(bspSchemaArray[index].Description);
						 }
						 if (bspSchemaArray != NULL) {
							 freeAddress(bspSchemaArray);
							 bspSchemaArray = NULL;
						 }
					 }
				 }
				 else if (itemString == "Free") {
					 lbMean->Text = str_free;

					 if (unitSchema != NULL) {

						 hr = freeAddress(unitSchema);

						 unitSchema = NULL;

						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = gcnew String(getReturnCode(hr));
					 }
				 }
				 else if (itemString == "GetCredentialState") {
					 lbMean->Text = str_getCredentialState;
					 WINBIO_CREDENTIAL_STATE credState;

					 hr = getCredentialState(&credState);

					 if (SUCCEEDED(hr)) {
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 switch (credState)
						 {
							 case WINBIO_CREDENTIAL_SET:
								 printf("\n Credential set.\n");
								 lbMessage->Text = "A credential has been specified.";
								 break;
							 case WINBIO_CREDENTIAL_NOT_SET:
								 printf("\n Credential NOT set.\n");
								 lbMessage->Text = "A credential has not been specified.";
								 break;
							 default:
								 printf("\n ERROR: Invalid credential state.");
								 lbMessage->Text = "ERROR: Invalid credential state.";
								 break;
						 }
					 }
				 }
				 else if (itemString == "GetDomainLogonSetting") {
					 lbMean->Text = str_getDomainLogonSetting;
					 BOOLEAN value = FALSE;
					 WINBIO_SETTING_SOURCE_TYPE source = WINBIO_SETTING_SOURCE_INVALID;

					 hr = getDomainLogonSetting(&value, &source);

					 if (SUCCEEDED(hr)) {
						 printf("\n Value: %s, Source: ", value ? "TRUE" : "FALSE");
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Biometric domain logon: " + (value ? "TRUE" : "FALSE") + "\r\n";
						 lbMessage->Text += "\n\n";
						 switch (source)
						 {
							 case WINBIO_SETTING_SOURCE_INVALID:
								 printf("\n WINBIO_SETTING_SOURCE_INVALID\n");
								 lbMessage->Text += "The setting is not valid.";
								 break;
							 case WINBIO_SETTING_SOURCE_DEFAULT:
								 printf("\n WINBIO_SETTING_SOURCE_DEFAULT\n");
								 lbMessage->Text += "The setting originated from built-in policy.";
								 break;
							 case WINBIO_SETTING_SOURCE_POLICY:
								 printf("\n WINBIO_SETTING_SOURCE_POLICY\n");
								 lbMessage->Text += "The setting was created by Group Policy.";
								 break;
							 case WINBIO_SETTING_SOURCE_LOCAL:
								 printf("\n WINBIO_SETTING_SOURCE_LOCAL\n");
								 lbMessage->Text += "The setting originated in the local computer register.";
								 break;
							 default:
								 printf("\n [unrecognized source]");
								 lbMessage->Text += "Source: Unrecognized source";
								 break;
						 }
					 }
				 }
				 else if (itemString == "GetEnabledSetting") {
					 lbMean->Text = str_getEnabledSetting;
					 BOOLEAN value = FALSE;
					 WINBIO_SETTING_SOURCE_TYPE source = WINBIO_SETTING_SOURCE_INVALID;

					 hr = getEnabledSetting(&value, &source);

					 if (SUCCEEDED(hr)) {
						 printf("\n Value: %s, Source: ", value ? "TRUE" : "FALSE");
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Windows Biometric Framework is currently enabled: " + (value ? "TRUE" : "FALSE") + "\r\n";
						 lbMessage->Text += "\n\n";
						 switch (source)
						 {
							 case WINBIO_SETTING_SOURCE_INVALID:
								 printf("\n WINBIO_SETTING_SOURCE_INVALID\n");
								 lbMessage->Text += "The setting is not valid.";
								 break;
							 case WINBIO_SETTING_SOURCE_DEFAULT:
								 printf("\n WINBIO_SETTING_SOURCE_DEFAULT\n");
								 lbMessage->Text += "The setting originated from built-in policy.";
								 break;
							 case WINBIO_SETTING_SOURCE_POLICY:
								 printf("\n WINBIO_SETTING_SOURCE_POLICY\n");
								 lbMessage->Text += "The setting was created by Group Policy.";
								 break;
							 case WINBIO_SETTING_SOURCE_LOCAL:
								 printf("\n WINBIO_SETTING_SOURCE_LOCAL\n");
								 lbMessage->Text += "The setting originated in the local computer registry.";
								 break;
							 default:
								 printf("\n [unrecognized source]");
								 lbMessage->Text += "Source: Unrecognized source";
								 break;
						 }
					 }
				 }
				 else if (itemString == "GetLogonSetting") {
					 lbMean->Text = str_getLogonSetting;
					 BOOLEAN value = FALSE;
					 WINBIO_SETTING_SOURCE_TYPE source = WINBIO_SETTING_SOURCE_INVALID;

					 hr = getLogonSetting(&value, &source);

					 if (SUCCEEDED(hr)) {
						 printf("\n Value: %s, Source: ", value ? "TRUE" : "FALSE");
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Biometric logons are enabled: " + (value ? "TRUE" : "FALSE") + "\r\n";
						 lbMessage->Text += "\n\n";
						 switch (source)
						 {
							 case WINBIO_SETTING_SOURCE_INVALID:
								 printf("\n WINBIO_SETTING_SOURCE_INVALID\n");
								 lbMessage->Text += "The setting is not valid.";
								 break;
							 case WINBIO_SETTING_SOURCE_DEFAULT:
								 printf("\n WINBIO_SETTING_SOURCE_DEFAULT\n");
								 lbMessage->Text += "The setting originated from built-in policy.";
								 break;
							 case WINBIO_SETTING_SOURCE_POLICY:
								 printf("\n WINBIO_SETTING_SOURCE_POLICY\n");
								 lbMessage->Text += "The setting was created by Group Policy.";
								 break;
							 case WINBIO_SETTING_SOURCE_LOCAL:
								 printf("\n WINBIO_SETTING_SOURCE_LOCAL\n");
								 lbMessage->Text += "The setting originated in the local computer registry.";
								 break;
							 default:
								 printf("\n [unrecognized source]");
								 lbMessage->Text += "Source: Unrecognized source";
								 break;
						 }
					 }
				 }				
				 else if (itemString == "LocateSensor") {
					 lbMean->Text = str_locateSensor;
					 
					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = "Press finger to retrieves the id number of biometric unit";

					 hr = openSession(WINBIO_FLAG_RAW);

					 locateSensor_work->RunWorkerAsync();
					 
					 comboBox1->Enabled = false;
					 comboBox2->Enabled = false;
					 btnCapture->Enabled = false;
					 btnEnroll->Enabled = false;
					 btnDelete->Enabled = false;
					 btnIndentify->Enabled = false;
					 btnVerify->Enabled = false;
					 btnCancel->Enabled = true;
				 }
				 else if (itemString == "LockUnit") {
					 lbMean->Text = str_lockUnit;

					 hr = lockUnit();

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }
				 else if (itemString == "LogonIdentifiedUser") {
					 lbMean->Text = str_logonIdentifiedUser;

					 lbMessage->Text = "Press finger to perform WinBioLogonIdentifiedUser function";

					 hr = openSession(WINBIO_FLAG_DEFAULT);

					 logonIdentifiedUser_work->RunWorkerAsync();

					 comboBox1->Enabled = false;
					 comboBox2->Enabled = false;
					 btnCapture->Enabled = false;
					 btnEnroll->Enabled = false;
					 btnDelete->Enabled = false;
					 btnIndentify->Enabled = false;
					 btnVerify->Enabled = false;
					 btnCancel->Enabled = true;
				 }
				 else if (itemString == "OpenSession") {
					 lbMean->Text = str_openSession;

					 hr = openSession(WINBIO_FLAG_RAW);

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }								
				 else if (itemString == "RemoveAllCredentials") {
					 lbMean->Text = str_removeAllCredentials;

					 hr = removeAllCredentials();

					 if (SUCCEEDED(hr)) {
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Successfully removed all biometric credentials.";
					 }
				 }
				 else if (itemString == "RemoveAllDomainCredentials") {
					 lbMean->Text = str_removeAllDomainCredentials;

					 hr = removeAllDomainCredentials();

					 if (SUCCEEDED(hr)) {
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Successfully removed all domain biometric credentials.";
					 }
				 }
				 else if (itemString == "RemoveCredential") {
					 lbMean->Text = str_removeCredential;

					 hr = removeCredential();

					 if (SUCCEEDED(hr)) {
						 lbMessage->Text = gcnew String(getReturnCode(hr));
					 }
					 else {
						 if (hr == WINBIO_E_CRED_PROV_NO_CREDENTIAL) {
							 lbMessage->Text = "The specified identity does not exist or does not \n\nhave any related records in the credential store.";
						 }
					 }
				 }			
				 else if (itemString == "UnlockUnit") {
					 lbMean->Text = str_unlockUnit;

					 hr = unlockUnit();

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }				 				
				 else if (itemString == "Wait") {
					 lbMean->Text = str_wait;

					 hr = wait();

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }
	}

	private: System::Void GUI_Load(System::Object^  sender, System::EventArgs^  e) {

				 HRESULT hr = S_OK;
				 SIZE_T unitCount = 0;

				 lbMean->Text = "The following functions are supported for client application development by the Windows Biometric Framework API";

				 hr = openSession(WINBIO_FLAG_RAW);

				 hr = enumBiometricUnits(&unitSchema, &unitCount);				 
	}

	private: System::Void GUI_Closed(System::Object^  sender, System::Windows::Forms::FormClosedEventArgs^  e) {

				 closeSession();
	}

	private: System::Void btnCapture_Click(System::Object^  sender, System::EventArgs^  e) {

				 groupBox_title->Text = "WinBioCaptureSample Function";
				 lbMean->Text = str_captureSample;

				 comboBox1->Enabled = false;
				 comboBox2->Enabled = false;
				 btnCapture->Enabled = false;
				 btnEnroll->Enabled = false;
				 btnDelete->Enabled = false;
				 btnVerify->Enabled = false;
				 btnIndentify->Enabled = false;
				 btnCancel->Enabled = true;

				 lbFingerSite->Visible = FALSE;

				 comboBox3->Focus();

				 pb_image->Image = nullptr;

				 hr = openSession(WINBIO_FLAG_RAW);

				 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 lbMessage->Text = "Press finger to capture image.";

				 capture_work->RunWorkerAsync();
	}

	private: System::Void capture_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 printf("\n capture_DoWork()\n");

				 hr = captureSampleFromService(&unitId, &sample, &sampleSize, &rejectDetail);
	}

	private: System::Void capture_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 printf("\n capture_Completed()\n");

				 if (FAILED(hr)) {

					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }
				 else {
					 if (sample != NULL) {
						 //PWINBIO_BIR_HEADER BirHeader = (PWINBIO_BIR_HEADER)(((PBYTE)data) + data->HeaderBlock.Offset);
						 PWINBIO_BDB_ANSI_381_HEADER AnsiBdbHeader = (PWINBIO_BDB_ANSI_381_HEADER)(((PBYTE)sample) + sample->StandardDataBlock.Offset);
						 PWINBIO_BDB_ANSI_381_RECORD AnsiBdbRecord = (PWINBIO_BDB_ANSI_381_RECORD)(((PBYTE)AnsiBdbHeader) + sizeof(WINBIO_BDB_ANSI_381_HEADER));

						 DWORD width = AnsiBdbRecord->HorizontalLineLength; // Width of image in pixels
						 DWORD height = AnsiBdbRecord->VerticalLineLength; // Height of image in pixels

						 //printf("\n Image resolution: %d x %d\n", width, height);

						 PBYTE firstPixel = (PBYTE)((PBYTE)AnsiBdbRecord) + sizeof(WINBIO_BDB_ANSI_381_RECORD);

						 std::vector<uint8_t> imageData(width * height);
						 memcpy(&imageData[0], firstPixel, width * height);

						 array<Byte>^ byteArray = gcnew array<Byte>(width * height);
						 Marshal::Copy((IntPtr)imageData.data(), byteArray, 0, width * height);

						 pb_image->Image = ToGrayBitmap(byteArray, width, height);

						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 //lbMessage->Text = "Unit ID: " + unitId + "\r\n";
						 //lbMessage->Text += "Data Length: " + sampleSize + " bytes";
						 lbMessage->Text = "Capture image success.";

						 freeAddress(sample);
						 sample = NULL;
					 }
					 else {
						 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
						 lbMessage->Text = "Capture image fail.";
					 }
				 }

				 comboBox1->Enabled = true;
				 comboBox2->Enabled = true;
				 btnCapture->Enabled = true;
				 btnEnroll->Enabled = true;
				 btnDelete->Enabled = true;
				 btnVerify->Enabled = true;
				 btnIndentify->Enabled = true;
				 btnCancel->Enabled = false;
	}

	private: System::Void btnEnroll_Click(System::Object^  sender, System::EventArgs^  e) {
				 groupBox_title->Text = "WinBioEnroll Function";
				 lbMean->Text = str_enrollCapture;

				 printf("\n subType = %d\n", subFactor);

				 hr = openSession(WINBIO_FLAG_DEFAULT);

				 hr = enrollBegin(subFactor);

				 if (FAILED(hr)) {
					 printf("\n enrollBegin failed. hr = 0x%x\n", hr);
					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }
				 else {
					 comboBox1->Enabled = false;
					 comboBox2->Enabled = false;
					 btnCapture->Enabled = false;
					 btnEnroll->Enabled = false;
					 btnDelete->Enabled = false;
					 btnVerify->Enabled = false;
					 btnIndentify->Enabled = false;
					 btnCancel->Enabled = true;

					 lbFingerSite->Visible = FALSE;

					 comboBox3->Focus();

					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text  = "Enroll fingerprint to " + subType_string + " site.\n\n\n";
					 lbMessage->Text += "Repeatedly lift and rest your finger on the sensor unitl setup is complete.";

					 enroll_work->RunWorkerAsync();
				 }
	}

	private: System::Void enroll_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

				 WINBIO_REJECT_DETAIL rejectDetail = 0;

				 hr = enrollCapture(&rejectDetail);
	}

	private: System::Void enroll_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
				 
				 WINBIO_IDENTITY identity = { 0 };
				 BOOLEAN isNewTemplate = TRUE;

				 //printf("\n Touch the sensor to capture %s sample.", (touchCount == 1) ? "the first" : "another");

				 if (hr == WINBIO_I_MORE_DATA) {
					 printf("\n WINBIO_I_MORE_DATA\n");

					 touchCount++;

					 lbMessage->Text = "Greate, touch sensor again.\n\n";
					 lbMessage->Text += "Count: " + touchCount;

					 enroll_work->RunWorkerAsync();
				 }
				 else {
					 if (FAILED(hr)) {

						 if (hr == WINBIO_E_BAD_CAPTURE) {
							 printf("\n Error: Bad capture; reason: 0x%x", hr);
							 
							 lbMessage->Text = gcnew String(getReturnCode(hr));

							 enroll_work->RunWorkerAsync();
						 }
						 else if (hr == WINBIO_E_CANCELED) {
							 lbMessage->Text = gcnew String(getReturnCode(hr));

							 touchCount = 0;

							 comboBox1->Enabled = true;
							 comboBox2->Enabled = true;
							 btnCapture->Enabled = true;
							 btnEnroll->Enabled = true;
							 btnDelete->Enabled = true;
							 btnVerify->Enabled = true;
							 btnIndentify->Enabled = true;
							 btnCancel->Enabled = false;
						 }
						 else {
							 printf("\n enrollCapture failed. hr = 0x%x", hr);

							 lbMessage->Text = gcnew String(getReturnCode(hr));

							 touchCount = 0;

							 closeSession();

							 comboBox1->Enabled = true;
							 comboBox2->Enabled = true;
							 btnCapture->Enabled = true;
							 btnEnroll->Enabled = true;
							 btnDelete->Enabled = true;
							 btnVerify->Enabled = true;
							 btnIndentify->Enabled = true;
							 btnCancel->Enabled = false;
						 }
					 }
					 else {
						 printf("\n Template completed.\n");

						 hr = enrollCommit(&identity, &isNewTemplate);

						 if (FAILED(hr)) {
							printf("\n WinBioEnrollCommit failed. hr = 0x%x\n", hr);
							lbMessage->Text = gcnew String(getReturnCode(hr));
						 }
						 else {
							 lbMessage->Text  = "All set !!\n\n";
							 lbMessage->Text += "Use your fingerprint the next time you want to \nunlock your device.";
						 }

						 touchCount = 0;

						 comboBox1->Enabled = true;
						 comboBox2->Enabled = true;
						 btnCapture->Enabled = true;
						 btnEnroll->Enabled = true;
						 btnDelete->Enabled = true;
						 btnVerify->Enabled = true;
						 btnIndentify->Enabled = true;
						 btnCancel->Enabled = false;
					 }
				 }
	}

	private: System::Void btnIndentify_Click(System::Object^  sender, System::EventArgs^  e) {
				 groupBox_title->Text = "WinBioIdentify Function";
				 lbMean->Text = str_identify;

				 comboBox1->Enabled = false;
				 comboBox2->Enabled = false;
				 btnCapture->Enabled = false;
				 btnEnroll->Enabled = false;
				 btnDelete->Enabled = false;
				 btnVerify->Enabled = false;
				 btnIndentify->Enabled = false;
				 btnCancel->Enabled = true;

				 lbFingerSite->Visible = FALSE;

				 comboBox3->Focus();

				 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 lbMessage->Text = "Press finger to identify an existing biometric template.";

				 hr = openSession(WINBIO_FLAG_DEFAULT);

				 identify_work->RunWorkerAsync();
	}

	private: System::Void identify_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 WINBIO_IDENTITY identity = { 0 };
				 WINBIO_UNIT_ID unitId = 0;

				 hr = identify(&unitId, &identity, &identify_SubFactor);

				 //printf("\n Unit ID: %d\n", unitId);
				 //DisplayGuid(&identity.Value.TemplateGuid);
	}

	private: System::Void identify_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

				 if (SUCCEEDED(hr)) {
					 lbFingerSite->Visible = true;

					 switch (identify_SubFactor)
					 {					 
					 case WINBIO_ANSI_381_POS_RH_THUMB:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "RH_THUMB";
						 break;
					 case WINBIO_ANSI_381_POS_RH_INDEX_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "RH_INDEX_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "RH_MIDDLE_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_RH_RING_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "RH_RING_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_RH_LITTLE_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "RH_LITTLE_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_LH_THUMB:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "LH_THUMB";
						 break;
					 case WINBIO_ANSI_381_POS_LH_INDEX_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "LH_INDEX_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "LH_MIDDLE_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_LH_RING_FINGER:
						 lbMessage->Text = "Identify to the\n";
						 lbFingerSite->Text = "LH_RING_FINGER";
						 break;
					 case WINBIO_ANSI_381_POS_LH_LITTLE_FINGER:
						 lbMessage->Text = "Identify to the\nR";
						 lbFingerSite->Text = "LH_LITTLE_FINGER";
						 break;
					 default:
						 lbMessage->Text = "The sub-factor is not correct";
						 lbFingerSite->Visible = false;
						 break;
					 }
				 }
				 else {
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }			 

				 comboBox1->Enabled = true;
				 comboBox2->Enabled = true;
				 btnCapture->Enabled = true;
				 btnEnroll->Enabled = true;
				 btnDelete->Enabled = true;
				 btnVerify->Enabled = true;
				 btnIndentify->Enabled = true;
				 btnCancel->Enabled = false;
	}

	private: System::Void btnVerify_Click(System::Object^  sender, System::EventArgs^  e) {
				 groupBox_title->Text = "WinBioVerify Function";
				 lbMean->Text = str_verify;

				 comboBox1->Enabled = false;
				 comboBox2->Enabled = false;
				 btnCapture->Enabled = false;
				 btnEnroll->Enabled = false;
				 btnDelete->Enabled = false;
				 btnVerify->Enabled = false;
				 btnIndentify->Enabled = false;

				 lbFingerSite->Visible = FALSE;

				 comboBox3->Focus();

				 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 lbMessage->Text = "Press finger and determines whether the sample \n\ncorresponds to the specified user identity";

				 hr = openSession(WINBIO_FLAG_DEFAULT);

				 verify_work->RunWorkerAsync();
	}

	private: System::Void verify_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {

				 WINBIO_UNIT_ID unitId = 0;
				 BOOLEAN match = FALSE;

				 hr = verify(subFactor, &unitId, &verify_match);

				 //printf("\n Fingerprint verified: %d\n", unitId);
				 //printf("\n Match: %s, ", match ? "TRUE" : "FALSE");
	}

	private: System::Void verify_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

				 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 //lbMessage->Text = "Fingerprint verified: " + unitId + "\r\n";
				 //lbMessage->Text += "Match: " + (match ? "TRUE" : "FALSE") + "\r\n";
				 if (SUCCEEDED(hr)) {
					 lbMessage->Text  = "Verify to " + subType_string + "\r\n\r\n";

					 lbFingerSite->Visible = TRUE;
					 lbFingerSite->Text = "Result : " + (verify_match ? "TRUE" : "FALSE");
				 }
				 else {
					 if (hr == WINBIO_E_NO_MATCH) {
						 lbMessage->Text = "No MATCH - identity verification failed.";
					 }
					 else if (hr == WINBIO_E_BAD_CAPTURE) {
						 lbMessage->Text = "Bad capture.";
					 }
					 else {
						 printf("\n WinBioVerify failed. hr = 0x%x\n", hr);
						 lbMessage->Text = gcnew String(getReturnCode(hr));
					 }
				 }

				 comboBox1->Enabled = true;
				 comboBox2->Enabled = true;
				 btnCapture->Enabled = true;
				 btnEnroll->Enabled = true;
				 btnDelete->Enabled = true;
				 btnVerify->Enabled = true;
				 btnIndentify->Enabled = true;
				 btnCancel->Enabled = false;
	}

	private: System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e) {

				 HRESULT hr = S_OK;

				 groupBox_title->Text = "WinBioCancel Function";
				 lbMean->Text = str_cancel;

				 hr = cancelSession();

				 if (SUCCEEDED(hr)) {
					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }
				 else {
					 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }
	}

	private: System::Void btnDelete_Click(System::Object^  sender, System::EventArgs^  e) {

				 HRESULT hr = S_OK;

				 lbMean->Text = str_deleteTemplate;

				 comboBox1->Enabled = false;
				 comboBox2->Enabled = false;
				 btnCapture->Enabled = false;
				 btnEnroll->Enabled = false;	
				 btnDelete->Enabled = false;
				 btnVerify->Enabled = false;
				 btnIndentify->Enabled = false;
				 btnCancel->Enabled = true;

				 lbFingerSite->Visible = FALSE;

				 comboBox3->Focus();

				 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;
				 lbMessage->Text = "If you want to delete the fingerprint, \n\nmake sure it is the owner of the device";

				 delete_work->RunWorkerAsync();
	}

	private: System::Void delete_Dowork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 WINBIO_IDENTITY identity = { 0 };
				 WINBIO_UNIT_ID unitId = 0;

				 hr = identify(&unitId, &identity, &identify_SubFactor);
	}

	private: System::Void delete_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

				 if (SUCCEEDED(hr)) {
					 hr = deleteTemplate();
				 }
				
				 lbMessage->Text = gcnew String(getReturnCode(hr));

				 comboBox1->Enabled = true;
				 comboBox2->Enabled = true;
				 btnCapture->Enabled = true;
				 btnEnroll->Enabled = true;
				 btnDelete->Enabled = true;
				 btnVerify->Enabled = true;
				 btnIndentify->Enabled = true;
				 btnCancel->Enabled = false;
	}

	public: static Bitmap^ ToGrayBitmap(array<Byte>^ rawValues, int width, int height) {
				Bitmap^ bmp = gcnew Bitmap(width, height, System::Drawing::Imaging::PixelFormat::Format8bppIndexed);
				System::Drawing::Rectangle rect = System::Drawing::Rectangle(0, 0, bmp->Width, bmp->Height);
				BitmapData^ bmpData = bmp->LockBits(rect, System::Drawing::Imaging::ImageLockMode::WriteOnly, bmp->PixelFormat);

				int stride = bmpData->Stride;
				int offset = stride - width;
				IntPtr iptr = bmpData->Scan0;
				int scanBytes = stride * height;

				int posScan = 0, posReal = 0;

				array<Byte>^ pixelValues = gcnew array<Byte>(scanBytes);

				for (int x = 0; x < height; x++) {
					for (int y = 0; y < width; y++) {
						pixelValues[posScan++] = rawValues[posReal++];
					}
					posScan += offset;
				}

				Marshal::Copy(pixelValues, 0, iptr, scanBytes);
				bmp->UnlockBits(bmpData);

				ColorPalette^ temPalette;

				Bitmap^ tempBmp = gcnew Bitmap(1, 1, System::Drawing::Imaging::PixelFormat::Format8bppIndexed);
				temPalette = tempBmp->Palette;

				for (int i = 0; i < 256; i++) {
					temPalette->Entries[i] = Color::FromArgb(i, i, i);
				}

				bmp->Palette = temPalette;

				return bmp;
	}

	private: System::Void DisplayGuid(__in PWINBIO_UUID Guid) {
				 printf("\n {%08X-%04X-%04X-%02X%02X-%02X%02X%02X%02X%02X%02X}",
					 Guid->Data1,
					 Guid->Data2,
					 Guid->Data3,
					 Guid->Data4[0],
					 Guid->Data4[1],
					 Guid->Data4[2],
					 Guid->Data4[3],
					 Guid->Data4[4],
					 Guid->Data4[5],
					 Guid->Data4[6],
					 Guid->Data4[7]
					 );
	}

	private: System::Void subType_selected(System::Object^  sender, System::EventArgs^  e) {

				 int selectedIndex = comboBox2->SelectedIndex;
				 printf("\n selectedIndex (%d)\n", selectedIndex);

				 Object^ selectedItem = comboBox2->SelectedItem;

				 subType_string = selectedItem->ToString();

				 switch (selectedIndex)
				 {
				 case 0:
					 subFactor = WINBIO_ANSI_381_POS_RH_THUMB;
					 break;
				 case 1:
					 subFactor = WINBIO_ANSI_381_POS_RH_INDEX_FINGER;
					 break;
				 case 2:
					 subFactor = WINBIO_ANSI_381_POS_RH_MIDDLE_FINGER;
					 break;
				 case 3:
					 subFactor = WINBIO_ANSI_381_POS_RH_RING_FINGER;
					 break;
				 case 4:
					 subFactor = WINBIO_ANSI_381_POS_RH_LITTLE_FINGER;
					 break;
				 case 5:
					 subFactor = WINBIO_ANSI_381_POS_LH_THUMB;
					 break;
				 case 6:
					 subFactor = WINBIO_ANSI_381_POS_LH_INDEX_FINGER;
					 break;
				 case 7:
					 subFactor = WINBIO_ANSI_381_POS_LH_MIDDLE_FINGER;
					 break;
				 case 8:
					 subFactor = WINBIO_ANSI_381_POS_LH_RING_FINGER;
					 break;
				 case 9:
					 subFactor = WINBIO_ANSI_381_POS_LH_LITTLE_FINGER;
					 break;
				 }
	}

	private: System::Void locateSensor_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
				 
				 hr = locateSensor(&unitId);				 
	}
	private: System::Void locateSensor_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {
	
				 if (SUCCEEDED(hr)) {
					 lbMessage->Text = "Specifies the biometric unit: " + ((unsigned long)unitId).ToString();
				 }
				 else {
					 lbMessage->Text = gcnew String(getReturnCode(hr));
				 }

				 comboBox1->Enabled = true;
				 comboBox2->Enabled = true;
				 btnCapture->Enabled = true;
				 btnEnroll->Enabled = true;
				 btnDelete->Enabled = true;
				 btnIndentify->Enabled = true;
				 btnVerify->Enabled = true;
				 btnCancel->Enabled = false;
	}

	private: System::Void logonIdentifiedUser_Dowork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e) {
	
				 hr = logonIdentifiedUser();
	}

	private: System::Void logonIdentifiedUser_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) {

				 lbMessage->TextAlign = System::Drawing::ContentAlignment::MiddleCenter;

				 switch (hr)
				 {
				 case S_FALSE:
					 lbMessage->Text = "Target is the logged on user. No action taken.";
					 break;
				 case S_OK:
					 lbMessage->Text = "Fast user switch initiated.";
					 break;
				 default:
					 lbMessage->Text = gcnew String(getReturnCode(hr));
					 break;
				 }

				 comboBox1->Enabled = true;
				 comboBox2->Enabled = true;
				 btnCapture->Enabled = true;
				 btnEnroll->Enabled = true;
				 btnDelete->Enabled = true;
				 btnVerify->Enabled = true;
				 btnIndentify->Enabled = true;
				 btnCancel->Enabled = false;
	}
};
}
