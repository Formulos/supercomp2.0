
#ifndef place_if
#define place_if

#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>

class place {
    // variáveis declaradas aqui são privadas por padrão
    private:
    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive & ar, const unsigned int version){
        ar & posx;
        ar & posy;
    }
    ;
    public:
        // variáveis declaradas aqui são públicas
        double posx;
        double posy;
        place();
        void add_point(double,double);
        
};

#endif