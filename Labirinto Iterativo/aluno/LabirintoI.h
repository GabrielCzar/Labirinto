#ifndef EXEMPLO_LAB_H
#define EXEMPLO_LAB_H

#include "../libs/ed_base.h"
#include "../libs/ed_mat.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

namespace aluno{
    int nlinhas = 20;
    int ncolunas = 35;
    matchar mat(nlinhas, ncolunas, 'k');
    vector<Par> dlc = {Par(-1, 0), Par(1, 0), Par(0, -1), Par(0, 1)};
    stack<Par> pilha;

    ///CRIACAO DO LABIRINTO ITERATIVO

    bool goToNext(Par par){
        int qtd = 0;
        for (int i = 0; i < 4; ++i) {
            if(!mat.is_inside(par + dlc[i]))
                continue;
            else if(mat.get(par + dlc[i]) != 'k')
                qtd++;
         }
         if(qtd <= 1)
             return true;
         else return false;
    }

    void attLab(Par pos, char cor){
        mat.get(pos) = cor;
        mat_paint_grid(mat);
        ed_show();
    }

    void makeLabirinto(){
        while (!pilha.empty()) {
            vector<Par> possiveisPosicoes;
            for (int i = 0; i < 4; ++i) {
                Par par = pilha.top() + dlc[i];
                if(!mat.is_inside(par))
                    continue;
                if(mat.get(par) == 'k')
                    if(goToNext(par))
                        possiveisPosicoes.push_back(par);
            }

            if(possiveisPosicoes.size() <= 0)
                pilha.pop();
            else{
                Par pos = possiveisPosicoes[rand() % possiveisPosicoes.size()];
                pilha.push(pos);
                attLab(pos, 'w');
            }
        }
    }

    void labirinto(){
        mat_paint_grid(mat);
        ed_set_autoplay(false);

        Par posIni = Par(1,1);
        mat.get(posIni) = 'w';
        pilha.push(posIni);

        makeLabirinto();

        ed_wait_esc();
    }

    ///SOLUCAO DO LABIRINTO

    void search(Par posInicial, Par PosFinal){
        pilha.push(posInicial);

        while (!pilha.empty()) {
            vector<Par> possiveisPosicoes;
            for (int i = 0; i < 4; ++i) {
                Par par = pilha.top() + dlc[i];
                if(!mat.is_inside(par))
                    continue;
                if(mat.get(par) == 'w')
                    possiveisPosicoes.push_back(par);
            }

            if(possiveisPosicoes.size() <= 0)
                pilha.pop();
            else{
                Par pos = possiveisPosicoes[rand() % possiveisPosicoes.size()];
                pilha.push(pos);
                attLab(pos, 'r');
            }
            if(pilha.top() == PosFinal)
                break;
        }
    }

    void solver(){
        Par posIni = mat_select_point(mat, "Selecione um ponto inicial do labirinto");
        Par posDes = mat_select_point(mat, "Selecione um ponto final do labirinto");
        ed_set_autoplay(false);

        search(posIni, posDes);

        ed_wait_esc();

    }

}

#endif // EXEMPLO_LAB_H
