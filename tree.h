#ifndef TREE_H
#define TREE_H


class Tree
{
public:
    virtual double dirtHeightResponse(double dirtHeight) const = 0;
    virtual double heightResponse(double height) const = 0;
    virtual double slopeResponse(double slope) const = 0;
    virtual double drainAreaResponse(double drain) const = 0;
    virtual double wetnessResponse(double wetness) const = 0;
    virtual double streamPowerResponse(double streamPower) const = 0;
    virtual double lightResponse(double light) const = 0;

    double chanceToSpawn(double dirtHeight, double height, double slope,
                         double drain, double wetness, double streamPower,
                         double light) const;
};

class Sapin : public Tree
{
public:
    Sapin();
    ~Sapin();

    virtual double dirtHeightResponse(double dirtHeight) const;
    virtual double heightResponse(double height) const;
    virtual double slopeResponse(double slope) const;
    virtual double drainAreaResponse(double drain) const;
    virtual double wetnessResponse(double wetness) const;
    virtual double streamPowerResponse(double streamPower) const;
    virtual double lightResponse(double light) const;
};

#endif // TREE_H
