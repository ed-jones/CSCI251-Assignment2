#include "header.h"
using namespace std;

Chrononaut::Chrononaut(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability) {
    name = _name;
    type = _type;
    travelAge = _travelAge;
    realAge = _realAge;
    isAlive = _isAlive;
    isRetired = _isRetired;
    ability = _ability;
}

vector<unique_ptr<Chrononaut>> generateChrononauts() {

    uniform_real_distribution<double> abDist(0, 1);
    default_random_engine abEng; // Create random engine variable
    abEng.seed(random_device{}()); // Seed the random number engine

    vector<unique_ptr<Chrononaut>> chrononauts;

    chrononauts.emplace_back(new JumpEngineer("Rufus", "Jump Engineer", 52, 52, true, false, abDist(abEng), abDist(abEng)));
    chrononauts.emplace_back(new Doctor("Sigmund Freud", "Doctor", 65, 65, true, false, abDist(abEng), abDist(abEng), abDist(abEng)));
    chrononauts.emplace_back(new Historian("Socrates", "Historian", 67, 67, true, false, abDist(abEng), abDist(abEng), abDist(abEng)));
    chrononauts.emplace_back(new Security("Genghis Khan", "Security", 55, 55, true, false, abDist(abEng), abDist(abEng), abDist(abEng)));
    chrononauts.emplace_back(new Chronodog("Abraham Lincoln", "Chronodog", 53, 53, true, false, abDist(abEng), abDist(abEng), abDist(abEng), abDist(abEng)));
    chrononauts.emplace_back(new Chronocat("Napoleon Bonaparte", "Chronocat", 40, 40, true, false, abDist(abEng), abDist(abEng), abDist(abEng), abDist(abEng)));
    chrononauts.emplace_back(new Chronobird("Ludwig van Beethoven", "Chronobird", 37, 37, true, false, abDist(abEng), abDist(abEng), abDist(abEng), abDist(abEng)));

    return chrononauts;
}

void Chrononaut::print() {
    if (!hasRetired() && isLiving()) {
        cout << "   " << type << ": \"" << name << "\"" << endl;
        cout << "   Travel Age: " << travelAge << endl;
        cout << "   Real Age: " << realAge << endl;
        cout << "   Ability: " << getPrettyAbility() << endl;

        printCharacteristics();
        
        cout << endl;
    } else if (hasRetired()) {
        cout << "   " << type << ": \"" << name << "\"" << endl;
        cout << "   Retired" << endl;
        cout << endl;
    } else if (!isLiving()) {
        cout << "   " << type << ": \"" << name << "\"" << endl;
        cout << "   Deceased" << endl;
        cout << endl;
    }
    
}

void Chrononaut::ageUp() {
    travelAge++;
}

string Chrononaut::getType() {
    return type;
}

Chrononaut::Chrononaut(const Chrononaut &_chrononaut) {
    name = _chrononaut.name;
    type = _chrononaut.type;
    travelAge = _chrononaut.travelAge;
    realAge = _chrononaut.realAge;
    isAlive = _chrononaut.isAlive;
    characteristics = _chrononaut.characteristics;
    ability = _chrononaut.ability;
}

string Chrononaut::getPrettyAbility() {
    return to_string((int)(ability*100)) + "%";
}

double Chrononaut::getAbility() {
    return ability;
}

JumpEngineer::JumpEngineer(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _volatility) : Chrononaut(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability) {
    volatility = _volatility;
} 

void JumpEngineer::increaseVolatility(int percentage) {
    volatility += volatility*(percentage/100);
}

Doctor::Doctor(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _qualifications, double _intelligence) : Chrononaut(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability) {
    qualifications = _qualifications;
    intelligence = _intelligence;
}

void Doctor::increaseQualifications(int percentage) {
    qualifications += qualifications*(percentage/100);
}

void Doctor::increaseIntelligence(int percentage) {
    intelligence += intelligence*(percentage/100);
}

Historian::Historian(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _qualifications, double _wisdom) : Chrononaut(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability) {
    qualifications = _qualifications;
    wisdom = _wisdom;
}

void Historian::increaseQualifications(int percentage) {
    qualifications += qualifications*(percentage/100);
}

void Historian::increaseWisdom(int percentage) {
    wisdom += wisdom*(percentage/100);
}

Security::Security(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _strength, double _diplomacy) : Chrononaut(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability) {
    strength = _strength;
    diplomacy = _diplomacy;
}

void Security::increaseStrength(int percentage) {
    strength += strength*(percentage/100);
}

void Security::increaseDiplomacy(int percentage) {
    diplomacy += diplomacy*(percentage/100);
}

