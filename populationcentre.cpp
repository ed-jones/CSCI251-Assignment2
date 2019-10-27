#include "header.h"
using namespace std;

// Copy constructor
PopulationCentre::PopulationCentre(const PopulationCentre & _populationCentre) : techEra(_populationCentre.technology) {

    if (_populationCentre.populationType == 5) {
        // Metropolis
        name = "Metropolis";
    } else if (_populationCentre.populationType == 4) {
        // City
        name = "City";
    } else if (_populationCentre.populationType == 3) {
        // Town
        name = "Town";
    } else if (_populationCentre.populationType == 2) {
        // Village
        name = "Village";
    } else if (_populationCentre.populationType == 1) {
        // Hamlet
        name = "Hamlet";
    } else {
        name = "Error: populationType cannot be of size " + to_string(populationType);
    }


    year = _populationCentre.year;
    yearsSinceJump = _populationCentre.yearsSinceJump;
    population = _populationCentre.population;
    populationType = _populationCentre.populationType;
    technology = _populationCentre.technology;
    basePopulationGrowthRate = _populationCentre.basePopulationGrowthRate;
    baseTechGrowthRate = _populationCentre.baseTechGrowthRate;
    artefact = _populationCentre.artefact;
    chrononauts = _populationCentre.chrononauts;
    majorEvents = _populationCentre.majorEvents;
}

// Initial constructor only used once
PopulationCentre::PopulationCentre(string _name, int _year, int _yearsSinceJump, int _population, int populationType, int _technology, double _basePopulationGrowthRate, double _baseTechGrowthRate, Artefact *_artefact, vector<unique_ptr<Chrononaut>> *_chrononauts, vector<string> _majorEvents) : techEra(_technology) {
    name = _name;
    year = _year;
    yearsSinceJump = _yearsSinceJump;
    population = _population;
    technology = _technology;
    basePopulationGrowthRate = _basePopulationGrowthRate; // 0.0035
    baseTechGrowthRate = _baseTechGrowthRate; // 0.00089
    artefact = _artefact;
    chrononauts = _chrononauts;
    majorEvents = _majorEvents;
}

