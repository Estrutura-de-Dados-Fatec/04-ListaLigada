
#include <iostream>
#include <cstdlib>   // malloc, free e system
using namespace std;

// ---------------------------------------------------------------------------
// Definição de tipo: cada nó ("post-it") guarda um valor e o endereço do
// próximo nó ("a seta"). No último nó, prox vale NULL.
// ---------------------------------------------------------------------------
struct NO {
	int valor;
	NO* prox;
};

// Ponto de entrada da lista. NULL significa lista vazia.
// Atenção: se você perder este ponteiro, perde a lista inteira.
NO* primeiro = NULL;

// headers
void menu();
void inicializar();
void liberarLista();
void exibirQuantidadeElementos();
void exibirElementos();
void inserirElemento();
void excluirElemento();
void buscarElemento();
NO* posicaoElemento(int numero);
void limparTela();
void pausar();
//--------------------------


int main()
{
	menu();
}

void menu()
{
	int op = 0;
	while (op != 7) {
		limparTela();
		cout << "Menu Lista Ligada";
		cout << endl << endl;
		cout << "1 - Inicializar Lista \n";
		cout << "2 - Exibir quantidade de elementos \n";
		cout << "3 - Exibir elementos \n";
		cout << "4 - Buscar elemento \n";
		cout << "5 - Inserir elemento \n";
		cout << "6 - Excluir elemento \n";
		cout << "7 - Sair \n\n";

		cout << "Opcao: ";
		if (!(cin >> op)) {
			// entrada inválida (ex.: uma letra) ou fim da entrada
			if (cin.eof()) {
				op = 7;
			}
			else {
				cin.clear();              // limpa o estado de erro do cin
				cin.ignore(10000, '\n');  // descarta o que foi digitado
				op = 0;
			}
		}

		switch (op)
		{
		case 1: inicializar();
			break;
		case 2: exibirQuantidadeElementos();
			break;
		case 3: exibirElementos();
			break;
		case 4: buscarElemento();
			break;
		case 5: inserirElemento();
			break;
		case 6: excluirElemento();
			break;

		case 7:
			// devolve ao sistema a memória de todos os nós antes de sair
			liberarLista();
			return;
		default:
			cout << "Opcao invalida \n";
			break;
		}

		pausar();
	}
}

// Percorre a lista liberando (free) cada nó e deixa a lista vazia.
// Usada por inicializar() e ao sair do programa, para não haver
// vazamento de memória.
void liberarLista()
{
	NO* aux = primeiro;
	while (aux != NULL) {
		NO* paraExcluir = aux;   // guarda o endereço do nó atual...
		aux = aux->prox;         // ...avança ANTES de liberar...
		free(paraExcluir);       // ...e só então libera o nó
	}
	primeiro = NULL;
}

void inicializar()
{
	// se a lista já possuir elementos, libera a memória ocupada
	liberarLista();
	cout << "Lista inicializada \n";
}

void exibirQuantidadeElementos() {

	int nElementos = 0;
	NO* aux = primeiro;
	while (aux != NULL) {
		nElementos++;
		aux = aux->prox;
	}
	cout << "Quantidade de elementos: " << nElementos << endl;

}

void exibirElementos()
{
	if (primeiro == NULL) {
		cout << "Lista vazia \n";
		return;
	}
	else {
		cout << "Elementos: \n";
		NO* aux = primeiro;
		while (aux != NULL) {
			cout << aux->valor << endl;
			aux = aux->prox;
		}
	}
}

void inserirElemento()
{
	// 1) Primeiro lemos o valor em uma variável local...
	int valor;
	cout << "Digite o elemento: ";
	cin >> valor;

	// -----------------------------------------------------------------
	// TAREFA 1: antes de alocar memória, verifique se 'valor' já existe
	// na lista (dica: use posicaoElemento). Se existir, avise o usuário
	// e saia da função com return.
	// Como nada foi alocado até aqui, sair neste ponto NÃO causa
	// vazamento de memória.
	// -----------------------------------------------------------------

	// 2) ...e só depois alocamos memória para o novo nó
	NO* novo = (NO*)malloc(sizeof(NO));
	if (novo == NULL)
	{
		cout << "Erro: memoria insuficiente \n";
		return;
	}
	novo->valor = valor;
	novo->prox = NULL;   // o novo nó será o último da lista

	if (primeiro == NULL)
	{
		// lista vazia: o novo nó passa a ser o primeiro
		primeiro = novo;
	}
	else
	{
		// procura o final da lista (o nó cujo prox é NULL)
		NO* aux = primeiro;
		while (aux->prox != NULL) {
			aux = aux->prox;
		}
		aux->prox = novo;
	}
}

void excluirElemento()
{
	// -----------------------------------------------------------------
	// TAREFA 3
	// 1. Peça o número e use posicaoElemento() para saber se ele existe.
	//    Se não existir, exiba "ELEMENTO NAO ENCONTRADO" e saia.
	// 2. Caso A - o nó é o primeiro: atualize 'primeiro' para o segundo
	//    nó ANTES de liberar o nó removido.
	// 3. Caso B - meio ou fim: percorra a lista com dois ponteiros
	//    (anterior e atual), faça anterior->prox apontar para atual->prox
	//    e só então libere 'atual'.
	// Lembre-se: todo nó removido precisa de free(), e um nó liberado
	// nunca mais deve ser usado.
	// -----------------------------------------------------------------
}

void buscarElemento()
{
	// -----------------------------------------------------------------
	// TAREFA 2
	// 1. Peça ao usuário o número a ser buscado.
	// 2. Chame posicaoElemento(numero).
	// 3. Retorno diferente de NULL -> exiba "ENCONTRADO"
	//    Retorno igual a NULL     -> exiba "ELEMENTO NAO ENCONTRADO"
	// -----------------------------------------------------------------
}



// retorna um ponteiro para o elemento buscado
// ou NULL se o elemento não estiver na lista
NO* posicaoElemento(int numero)
{
	NO* aux = primeiro;
	while (aux != NULL) {
		if (aux->valor == numero)
		{
			break;
		}
		aux = aux->prox;
	}
	return aux;
}

// ---------------------------------------------------------------------------
// Utilitários de tela: funcionam no Windows (Visual Studio) e também no
// Linux/macOS (g++ ou clang++).
// ---------------------------------------------------------------------------
void limparTela()
{
#ifdef _WIN32
	system("cls");
#else
	system("clear");
#endif
}

void pausar()
{
#ifdef _WIN32
	system("pause");
#else
	cout << "Pressione ENTER para continuar...";
	cin.ignore(10000, '\n');
	cin.get();
#endif
}