Chronopet::Chronopet(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _endearing) : Chrononaut(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability) {
    endearing = _endearing;
}

void Chronopet::increaseEndearing(int percentage) {
    endearing += endearing*(percentage/100);
}

Chronodog::Chronodog(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _endearing, double _olfaction, double _excavation): Chronopet(_name, _type, _travelAge, _realAge, _isAlive,_isRetired,  _ability, _endearing) {
    olfaction = _olfaction;
    excavation = _excavation;
}

void Chronodog::increaseOlfaction(int percentage) {
    olfaction += olfaction*(percentage/100);
}

void Chronodog::increaseExcavation(int percentage) {
    excavation += excavation*(percentage/100);
}

Chronocat::Chronocat(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _endearing, double _hunting, double _climbing): Chronopet(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability, _endearing) {
    hunting = _hunting;
    climbing = _climbing;
}

void Chronocat::increaseHunting(int percentage) {
    hunting += hunting*(percentage/100);
}

void Chronocat::increaseClimbing(int percentage) {
    climbing += climbing*(percentage/100);
}

Chronobird::Chronobird(string _name, string _type, int _travelAge, int _realAge, bool _isAlive, bool _isRetired, double _ability, double _endearing, double _scouting, double _collecting): Chronopet(_name, _type, _travelAge, _realAge, _isAlive, _isRetired, _ability, _endearing) {
    scouting = _scouting;
    collecting = _collecting;
}

void Chronobird::increaseScouting(int percentage) {
    scouting += scouting*(percentage/100);
}

void Chronobird::increaseCollecting(int percentage) {
    collecting += collecting*(percentage/100);
}

void Chrononaut::kill() {
    isAlive = false; // Don't fear the reaper
    ability = 0;
}

string Chrononaut::getName() {
    return name;
}

bool Chrononaut::isLiving() {
    return isAlive;
}

bool Chrononaut::isJumpEngineer() {
    return false;
}

bool JumpEngineer::isJumpEngineer() {
    return true;
}

bool Chrononaut::isDoctor() {
    return false;
}

bool Doctor::isDoctor() {
    return true;
}

bool Chrononaut::isHistorian() {
    return false;
}

bool Historian::isHistorian() {
    return true;
}

bool Chrononaut::isSecurity() {
    return false;
}

bool Security::isSecurity() {
    return true;
}

bool Chrononaut::isChronodog() {
    return false;
}

bool Chronodog::isChronodog() {
    return true;
}

bool Chrononaut::isChronocat() {
    return false;
}

bool Chronocat::isChronocat() {
    return true;
}

bool Chrononaut::isChronobird() {
    return false;
}

bool Chronobird::isChronobird() {
    return true;
}

void Chrononaut::increaseAbility(int percent) {
    ability += ability * percent/100;
}

void Chrononaut::retire() {
    isRetired = true;
}

bool Chrononaut::hasRetired() {
    return isRetired;
}

void Chrononaut::event() {
    cout << "Chrononaut Event" << endl;
}

void JumpEngineer::event() {
    cout << "       EVENT: JUMP ENGINEER" << endl;

    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 5/volatility); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "           " << getName() << " the " << getType() << " has spontaneously combusted." << endl;
        kill();
    } else {
        cout << "           " << getName() << " the " << getType() << " is looking increasingly more volatile." << endl;
        increaseVolatility(5);
    }

}

void Doctor::event() {
    cout << "       EVENT: DOCTOR" << endl;

    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 2); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "           " << getName() << " the " << getType() << " has gained a new medical qualification." << endl;
        cout << "           Doctor will be better at preventing plagues." << endl;
        increaseQualifications(5);
    } else {
        cout << "           " << getName() << " the " << getType() << " has discovered some new medical knowledge from the locals." << endl;
        cout << "           Doctor will be better at reducing the death toll from plagues." << endl;
        increaseIntelligence(5);
    }
}

void Historian::event() {
    cout << "       EVENT: HISTORIAN" << endl;
    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 2); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "           " << getName() << " the " << getType() << " has gained new archeological qualifications." << endl;
        cout << "           Clues and artefacts will be found sooner from now on." << endl;
        increaseQualifications(5);
    } else {
        cout << "           " << getName() << " the " << getType() << " has learned new wisdom from the locals." << endl;
        cout << "           Clues and artefacts will be found sooner from now on." << endl;
        increaseWisdom(5);
    }
}

void Security::event() {
    cout << "       EVENT: SECURITY" << endl;
    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 2); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "           " << getName() << " the " << getType() << " has been working on their strength at the gym." << endl;
        cout << "           Skirmishes will have a lower death toll from now on." << endl;
        increaseStrength(5);
    } else {
        cout << "           " << getName() << " the " << getType() << " has been discussing with local diplomats." << endl;
        cout << "           Better diplomacy will reduce the chance of skirmishes." << endl;
        increaseDiplomacy(5);
    }
}