// Increment Population Centre
void PopulationCentre::operator++() {

    bool noEvents = true;

    year++; // Increment year

    if (year == 0) {
        year++; // There is no year 0!
    } 
    
    yearsSinceJump++;

    techEra = TechEra(year); // Update techEra to the new year

    population = population*(1+basePopulationGrowthRate); // Increase population
    technology = technology*(1+baseTechGrowthRate); // Increase technology 0.00089

    vector<int> validChrononauts; // Create a list of valid chrononaut indexes
    int i = 0;
    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->isLiving() && !chrononaut->hasRetired()) {
            validChrononauts.push_back(i);
        }
        i++;
    }

    transition();

    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->isLiving()) {
            chrononaut->ageUp(); // Increase chrononaut age
        }
    }

    if (validChrononauts.size() != 0) {
        JumpEngineer *jumpEngineer = (JumpEngineer *)&*(*chrononauts)[0];
        Doctor *doctor = (Doctor *)&*(*chrononauts)[1];
        Historian *historian = (Historian *)&*(*chrononauts)[2];
        Security *security = (Security *)&*(*chrononauts)[3];
        Chronodog *chronodog = (Chronodog *)&*(*chrononauts)[4];
        Chronocat *chronocat = (Chronocat *)&*(*chrononauts)[5];
        Chronobird *chronobird = (Chronobird *)&*(*chrononauts)[6];


        // EVENTS

        default_random_engine randEng; 

        // Find artefact information
        
        uniform_int_distribution<unsigned> artefactProbability(1, ceil((100*historian->getQualifications()*chronodog->getExcavation()*chronobird->getCollecting())/yearsSinceJump)+1); 
        randEng.seed(random_device{}()); 

        if (artefactProbability(randEng) == 1) {
            if (!artefact->foundInformation()) {
                findArtefactInfo();
                noEvents = false;
            }
        }

        if (yearsSinceJump > 5) { // must take at least 5 years to find the jump clue


            // Find jump clue

            uniform_int_distribution<unsigned> clue(1, ceil((100*historian->getWisdom()*chronodog->getOlfaction()*chronocat->getClimbing())/yearsSinceJump)+1); 

            if (clue(randEng) == 1) {
                if (!artefact->foundClue()) {
                    discoverJumpClue();
                    noEvents = false;
                }
            }

            // Realise Counterfeit

            uniform_int_distribution<unsigned> counterfeit(1, 100); 

            if (techEra.getName() == "Classical") {
                uniform_int_distribution<unsigned> counterfeit(1, 50); 
            } 

            if (counterfeit(randEng) == 1) {
                realiseCounterfeit();
                noEvents = false;
            }


        }

        // Plague

        uniform_int_distribution<unsigned> plagueProbability(1, ceil(20*doctor->getQualifications()*chronocat->getHunting())); 

        if (techEra.getName() == "Medieval Period") {
            uniform_int_distribution<unsigned> plagueProbability(1, ceil(10*doctor->getQualifications()*chronocat->getHunting())); 
        }

        if (plagueProbability(randEng) == 1 && techEra.getName() != "Information Age") {
            plague();
            noEvents = false;
        }


        // Skirmish
        uniform_int_distribution<unsigned> skirmishProbability(1, ceil(20*security->getStrength()*chronobird->getScouting())); 

        if (skirmishProbability(randEng) == 1) {
            skirmish();
            noEvents = false;
        }

        // Tech Breakthrough
        uniform_int_distribution<unsigned> breakthrough(1, 10); 
        if (name == "Renaissance") {
            uniform_int_distribution<unsigned> breakthrough(1, 5); 
        } 

        
        if (breakthrough(randEng) == 1) {
            techBreakthrough();
            noEvents = false;
        }

        // Revolution

        uniform_int_distribution<unsigned> revolutionProbability(1, 20); 

        if (techEra.getName() == "Industrial Revolution") {
            uniform_int_distribution<unsigned> revolutionProbability(1, 10); 
        } 


        
        if (revolutionProbability(randEng) == 1) {
            revolution();
            noEvents = false;
        }

        // Interactions with locals
        uniform_int_distribution<unsigned> interactionDist(1, 100*chronodog->getEndearing()*chronocat->getEndearing()*chronobird->getEndearing()); 


        if (interactionDist(randEng) == 1) {
            localInteraction();
            noEvents = false;
        }

        // Special Chrononaut Event

        uniform_int_distribution<unsigned> chronoDist(1, 10); 
        default_random_engine chronoProbability; 
        chronoProbability.seed(random_device{}()); 

        uniform_int_distribution<unsigned> chrononautDist(0, validChrononauts.size()-1); 
        default_random_engine chrononautEngine; 
        chrononautEngine.seed(random_device{}());

        int chrononautIndex = chrononautDist(chrononautEngine); // Pick a random chrononaut index
        Chrononaut *randomChrononaut = &*(*chrononauts)[chrononautIndex]; // Pick a random chrononaut using the index

        
        if (chronoDist(chronoProbability) == 1) {
            if (randomChrononaut->isLiving()) {
                randomChrononaut->event();
                noEvents = false;
            }
        }
        
        if (noEvents) {
            cout << "       NO EVENTS THIS YEAR" << endl;
        }


    } else {
        cout << "       ALL CHRONONAUTS ARE DEAD OR RETIRED - MISSION FAILED" << endl;
    }
}

// Jump Population Centre to new year
void PopulationCentre::jump(int _year) {
    yearsSinceJump = 0;
    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->isJumpEngineer()) {
            if (!chrononaut->isLiving()) {
                cout << "Since Jump Engineer " << chrononaut->getName() << " is dead the Chrononauts can no longer jump." << endl;
                cout << "All surviving Chrononauts are now stuck in the year " << getPrettyYear() << " where they will live out the rest of their lives..." << endl;
                exit(EXIT_FAILURE);
            }
        }
    }
    if (_year == 0) {
        _year = 1; // There is no year 0!
    }

    int travelDistance = year - _year;
    year = _year; // Set current year to jump year

    techEra = TechEra(technology); // Update techEra to the new year

    // Recalculate population size - unfortunately there can be a large margin of error when doing this
    if (travelDistance > 0) { // Going back in time creates a new parallel universe based on the original universe in 2525
        population = CURRENT_POP*pow(1-basePopulationGrowthRate, CURRENT_YEAR - _year); 
        technology = CURRENT_TECH*pow(1-baseTechGrowthRate, CURRENT_YEAR - _year); 
    } else { // Going forward in time
        population = population*pow(1+basePopulationGrowthRate, abs(travelDistance));
        technology = technology*pow(1+baseTechGrowthRate, abs(travelDistance));
    }

    transition();

}

