#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <locale.h>

int destino, origem, vertices = 0;
float *custos = NULL;
float custo = 0;
float G_VAL = 6.596; //Valor médio da gasolina

void dijkstra(int vertices, int origem, int destino, float *custos) {
	setlocale(LC_ALL, "Portuguese");
	int i, v, cont = 0;
	int* ant, * tmp;
	int* z;
	double min;
	double dist[vertices];

	ant = (int*)calloc(vertices, sizeof(int*));
	tmp = (int*)calloc(vertices, sizeof(int*));
	z = (int*)calloc(vertices, sizeof(int*));

	for (i = 0; i < vertices; i++) {
		
		if (custos[(origem - 1) * vertices + i] != -1) {
			ant[i] = origem - 1;
			dist[i] = custos[(origem - 1) * vertices + i];
		}
		else {	
			ant[i] = -1;
			dist[i] = HUGE_VAL;
		}

		z[i] = 0;	
	}


	z[origem - 1] = 1;
	dist[origem - 1] = 0;

	
	do {
		//Encontrando o menor valor para z (caminho ideal)
		min = HUGE_VAL;	

		for (i = 0; i < vertices; i++) {
			if (!z[i]) {	
				if (dist[i] >= 0 && dist[i] < min) {	
					min = dist[i];	
					v = i;
				}
			}
		}

		if (min != HUGE_VAL && v != destino - 1) {
			z[v] = 1;

			for (i = 0; i < vertices; i++) {
				if (!z[i]) {
					if (custos[v * vertices + i] != -1 && dist[v] + custos[v * vertices + i] < dist[i]) {
						dist[i] = dist[v] + custos[v * vertices + i];
						ant[i] = v;
					}
				}
			}
		}
	} while (v != destino - 1 && min != HUGE_VAL);
	

	printf("De %d para %d: ", origem, destino);
	if (min == HUGE_VAL) {
		printf("Nao Existe\t");
		printf("\t | Custo: - \n");
	}
	else { 
		i = destino;
		i = ant[i - 1];

		while (i != -1) {
			tmp[cont] = i + 1;
			cont++;
			i = ant[i];
		}

		for (i = cont; i > 0; i--) {
			printf("%d -> ", tmp[i - 1]);
		}

		printf("%d", destino);
		printf("\t | Custo: %.3f\n", dist[destino - 1]);
	}
}

void grafo_inicializar() {
	int i;
	
	do {
		printf("Informe o numero de vertices (minimo de 3, no mapa o valor fixo e 5): ");
		scanf("%d", &vertices);
	} while (vertices < 3);
	
	custos = (float*)malloc(sizeof(float)*vertices*vertices);
	
	for (i = 0; i < vertices * vertices; i++) {
		custos[i] = -1;
	}
	
	do {
		printf("Entre com as arestas: ");
		
		
		do {
			printf("Origem entre 1 e %d ou '0' para sair: ", vertices);
			scanf("%d", &origem);
		} while(origem < 0 || origem > vertices);
		printf("\n");
		
		if (origem) {
			do {
				printf("Destino entre 1 e %d (menos %d) ou '0' para sair: ", vertices, origem);
				scanf("%d", &destino);
			} while (destino < 1 || destino > vertices || destino == origem);
			printf("\n");
		
			do {
				printf("Custo (positivo) do vertice %d para op vertice %d (DIGITAR O RA CADA DIGITO POR VEZ E O PROGRAMA FARA O CALCULO COM O VALOR MEDIO DA GASOLINA AUTOMATICAMENTE): ", origem, destino);
				scanf("%f", &custo);
			} while(custo < 0);
		
			custos[(origem-1) * vertices + (destino - 1)] = (float)custo*G_VAL;
			printf("\n");
		}
	} while(origem);
}

void grafo_procurar() {
	int i, j;

	for (i = 1; i <= vertices; i++) {
		for (j = 1; j <= vertices; j++) {
			dijkstra(vertices, i, j, custos);
		}
		printf("\n");
	}
}

int main() {
	printf("\n-=-=-=--=-=-=-=-=-=-=-=-=-=-| PROGRAMA FINAL - MAPA EDI - ALGORTIMO DE DIJKSTRA |=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=\n");
	grafo_inicializar();
	grafo_procurar();	
	
	return 0;
}
