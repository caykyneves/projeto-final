#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char proprietario[50];
    char combustivel[20];
    char modelo[50];
    char cor[20];
    char chassi[20];
    int ano;
    char placa[8];
} Veiculo;

typedef struct Node {
    Veiculo data;
    struct Node* next;
} Node;

Node* createNode(Veiculo data) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = data;
    newNode->next = NULL;
    return newNode;
}

void addVeiculo(Node** head, Veiculo data) {
    Node* newNode = createNode(data);
    newNode->next = *head;
    *head = newNode;
}

void listarProprietariosDiesel2010(Node* head) {
    printf("Proprietários de carros do ano de 2010 ou posterior e movidos a diesel:\n");
    while (head != NULL) {
        if (head->data.ano >= 2010 && strcmp(head->data.combustivel, "diesel") == 0) {
            printf("%s\n", head->data.proprietario);
        }
        head = head->next;
    }
}


void listarPlacasJ(Node* head) {
    printf("Placas que começam com a letra J e terminam com 0, 2, 4 ou 7 e seus respectivos proprietários:\n");
    while (head != NULL) {
        if (head->data.placa[0] == 'J' && (head->data.placa[7] == '0' || head->data.placa[7] == '2' || head->data.placa[7] == '4' || head->data.placa[7] == '7')) {
            printf("Placa: %s, Proprietário: %s\n", head->data.placa, head->data.proprietario);
        }
        head = head->next;
    }
}

void listarModeloCorVogal(Node* head) {
    printf("Modelo e cor dos veículos cujas placas possuem como segunda letra uma vogal e cuja soma dos valores numéricos fornece um número par:\n");
    while (head != NULL) {
        if ((head->data.placa[1] == 'A' || head->data.placa[1] == 'E' || head->data.placa[1] == 'I' || head->data.placa[1] == 'O' || head->data.placa[1] == 'U') &&
            ((head->data.placa[2] - '0') + (head->data.placa[3] - '0') + (head->data.placa[4] - '0') + (head->data.placa[5] - '0') + (head->data.placa[6] - '0') + (head->data.placa[7] - '0')) % 2 == 0) {
            printf("Modelo: %s, Cor: %s\n", head->data.modelo, head->data.cor);
        }
        head = head->next;
    }
}


void trocarProprietario(Node* head, char chassi[20], char novoProprietario[50]) {
    while (head != NULL) {
        if (strcmp(head->data.chassi, chassi) == 0 && strpbrk(head->data.placa, "0") == NULL) {
            strcpy(head->data.proprietario, novoProprietario);
            printf("Proprietário do veículo com chassi %s alterado para %s\n", chassi, novoProprietario);
            return;
        }
        head = head->next;
    }
    printf("Veículo com chassi %s não encontrado ou não atende aos critérios\n", chassi);
}

int main() {
    Node* listaVeiculos = NULL;

    Veiculo v1 = {"Proprietario1", "diesel", "Modelo1", "Cor1", "Chassi1", 2012, "JAB1234"};
    Veiculo v2 = {"Proprietario2", "gasolina", "Modelo2", "Cor2", "Chassi2", 2015, "JBC5678"};
    Veiculo v3 = {"Proprietario3", "álcool", "Modelo3", "Cor3", "Chassi3", 2010, "JDE9876"};

    addVeiculo(&listaVeiculos, v1);
    addVeiculo(&listaVeiculos, v2);
    addVeiculo(&listaVeiculos, v3);

    listarProprietariosDiesel2010(listaVeiculos);
    listarPlacasJ(listaVeiculos);
    listarModeloCorVogal(listaVeiculos);

    trocarProprietario(listaVeiculos, "Chassi2", "NovoProprietario");

    return 0;
}