void PopulationCentre::print() {
    cout << "   Tech Era: " << techEra.getName() << endl;
    cout << "   Population Type: " << name << endl;
    cout << "   Year: " << getPrettyYear() << endl;
    cout << "   Total Population " << getPrettyPopulation() << endl;
}

string PopulationCentre::getPrettyYear() {
    string prettyYear; // Create a string that holds the year value formatted as CE or BCE

    if (year > 0) {
        prettyYear = to_string(year) + " CE";
    } else if (year < 0) {
        prettyYear = to_string(-1*year) + " BCE";
    } else {
        prettyYear = "Error: There is no year zero in the Gregorian calendar.";
    }

    return prettyYear;
}


string PopulationCentre::getEra() {
    return techEra.getName();
}

string PopulationCentre::getPrettyPopulation() {
    string prettyPopulation = to_string((int)population);
    int insertPosition = prettyPopulation.length() - 3;
    while (insertPosition > 0) {
        prettyPopulation.insert(insertPosition, ",");
        insertPosition-=3;
    }
    return prettyPopulation;
}

void PopulationCentre::findArtefactInfo() {
    cout << "       EVENT: FOUND ARTEFACT INFO" << endl;
    artefact->findArtefactInfo(year);
}

void PopulationCentre::discoverJumpClue() {
    cout << "       EVENT: FOUND CLUE" << endl;
    int clue;

    while (true) {
        normal_distribution<double> yearDistribution(artefact->getClue(), 500); // Create a distribution 
        default_random_engine clueEng; // Create random engine variable
        clueEng.seed(random_device{}()); // Seed the random number generator
        clue = yearDistribution(clueEng); 
        clue = -abs(clue);
        if (clue >= -500 && clue <= 3000) {
            break;
        }
    }
    artefact->setClue(clue);
}

void PopulationCentre::realiseCounterfeit() {
    cout << "       EVENT: REALISE COUNTERFEIT" << endl;
    cout << "           The Chrononauts have discovered that their original artefact back in 2525 is a fraud!" << endl;
    cout << "           Ending this search" << endl;
    
    artefact->setCounterfeit();

}

void PopulationCentre::plague() {
    // Calculate random death count. Never more than 25%
    uniform_int_distribution<unsigned> plagueDeathCountDistribution(1, population/4); 
    default_random_engine plagueDeathCountEngine; 
    plagueDeathCountEngine.seed(random_device{}());
    int plagueDeathCount = plagueDeathCountDistribution(plagueDeathCountEngine);
    // Add commas to death count for nice printing
    string prettyDeathCount = to_string((int)plagueDeathCount);
    int insertPosition = prettyDeathCount.length() - 3;
    while (insertPosition > 0) {
        prettyDeathCount.insert(insertPosition, ",");
        insertPosition-=3;
    }

    // Print event details
    cout << "       EVENT: PLAGUE" << endl;
    cout << "           " << prettyDeathCount << " people have died or ";
    printf("%.2f", ((double)plagueDeathCount/population)*100);
    cout << "% of the total population" << endl;

    population -= plagueDeathCount;

    // Kill a Chrononaut
    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->isLiving()) {
            uniform_int_distribution<unsigned> chrononautDeathDistribution(1, 100); // 1 in 100 chance this chrononaut dies
            default_random_engine chrononautDeathEngine; 
            chrononautDeathEngine.seed(random_device{}()); 
            if (chrononautDeathDistribution(chrononautDeathEngine) == 1) {
                chrononaut->kill();
                cout << "           " << chrononaut->getName();
                cout << " the " << chrononaut->getType() << " caught the plague and died" << endl;
                majorEvents.push_back(chrononaut->getName() + " the " + chrononaut->getType() + " caught the plague and died");
            }
        }
    }
}

