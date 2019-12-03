- Como compilar:
esse progeto pode ser compilado usando cmake (CmakeList.txt ja esta incluso), simplesme usando o comando cmake e usando o make criado

- Ao rodar o projeto (usando mpiexec) é esperado os seguintes inputs:

A entrada de nosso programa será um conjunto de `N` pontos `x_i, y_i`. 

O formato de entrada será 

    N
    x_0 y_0
    ....
    x_(N-1) y_(N-1)

O formato de saída será 

    dist opt
    0 e_1 ... e_(N-1)

* `dist` é o comprimento do caminho encontrado usando 5 casas decimais.
* `e_1 ... e_(N-1)` é a sequência de empresas visitadas no trajeto
* `opt` é `1` se a solução encontrada é a ótima e `0` se foi usada outra estratégia
* depois que a simulação acaba o seu tempo de execução sai pelo cerr

Existe testes ja prontos como teste1.txt, para usá-los rode o programa compilado e faça um pipe do arquivo para o programa
