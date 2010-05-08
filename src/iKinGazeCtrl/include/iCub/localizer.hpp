
#ifndef __LOCALIZER_H__
#define __LOCALIZER_H__

#include <yarp/os/BufferedPort.h>
#include <yarp/os/RateThread.h>

#include <iCub/pids.h>

#include <iCub/utils.hpp>
                            
#define KP_PAN               0.0012
#define KP_TILT              0.0012
#define KP_VERG              0.0005
#define KI_PAN               0.0001
#define KI_TILT              0.0001
#define KI_VERG              0.0001
#define LIM_LOW             -0.2
#define LIM_HIGH             0.2

using namespace std;
using namespace yarp;
using namespace yarp::os;
using namespace yarp::sig;
using namespace yarp::math;
using namespace ctrl;
using namespace iKin;


// The thread launched by the application which is
// in charge of localizing target 3D position from
// image coordinates.
class Localizer : public RateThread
{
protected:
    exchangeData         *commData;
    xdPort               *port_xd;
    BufferedPort<Bottle> *port_mono;
    BufferedPort<Bottle> *port_stereo;
    
    string localName;
    string configFile;
    unsigned int period;
    double Ts;

    iCubEye *eyeL;
    iCubEye *eyeR;

    Matrix *PrjL, *invPrjL;
    Matrix *PrjR, *invPrjR;
    double  cx;
    double  cy;

    parallelPID *pid;

    void handleMonocularInput();
    void handleStereoInput();

public:
    Localizer(exchangeData *_commData, const string &_localName,
              const string &_configFile, unsigned int _period);

    void set_xdport(xdPort *_port_xd) { port_xd=_port_xd; }

    virtual bool threadInit();
    virtual void afterStart(bool s);
    virtual void run();
    virtual void threadRelease();
};


#endif


