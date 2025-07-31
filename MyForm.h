

#pragma once

#include "wrappers.h"
#include <string>


#include <msclr\marshal_cppstd.h>
#include <Windows.h>



namespace Project2 {




	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;


	//other class!!!



	/// <summary>
	/// Resumen de MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:

		ref class FileItem
		{
		public:
			String^ FileName;
			String^ FullPath;

			FileItem(String^ fileName, String^ fullPath)
			{
				this->FileName = fileName;
				this->FullPath = fullPath;
			}

			virtual String^ ToString() override
			{
				return FileName; // Esto es lo que se mostrará en el ListBox
			}
		};

		MyForm(void)
		{
			InitializeComponent();
			this->AllowDrop = true;
			this->listBox1->AllowDrop = true;

			this->DragEnter += gcnew DragEventHandler(this, &MyForm::Form_DragEnter);
			this->DragDrop += gcnew DragEventHandler(this, &MyForm::Form_DragDrop);
			this->listBox1->DragEnter += gcnew DragEventHandler(this, &MyForm::ListBox_DragEnter);
			this->listBox1->DragDrop += gcnew DragEventHandler(this, &MyForm::ListBox_DragDrop);



			this->lbFileSecreto->AllowDrop = true;
			this->lbFileSecreto->DragEnter += gcnew DragEventHandler(this, &MyForm::lbFileSecreto_DragEnter);
			this->lbFileSecreto->DragDrop += gcnew DragEventHandler(this, &MyForm::lbFileSecreto_DragDrop);

			this->lbFileSecreto->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Project2::MyForm::lbFileSecreto_KeyDown);


			//lbFileSecreto  lbFileSecreto_DragEnter



			this->listBox1->KeyDown += gcnew System::Windows::Forms::KeyEventHandler(this, &Project2::MyForm::listBox1_KeyDown);