void PopulationCentre::skirmish() {
    // Calculate random death count. Never more than 12.5%
    uniform_int_distribution<unsigned> skirmishDeathCountDistribution(1, population/8); 
    default_random_engine skirmishDeathCountEngine; 
    skirmishDeathCountEngine.seed(random_device{}());
    int skirmishDeathCount = skirmishDeathCountDistribution(skirmishDeathCountEngine);
    // Add commas to death count for nice printing
    string prettyDeathCount = to_string((int)skirmishDeathCount);
    int insertPosition = prettyDeathCount.length() - 3;
    while (insertPosition > 0) {
        prettyDeathCount.insert(insertPosition, ",");
        insertPosition-=3;
    }

    // Print event details
    cout << "       EVENT: SKIRMISH" << endl;
    cout << "           " << prettyDeathCount << " people have died or ";
    printf("%.2f", ((double)skirmishDeathCount/population)*100);
    cout << "% of the total population" << endl;

    population -= skirmishDeathCount;

    // Kill a Chrononaut
    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->isLiving()) {
            uniform_int_distribution<unsigned> chrononautDeathDistribution(1, 100); // 1 in 100 chance this chrononaut dies
            default_random_engine chrononautDeathEngine; 
            chrononautDeathEngine.seed(random_device{}()); 
            if (chrononautDeathDistribution(chrononautDeathEngine) == 1) {
                chrononaut->kill();
                cout << "           " << chrononaut->getName();
                cout << " the " << chrononaut->getType() << " has been killed in the skirmish" << endl;
                majorEvents.push_back(chrononaut->getName() + " the " + chrononaut->getType() + " has been killed in the skirmish");

            }
        }
    }

    // Grant Tech Boost
    uniform_int_distribution<unsigned> techBoostDist(1, 5); 
    default_random_engine techBoostEngine; 
    techBoostEngine.seed(random_device{}());
    int techBoost = techBoostDist(techBoostEngine);
    cout << "           Technology increased by " << techBoost << "% from " << technology;
    technology = technology + techBoost;
    cout << "% to " << technology << "%" << endl;
}

void PopulationCentre::techBreakthrough() {
    cout << "       EVENT: TECH BREAKTHROUGH" << endl;

    // Grant Tech Boost
    uniform_int_distribution<unsigned> techBoostDist(1, 10); 
    default_random_engine techBoostEngine; 
    techBoostEngine.seed(random_device{}());
    int techBoost = techBoostDist(techBoostEngine);
    cout << "           Technology increased by " << techBoost << "% from " << technology;
    technology = technology + techBoost;
    cout << "% to " << technology << "%" << endl;
}

void PopulationCentre::revolution() {
    cout << "       EVENT: REVOLUTION" << endl;
    uniform_int_distribution<unsigned> revolutionDist(1, 4); 
    default_random_engine revolutionEngine; 
    revolutionEngine.seed(random_device{}());

    uniform_int_distribution<unsigned> populationDist(1, population/8); 
    default_random_engine populationEngine; 
    populationEngine.seed(random_device{}());
    int populationChange = populationDist(populationEngine);

    string prettyPopulationChange = to_string((int)populationChange);
    int insertPosition = prettyPopulationChange.length() - 3;
    while (insertPosition > 0) {
        prettyPopulationChange.insert(insertPosition, ",");
        insertPosition-=3;
    }

    string gov = "monarchy";
    string leader = "king";
    string country = "kingdom";
    if (techEra.getName() == "Information Age") {
        gov = "government";
        leader = "president";
        country = "nation";
    }
    switch (revolutionDist(revolutionEngine)) {
        case 1:
            cout << "           The people's revolt has successfully overthrown the " << gov << "." << endl;
            cout << "           Under this new republic the " << country << " thrives." << endl;
            cout << "           Population increases by " << prettyPopulationChange << " people or ";
            printf("%.2f", ((double)populationChange/population)*100);
            cout << "%" << endl;
            population += populationChange;
            break;
        case 2:
            cout << "           The people's revolt was swiftly dealt with by the " << gov << ". Long live the " << leader <<"." << endl;
            cout << "           Population decreases by " << prettyPopulationChange << " people or ";
            printf("%.2f", ((double)populationChange/population)*100);
            cout << "%" << endl;
            population -= populationChange;
            break;
        case 3:
            cout << "           The people's revolt has successfully overthrown the " << gov << "." << endl;
            cout << "           The new republic is a failure. The " << gov << " is reinstated." << endl;
            cout << "           Population decreases by " << prettyPopulationChange << " people or ";
            printf("%.2f", ((double)populationChange/population)*100);
            cout << "%" << endl;
            population -= populationChange;
            break;
        case 4:
            cout << "           The " << gov << " has compromised with the demands of the people's revolt." << endl;
            cout << "           The " << country << " thrives and the " << gov << " remains." << endl;
            cout << "           Population increases by " << prettyPopulationChange << " people or ";
            printf("%.2f", ((double)populationChange/population)*100);
            cout << "%" << endl;
            population += populationChange;
            break;

    }

}

