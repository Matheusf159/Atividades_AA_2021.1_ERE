#include <stdio.h>
#include <stdlib.h>
#include <time.h>


//ALGORITMO DE ORDENACAO INSERTION SORT
void insertionSort(int *v, int j){
    int i, n, aux;
    for(i = 0; i < j; i++){
        aux = v[i];
        for(n = i; (n > 0) && (aux < v[n - 1]); n--)
            v[n] = v[n - 1];
        v[n] = aux;
    }
}

//ALGORITMO DE ORDENACAO BUBBLESORT
void BubbleSort(int *vet, int tam){
    int aux, i, j;
    for(i = 0; i < tam; i++){
        for(j = 0; j < tam-1; j++){
            if (vet[j] > vet[j + 1]){
                aux = vet[j];
                vet[j] = vet[j + 1];
                vet[j + 1] = aux;
            }
        }
    }
}

//ALGORITMO DE ORDENACAO QUICK SORT
void QuickSort(int *v, int inicio, int fim){
    int pivo;
    if(fim > inicio){
        pivo = Particiona(v, inicio, fim);
        QuickSort(v, inicio, pivo-1);
        QuickSort(v, pivo+1, fim);
    }
}
//PARTICIONAMENTO DO QUICK SORT
int Particiona(int *v, int inicio, int fim){
    int esq, dir, pivo, aux;
    esq  = inicio;
    dir = fim;
    pivo = v[inicio];

    while(esq < dir){
        while(esq <= fim && v[esq] <= pivo)
            esq++;

        while(dir >= 0 && v[dir] > pivo)
            dir--;
        if(esq < dir){
            aux = v[esq];
            v[esq] = v[dir];
            v[dir] = aux;
            }
    }
    v[inicio] = v[dir];
    v[dir] = pivo;
    return dir;
}

//ALGORITMO DE ORDENACAO MARGE SORT
void MergeSort(int *v, int p, int r){
    if(p < r - 1){
        int q = (p+r)/2;
        MergeSort(v, p, q);
        MergeSort(v, q, r);
        IntercalaMerge(v, p, q, r);
    }
}
//INTERCALAMENTO DO MERGE SORTE
void IntercalaMerge(int *v, int p, int q, int r){
    int i, j, k, *w;
    w = (int*)malloc((r-p)*sizeof(int));
    i = p;
    j = q;
    k = 0;

    while(i < q && j < r){
        if(v[i] <= v[j])
            w[k++] = v[i++];
        else
            w[k++] = v[j++];
    }

    while(i < q){
        w[k++] = v[i++];
    }
    while(j < r)
        w[k++] = v[j++];
    for(i = p; i < r; i++)
        v[i] = w[i-p];
    free(w);
}


