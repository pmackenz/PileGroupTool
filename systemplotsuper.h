#ifndef SYSTEMPLOTSUPER_H
#define SYSTEMPLOTSUPER_H

#include <QWidget>
#include "pilegrouptool_parameters.h"
#include "qcustomplot.h"

namespace Ui {
class SystemPlotSuper;
}

class SystemPlotSuper : public QWidget
{
public:
    explicit SystemPlotSuper(QWidget *parent = 0);
    ~SystemPlotSuper();
    virtual void refresh() = 0;
    virtual void setLoadType(LoadControlType);
    virtual void updatePiles(QVector<PILE_INFO> &);
    virtual void updateLoad(double, double, double);
    virtual void updateSoil(QVector<double> &);
    virtual void updateGWtable(double);
    virtual void updateDisplacement(double ux=0.0, double uy=0.0);
    virtual void updateDispProfile(QVector<double> &);
    virtual void updatePileDeformation(QVector<double> &, QVector<QVector<double> > &);

    virtual void setActivePile(int index) {activePileIdx = index;}
    virtual int  getActivePileIndex() {return activePileIdx;}
    virtual void setActiveLayer(int index) {activeLayerIdx = index;}
    virtual int  getActiveLayerIndex() {return activeLayerIdx;}

    virtual QList<QCPAbstractPlottable *> selectedPlottables();

private:

protected:
    LoadControlType loadControlType;

    double P;     // lateral force on pile cap
    double PV;    // vertical force on pile cap
    double PMom;  // applied moment on pile cap

    double HDisp; // prescribed horizontal displacement
    double VDisp; // prescriber vertical displacement

    double surfaceDisp;    // prescribed soil surface displacement
    double percentage12;   // percentage of surface displacement at 1st layer interface
    double percentage23;   // percentage of surface displacement at 2nd layer interface
    double percentageBase; // percentage of surface displacement at base of soil column

    // get parameters
    double gwtDepth;  // depth of ground water table below the surface

    int    numPileElements;
    int    numPiles;

    // states
    bool assumeRigidPileHeadConnection = false;

    // meshing parameters
    int minElementsPerLayer = MIN_ELEMENTS_PER_LAYER;
    int maxElementsPerLayer = MAX_ELEMENTS_PER_LAYER;
    int numElementsInAir    = NUM_ELEMENTS_IN_AIR;

    double L1;                      // pile length above ground (all the same)
    double L2[MAXPILES];            // embedded length of pile
    double pileDiameter[MAXPILES];  // pile diameter
    double xOffset[MAXPILES];       // x-offset of pile

    int numNodePiles;
    int numNodePile[MAXPILES];
    int maxLayers[MAXPILES];
    int nodeIDoffset[MAXPILES];
    int elemIDoffset[MAXPILES];

    // others
    QVector<HEAD_NODE_TYPE> headNodeList = QVector<HEAD_NODE_TYPE>(MAXPILES, {-1,-1,0.0, 1.0, 1.0});

    int numLoadedNode;
    QVector<double> depthOfLayer = QVector<double>(4, 0.0);

    // selection tracking
    int activePileIdx = 0;
    int activeLayerIdx = -1;
};

#endif // SYSTEMPLOTSUPER_H
