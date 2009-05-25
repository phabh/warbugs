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
			_coreServer = gcnew CCoreServer(_dataBase,30);
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
	private: System::Windows::Forms::TabPage^  tabManutencaoBD;
	private: System::Windows::Forms::StatusStrip^  barStatus;
	protected: 


	private: System::Windows::Forms::ToolStripStatusLabel^  barStatusJogo;
	private: System::Windows::Forms::MenuStrip^  menu;
	private: System::Windows::Forms::DataGridView^  gridResultados;



	private: System::Windows::Forms::Button^  btConsultar;

	private: System::Windows::Forms::Button^  btExecutar;

	private: System::Windows::Forms::Button^  btConectar;

	private: System::Windows::Forms::TextBox^  txtBD;

	private: System::Windows::Forms::TextBox^  txtHost;

	private: System::Windows::Forms::TextBox^  txtSenha;

	private: System::Windows::Forms::TextBox^  txtLogin;
	private: System::Windows::Forms::TextBox^  txtSQL;


	private: System::Windows::Forms::Label^  labResultados;

	private: System::Windows::Forms::Label^  labSQL;


	private: System::Windows::Forms::Label^  labBD;

	private: System::Windows::Forms::Label^  labHost;

	private: System::Windows::Forms::Label^  labSenha;

	private: System::Windows::Forms::Label^  labLogin;
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
	private: System::Windows::Forms::Timer^  timerBD;
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
			this->tabManutencaoBD = (gcnew System::Windows::Forms::TabPage());
			this->labResultados = (gcnew System::Windows::Forms::Label());
			this->labSQL = (gcnew System::Windows::Forms::Label());
			this->labBD = (gcnew System::Windows::Forms::Label());
			this->labHost = (gcnew System::Windows::Forms::Label());
			this->labSenha = (gcnew System::Windows::Forms::Label());
			this->labLogin = (gcnew System::Windows::Forms::Label());
			this->gridResultados = (gcnew System::Windows::Forms::DataGridView());
			this->btConsultar = (gcnew System::Windows::Forms::Button());
			this->btExecutar = (gcnew System::Windows::Forms::Button());
			this->btConectar = (gcnew System::Windows::Forms::Button());
			this->txtBD = (gcnew System::Windows::Forms::TextBox());
			this->txtHost = (gcnew System::Windows::Forms::TextBox());
			this->txtSenha = (gcnew System::Windows::Forms::TextBox());
			this->txtLogin = (gcnew System::Windows::Forms::TextBox());
			this->txtSQL = (gcnew System::Windows::Forms::TextBox());
			this->tabLog = (gcnew System::Windows::Forms::TabPage());
			this->logBox = (gcnew System::Windows::Forms::ListBox());
			this->barStatus = (gcnew System::Windows::Forms::StatusStrip());
			this->barStatusJogo = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barStatusBD = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->barNumJogadores = (gcnew System::Windows::Forms::ToolStripStatusLabel());
			this->menu = (gcnew System::Windows::Forms::MenuStrip());
			this->arquivoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->timerBD = (gcnew System::Windows::Forms::Timer(this->components));
			this->abas->SuspendLayout();
			this->tabJogadoresOn->SuspendLayout();
			this->gbJogador->SuspendLayout();
			this->gbServer->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridJogadores))->BeginInit();
			this->tabManutencaoBD->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridResultados))->BeginInit();
			this->tabLog->SuspendLayout();
			this->barStatus->SuspendLayout();
			this->menu->SuspendLayout();
			this->SuspendLayout();
			// 
			// abas
			// 
			this->abas->Controls->Add(this->tabJogadoresOn);
			this->abas->Controls->Add(this->tabManutencaoBD);
			this->abas->Controls->Add(this->tabLog);
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
			// 
			// gridJogadores
			// 
			this->gridJogadores->AllowUserToAddRows = false;
			this->gridJogadores->AllowUserToDeleteRows = false;
			this->gridJogadores->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridJogadores->Columns->AddRange(gcnew cli::array< System::Windows::Forms::DataGridViewColumn^  >(4) {this->idConexao, 
				this->nomeJogador, this->nomePersonagem, this->nomeCenario});
			this->gridJogadores->Location = System::Drawing::Point(3, 6);
			this->gridJogadores->Name = L"gridJogadores";
			this->gridJogadores->ReadOnly = true;
			this->gridJogadores->Size = System::Drawing::Size(637, 414);
			this->gridJogadores->TabIndex = 0;
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
			// tabManutencaoBD
			// 
			this->tabManutencaoBD->Controls->Add(this->labResultados);
			this->tabManutencaoBD->Controls->Add(this->labSQL);
			this->tabManutencaoBD->Controls->Add(this->labBD);
			this->tabManutencaoBD->Controls->Add(this->labHost);
			this->tabManutencaoBD->Controls->Add(this->labSenha);
			this->tabManutencaoBD->Controls->Add(this->labLogin);
			this->tabManutencaoBD->Controls->Add(this->gridResultados);
			this->tabManutencaoBD->Controls->Add(this->btConsultar);
			this->tabManutencaoBD->Controls->Add(this->btExecutar);
			this->tabManutencaoBD->Controls->Add(this->btConectar);
			this->tabManutencaoBD->Controls->Add(this->txtBD);
			this->tabManutencaoBD->Controls->Add(this->txtHost);
			this->tabManutencaoBD->Controls->Add(this->txtSenha);
			this->tabManutencaoBD->Controls->Add(this->txtLogin);
			this->tabManutencaoBD->Controls->Add(this->txtSQL);
			this->tabManutencaoBD->Location = System::Drawing::Point(4, 22);
			this->tabManutencaoBD->Name = L"tabManutencaoBD";
			this->tabManutencaoBD->Padding = System::Windows::Forms::Padding(3);
			this->tabManutencaoBD->Size = System::Drawing::Size(766, 423);
			this->tabManutencaoBD->TabIndex = 1;
			this->tabManutencaoBD->Text = L"Manutenção Banco de Dados";
			this->tabManutencaoBD->UseVisualStyleBackColor = true;
			// 
			// labResultados
			// 
			this->labResultados->AutoSize = true;
			this->labResultados->Location = System::Drawing::Point(3, 250);
			this->labResultados->Name = L"labResultados";
			this->labResultados->Size = System::Drawing::Size(60, 13);
			this->labResultados->TabIndex = 14;
			this->labResultados->Text = L"Resultados";
			// 
			// labSQL
			// 
			this->labSQL->AutoSize = true;
			this->labSQL->Location = System::Drawing::Point(3, 64);
			this->labSQL->Name = L"labSQL";
			this->labSQL->Size = System::Drawing::Size(28, 13);
			this->labSQL->TabIndex = 13;
			this->labSQL->Text = L"SQL";
			// 
			// labBD
			// 
			this->labBD->AutoSize = true;
			this->labBD->Location = System::Drawing::Point(449, 17);
			this->labBD->Name = L"labBD";
			this->labBD->Size = System::Drawing::Size(126, 13);
			this->labBD->TabIndex = 12;
			this->labBD->Text = L"Nome da Base de Dados";
			// 
			// labHost
			// 
			this->labHost->AutoSize = true;
			this->labHost->Location = System::Drawing::Point(289, 17);
			this->labHost->Name = L"labHost";
			this->labHost->Size = System::Drawing::Size(29, 13);
			this->labHost->TabIndex = 11;
			this->labHost->Text = L"Host";
			// 
			// labSenha
			// 
			this->labSenha->AutoSize = true;
			this->labSenha->Location = System::Drawing::Point(132, 17);
			this->labSenha->Name = L"labSenha";
			this->labSenha->Size = System::Drawing::Size(38, 13);
			this->labSenha->TabIndex = 10;
			this->labSenha->Text = L"Senha";
			// 
			// labLogin
			// 
			this->labLogin->AutoSize = true;
			this->labLogin->Location = System::Drawing::Point(5, 17);
			this->labLogin->Name = L"labLogin";
			this->labLogin->Size = System::Drawing::Size(33, 13);
			this->labLogin->TabIndex = 9;
			this->labLogin->Text = L"Login";
			// 
			// gridResultados
			// 
			this->gridResultados->AllowUserToAddRows = false;
			this->gridResultados->AllowUserToDeleteRows = false;
			this->gridResultados->ColumnHeadersHeightSizeMode = System::Windows::Forms::DataGridViewColumnHeadersHeightSizeMode::AutoSize;
			this->gridResultados->Location = System::Drawing::Point(6, 266);
			this->gridResultados->Name = L"gridResultados";
			this->gridResultados->ReadOnly = true;
			this->gridResultados->Size = System::Drawing::Size(752, 150);
			this->gridResultados->TabIndex = 8;
			// 
			// btConsultar
			// 
			this->btConsultar->Location = System::Drawing::Point(607, 241);
			this->btConsultar->Name = L"btConsultar";
			this->btConsultar->Size = System::Drawing::Size(151, 19);
			this->btConsultar->TabIndex = 7;
			this->btConsultar->Text = L"Consultar";
			this->btConsultar->UseVisualStyleBackColor = true;
			this->btConsultar->Click += gcnew System::EventHandler(this, &frmPrincipal::btConsultar_Click);
			// 
			// btExecutar
			// 
			this->btExecutar->Location = System::Drawing::Point(450, 241);
			this->btExecutar->Name = L"btExecutar";
			this->btExecutar->Size = System::Drawing::Size(151, 19);
			this->btExecutar->TabIndex = 6;
			this->btExecutar->Text = L"Executar";
			this->btExecutar->UseVisualStyleBackColor = true;
			this->btExecutar->Click += gcnew System::EventHandler(this, &frmPrincipal::btExecutar_Click);
			// 
			// btConectar
			// 
			this->btConectar->Location = System::Drawing::Point(606, 31);
			this->btConectar->Name = L"btConectar";
			this->btConectar->Size = System::Drawing::Size(151, 22);
			this->btConectar->TabIndex = 5;
			this->btConectar->Text = L"Conectar";
			this->btConectar->UseVisualStyleBackColor = true;
			this->btConectar->Click += gcnew System::EventHandler(this, &frmPrincipal::btConectar_Click);
			// 
			// txtBD
			// 
			this->txtBD->Location = System::Drawing::Point(449, 33);
			this->txtBD->Name = L"txtBD";
			this->txtBD->Size = System::Drawing::Size(151, 20);
			this->txtBD->TabIndex = 4;
			// 
			// txtHost
			// 
			this->txtHost->Location = System::Drawing::Point(292, 33);
			this->txtHost->Name = L"txtHost";
			this->txtHost->Size = System::Drawing::Size(151, 20);
			this->txtHost->TabIndex = 3;
			// 
			// txtSenha
			// 
			this->txtSenha->Location = System::Drawing::Point(135, 33);
			this->txtSenha->Name = L"txtSenha";
			this->txtSenha->PasswordChar = '?';
			this->txtSenha->Size = System::Drawing::Size(151, 20);
			this->txtSenha->TabIndex = 2;
			// 
			// txtLogin
			// 
			this->txtLogin->Location = System::Drawing::Point(5, 33);
			this->txtLogin->Name = L"txtLogin";
			this->txtLogin->Size = System::Drawing::Size(124, 20);
			this->txtLogin->TabIndex = 1;
			// 
			// txtSQL
			// 
			this->txtSQL->Font = (gcnew System::Drawing::Font(L"Courier New", 9.75F, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				static_cast<System::Byte>(0)));
			this->txtSQL->Location = System::Drawing::Point(6, 80);
			this->txtSQL->Multiline = true;
			this->txtSQL->Name = L"txtSQL";
			this->txtSQL->ScrollBars = System::Windows::Forms::ScrollBars::Vertical;
			this->txtSQL->Size = System::Drawing::Size(752, 155);
			this->txtSQL->TabIndex = 0;
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
			// barStatus
			// 
			this->barStatus->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {this->barStatusJogo, this->barStatusBD, 
				this->barNumJogadores});
			this->barStatus->Location = System::Drawing::Point(0, 476);
			this->barStatus->Name = L"barStatus";
			this->barStatus->Size = System::Drawing::Size(776, 22);
			this->barStatus->TabIndex = 1;
			this->barStatus->Text = L"statusStrip1";
			// 
			// barStatusJogo
			// 
			this->barStatusJogo->AutoSize = false;
			this->barStatusJogo->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barStatusJogo->Name = L"barStatusJogo";
			this->barStatusJogo->Size = System::Drawing::Size(200, 17);
			this->barStatusJogo->Text = L"Status do Jogo: ON";
			this->barStatusJogo->Click += gcnew System::EventHandler(this, &frmPrincipal::toolStripStatusLabel1_Click);
			// 
			// barStatusBD
			// 
			this->barStatusBD->AutoSize = false;
			this->barStatusBD->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barStatusBD->Name = L"barStatusBD";
			this->barStatusBD->Size = System::Drawing::Size(200, 17);
			this->barStatusBD->Text = L"Status BD: ON";
			// 
			// barNumJogadores
			// 
			this->barNumJogadores->AutoSize = false;
			this->barNumJogadores->BorderSides = static_cast<System::Windows::Forms::ToolStripStatusLabelBorderSides>((((System::Windows::Forms::ToolStripStatusLabelBorderSides::Left | System::Windows::Forms::ToolStripStatusLabelBorderSides::Top) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Right) 
				| System::Windows::Forms::ToolStripStatusLabelBorderSides::Bottom));
			this->barNumJogadores->Name = L"barNumJogadores";
			this->barNumJogadores->Size = System::Drawing::Size(200, 17);
			this->barNumJogadores->Text = L"Número de Jogador ON: 500.000";
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
			// timerBD
			// 
			this->timerBD->Enabled = true;
			this->timerBD->Interval = 33;
			this->timerBD->Tick += gcnew System::EventHandler(this, &frmPrincipal::timerBD_Tick);
			// 
			// frmPrincipal
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(776, 498);
			this->Controls->Add(this->barStatus);
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
			this->tabManutencaoBD->ResumeLayout(false);
			this->tabManutencaoBD->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->gridResultados))->EndInit();
			this->tabLog->ResumeLayout(false);
			this->barStatus->ResumeLayout(false);
			this->barStatus->PerformLayout();
			this->menu->ResumeLayout(false);
			this->menu->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void frmPrincipal_Load(System::Object^  sender, System::EventArgs^  e) {

			 }
	private: System::Void toolStripStatusLabel1_Click(System::Object^  sender, System::EventArgs^  e) {
			 }
	private: System::Void btConectar_Click(System::Object^  sender, System::EventArgs^  e) {
			
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

private: System::Void timerBD_Tick(System::Object^  sender, System::EventArgs^  e) {
			this->barStatusBD->Text = L"Status BD: "+( _dataBase->isConnected() ? "ON":"OFF");

			_coreServer->readPackets();

			gridJogadores->Rows->Clear();

			while(gridJogadores->Rows->Count < _coreServer->getPlayers()->size())
			{ 
				gridJogadores->Rows->Add();
			}



			//atualização da aba de Jogadores On Line
			for(int i = 0; i < _coreServer->getPlayers()->size(); i++)
			{
				//primeira coluna
				gridJogadores->Rows[i]->Cells[0]->Value = i+1;

				//gridJogadores->Rows[i]->Cells[1]->Value = _coreServer->getPlayers()->getElementAt(i)->getID();
				
				if(_coreServer->getPlayers()->getElementAt(i)->getName() != NULL)
					gridJogadores->Rows[i]->Cells[1]->Value = gcnew String(_coreServer->getPlayers()->getElementAt(i)->getName());
/*
				if(_coreServer->getPlayers()->getElementAt(i)->getCharacter() != NULL)
					gridJogadores->Rows[i]->Cells[2]->Value = gcnew String(_coreServer->getPlayers()->getElementAt(i)->getCharacter()->getName());

				if(_coreServer->getPlayers()->getElementAt(i)->getScene() != NULL)
					gridJogadores->Rows[i]->Cells[4]->Value = gcnew String(L""+_coreServer->getPlayers()->getElementAt(i)->getScene()->getID());
*/

			}

	//		_coreServer->verificaPlayers();

			//Atualiza os Server
			_coreServer->updateAll();

			//Envia mensagens para os clientes
			_coreServer->sendAllMessages();
	

		 }


private: System::Void btExecutar_Click(System::Object^  sender, System::EventArgs^  e) {
			 if(_dataBase->insertNow(toChar2(txtSQL->Text)))
			 {
				 System::Windows::Forms::MessageBox::Show(L"OK, Feito!",L"Mensagem - OK");
			 }
			 else
			 {
				 System::Windows::Forms::MessageBox::Show(L"É... Deu pau!",L"Mensagem - Erro");			 
			 }
		 }
private: System::Void btConsultar_Click(System::Object^  sender, System::EventArgs^  e) {
				TDadosBD ^ dados = gcnew ArrayList();
				unsigned int numCampos;
				unsigned int numRegs;
				unsigned int indexCampos = 0, indexRegs = 0;
				gridResultados->Columns->Clear();
				
				if(_dataBase->selectNow(toChar2(txtSQL->Text), numCampos, numRegs, dados))
				{

					for(indexCampos = 0; indexCampos < numCampos; indexCampos++)
					{
						String ^ text = dados[0]->ToString();
						gridResultados->Columns->Add(L"_"+text,L""+text);
						dados->RemoveAt(0);
					}

					gridResultados->Rows->Add(numRegs);


					while (numRegs > indexRegs)
					{
						for(indexCampos = 0; indexCampos < numCampos; indexCampos++)
						{
							char * s = toChar2(dados[0]->ToString()) != NULL ? toChar2(dados[0]->ToString()): "NULL";
							String ^ text = gcnew String(s);
							gridResultados->Rows[indexRegs]->Cells[indexCampos]->Value = text;
							dados->RemoveAt(0);
						}

						indexRegs++;
					} 			
				}
		 }
};
}

