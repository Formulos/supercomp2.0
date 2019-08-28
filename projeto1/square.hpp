
#ifndef square_if
#define square_if



class square {
    // variáveis declaradas aqui são privadas por padrão
    ;
    public:
        square();
        // variáveis declaradas aqui são públicas
        int width;
        int height;
        int mass;
        double speedx;
        double speedy;
        double posx;
        double posy;
        bool ci; //colision iminent
        void new_square();
        void colide(square);
        void update_pos(double,double);
        void update_speed(double,double);
        
};

#endif