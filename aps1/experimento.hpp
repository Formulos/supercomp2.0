
#ifndef experimento_h
#define experimento_h

#include <chrono>
#include <iostream>



class experimento {
    // variáveis declaradas aqui são privadas por padrão
    ;
    public:
        experimento(int);
        virtual void experiment_code();
        void run();
        // variáveis declaradas aqui são públicas
        double *vector;
        int n;
        std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> start;
        std::chrono::time_point<std::chrono::_V2::system_clock, std::chrono::nanoseconds> end;
        double duration();
};

#endif