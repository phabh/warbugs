#pragma once
#include "CCoreServer.h"
#include <stdlib.h>
#include <vcclr.h>

namespace WarBugsServer {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class frmPrincipal : public System::Windows::Forms::Form
	{
	public:
		// Variaveis do Jogo
		CDataBase			* _dataBase;
	private: System::Windows::Forms::ToolStripStatusLabel^  barHora;
	private: System::Windows::Forms::ToolStripStatusLabel^  barFPS;
	private: System::Windows::Forms::ToolStripStatusLabel^  barTempoAtualizacao;
	private: System::Windows::Forms::TabPage^  tabConfig;
	private: System::Windows::Forms::GroupBox^  gbConfigIniciais;




	private: System::Windows::Forms::GroupBox^  gbConfigBD;
	private: System::Windows::Forms::GroupBox^  groupBox1;
	private: System::Windows::Forms::Label^  labValorAtualBkp;

	private: System::Windows::Forms::Button^  btAplicarHorasBkp;



	private: System::Windows::Forms::GroupBox^  groupBox2;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  labValorBkpMercado;


	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::Button^  btAplicarMercadoBkp;



	private: System::Windows::Forms::Label^  lnovoValorBkp;
	private: System::Windows::Forms::Label^  labValorBkpTotal;









	private: System::Windows::Forms::GroupBox^  groupBox5;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  labValorToleranciaPing;

	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::Button^  btAplicarToleranciaPing;



	private: System::Windows::Forms::GroupBox^  groupBox4;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  labValorVerPing;

	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Button^  btAplicarIntervaloPing;




	private: System::Windows::Forms::GroupBox^  groupBox3;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::Label^  labValorFPS;


	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::Button^  btAplicarFPS;
	private: System::Windows::Forms::MaskedTextBox^  txtValorBkpTotal;

	private: System::Windows::Forms::MaskedTextBox^  txtToleranciaPing;
	private: System::Windows::Forms::MaskedTextBox^  txtValorVerPing;
	private: System::Windows::Forms::MaskedTextBox^  txtValorFPS;
	private: System::Windows::Forms::MaskedTextBox^  txtValorBkpMercado;



	private: System::Windows::Forms::Label^  labHost;
	private: System::Windows::Forms::TextBox^  txtHost;
	private: System::Windows::Forms::GroupBox^  groupBox6;
	private: System::Windows::Forms::Label^  labSenha;
	private: System::Windows::Forms::TextBox^  txtSenha;
	private: System::Windows::Forms::Label^  labLogin;
	private: System::Windows::Forms::TextBox^  txtLogin;
	private: System::Windows::Forms::Button^  btConectar;
	private: System::Windows::Forms::Label^  labBD;
	private: System::Windows::Forms::TextBox^  txtBD;
	private: System::Windows::Forms::TabPage^  tabMercado;





	private: System::Windows::Forms::GroupBox^  gbDadosIniciais;


	private: System::Windows::Forms::Label^  lbPeriodoFinal;
	private: System::Windows::Forms::Label^  lbPeriodoInicial;
	private: System::Windows::Forms::Label^  lbVendedores;
	private: System::Windows::Forms::ComboBox^  cbVendedor;
	private: System::Windows::Forms::DateTimePicker^  dtPeriodoInicial;
	private: System::Windows::Forms::DateTimePicker^  dtPeriodoFinal;
	private: System::Windows::Forms::Button^  btGeraGrafico;
private: System::Windows::Forms::DataVisualization::Charting::Chart^  graficoCapital;
private: System::Windows::Forms::GroupBox^  groupBox7;
private: System::Windows::Forms::GroupBox^  groupBox8;
private: System::Windows::Forms::Button^  btAplicarCoeficientes;


private: System::Windows::Forms::Label^  label13;
private: System::Windows::Forms::Label^  label11;
private: System::Windows::Forms::Label^  label7;
private: System::Windows::Forms::Label^  label5;
private: System::Windows::Forms::Label^  label3;
private: System::Windows::Forms::DomainUpDown^  nDescontoTempo;

private: System::Windows::Forms::DomainUpDown^  nDescontoLealdade;

private: System::Windows::Forms::Button^  btVerCoeficientes;





private: System::Windows::Forms::ComboBox^  comboBox1;
private: System::Windows::Forms::NumericUpDown^  nCorteOferta;

private: System::Windows::Forms::NumericUpDown^  nCorteDemanda;

private: System::Windows::Forms::NumericUpDown^  nCorteDurabilidade;

private: System::Windows::Forms::GroupBox^  groupBox9;
private: System::Windows::Forms::Label^  label18;
private: System::Windows::Forms::Label^  label19;
private: System::Windows::Forms::Label^  label20;
private: System::Windows::Forms::Label^  label17;
private: System::Windows::Forms::Label^  label16;
private: System::Windows::Forms::Label^  label15;
private: System::Windows::Forms::Button^  button4;
private: System::Windows::Forms::Button^  button3;
private: System::Windows::Forms::MaskedTextBox^  maskedTextBox6;
private: System::Windows::Forms::MaskedTextBox^  maskedTextBox5;
private: System::Windows::Forms::MaskedTextBox^  maskedTextBox4;
private: System::Windows::Forms::MaskedTextBox^  maskedTextBox3;
private: System::Windows::Forms::MaskedTextBox^  maskedTextBox2;
private: System::Windows::Forms::MaskedTextBox^  maskedTextBox1;
private: System::Windows::Forms::Label^  label14;













	internal: 
	private: 
















	public: 
		CCoreServer			^ _coreServer;


