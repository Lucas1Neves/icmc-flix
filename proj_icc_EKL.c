/* Projeto de laboratório de ICC, BSI 2020
 *
*/




#include <stdio.h> 
#include <stdlib.h> 
#include <string.h>
#include <unistd.h> // equivale ao windows.h

#define max 20

/*

getch() foi substituido por getchar()

No linux, o 'fflush(stdin)' não conserta o problema de captura de strings no terminal,
por isso, usei a função "while(getchar() != '\n')"

Sleep() corresponde ao sleep()
system('reset') coresponde ao system('cls')

*/



// Declaração dos Structs
struct filme{
    int numCatalogo;
    char titulo[60];
    char genero[20];
    int ano;
};

struct usuario{
    char nome[30];
    char cpf[12];
    int alugados;
    int atrasos;
};


// Prototipo das Funções
    
    // Funcoes de Menu
void menuPrincipal();
void menuUsuario();
void menuFilme();
void menuLocacao();

    // Funcoes Relacionadas aos Usuarios
int inserirUsuario(); 
void editarUsuario(); 
void excluirUsuario();
void listarUsuarios(); 

    // Funcoes Relacionadas aos Filmes
int inserirFilme(); 
void editarFilme(); 
void excluirFilme();
void listarFilmes(); 

    // Funcoes Relacionadas aos Filmes
void listarFilmesDisponiveis(); 
void listarFilmesLocados(); 
void locarFilme();
void devolverFilme(); 


// Main
void main(){
    struct filme filmes[max];
    struct usuario usuarios[max];
    int opcaoMenu=1, i, filmesCadastrados=0, inseriu, numCatalogo, usuariosCadastrados=0, novoUsuario;
    char genero[20], titulo[20], cpfUsuario[12];

    // Inicia Banco de Filmes e de Usuários com todas as posições 0 ou Nao Cadastrado
    for ( i = 0; i < max; i++){
        filmes[i].numCatalogo=0;
        filmes[i].ano=0;
        strcpy(filmes[i].titulo, "Nao Cadastrado!");
        strcpy(filmes[i].genero, "Nao Cadastrado!");
    } 

    for ( i = 0; i < max; i++){
        strcpy(usuarios[i].nome, "");
        strcpy(usuarios[i].cpf, "");
        usuarios[i].alugados = 0;
        usuarios[i].atrasos = 0;
    }  // A intenção é substituir este método por um gerenciamento em .sql ou .txt

    while (opcaoMenu != 0){
        menuPrincipal();
        scanf(" %d", &opcaoMenu);

        switch (opcaoMenu){

        case 0:
            printf("Saindo...");
            break;

        case 1:
            menuUsuario();
            scanf(" %d", &opcaoMenu);

            switch (opcaoMenu){
            case 0:
                opcaoMenu=10;
                break;

            case 1: // Insere um novo usuário
                novoUsuario = inserirUsuario(usuarios, usuariosCadastrados);
                    if(novoUsuario){
                        printf("\nUsuario cadastrado com sucesso!\nDigite qualquer tecla para voltar ao inicio.");
                        usuariosCadastrados++; 
		    }
		    getchar();
            break;
            
            case 2: // Edita um usuario a partir do cpf
            if(!(!usuariosCadastrados)){
                printf("\n----------------------------------");
                printf("\n\nDigite o CPF do usuario que deseja EDITAR: ");
                gets(cpfUsuario);
                while (getchar() != '\n');
                editarUsuario(usuarios, cpfUsuario);
            }
                getchar();
                break;
            
            case 3: // Exclui usuarios (verificar se o cara tem dívida antes...)
                if(!(!usuariosCadastrados)){
                    printf("\n----------------------------------");
                    printf("\n\nDigite o CPF que deseja EXCLUIR: ");
		            while (getchar() != '\n');
                    gets(cpfUsuario);
		            excluirUsuario(usuarios, cpfUsuario);
                }
                getchar();
                break;

            case 4: // Lista todos os usuarios registrados
                listarUsuarios(usuarios, usuariosCadastrados);
                getchar();
                break;
          
            default:
                printf("\nOpcao Invalida! Tente Novamente!");
                getchar();
                break;
            }
            break;

	case 2:
        menuFilme();
        scanf(" %d", &opcaoMenu);
        switch (opcaoMenu){
            case 0:
                opcaoMenu=10;
                break;

            case 1: // Insere um filme
                inseriu = inserirFilme(filmes, filmesCadastrados);
                if(inseriu){
                    printf("\nFilme inserido com sucesso!");
                    filmesCadastrados++;
                    getchar();
		        }   
                break;
            
            case 2: // Edita filme por título
                listarFilmes(filmes, filmesCadastrados);
                if(!(!filmesCadastrados)){
                    printf("\n----------------------------------");
                    printf("\n\nDigite o Titulo do filme que deseja EDITAR: ");
		    fflush(stdin);
		    while (getchar() != '\n');
                    gets(titulo);
		    
                    editarFilme(filmes, titulo);
                }
                getchar();
                break;

            
            case 3: // Exclui filme da biblioteca baseado no número de registro
                listarFilmes(filmes, filmesCadastrados);
                if(!(!filmesCadastrados)){
                    printf("\n----------------------------------");
                    printf("\n\nDigite o Numero do filme que deseja EXCLUIR: ");
                    scanf(" %d", &numCatalogo);
                    excluirFilme(filmes, numCatalogo);
		            filmesCadastrados--;
                }
                getchar();
                break;

            case 4: // Lista filmes
                listarFilmes(filmes, filmesCadastrados);
                getchar();
                break;
            
            default:
                printf("\nOpcao Invalida! Tente Novamente!");   
                getchar();
                break;
            }
            break;
        
//			COMING SOON


/*        case 3:
            menuLocacao();
            scanf(" %d", &opcaoMenu);
            switch (opcaoMenu){
            case 0:
                opcaoMenu=10;
                break;

            case 1:
                listarFilmesDisponiveis(); // Desenvolver Parametros
                break;
            
            case 2:
                listarFilmesLocados(); // Desenvolver Parametros
                break;
            
            case 3:
                locarFilme(); // Desenvolver Parametros
                break;

            case 4:
                devolverFilme(); // Desenvolver Parametros
                break;
            
            default:
                printf("\nOpcao Invalida! Tente Novamente!");   
                getch();
                break;
            }
            break;
*/        
        default:
            printf("\nOpcao Invalida! Tente Novamente!");
            getchar();
            break;
	    
        } 
    } 
}

