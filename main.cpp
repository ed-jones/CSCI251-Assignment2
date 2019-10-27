#include "header.h"
using namespace std;

int main(int argc, char* argv[]) {

    argumentTests(argc, argv); // Will terminate program if arguments are invalid

    int artefactCount = atoi(argv[1]); // set artefactCount to the 1st argument
    int jumpsPerArtefact = atoi(argv[2]); // set jumpsPerArtefact to the 2nd argument

    vector<Artefact *> artefacts = generateArtefacts(artefactCount); // Create a vector of randomly chosen artefacts
    vector<unique_ptr<Chrononaut>> chrononauts = generateChrononauts(); // Create a vector of all chrononauts
    vector<string> majorEvents; // Create an empty string vector to be used in the populationCentre constructor
    PopulationCentre populationCentre("Metropolis", CURRENT_YEAR, 0, CURRENT_POP, 5, CURRENT_TECH, POP_GROWTH_RATE, TECH_GROWTH_RATE, artefacts[0], &chrononauts, majorEvents);

    cout << "STARTING MISSION" << endl;
    cout << endl;
    
    for (Artefact *artefact : artefacts) { // Repeat this code for each artefact
        populationCentre.setArtefact(artefact); // Update population centre to include current artefact
        for (int jump = 0; jump < jumpsPerArtefact; jump++) { // Repeat this code for allowed number of jumps (given as argument) 
            // Run this code only if all chrononauts are alive and the artefact is not known to be counterfeit 
            if (!populationCentre.chrononautsStatus() && !populationCentre.jumpEngineerStatus() && !artefact->isCounterfeit()) { 
                artefact->resetInfoClueStatus(); // Since we haven't found the clue or information yet for this jump set the "found" variables to false
                
                // Print Chrononaut status before we jump
                cout << "CHRONONAUT STATUS PRE-JUMP" << endl;
                for (unique_ptr<Chrononaut> &chrononaut : chrononauts) {
                    chrononaut->print();
                }

                // Print Population status before we jump
                cout << "POPULATION STATUS PRE-JUMP" << endl;
                populationCentre.print(); // Before jump population details
                cout << endl;

                // Print a message detailing that we are about to jump
                cout << "INITIATING JUMP SEQUENCE" << endl;
                cout << endl;

                populationCentre.jump(artefact->getClue()); // Jump to year that current clue points to

                // Print a message detailing the chrononaut status post jump
                cout << "CHRONONAUT STATUS POST-JUMP" << endl;
                for (unique_ptr<Chrononaut> &chrononaut : chrononauts) {
                    chrononaut->print();
                }

                // Print a message detailing the population status post jump
                cout << "POPULATION STATUS POST-JUMP" << endl;
                populationCentre.print(); // After jump population details
                cout << endl;

                // Print a message detailing which artefact we are investigating
                cout << "INVESTIGATING ARTEFACT \"" << artefact->getName() << "\"" << endl; 


                int i = 0; // Use this as a counter to make sure we don't get stuck in an infinite loop

                while (true) { // Loop until we find the clue and information
                    // Print a messsage detailing the year, the tech era and the current population
                    cout << "   YEAR " << populationCentre.getPrettyYear() << " - Tech Era: " << populationCentre.getEra() << " - Population: " << populationCentre.getPrettyPopulation() << endl;
                    
                    ++populationCentre; // Use the overloaded++ operator to increase population

                    // If all chrononauts are dead stop running this loop
                    if (populationCentre.chrononautsStatus()) { 
                        break; 
                    }

                    // If artefact is found to be counterfeit in 2525
                    if (artefact->isCounterfeit()) {
                        break;
                    }

                    // If the Chrononauts have found the next clue and some information
                    if (artefact->foundInformation() && artefact->foundClue()) {
                        break;
                    }

                    // If nothing has broken this loop for over 1000 loops
                    if (i > 1000) {
                        cerr << "Error: timed out investigating artefact" << endl;
                        exit(EXIT_FAILURE); // Quit the program
                    }

                    i++;
                }

                if (jump == jumpsPerArtefact-1) { // If this is the last jump
                    cout << "       OUT OF JUMPS - MOVING TO NEXT ARTEFACT" << endl;
                    cout << "       TOTAL INFORMATION DISCOVERED: " << artefact->getPrettyInformation() << endl;
                } else {
                    cout << "       CLUE AND INFORMATION FOUND - PREPARING NEXT JUMP" << endl;
                }
                cout << endl;
            } 
        }       
    }

    bool victory = true;
    for (Artefact *artefact : artefacts) {
        if (!artefact->foundAllInformation()) {
            victory = false;
        }
    }


    // Print end of journey summary
    cout << "END OF JOURNEY SUMMARY" << endl;

        // Print a message detailing the chrononaut status post jump
    cout << "FINAL CHRONONAUT SUMMARY" << endl;
    for (unique_ptr<Chrononaut> &chrononaut : chrononauts) {
        chrononaut->print();
    }

    // Print a message detailing the population status post jump
    cout << "FINAL POPULATION STATUS" << endl;
    populationCentre.print(); // After jump population details

    cout << endl;
    cout << "ARTEFACTS: " << endl;
    for (Artefact *artefact : artefacts) {
        artefact->print(); // Print details for each artefact
    }

    cout << "MAJOR EVENTS: " << endl;
    if (populationCentre.getMajorEvents().size() == 0) { 
        cout << "   There were no major events" << endl;
    } else {
        for (string &majorEvent : populationCentre.getMajorEvents()) {
            cout << "   " << majorEvent << endl; // Print each major event
        }
    }   
    cout << endl;

    if (populationCentre.chrononautsStatus()) { // If all chrononauts are dead print the following
        cout << "ALL CHRONONAUTS ARE DEAD OR RETIRED" << endl;
        cout << endl;
    } else if (populationCentre.jumpEngineerStatus()) { // If jump engineer died print the following
        cout << "JUMP ENGINEER DEAD OR RETIRED" << endl;
        cout << endl;
    }

    if (victory) {
        cout << "MISSION SUCCESS - ALL ARTEFACTS FULLY RESEARCHED" << endl;
    } else {
        cout << "MISSION FAILED - DID NOT RESEARCH ALL ARTEFACTS" << endl;
    }
    cout << endl;

}