			this->MouseDown += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseDown);
			this->MouseMove += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseMove);
			this->MouseUp += gcnew System::Windows::Forms::MouseEventHandler(this, &MyForm::MyForm_MouseUp);

			//
			//TODO: agregar código de constructor aquí
			//

			this->listBox1->MouseDoubleClick += gcnew MouseEventHandler(this, &MyForm::listBox1_MouseDoubleClick);

		}




	protected:
		/// <summary>
		/// Limpiar los recursos que se estén usando.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}

	private: System::Windows::Forms::ListBox^ listBox1;
	private: System::Windows::Forms::GroupBox^ groupBox1;


	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::GroupBox^ groupBox3;
	private: System::Windows::Forms::GroupBox^ groupBox2;
	private: System::Windows::Forms::Label^ label2;

	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::RadioButton^ rbOcultarRGB;

	private: System::Windows::Forms::Button^ button2;
	private: System::Windows::Forms::RadioButton^ rbExtraerRGB;


	private: System::Windows::Forms::Label^ label4;




	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::GroupBox^ groupBox4;
	private: System::Windows::Forms::Label^ label8;

	private: System::Windows::Forms::Button^ button3;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::RadioButton^ radioButton7;
	private: System::Windows::Forms::RadioButton^ radioButton5;
	private: System::Windows::Forms::GroupBox^ groupBox5;
	private: System::Windows::Forms::TextBox^ txtKPublica;
	private: System::Windows::Forms::TextBox^ txtKPrivada;


	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Button^ btnKPrivada;
	private: System::Windows::Forms::Button^ btnKPublica;



	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Button^ button6;
	private: System::Windows::Forms::TextBox^ txtPassExtraer;


	private: System::Windows::Forms::Button^ button7;

	private: System::Windows::Forms::ListBox^ lbFileSecreto;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::RadioButton^ radioButton1;





	protected:

	private:


		/// <summary>
		/// Variable del diseñador necesaria.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Método necesario para admitir el Diseñador. No se puede modificar
		/// el contenido de este método con el editor de código.
		/// </summary>
		void InitializeComponent(void)
		{
			System::ComponentModel::ComponentResourceManager^ resources = (gcnew System::ComponentModel::ComponentResourceManager(MyForm::typeid));
			this->listBox1 = (gcnew System::Windows::Forms::ListBox());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->txtPassExtraer = (gcnew System::Windows::Forms::TextBox());
			this->button2 = (gcnew System::Windows::Forms::Button());
			this->rbExtraerRGB = (gcnew System::Windows::Forms::RadioButton());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->rbOcultarRGB = (gcnew System::Windows::Forms::RadioButton());
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->radioButton7 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton5 = (gcnew System::Windows::Forms::RadioButton());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->button7 = (gcnew System::Windows::Forms::Button());
			this->btnKPrivada = (gcnew System::Windows::Forms::Button());
			this->btnKPublica = (gcnew System::Windows::Forms::Button());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->txtKPublica = (gcnew System::Windows::Forms::TextBox());
			this->txtKPrivada = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->button6 = (gcnew System::Windows::Forms::Button());
			this->lbFileSecreto = (gcnew System::Windows::Forms::ListBox());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->groupBox1->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->SuspendLayout();
			// 
			// listBox1
			// 
			this->listBox1->AllowDrop = true;
			this->listBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->listBox1->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->listBox1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->listBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->listBox1->FormattingEnabled = true;
			this->listBox1->ItemHeight = 16;
			this->listBox1->Location = System::Drawing::Point(23, 72);
			this->listBox1->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->listBox1->Name = L"listBox1";
			this->listBox1->Size = System::Drawing::Size(206, 178);
			this->listBox1->TabIndex = 1;
			this->listBox1->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::listBox1_SelectedIndexChanged);
			// 
			// groupBox1
			// 
			this->groupBox1->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->groupBox1->Controls->Add(this->groupBox3);
			this->groupBox1->Controls->Add(this->groupBox2);
			this->groupBox1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->groupBox1->Location = System::Drawing::Point(247, 72);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(200, 324);
			this->groupBox1->TabIndex = 2;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L"Metodología";
			this->groupBox1->Enter += gcnew System::EventHandler(this, &MyForm::groupBox1_Enter);
			// 
			// groupBox3
			// 
			this->groupBox3->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->groupBox3->Controls->Add(this->radioButton2);
			this->groupBox3->Controls->Add(this->txtPassExtraer);
			this->groupBox3->Controls->Add(this->button2);
			this->groupBox3->Controls->Add(this->rbExtraerRGB);
			this->groupBox3->Controls->Add(this->label4);
			this->groupBox3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->groupBox3->Location = System::Drawing::Point(6, 174);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(188, 144);
			this->groupBox3->TabIndex = 6;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"Extraer";
			// 
			// txtPassExtraer
			// 
			this->txtPassExtraer->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->txtPassExtraer->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtPassExtraer->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtPassExtraer->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->txtPassExtraer->Location = System::Drawing::Point(6, 112);
			this->txtPassExtraer->Margin = System::Windows::Forms::Padding(15, 3, 3, 3);
			this->txtPassExtraer->Name = L"txtPassExtraer";
			this->txtPassExtraer->Size = System::Drawing::Size(78, 26);
			this->txtPassExtraer->TabIndex = 14;
			this->txtPassExtraer->Text = L"clave";
			// 
			// button2
			// 
			this->button2->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12));
			this->button2->Location = System::Drawing::Point(87, 112);
			this->button2->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->button2->Name = L"button2";
			this->button2->Size = System::Drawing::Size(95, 26);
			this->button2->TabIndex = 10;
			this->button2->Text = L"Extraer de";
			this->button2->UseVisualStyleBackColor = true;
			this->button2->Click += gcnew System::EventHandler(this, &MyForm::button2_Click);
			// 
			// rbExtraerRGB
			// 
			this->rbExtraerRGB->AutoSize = true;
			this->rbExtraerRGB->Location = System::Drawing::Point(6, 38);
			this->rbExtraerRGB->Name = L"rbExtraerRGB";
			this->rbExtraerRGB->Size = System::Drawing::Size(136, 20);
			this->rbExtraerRGB->TabIndex = 8;
			this->rbExtraerRGB->TabStop = true;
			this->rbExtraerRGB->Text = L"Sustitución RGB";
			this->rbExtraerRGB->UseVisualStyleBackColor = true;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label4->Location = System::Drawing::Point(6, 19);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(63, 16);
			this->label4->TabIndex = 7;
			this->label4->Text = L"Método";
			// 
			// groupBox2
			// 
			this->groupBox2->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->groupBox2->Controls->Add(this->radioButton1);
			this->groupBox2->Controls->Add(this->label3);
			this->groupBox2->Controls->Add(this->rbOcultarRGB);
			this->groupBox2->Controls->Add(this->button1);
			this->groupBox2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->groupBox2->Location = System::Drawing::Point(6, 22);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(188, 146);
			this->groupBox2->TabIndex = 5;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L"Ocultar";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label3->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label3->Location = System::Drawing::Point(6, 19);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(57, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Método";
			// 
			// rbOcultarRGB
			// 
			this->rbOcultarRGB->AutoSize = true;
			this->rbOcultarRGB->Location = System::Drawing::Point(6, 37);
			this->rbOcultarRGB->Name = L"rbOcultarRGB";
			this->rbOcultarRGB->Size = System::Drawing::Size(136, 20);
			this->rbOcultarRGB->TabIndex = 1;
			this->rbOcultarRGB->TabStop = true;
			this->rbOcultarRGB->Text = L"Sustitución RGB";
			this->rbOcultarRGB->UseVisualStyleBackColor = true;
			// 
			// button1
			// 
			this->button1->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12));
			this->button1->Location = System::Drawing::Point(87, 114);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(95, 26);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Ocultar en";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label1->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label1->Location = System::Drawing::Point(20, 53);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(165, 16);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Arrastre la imagen aquí";
			this->label1->Click += gcnew System::EventHandler(this, &MyForm::label1_Click);
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label2->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label2->Location = System::Drawing::Point(468, 53);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(123, 16);
			this->label2->TabIndex = 5;
			this->label2->Text = L"Archivo a ocultar";
			// 
			// groupBox4
			// 
			this->groupBox4->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->groupBox4->Controls->Add(this->radioButton7);
			this->groupBox4->Controls->Add(this->radioButton5);
			this->groupBox4->Controls->Add(this->label8);
			this->groupBox4->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox4->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->groupBox4->Location = System::Drawing::Point(465, 256);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(202, 140);
			this->groupBox4->TabIndex = 6;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Encriptación";
			// 
			// radioButton7
			// 
			this->radioButton7->AutoSize = true;
			this->radioButton7->Location = System::Drawing::Point(9, 38);
			this->radioButton7->Name = L"radioButton7";
			this->radioButton7->Size = System::Drawing::Size(89, 20);
			this->radioButton7->TabIndex = 8;
			this->radioButton7->Text = L"Simétrica";
			this->radioButton7->UseVisualStyleBackColor = true;
			// 
			// radioButton5
			// 
			this->radioButton5->AutoSize = true;
			this->radioButton5->Location = System::Drawing::Point(9, 63);
			this->radioButton5->Name = L"radioButton5";
			this->radioButton5->Size = System::Drawing::Size(96, 20);
			this->radioButton5->TabIndex = 7;
			this->radioButton5->Text = L"Asimétrica";
			this->radioButton5->UseVisualStyleBackColor = true;
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label8->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label8->Location = System::Drawing::Point(6, 19);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(57, 16);
			this->label8->TabIndex = 6;
			this->label8->Text = L"Método";
			// 
			// button3
			// 
			this->button3->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button3->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12));
			this->button3->Location = System::Drawing::Point(652, 5);
			this->button3->Margin = System::Windows::Forms::Padding(1);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(36, 26);
			this->button3->TabIndex = 7;
			this->button3->Text = L"X";
			this->button3->UseVisualStyleBackColor = true;
			this->button3->Click += gcnew System::EventHandler(this, &MyForm::button3_Click);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 14.25F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label7->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label7->Location = System::Drawing::Point(12, 9);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(310, 19);
			this->label7->TabIndex = 8;
			this->label7->Text = L"Diplomatic Oculter | estenografía";
			// 
			// groupBox5
			// 
			this->groupBox5->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->groupBox5->Controls->Add(this->button7);
			this->groupBox5->Controls->Add(this->btnKPrivada);
			this->groupBox5->Controls->Add(this->btnKPublica);
			this->groupBox5->Controls->Add(this->label10);
			this->groupBox5->Controls->Add(this->txtKPublica);
			this->groupBox5->Controls->Add(this->txtKPrivada);
			this->groupBox5->Controls->Add(this->label9);
			this->groupBox5->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->groupBox5->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->groupBox5->Location = System::Drawing::Point(23, 256);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(206, 140);
			this->groupBox5->TabIndex = 9;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L"Llaves";
			// 
			// button7
			// 
			this->button7->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button7->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12));
			this->button7->Location = System::Drawing::Point(9, 108);
			this->button7->Margin = System::Windows::Forms::Padding(0, 3, 3, 3);
			this->button7->Name = L"button7";
			this->button7->Size = System::Drawing::Size(95, 26);
			this->button7->TabIndex = 16;
			this->button7->Text = L"Generar";
			this->button7->UseVisualStyleBackColor = true;
			this->button7->Click += gcnew System::EventHandler(this, &MyForm::button7_Click);
			// 
			// btnKPrivada
			// 
			this->btnKPrivada->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnKPrivada->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnKPrivada->Location = System::Drawing::Point(147, 68);
			this->btnKPrivada->Name = L"btnKPrivada";
			this->btnKPrivada->Size = System::Drawing::Size(49, 23);
			this->btnKPrivada->TabIndex = 15;
			this->btnKPrivada->Text = L"Copiar";
			this->btnKPrivada->UseVisualStyleBackColor = true;
			this->btnKPrivada->Click += gcnew System::EventHandler(this, &MyForm::btnKPrivada_Click);
			// 
			// btnKPublica
			// 
			this->btnKPublica->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->btnKPublica->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 8.25F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->btnKPublica->Location = System::Drawing::Point(147, 37);
			this->btnKPublica->Name = L"btnKPublica";
			this->btnKPublica->Size = System::Drawing::Size(49, 23);
			this->btnKPublica->TabIndex = 10;
			this->btnKPublica->Text = L"Copiar";
			this->btnKPublica->UseVisualStyleBackColor = true;
			this->btnKPublica->Click += gcnew System::EventHandler(this, &MyForm::button4_Click);
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label10->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label10->Location = System::Drawing::Point(6, 70);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(58, 16);
			this->label10->TabIndex = 14;
			this->label10->Text = L"Privada";
			// 
			// txtKPublica
			// 
			this->txtKPublica->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->txtKPublica->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtKPublica->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtKPublica->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->txtKPublica->Location = System::Drawing::Point(67, 37);
			this->txtKPublica->Margin = System::Windows::Forms::Padding(15, 3, 3, 3);
			this->txtKPublica->Multiline = true;
			this->txtKPublica->Name = L"txtKPublica";
			this->txtKPublica->Size = System::Drawing::Size(81, 20);
			this->txtKPublica->TabIndex = 13;
			// 
			// txtKPrivada
			// 
			this->txtKPrivada->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->txtKPrivada->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->txtKPrivada->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->txtKPrivada->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->txtKPrivada->Location = System::Drawing::Point(67, 68);
			this->txtKPrivada->Margin = System::Windows::Forms::Padding(15, 3, 3, 3);
			this->txtKPrivada->Multiline = true;
			this->txtKPrivada->Name = L"txtKPrivada";
			this->txtKPrivada->Size = System::Drawing::Size(81, 20);
			this->txtKPrivada->TabIndex = 12;
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->label9->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->label9->Location = System::Drawing::Point(6, 41);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(55, 16);
			this->label9->TabIndex = 6;
			this->label9->Text = L"Pública";
			// 
			// button6
			// 
			this->button6->BackgroundImage = (cli::safe_cast<System::Drawing::Image^>(resources->GetObject(L"button6.BackgroundImage")));
			this->button6->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->button6->FlatAppearance->BorderSize = 0;
			this->button6->FlatStyle = System::Windows::Forms::FlatStyle::Flat;
			this->button6->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12));
			this->button6->Location = System::Drawing::Point(200, 50);
			this->button6->Margin = System::Windows::Forms::Padding(1);
			this->button6->Name = L"button6";
			this->button6->Size = System::Drawing::Size(29, 22);
			this->button6->TabIndex = 10;
			this->button6->UseVisualStyleBackColor = true;
			// 
			// lbFileSecreto
			// 
			this->lbFileSecreto->AllowDrop = true;
			this->lbFileSecreto->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(62)), static_cast<System::Int32>(static_cast<System::Byte>(70)),
				static_cast<System::Int32>(static_cast<System::Byte>(55)));
			this->lbFileSecreto->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->lbFileSecreto->Font = (gcnew System::Drawing::Font(L"MS UI Gothic", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(0)));
			this->lbFileSecreto->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->lbFileSecreto->FormattingEnabled = true;
			this->lbFileSecreto->ItemHeight = 16;
			this->lbFileSecreto->Location = System::Drawing::Point(465, 72);
			this->lbFileSecreto->Margin = System::Windows::Forms::Padding(15, 3, 15, 3);
			this->lbFileSecreto->Name = L"lbFileSecreto";
			this->lbFileSecreto->Size = System::Drawing::Size(202, 178);
			this->lbFileSecreto->TabIndex = 11;
			this->lbFileSecreto->SelectedIndexChanged += gcnew System::EventHandler(this, &MyForm::lbFileSecreto_SelectedIndexChanged);
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(6, 63);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(107, 20);
			this->radioButton1->TabIndex = 7;
			this->radioButton1->TabStop = true;
			this->radioButton1->Text = L"Incrustación";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Location = System::Drawing::Point(6, 64);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(107, 20);
			this->radioButton2->TabIndex = 16;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Incrustación";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// MyForm
			// 
			this->AllowDrop = true;
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->BackColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(74)), static_cast<System::Int32>(static_cast<System::Byte>(89)),
				static_cast<System::Int32>(static_cast<System::Byte>(66)));
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Stretch;
			this->ClientSize = System::Drawing::Size(693, 408);
			this->Controls->Add(this->lbFileSecreto);
			this->Controls->Add(this->button6);
			this->Controls->Add(this->groupBox5);
			this->Controls->Add(this->label7);
			this->Controls->Add(this->button3);
			this->Controls->Add(this->groupBox4);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->groupBox1);
			this->Controls->Add(this->listBox1);
			this->ForeColor = System::Drawing::Color::FromArgb(static_cast<System::Int32>(static_cast<System::Byte>(222)), static_cast<System::Int32>(static_cast<System::Byte>(223)),
				static_cast<System::Int32>(static_cast<System::Byte>(214)));
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::None;
			this->Name = L"MyForm";
			this->Text = L"MyForm";
			this->Load += gcnew System::EventHandler(this, &MyForm::MyForm_Load);
			this->groupBox1->ResumeLayout(false);
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}





	private: System::Void Form_DragEnter(System::Object^ sender, DragEventArgs^ e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;
		else
			e->Effect = DragDropEffects::None;
	}

	private: System::Void Form_DragDrop(System::Object^ sender, DragEventArgs^ e) {
		HandleFileDrop(e);
	}
	private: System::Drawing::Point mouseOffset; // Para almacenar la posición del mouse
	private: bool dragging; // Para saber si estamos arrastrando
	private: System::Void listBox1_MouseDoubleClick(System::Object^ sender, MouseEventArgs^ e)
	{
		// Verificar cli
		int index = listBox1->IndexFromPoint(e->Location);
		if (index != ListBox::NoMatches)
		{
			FileItem^ selectedItem = safe_cast<FileItem^>(listBox1->Items[index]);
			MessageBox::Show(
				"Nombre: " + selectedItem->FileName + "\n" +
				"Ruta completa: " + selectedItem->FullPath,
				"Información del archivo",
				MessageBoxButtons::OK,
				MessageBoxIcon::Information
			);
		}
	}

	private: System::Void ListBox_DragEnter(System::Object^ sender, DragEventArgs^ e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;
		else
			e->Effect = DragDropEffects::None;
	}

	private: System::Void lbFileSecreto_DragEnter(System::Object^ sender, DragEventArgs^ e) {
		if (e->Data->GetDataPresent(DataFormats::FileDrop))
			e->Effect = DragDropEffects::Copy;
		else
			e->Effect = DragDropEffects::None;
	}

	private: System::Void ListBox_DragDrop(System::Object^ sender, DragEventArgs^ e)
	{
		HandleFileDrop(e);
	}
	private: System::Void lbFileSecreto_DragDrop(System::Object^ sender, DragEventArgs^ e)
	{
		HandleFileDropLbFileSecreto(e);
	}

	private: void HandleFileDrop(DragEventArgs^ e) {
		// Asegúrate de que estás usando el tipo correcto
		array<String^>^ files = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop));
		for each (String ^ file in files) {
			String^ fileName = System::IO::Path::GetFileName(file); // Solo el nombre

			// Verificar si ya existe (comparando solo nombres)
			bool exists = false;
			for each (FileItem ^ item in listBox1->Items) {
				if (item->FileName == fileName) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				// Crear un nuevo FileItem y agregarlo al ListBox
				FileItem^ newItem = gcnew FileItem(fileName, file);
				listBox1->Items->Add(newItem);
			}
		}
	}

	private: void HandleFileDropLbFileSecreto(DragEventArgs^ e) {
		// Asegúrate de que estás usando el tipo correcto
		array<String^>^ files = safe_cast<array<String^>^>(e->Data->GetData(DataFormats::FileDrop));
		for each (String ^ file in files) {
			String^ fileName = System::IO::Path::GetFileName(file); // Solo el nombre

			// Verificar si ya existe (comparando solo nombres)
			bool exists = false;
			for each (FileItem ^ item in lbFileSecreto->Items) {
				if (item->FileName == fileName) {
					exists = true;
					break;
				}
			}

			if (!exists) {
				// Crear un nuevo FileItem y agregarlo al ListBox
				FileItem^ newItem = gcnew FileItem(fileName, file);
				lbFileSecreto->Items->Add(newItem);
			}
		}
	}