// Corpo das Funções

    // Funcoes de Menu
void menuPrincipal(){
    system("cls");
    printf("----------- ICMC Flix -----------\n");
    printf("\n1 - Usuarios");
    printf("\n2 - Filmes");
//    printf("\n3 - Locacao");
    printf("\n0 - Sair");
    printf("\n\nDigite a opcao desejada: ");
}

void menuUsuario(){
    system("cls");
    printf("----------- ICMC Flix -----------\n");
    printf("\n1 - Cadastrar Novo Usuario");
    printf("\n2 - Editar Usuario");
    printf("\n3 - Remover Usuario");
    printf("\n4 - Listar Usuarios Cadastrados");
    printf("\n0 - Voltar");
    printf("\n\nDigite a opcao desejada: ");
}

void menuFilme(){
    system("cls");
    printf("----------- ICMC Flix -----------\n");
    printf("\n1 - Cadastrar Novo Filme");
    printf("\n2 - Editar Filme");
    printf("\n3 - Remover Filme");
    printf("\n4 - Listar Filmes Cadastrados");
    printf("\n0 - Voltar");
    printf("\n\nDigite a opcao desejada: ");
}

void menuLocacao(){  // isto é um easter egg (mentira)
    system("cls");
    printf("----------- ICMC Flix -----------\n");
    printf("\n1 - Listar Filmes Disponiveis");
    printf("\n2 - Listar Filmes Locados");
    printf("\n3 - Locar Filme");
    printf("\n4 - Devolver Filme");
    printf("\n0 - Voltar");
    printf("\n\nDigite a opcao desejada: ");

}

    // Funcoes relacionadas aos Usuarios
int inserirUsuario(struct usuario *usuarios, int usuariosCadastrados){
    int novoUsuario = 0 ;

    // usamos a variável que mostra o número de usuários também como 'iterador'
    for(usuariosCadastrados; usuariosCadastrados < max; usuariosCadastrados++){
        if(strlen(usuarios[usuariosCadastrados].nome) == 0){
            printf("\nNome do usuario: \n");
	        fflush(stdin);
	        while (getchar() != '\n');
            gets(usuarios[usuariosCadastrados].nome);
            printf("CPF: ");
            fflush(stdin);
            gets(usuarios[usuariosCadastrados].cpf);
            novoUsuario = 1;
            break;
        }
    }

    if(!novoUsuario){
        printf("\nOcorreu um erro de alocacao.\nPedimos desculpas pelo incomodo.");
        getchar();
    }

    return novoUsuario;
}

//void editarUsuario(){
void editarUsuario(struct usuario *usuarios, char cpfUsuario[]){
    int i, editado=0, encontrado=0;
    char confirma;

    for ( i = 0; i < max; i++)
    {
        if(strcmp(cpfUsuario, usuarios[i].cpf) == 0){
            printf("\n----------------------------------");
            printf("\nNome: %s\nCPF: %s\nAlugueis pendentes: %s\nAtrasos: %d\n\n",
            usuarios[i].nome, usuarios[i].cpf, usuarios[i].alugados, usuarios[i].atrasos);
            printf("Este e o cadastro que deseja editar? [s/n]");
            scanf("%c", &confirma);
            if (confirma == 's'){
                encontrado = 1;
                break;
            }
        }
    }

    if(encontrado == 1){
        printf("\nNome: ");
        fflush(stdin);
        while (getchar() != '\n');
        gets(usuarios[i].nome);
        editado=1;
    }
    if(!encontrado) printf("\nNao foram encontrados cadastros com este cpf!");

    if(editado) printf("\nCadastro editado com sucesso!");
    else printf("\nHouve um erro que nem os programadores entenderam!");
}

