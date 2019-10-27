class TechEra {
    protected:
        std::string name;
        double baseGrowthRate;
    public:
        TechEra(const TechEra &); // Copy Constructor
        TechEra(std::string, double, int); // Constructor for subclasses to use
        TechEra(int); // Construct based on year
        std::string getName();
        int getTechnology();
}; 

class ClassicalEra : public TechEra {
    public:
        using TechEra::TechEra;
        ClassicalEra();
};

class MedievalPeriod : public TechEra {
    public:
        using TechEra::TechEra;
        MedievalPeriod();
};

class Renaissance : public TechEra {
    public:
        using TechEra::TechEra;
        Renaissance();
};

class IndustrialRevolution : public TechEra {
    public:
        using TechEra::TechEra;
        IndustrialRevolution();
};

class InformationAge : public TechEra {
    public:
        using TechEra::TechEra;
        InformationAge();
};
