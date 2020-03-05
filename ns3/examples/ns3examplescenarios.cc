#include "ns3examplescenarios.h"

// lte examples
#include "lte-simple-epc-mobile/ltesimpleepcmobile.h"
#include "lte-simple-epc-static/ltesimpleepcstatic.h"
#include "lte-simple-static/ltesimplestatic.h"
#include "lte-coverage-mobile/ltecoveragemobile.h"
#include "lte-coverage-static/ltecoveragestatic.h"
#include "lte-beam-steering/ltebeamsteering.h"
#include "lte-follower/ltefollower.h"
#include "lte-static-follower/ltestaticfollower.h"
#include "lte-aerial-basestation-cluster/lteaerialbasestationcluster.h"

#include "standalone/scenarioregistry.h"

#ifdef NS_MMW_BUILD
// millimeter-wave examples
#include "mmwave-simple-epc-static/mmwavesimpleepcstatic.h"
#include "mmwave-car-following/mmwavecarfollowing.h"
#include "mmwave-beam-steering/mmwavebeamsteering.h"
#endif

// parcel delivery examples
#include "parcel-delivery/parceldelivery.h"
#include "parcel-delivery/parceldelivery_lte.h"
#include "parcel-delivery/parceldelivery_wave.h"
#include "parcel-delivery/parceldelivery_cv2x.h"

#ifdef NS_V2X_BUILD
// v2x examples
#include "v2x-simple/v2xsimple.h"
#endif

// wifi examples
#include "wifi-reach-mobile/wifi-reach-mobile.h"
#include "wifi-reach-static/wifi-reach-static.h"

#include "wave-follower/wavefollower.h"

#include <numeric>

