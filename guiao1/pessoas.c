#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include "pessoa.h"

Pessoa p;

int isInteger(const char *str) {
    char *endptr;
    strtol(str, &endptr, 10);
    return (*str != '\0' && *endptr == '\0');
}

int inserirPessoa(char const *nome, char const *idade) {
    int fd = open("pessoas.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    strcpy(p.nome, nome);
    p.idade = atoi(idade);

    if (write(fd, &p, sizeof(p)) == -1) {
        perror("write");
        return -1;
    }

    printf("Pessoa inserida com sucesso\n");
    close(fd);
    return 0;
}

int listaPessoas(char const *n) {
    int fd = open("pessoas.txt", O_RDONLY);
    int n_pessoas = atoi(n);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    while (read(fd, &p, sizeof(p)) > 0 && n_pessoas-- > 0) {
        printf("Nome: %s || Idade: %d\n", p.nome, p.idade);
    }

    close(fd);
    return 0;
}

int atualizaIdade(char const *nome, char const *idade) {
    int fd = open("pessoas.txt", O_RDWR | O_RDONLY, 0644);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // caso tenha sido inserida a posicao em vez do nome
    if(isInteger(nome)) {
        lseek(fd, (atoi(nome) - 1) * sizeof(Pessoa), SEEK_SET);
        read(fd, &p, sizeof(Pessoa));
        p.idade = atoi(idade);
        lseek(fd, -sizeof(Pessoa), SEEK_CUR);
        write(fd, &p, sizeof(Pessoa));
    }

    else {
        while(read(fd, &p, sizeof(p)) > 0) {
            if (strcmp(p.nome, nome) == 0) {
                p.idade = atoi(idade);
                lseek(fd, -sizeof(p), SEEK_CUR);
                write(fd, &p, sizeof(p));
            }
        }
    }

    printf("Idade atualizada com sucesso\n");
    close(fd);
    return 0;
}

int tamanhoRegisto() {
    int fd = open("pessoas.txt", O_RDONLY);
    int size = lseek(fd, 0, SEEK_END);
    close(fd);
    return size;
}

int main(int argc, char const *argv[]) {
    // inserir pessoa
    if (strcmp(argv[1], "-i") == 0) {
        inserirPessoa(argv[2], argv[3]);
        int size = tamanhoRegisto();
        int posicao = size / sizeof(p);
        printf("Pessoa inserida na posição %d\n", posicao);
    }

    // listar pessoas
    if (strcmp(argv[1], "-l") == 0) {
        listaPessoas(argv[2]);
    }

    // atualizar pessoa
    if (strcmp(argv[1], "-u") == 0) {
        atualizaIdade(argv[2], argv[3]);    
        // opcao -o nao e necssaria nesta implementacao
    }
}
