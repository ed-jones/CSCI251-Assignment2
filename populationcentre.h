class PopulationCentre {
    protected:
        std::string name;
        int year;
        int yearsSinceJump;
        unsigned int population;
        int populationType; // 1-5 representing each type
        double technology;
        double basePopulationGrowthRate;
        double baseTechGrowthRate;
        TechEra techEra;
        Artefact *artefact;
        std::vector<std::unique_ptr<Chrononaut>> *chrononauts;
        std::vector<std::string> majorEvents;
        void transition();
    public:
        void operator++();
        PopulationCentre(const PopulationCentre &);
        PopulationCentre(std::string, int, int, int, int, int, double, double, Artefact *, std::vector<std::unique_ptr<Chrononaut>> *, std::vector<std::string>); 
        void print();
        // Get functions
        std::string getEra();
        std::string getPrettyYear();
        std::string getPrettyPopulation();
        bool chrononautsStatus();
        bool jumpEngineerStatus();
        std::vector<std::string> getMajorEvents();
        // Set functions
        void setArtefact(Artefact *);
        void jump(int);
        // Events
        void findArtefactInfo();
        void discoverJumpClue();
        void realiseCounterfeit();
        void plague();
        void skirmish();
        void techBreakthrough();
        void revolution();
        void localInteraction();
};

class Hamlet : public PopulationCentre {  
    public:  
        Hamlet(const PopulationCentre &);
    private:
        double shrine;
};

class Village : public PopulationCentre {
    public:  
        Village(const PopulationCentre &);
    private:
        double monastery;
        double workshop;
};

class Town : public PopulationCentre {
    public:  
        Town(const PopulationCentre &);
    private:
        double sickhouse;
        double blacksmith;
        double motel;
};

class City : public PopulationCentre {
    public:  
        City(const PopulationCentre &);
    private:
        double clinic;
        double factory;
        double hotel;
        double airport;
};

class Metropolis : public PopulationCentre {
    public:  
        Metropolis(const PopulationCentre &);
    private:
        double hospital;
        double laboratory;
        double resort;
        double spaceport;
        double hydroponicum;
};
