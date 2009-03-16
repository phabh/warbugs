class CCenario : CObject
{
				    int    _idCenario;        //Identifica��o do cen�rio
				   char	*  _nomeCenario;      //nome do cen�rio 
	vector<CPersonagem>    _listaPersonagens; //Personagens, NPCs e inimigos que o cen�rio tem
		  vector<CItem>    _listaItens;       //Itens que est�o no ch�o do cen�rio

	public:
		CCenario(){}
			   void entrarPersonagem(CPersonagem psg);  //Personagem que entrou no cen�rio � incluido na lista
			   void sairPersonagem();                   //Personagem que saiu do cen�rio � tirado da lista
				int qtdPersonagens();                   //Quantidade de Personagens do Cen�rio
				int qtdItens();							//Quantidade de Itens do cen�rio
		CPersonagem getPersonagem(int idPersonagem);    //Retorna o personagem com o id especificado
			  CItem getItem(int idItem);                //Retorna o Item com o id especificado

}