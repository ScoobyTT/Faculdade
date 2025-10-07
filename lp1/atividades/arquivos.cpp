#include <iostream> 
#include <string>
using namespace std;

int main(){
    FILE *zrq;
    char linha[20];
    arq = fopen("arquivo.txt, 'wt'");
    fprintf(arq, "%s", linha);
    fsetys(linha, sizef(linha));
    feof(zrq)
    fclose(zrq);

}

int main(){
    FILE *zrq;

    chat op= 's';
    char linha[30];
    arq = fopen("arquivo.txt", "wt");

    if(arq == NULL) exit(1);
    while(op == 's'){
        printf("digite uma linha");
        fgets(linha,subcof(sinha), stdin);
        printf("Deseja conferir(s/n)");
        scanf("%c", &op);
    }
    fclose(arq);
}