namespace LIMoSim {
namespace NS3 {
namespace Examples {


void lteSimpleEpcMobile()
{
    LogComponentEnable("LteSimpleEpcMobile", LOG_LEVEL_INFO);
    LteSimpleEpcMobile::setup();
}

void lteSimpleEpcMobile_mult()
{
    LogComponentEnable("LteSimpleEpcMobile", LOG_LEVEL_INFO);
    for (int i = 0; i < 2; i++) {
        LteSimpleEpcMobile::setup(i);
    }
}

void lteSimpleEpcStatic()
{
    LogComponentEnable("LteSimpleEpcStatic", LOG_LEVEL_INFO);
    LteSimpleEpcStatic::setup();
}

void lteSimpleStatic()
{
    LogComponentEnable("LteSimpleStatic", LOG_LEVEL_INFO);
    LteSimpleStatic::setup();
}

void lteCoverageMobile()
{
    LogComponentEnable("LteCoverageMobile", LOG_LEVEL_INFO);
    LteCoverageMobile::setup(0, 150, 1);
}

void lteCoverageMobile_mult(unsigned int runs)
{
    LogComponentEnable("LteCoverageMobile", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes(10);
    std::iota(std::begin(numsOfUes), std::end(numsOfUes), 1);
    numsOfUes.push_back(20);
    numsOfUes.push_back(50);

    std::vector<uint16_t> interPacketIntervals {10};

    std::vector<uint16_t> packetSizes {8000};

    std::cout << "scenario variations: " << std::endl;
    std::cout << "- num of Ues: " << numsOfUes.size()  << " variations" << std::endl
              << "- packet size: " << packetSizes.size() << " variations" << std::endl
              << "- inter packet intervall: " << interPacketIntervals.size() << " variations" << std::endl;


    uint16_t p = 0;
    uint16_t i = 0;
    uint16_t n = 9;
    uint16_t r = 0;
    uint16_t simTime = 1800;

    for (; p < packetSizes.size(); p++) {
        uint16_t packetSize = packetSizes.at(p);

        for (; i < interPacketIntervals.size(); i++) {
            uint16_t interPacketInterval = interPacketIntervals.at(i);

            for (; n < 10; n++) {
                uint16_t numOfUes = numsOfUes.at(n);

                for (; r < runs; r++) {
                    LteCoverageMobile::setup(static_cast<int>(r),
                                             simTime,
                                             numOfUes,
                                             interPacketInterval,
                                             packetSize);
                }
                r = 0;
            }
            n = 0;
        }
        i = 0;
    }
    p = 0;
}

void lteCoverageMobile_perf(unsigned int runs)
{
    LogComponentEnable("LteCoverageMobile", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes(10);
    std::iota(std::begin(numsOfUes), std::end(numsOfUes), 1);
    std::vector<uint16_t> interPacketIntervals {500, 250, 10};
    std::vector<uint16_t> packetSizes {100, 500, 1000, 8000};

    for (uint16_t packetSize : packetSizes) {
        for (uint16_t interPacketInterval : interPacketIntervals) {
            for (uint16_t numOfUes : numsOfUes) {
                for (unsigned int i = 0; i < runs; i++) {
                    LteCoverageMobile::setup(static_cast<int>(i),
                                             10,
                                             numOfUes,
                                             interPacketInterval,
                                             packetSize);
                }
            }
        }
    }
}

void lteCoverageStatic()
{
    LogComponentEnable("LteCoverageStatic", LOG_LEVEL_INFO);
    LteCoverageStatic::setup(0, 150, 1);
}

void lteCoverageStatic_mult(unsigned int runs)
{
    LogComponentEnable("LteCoverageStatic", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes (10);
    std::iota(std::begin(numsOfUes), std::end(numsOfUes), 1);

    std::vector<uint16_t> interPacketIntervals {10};

    std::vector<uint16_t> packetSizes {8000};

    std::cout << "scenario variations: " << std::endl;
    std::cout << "- num of Ues: " << numsOfUes.size()  << " variations" << std::endl
              << "- packet size: " << packetSizes.size() << " variations" << std::endl
              << "- inter packet intervall: " << interPacketIntervals.size() << " variations" << std::endl;


    uint16_t p = 0;
    uint16_t i = 0;
    uint16_t n = 5;
    uint16_t r = 7;
    uint16_t simTime = 300;

    for (; p < packetSizes.size(); p++) {
        uint16_t packetSize = packetSizes.at(p);

        for (; i < interPacketIntervals.size(); i++) {
            uint16_t interPacketInterval = interPacketIntervals.at(i);

            for (; n < 10; n++) {
                uint16_t numOfUes = numsOfUes.at(n);

                for (; r < runs; r++) {
                    LteCoverageStatic::setup(static_cast<int>(r),
                                             simTime,
                                             numOfUes,
                                             interPacketInterval,
                                             packetSize);
                }
                r = 0;
            }
            n = 0;
        }
        i = 0;
    }
    p = 0;
}

void lteCoverageStatic_perf(unsigned int runs)
{
    LogComponentEnable("LteCoverageStatic", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes(10);
    std::iota(std::begin(numsOfUes), std::end(numsOfUes), 1);
    std::vector<uint16_t> interPacketIntervals {500, 250, 10};
    std::vector<uint16_t> packetSizes {100, 500, 1000, 8000};

    for (uint16_t packetSize : packetSizes) {
        for (uint16_t interPacketInterval : interPacketIntervals) {
            for (uint16_t numOfUes : numsOfUes) {
                for (unsigned int i = 0; i < runs; i++) {
                    LteCoverageStatic::setup(static_cast<int>(i),
                                             10,
                                             numOfUes,
                                             interPacketInterval,
                                             packetSize);
                }
            }
        }
    }
}

void lteBeamSteering()
{
    LogComponentEnable("LteBeamSteering", LOG_LEVEL_INFO);
    LteBeamSteering::setup();
}

void lteBeamSteering_mult(unsigned int runs)
{
    LogComponentEnable("LteBeamSteering", LOG_LEVEL_INFO);
    for (int i = 0; i < runs; i++) {
        LteBeamSteering::setup(i);
    }
}

void lteAerialBasestationCluster()
{
    LogComponentEnable("LteAerialBasestationCluster", LOG_LEVEL_INFO);
    LteAerialBasestationCluster::setup();
}

void lteAerialBasestationCluster_mult(unsigned int runs)
{
    LogComponentEnable("LteBeamSteering", LOG_LEVEL_INFO);

    std::vector<uint16_t> numsOfUes(10);
    std::iota(std::begin(numsOfUes), std::end(numsOfUes), 1);

    uint16_t n = 7;
    unsigned int r = 0;

    for (; n < 8; n++) {
        uint16_t numOfUes = numsOfUes.at(n);
        for (; r < 5; r++) {
            LteAerialBasestationCluster::setup(static_cast<int>(r), 2, numOfUes, 1800);
        }
        r = 0;
    }
}

void lteFollower()
{
    LogComponentEnable("LteFollower", LOG_LEVEL_INFO);
    LteFollower::setup(0, 1);
}

void lteFollower_mult(unsigned int runs)
{
    LogComponentEnable("LteFollower", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes (10);
    std::iota(numsOfUes.begin(), numsOfUes.end(), 1);

    uint16_t n = 8;
    unsigned int r = 0;

    for (; n < 9; n++) {
        uint16_t numOfUes = numsOfUes.at(n);
        for (; r < runs; r++) {
            LteFollower::setup(static_cast<int>(r), numOfUes, 1800);
        }
        r = 0;
    }
}

#ifdef NS_MMW_BUILD
void mmwaveSimpleEpcStatic()
{
    LogComponentEnable("MmwaveSimpleEpcStatic", LOG_LEVEL_INFO);
    MmwaveSimpleEpcStatic::setup();
}

void mmwaveSimpleEpcStatic_mult(unsigned int runs)
{
    LogComponentEnable("MmwaveSimpleEpcStatic", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes (10);
    std::iota(numsOfUes.begin(), numsOfUes.end(), 1);

    uint16_t n = 0;
    unsigned int r = 0;

    for (; n < 10; n++) {
        uint16_t numOfUes = numsOfUes.at(n);
        for (; r < runs; r++) {
            MmwaveSimpleEpcStatic::setup(static_cast<int>(r), numOfUes,3);
        }
        r = 0;
    }
}

void mmwaveCarFollowing()
{
    LogComponentEnable("MmwaveCarFollowing", LOG_LEVEL_INFO);
    MmwaveCarFollowing::setup();
}

void mmwaveBeamSteering()
{
    LogComponentEnable("MmwaveBeamSteering", LOG_LEVEL_INFO);
    MmwaveBeamSteering::setup();
}

#endif


void parcelDelivery()
{
    LogComponentEnable("ParcelDelivery", LOG_LEVEL_INFO);
    ParcelDelivery::setup(0, 1);
}

void parcelDeliveryWithLte()
{
    LogComponentEnable("ParcelDelivery_LTE", LOG_LEVEL_INFO);
    ParcelDelivery::LTE::setup(0, 1);
}

void parcelDeliveryWithWave()
{
    LogComponentEnable("ParcelDelivery_Wave", LOG_LEVEL_INFO);
    ParcelDelivery::Wave::setup();
}

#ifdef NS_V2X_BUILD
void parcelDeliveryWithCV2X()
{
    LogComponentEnable("ParcelDelivery_CV2X", LOG_LEVEL_INFO);
    ParcelDelivery::CV2X::setup();
}
#endif

#ifdef NS_V2X_BUILD
void v2xSimple()
{
    LogComponentEnable("V2XSimple", LOG_LEVEL_INFO);
    V2XSimple::setup();
}

void v2xSimple_mult(unsigned int runs)
{
    LogComponentEnable("V2XSimple", LOG_LEVEL_INFO);
    std::vector<uint16_t> numsOfUes (10);
    std::iota(numsOfUes.begin(), numsOfUes.end(), 1);


    uint16_t n = 0;
    unsigned int r = 0;

    for (; n < 10; n++) {
        uint16_t numOfUes = numsOfUes.at(n);
        for (; r < runs; r++) {
            V2XSimple::setup(static_cast<int>(r), numOfUes, 1800);
        }
        r = 0;
    }
}

#endif

void wifiReachMobile()
{
    LogComponentEnable("WiFiReachMobile", LOG_LEVEL_INFO);
    WifiReachMobile::setup();
}

void wifiReachStatic()
{
    LogComponentEnable("WifiReachStatic", LOG_LEVEL_INFO);
    WifiReachStatic::setup();
}

}

namespace helpers {

void loadScenarioRegistry()
{
    ScenarioRegistry *registry = ScenarioRegistry::getInstance();

    registry->registerScenario("parcelDelivery", [](){Examples::ParcelDelivery::setup();});
    #ifdef NS_V2X_BUILD
    registry->registerScenario("parcelDeliveryWithCV2X", [](){Examples::ParcelDelivery::CV2X::setup();});
    registry->registerScenario("v2xFollower", [](){Examples::V2XSimple();});
    #endif
    registry->registerScenario("parcelDeliveryWithLTE", [](){Examples::ParcelDelivery::LTE::setup();});
    registry->registerScenario("parcelDeliveryWithWave", [](){Examples::ParcelDelivery::Wave::setup();});
    registry->registerScenario("lteAerialBsCluster", [](){Examples::LteAerialBasestationCluster::setup();});
    registry->registerScenario("lteCoverageMobile", [](){Examples::LteCoverageMobile::setup();});
    registry->registerScenario("lteCoverageStatic", [](){Examples::LteCoverageStatic::setup();});
    registry->registerScenario("lteFollower", [](){Examples::LteFollower::setup();});
    registry->registerScenario("lteStaticFollower", [](){Examples::LteStaticFollower::setup();});
    registry->registerScenario("waveFollower", [](){Examples::WaveFollower::setup();});
}
void printAvailableScenarios() {
    std::cout << "List of available standalone scenarios:\n";
    ScenarioRegistry::getInstance()->printScenarios();
}

} // namespace helpers
}


}