void Chronodog::event() {
    cout << "       EVENT: CHRONODOG" << endl;
    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 2); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "           " << getName() << " the " << getType() << " is getting better at smelling." << endl;
        cout << "           Clues will be easier to find from now on." << endl;
        increaseOlfaction(5);
    } else {
        cout << "           " << getName() << " the " << getType() << " is getting better at digging." << endl;
        cout << "           Artefacts will be easier to find from now on." << endl;
        increaseExcavation(5);
    }
}

void Chronocat::event() {
    cout << "       EVENT: CHRONOCAT" << endl;
    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 2); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "           " << getName() << " the " << getType() << " is getting better at hunting." << endl;
        cout << "           With the reduction in the rat population, plagues become less common." << endl;
        increaseHunting(5);
    } else {
        cout << "           " << getName() << " the " << getType() << " is getting better at climbing." << endl;
        cout << "           The Chronocat is better able to find clues." << endl;
        increaseClimbing(5);
    }
}

void Chronobird::event() {
    cout << "       EVENT: CHRONOCAT" << endl;
    uniform_int_distribution<unsigned> eventProbabilityDistr(1, 2); 
    default_random_engine randEng; 
    randEng.seed(random_device{}()); 
    int eventProbability = eventProbabilityDistr(randEng);

    if (eventProbability == 1) {
        cout << "       EVENT: CHRONOBIRD" << endl;
        cout << "           " << getName() << " the " << getType() << " has upgraded its wings." << endl;
        cout << "           With this improved scouting ability skirmishes will be less common." << endl;
        increaseScouting(5);
    } else {
        cout << "       EVENT: CHRONOBIRD" << endl;
        cout << "           " << getName() << " the " << getType() << " has upgraded its eyesight." << endl;
        cout << "           With this improved collecting ability artefacts will be found more readily." << endl;
        increaseCollecting(5);
    }
}

double JumpEngineer::getVolatility() {
    return volatility*ability;
}

double Doctor::getQualifications() {
    return qualifications*ability;
}

double Doctor::getIntelligence() {
    return intelligence*ability;
}

double Historian::getQualifications() {
    return qualifications*ability;
}

double Historian::getWisdom() {
    return wisdom*ability;
}

double Security::getStrength() {
    return strength*ability;
}

double Security::getDiplomacy() {
    return diplomacy*ability;
}

double Chronopet::getEndearing() {
    return endearing*ability;
}

double Chronodog::getOlfaction() {
    return olfaction*ability;
}

double Chronodog::getExcavation() {
    return excavation*ability;
}

double Chronocat::getHunting() {
    return hunting*ability;
}

double Chronocat::getClimbing() {
    return climbing*ability;
}

double Chronobird::getScouting() {
    return scouting*ability;
}

double Chronobird::getCollecting() {
    return collecting*ability;
}

void Chrononaut::printCharacteristics() {
    cout << "Null" << endl;
}

void JumpEngineer::printCharacteristics() {
    cout << "   Volatility: " << floor(volatility*100) << "%" << endl;
}

void Doctor::printCharacteristics() {
    cout << "   Qualifications: " << floor(qualifications*100) << "%" << endl;
    cout << "   Intelligence: " << floor(intelligence*100) << "%" << endl;
}

void Historian::printCharacteristics() {
    cout << "   Qualifications: " << qualifications << endl;
    cout << "   Wisdom: " << floor(wisdom*100) << "%" << endl;
}

void Security::printCharacteristics() {
    cout << "   Strength: " << floor(strength*100) << "%" << endl;
    cout << "   Diplomacy: " << floor(diplomacy*100) << "%" << endl;
}

void Chronodog::printCharacteristics() {
    cout << "   Endearing: " << floor(endearing*100) << "%" << endl;
    cout << "   Olfaction: " << floor(olfaction*100) << "%" << endl;
    cout << "   Excavation: " << floor(excavation*100) << "%" << endl;
}

void Chronocat::printCharacteristics() {
    cout << "   Endearing: " << floor(endearing*100) << "%" << endl;
    cout << "   Hunting: " << floor(hunting*100) << "%" << endl;
    cout << "   Climbing: " << floor(climbing*100) << "%" << endl;
}

void Chronobird::printCharacteristics() {
    cout << "   Endearing: " << floor(endearing*100) << "%" << endl;
    cout << "   Scouting: " << floor(scouting*100) << "%" << endl;
    cout << "   Collecting: " << floor(collecting*100) << "%" << endl;
}