		frmPrincipal(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//
			WarBugsLog::_log = logBox;
			_dataBase = new CDataBase("localhost","warbugs","bd","bugsteam");
			this->barStatusBD->Text = L"Status BD: "+( _dataBase->isConnected() ? "ON":"OFF");
			this->barStatusJogo->Text = L"Status Jogo: "+( timer->Enabled ? "ON":"OFF");
			_coreServer = gcnew CCoreServer(_dataBase);
			this->barHora->Text = L""+DateTime::Now;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~frmPrincipal()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::TabControl^  abas;
	protected: 

	protected: 

	private: System::Windows::Forms::TabPage^  tabJogadoresOn;
private: System::Windows::Forms::StatusStrip^  sa;


	protected: 


	private: System::Windows::Forms::ToolStripStatusLabel^  barStatusJogo;
	private: System::Windows::Forms::MenuStrip^  menu;
































	private: System::Windows::Forms::ToolStripStatusLabel^  barStatusBD;
	private: System::Windows::Forms::ToolStripStatusLabel^  barNumJogadores;
	private: System::Windows::Forms::ToolStripMenuItem^  arquivoToolStripMenuItem;
	private: System::Windows::Forms::DataGridView^  gridJogadores;




	private: System::Windows::Forms::GroupBox^  gbJogador;
	private: System::Windows::Forms::Button^  btMandarMSG;


	private: System::Windows::Forms::Button^  btKicar;

	private: System::Windows::Forms::GroupBox^  gbServer;
	private: System::Windows::Forms::Button^  btLigarServer;
	private: System::Windows::Forms::TextBox^  txtMSG;

	private: System::Windows::Forms::DataGridViewTextBoxColumn^  idConexao;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nomeJogador;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nomePersonagem;
	private: System::Windows::Forms::DataGridViewTextBoxColumn^  nomeCenario;
private: System::Windows::Forms::Timer^  timer;

	private: System::Windows::Forms::TabPage^  tabLog;
	private: System::Windows::Forms::ListBox^  logBox;
	private: System::ComponentModel::IContainer^  components;











	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle1 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle2 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataGridViewCellStyle^  dataGridViewCellStyle3 = (gcnew System::Windows::Forms::DataGridViewCellStyle());
			System::Windows::Forms::DataVisualization::Charting::ChartArea^  chartArea1 = (gcnew System::Windows::Forms::DataVisualization::Charting::ChartArea());
			System::Windows::Forms::DataVisualization::Charting::Legend^  legend1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Legend());
			System::Windows::Forms::DataVisualization::Charting::Title^  title1 = (gcnew System::Windows::Forms::DataVisualization::Charting::Title());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(frmPrincipal::typeid));
			this->abas = (gcnew System::Windows::Forms::TabControl());
			this->tabJogadoresOn = (gcnew System::Windows::Forms::TabPage());
			this->gbJogador = (gcnew System::Windows::Forms::GroupBox());
			this->txtMSG = (gcnew System::Windows::Forms::TextBox());
			this->btMandarMSG = (gcnew System::Windows::Forms::Button());
			this->btKicar = (gcnew System::Windows::Forms::Button());
			this->gbServer = (gcnew System::Windows::Forms::GroupBox());
			this->btLigarServer = (gcnew System::Windows::Forms::Button());
			this->gridJogadores = (gcnew System::Windows::Forms::DataGridView());
			this->idConexao = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nomeJogador = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nomePersonagem = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->nomeCenario = (gcnew System::Windows::Forms::DataGridViewTextBoxColumn());
			this->tabConfig = (gcnew System::Windows::Forms::TabPage());
			this->groupBox8 = (gcnew System::Windows::Forms::GroupBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->button4 = (gcnew System::Windows::Forms::Button());
			this->button3 = (gcnew System::Windows::Forms::Button());
			this->groupBox9 = (gcnew System::Windows::Forms::GroupBox());
			this->maskedTextBox6 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox5 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox4 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox3 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox2 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->maskedTextBox1 = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label18 = (gcnew System::Windows::Forms::Label());
			this->label19 = (gcnew System::Windows::Forms::Label());
			this->label20 = (gcnew System::Windows::Forms::Label());
			this->label17 = (gcnew System::Windows::Forms::Label());
			this->label16 = (gcnew System::Windows::Forms::Label());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->comboBox1 = (gcnew System::Windows::Forms::ComboBox());
			this->groupBox7 = (gcnew System::Windows::Forms::GroupBox());
			this->nCorteOferta = (gcnew System::Windows::Forms::NumericUpDown());
			this->nCorteDemanda = (gcnew System::Windows::Forms::NumericUpDown());
			this->nCorteDurabilidade = (gcnew System::Windows::Forms::NumericUpDown());
			this->btVerCoeficientes = (gcnew System::Windows::Forms::Button());
			this->nDescontoTempo = (gcnew System::Windows::Forms::DomainUpDown());
			this->nDescontoLealdade = (gcnew System::Windows::Forms::DomainUpDown());
			this->btAplicarCoeficientes = (gcnew System::Windows::Forms::Button());
			this->label13 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->gbConfigBD = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox2 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorBkpMercado = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->labValorBkpMercado = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->btAplicarMercadoBkp = (gcnew System::Windows::Forms::Button());
			this->groupBox1 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorBkpTotal = (gcnew System::Windows::Forms::MaskedTextBox());
			this->lnovoValorBkp = (gcnew System::Windows::Forms::Label());
			this->labValorBkpTotal = (gcnew System::Windows::Forms::Label());
			this->labValorAtualBkp = (gcnew System::Windows::Forms::Label());
			this->btAplicarHorasBkp = (gcnew System::Windows::Forms::Button());
			this->gbConfigIniciais = (gcnew System::Windows::Forms::GroupBox());
			this->groupBox6 = (gcnew System::Windows::Forms::GroupBox());
			this->btConectar = (gcnew System::Windows::Forms::Button());
			this->labBD = (gcnew System::Windows::Forms::Label());
			this->txtBD = (gcnew System::Windows::Forms::TextBox());
			this->labSenha = (gcnew System::Windows::Forms::Label());
			this->txtSenha = (gcnew System::Windows::Forms::TextBox());
			this->labLogin = (gcnew System::Windows::Forms::Label());
			this->labHost = (gcnew System::Windows::Forms::Label());
			this->txtLogin = (gcnew System::Windows::Forms::TextBox());
			this->txtHost = (gcnew System::Windows::Forms::TextBox());
			this->groupBox5 = (gcnew System::Windows::Forms::GroupBox());
			this->txtToleranciaPing = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->labValorToleranciaPing = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->btAplicarToleranciaPing = (gcnew System::Windows::Forms::Button());
			this->groupBox4 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorVerPing = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->labValorVerPing = (gcnew System::Windows::Forms::Label());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->btAplicarIntervaloPing = (gcnew System::Windows::Forms::Button());
			this->groupBox3 = (gcnew System::Windows::Forms::GroupBox());
			this->txtValorFPS = (gcnew System::Windows::Forms::MaskedTextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->labValorFPS = (gcnew System::Windows::Forms::Label());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->btAplicarFPS = (gcnew System::Windows::Forms::Button());
			this->tabLog = (gcnew System::Windows::Forms::TabPage());
			this->logBox = (gcnew System::Windows::Forms::ListBox());
			this->tabMercado = (gcnew System::Windows::Forms::TabPage());
			this->gbDadosIniciais = (gcnew System::Windows::Forms::GroupBox());
			this->lbPeriodoFinal = (gcnew System::Windows::Forms::Label());
			this->lbPeriodoInicial = (gcnew System::Windows::Forms::Label());
			this->lbVendedores = (gcnew System::Windows::Forms::Label());
			this->cbVendedor = (gcnew System::Windows::Forms::ComboBox());
			this->dtPeriodoInicial = (gcnew System::Windows::Forms::DateTimePicker());
			this->dtPeriodoFinal = (gcnew System::Windows::Forms::DateTimePicker());
			this->btGeraGrafico = (gcnew System::Windows::Forms::Button());
			this->graficoCapital = (gcnew System::Windows::Forms::DataVisualization::Charting::Chart());
			this->sa = (gcnew System::Windows::Forms::StatusStrip());
			this->barStatusJogo = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barStatusBD = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barNumJogadores = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barHora = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barFPS = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barTempoAtualizacao = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->arquivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timer = (gcnew System::Windows::Forms::Timer(this->components));
			this->abas->SuspendLayout();
			this->tabJogadoresOn->SuspendLayout();
			this->gbJogador->SuspendLayout();
			this->gbServer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridJogadores))->BeginInit();
			this->tabConfig->SuspendLayout();
			this->groupBox8->SuspendLayout();
			this->groupBox9->SuspendLayout();
			this->groupBox7->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nCorteOferta))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nCorteDemanda))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nCorteDurabilidade))->BeginInit();
			this->gbConfigBD->SuspendLayout();
			this->groupBox2->SuspendLayout();
			this->groupBox1->SuspendLayout();
			this->gbConfigIniciais->SuspendLayout();
			this->groupBox6->SuspendLayout();
			this->groupBox5->SuspendLayout();
			this->groupBox4->SuspendLayout();
			this->groupBox3->SuspendLayout();
			this->tabLog->SuspendLayout();
			this->tabMercado->SuspendLayout();
			this->gbDadosIniciais->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graficoCapital))->BeginInit();
			this->sa->SuspendLayout();
			this->menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// abas
			// 
			this->abas->Controls->Add(this->tabJogadoresOn);
			this->abas->Controls->Add(this->tabConfig);
			this->abas->Controls->Add(this->tabLog);
			this->abas->Controls->Add(this->tabMercado);
			this->abas->Location = System::Drawing::Point(2, 27);
			this->abas->Name = L"abas";
			this->abas->SelectedIndex = 0;
			this->abas->Size = System::Drawing::Size(774, 449);
			this->abas->TabIndex = 0;
			// 
			// tabJogadoresOn
			// 
			this->tabJogadoresOn->Controls->Add(this->gbJogador);
			this->tabJogadoresOn->Controls->Add(this->gbServer);
			this->tabJogadoresOn->Controls->Add(this->gridJogadores);
			this->tabJogadoresOn->Location = System::Drawing::Point(4, 22);
			this->tabJogadoresOn->Name = L"tabJogadoresOn";
			this->tabJogadoresOn->Padding = System::Windows::Forms::Padding(3);
			this->tabJogadoresOn->Size = System::Drawing::Size(766, 423);
			this->tabJogadoresOn->TabIndex = 0;
			this->tabJogadoresOn->Text = L"Jogadores On-Line";
			this->tabJogadoresOn->UseVisualStyleBackColor = true;
			// 
			// gbJogador
			// 
			this->gbJogador->Controls->Add(this->txtMSG);
			this->gbJogador->Controls->Add(this->btMandarMSG);
			this->gbJogador->Controls->Add(this->btKicar);
			this->gbJogador->Location = System::Drawing::Point(644, 99);
			this->gbJogador->Name = L"gbJogador";
			this->gbJogador->Size = System::Drawing::Size(115, 231);
			this->gbJogador->TabIndex = 8;
			this->gbJogador->TabStop = false;
			this->gbJogador->Text = L" Jogador Selecionado";
			// 
			// txtMSG
			// 
			this->txtMSG->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtMSG->Location = System::Drawing::Point(6, 79);
			this->txtMSG->MaxLength = 255;
			this->txtMSG->Multiline = true;
			this->txtMSG->Name = L"txtMSG";
			this->txtMSG->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtMSG->Size = System::Drawing::Size(103, 91);
			this->txtMSG->TabIndex = 5;
			// 
			// btMandarMSG
			// 
			this->btMandarMSG->Location = System::Drawing::Point(6, 176);
			this->btMandarMSG->Name = L"btMandarMSG";
			this->btMandarMSG->Size = System::Drawing::Size(103, 23);
			this->btMandarMSG->TabIndex = 4;
			this->btMandarMSG->Text = L"Mandar MSG";
			this->btMandarMSG->UseVisualStyleBackColor = true;
			// 
			// btKicar
			// 
			this->btKicar->Location = System::Drawing::Point(6, 38);
			this->btKicar->Name = L"btKicar";
			this->btKicar->Size = System::Drawing::Size(103, 23);
			this->btKicar->TabIndex = 3;
			this->btKicar->Text = L"Kicar";
			this->btKicar->UseVisualStyleBackColor = true;
			this->btKicar->Click += gcnew System::EventHandler(this, &frmPrincipal::btKicar_Click);
			// 
			// gbServer
			// 
			this->gbServer->Controls->Add(this->btLigarServer);
			this->gbServer->Location = System::Drawing::Point(644, 6);
			this->gbServer->Name = L"gbServer";
			this->gbServer->Size = System::Drawing::Size(115, 64);
			this->gbServer->TabIndex = 7;
			this->gbServer->TabStop = false;
			this->gbServer->Text = L" Server ";
			// 
			// btLigarServer
			// 
			this->btLigarServer->Location = System::Drawing::Point(6, 29);
			this->btLigarServer->Name = L"btLigarServer";
			this->btLigarServer->Size = System::Drawing::Size(103, 23);
			this->btLigarServer->TabIndex = 3;
			this->btLigarServer->Text = L"Ligar";
			this->btLigarServer->UseVisualStyleBackColor = true;
			this->btLigarServer->Click += gcnew System::EventHandler(this, &frmPrincipal::btLigarServer_Click);
			// 
			// gridJogadores
			// 
			this->gridJogadores->AllowUserToAddRows = false;
			this->gridJogadores->AllowUserToDeleteRows = false;
			dataGridViewCellStyle1->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle1->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle1->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle1->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle1->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle1->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridJogadores->ColumnHeadersDefaultCellStyle = dataGridViewCellStyle1;
			this->gridJogadores->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridJogadores->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->idConexao, 
				this->nomeJogador, this->nomePersonagem, this->nomeCenario});
			dataGridViewCellStyle2->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle2->BackColor = System::Drawing::SystemColors::Window;
			dataGridViewCellStyle2->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle2->ForeColor = System::Drawing::SystemColors::ControlText;
			dataGridViewCellStyle2->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle2->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle2->WrapMode = System::Windows::Forms::DataGridViewTriState::False;
			this->gridJogadores->DefaultCellStyle = dataGridViewCellStyle2;
			this->gridJogadores->Location = System::Drawing::Point(3, 6);
			this->gridJogadores->Name = L"gridJogadores";
			this->gridJogadores->ReadOnly = true;
			dataGridViewCellStyle3->Alignment = System::Windows::Forms::DataGridViewContentAlignment::MiddleLeft;
			dataGridViewCellStyle3->BackColor = System::Drawing::SystemColors::Control;
			dataGridViewCellStyle3->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 8.25F, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, static_cast<System::Byte>(0)));
			dataGridViewCellStyle3->ForeColor = System::Drawing::SystemColors::WindowText;
			dataGridViewCellStyle3->SelectionBackColor = System::Drawing::SystemColors::Highlight;
			dataGridViewCellStyle3->SelectionForeColor = System::Drawing::SystemColors::HighlightText;
			dataGridViewCellStyle3->WrapMode = System::Windows::Forms::DataGridViewTriState::True;
			this->gridJogadores->RowHeadersDefaultCellStyle = dataGridViewCellStyle3;
			this->gridJogadores->SelectionMode = System::Windows::Forms::DataGridViewSelectionMode::FullRowSelect;
			this->gridJogadores->Size = System::Drawing::Size(637, 414);
			this->gridJogadores->TabIndex = 0;
			this->gridJogadores->CellContentClick += gcnew System::Windows::Forms::DataGridViewCellEventHandler(this, &frmPrincipal::gridJogadores_CellContentClick);
			// 
			// idConexao
			// 
			this->idConexao->HeaderText = L"IDConexao";
			this->idConexao->Name = L"idConexao";
			this->idConexao->ReadOnly = true;
			this->idConexao->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->idConexao->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->idConexao->Width = 70;
			// 
			// nomeJogador
			// 
			this->nomeJogador->HeaderText = L"Nome do Jogador";
			this->nomeJogador->Name = L"nomeJogador";
			this->nomeJogador->ReadOnly = true;
			this->nomeJogador->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nomeJogador->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->nomeJogador->Width = 150;
			// 
			// nomePersonagem
			// 
			this->nomePersonagem->HeaderText = L"Nome Personagem";
			this->nomePersonagem->Name = L"nomePersonagem";
			this->nomePersonagem->ReadOnly = true;
			this->nomePersonagem->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nomePersonagem->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->nomePersonagem->Width = 150;
			// 
			// nomeCenario
			// 
			this->nomeCenario->HeaderText = L"Cenário";
			this->nomeCenario->Name = L"nomeCenario";
			this->nomeCenario->ReadOnly = true;
			this->nomeCenario->Resizable = System::Windows::Forms::DataGridViewTriState::False;
			this->nomeCenario->SortMode = System::Windows::Forms::DataGridViewColumnSortMode::NotSortable;
			this->nomeCenario->Width = 150;
			// 
			// tabConfig
			// 
			this->tabConfig->Controls->Add(this->groupBox8);
			this->tabConfig->Controls->Add(this->groupBox7);
			this->tabConfig->Controls->Add(this->gbConfigBD);
			this->tabConfig->Controls->Add(this->gbConfigIniciais);
			this->tabConfig->Location = System::Drawing::Point(4, 22);
			this->tabConfig->Name = L"tabConfig";
			this->tabConfig->Padding = System::Windows::Forms::Padding(3);
			this->tabConfig->Size = System::Drawing::Size(766, 423);
			this->tabConfig->TabIndex = 3;
			this->tabConfig->Text = L"Configuração Server";
			this->tabConfig->UseVisualStyleBackColor = true;
			// 
			// groupBox8
			// 
			this->groupBox8->Controls->Add(this->label14);
			this->groupBox8->Controls->Add(this->button4);
			this->groupBox8->Controls->Add(this->button3);
			this->groupBox8->Controls->Add(this->groupBox9);
			this->groupBox8->Controls->Add(this->comboBox1);
			this->groupBox8->Location = System::Drawing::Point(3, 320);
			this->groupBox8->Name = L"groupBox8";
			this->groupBox8->Size = System::Drawing::Size(749, 97);
			this->groupBox8->TabIndex = 3;
			this->groupBox8->TabStop = false;
			this->groupBox8->Text = L" Configurações de Meta dos Vendedores ";
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(5, 30);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(59, 13);
			this->label14->TabIndex = 24;
			this->label14->Text = L"Vendedor: ";
			// 
			// button4
			// 
			this->button4->Location = System::Drawing::Point(633, 60);
			this->button4->Name = L"button4";
			this->button4->Size = System::Drawing::Size(110, 31);
			this->button4->TabIndex = 23;
			this->button4->Text = L"Aplicar";
			this->button4->UseVisualStyleBackColor = true;
			// 
			// button3
			// 
			this->button3->Location = System::Drawing::Point(633, 15);
			this->button3->Name = L"button3";
			this->button3->Size = System::Drawing::Size(110, 39);
			this->button3->TabIndex = 22;
			this->button3->Text = L"Visualizar valores atuais";
			this->button3->UseVisualStyleBackColor = true;
			// 
			// groupBox9
			// 
			this->groupBox9->Controls->Add(this->maskedTextBox6);
			this->groupBox9->Controls->Add(this->maskedTextBox5);
			this->groupBox9->Controls->Add(this->maskedTextBox4);
			this->groupBox9->Controls->Add(this->maskedTextBox3);
			this->groupBox9->Controls->Add(this->maskedTextBox2);
			this->groupBox9->Controls->Add(this->maskedTextBox1);
			this->groupBox9->Controls->Add(this->label18);
			this->groupBox9->Controls->Add(this->label19);
			this->groupBox9->Controls->Add(this->label20);
			this->groupBox9->Controls->Add(this->label17);
			this->groupBox9->Controls->Add(this->label16);
			this->groupBox9->Controls->Add(this->label15);
			this->groupBox9->Location = System::Drawing::Point(201, 8);
			this->groupBox9->Name = L"groupBox9";
			this->groupBox9->Size = System::Drawing::Size(426, 85);
			this->groupBox9->TabIndex = 21;
			this->groupBox9->TabStop = false;
			this->groupBox9->Text = L" Meta de Capital ";
			// 
			// maskedTextBox6
			// 
			this->maskedTextBox6->Location = System::Drawing::Point(346, 58);
			this->maskedTextBox6->Mask = L"000000000";
			this->maskedTextBox6->Name = L"maskedTextBox6";
			this->maskedTextBox6->PromptChar = '0';
			this->maskedTextBox6->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox6->TabIndex = 32;
			// 
			// maskedTextBox5
			// 
			this->maskedTextBox5->Location = System::Drawing::Point(346, 36);
			this->maskedTextBox5->Mask = L"000000000";
			this->maskedTextBox5->Name = L"maskedTextBox5";
			this->maskedTextBox5->PromptChar = '0';
			this->maskedTextBox5->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox5->TabIndex = 31;
			// 
			// maskedTextBox4
			// 
			this->maskedTextBox4->Location = System::Drawing::Point(346, 14);
			this->maskedTextBox4->Mask = L"000000000";
			this->maskedTextBox4->Name = L"maskedTextBox4";
			this->maskedTextBox4->PromptChar = '0';
			this->maskedTextBox4->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox4->TabIndex = 30;
			// 
			// maskedTextBox3
			// 
			this->maskedTextBox3->Location = System::Drawing::Point(120, 59);
			this->maskedTextBox3->Mask = L"000000000";
			this->maskedTextBox3->Name = L"maskedTextBox3";
			this->maskedTextBox3->PromptChar = '0';
			this->maskedTextBox3->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox3->TabIndex = 29;
			// 
			// maskedTextBox2
			// 
			this->maskedTextBox2->Location = System::Drawing::Point(120, 36);
			this->maskedTextBox2->Mask = L"000000000";
			this->maskedTextBox2->Name = L"maskedTextBox2";
			this->maskedTextBox2->PromptChar = '0';
			this->maskedTextBox2->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox2->TabIndex = 28;
			// 
			// maskedTextBox1
			// 
			this->maskedTextBox1->Location = System::Drawing::Point(120, 13);
			this->maskedTextBox1->Mask = L"000000000";
			this->maskedTextBox1->Name = L"maskedTextBox1";
			this->maskedTextBox1->PromptChar = '0';
			this->maskedTextBox1->Size = System::Drawing::Size(66, 20);
			this->maskedTextBox1->TabIndex = 27;
			// 
			// label18
			// 
			this->label18->AutoSize = true;
			this->label18->Location = System::Drawing::Point(250, 61);
			this->label18->Name = L"label18";
			this->label18->Size = System::Drawing::Size(90, 13);
			this->label18->TabIndex = 26;
			this->label18->Text = L"Samara (Vespas):";
			// 
			// label19
			// 
			this->label19->AutoSize = true;
			this->label19->Location = System::Drawing::Point(194, 39);
			this->label19->Name = L"label19";
			this->label19->Size = System::Drawing::Size(146, 13);
			this->label19->TabIndex = 25;
			this->label19->Text = L"Resplandora (Louva-a-Deus):";
			// 
			// label20
			// 
			this->label20->AutoSize = true;
			this->label20->Location = System::Drawing::Point(227, 17);
			this->label20->Name = L"label20";
			this->label20->Size = System::Drawing::Size(113, 13);
			this->label20->TabIndex = 24;
			this->label20->Text = L"Abgrundi (Escorpiões):";
			// 
			// label17
			// 
			this->label17->AutoSize = true;
			this->label17->Location = System::Drawing::Point(11, 62);
			this->label17->Name = L"label17";
			this->label17->Size = System::Drawing::Size(103, 13);
			this->label17->TabIndex = 23;
			this->label17->Text = L"Mabi-log (Besouros):";
			// 
			// label16
			// 
			this->label16->AutoSize = true;
			this->label16->Location = System::Drawing::Point(8, 39);
			this->label16->Name = L"label16";
			this->label16->Size = System::Drawing::Size(106, 13);
			this->label16->TabIndex = 22;
			this->label16->Text = L"Typhoona (Aranhas):";
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(25, 17);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(89, 13);
			this->label15->TabIndex = 21;
			this->label15->Text = L"Oblivion (Neutra):";
			// 
			// comboBox1
			// 
			this->comboBox1->FormattingEnabled = true;
			this->comboBox1->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Tzorerr LiQenot(Aranha)", L"Taco(Besouro)", L"Zeravin(Escorpião)", 
				L"Ding Ding(Louva-a-Deus)", L"(Vespa)"});
			this->comboBox1->Location = System::Drawing::Point(8, 47);
			this->comboBox1->MaxDropDownItems = 5;
			this->comboBox1->Name = L"comboBox1";
			this->comboBox1->Size = System::Drawing::Size(187, 21);
			this->comboBox1->TabIndex = 13;
			// 
			// groupBox7
			// 
			this->groupBox7->Controls->Add(this->nCorteOferta);
			this->groupBox7->Controls->Add(this->nCorteDemanda);
			this->groupBox7->Controls->Add(this->nCorteDurabilidade);
			this->groupBox7->Controls->Add(this->btVerCoeficientes);
			this->groupBox7->Controls->Add(this->nDescontoTempo);
			this->groupBox7->Controls->Add(this->nDescontoLealdade);
			this->groupBox7->Controls->Add(this->btAplicarCoeficientes);
			this->groupBox7->Controls->Add(this->label13);
			this->groupBox7->Controls->Add(this->label11);
			this->groupBox7->Controls->Add(this->label7);
			this->groupBox7->Controls->Add(this->label5);
			this->groupBox7->Controls->Add(this->label3);
			this->groupBox7->Location = System::Drawing::Point(352, 131);
			this->groupBox7->Name = L"groupBox7";
			this->groupBox7->Size = System::Drawing::Size(406, 183);
			this->groupBox7->TabIndex = 2;
			this->groupBox7->TabStop = false;
			this->groupBox7->Text = L" Configurações do Mercado ";
			// 
			// nCorteOferta
			// 
			this->nCorteOferta->Location = System::Drawing::Point(163, 85);
			this->nCorteOferta->Name = L"nCorteOferta";
			this->nCorteOferta->Size = System::Drawing::Size(49, 20);
			this->nCorteOferta->TabIndex = 14;
			this->nCorteOferta->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			// 
			// nCorteDemanda
			// 
			this->nCorteDemanda->Location = System::Drawing::Point(163, 59);
			this->nCorteDemanda->Name = L"nCorteDemanda";
			this->nCorteDemanda->Size = System::Drawing::Size(49, 20);
			this->nCorteDemanda->TabIndex = 13;
			this->nCorteDemanda->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			// 
			// nCorteDurabilidade
			// 
			this->nCorteDurabilidade->Location = System::Drawing::Point(163, 33);
			this->nCorteDurabilidade->Name = L"nCorteDurabilidade";
			this->nCorteDurabilidade->Size = System::Drawing::Size(49, 20);
			this->nCorteDurabilidade->TabIndex = 12;
			this->nCorteDurabilidade->Value = System::Decimal(gcnew cli::array< System::Int32 >(4) {50, 0, 0, 0});
			// 
			// btVerCoeficientes
			// 
			this->btVerCoeficientes->Location = System::Drawing::Point(236, 33);
			this->btVerCoeficientes->Name = L"btVerCoeficientes";
			this->btVerCoeficientes->Size = System::Drawing::Size(149, 72);
			this->btVerCoeficientes->TabIndex = 11;
			this->btVerCoeficientes->Text = L"Visualizar valores atuais";
			this->btVerCoeficientes->UseVisualStyleBackColor = true;
			this->btVerCoeficientes->Click += gcnew System::EventHandler(this, &frmPrincipal::btVerCoeficientes_Click);
			// 
			// nDescontoTempo
			// 
			this->nDescontoTempo->Items->Add(L"0%");
			this->nDescontoTempo->Items->Add(L"1%");
			this->nDescontoTempo->Items->Add(L"2%");
			this->nDescontoTempo->Items->Add(L"3%");
			this->nDescontoTempo->Items->Add(L"4%");
			this->nDescontoTempo->Location = System::Drawing::Point(163, 141);
			this->nDescontoTempo->Name = L"nDescontoTempo";
			this->nDescontoTempo->Size = System::Drawing::Size(49, 20);
			this->nDescontoTempo->TabIndex = 10;
			this->nDescontoTempo->Text = L"4%";
			// 
			// nDescontoLealdade
			// 
			this->nDescontoLealdade->Items->Add(L"0%");
			this->nDescontoLealdade->Items->Add(L"1%");
			this->nDescontoLealdade->Items->Add(L"2%");
			this->nDescontoLealdade->Items->Add(L"3%");
			this->nDescontoLealdade->Items->Add(L"4%");
			this->nDescontoLealdade->Items->Add(L"5%");
			this->nDescontoLealdade->Items->Add(L"6%");
			this->nDescontoLealdade->Items->Add(L"7%");
			this->nDescontoLealdade->Items->Add(L"8%");
			this->nDescontoLealdade->Items->Add(L"9%");
			this->nDescontoLealdade->Items->Add(L"10%");
			this->nDescontoLealdade->Location = System::Drawing::Point(163, 114);
			this->nDescontoLealdade->Name = L"nDescontoLealdade";
			this->nDescontoLealdade->Size = System::Drawing::Size(49, 20);
			this->nDescontoLealdade->TabIndex = 9;
			this->nDescontoLealdade->Text = L"10%";
			// 
			// btAplicarCoeficientes
			// 
			this->btAplicarCoeficientes->Location = System::Drawing::Point(236, 114);
			this->btAplicarCoeficientes->Name = L"btAplicarCoeficientes";
			this->btAplicarCoeficientes->Size = System::Drawing::Size(149, 47);
			this->btAplicarCoeficientes->TabIndex = 5;
			this->btAplicarCoeficientes->Text = L"Aplicar";
			this->btAplicarCoeficientes->UseVisualStyleBackColor = true;
			this->btAplicarCoeficientes->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarCoeficientes_Click);
			// 
			// label13
			// 
			this->label13->AutoSize = true;
			this->label13->Location = System::Drawing::Point(18, 142);
			this->label13->Name = L"label13";
			this->label13->Size = System::Drawing::Size(139, 13);
			this->label13->TabIndex = 4;
			this->label13->Text = L"Kt (desconto tempo inativo):";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(42, 116);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(115, 13);
			this->label11->TabIndex = 3;
			this->label11->Text = L"Kl (desconto lealdade):";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(55, 87);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(101, 13);
			this->label7->TabIndex = 2;
			this->label7->Text = L"Ko (corte de oferta):";
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(38, 61);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(118, 13);
			this->label5->TabIndex = 1;
			this->label5->Text = L"Kd (corte de demanda):";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(29, 35);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(128, 13);
			this->label3->TabIndex = 0;
			this->label3->Text = L"Kr (corte de durabilidade):";
			// 
			// gbConfigBD
			// 
			this->gbConfigBD->Controls->Add(this->groupBox2);
			this->gbConfigBD->Controls->Add(this->groupBox1);
			this->gbConfigBD->Location = System::Drawing::Point(352, 6);
			this->gbConfigBD->Name = L"gbConfigBD";
			this->gbConfigBD->Size = System::Drawing::Size(406, 119);
			this->gbConfigBD->TabIndex = 1;
			this->gbConfigBD->TabStop = false;
			this->gbConfigBD->Text = L" Configurações de Saves ";
			this->gbConfigBD->UseCompatibleTextRendering = true;
			// 
			// groupBox2
			// 
			this->groupBox2->Controls->Add(this->txtValorBkpMercado);
			this->groupBox2->Controls->Add(this->label2);
			this->groupBox2->Controls->Add(this->labValorBkpMercado);
			this->groupBox2->Controls->Add(this->label4);
			this->groupBox2->Controls->Add(this->btAplicarMercadoBkp);
			this->groupBox2->Location = System::Drawing::Point(6, 68);
			this->groupBox2->Name = L"groupBox2";
			this->groupBox2->Size = System::Drawing::Size(394, 43);
			this->groupBox2->TabIndex = 7;
			this->groupBox2->TabStop = false;
			this->groupBox2->Text = L" Tempo de Backup de Mercado ";
			// 
			// txtValorBkpMercado
			// 
			this->txtValorBkpMercado->Location = System::Drawing::Point(265, 17);
			this->txtValorBkpMercado->Mask = L"00";
			this->txtValorBkpMercado->Name = L"txtValorBkpMercado";
			this->txtValorBkpMercado->Size = System::Drawing::Size(32, 20);
			this->txtValorBkpMercado->TabIndex = 15;
			this->txtValorBkpMercado->Text = L"00";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(193, 20);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(66, 13);
			this->label2->TabIndex = 10;
			this->label2->Text = L"Novo Valor: ";
			// 
			// labValorBkpMercado
			// 
			this->labValorBkpMercado->AutoSize = true;
			this->labValorBkpMercado->Location = System::Drawing::Point(133, 20);
			this->labValorBkpMercado->Name = L"labValorBkpMercado";
			this->labValorBkpMercado->Size = System::Drawing::Size(16, 13);
			this->labValorBkpMercado->TabIndex = 9;
			this->labValorBkpMercado->Text = L"0 ";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(17, 20);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(110, 13);
			this->label4->TabIndex = 8;
			this->label4->Text = L"Valor Atual (Minutos): ";
			// 
			// btAplicarMercadoBkp
			// 
			this->btAplicarMercadoBkp->Location = System::Drawing::Point(303, 17);
			this->btAplicarMercadoBkp->Name = L"btAplicarMercadoBkp";
			this->btAplicarMercadoBkp->Size = System::Drawing::Size(76, 20);
			this->btAplicarMercadoBkp->TabIndex = 7;
			this->btAplicarMercadoBkp->Text = L"Aplicar";
			this->btAplicarMercadoBkp->UseVisualStyleBackColor = true;
			this->btAplicarMercadoBkp->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarMercadoBkp_Click);
			// 
			// groupBox1
			// 
			this->groupBox1->Controls->Add(this->txtValorBkpTotal);
			this->groupBox1->Controls->Add(this->lnovoValorBkp);
			this->groupBox1->Controls->Add(this->labValorBkpTotal);
			this->groupBox1->Controls->Add(this->labValorAtualBkp);
			this->groupBox1->Controls->Add(this->btAplicarHorasBkp);
			this->groupBox1->Location = System::Drawing::Point(6, 19);
			this->groupBox1->Name = L"groupBox1";
			this->groupBox1->Size = System::Drawing::Size(394, 43);
			this->groupBox1->TabIndex = 6;
			this->groupBox1->TabStop = false;
			this->groupBox1->Text = L" Tempo de Backup Total  ";
			// 
			// txtValorBkpTotal
			// 
			this->txtValorBkpTotal->Location = System::Drawing::Point(265, 16);
			this->txtValorBkpTotal->Mask = L"00";
			this->txtValorBkpTotal->Name = L"txtValorBkpTotal";
			this->txtValorBkpTotal->Size = System::Drawing::Size(32, 20);
			this->txtValorBkpTotal->TabIndex = 14;
			this->txtValorBkpTotal->Text = L"00";
			// 
			// lnovoValorBkp
			// 
			this->lnovoValorBkp->AutoSize = true;
			this->lnovoValorBkp->Location = System::Drawing::Point(193, 20);
			this->lnovoValorBkp->Name = L"lnovoValorBkp";
			this->lnovoValorBkp->Size = System::Drawing::Size(66, 13);
			this->lnovoValorBkp->TabIndex = 10;
			this->lnovoValorBkp->Text = L"Novo Valor: ";
			// 
			// labValorBkpTotal
			// 
			this->labValorBkpTotal->AutoSize = true;
			this->labValorBkpTotal->Location = System::Drawing::Point(121, 20);
			this->labValorBkpTotal->Name = L"labValorBkpTotal";
			this->labValorBkpTotal->Size = System::Drawing::Size(16, 13);
			this->labValorBkpTotal->TabIndex = 9;
			this->labValorBkpTotal->Text = L"0 ";
			// 
			// labValorAtualBkp
			// 
			this->labValorAtualBkp->AutoSize = true;
			this->labValorAtualBkp->Location = System::Drawing::Point(17, 20);
			this->labValorAtualBkp->Name = L"labValorAtualBkp";
			this->labValorAtualBkp->Size = System::Drawing::Size(101, 13);
			this->labValorAtualBkp->TabIndex = 8;
			this->labValorAtualBkp->Text = L"Valor Atual (Horas): ";
			// 
			// btAplicarHorasBkp
			// 
			this->btAplicarHorasBkp->Location = System::Drawing::Point(303, 15);
			this->btAplicarHorasBkp->Name = L"btAplicarHorasBkp";
			this->btAplicarHorasBkp->Size = System::Drawing::Size(76, 20);
			this->btAplicarHorasBkp->TabIndex = 7;
			this->btAplicarHorasBkp->Text = L"Aplicar";
			this->btAplicarHorasBkp->UseVisualStyleBackColor = true;
			this->btAplicarHorasBkp->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarHorasBkp_Click);
			// 
			// gbConfigIniciais
			// 
			this->gbConfigIniciais->Controls->Add(this->groupBox6);
			this->gbConfigIniciais->Controls->Add(this->groupBox5);
			this->gbConfigIniciais->Controls->Add(this->groupBox4);
			this->gbConfigIniciais->Controls->Add(this->groupBox3);
			this->gbConfigIniciais->Location = System::Drawing::Point(3, 6);
			this->gbConfigIniciais->Name = L"gbConfigIniciais";
			this->gbConfigIniciais->Size = System::Drawing::Size(343, 308);
			this->gbConfigIniciais->TabIndex = 0;
			this->gbConfigIniciais->TabStop = false;
			this->gbConfigIniciais->Text = L" Configurações Iniciais ";
			// 
			// groupBox6
			// 
			this->groupBox6->Controls->Add(this->btConectar);
			this->groupBox6->Controls->Add(this->labBD);
			this->groupBox6->Controls->Add(this->txtBD);
			this->groupBox6->Controls->Add(this->labSenha);
			this->groupBox6->Controls->Add(this->txtSenha);
			this->groupBox6->Controls->Add(this->labLogin);
			this->groupBox6->Controls->Add(this->labHost);
			this->groupBox6->Controls->Add(this->txtLogin);
			this->groupBox6->Controls->Add(this->txtHost);
			this->groupBox6->Location = System::Drawing::Point(6, 170);
			this->groupBox6->Name = L"groupBox6";
			this->groupBox6->Size = System::Drawing::Size(331, 130);
			this->groupBox6->TabIndex = 15;
			this->groupBox6->TabStop = false;
			this->groupBox6->Text = L" Conexão com o Banco de Dados ";
			// 
			// btConectar
			// 
			this->btConectar->Location = System::Drawing::Point(13, 102);
			this->btConectar->Name = L"btConectar";
			this->btConectar->Size = System::Drawing::Size(309, 22);
			this->btConectar->TabIndex = 20;
			this->btConectar->Text = L"Conectar";
			this->btConectar->UseVisualStyleBackColor = true;
			// 
			// labBD
			// 
			this->labBD->AutoSize = true;
			this->labBD->Location = System::Drawing::Point(181, 60);
			this->labBD->Name = L"labBD";
			this->labBD->Size = System::Drawing::Size(126, 13);
			this->labBD->TabIndex = 19;
			this->labBD->Text = L"Nome da Base de Dados";
			// 
			// txtBD
			// 
			this->txtBD->Location = System::Drawing::Point(184, 76);
			this->txtBD->Name = L"txtBD";
			this->txtBD->Size = System::Drawing::Size(138, 20);
			this->txtBD->TabIndex = 18;
			// 
			// labSenha
			// 
			this->labSenha->AutoSize = true;
			this->labSenha->Location = System::Drawing::Point(181, 19);
			this->labSenha->Name = L"labSenha";
			this->labSenha->Size = System::Drawing::Size(38, 13);
			this->labSenha->TabIndex = 15;
			this->labSenha->Text = L"Senha";
			// 
			// txtSenha
			// 
			this->txtSenha->Location = System::Drawing::Point(184, 35);
			this->txtSenha->Name = L"txtSenha";
			this->txtSenha->PasswordChar = '?';
			this->txtSenha->Size = System::Drawing::Size(138, 20);
			this->txtSenha->TabIndex = 14;
			// 
			// labLogin
			// 
			this->labLogin->AutoSize = true;
			this->labLogin->Location = System::Drawing::Point(10, 19);
			this->labLogin->Name = L"labLogin";
			this->labLogin->Size = System::Drawing::Size(33, 13);
			this->labLogin->TabIndex = 13;
			this->labLogin->Text = L"Login";
			// 
			// labHost
			// 
			this->labHost->AutoSize = true;
			this->labHost->Location = System::Drawing::Point(10, 60);
			this->labHost->Name = L"labHost";
			this->labHost->Size = System::Drawing::Size(29, 13);
			this->labHost->TabIndex = 15;
			this->labHost->Text = L"Host";
			// 
			// txtLogin
			// 
			this->txtLogin->Location = System::Drawing::Point(13, 35);
			this->txtLogin->Name = L"txtLogin";
			this->txtLogin->Size = System::Drawing::Size(165, 20);
			this->txtLogin->TabIndex = 12;
			// 
			// txtHost
			// 
			this->txtHost->Location = System::Drawing::Point(13, 76);
			this->txtHost->Name = L"txtHost";
			this->txtHost->Size = System::Drawing::Size(165, 20);
			this->txtHost->TabIndex = 14;
			// 
			// groupBox5
			// 
			this->groupBox5->Controls->Add(this->txtToleranciaPing);
			this->groupBox5->Controls->Add(this->label10);
			this->groupBox5->Controls->Add(this->labValorToleranciaPing);
			this->groupBox5->Controls->Add(this->label12);
			this->groupBox5->Controls->Add(this->btAplicarToleranciaPing);
			this->groupBox5->Location = System::Drawing::Point(6, 117);
			this->groupBox5->Name = L"groupBox5";
			this->groupBox5->Size = System::Drawing::Size(331, 47);
			this->groupBox5->TabIndex = 14;
			this->groupBox5->TabStop = false;
			this->groupBox5->Text = L" Valor de Tolerância de Ping ";
			// 
			// txtToleranciaPing
			// 
			this->txtToleranciaPing->Location = System::Drawing::Point(240, 19);
			this->txtToleranciaPing->Mask = L"000";
			this->txtToleranciaPing->Name = L"txtToleranciaPing";
			this->txtToleranciaPing->Size = System::Drawing::Size(28, 20);
			this->txtToleranciaPing->TabIndex = 13;
			this->txtToleranciaPing->Text = L"005";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(172, 23);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(66, 13);
			this->label10->TabIndex = 10;
			this->label10->Text = L"Novo Valor: ";
			// 
			// labValorToleranciaPing
			// 
			this->labValorToleranciaPing->AutoSize = true;
			this->labValorToleranciaPing->Location = System::Drawing::Point(138, 23);
			this->labValorToleranciaPing->Name = L"labValorToleranciaPing";
			this->labValorToleranciaPing->Size = System::Drawing::Size(16, 13);
			this->labValorToleranciaPing->TabIndex = 9;
			this->labValorToleranciaPing->Text = L"0 ";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(11, 23);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(121, 13);
			this->label12->TabIndex = 8;
			this->label12->Text = L"Valor Atual (Segundos): ";
			// 
			// btAplicarToleranciaPing
			// 
			this->btAplicarToleranciaPing->Location = System::Drawing::Point(274, 19);
			this->btAplicarToleranciaPing->Name = L"btAplicarToleranciaPing";
			this->btAplicarToleranciaPing->Size = System::Drawing::Size(49, 20);
			this->btAplicarToleranciaPing->TabIndex = 7;
			this->btAplicarToleranciaPing->Text = L"Aplicar";
			this->btAplicarToleranciaPing->UseVisualStyleBackColor = true;
			this->btAplicarToleranciaPing->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarToleranciaPing_Click);
			// 
			// groupBox4
			// 
			this->groupBox4->Controls->Add(this->txtValorVerPing);
			this->groupBox4->Controls->Add(this->label1);
			this->groupBox4->Controls->Add(this->labValorVerPing);
			this->groupBox4->Controls->Add(this->label9);
			this->groupBox4->Controls->Add(this->btAplicarIntervaloPing);
			this->groupBox4->Location = System::Drawing::Point(6, 68);
			this->groupBox4->Name = L"groupBox4";
			this->groupBox4->Size = System::Drawing::Size(331, 43);
			this->groupBox4->TabIndex = 13;
			this->groupBox4->TabStop = false;
			this->groupBox4->Text = L"Tempo de Verificação de Ping ";
			// 
			// txtValorVerPing
			// 
			this->txtValorVerPing->Location = System::Drawing::Point(239, 17);
			this->txtValorVerPing->Mask = L"000";
			this->txtValorVerPing->Name = L"txtValorVerPing";
			this->txtValorVerPing->Size = System::Drawing::Size(28, 20);
			this->txtValorVerPing->TabIndex = 12;
			this->txtValorVerPing->Text = L"010";
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(172, 21);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(66, 13);
			this->label1->TabIndex = 10;
			this->label1->Text = L"Novo Valor: ";
			// 
			// labValorVerPing
			// 
			this->labValorVerPing->AutoSize = true;
			this->labValorVerPing->Location = System::Drawing::Point(137, 21);
			this->labValorVerPing->Name = L"labValorVerPing";
			this->labValorVerPing->Size = System::Drawing::Size(16, 13);
			this->labValorVerPing->TabIndex = 9;
			this->labValorVerPing->Text = L"0 ";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(10, 21);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(121, 13);
			this->label9->TabIndex = 8;
			this->label9->Text = L"Valor Atual (Segundos): ";
			// 
			// btAplicarIntervaloPing
			// 
			this->btAplicarIntervaloPing->Location = System::Drawing::Point(273, 16);
			this->btAplicarIntervaloPing->Name = L"btAplicarIntervaloPing";
			this->btAplicarIntervaloPing->Size = System::Drawing::Size(49, 20);
			this->btAplicarIntervaloPing->TabIndex = 7;
			this->btAplicarIntervaloPing->Text = L"Aplicar";
			this->btAplicarIntervaloPing->UseVisualStyleBackColor = true;
			this->btAplicarIntervaloPing->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarIntervaloPing_Click);
			// 
			// groupBox3
			// 
			this->groupBox3->Controls->Add(this->txtValorFPS);
			this->groupBox3->Controls->Add(this->label6);
			this->groupBox3->Controls->Add(this->labValorFPS);
			this->groupBox3->Controls->Add(this->label8);
			this->groupBox3->Controls->Add(this->btAplicarFPS);
			this->groupBox3->Location = System::Drawing::Point(6, 19);
			this->groupBox3->Name = L"groupBox3";
			this->groupBox3->Size = System::Drawing::Size(331, 43);
			this->groupBox3->TabIndex = 12;
			this->groupBox3->TabStop = false;
			this->groupBox3->Text = L"FPS ";
			// 
			// txtValorFPS
			// 
			this->txtValorFPS->Location = System::Drawing::Point(239, 17);
			this->txtValorFPS->Mask = L"00";
			this->txtValorFPS->Name = L"txtValorFPS";
			this->txtValorFPS->Size = System::Drawing::Size(29, 20);
			this->txtValorFPS->TabIndex = 11;
			this->txtValorFPS->Text = L"30";
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(172, 20);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(66, 13);
			this->label6->TabIndex = 10;
			this->label6->Text = L"Novo Valor: ";
			// 
			// labValorFPS
			// 
			this->labValorFPS->AutoSize = true;
			this->labValorFPS->Location = System::Drawing::Point(80, 19);
			this->labValorFPS->Name = L"labValorFPS";
			this->labValorFPS->Size = System::Drawing::Size(16, 13);
			this->labValorFPS->TabIndex = 9;
			this->labValorFPS->Text = L"0 ";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(10, 19);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(64, 13);
			this->label8->TabIndex = 8;
			this->label8->Text = L"Valor Atual: ";
			// 
			// btAplicarFPS
			// 
			this->btAplicarFPS->Location = System::Drawing::Point(274, 16);
			this->btAplicarFPS->Name = L"btAplicarFPS";
			this->btAplicarFPS->Size = System::Drawing::Size(48, 20);
			this->btAplicarFPS->TabIndex = 7;
			this->btAplicarFPS->Text = L"Aplicar";
			this->btAplicarFPS->UseVisualStyleBackColor = true;
			this->btAplicarFPS->Click += gcnew System::EventHandler(this, &frmPrincipal::btAplicarFPS_Click);
			// 
			// tabLog
			// 
			this->tabLog->Controls->Add(this->logBox);
			this->tabLog->Cursor = System::Windows::Forms::Cursors::Arrow;
			this->tabLog->Location = System::Drawing::Point(4, 22);
			this->tabLog->Name = L"tabLog";
			this->tabLog->Padding = System::Windows::Forms::Padding(3);
			this->tabLog->Size = System::Drawing::Size(766, 423);
			this->tabLog->TabIndex = 2;
			this->tabLog->Text = L"Log";
			this->tabLog->UseVisualStyleBackColor = true;
			// 
			// logBox
			// 
			this->logBox->FormattingEnabled = true;
			this->logBox->Location = System::Drawing::Point(6, 10);
			this->logBox->Name = L"logBox";
			this->logBox->ScrollAlwaysVisible = true;
			this->logBox->Size = System::Drawing::Size(754, 407);
			this->logBox->TabIndex = 0;
			// 
			// tabMercado
			// 
			this->tabMercado->Controls->Add(this->gbDadosIniciais);
			this->tabMercado->Controls->Add(this->graficoCapital);
			this->tabMercado->Location = System::Drawing::Point(4, 22);
			this->tabMercado->Name = L"tabMercado";
			this->tabMercado->Padding = System::Windows::Forms::Padding(3);
			this->tabMercado->Size = System::Drawing::Size(766, 423);
			this->tabMercado->TabIndex = 4;
			this->tabMercado->Text = L"Gráfico de Mercado";
			this->tabMercado->UseVisualStyleBackColor = true;
			// 
			// gbDadosIniciais
			// 
			this->gbDadosIniciais->Controls->Add(this->lbPeriodoFinal);
			this->gbDadosIniciais->Controls->Add(this->lbPeriodoInicial);
			this->gbDadosIniciais->Controls->Add(this->lbVendedores);
			this->gbDadosIniciais->Controls->Add(this->cbVendedor);
			this->gbDadosIniciais->Controls->Add(this->dtPeriodoInicial);
			this->gbDadosIniciais->Controls->Add(this->dtPeriodoFinal);
			this->gbDadosIniciais->Controls->Add(this->btGeraGrafico);
			this->gbDadosIniciais->Location = System::Drawing::Point(6, 6);
			this->gbDadosIniciais->Name = L"gbDadosIniciais";
			this->gbDadosIniciais->Size = System::Drawing::Size(752, 51);
			this->gbDadosIniciais->TabIndex = 8;
			this->gbDadosIniciais->TabStop = false;
			this->gbDadosIniciais->Text = L" Dados Iniciais ";
			// 
			// lbPeriodoFinal
			// 
			this->lbPeriodoFinal->AutoSize = true;
			this->lbPeriodoFinal->Location = System::Drawing::Point(405, 22);
			this->lbPeriodoFinal->Name = L"lbPeriodoFinal";
			this->lbPeriodoFinal->Size = System::Drawing::Size(68, 13);
			this->lbPeriodoFinal->TabIndex = 14;
			this->lbPeriodoFinal->Text = L"Periodo Final";
			// 
			// lbPeriodoInicial
			// 
			this->lbPeriodoInicial->AutoSize = true;
			this->lbPeriodoInicial->Location = System::Drawing::Point(223, 22);
			this->lbPeriodoInicial->Name = L"lbPeriodoInicial";
			this->lbPeriodoInicial->Size = System::Drawing::Size(73, 13);
			this->lbPeriodoInicial->TabIndex = 13;
			this->lbPeriodoInicial->Text = L"Periodo Inicial";
			// 
			// lbVendedores
			// 
			this->lbVendedores->AutoSize = true;
			this->lbVendedores->Location = System::Drawing::Point(7, 22);
			this->lbVendedores->Name = L"lbVendedores";
			this->lbVendedores->Size = System::Drawing::Size(64, 13);
			this->lbVendedores->TabIndex = 12;
			this->lbVendedores->Text = L"Vendedores";
			// 
			// cbVendedor
			// 
			this->cbVendedor->FormattingEnabled = true;
			this->cbVendedor->Items->AddRange(gcnew cli::array< System::Object^  >(5) {L"Vendedor Aranha", L"Vendedor Besouro", L"Vendedor Escorpiao", 
				L"Vendedor Louva-a-Deus", L"Vendedor Vespa"});
			this->cbVendedor->Location = System::Drawing::Point(77, 19);
			this->cbVendedor->MaxDropDownItems = 5;
			this->cbVendedor->Name = L"cbVendedor";
			this->cbVendedor->Size = System::Drawing::Size(140, 21);
			this->cbVendedor->TabIndex = 11;
			// 
			// dtPeriodoInicial
			// 
			this->dtPeriodoInicial->CustomFormat = L"dd/MM/yyyy";
			this->dtPeriodoInicial->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtPeriodoInicial->Location = System::Drawing::Point(302, 18);
			this->dtPeriodoInicial->Name = L"dtPeriodoInicial";
			this->dtPeriodoInicial->Size = System::Drawing::Size(97, 20);
			this->dtPeriodoInicial->TabIndex = 10;
			// 
			// dtPeriodoFinal
			// 
			this->dtPeriodoFinal->CustomFormat = L"dd/MM/yyyy";
			this->dtPeriodoFinal->Format = System::Windows::Forms::DateTimePickerFormat::Custom;
			this->dtPeriodoFinal->Location = System::Drawing::Point(479, 18);
			this->dtPeriodoFinal->Name = L"dtPeriodoFinal";
			this->dtPeriodoFinal->Size = System::Drawing::Size(97, 20);
			this->dtPeriodoFinal->TabIndex = 9;
			// 
			// btGeraGrafico
			// 
			this->btGeraGrafico->Location = System::Drawing::Point(582, 18);
			this->btGeraGrafico->Name = L"btGeraGrafico";
			this->btGeraGrafico->Size = System::Drawing::Size(164, 20);
			this->btGeraGrafico->TabIndex = 8;
			this->btGeraGrafico->Text = L"Gerar Gráfico";
			this->btGeraGrafico->UseVisualStyleBackColor = true;
			this->btGeraGrafico->Click += gcnew System::EventHandler(this, &frmPrincipal::btGeraGrafico_Click);
			// 
			// graficoCapital
			// 
			chartArea1->AxisX->Title = L"Tempo decorrido";
			chartArea1->AxisY->MajorGrid->LineColor = System::Drawing::Color::Gainsboro;
			chartArea1->AxisY->ScrollBar->LineColor = System::Drawing::Color::Red;
			chartArea1->AxisY->Title = L"Capital (sementes) ";
			chartArea1->BorderColor = System::Drawing::Color::Gainsboro;
			chartArea1->CursorX->AxisType = System::Windows::Forms::DataVisualization::Charting::AxisType::Secondary;
			chartArea1->Name = L"ChartArea1";
			this->graficoCapital->ChartAreas->Add(chartArea1);
			legend1->Name = L"legendas";
			legend1->Title = L"Legendas";
			this->graficoCapital->Legends->Add(legend1);
			this->graficoCapital->Location = System::Drawing::Point(6, 63);
			this->graficoCapital->Name = L"graficoCapital";
			this->graficoCapital->Size = System::Drawing::Size(752, 354);
			this->graficoCapital->TabIndex = 0;
			this->graficoCapital->Text = L"Gráfico";
			title1->Font = (gcnew System::Drawing::Font(L"Arial", 9.75F, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			title1->Name = L"CapitalporTempo";
			title1->Text = L"Equilíbrio de capital utilizando precificação por meta-alvo";
			this->graficoCapital->Titles->Add(title1);
			this->graficoCapital->Click += gcnew System::EventHandler(this, &frmPrincipal::chart1_Click);
			// 
			// sa
			// 
			this->sa->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(6) {this->barStatusJogo, this->barStatusBD, 
				this->barNumJogadores, this->barHora, this->barFPS, this->barTempoAtualizacao});
			this->sa->Location = System::Drawing::Point(0, 476);
			this->sa->Name = L"sa";
			this->sa->Size = System::Drawing::Size(776, 22);
			this->sa->TabIndex = 1;
			this->sa->Text = L"statusStrip1";
			// 
			// barStatusJogo
			// 
			this->barStatusJogo->AutoSize = false;
			this->barStatusJogo->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barStatusJogo->Name = L"barStatusJogo";
			this->barStatusJogo->Size = System::Drawing::Size(120, 17);
			this->barStatusJogo->Text = L"Status do Jogo:";
			this->barStatusJogo->Click += gcnew System::EventHandler(this, &frmPrincipal::toolStripStatusLabel1_Click);
			// 
			// barStatusBD
			// 
			this->barStatusBD->AutoSize = false;
			this->barStatusBD->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barStatusBD->Name = L"barStatusBD";
			this->barStatusBD->Size = System::Drawing::Size(120, 17);
			this->barStatusBD->Text = L"Status BD:";
			// 
			// barNumJogadores
			// 
			this->barNumJogadores->AutoSize = false;
			this->barNumJogadores->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barNumJogadores->Name = L"barNumJogadores";
			this->barNumJogadores->Size = System::Drawing::Size(180, 17);
			this->barNumJogadores->Text = L"Número de Jogador ON:";
			// 
			// barHora
			// 
			this->barHora->AutoSize = false;
			this->barHora->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barHora->Name = L"barHora";
			this->barHora->Size = System::Drawing::Size(120, 17);
			this->barHora->Text = L"Horario do Server";
			// 
			// barFPS
			// 
			this->barFPS->AutoSize = false;
			this->barFPS->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barFPS->Name = L"barFPS";
			this->barFPS->Size = System::Drawing::Size(60, 17);
			this->barFPS->Text = L"FPS";
			// 
			// barTempoAtualizacao
			// 
			this->barTempoAtualizacao->AutoSize = false;
			this->barTempoAtualizacao->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barTempoAtualizacao->Name = L"barTempoAtualizacao";
			this->barTempoAtualizacao->Size = System::Drawing::Size(150, 17);
			this->barTempoAtualizacao->Text = L"Tempo de Atualização:";
			// 
			// menu
			// 
			this->menu->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(1) {this->arquivoToolStripMenuItem});
			this->menu->Location = System::Drawing::Point(0, 0);
			this->menu->Name = L"menu";
			this->menu->Size = System::Drawing::Size(776, 24);
			this->menu->TabIndex = 2;
			this->menu->Text = L"menuStrip1";
			// 
			// arquivoToolStripMenuItem
			// 
			this->arquivoToolStripMenuItem->Name = L"arquivoToolStripMenuItem";
			this->arquivoToolStripMenuItem->Size = System::Drawing::Size(56, 20);
			this->arquivoToolStripMenuItem->Text = L"&Arquivo";
			// 
			// timer
			// 
			this->timer->Interval = 33;
			this->timer->Tick += gcnew System::EventHandler(this, &frmPrincipal::timerBD_Tick);
			// 
			// frmPrincipal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(776, 498);
			this->Controls->Add(this->sa);
			this->Controls->Add(this->menu);
			this->Controls->Add(this->abas);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->MainMenuStrip = this->menu;
			this->Name = L"frmPrincipal";
			this->Text = L"WarBugs Server";
			this->Load += gcnew System::EventHandler(this, &frmPrincipal::frmPrincipal_Load);
			this->abas->ResumeLayout(false);
			this->tabJogadoresOn->ResumeLayout(false);
			this->gbJogador->ResumeLayout(false);
			this->gbJogador->PerformLayout();
			this->gbServer->ResumeLayout(false);
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridJogadores))->EndInit();
			this->tabConfig->ResumeLayout(false);
			this->groupBox8->ResumeLayout(false);
			this->groupBox8->PerformLayout();
			this->groupBox9->ResumeLayout(false);
			this->groupBox9->PerformLayout();
			this->groupBox7->ResumeLayout(false);
			this->groupBox7->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nCorteOferta))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nCorteDemanda))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->nCorteDurabilidade))->EndInit();
			this->gbConfigBD->ResumeLayout(false);
			this->groupBox2->ResumeLayout(false);
			this->groupBox2->PerformLayout();
			this->groupBox1->ResumeLayout(false);
			this->groupBox1->PerformLayout();
			this->gbConfigIniciais->ResumeLayout(false);
			this->groupBox6->ResumeLayout(false);
			this->groupBox6->PerformLayout();
			this->groupBox5->ResumeLayout(false);
			this->groupBox5->PerformLayout();
			this->groupBox4->ResumeLayout(false);
			this->groupBox4->PerformLayout();
			this->groupBox3->ResumeLayout(false);
			this->groupBox3->PerformLayout();
			this->tabLog->ResumeLayout(false);
			this->tabMercado->ResumeLayout(false);
			this->gbDadosIniciais->ResumeLayout(false);
			this->gbDadosIniciais->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->graficoCapital))->EndInit();
			this->sa->ResumeLayout(false);
			this->sa->PerformLayout();
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void frmPrincipal_Load(System::Object^  sender, System::EventArgs^  e) 
			 {

			 }
	private: System::Void toolStripStatusLabel1_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			 }
	private: System::Void btConectar_Click(System::Object^  sender, System::EventArgs^  e) 
			 {
			
			_dataBase = NULL;
			_dataBase = new CDataBase(toChar2(txtHost->Text),toChar2(txtBD->Text),toChar2(txtLogin->Text),toChar2(txtSenha->Text));
		 }

