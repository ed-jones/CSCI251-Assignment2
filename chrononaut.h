class Chrononaut {
    private:
        std::string name;
        std::string type;
        int realAge;
        bool isAlive;
        bool isRetired;
        std::vector<std::string> characteristics;
        int travelAge;
    protected:
        double ability;
    public:
        Chrononaut(std::string, std::string, int, int, bool, bool, double);
        Chrononaut(const Chrononaut &);
        void print();
        void ageUp();
        std::string getType();
        std::string getName();
        double getAbility();
        std::string getPrettyAbility();
        void kill();
        void retire();
        bool hasRetired();
        bool isLiving();
        void increaseAbility(int);
        virtual void event();
        virtual void printCharacteristics();
        bool isJumpEngineer();
        bool isDoctor();
        bool isHistorian();
        bool isSecurity();
        bool isChronodog();
        bool isChronocat();
        bool isChronobird();
};

std::vector<std::unique_ptr<Chrononaut>> generateChrononauts();

class JumpEngineer: public Chrononaut {
    public:
        JumpEngineer(std::string, std::string, int, int, bool, bool, double, double);
        void event();
        void printCharacteristics();
        void increaseVolatility(int);
        bool isJumpEngineer();
        double getVolatility();
    private:
        double volatility;
};

class Doctor: public Chrononaut {
    public:
        Doctor(std::string, std::string, int, int, bool, bool, double, double, double);
        void event();
        void printCharacteristics();
        void increaseQualifications(int);
        void increaseIntelligence(int);
        bool isDoctor();
        double getQualifications();
        double getIntelligence();
    private:
        double qualifications;
        double intelligence;
};

class Historian: public Chrononaut {
    public:
        Historian(std::string, std::string, int, int, bool, bool, double, double, double);
        void event();
        void printCharacteristics();
        void increaseQualifications(int);
        void increaseWisdom(int);
        bool isHistorian();
        double getQualifications();
        double getWisdom();
    private:
        double qualifications;
        double wisdom;
};

class Security: public Chrononaut {
    public:
        Security(std::string, std::string, int, int, bool, bool, double, double, double);
        void event();
        void printCharacteristics();
        void increaseStrength(int);
        void increaseDiplomacy(int);
        bool isSecurity();
        double getStrength();
        double getDiplomacy();
    private:
        double strength;
        double diplomacy;
};

class Chronopet: public Chrononaut {
    public:
        Chronopet(std::string, std::string, int, int, bool, bool, double, double);
        virtual void event() = 0;
        virtual void printCharacteristics() = 0;
        void increaseEndearing(int);
        bool isChronopet();
        double getEndearing();
    protected:
        double endearing;
};

class Chronodog: public Chronopet {
    public:
        Chronodog(std::string, std::string, int, int, bool, bool, double, double, double, double);
        void event();
        void printCharacteristics();
        void increaseOlfaction(int);
        void increaseExcavation(int);
        bool isChronodog();
        double getOlfaction();
        double getExcavation();
    private:
        double olfaction;
        double excavation;
};

class Chronocat: public Chronopet {
    public:
        Chronocat(std::string, std::string, int, int, bool, bool, double, double, double, double);
        void event();
        void printCharacteristics();
        void increaseHunting(int);
        void increaseClimbing(int);
        bool isChronocat();
        double getHunting();
        double getClimbing();
    private:
        double hunting;
        double climbing;
};

class Chronobird: public Chronopet {
    public:
        Chronobird(std::string, std::string, int, int, bool, bool, double, double, double, double);
        void event();
        void printCharacteristics();
        void increaseScouting(int);
        void increaseCollecting(int);
        bool isChronobird();
        double getScouting();
        double getCollecting();
    private:
        double scouting;
        double collecting;
};