void PopulationCentre::localInteraction() {
    cout << "       EVENT: LOCAL INTERACTION" << endl;

    uniform_int_distribution<unsigned> interactionDist(1, 5); 
    default_random_engine interactionEngine; 
    interactionEngine.seed(random_device{}());

    uniform_int_distribution<unsigned> chrononautDist(0, chrononauts->size()-1); 
    default_random_engine chrononautEngine; 
    chrononautEngine.seed(random_device{}());

    uniform_int_distribution<unsigned> abilityDist(1, 5); 
    default_random_engine abilityEngine; 
    abilityEngine.seed(random_device{}());
    int abilityIncreasePercent = abilityDist(abilityEngine);
    int chrononautIndex = chrononautDist(chrononautEngine);


    Chrononaut *randomChrononaut = &*((*chrononauts)[chrononautIndex]);

    int i = 0;
    while (!randomChrononaut->isLiving() || randomChrononaut->hasRetired()) {
        chrononautIndex = chrononautDist(chrononautEngine);
        randomChrononaut = &*(*chrononauts)[chrononautIndex];
        if (i>1000) {
            cerr << "Error: timed out trying to find a random chrononaut for this event" << endl;
            exit(EXIT_FAILURE); // Quit the program
        }
        i++;
    }

    uniform_int_distribution<unsigned> techBoostDist(1, 10); 
    default_random_engine techBoostEngine; 
    techBoostEngine.seed(random_device{}());
    int techBoost = techBoostDist(techBoostEngine);




    switch (interactionDist(interactionEngine)) {
        case 1:
            // Chrononaut falls in love with local and stays in this timeline
            cout << "           " << randomChrononaut->getName() << " the " << randomChrononaut->getType() << " has fallen in love and married a local." << endl;
            cout << "           " << randomChrononaut->getName() << " has now retired from the mission." << endl;
            randomChrononaut->retire();
            majorEvents.push_back(randomChrononaut->getName() + " the " + randomChrononaut->getType() + " has fallen in love and married a local.");
            break;
        case 2:
            // Chrononauts learn from locals
            cout << "           " << randomChrononaut->getName() << " the " << randomChrononaut->getType() << " has been studying with local experts." << endl;
            cout << "           Ability increased for " << randomChrononaut->getName() << " by " << abilityIncreasePercent << "%" << endl;
            randomChrononaut->increaseAbility(abilityIncreasePercent);
            break;
        case 3:
            // Chrononaut is burned as a witch
            // OR Chrononaut is arrested depending on tech era
            if (techEra.getName() == "Information Age") {
                cout << "           " << randomChrononaut->getName() << " the " << randomChrononaut->getType() << " has been arrested by the local police department." << endl;
                cout << "           " << randomChrononaut->getName() << " has now retired from the mission." << endl;
                majorEvents.push_back(randomChrononaut->getName() + " the " + randomChrononaut->getType() + " has been arrested by the local police department.");

                randomChrononaut->retire();
            } else {
                cout << "           " << randomChrononaut->getName() << " the " << randomChrononaut->getType() << " has been burned as a witch by superstitious locals." << endl;
                cout << "           " << randomChrononaut->getName() << " did not survive." << endl;
                majorEvents.push_back(randomChrononaut->getName() + " the " + randomChrononaut->getType() + " has been burned as a witch by superstitious locals.");
                randomChrononaut->kill();
            }

            break;
        case 4:
            // Chrononaut is crowned king
            if (techEra.getName() == "Information Age") {
                cout << "           " << randomChrononaut->getName() << " the " << randomChrononaut->getType() << " has been elected president." << endl;
                majorEvents.push_back(randomChrononaut->getName() + " the " + randomChrononaut->getType() + " has been elected president.");
            } else {
                cout << "           " << randomChrononaut->getName() << " the " << randomChrononaut->getType() << " has been chosen by a small council to be king." << endl;
                majorEvents.push_back(randomChrononaut->getName() + " the " + randomChrononaut->getType() + " has been chosen by a small council to be king.");
            }
            cout << "           " << randomChrononaut->getName() << " has now retired from the mission." << endl;
            randomChrononaut->retire();

            break;
        case 5:
            // Tech stolen from chrononauts
            cout << "           Locals have made a technological breakthrough by investigating Chrononaut technology." << endl;
            cout << "           Technology increased by " << techBoost << "% from " << technology;
            technology = technology + techBoost;
            cout << "% to " << technology << "%" << endl;
    }
}

