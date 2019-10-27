class Artefact {
    private:
        std::string name;
        std::string description;
        std::vector<std::string> information;
        int clue;
        bool informationStatus;
        bool clueStatus;
        bool counterfeit;
    public:
        Artefact(std::string, std::string, int);
        void print(void);
        int getClue();
        void setClue(int);
        std::string getName();
        std::string getPrettyInformation();
        bool foundInformation();
        bool foundClue();
        void findArtefactInfo(int);
        void resetInfoClueStatus();
        bool isCounterfeit();
        void setCounterfeit();
        bool foundAllInformation();
};

std::vector<Artefact *> generateArtefacts(int);
