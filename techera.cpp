#include "header.h"
using namespace std;

TechEra::TechEra(const TechEra &_techEra) {
    name = _techEra.name;
    baseGrowthRate = _techEra.baseGrowthRate;
}

TechEra::TechEra(string _name, double _baseGrowthRate, int _technology) {
    name = _name;
    baseGrowthRate = _baseGrowthRate;
}

TechEra::TechEra(int _technology) {
    if (_technology < 20) {
        // Classical Era
        *this = ClassicalEra();
    } else if (_technology >= 17 && _technology < 40) {
        // Medieval Period
        *this = MedievalPeriod();
    } else if (_technology >= 40 && _technology < 50) {
        // Renaissance 
        *this = Renaissance();
    } else if (_technology >= 50 && _technology < 60) {
        // Industrial Revolution
        *this = IndustrialRevolution();
    } else if (_technology >= 60) {
        // Information Age
        *this = InformationAge();
    }
}

string TechEra::getName() {
    return name;
}

ClassicalEra::ClassicalEra() : TechEra("Classical Era", 0.002, 1) {}
MedievalPeriod::MedievalPeriod() : TechEra("Medieval Period", 0.005, 2) {}
Renaissance::Renaissance() : TechEra("Renaissance", 0.01, 3) {}
IndustrialRevolution::IndustrialRevolution() : TechEra("Industrial Revolution", 0.02, 4) {}
InformationAge::InformationAge() : TechEra("Information Age", 0.05, 5) {}





