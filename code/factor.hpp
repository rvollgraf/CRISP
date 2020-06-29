#ifndef F_GRAPH_HPP
#define F_GRAPH_HPP

#include "node.hpp"
#include "distribution.hpp"

using namespace std;

class Node;


class Factor {
    Factor( const Factor &) = delete;

public:
    vector<Node*> _nodes;

    virtual double potential( const vector<unsigned int> &) = 0;

public:
    Factor( const vector<Node*> &nodes, const vector<Node*> &child_nodes = vector<Node*>());
    virtual ~Factor() {}

    virtual MessagePtr message_to( Node *);
};


class TableFactor: public Factor {
    const Message _tab;
protected:
    virtual double potential( const vector<unsigned int> &);

public:
    TableFactor( vector<Node*> &nodes, Message tab);

};



class SEIRFactor : public Factor {

    const Message _piE; 
    const Message _piI;
    double _p0;
    double _p1;

    static const vector<double> init_pi( const Distribution &q);

    static vector<Node *> init_helper(SEIRNode &in, SEIRNode &out, vector<SEIRNode *> contacts );

    MessagePtr message_forward();
    MessagePtr message_backward();
    MessagePtr message_horizontally( bool forward);
    MessagePtr message_vertically( Node *n);

    const SEIRStateSpace &_states;

public:
    SEIRFactor( const Distribution &qE, const Distribution &qI,
                double p0, double p1, 
                SEIRNode &in, SEIRNode &out, 
                vector<SEIRNode *> contacts = vector<SEIRNode*>(),
                const vector<Node*> &child_nodes = vector<Node*>());
    virtual ~SEIRFactor(){}
    MessagePtr message_to( Node *);

    virtual double potential( const vector<unsigned int> &);

};


class SEIRInitFactor: public Factor {
    bool _patient_zero;
    const SEIRStateSpace &_states;

public:
    SEIRInitFactor( SEIRNode &in, bool patient_zero = false);
    virtual ~SEIRInitFactor(){}
    virtual double potential( const vector<unsigned int> &);
    MessagePtr message_to( Node *);
};


class SEIRTestFactor: public Factor {
    bool _positive;
    double _alpha;
    double _beta;
    const SEIRStateSpace &_states;

public:
    SEIRTestFactor( SEIRNode &in, bool positive, double alpha, double beta);
    virtual ~SEIRTestFactor(){}
    virtual double potential( const vector<unsigned int> &);
};

#endif