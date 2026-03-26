#include <stdlib.h>
#include <stdio.h>
#include <math.h>

#include "poli.h"


polinomio * poli_create(int grau){
    // TODO: Implemente aqui a solucao para operacao create

    polinomio *p = (polinomio *) malloc(sizeof(polinomio));

    p->grau = grau;

    p->coeficientes = (int *) malloc((grau + 1) * sizeof(int));

    if (p->coeficientes == NULL) {
        free(p);
        return NULL;
    }
    
    for (int i = 0; i <= grau; i++) { p->coeficientes[i] = 0; }

    p->termos = grau;

    return p;
}

void poli_destroy(polinomio **p){
    // TODO: Implemente aqui a solucao para operacao destroy

    if (p == NULL || *p == NULL) return -1;

    if ((*p)->coeficientes != NULL) { 
        free((*p)->coeficientes); 
        (*p)->coeficientes = NULL;
    }

    free(*p);
    *p = NULL;
}

int poli_ins_termo(polinomio *p, int exp, int coef) {
    // TODO: Implemente aqui a solucao para operacao insere coeficiente

    // polinômio: P(x) = 10x^3 + 2x^1
    // coenficientes: 10 e 2
    // expoentes: 3 e 1


    // poli_ins_termo(p, 3, 10);
    // poli_ins_termo(p, 1, 2);
    
    // (polinomio, grau específico (expoente), elemento apenas (coeficiente))

    // TERMO NÃO É PARA ALOCAR
    // E CADA GRAU NO INDEX RESPONSÁVEL

    // EX: [0,2,0,10]

    if (exp < 0 || exp > p->grau) {
        return -1;
    }

    // Se a posição estava zerada e agora ganha um valor, aumenta o contador
    if (p->coeficientes[exp] == 0 && coef != 0) {
        p->termos++;
    } 
    // Se tinha valor e você está "limpando" para zero, diminui o contador
    else if (p->coeficientes[exp] != 0 && coef == 0) {
        p->termos--;
    }
    else (p->coeficientes[exp] != 0 && coef != 0){
        p->termos++;
    }

    // COEFICIENTE: 10 e 2
    // GRAU: 3 e 1


    // p->elementos[grau específico] = termo;
    p->coeficientes[exp] = coef;

    return 0;
}

int poli_get_termo(polinomio *p, int exp, int *coef) { 
    // Confirmar com o professor se é pra retornar o valor apenas ou se serve como um validador de termo.

    // TODO: Implemente aqui a solucao para operacao get coeficiente

    // Para o programa não tentar acessar uma memória que não lhe pertence e travar com um Segmentation Fault.

    if (exp < 0 || exp > p->grau) { 
        return -1; 
    }

    // serve para retornar o termo (coeficiente).
    // *termo = p->termos[grau específico];
    *coef = p->coeficientes[exp];

    return 0;
}

int calcula_px(polinomio *p, int x){
    // TODO: Implemente aqui a solucao para operacao calcula o valor de P(x)     
    
    /*
    
    P(x) = x^3 - 5*x + 2

    x = – 1 temos P(– 1) = 6. 

    P(-1) = -1^3 - 5*-1 + 2
    P(-1) = -1 + 5 + 2
    P(-1) = -1 + 7
    P(-1) = 6
    
    */


    // Aqui importa apenas se p existe, e não se tem ou não algo dentro de p (no caso um ponteiro: *p).
    // Assim eliminando também a redundância;
    if (p == NULL) return -1;

    int calculo_polinomio = 0;


    // Exemplo: i sendo 0 | p->coeficientes[0] * pow(-1, 0) | 2 * -1^0 | 2 * 1 = 2

    for (int i = 0; i <= p->grau; i++) {
        if (p->coeficientes[i] != 0) { // Aqui é diferente de zero porque se o termo for 0 ele não existe.
            calculo_polinomio += p->coeficientes[i] * pow(x, i);
        }
    }

    return calculo_polinomio;
}

polinomio * poli_soma(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que soma dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_mult(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que multiplica dois polinomios e gera um terceiro

    return NULL;
}

polinomio * poli_div(polinomio *p, polinomio *q){
    // TODO: Implemente aqui a solucao para operacao que divide dois polinomios e gera um terceiro
    if(p == NULL || q == NULL){
        return NULL;
    }
    if(q->grau == 0 && q->coeficientes[0] == 0){
        return NULL;
    }
    if(p->grau < q->grau){
        return poli_create(0);
    }

    int grau_res = p->grau - q->grau;
    polinomio *res = poli_create(grau_res);

    while(p->grau >= q->grau){
        int coef = p->coeficientes[p->grau]/q->coeficientes[q->grau];
        int exp = p->grau - q->grau;
        poli_ins_termo(res, exp, coef);
        for(int i = 0; i <= q->grau; i++){
            p->coeficientes[i + exp] -= coef * q->coeficientes[i];
        }
        while(p->grau > 0 && p->coeficientes[p->grau] == 0){
            p->grau--;
        }
    }
    return res;
}
