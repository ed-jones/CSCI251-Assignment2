#include "header.h"
using namespace std;

Artefact::Artefact(string _name, string _description, int _clue) {
    name = _name;
    description = _description;
    clue = _clue;
    informationStatus = false;
    clueStatus = false;
    counterfeit = false;
}

void Artefact::print() {
    cout << "   Name: " << name << endl;
    cout << "   Description: " << description << endl;
    if (counterfeit) {
        cout << "   Is known to be a counterfeit" << endl;
    }
    cout << "   Information: " << getPrettyInformation() << endl;
    for (string info : information) {
        cout << "       " << info << endl;
    }
    cout << endl;
}

vector<Artefact *> generateArtefacts(int artefactCount) {
    vector<int> randomArtefactNumbers; // vector to store assigned artefact numbers as we go
    vector<Artefact *> randomArtefacts;
    for (int i=1; i<=artefactCount; i++) {
        while (true) {
            uniform_int_distribution<unsigned> uniform(1, 5); // Create a distribution from 1 to 5
            default_random_engine randEng; 
            randEng.seed(random_device{}()); // Seed the random number generator
            int newRandomArtefactNumber = uniform(randEng); // pick a whole number inclusively between 1 and 5
            bool unique = true;

            for (int randomArtefactNumber : randomArtefactNumbers) {
                if (randomArtefactNumber == newRandomArtefactNumber) {
                    unique = false;
                }
            }

            if (unique) {
                randomArtefactNumbers.push_back(newRandomArtefactNumber); // add this artefact number to vector of chosen artefact numbers
                
                switch(newRandomArtefactNumber) {
                    case 1:
                        randomArtefacts.emplace_back(new Artefact("Antikythera Mechanism", "An ancient Greek analogue computer, possibly designed by Archimedes himself.", -87));
                        break;
                    case 2:
                        randomArtefacts.emplace_back(new Artefact("Baghdad Battery", "An ancient battery that predates the invention of the Voltaic Pile", 224));
                        break;
                    case 3:
                        randomArtefacts.emplace_back(new Artefact("Goddard Coin", "A medieval Norwegian coin discovered in North America. Evidence supporting pre-Colombian trans-Oceanic contact.", 1067));
                        break;
                    case 4:
                        randomArtefacts.emplace_back(new Artefact("Voynich Manuscript", "An undecyphered tome written in an unknown writing system. Dated back to the early 15th century, this book includes descriptions of herbology, astronomy, astrology, biology, cosmology and pharmacology.", 1404));
                        break;
                    case 5:
                        randomArtefacts.emplace_back(new Artefact("Colossus Computer", "A set of computers built by British codebreakers during WWII. These were the first electronic, programmable computers. Most were immediately destroyed after the war.", 1943));
                        break;
                }
                
                break;
            }
        }
    }
    return randomArtefacts;
}


int Artefact::getClue() {
    return clue;
}

string Artefact::getName() {
    return name;
}

void Artefact::setClue(int _clue) {
    clue = _clue;
    clueStatus = true;
}

string Artefact::getPrettyInformation() {
    return to_string(information.size()*10) + "%";
}

bool Artefact::foundInformation() {
    return informationStatus;
}

bool Artefact::foundClue() {
    return clueStatus;
}

void Artefact::findArtefactInfo(int year) {
    informationStatus = true;

    
    string prettyYear;
    if (year > 0) {
        prettyYear = to_string(year) + " CE";
    } else if (year < 0) {
        prettyYear = to_string(-1*year) + " BCE";
    } else {
        prettyYear = "Error: There is no year zero in the Gregorian calendar.";
    }

    switch(information.size() + 1) {
        case 1:
            information.push_back("Year of Manufacture (discovered " + prettyYear + ")");
            break;
        case 2:
            information.push_back("Original Manufacturer (discovered " + prettyYear + ")");
            break;
        case 3:
            information.push_back("Original Use (discovered " + prettyYear + ")");
            break;
        case 4:
            information.push_back("Location of Manufacture (discovered " + prettyYear + ")");
            break;
        case 5:
            information.push_back("Reason for Manufacture (discovered " + prettyYear + ")");
            break;
        case 6:
            information.push_back("Reason for Going Missing (discovered " + prettyYear + ")");
            break;
        case 7:
            information.push_back("Monetary Value at Time of Manufacture (discovered " + prettyYear + ")");
            break;
        case 8:
            information.push_back("How it was Manufactured (discovered " + prettyYear + ")");
            break;
        case 9:
            information.push_back("Cultural Significance (discovered " + prettyYear + ")");
            break;
        case 10:
            information.push_back("Religious Significance (discovered " + prettyYear + ")");
            break;
    }
}

void Artefact::resetInfoClueStatus() {
    informationStatus = false;
    clueStatus = false;
}

bool Artefact::isCounterfeit() {
    return counterfeit;
}

void Artefact::setCounterfeit() {
    counterfeit = true;
}

bool Artefact::foundAllInformation() {
    bool success = false;

    if (information.size() == 10) {
        success = true;
    } 

    if (counterfeit) {
        success = true;
    } 

    return success;
}