#pragma endregion
	private: System::Void button1_Click(System::Object^ sender, System::EventArgs^ e) {



		if (listBox1->SelectedIndex == -1)
		{
			MessageBox::Show("Por favor seleccione un archivo");
			return;

		}


		// Declarar un contador estático para el número de salida
		static int outputCounter = 0;

		if (rbOcultarRGB->Checked) {
			try {
				if (listBox1->SelectedIndex > -1 && (lbFileSecreto->SelectedIndex > -1)) {
					FileItem^ selectedItemIMG = safe_cast<FileItem^>(listBox1->Items[listBox1->SelectedIndex]);
					FileItem^ selectedItemSecreto = safe_cast<FileItem^>(lbFileSecreto->Items[lbFileSecreto->SelectedIndex]);

					// Obtener la extensión del archivo de imagen seleccionado
					String^ extension = System::IO::Path::GetExtension(selectedItemIMG->FullPath);


					if (extension != ".bmp") {

						MessageBox::Show("El archivo de imagen debe ser un BMP.");
						return;
					}
					// Generar el nuevo nombre de archivo de salida
					String^ outputFileName = String::Format("out{0}{1}", outputCounter++, extension);

					// Llamar a HideFileHybrid con el nuevo nombre de archivo
					P::LsbWrapper::HideFileHybrid(selectedItemIMG->FullPath, selectedItemSecreto->FullPath, outputFileName, txtKPublica->Text);
					//MessageBox::Show("Archivo ocultado con cifrado híbrido exitosamente!");
				}
				else {
					MessageBox::Show("Seleccione los archivos para procesar");
				}
			}
			catch (Exception^ e) {
				MessageBox::Show("Error: " + e->Message);
			}
		}









	}

	private: System::Void listBox1_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}


	private: System::Void listBox1_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// Verificar si la tecla presionada es Suprimir
		if (e->KeyCode == System::Windows::Forms::Keys::Delete) {
			// Verificar si hay un ítem seleccionado
			if (listBox1->SelectedIndex != -1) {
				// Eliminar el ítem seleccionado
				listBox1->Items->RemoveAt(listBox1->SelectedIndex);
			}
		}
	}



	private: System::Void lbFileSecreto_KeyDown(System::Object^ sender, System::Windows::Forms::KeyEventArgs^ e) {
		// Verificar si la tecla presionada es Suprimir
		if (e->KeyCode == System::Windows::Forms::Keys::Delete) {
			// Verificar si hay un ítem seleccionado
			if (lbFileSecreto->SelectedIndex != -1) {
				// Eliminar el ítem seleccionado
				lbFileSecreto->Items->RemoveAt(lbFileSecreto->SelectedIndex);
			}
		}
	}



	private: System::Void MyForm_Load(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void label1_Click(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void textBox1_TextChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void groupBox1_Enter(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button3_Click(System::Object^ sender, System::EventArgs^ e) {
		Close();
	}
	private: System::Void button7_Click(System::Object^ sender, System::EventArgs^ e) {
		P::LsbWrapper::GenerateAndShowKeys();
		P::LsbWrapper::GetCurrentPrivateKey();
		P::LsbWrapper::GetCurrentPublicKey();

		txtKPrivada->Text = P::LsbWrapper::current_priv_key;
		txtKPublica->Text = P::LsbWrapper::current_pub_key;


	}


	private: System::Void button2_Click(System::Object^ sender, System::EventArgs^ e) {



		if (rbExtraerRGB->Checked) {


			static int n = 0;
			n++;


			if (listBox1->SelectedIndex > -1)
			{
				FileItem^ selectedItem = safe_cast<FileItem^>(listBox1->Items[listBox1->SelectedIndex]);
				String^ outputFileName = String::Format("secreto{0}", n);


				String^ extension = System::IO::Path::GetExtension(selectedItem->FullPath);


				if (extension != ".bmp") {

					MessageBox::Show("El archivo de imagen debe ser un BMP.");
					return;
				}
				// Construir ruta completa
				P::LsbWrapper::ExtractFileHybrid(
					selectedItem->FullPath,
					outputFileName,
					txtKPrivada->Text
				);


			}



		}









	}



		   // Manejador de MouseDown
	private: System::Void MyForm_MouseDown(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			dragging = true; // Iniciar el arrastre
			mouseOffset = System::Drawing::Point(e->X, e->Y); // Guardar la posición del mouse
		}
	}
		   // Manejador de MouseMove
	private: System::Void MyForm_MouseMove(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (dragging) {
			// Mover el formulario
			this->Location = System::Drawing::Point(this->Location.X + e->X - mouseOffset.X, this->Location.Y + e->Y - mouseOffset.Y);
		}
	}
		   // Manejador de MouseUp
	private: System::Void MyForm_MouseUp(System::Object^ sender, System::Windows::Forms::MouseEventArgs^ e) {
		if (e->Button == System::Windows::Forms::MouseButtons::Left) {
			dragging = false; // Detener el arrastre
		}
	}






	private: System::Void lbFileSecreto_SelectedIndexChanged(System::Object^ sender, System::EventArgs^ e) {
	}
	private: System::Void button4_Click(System::Object^ sender, System::EventArgs^ e) {
		Clipboard::SetText(txtKPublica->Text);
	}
	private: System::Void btnKPrivada_Click(System::Object^ sender, System::EventArgs^ e) {

		Clipboard::SetText(txtKPrivada->Text);


	}
	};





}
