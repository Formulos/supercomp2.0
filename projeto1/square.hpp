
#ifndef square_if
#define square_if



class square {
    // variáveis declaradas aqui são privadas por padrão
    ;
    public:
        square();
        // variáveis declaradas aqui são públicas
        int size;
        int width;
        int mass;
        double speedx;
        double speedy;
        int posx;
        int posy;
        void new_square();
        void update_pos(int,int);
        void update_speed(double,double);
        
};

#endif