void PopulationCentre::setArtefact(Artefact *_artefact) {
    artefact = _artefact;
}

bool PopulationCentre::chrononautsStatus() {
    bool status = false;
    vector<int> validChrononauts; // Create a list of valid chrononaut indexes
    int i = 0;
    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->isLiving() && !chrononaut->hasRetired()) {
            validChrononauts.push_back(i);
        }
        i++;
    }

    if (validChrononauts.size() == 0) {
        status = true;
    }

    return status;
}

bool PopulationCentre::jumpEngineerStatus() {
    bool status = false;
    for (unique_ptr<Chrononaut> &chrononaut : *chrononauts) {
        if (chrononaut->getType() == "Jump Engineer") {
            if (!chrononaut->isLiving() || chrononaut->hasRetired()) {
                status = true;
            }
        }
    }

    return status;
}

vector<string> PopulationCentre::getMajorEvents() {
    return majorEvents;
}

void PopulationCentre::transition() {
    if (population >= 10000000) {
        // Metropolis
        if (populationType < 5) { 
            populationType++;
        } else if (populationType > 5) {
            populationType--;
        }
    } else if (population >= 200000) {
        // City
        if (populationType < 4) {
            populationType++;
        } else if (populationType > 4) {
            populationType--;
        }
    } else if (population >= 10000) {
        // Town
        if (populationType < 3) { 
            populationType++;
        } else if (populationType > 3) {
            populationType--;
        }
    } else if (population >= 1000) {
        // Village
        if (populationType < 2) { 
            populationType++;
        } else if (populationType > 2) {
            populationType--;
        }
    } else if (population > 0) {
        // Hamlet
        if (populationType < 1) { 
            populationType++;
        } else if (populationType > 1) {
            populationType--;
        }
    }

    switch(populationType) {
        case 1:
            name = "Hamlet";
            *this = Hamlet(*this);
        case 2:
            name = "Village";
            *this = Village(*this);
        case 3:
            name = "Town";
            *this = Town(*this);
        case 4:
            name = "City";
            *this = City(*this);
        case 5:
            name = "Metropolis";
            *this = Metropolis(*this);
    }
}

Hamlet::Hamlet(const PopulationCentre & _populationCentre) : PopulationCentre(_populationCentre) {
    shrine = 0.9; // Very Small Plague Reduction
}

Village::Village(const PopulationCentre & _populationCentre) : PopulationCentre(_populationCentre) {
    monastery = 0.8; // Mild Plague Reduction
    workshop = 1.2;
}

Town::Town(const PopulationCentre & _populationCentre) : PopulationCentre(_populationCentre) {
    sickhouse = 0.5; // Medium Plague Reduction
    blacksmith = 1.5;
    motel = 0.8;
}

City::City(const PopulationCentre & _populationCentre) : PopulationCentre(_populationCentre) {
    clinic = 0.8; // High Plague Reduction
    factory = 2;
    hotel = 0.6;
    airport = 0.6;
    
}

Metropolis::Metropolis(const PopulationCentre & _populationCentre) : PopulationCentre(_populationCentre) {

    hospital = 1; // Complete plague reduction
    laboratory = 0.5;
    resort = 0.4;
    spaceport = 0.4;
    hydroponicum = 0.5;
}