/*Transforma a porra do tipo string do windows em coisa de macho!*/
	private : char * toChar2(System::String^ str)
		{
			char * target;

			pin_ptr<const wchar_t> wch = PtrToStringChars( str );

			size_t i;

			int len = (( str->Length+1) * 2);

			target = new char[ len ];
						
			wcstombs_s(&i, target, (size_t)len, wch, (size_t)len );

			return target;
		}

private: System::Void timerBD_Tick(System::Object^  sender, System::EventArgs^  e) 
		 {
		
			 __int64 startTime = DateTime::Now.Ticks;
			 

			this->barStatusBD->Text = L"Status BD: "+( _dataBase->isConnected() ? "ON":"OFF");

			this->barHora->Text = L""+DateTime::Now;

			this->barNumJogadores->Text = L"Número de Jogadores: "+_coreServer->getPlayers()->size();

			_coreServer->readPackets();
			
			if(gridJogadores->Rows->Count > _coreServer->getPlayers()->size())
			{
				gridJogadores->Rows->Clear();
			}

			while(gridJogadores->Rows->Count < _coreServer->getPlayers()->size())
			{
				gridJogadores->Rows->Add(_coreServer->getPlayers()->size());
			}

			String ^ temp2;
			String ^ temp3;
			String ^ temp4;

			for(int i = 0; i < _coreServer->getPlayers()->size(); i++)
			{
				

				try
				{
					temp2 = gcnew String(_coreServer->getPlayers()->getElementAt(i)->getName());
				}
				catch(...)
				{
					temp2 = L"";
				}

				try
				{
					temp3 = gcnew String(_coreServer->getPlayers()->getElementAt(i)->getCharacter()->getName());
				}
				catch(...)
				{
					temp3 = L"";
				}

				try
				{
					temp4 = gcnew String(L""+_coreServer->getPlayers()->getElementAt(i)->getScene()->getID());
				}
				catch(...)
				{
					temp4 = L"";
				}

				//primeira coluna
				gridJogadores->Rows[i]->Cells[0]->Value = i+1;
				gridJogadores->Rows[i]->Cells[1]->Value = temp2;
				gridJogadores->Rows[i]->Cells[2]->Value = temp3;
				gridJogadores->Rows[i]->Cells[3]->Value = temp4;

			}

			
			//Atualiza os Server
			_coreServer->updateAll();

			if(_coreServer->getPlayers()->size() > 0)
		for(int i = 0; i < _coreServer->_cenarioList->size(); i++)
			{
				for(int j = 0; j < _coreServer->_cenarioList->getElementAt(i)->monsterCount(); j++)
				{
					/*
					float x = _coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->getPosition()->x + 0.2f;
					float z = _coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->getPosition()->z + 0.2f;
					_coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->setPosition( x, z);*/
					
					CCoreServer::sendMessage(true,_coreServer->_cenarioList->getElementAt(i)->getID(),NULL,UPDATE_POSITION,_coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->getSceneID(),_coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->getPosition()->x,_coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->getPosition()->z, _coreServer->_cenarioList->getElementAt(i)->getMonsterAt(j)->getDirection());
				}			
			}



	/*		int tempoPing = ((DateTime::Now.Ticks/TimeSpan::TicksPerSecond) - _coreServer->getBeginTimePing());
	
			if(tempoPing > _coreServer->getIntervalTimePing() && _coreServer->getPlayers()->size() > 0)
			{
				//envia mensagem de ping
				_coreServer->sendMessage(true,-1,NULL,PING);

				for(int i = 0; i < _coreServer->getPlayers()->size(); i++)
				{

					//Verifica o jogador que está  com o ping Alto
					long pingInicial = _coreServer->getPlayers()->getElementAt(i)->getEndTimePing();
					long pingFinal   = _coreServer->getPlayers()->getElementAt(i)->getBeginTimePing();
					if( (pingFinal - pingInicial) >_coreServer->getToleranceMaxPing())
					{
						kicar(i);
					}
					else
					{
						_coreServer->getPlayers()->getElementAt(i)->setBeginTimePing(_coreServer->getBeginTimePing());
					}
				}
			}*/



			//Envia mensagens para os clientes
			_coreServer->sendMessage(true, -1, NULL, END_FRAME);
			//_coreServer->sendAllMessages();

			//Verifica a taxa de atualização e FPS
			__int64 timeNow = DateTime::Now.Ticks;

			long time = (timeNow  - startTime)/TimeSpan::TicksPerMillisecond;

			this->barTempoAtualizacao->Text = L"Tempo Atualização: "+time;

			this->barFPS->Text = L"FPS: "+(1000/(timer->Interval + time));

		 }


