#include <stdio.h>

///Esta funcion retorna un booleando indicando si es primo el numero
bool es_primo(int num){
    bool creoEsPrimo=true;
    int div=2;
    do{
        if(num%div==0)
            creoEsPrimo=false;
        div++;
    }while(div<=num/2 and creoEsPrimo);

    return creoEsPrimo;
}

int main()
{
    cout << "Hello world!" << endl;
    return 0;
}
