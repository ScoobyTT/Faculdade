#include <stdio.h>
#include <string.h>
#define TAM 10

typedef struct aluno {
    char nome[25];
    char mat[10];
    int idade;
    float notas[3];
    float media;
} Aluno;

typedef struct usuario {
    char login[20];
    char senha[20];
    int tipo;
} Usuario;

void cadastroAluno(Aluno T[], int pos);
void imprimirTabela(Aluno T[], int tam);
void ordenarPorNome(Aluno T[], int tam);
int buscaBinaria(Aluno T[], int tam, char nomeBusca[]);
int fazerLogin(Usuario usuarios[], int numUsuarios);
void menuPrincipal(Aluno alunos[], int *numAlunos);
void corrigirNotas(Aluno T[], int tam, char nomeBusca[]);
void estatisticasTurma(Aluno T[], int tam);
void exportarDados(Aluno T[], int tam);

void cadastroAluno(Aluno T[], int pos) {
    printf("Informe o nome: ");
    scanf(" %[^\n]", T[pos].nome);
    
    printf("Informe a matricula (9 digitos): ");
    scanf("%s", T[pos].mat);
    
    if (strlen(T[pos].mat) != 9) {
        printf("Matricula deve ter 9 digitos!\n");
        return;
    }
    
    printf("Informe a idade: ");
    scanf("%d", &T[pos].idade);
    
    for (int i = 0; i < 3; i++) {
        printf("Informe a nota %d: ", i+1);
        scanf("%f", &T[pos].notas[i]);
    }
    
    T[pos].media = (T[pos].notas[0] + T[pos].notas[1] + T[pos].notas[2]) / 3.0;
    printf("Media calculada: %.2f\n", T[pos].media);
}

void imprimirTabela(Aluno T[], int tam) {
    printf("\n=== DADOS DOS ALUNOS ===\n");
    for(int i = 0; i < tam; i++) {
        printf("Aluno %d:\n", i+1);
        printf("Nome: %s\n", T[i].nome);
        printf("Matricula: %s\n", T[i].mat);
        printf("Idade: %d\n", T[i].idade);
        printf("Notas: %.1f, %.1f, %.1f\n", T[i].notas[0], T[i].notas[1], T[i].notas[2]);
        printf("Media: %.2f\n", T[i].media);
        printf("-------------------\n");
    }
}

void ordenarPorNome(Aluno T[], int tam) {
    for(int i = 0; i < tam-1; i++) {
        for(int j = i+1; j < tam; j++) {
            if(strcmp(T[i].nome, T[j].nome) > 0) {
                Aluno temp = T[i];
                T[i] = T[j];
                T[j] = temp;
            }
        }
    }
}

int buscaBinaria(Aluno T[], int tam, char nomeBusca[]) {
    int inicio = 0, fim = tam-1;
    
    while(inicio <= fim) {
        int meio = (inicio + fim) / 2;
        int comparacao = strcmp(T[meio].nome, nomeBusca);
        
        if(comparacao == 0) return meio;
        else if(comparacao < 0) inicio = meio + 1;
        else fim = meio - 1;
    }
    return -1;
}

int fazerLogin(Usuario usuarios[], int numUsuarios) {
    char login[20], senha[20];
    printf("Login: ");
    scanf("%s", login);
    printf("Senha: ");
    scanf("%s", senha);
    
    for(int i = 0; i < numUsuarios; i++) {
        if(strcmp(usuarios[i].login, login) == 0 && 
           strcmp(usuarios[i].senha, senha) == 0) {
            printf("Login bem-sucedido!\n");
            return usuarios[i].tipo;
        }
    }
    printf("Login ou senha incorretos!\n");
    return -1;
}

void corrigirNotas(Aluno T[], int tam, char nomeBusca[]) {
    int pos = buscaBinaria(T, tam, nomeBusca);
    if(pos == -1) {
        printf("Aluno nao encontrado!\n");
        return;
    }
    
    char escolha;
    float novanota;
    
    for(int j = 0; j < 3; j++) {
        printf("Nota %d = %.1f. Deseja corrigir? (s/n): ", j+1, T[pos].notas[j]);
        scanf(" %c", &escolha);
        
        if(escolha == 's' || escolha == 'S') {
            printf("Novo valor da nota: ");
            scanf("%f", &novanota);
            T[pos].notas[j] = novanota;
        }
    }
    
    T[pos].media = (T[pos].notas[0] + T[pos].notas[1] + T[pos].notas[2]) / 3.0;
    printf("Notas atualizadas. Nova media: %.2f\n", T[pos].media);
}

