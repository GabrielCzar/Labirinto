#ifndef EXEMPLO_LAB_H
#define EXEMPLO_LAB_H

#include "../libs/ed_base.h"
#include "../libs/ed_mat.h"
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

namespace aluno{
    int nlinhas = 20;
    int ncolunas = 35;
    matchar mat(nlinhas, ncolunas, 'k');
    vector<Par> viz = {Par(-1, 0), Par(1, 0), Par(0, -1), Par(0, 1)};
    int size = viz.size();

    ///CRIACAO DO LABIRINTO RECURSIVO

    bool verificarVizinhos(Par par, int i, int cont){
        if(mat.is_inside(par + viz[i]) && mat.get(par + viz[i]) != 'k')
            cont++;
        if(cont <= 1 && i >= 3)
            return true;
        if(i >= 3)
            return false;

        return verificarVizinhos(par, i += 1, cont);
    }

    void makeLabirinto(Par pos){
        int r = rand() % size;

        if(!mat.is_inside(pos))
            return;
        if(mat.get(pos) == 'k'){
            mat.get(pos) = 'w';
            mat_paint_grid(mat);
            ed_show();
        }

        if(verificarVizinhos(pos + viz[r % size], 0, 0))
            makeLabirinto(pos + viz[r % size]);
        if(verificarVizinhos(pos + viz[(r + 1) % size], 0, 0))
            makeLabirinto(pos + viz[(r + 1) % size]);
        if(verificarVizinhos(pos + viz[(r + 2) % size], 0, 0))
            makeLabirinto(pos + viz[(r + 2) % size]);
        if(verificarVizinhos(pos + viz[(r + 3) % size], 0, 0))
            makeLabirinto(pos + viz[(r + 3) % size]);
    }

    void labirinto(){
        srand(time(NULL));
        ed_set_autoplay(false);
        Par pos(2,2);
        mat.get(pos) = 'w';

        mat_paint_grid(mat);
        ed_show();

        makeLabirinto(pos);

        ed_wait_esc();
    }

    ///SOLUCAO DO LABIRINTO RECURSIVA

    bool solverLab(Par posIni, Par posDes){
        int r = rand() % size;
        if(!mat.is_inside(posIni))
            return false;
        if(mat.get(posIni) != 'w')
            return false;
        if(posIni == posDes)
            return true;

        mat.get(posIni) = 'r';
        mat_paint_grid(mat);
        ed_show();

        bool isCaminho = solverLab(posIni + viz[r % size], posDes) ||
                         solverLab(posIni + viz[(r + 1) % size], posDes) ||
                         solverLab(posIni + viz[(r + 2) % size], posDes) ||
                         solverLab(posIni + viz[(r + 3) % size], posDes);

        if(isCaminho){
            mat.get(posIni) = 'b';
            mat_paint_grid(mat);
            ed_show();
        }

        if(mat.get(posIni) == 'r')
            mat.get(posIni) = 'w';

        return isCaminho;
    }

    void solucaoLabirinto(){
        Par posIni = mat_select_point(mat, "Selecione um ponto inicial do labirinto");
        Par posDes = mat_select_point(mat, "Selecione um ponto final do labirinto");
        ed_set_autoplay(false);

        solverLab(posIni, posDes);

        ed_wait_esc();
    }
}

#endif // EXEMPLO_LAB_H
