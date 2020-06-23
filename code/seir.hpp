#ifndef _SEIR_HPP
#define _SEIR_HPP


#include <vector>
#include <map>
using namespace std;

class SEIRState;
typedef vector<SEIRState> SEIRStateSpace;

#include "node.hpp"



/*
// This enum captures the four states of infection that an individual can be in
enum SEIRState 
{   Susceptible = 0, 
    Exposed     = 1, 
    Infectious  = 2,
    Recovered   = 3
};
*/


class SEIRState {
public:
    enum Phase { S=0, E=1, I=2, R=3};

    SEIRState( Phase p, int d=0);
    SEIRState( const SEIRState &other);

    SEIRState next( bool change=false) const;
    bool operator== (const SEIRState &other) const;
    bool operator== (Phase other) const;

    Phase phase() const { return _p;}
    int days() const { return _d;}

    static SEIRStateSpace all_states( int dE, int dI);

private:
    Phase _p;
    int _d;

};

ostream& operator<<(ostream& os, const SEIRState &s);



Message basic_states( const Message &message, const SEIRStateSpace &states);



class VirusLoad {

    map<double, double> _Px;

public:
    VirusLoad(); 
    void add_source( double p, double x);

    map<double, double>::const_iterator cbegin() const {return _Px.cbegin();};
    map<double, double>::const_iterator cend() const {return _Px.cend();};

};

ostream& operator<<(ostream& os, const VirusLoad &l);


#endif