private: System::Void btKicar_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			 int i = 0;
			 for(i = 0; i < gridJogadores->Rows->Count; i++)
			 {
				 if(gridJogadores->Rows[i]->Selected)
				 {
					 gridJogadores->Rows->RemoveAt(i);
					 kicar(i);
				 }
			 }
			 gridJogadores->Rows->Clear();

		 }
private: void kicar(int posJogador)
		 {
			 if(_coreServer->getPlayers()->size() > 0)
			 {
				//char c[1400];
				CBugMessage * m = new CBugMessage();
				//m.init(c,1400);
//				m->init();

				m->writeInt(0);
				m->writeInt(DISCONNECT);

				if(_coreServer->getPlayers()->getElementAt(posJogador)->getSocket()->_connected)
				{
					_coreServer->getPlayers()->getElementAt(posJogador)->getSocket()->sendMessage(m);
					_coreServer->getPlayers()->getElementAt(posJogador)->getSocket()->close();
				}
				_coreServer->getPlayers()->removeJogadorAt(posJogador);					 
			}
		 }
private: System::Void btLigarServer_Click(System::Object^  sender, System::EventArgs^  e) {
			 timer->Enabled = true;
			 this->barStatusJogo->Text = L"Status Jogo: "+( timer->Enabled ? "ON":"OFF");
		 }