void estatisticasTurma(Aluno T[], int tam) {
    if(tam == 0) {
        printf("Nenhum aluno cadastrado!\n");
        return;
    }
    
    float mediaTurma = 0, maiorMedia = 0, menorMedia = 10;
    int aprovados = 0;
    
    for(int i = 0; i < tam; i++) {
        mediaTurma += T[i].media;
        if(T[i].media > maiorMedia) maiorMedia = T[i].media;
        if(T[i].media < menorMedia) menorMedia = T[i].media;
        if(T[i].media >= 6.0) aprovados++;
    }
    mediaTurma /= tam;
    
    printf("\n=== ESTATISTICAS DA TURMA ===\n");
    printf("Media da turma: %.2f\n", mediaTurma);
    printf("Maior media: %.2f\n", maiorMedia);
    printf("Menor media: %.2f\n", menorMedia);
    printf("Aprovados: %d/%d\n", aprovados, tam);
    printf("Reprovados: %d/%d\n", tam - aprovados, tam);
}

void exportarDados(Aluno T[], int tam) {
    FILE *arquivo = fopen("alunos.txt", "w");
    if(arquivo == NULL) {
        printf("Erro ao criar arquivo!\n");
        return;
    }
    
    for(int i = 0; i < tam; i++) {
        fprintf(arquivo, "%s;%s;%d;%.1f;%.1f;%.1f;%.2f\n", 
                T[i].nome, T[i].mat, T[i].idade,
                T[i].notas[0], T[i].notas[1], T[i].notas[2],
                T[i].media);
    }
    fclose(arquivo);
    printf("Dados exportados para 'alunos.txt'\n");
}

void menuPrincipal(Aluno alunos[], int *numAlunos) {
    int opcao;
    char nomeBusca[25];
    int resultado;
    
    do {
        printf("\n=== SISTEMA ACADEMICO ===\n");
        printf("1. Cadastrar aluno\n");
        printf("2. Listar todos alunos\n");
        printf("3. Buscar aluno por nome\n");
        printf("4. Ordenar alunos por nome\n");
        printf("5. Corrigir notas\n");
        printf("6. Estatisticas da turma\n");
        printf("7. Exportar dados\n");
        printf("0. Sair\n");
        printf("Escolha: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1:
                if(*numAlunos < TAM) {
                    cadastroAluno(alunos, *numAlunos);
                    (*numAlunos)++;
                } else {
                    printf("Limite de alunos atingido!\n");
                }
                break;
            case 2:
                imprimirTabela(alunos, *numAlunos);
                break;
            case 3:
                if(*numAlunos == 0) {
                    printf("Nenhum aluno cadastrado!\n");
                    break;
                }
                printf("Nome para buscar: ");
                scanf(" %[^\n]", nomeBusca);
                resultado = buscaBinaria(alunos, *numAlunos, nomeBusca);
                if(resultado != -1) {
                    printf("Aluno encontrado na posicao %d\n", resultado);
                    printf("Nome: %s\n", alunos[resultado].nome);
                    printf("Media: %.2f\n", alunos[resultado].media);
                } else {
                    printf("Aluno nao encontrado!\n");
                }
                break;
            case 4:
                if(*numAlunos == 0) {
                    printf("Nenhum aluno cadastrado!\n");
                    break;
                }
                ordenarPorNome(alunos, *numAlunos);
                printf("Alunos ordenados por nome!\n");
                break;
            case 5:
                if(*numAlunos == 0) {
                    printf("Nenhum aluno cadastrado!\n");
                    break;
                }
                printf("Nome do aluno para corrigir notas: ");
                scanf(" %[^\n]", nomeBusca);
                corrigirNotas(alunos, *numAlunos, nomeBusca);
                break;
            case 6:
                estatisticasTurma(alunos, *numAlunos);
                break;
            case 7:
                if(*numAlunos == 0) {
                    printf("Nenhum aluno cadastrado!\n");
                    break;
                }
                exportarDados(alunos, *numAlunos);
                break;
            case 0:
                printf("Saindo do sistema...\n");
                break;
            default:
                printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
}

int main() {
    Aluno LP1[TAM];
    int numAlunos = 0;
    
    Usuario usuarios[2] = {
        {"admin", "123", 1},
        {"user", "456", 2}
    };
    
    printf("=== SISTEMA ACADEMICO UNEB ===\n");
    if(fazerLogin(usuarios, 2) != -1) {
        menuPrincipal(LP1, &numAlunos);
    }
    
    return 0;
}