int main(){
    //Variavel
    int a, op = 0, i, cont = 0, n = 0, elem, m;
    //Variavel do arquivo
    FILE *arquivo;
    //Variaveis para calcular o tempo de execucao
    clock_t sel, bub, ins, mer, qui, hea, rad;
    //Variaveis char
    char nome[50], nome1[50], nome2[50], nome3[50], name[50];
    //Ponteiros para armazenar os valores
    int *vet, *vet1, *vet2, *vet3, *vet4, *vet5, *vet6, *vet7, *vet8, *vet9;


    printf("=== PROJETO ORDENACAO ===\n");
    printf("1 - Gerar arquivo\n2 - Ordenar arquivo\n3 - Buscar \n0 - Sair\n");
    printf("Opcao: ");
    scanf("%d", &op);

    while(op != 0){
        //CRIACAO DO ARQUIVO
        if(op == 1){
            printf("Nome do Arquivo :");
            scanf("%s", nome1); //nome que sera dado ao arquivo
            sprintf(nome, "%s.txt", nome1); //atribuicao do nome para o arquivo
            arquivo = fopen(nome, "w"); //criacao do arquivo

            printf("\nEscolha o TAMANHO DO VETOR\n");
            scanf("%d", &a);
            vet =(int*)malloc(a*sizeof(int));
            printf("\n");
            srand( time(NULL) );//funcao que ira gerar valores aleatorios

            //os valores aleatorios serao armazenado no vet
            for (int i = 0; i < a; i++){
                vet[i] = (rand() % 100);
            }
            //os valores que estao no vet irao ser armazenados no arquivo
            for(int k = 0; k < a; k++){
                fprintf(arquivo," %d ",vet[k]);
            }

            fclose(arquivo);//fechar o arquivo

            printf("Arquivo de %d numeros criado com sucesso!\n", a);

            printf("\n=== PROJETO ORDENACAO ===\n");
            printf("1 - Gerar arquivo\n2 - Ordenar arquivo\n3 - Buscar \n0 - Sair\n");
            printf("Opcao: ");
            scanf("%d", &op);
        }

        //ORDENARCAO DO ARQUIVO
        if(op == 2){
            printf("\n--Ordenando Arquivo--\n");
            n = 0;
            printf("Qual arquivo deseja ordenar: ");//o usuario ira digitar o nome do arquivo
            scanf("%s", nome1);
            sprintf(nome,"%s.txt", nome1);
            arquivo = fopen(nome, "r"); //o arquivo sera aberto para leitura

            if(arquivo == NULL)//ira verificar se o arquivo existe
                printf("Arquivo nao encontrado!\n");

            else{
                //alocacao dos vet's para nao perder os valores na hora da ordenacao
                vet1 = (int*)malloc(100001*sizeof(int));
                vet2 = (int*)malloc(100001*sizeof(int));
                vet3 = (int*)malloc(100001*sizeof(int));
                vet5 = (int*)malloc(100001*sizeof(int));
                vet6 = (int*)malloc(100001*sizeof(int));

                //ira percorrer o arquivo e armazenar os valores em vet1
                while(arquivo != NULL && !feof(arquivo)){
                    fscanf(arquivo, "%d", &vet1[n]);
                    n++;
                }
                //esse for serve para clonar o vet1 nos outros vet's
                for(int p = 0; p < n-1; p++){
                    vet2[p] = vet1[p];
                    vet3[p] = vet1[p];
                    vet5[p] = vet1[p];
                    vet6[p] = vet1[p];
                }

                //ORDENACAO COM INSERTIONSORT
                //ira criar um arquivo para salvar os valores ordenados pelo insertion sort
                sprintf(nome, "%s-InsertionSort.txt", nome1);
                arquivo = fopen(nome, "w");

                ins = clock();
                insertionSort(vet3, n-1); //ordenacao do vet3 pelo insertion sort
                ins = clock() - ins; //calculo do tempo do insertion sort

                //ira armazenar os valores ordenados do vet3 pelo insertion sort no arquivo
                for(int r = 0; r < n-1; r++){
                    fprintf(arquivo, " %d ",vet3[r]);

                }

                fclose(arquivo);//fechar arquivo

                //ORDENACAO COM BUBBLESORT
                //ira criar um arquivo para salvar os valores ordenados pelo bubblesort
                sprintf(nome, "%s-BubbleSort.txt", nome1);
                arquivo = fopen(nome, "w");

                bub = clock();
                BubbleSort(vet2, n-1);//ordenacao do vet2 pelo bubble sort
                bub = clock() - bub;//calculo do tempo do bubble sort

                //ira armazenar os valores ordenados do vet2 pelo bubble sort no arquivo
                for(int r = 0; r < n-1; r++){
                    fprintf(arquivo, " %d ",vet2[r]);

                }

                fclose(arquivo); //fecha do arquivo

                //ORDENACAO COM QUICKSOFT
                //ira criar um arquivo para armazenar os valores ordenados pelo quick sort
                sprintf(nome2, "%s-QuickSort.txt", nome1);
                arquivo = fopen(nome2, "w");

                qui = clock();
                QuickSort(vet5, -1, n-1);//ordenacao do vet5 pelo quick sort
                qui = clock() - qui;//calculo do tempo do quick sort

                //ira armazenar os valores ordenados do vet5 pelo quick sort no arquivo
                for(int r = 0; r < n-1; r++){
                    fprintf(arquivo, " %d ",vet5[r]);

                }

                fclose(arquivo);//fechar arquivo

                //ORDENACAO COM MERGESORT
                //ira criar um arquivo para armazenar os valores ordenados pelo merge sort
                sprintf(nome, "%s-MergeSort.txt", nome1);
                arquivo = fopen(nome, "w");

                mer = clock();
                MergeSort(vet6, 0, n-1);//ordenacao do vet6 pelo merge sort
                mer = clock() - mer;//calculo do tempo do merge sort

                //ira armazenar os valores ordenados do vet6 pelo merge sort no arquivo
                for(int r = 0; r < n-1; r++){
                    fprintf(arquivo, " %d ",vet6[r]);

                }

                fclose(arquivo);//fechar arquivo

                //PERFOMANCE DE CADA ALGORITMO DE ORDENACAO
                printf("\nALGORITMO: InsertionSort\n");
                printf("Tamanho: %d\n",n-1);
                printf("Tempo: %f s\n",((float)ins)/CLOCKS_PER_SEC);
                printf("Arquivo Ordenado: ok\n");

                printf("\nALGORITMO: BubbleSort\n");
                printf("Tamanho: %d\n",n-1);
                printf("Tempo: %f s\n",((float)bub)/CLOCKS_PER_SEC);
                printf("Arquivo Ordenado: ok\n");

                printf("\nALGORITMO: QuickSort\n");
                printf("Tamanho: %d\n",n-1);
                printf("Tempo: %f s\n",((float)qui)/CLOCKS_PER_SEC);
                printf("Arquivo Ordenado: ok\n");

                printf("\nALGORITMO: MergeSort\n");
                printf("Tamanho: %d\n",n-1);
                printf("Tempo: %f s\n",((float)mer)/CLOCKS_PER_SEC);
                printf("Arquivo Ordenado: ok\n");

            }

            printf("\n=== PROJETO ORDENACAO ===\n");
            printf("1 - Gerar arquivo\n2 - Ordenar arquivo\n3 - Buscar \n0 - Sair\n");
            printf("Opcao: ");
            scanf("%d", &op);
        }
    }
}