private: System::Void btAplicarFPS_Click(System::Object^  sender, System::EventArgs^  e) {
			 
			 if(txtValorFPS->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorFPS->Text);
				 if(temp > 0)
				 {
					 _coreServer->setFPS(temp);
					 labValorFPS->Text = L""+temp;
					 timer->Interval = 1000/_coreServer->getFPS();
				 }
				 else
				 {
					 _coreServer->setFPS(0);				 
					 labValorFPS->Text = L"0";
				 }
				
			 }
		 }
private: System::Void btAplicarIntervaloPing_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtValorVerPing->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorVerPing->Text);
				 if(temp > 0)
				 {
					 _coreServer->setIntervalTimePing(temp);
					 _coreServer->setBeginTimePing(DateTime::Now.Ticks/TimeSpan::TicksPerSecond);
					 labValorVerPing->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setIntervalTimePing(0);
					 labValorVerPing->Text = L"0";
				 }
			 }

		 }
private: System::Void btAplicarToleranciaPing_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtToleranciaPing->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtToleranciaPing->Text);
				 if(temp > 0)
				 {
					 _coreServer->setToleranceMaxPing(temp);
					 labValorToleranciaPing->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setToleranceMaxPing(0);				 
					 labValorToleranciaPing->Text = L"0";
				 }
				
			 }

		 }
