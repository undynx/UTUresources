#include <iostream>
#include <stdio.h>
#include <string>

using namespace std;

int main()
{
    int matriz[3][3], conteo = 1;

    for(int pos1 = 0 ; pos1<3 ; pos1++){
        for(int pos2 = 0 ; pos2<3 ; pos2++){
            matriz[pos1][pos2] = conteo;
            conteo++;
        }
    }


    for(int pos1 = 0 ; pos1<3 ; pos1++){
        for(int pos2 = 0 ; pos2<3 ; pos2++){
            printf("| %d |", matriz[pos1][pos2]);
        }
        printf("\n");
    }

    printf("\n\\\\\\\\\\\\\\\\\\\\\n\n");

    for(int pos2 = 0 ; pos2<3 ; pos2++){
        for(int pos1 = 2 ; pos1>=0 ; pos1--){
            printf("| %d |", matriz[pos1][pos2]);
        }
        printf("\n");
    }

    printf("\n\\\\\\\\\\\\\\\\\\\\\n\n");

    for(int pos1 = 2 ; pos1>=0 ; pos1--){
        for(int pos2 = 2 ; pos2>=0 ; pos2--){
            printf("| %d |", matriz[pos1][pos2]);
        }
        printf("\n");
    }



    return 0;
}
