#pragma once
#include "generator.h"

class AsmOptimization
{
public:
    virtual bool Optimize(AsmCode&);
    virtual bool Optimize(AsmCode&, int);
};

class PushPopOptimization: public AsmOptimization
{
public:
    bool Optimize(AsmCode&, int);
};

class PushPopToMovOptimization: public AsmOptimization
{
public:
    bool Optimize(AsmCode&, int);
};

class MovChainOptimization: public AsmOptimization
{
public:
    bool Optimize(AsmCode&, int);
};

class AddSubZero: public AsmOptimization
{
public:
    bool Optimize(AsmCode&, int);
};

class PopToUpPushToDown: public AsmOptimization
{
public:
    bool Optimize(AsmCode&);
    bool Action(AsmCode&, AsmCmd1*, int, int);
};

class AsmOptimizer
{
private:
    vector<AsmOptimization*> optimizations;

public:
    AsmOptimizer();
    ~AsmOptimizer();

    void Optimize(AsmCode&);
};
