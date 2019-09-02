- Como compilar:
esse progeto pode ser compilado com g++ main.cc square.cpp
ou usando cmake (CmakeList.txt ja esta incluso), simplesme usando o comando cmake e usando o make criado

- Ao rodar o projeto é esperado os seguintes inputs:

w h mu_d
N
m wr hr x y vx vy 
.... 
m wr hr x y vx vy 
dt print_freq max_iter

w, h e mu_d se referem ao tamanho do campo de simulação e seu coeficiente de atrito dinâmico.
N é o número de retângulos da simulação. Cada linha subsequente contém um retângulo com as seguintes propriedades:
     massa m
     largura wr
     altura hr
     posição inicial (x, y)
     velocidade inicial  (vx, vy)
dt representa o tamanho do passo de simulação. 
a cada print_freq iterações o estado da simulação é mostrado na saída padrão.
a simulação roda no maximo max_iter vezes. Note que ela pode acabar antes.

tambem é posivel passar um arquivo como input, a ordem so deve ser a mesma, por exemplo "a.out < teste1"
veja tambem o arquivo teste 1 como exemplo

a saida é dada da seguinte forma:

itereração
x1 y1 vx1 vy1
...
xN yN vxN vyN

depois que a simulação acaba o seu tempo de execução sai pelo cerr