private: System::Void btAplicarHorasBkp_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtValorBkpTotal->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorBkpTotal->Text);
				 if(temp > 0)
				 {
					 _coreServer->setIntervalTimeSaveAll(temp);
					 labValorBkpTotal->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setIntervalTimeSaveAll(0);
					 labValorBkpTotal->Text = L"0";
				 }
				
			 }
		 }
private: System::Void btAplicarMercadoBkp_Click(System::Object^  sender, System::EventArgs^  e) {

			 if(txtValorBkpMercado->Text->Length > 0)
			 {
				 int temp = Int32::Parse(txtValorBkpMercado->Text);
				 if(temp > 0)
				 {
					 _coreServer->setIntervalTimeSaveMarket(temp);
					 labValorBkpMercado->Text = L""+temp;
				 }
				 else
				 {
					 _coreServer->setIntervalTimeSaveMarket(0);
					 labValorBkpMercado->Text = L"0";
				 }
				
			 }
		 }
private: System::Void chart1_Click(System::Object^  sender, System::EventArgs^  e) {
		 }
private: System::Void gridJogadores_CellContentClick(System::Object^  sender, System::Windows::Forms::DataGridViewCellEventArgs^  e) {
		 }
private: System::Void btGeraGrafico_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
			graficoCapital->Series->Clear();

			for(int i = 0; i < graficoCapital->Series->Count; i++)
				graficoCapital->Series->RemoveAt(0);

			graficoCapital->Refresh();

			ArrayList ^ capital = gcnew ArrayList();
			ArrayList ^ meta    = gcnew ArrayList();
			ArrayList ^ tempo   = gcnew ArrayList();
			ArrayList ^ lua     = gcnew ArrayList();

			int idVendedor;

			switch(cbVendedor->SelectedIndex)
			{
				case 0:
					idVendedor = 0; // isso será cadastrado os vendedores ainda no bd
					break;
				case 1:
					idVendedor = 1; 
					break;
				case 2:
					idVendedor = 2;
					break;
				case 3:
					idVendedor = 3;
					break;
				case 4:			
					idVendedor = 4;
					break;
			}

			_coreServer->getDataManager()->getInformacaoVendedor(idVendedor, capital, meta, tempo, lua, dtPeriodoInicial->Value, dtPeriodoFinal->Value);

			gerarGrafico(capital, meta, tempo, lua);
		 }

