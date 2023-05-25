#include <locale.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct produtos {

  char jogo[50];
  char prod[50];
  int qtd;
  float preco;
  
  

} game;
// funcao  string.h
int strcmp(const char *str1, const char *str2) {

  int diferente = 0;

  for (int i = 0; (str1[i] != '\0' || str2[i] != '\0'); i++) {

    if (str1[i] != str2[i]) {

      diferente = 1;

      // fim if
    }


    // fim for
  }

  return (diferente);
  // fim função
}

void Inserir(FILE *p, game *c) {
  // abre file acrescentar
  if ((p = fopen("game.txt", "a")) == NULL) {
    printf("erro na abertura do arquivo \n");
    exit(0); /*encerra o programa e volta ao sistema operacional*/
  }
    
  getchar();
    printf("\nDigite o Nome do jogo: ");
    gets(c->jogo);
    printf("\nDigite o Nome da produtora: ");
    gets( c->prod);
    printf("\nDigite o Preço do jogo: ");
    scanf("%f", &c->preco);
    printf("\nDigite a Quantidade Inicial do jogo: ");
    scanf("%d", &c->qtd);
    

    // gravar
    
    fwrite(c, sizeof(*c), 1, p);
  
    
    
 

  // fecha file escrita
  fclose(p);
  // fim pro
}
void Listar(FILE *file, game *c){
   
  // abre file leitura
     
  if ((file = fopen("game.txt", "r")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

    //ler e listar
    int i = 0;
    while ( fread(c, sizeof(*c), 1, file) != 0) {
    
       if(*c->jogo != 0){
      printf("\n ____________________________ ");
      printf("\n| %d° \n| Jogo: %s\n| Produtora: %s\n| Preço: %.2f \n|Quantidade: %d", i+1,c->jogo, c->prod, c->preco, c->qtd);
       printf("\n|____________________________|");

         i++;
         //fim if
       }
    // fim while
  }
 
  
    // fecha file leitura
    fclose(file);
  //fim proc
}
void PesquisaJogo( FILE *file, game *c){
     
 
  if ((file = fopen("game.txt", "r")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

  //perguntar
  char pesq[50];
  char *p = &pesq[0];
  int enc =0;
  //ecvita bug
  getchar();
  printf("\nDigite o nome do jogo: ");
  gets(p);
  
  
    //fazer pesquisa
   while(fread(c, sizeof(*c), 1, file) != 0)
  {
   if(strcmp(c->jogo, pesq) == 0){
     
     printf("\n ____________________________ ");
       printf("\n| Jogo: %s\n| Produtora: %s\n| Preco: %f \n|Quantidade: %d", c->jogo, c->prod,c->preco, c->qtd);
       printf("\n|____________________________|");
      enc =1;
      //fim if
    }

    //fim while
  }
    if(enc == 0)
    printf("\nJogo não encontrado!");
  
 
  
  fclose(file);
  //fim proc
}
void PesquisaProdutora( FILE *file, game *c){
     
 
  if ((file = fopen("game.txt", "r")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

  //perguntar
  char pesq[50];
  char *p = &pesq[0];
  int enc =0;
  //evita bug
  getchar();
  printf("\nDigite o nome da produtora: ");
  gets( p);
  
  
    //fazer pesquisa
 
   while(fread(c, sizeof(*c), 1, file) != 0)
  {
    
    if(strcmp(c->prod, pesq) == 0){
     
     printf("\n ____________________________ ");
       printf("\n| Jogo: %s\n| Produtora: %s\n| Preco: %f \n|Quantidade: %d", c->jogo, c->prod,c->preco, c->qtd);
       printf("\n|____________________________|");
      enc =1;
      //fim if
    }
    //fim while
    
  }
  if(enc == 0)
    printf("\nProdutora não encontrado!");
  
 
  
  fclose(file);
  //fim proc
}
void PesquisaPreco( FILE *file, game *c){ 

  int enc=0;
  if ((file = fopen("game.txt", "r")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }
  //variaveis min e max
  float min, max;
  printf("\nDigite o preço inicial: ");
  scanf("%f", &min);
   printf("\nDigite o preço máximo: ");
  scanf("%f", &max);

   while(fread(c, sizeof(*c), 1, file) != 0)
  {
    
    if(c->preco >= min && c->preco <= max){
     
     printf("\n ____________________________ ");
       printf("\n| Jogo: %s\n| Produtora: %s\n| Preco: %.2f \n|Quantidade: %d", c->jogo, c->prod,c->preco, c->qtd);
       printf("\n|____________________________|");
      enc =1;
      //fim if
    }
    //fim while
    
  }
  if(enc == 0){
    printf("\nNenhum Jogo encontrado com essa faixa de preço");
  }
  



}
void AlterarQtd( FILE *file, game *c){
     
    // abre file leitura
     
  if ((file = fopen("game.txt", "r+")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

  //perguntar
  char pesq[50];
  char *p = &pesq[0];
  int a =0, es, enc =0;

  //evita bug
  getchar();
  printf("\nDigite o nome do jogo: ");
  gets( p);
  
  
    //fazer pesquisa
   for(int i = 0;fread(c, sizeof(*c), 1, file) != 0; i++)
  {
    
    if(strcmp(c->jogo, pesq) == 0){
        
    
    printf("\nDigite a Entrada(números positivos) ou Saída('-' Números negativos) do produto: ");
    scanf("%d", &es);

      c->qtd = c->qtd + es;
      if (c->qtd < 0){
        //nao existir prod negativo
         c->qtd = 0;
      }
      a = i * sizeof(*c);
        fseek(file,a, SEEK_SET);
     fwrite(c, sizeof(*c), 1, file);
      
      enc =1;
      //fim if
    }

    //fim for
  }
    if(enc == 0)
    printf("\nJogo não encontrado!");
  
  
  fclose(file);
  //fim proc
}
void AlterarPreco( FILE *file, game *c){
     
    // abre file leitura
     
  if ((file = fopen("game.txt", "r+")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

  //perguntar
  char pesq[50];
  char *p = &pesq[0];
  int a =0, enc = 0;
  //evita bug
  getchar();
  printf("\nDigite o nome do jogo: ");
  gets( p);
  
  
    //fazer pesquisa
   for(int i = 0;fread(c, sizeof(*c), 1, file) != 0; i++)
  {
    
    if(strcmp(c->jogo, pesq) == 0){
        
     
    printf("\nDigite o novo Preço do produto: ");
   scanf("%f", &c->preco);

      a = i * sizeof(*c);
        fseek(file,a, SEEK_SET);
     fwrite(c, sizeof(*c), 1, file);
      
      enc =1;
      //fim if
    }

    //fim for
  }
    if(enc == 0)
    printf("\nJogo não encontrado!");
  
  
  fclose(file);
  //fim proc
}
void Alterar( FILE *file, game *c){
     
    // abre file leitura
     
  if ((file = fopen("game.txt", "r+")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

  //perguntar
  char pesq[50];
  char *p = &pesq[0];
  int a =0, enc =0;

  //evita bug
  getchar();
  printf("\nDigite o nome do jogo: ");
  gets( p);
  
  
    //fazer pesquisa
   for(int i = 0;fread(c, sizeof(*c), 1, file) != 0; i++)
  {
    
    if(strcmp(c->jogo, pesq) == 0){
        
     printf("\nDigite o novo Nome do jogo: ");
    gets( c->jogo);
    printf("\nDigite o novo Nome da produtora: ");
    gets( c->prod);

      a = i * sizeof(*c);
        fseek(file,a, SEEK_SET);
     fwrite(c, sizeof(*c), 1, file);
      
      enc =1;
      //fim if
    }

    //fim for
  }
    if(enc == 0)
    printf("\nJogo não encontrado!");
  
  
  fclose(file);
  //fim proc
}
void Excluir( FILE *file, game *c){
     
    // abre file leitura
     
  if ((file = fopen("game.txt", "r+")) == NULL) {
      printf("erro na abertura do arquivo \n");
      exit(0); /*encerra o programa e volta ao sistema operacional*/
    }

  //perguntar
  char pesq[50];
  char *p = &pesq[0];
  int a =0, enc =0;
  //evita bug
  getchar();
  printf("\nDigite o nome do jogo: ");
   gets( p);
  
  
    //fazer pesquisa
   for(int i = 0;fread(c, sizeof(*c), 1, file) != 0; i++)
  {
    
    if(strcmp(c->jogo, pesq) == 0){
        
      *c->jogo = 0;
      *c->prod = 0;
        c->preco = -10;
       c->qtd = -1;
      
      a = i * sizeof(*c);
        fseek(file,a, SEEK_SET);
     fwrite(c, sizeof(*c), 1, file);
      
      enc =1;
      //fim if
    }

    //fim for
  }
    if(enc == 0)
    printf("\nJogo não encontrado!");
  
  
  fclose(file);
  //fim proc
}
int main() // principais do main  
{
   // entrada      
  FILE *p;
 game cada;
  game *pjg = &cada;
  // entrada      
  int escolhaMenu, saida = 0;
  char a='|';
  // para o usuário escolher sair   
  do {

    // inicio projeto       
    do {
      // alimentação
      system("cls");
      printf("\nBem Vindo \nDeseja fazer:\n -------------------------------------\n|1 - Entrada de Dados   %15c|\n|2 - Listar Dados       %15c|\n|3 - Pesquisa jogo      %15c|\n|4 - Pesquisar Produtora%15c|\n|5 - Pesquisa jogo por faixa de preço %1c|\n|6 - Alterar Quantidade %15c|\n|7 - Alterar Preço      %15c|\n|8 - Alterar Dados      %15c|\n|9 - Excluir Dados    %17c|\n|10 - Sair              %15c|\n|_____________________________________||\n",a,a,a,a,a,a,a,a,a,a);
      scanf("%d", &escolhaMenu);

      if (escolhaMenu > 10 || escolhaMenu < 1) {

        printf("Erro! Opção Inválida");
      }
    } while (escolhaMenu > 10 || escolhaMenu < 1);
    // função
    switch (escolhaMenu) {
    // 1 entrada de dados
    case 1: {
      // chama funcao
      Inserir(p, pjg);
      // fim case
      break;
    }

    // 2 listar de dados
    case 2: {
      // chama funcao
      Listar(p, pjg);
      // fim case
      break;
    }
    // 3 pesquisa jogo
    case 3: {
      // chama funcao
      PesquisaJogo(p, pjg);
      // fim case
      break;
    }
    // 4 pesquisa produtora
    case 4: {
      // chama funcao
      PesquisaProdutora(p, pjg);
      // fim case
      break;
    }
    // 5 pesquisa preço
    case 5: {
      // chama funcao
      PesquisaPreco(p, pjg);
      // fim case
      break;
    }
     // alterar quantidade do jogo
    case 6: {
      // chama funcao
      AlterarQtd(p, pjg);
      // fim case
      break;
    }
       // alterar preço
    case 7: {
      // chama funcao
      AlterarPreco(p, pjg);
      // fim case
      break;
    }
     // alterar jogo
    case 8: {
      // chama funcao
      Alterar(p, pjg);
      // fim case
      break;
    }
    // excluir
    case 9: {
      // chama funcao
      Excluir(p, pjg);
      // fim case
      break;
    }
    
   
      // fim switch
    }
  } while (escolhaMenu != 10);

  printf("Obrigado por utilizar o programa");
}