void excluirUsuario(struct usuario *usuarios, char cpfUsuario[]){
    int i, excluido=0;

    for ( i = 0; i < max; i++)
    {
        if(strcmp(cpfUsuario, usuarios[i].cpf) == 0){
	    if(!(usuarios[i].alugados) | !(usuarios[i].atrasos)){
		    printf("Nao e possivel remover cadastros em situacao irregular");
	    }
	    else{
            strcpy(usuarios[i].nome, "");
            strcpy(usuarios[i].cpf, "");
            excluido=1;
	    }
        }
    }

    if(excluido) printf("\nCadastro removido com Sucesso!");
    else printf("\nUsuario nao encontrado");
}

void listarUsuarios(struct usuario *usuarios, int usuariosCadastrados){
    int i;

    if(!usuariosCadastrados){
        printf("\nNenhum Usuario Cadastrado.");
    }else{
        for ( i = 0; i < max; i++)
        {
                if(strlen(usuarios[i].nome) != 0){
                    printf("\n----------------------------------");
                    printf("\nNome: %s\nCPF: %s\n",
                                    usuarios[i].nome, usuarios[i].cpf);
            }
        }
        printf("\n\nAcima estao as pessoas cadastrados\nPressione qualquer tecla para voltar ao menu principal\n");
        getchar();
    }
}

    // Funcoes relacionadas aos Filmes
int inserirFilme(struct filme *filmes, int filmesCadastrados){
    int inseriu = 0, i;

    for ( i = 0; i < max; i++)
    {
        if(filmes[i].numCatalogo == 0){
            printf("\nNumero de Catalogo: %d\n", (filmesCadastrados+1));
            filmes[i].numCatalogo = filmesCadastrados+1;
            printf("Titulo do Filme: ");
            fflush(stdin);
            while (getchar() != '\n');
            gets(filmes[i].titulo);
            printf("Genero do Filme: ");
            fflush(stdin);
            gets(filmes[i].genero);
            printf("Ano do Filme: ");
            scanf("%d", &filmes[i].ano);
            inseriu = 1;
            break;
        }
    }

    if(!inseriu){
        printf("\nBanco de Filmes Cheio.");
        getchar();
    }

    return inseriu;
}

void editarFilme(struct filme *filmes, char titulo[]){
    int i, editado=0, encontrado=0;
    char confirma;

    for ( i = 0; i < max; i++)
    {
        if(strcmp(titulo, filmes[i].titulo) == 0){
            printf("\n----------------------------------");
            printf("\nNumero de Catalogo: %d\nNome do Filme: %s\nGenero: %s\nAno: %d\n\n",
            filmes[i].numCatalogo, filmes[i].titulo, filmes[i].genero, filmes[i].ano);
	        printf("Este e o filme que deseja editar? [s/n]");
	        scanf("%c", &confirma);
	        if (confirma == 's'){
	            encontrado = 1;
		        break;
	        }
        }
    }

    if(encontrado == 1){
        printf("\nTitulo do Filme: ");
        fflush(stdin);
        while (getchar() != '\n');
        gets(filmes[i].titulo);
        printf("Genero do Filme: ");
        fflush(stdin);
        gets(filmes[i].genero);
        printf("Ano do Filme: ");
        scanf("%d", &filmes[i].ano);
        editado=1;
    }
    if(!encontrado) printf("\nNao foram encontrados filmes com este titulo!");

    if(editado) printf("\nFilme editado com sucesso!");
    else printf("\nHouve um erro que nem os programadores entenderam!");

//    sleep(800);    por que esse timer existe? Sei lá.
}

void excluirFilme(struct filme *filmes, int numCatalogo){
    int i, excluido=0;

    for ( i = 0; i < max; i++)
    {
        if(filmes[i].numCatalogo == numCatalogo){
            filmes[i].numCatalogo = 0 ;
            filmes[i].ano = 0 ;
            strcpy(filmes[i].titulo, "Nao Cadastrado!");
            strcpy(filmes[i].genero, "Nao Cadastrado!");
            excluido=1;
        }
    }

    if(excluido) printf("\nExcluido com Sucesso!");
    else printf("\nFilme nao encontrado");
}

void listarFilmes(struct filme *filmes, int filmesCadastrados){
    int i;

    if(!filmesCadastrados){
        printf("\nNenhum Filme Cadastrado.");
    }else{
        for ( i = 0; i < max; i++)
        {
                if(filmes[i].numCatalogo != 0){
                    printf("\n----------------------------------");
                    printf("\nNumero de Catalogo: %d\nNome do Filme: %s\nGenero: %s\nAno: %d",
                                    filmes[i].numCatalogo, filmes[i].titulo, filmes[i].genero, filmes[i].ano);
            }
        }
	printf("\n\nAcima estao os filmes cadastrados\nPressione qualquer tecla para voltar ao menu principal\n");
	getchar();
    }
}


    // Funcoes relacionadas a Locacao
void listarFilmesDisponiveis(){

}

void listarFilmesLocados(){

} 

void locarFilme(){

}

void devolverFilme(){

}