private: System::Void gerarGrafico(ArrayList ^ capital, ArrayList ^ meta, ArrayList ^ tempo, ArrayList ^ lua)
		 {
			int numRegsCapital, numRegsMeta, numRegsTempo;

			numRegsCapital = capital->Count;
			numRegsMeta    = meta->Count;
			numRegsTempo   = tempo->Count;

			if(numRegsCapital == 0 || numRegsMeta == 0 || numRegsTempo == 0)
			{
				return;
			}

			String ^ tempCapital = L"Capital do Vendedor";
			String ^ tempMeta = L"Meta do Vendedor";

			DataVisualization::Charting::Series ^ seriesCapital = gcnew DataVisualization::Charting::Series(tempCapital);
			DataVisualization::Charting::Series ^ seriesMeta    = gcnew DataVisualization::Charting::Series(tempMeta);

			seriesCapital->ChartType = DataVisualization::Charting::SeriesChartType::Spline;
			seriesMeta->ChartType = DataVisualization::Charting::SeriesChartType::Line;

			seriesCapital->BorderWidth = 2;
			seriesMeta->BorderWidth = 2;

			seriesCapital->ShadowOffset = 1;
			seriesMeta->ShadowOffset = 1;

			seriesCapital->XValueType = DataVisualization::Charting::ChartValueType::DateTime;
			seriesMeta->XValueType = DataVisualization::Charting::ChartValueType::DateTime;


			String ^ temp = L" ";

			for(int indexCapital = 0; indexCapital < numRegsCapital; indexCapital += 1)
			{
				DataVisualization::Charting::DataPoint ^ point = gcnew DataVisualization::Charting::DataPoint();
				point->SetValueXY(tempo[indexCapital],Double::Parse(capital[indexCapital]->ToString()));
				seriesCapital->Points->Add(point);


				DataVisualization::Charting::DataPoint ^ point2 = gcnew DataVisualization::Charting::DataPoint();

				point2->SetValueXY((DateTime)tempo[indexCapital],Double::Parse(meta[indexCapital]->ToString()));
				
				if(!temp->Equals(lua[indexCapital]->ToString()))
				{
					point2->IsValueShownAsLabel = true;
					point2->Label = lua[indexCapital]->ToString();
				}

				seriesMeta->Points->Add(point2);

				temp = lua[indexCapital]->ToString();
			}


			graficoCapital->Series->Clear();
			graficoCapital->Series->Add(seriesCapital);
			graficoCapital->Series->Add(seriesMeta);

		 }

