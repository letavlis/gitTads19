
#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>
#include <time.h>

#define TAM 15
#define lin 20
#define col 50
#define nlin 15
#define ncol 30

typedef struct{
	char nome[20];
	int id;
	int point;
} JOGADOR;

int getch(void);

int enigma(int, int);

int main(){

	//jogador *tudo = malloc(30*sizeof(char)); 
	int a = 0, b, i, j, saida = 0, caminho = 0, entrada = 13, aux = 0, cont, cool, enig, ra, *pa;
	int mapa[lin][col];
	int c, fim, jogada, jogo , resp, flag = 0, high = 0, nhigh = 0;
	int resposconta, conta = 0, aleatorio, resposcontad, aleatoriod, existe = 0, p1, p2, p3 = 0, retorno;
	char responome[15], responome2[15], responomed[15], responomed2[15];
	int j_existe, *pontos_j, w, top;
	FILE *arq;
	FILE *arqb;
	FILE *file;
	FILE *fileb;
	JOGADOR p, pc;
	
	system("clear");
		
	printf("\n\n\n\n\n");
	sleep(1);
	printf("----\t");		printf("       -\t");		printf("-----\t");	printf("----\t");	printf("-----\t");	printf("----\t");	printf("---   --\n");		
	printf("----\t");		printf("      ---\t");		printf("--  --\t");	printf("----\t");	printf("--  --\t");	printf("----\t");	printf("----  --\n");	
	printf("----\t");		printf("     -   -\t");		printf("-----\t");	printf("----\t");	printf("-----\t");	printf("----\t");	printf("-- -- --\n");	
	printf("----\t");		printf("    --   --\t");	printf("-----\t");	printf("----\t");	printf("---\t");	printf("----\t");	printf("-- -- --\n");	
	printf("-------- ");	printf("  ---------\t");	printf("--  --\t");	printf("----\t");	printf("-- --\t");	printf("----\t");	printf("--  ----\n");	
	printf("-------- ");	printf(" -----  -----\t");	printf("------\t");	printf("----\t");	printf("--  --\t");	printf("----\t");	printf("--   ---\n");	

	printf("\n\n");
	printf("\n\t\tPressione Enter para iniciar");

	getchar();

	jogo = 1;// variavel para que eu consiga saber quando é o final do jogo	
	while(jogo != 0){//enquanto 
		
		if (jogo == 1){
			system("clear");
			printf("\tDificuldade\n(1)Normal\n(2)Difícil\n\nEscolhe ae pô\n\n");
			scanf("%i", &c);
			system("clear");				
		}

		if(c == 1){
			//para preencher o mapa
			for (i = 0; i < nlin; ++i){
				for (j = 0; j < ncol; ++j){
					mapa[i][j] = 1;
				}
			}
			
			cont = nlin -2;
			srand(time(NULL));	
			i = 0;
			j = 0;
			cool = 0;
			if(i == 0 && j == 0){
				i = 1+rand()%cont;
				aux = i;
				mapa[i][j] = entrada;
				j++;
				mapa[i][j] = caminho;
				
				do{
					i = 1+rand()%cont;				
					if(i == aux && j < ncol -2){
						j++;
						mapa[i][j] = caminho;
						aux = i;						
					}
					else if (i == aux-1 && mapa[i][j-1] != caminho){
						mapa[i][j] = caminho;
						aux = i;
						j = j;						
					}
					else if (i == aux+1 && mapa[i][j-1] != caminho){
						mapa[i][j] = caminho;
						aux = i;
						j = j;							
					}
					
				}while(j < ncol -2 );
				j++;
				mapa[i][j]=saida;

				//para contar quantos passos existem até o final
				for (i = 0; i < nlin; ++i){
					for (j = 0; j < ncol; ++j){
						if(mapa[i][j] == 0){
							cool++;
						}
					}
				}				
			}

			//mostra o mapa para o jogador
			system("clear");
			for (i = 0; i < nlin; ++i){
				for (j = 0; j < ncol; ++j){
					if(mapa[i][j] == 1){
						printf("# ");
					}
					else if(mapa[i][j] == 13){printf("❍ ");}
					else if(mapa[i][j] == 0){printf("  ");}
				}
				printf("\n");
			}
			system("sleep 03");
			fim = 0;
			cool = cool + 13;
			//começa o jogo
			do{	
				system("clear");
				printf("\n\t\t\t\t\tPassometro: %d \n", cool);
				for (i = 0; i < nlin; ++i){
					for (j = 0; j < ncol; ++j){
						if(mapa[i][j] == 13){
							printf("❍ ");

							if(j == ncol -1 && mapa[i][j] == 13){// quando a ultima coluna o mapa estiver preenchido com 13 chegou ao final
								fim = 1;
							}

							jogada = getch(); // captura a tecla

							if(jogada == 27) {//para poder utilizar as teclas direcionais
							jogada = getch(); 

								if(jogada == 91) {      
									jogada = getch();
									
									// CIMA
									if(jogada == 65 && mapa[i-1][j] == 0) {// só vai pra cima se o mapa na linha acima (i-1)da atual estiver preenchido com 0 
										mapa[i][j] = 0;
										i = i-1;
										mapa[i][j] = 13;
										cool--;
									}		
						  			// BAIXO
									else if(jogada == 66 && mapa[i+1][j] == 0) {// só vai pra baixo se o mapa na linha a baixo (i+1) da atual estiver preenchido com 0
							    		mapa[i][j] = 0;
										i = i+1;
										mapa[i][j] = 13;
										cool--;	
									}
									// DIREITA
									else if(jogada == 67 && mapa[i][j+1] == 0) {// só vai pra direita se o mapa na coluna a direita (j+1) da atual estiver preenchido com 0
										mapa[i][j] = 0;
										j = j+1;
										mapa[i][j] = 13;
										cool--;	
								    }
									// ESQUERDA
									else if(jogada == 68 && mapa[i][j-1] == 0 && j != 0) {// só vai pra esquerda se o mapa na coluna a esquerda (j-1) da atual estiver preenchido com 0
										mapa[i][j] = 0;
										j = j-1;
										mapa[i][j] = 13;
										cool--;
									}
								}
							}
						}
						else if(mapa[i][j] != 13){printf("  ");}
					}
					printf("\n");
				}
				
				if (cool == 0){
					fim = 2;
				}
			}while(fim == 0);

			system("clear");
			for (i = 0; i < nlin; ++i){//mostra o mapa com a posição final
				for (j = 0; j < ncol; ++j){
					if(mapa[i][j] == 1){
						printf("# ");
					}
					else if(mapa[i][j] == 13){printf("❍ ");}
					else if(mapa[i][j] == 0){printf("  ");}
				}
				printf("\n");
			}
			//fiz um ponteiro para fazer malloc em jogador, n sei se uso esse ponteiro(tudo) ou a struct (pessoa)
			//falta } pro primeiro if
			if(fim == 1){//se chegou ao final
				printf("\nPARABENS VOCE ACHOU A SAIDA! UHUUUL!!\n");
				printf("\nPassometro: %d\n", cool);
				system("sleep 05");

				arqb = fopen("cadastro.bin","a+b");
				//arq = fopen("HighScore Normal", "a+");	

				printf ("\nJá possui uma conta?(1)Sim(2)Não\n");
				scanf("%d", &resposconta);
				__fpurge(stdin);
				system("clear");
				//dando falha de segmentação depois do printf
				if ((resposconta = 1)){
					j_existe = 0;
					printf("\nDigite seu id 1: ");
					scanf("%d", &p1);
					//__fpurge(stdin);
					printf("\nteste1");
					retorno = fread(&p, sizeof(JOGADOR), 1, arqb);
					printf("\nteste2");
					while(retorno != 0){
						if(p1 == p.id){
							p.point = cool;
							j_existe = 1;
						}
						retorno = fread(&p, sizeof(JOGADOR), 1, arqb);
					}//while retorno
					printf("\nteste3");					
					rewind(arqb);
					w = 0;
					pontos_j = malloc(1 * sizeof(int));
					retorno = fread(&p, sizeof(JOGADOR), 1, arqb);
					while(retorno != 0){
						pontos_j[w] = p.point;
						w++;
						pontos_j = realloc(pontos_j,(w+1) * sizeof(int));
						
						retorno = fread(&p, sizeof(JOGADOR), 1, arqb);
					}//while retorno
					top = 0;
					for(i = 0; i < w; i++){
						if(pontos_j[i] < cool){
							top = 1;
						}
						else{
							top = 0;
							break;
						}
					}
					if(top == 1){
						printf ("\nTU É FODA MLK\nMAIOR SCORE DE TODOOOOS\n\t\t\t%d", cool);
					}
					
					if(j_existe == 0){
						printf("\n\tVoce nao possui cadastro.");
						resposconta = 2;		
					}	
				}
				fclose(arqb);
				arqb = fopen("cadastro.bin","a+b");
				if ((resposconta == 2) || (existe = 1)){
					
					do{
						existe = 0;
						printf("\nDigite seu id 2: ");
						scanf("%d", &p1);
						retorno = fread(&p, sizeof(JOGADOR), 1, arqb);
						while(retorno != 0){
							if(p1 == p.id){
								printf("\n\tID ja em uso. Tente outro");
								existe = 1;
								break;								
							}
							retorno = fread(&p, sizeof(JOGADOR), 1, arqb);
						}//while retorno
					}while(existe == 1);
						
						
						
						
						printf("\nDigite seu nome: ");
						__fpurge(stdin);					
						gets(nome_aux);
						strcpy(pc.nome,nome_aux);
						pc.id = p1;
						pc.point = cool;
						fwrite(&pc, sizeof(JOGADOR), 1, arqb);
						printf("\nSeu cadastro foi feito com sucesso");
						sleep(2);
						system("clear");
						existe = 0;
					}	
				
				fclose(arqb);			
			}			
			else if (fim == 2){
				printf("\n\nOH NÃO!! SEUS PASSOS ACABARAM\n\n");
				system("sleep 05");
			}

			do{
				system("clear");//mensagem de jogar novamente
				printf("\n\t\tjogar novamente? \n (1) SIM.\n (2) NÃO.\n\n");
				resp = getch();
				if (resp == 49){
					do{
						system("clear");// mensagem de trocar de difculdade
						printf("\n\t\t Trocar de dificuldade?\n (1) SIM.\n (2) NÃO.\n\n");
						resp = getch();
						if (resp == 49){jogo = 1;}//49 na tabela ascii é o número 1// jogo == 1 significa que ira voltar ao menu para pessoa escolher o nivel
						else if( resp == 50){
							jogo++;
							c = 49;
						}// 50 é o numero 2// c == 1 significa que voltou a parte do codigo que é referente ao nivel normal
						else { printf("\nOpção invalida tente novamente");}
					}while(resp != 49 && resp != 50);// mostrar a mensagem enquanto não for digitao um numero valido 
				}
				else if(resp == 50){ jogo = 0;}
				else { printf("\nOpção invalida tente novamente");}
			}while(resp != 49 && resp != 50);// mostrar a mensagem enquanto não for digitao um numero valido
		}

		else if(c == 2){// nivel dificil
			//para preencher o mapa// preenche novamente para que os valores contidos dentro da matriz voltem  ao inicio caso escolha jogar novamente
			for (i = 0; i < lin; ++i){
				for (j = 0; j < col; ++j){
					mapa[i][j] = 1;
				}
			}
			//mapa aleatório
			cont = lin -2;
			srand(time(NULL));	
			i = 0;
			j = 0;
			cool = 0;
			if(i == 0 && j == 0){
				i = 1+rand()%cont;
				aux = i;
				mapa[i][j] = entrada;
				j++;
				mapa[i][j] = caminho;

				do{
					i = 1+rand()%cont;				
					if(i == aux && j < col -2){
						j++;
						mapa[i][j] = caminho;
						aux = i;
					}
					else if (i == aux-1 && mapa[i][j-1]!=caminho){
						mapa[i][j] = caminho;
						aux = i;
						j = j;
					}
					else if (i == aux+1 && mapa[i][j-1]!=caminho){
						mapa[i][j] = caminho;
						aux = i;
						j = j;
					}
				}while(j < col -2 );
				j++;
				mapa[i][j]=saida;
			}

			for (i = 0; i < lin; ++i){
				for (j = 0; j < col; ++j){
					if(mapa[i][j] == 0){
						cool++;
					}
				}
			}

			//mostra o mapa para o jogador
			system("clear");
			for (i = 0; i < lin; ++i){
				for (j = 0; j < col; ++j){
					if(mapa[i][j] == 1){
						printf("# ");
					}
					else if(mapa[i][j] == 13){printf("❍ ");}
					else if(mapa[i][j] == 0){printf("  ");}
				}
				printf("\n");
			}
			system("sleep 02");
			fim = 0;
			cool = cool + 9;
			//começa o jogo // mesma coisa do modo normal só mundando algumas variaveis pra compreender um mapa maior (vide define)
			do{				
				system("clear");
				printf("\n\t\t\t\t\tPassometro: %d \n", cool);
				for (i = 0; i < lin; ++i){
					for (j = 0; j < col; ++j){
						if(mapa[i][j] == 13){
							printf("❍ ");

							if(j == col -1 && mapa[i][j] == 13){
								fim = 1;
							}

							jogada = getch();

							if(jogada == 27) {
							jogada = getch(); 

								if(jogada == 91) {      
									jogada = getch();
									
									// CIMA
									if(jogada == 65 && mapa[i-1][j] == 0) {
										mapa[i][j] = 0;
										i = i-1;
										mapa[i][j] = 13;
										cool--;										
									}		
						  			// BAIXO
									else if(jogada == 66 && mapa[i+1][j] == 0) {
							    		mapa[i][j] = 0;
										i = i+1;
										mapa[i][j] = 13;
										cool--;	
									}
									// DIREITA
									else if(jogada == 67 && mapa[i][j+1] == 0) {
										mapa[i][j] = 0;
										j = j+1;
										mapa[i][j] = 13;
										cool--;	
								    }
									// ESQUERDA
									else if(jogada == 68 && mapa[i][j-1] == 0 && j != 0) {
										mapa[i][j] = 0;
										j = j-1;
										mapa[i][j] = 13;
										cool--;
									}
								}
							}
						}
						else if(mapa[i][j] != 13){printf("  ");}
						if((mapa[i][j] == 13 && mapa[i][j-1] != 0 && mapa[i][j+1] != 0) && (mapa[i-1][j] != 0 || mapa[i+1][j] != 0)){
							flag = 1;
						}
					}
					printf("\n");
				}
								
				if (flag == 1){
					system("clear");
					srand(time(NULL));
					enig = rand()%5;
					cool = enigma(enig, cool);
					flag = 0;					
				}
				
			}while(fim == 0);

			system("clear");
			for (i = 0; i < lin; ++i){
				for (j = 0; j < col; ++j){
					if(mapa[i][j] == 1){
						printf("# ");
					}
					else if(mapa[i][j] == 13){printf("❍ ");}
					else if(mapa[i][j] == 0){printf("  ");}
				}
				printf("\n");
			}

			if(fim == 1){//se chegou ao final
				printf("\nPARABENS VOCE ACHOU A SAIDA! UHUUUL!!\n");
				printf("\nPassometro: %d\n", cool);
				system("sleep 05");	
				printf ("\nJá possui uma conta?(1)Sim(2)Não\n");
				scanf("%d", &resposcontad);
				__fpurge(stdin);
				system("clear");
				if ((resposcontad = 1)){
					arqb = fopen("cadastro.bin","a+b");
					printf("\nDigite seu id 3: ");
					scanf("%d", &p1);
					__fpurge(stdin);
					if(p1 == p.id){
						fprintf(arqb,"%d", p1);
						p.id = p1;
					}
					do{
						pa = malloc(30*sizeof(int));
						fscanf(file, "%d", &pa);
						file = fopen("HighScore Difícil", "a+");
						if (cool > pa){
							printf ("\nTU É FODA MLK\nMAIOR SCORE DE TODOOOOS\n\t\t\t%d", cool);
						}
					}while(pa =! EOF);
					fprintf(file, "%d", cool);
					fclose(file);
					fclose(arqb);	
				}
				else if ((resposcontad == 2) || (existe = 1)){
					arqb = fopen("cadastro.bin","a+b");
					printf("\nDigite seu id 4: ");
					scanf("%d", &p1);
					__fpurge(stdin);
					//procurar id
					p2 = p1;
					p1 = p3;
					if(p2 == p1){
						printf ("\nEsse nome já existe");
						sleep(2);
						system("clear");
						existe = 1;
					}
					else if (p2 != p1){
						p2 = p3;
						fprintf(arqb,"%d", p1);
						//salvar point na struct
						p.id = p2;
						printf("\nSeu cadastro foi feito com sucesso");
						sleep(2);
						system("clear");
						existe = 0;
					}	
					file = fopen("HighScore Difícil","a+");
					fprintf(file,"%d", cool);
					do{
						pa = malloc(30*sizeof(int));
						fscanf(file, "%d", &pa);
						if (cool > pa){
							printf ("\nTU É FODA MLK\nMAIOR SCORE DE TODOOOOS\n\t\t\t%d", cool);
						}
					}while(pa =! EOF);
					fclose(file);
					fclose(arqb);
				}			
			}				
			else if (fim == 2){
				printf("\n\nOH NÃO!! SEUS PASSOS ACABARAM\n\n");
				system("sleep 05");
			}			
			do{
				system("clear");
				printf("\n\t\tjogar novamente? \n (1) SIM.\n (2) NÃO.\n\n");
				resp = getch();
				if (resp == 49){
					do{
						system("clear");
						printf("\n\t\t Trocar de dificuldade?\n (1) SIM.\n (2) NÃO.\n\n");
						resp = getch();
						if (resp == 49){jogo = 1;}
						else if( resp == 50){jogo++; c = 2;}
						else { printf("\nOpção invalida tente novamente");}
					}while(resp != 49 && resp != 50);
				}
				else if(resp == 50){ jogo = 0;}
				else { printf("\nOpção invalida tente novamente");}
			}while(resp != 49 && resp != 50);
		}
		else{
			printf("\nAlgo foi digitado errado");
			jogo = 1;
		}
	}	
	return 0;
}
int getch(void) {

    struct termios oldattr, newattr;
    int ch;

    tcgetattr( STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO);
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr);
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr);

    return ch;
}
int enigma(int enig, int passos){
	char *resposta = malloc(10*sizeof(char));

	if(enig == 0){
		system("sleep 01");
		printf("\n");
		printf("\n\t\t\tVOCE CAIU NO ENIGMA!!\n\n\n");
		printf("\n\t\t\tNão utilize acentos\n\n");
		printf("\n\t\t------------------------------------------------");
		printf("\n\t\t--.- ..- .- .-.. / .- / -.-. .. -.. .- -.. . / ");
		printf("\n\t\t-- .- .. ... / .- -. - .. --. .- / ");
		printf("\n\t\t-.. --- / -- ..- -. -.. --- ..--..");
		printf("\n\t\t------------------------------------------------");
		printf("\n\n\t\t\tDica: Palestina!");
		printf("\n\n\t\t\tDigite a respostas: ");
		gets(resposta);
		__fpurge(stdin);
		if(((strcmp(resposta, "Jerico")) == 0)||((strcmp(resposta, "jerico") == 0))){
			passos = passos + 5;
			printf("\n\nUHUUUUL VOCE ACERTOU!! TOMA AQUI 5 PASSOS EXTRAS");
			system("sleep 03");	
		}
		else{
			passos = passos - 3;
			printf("\n\n ERROOOOOOOOOWW!! FIZEMOS UM CONTINGENCIAMENTO NOS SEUS PASSOS (- 3)");
			system("sleep 03");
		}
		return passos;
	}
	else if (enig == 1){		
		system("sleep 01");
		printf("\n");
		printf("\n\t\t\tVOCE CAIU NO ENIGMA!!\n\n\n");
		printf("\n\t\t\tNão utilize acentos\n\n");
		printf("\n\t\t\t---------------------------------------");
		printf("\n\t\t\t\"Tornamo-nos odiados tanto fazendo o ");
		printf("\n\t\t\tbem como fazendo o mal.\"");
		printf("\n\t\t\t---------------------------------------");
		printf("\n\n\t\t\tDica: O principe");
		printf("\n\n\t\t\tDigite a respostas: ");
		gets(resposta);
		__fpurge(stdin);
		if(((strcmp(resposta, "Maquiavel")) == 0)||((strcmp(resposta, "maquiavel") == 0))){
			passos = passos + 2;
			printf("\n\nUHUUUUL VOCE ACERTOU!! TOMA AQUI 2 PASSOS EXTRAS");	
			system("sleep 03");	
		}
		else{
			passos = passos - 3;
			printf("\n\n ERROOOOOOOOOWW!! FIZEMOS UM CONTINGENCIAMENTO NOS SEUS PASSOS (- 3)");
			system("sleep 03");
		}
		return passos;
	}
	else if (enig == 2){
		system("sleep 01");
		printf("\n");
		printf("\n\t\t\tVOCE CAIU NO ENIGMA!!\n\n\n");
		printf("\n\t\t\tNão utilize acentos\n\n");
		printf("\n\t\t\t------------------------------------------");
		printf("\n\t\t\t\"Os oito de nós não avançam para ");
		printf("\n\t\t\tproteger o nosso rei de um ataque inimigo. \"");
		printf("\n\t\t\t------------------------------------------");
		printf("\n\n\t\t\tDica: xeque!");
		printf("\n\n\t\t\tDigite a respostas: ");
		gets(resposta);
		__fpurge(stdin);
		if(((strcmp(resposta, "Peoes")) == 0)||((strcmp(resposta, "peoes") == 0))){
			passos = passos + 2;
			printf("\n\nUHUUUUL VOCE ACERTOU!! TOMA AQUI 2 PASSOS EXTRAS");
			system("sleep 03");	
		}
		else{
			passos = passos - 3;
			printf("\n\n ERROOOOOOOOOWW!! FIZEMOS UM CONTINGENCIAMENTO NOS SEUS PASSOS (- 3)");
			system("sleep 03");
		}
		return passos;	
	}
	else if (enig == 3){
		system("sleep 01");
		printf("\n");
		printf("\n\t\t\tVOCE CAIU NO ENIGMA!!\n\n\n");
		printf("\n\t\t\tNão utilize acentos\n\n");
		printf("\n\t\t\t-------------------------------");
		printf("\n\t\t\tTMAC OSCP AMLRGLSYP?");
		printf("\n\t\t\t-------------------------------");
		printf("\n\n\t\t\tDica: Cifra de cesar!");
		printf("\n\n\t\t\tDigite a respostas: ");
		gets(resposta);
		__fpurge(stdin);
		if(((strcmp(resposta, "Sim")) == 0)||((strcmp(resposta, "sim") == 0))){
			passos = passos + 4;
			printf("\n\nUHUUUUL VOCE ACERTOU!! TOMA AQUI 4 PASSOS EXTRAS");
			system("sleep 03");	
		}
		else{
			passos = passos - 3;
			printf("\n\n ERROOOOOOOOOWW!! FIZEMOS UM CONTINGENCIAMENTO NOS SEUS PASSOS (- 3)");
			system("sleep 03");
		}
		return passos;
	}
	else if (enig == 4){
		system("sleep 01");
		printf("\n");
		printf("\n\t\t\tVOCE CAIU NO ENIGMA!!\n\n\n");
		printf("\n\t\t\tNão utilize acentos\n\n");
		printf("\n\t\t\t---------------------------------------");
		printf("\n\t\t\t\"00101101 00110010 00110101 00101110 ");
		printf("\n\t\t\t00110101 00111000 00110101 00110011 ");
		printf("\n\t\t\t00110010 00110111 00110000 00110101 ");
		printf("\n\t\t\t00101100 00100000 00101101 00110100 ");
		printf("\n\t\t\t00111000 00101110 00110101 00110110 ");
		printf("\n\t\t\t00110101 00110001 00110100 00111001 ");
		printf("\n\t\t\t00110011 00110001 ");
		printf("\n\t\t\t---------------------------------------");
		printf("\n\n\t\t\tDica: Tabela ASCII + pesquisa no google mané!");
		printf("\n\n\t\t\tDigite a respostas: ");
		gets(resposta);
		__fpurge(stdin);
		if((strcmp(resposta, "IFPR")) == 0){
			passos = passos + 5;
			printf("\n\nUHUUUUL VOCE ACERTOU!! TOMA AQUI 5 PASSOS EXTRAS");
			system("sleep 03");	
		}
		else{
			passos = passos - 3;
			printf("\n\n ERROOOOOOOOOWW!! FIZEMOS UM CONTINGENCIAMENTO NOS SEUS PASSOS (- 3)");
			system("sleep 03");
		}
		return passos;
	}
	return 0;
}
