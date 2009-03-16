class CCenario : CObject
{
				    int    _idCenario;        //Identificação do cenário
				   char	*  _nomeCenario;      //nome do cenário 
	vector<CPersonagem>    _listaPersonagens; //Personagens, NPCs e inimigos que o cenário tem
		  vector<CItem>    _listaItens;       //Itens que estão no chão do cenário

	public:
		CCenario(){}
			   void entrarPersonagem(CPersonagem psg);  //Personagem que entrou no cenário é incluido na lista
			   void sairPersonagem();                   //Personagem que saiu do cenário é tirado da lista
				int qtdPersonagens();                   //Quantidade de Personagens do Cenário
				int qtdItens();							//Quantidade de Itens do cenário
		CPersonagem getPersonagem(int idPersonagem);    //Retorna o personagem com o id especificado
			  CItem getItem(int idItem);                //Retorna o Item com o id especificado

}