private: System::Void button2_Click(System::Object^  sender, System::EventArgs^  e) {

		 }
private: System::Void btVerCoeficientes_Click(System::Object^  sender, System::EventArgs^  e) {

			int Kr = 0,
				Kd = 0,
				Ko = 0,
				Kl = 0,
				Kt = 0;

			_coreServer->getDataManager()->getCoeficientesMercado( Kr, Kd, Ko, Kl, Kt);

			nCorteDemanda->Value = Kd;
			nCorteOferta->Value = Ko;
			nCorteDurabilidade->Value = Kr;
			nDescontoLealdade->SelectedIndex = Kl;
			nDescontoTempo->SelectedIndex = Kt;

		 }
private: System::Void btAplicarCoeficientes_Click(System::Object^  sender, System::EventArgs^  e) {

			int Kr = 0,
				Kd = 0,
				Ko = 0,
				Kl = 0,
				Kt = 0;

			Kd = Decimal::ToInt32(nCorteDemanda->Value);
			Ko = Decimal::ToInt32(nCorteOferta->Value);
			Kr = Decimal::ToInt32(nCorteDurabilidade->Value);

			Kl = nDescontoLealdade->SelectedIndex;
			Kt = nDescontoTempo->SelectedIndex;

			if(_coreServer->getDataManager()->atualizaCoeficientesMercado(Kr, Kd, Ko, Kl, Kt))
			{
				MessageBox::Show(L"Coeficientes aplicados com sucesso!");
			}
			else
			{
				MessageBox::Show(L"Erro ao aplicar coeficientes!");
			}
		 }
};
}

