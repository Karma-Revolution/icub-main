/*
 * Copyright (C) 2007-2009 Arjan Gijsberts @ Italian Institute of Technology
 * CopyPolicy: Released under the terms of the GNU GPL v2.0.
 *
 * Implementation of a fixed range scaler.
 *
 */

#include <cfloat>
#include <sstream>

#include <yarp/os/Value.h>

#include "iCub/FixedRangeScaler.h"

namespace iCub {
namespace contrib {
namespace learningmachine {

FixedRangeScaler::FixedRangeScaler(std::string name, double li, double ui, double lo, double uo) : IScaler(name) {
    this->setLowerBoundIn(li);
    this->setUpperBoundIn(ui);
    this->setLowerBoundOut(lo);
    this->setUpperBoundOut(uo);
}

void FixedRangeScaler::updateScales() {
    this->scale = (this->getUpperBoundIn() - this->getLowerBoundIn()) / (this->getUpperBoundOut() - this->getLowerBoundOut());
    this->offset = this->getLowerBoundIn() - (this->getLowerBoundOut() * this->scale);
}

std::string FixedRangeScaler::getStats() {
    std::ostringstream buffer;
    buffer << this->IScaler::getStats() << ", ";
    buffer << "In Bounds: [" << this->getLowerBoundIn() << "," << this->getUpperBoundIn() << "], ";
    buffer << "Out Bounds: [" << this->getLowerBoundOut() << "," << this->getUpperBoundOut() << "]";
    return buffer.str();
}

bool FixedRangeScaler::configure(Searchable& config) {
    bool success = this->IScaler::configure(config);

    // set the expected incoming lower bound (double)
    if(config.find("lowerin").isDouble() || config.find("lowerin").isInt()) {
        this->setLowerBoundIn(config.find("lowerin").asDouble());
        success = true;
    }
    // set the expected incoming bound (double)
    if(config.find("upperin").isDouble() || config.find("upperin").isInt()) {
        this->setUpperBoundIn(config.find("upperin").asDouble());
        success = true;
    }

    // set the desired outgoing lower bound (double)
    if(config.find("lowerout").isDouble() || config.find("lowerout").isInt()) {
        this->setLowerBoundOut(config.find("lowerout").asDouble());
        success = true;
    }
    // set the desired outgoing bound (double)
    if(config.find("upperout").isDouble() || config.find("upperout").isInt()) {
        this->setUpperBoundOut(config.find("upperout").asDouble());
        success = true;
    }

    return success;
}

} // learningmachine
} // contrib
} // iCub

