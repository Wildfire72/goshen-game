#include <iostream>
#include <string>
#include <cstdlib>
#include <array>
using namespace std;

class Tool{
    private:
        string name;
        int bonus;
        int cost;
        int number;
    public:
        Tool(string name, int bonus, int cost, int number);
        Tool();
        string getName();
        int getBonus();
        int getCost();
        int getNumber();
};

Tool::Tool(){
    name = "";
    bonus = 0;
    cost = 0;
    number = 0;
}

Tool::Tool(string name, int bonus, int cost,int number){
    this->name = name;
    this-> bonus = bonus;
    this->cost = cost;
    this->number = number;
}

string Tool::getName(){ return name;}
int Tool::getBonus(){ return bonus;}
int Tool::getCost(){ return cost;}
int Tool::getNumber(){ return number;}

class Player{
    private:
        string name;
        int maxEnergy;
        int energy;
        int skill;
        int credits;
        int reputation;
        Tool currentTool;
        int background;
        int missionsCompleted;
    public:
        Player(string name,int background,Tool curTool);
        string getName();
        int getEnergy();
        int getSkill();
        int getCredits();
        int getReputation();
        Tool getCurrentTool();
        int getBackground();
        int getMissionsComp();

        void setEnergy(int e);
        void setCredits(int c);
        void setReputation(int r);
        void setCurrentTool(Tool t);
        void completeMission();
        
        void train();
        void printStats(string backgroundNames[5]);
        void rest();
        int getScore();
};

Player::Player(string name,int background,Tool curTool) : currentTool(curTool){
    this->name = name;
    this->background = background;
    maxEnergy = 100;
    energy = maxEnergy;
    skill = 10;
    credits = 20;
    reputation = 0;
    currentTool = curTool;
    if (background == 2){
        skill += 15;
    } else if (background == 3){
        credits += 80;
    }
}

string Player::getName(){ return name;}
int Player::getEnergy(){ return energy;}
int Player::getSkill(){ return skill;}
int Player::getCredits(){ return credits;}
int Player::getReputation(){ return reputation;}
Tool Player::getCurrentTool(){ return currentTool;}
int Player::getBackground(){ return background;}
int Player::getMissionsComp(){ return missionsCompleted;}

void Player::setEnergy(int e){ energy = e; }
void Player::setCredits(int c){ credits = c; }
void Player::setReputation(int r){ reputation = r; }
void Player::setCurrentTool(Tool t){ currentTool = t; }
void Player::completeMission(){ missionsCompleted++; }

void Player::train(){
    int roll = rand() % 20;
    energy -= 8;
    int tempskill = 0;
    if (roll<8){
        tempskill += 8;
    } else if (roll<13){
        tempskill += 10;
    } else if (roll<17){
        tempskill += 12;
    } else{
        tempskill += 15;
    }
    cout << "Training results:\nSkill: +" << tempskill << endl << "Energy: -8" << endl;
    skill += tempskill;
    if (background==1){
        energy += 4;
        cout << "You regained " << 4 << " energy thanks to your tireless spirit" << endl;
    }
    if (background==5){
        skill += reputation/2;
        cout << "You gained an additional " << reputation/2 << " skill due to your reputation." << endl;
    }
}

void Player::rest(){
    energy += maxEnergy/2;
    if (energy > maxEnergy){
        energy = maxEnergy;
    }
    cout << "You enjoy some time relaxing in the summer sun. You now have " << energy << " Energy.\n";
}

int Player::getScore(){
    int score = credits + energy;
    score += 2*skill;
    score += 4*reputation;
    score += 10*missionsCompleted;
    return score;
}

void Player::printStats(string backgroundNames[5]){
    cout << "----Player Status----" << endl;
    cout << "Name: " << name << endl;
    cout << "Background: " << backgroundNames[background-1] << endl;
    cout << "Energy: " << energy << endl;
    cout << "Skill: " << skill << endl;
    cout << "Money: $" << credits << endl;
    cout << "Reputation: " << reputation << endl;
    cout << "Current Tool: " << currentTool.getName() << endl;
    cout << "Missions Completed: " << missionsCompleted << endl;
    cout << "Score: " << getScore() << endl;
}

class Mission{
    private:
        string name;
        int difficulty;
        int credits;
        int reputation;
        int energy;
        bool completed;
    public:
        Mission(string name,int difficulty,int credits,int reputation,int energy);
        Mission();
        string getName();
        int getDifficulty();
        int getCredits();
        int getReputation();
        int getEnergy();
        bool getCompleted();

        void attempt(Player& p);
};

Mission::Mission(){
    name = "";
    difficulty = 0;
    credits = 0;
    reputation = 0;
    energy = 0;
    completed = false;
}

Mission::Mission(string name, int difficulty, int credits, int reputation, int energy){
    this->name = name;
    this->difficulty = difficulty;
    this->credits = credits;
    this->reputation = reputation;
    this->energy = energy;
    completed = false;
}

string Mission::getName(){ return name;}
int Mission::getDifficulty(){ return difficulty;}
int Mission::getCredits(){ return credits;}
int Mission::getReputation(){ return reputation;}
int Mission::getEnergy(){ return energy;}
bool Mission::getCompleted(){ return completed;}

void Mission::attempt(Player& p){
    p.setEnergy(p.getEnergy()-energy);
    if (p.getBackground() == 1){
        p.setEnergy(p.getEnergy()+energy/2);
        cout << "You regained " << energy/2 << " energy thanks to your tireless spirit" << endl;
    }
    int roll = rand() % 10 + 1; //1-10
    cout << "Skill: " << p.getSkill() << endl;
    cout << "Tool Bonus: " << p.getCurrentTool().getBonus() << endl;
    cout << "Roll: " << roll << endl;
    if (roll+p.getSkill()+p.getCurrentTool().getBonus()<difficulty){
        cout << "Mission Failed! Better luck next time." << endl;
        return;
    }
    cout << "Mission SUCCESS!" << endl;
    p.setCredits(p.getCredits()+credits);
    cout << "You earned $" << credits << ". You now have $" << p.getCredits() << endl;
    if (p.getBackground()==5){
        p.setCredits(p.getCredits()+p.getReputation()/2);
        cout << "You earned an additional $" << p.getReputation()/2 << " due to your reputation.\n";
    }
    p.setReputation(p.getReputation()+reputation);
    cout << "Your reputation increased by " << reputation << endl;
    completed = true;
    p.completeMission();
}

void makeMissions(Mission* missions){
    missions[0] = Mission("Get Hired", 10, 20, 1, 4);
    missions[1] = Mission("Arrive at Camp", 15, 25, 2, 6);
    missions[2] = Mission("Clear Trails", 20, 30, 3, 8);
    missions[3] = Mission("Canvas Challenge", 30, 35, 4, 12);
    missions[4] = Mission("Site Guide", 40, 40, 5, 10);
    missions[5] = Mission("Teach Class", 50, 40, 7, 12);
    missions[6] = Mission("Do Paperwork", 60, 65, 6, 10);
    missions[7] = Mission("Project X", 70, 70, 8, 20);
    missions[8] = Mission("SWAG Crew", 80, 80, 9, 14);
    missions[9] = Mission("Tear Down", 100, 250, 50, 24);
}

void shop(Player& p, Tool* tools){
    cout << "Welcome to the Trading Post! There are multiple wonderful items here: " << endl;
    if (p.getCurrentTool().getNumber() == 5){
        cout << "You already have the " << tools[5].getName() << "! There's nothing left to buy!" << endl;
        return;
    }
    int i = p.getCurrentTool().getNumber()+1;
    while (i<6){
        cout << "[" << i << "] " << tools[i].getName() << " - Bonus: +" << tools[i].getBonus() << ", Cost: $" << tools[i].getCost() << endl;
        i++;
    }
    cout << "Please enter a tool number to purchase: ";
    cin >> i;
    while (i<p.getCurrentTool().getNumber()+1 || i>5){
        cout << "That is not a valid tool number. Please enter a number from " << p.getCurrentTool().getNumber()+1 << "-5: ";
        cin >> i; 
    }
    if (p.getCredits() < tools[i].getCost()){
        cout << "That item is too expensive! Come back when you've made some more money.\n";
    } else{
        p.setCredits(p.getCredits()-tools[i].getCost());
        cout << "You purchased the " << tools[i].getName() << " for $" << tools[i].getCost() << "! You now have $" << p.getCredits() << endl;
        p.setCurrentTool(tools[i]);
    }
    cout << "Hope to see you again!" << endl;
}

void makeTools(Tool* tools, int background){
    if (background!=4){
        tools[0] = Tool("Bare Hands",0,0,0);
        tools[1] = Tool("Slushie Cup",5,20,1);
        tools[2] = Tool("Pocketknife",10,45,2);
        tools[3] = Tool("Mop",20,100,3);
        tools[4] = Tool("Clipboard",30,160,4);
        tools[5] = Tool("White Truck", 45,250,5);
    } else{
        tools[0] = Tool("Bare Hands",0,0,0);
        tools[1] = Tool("Slushie Cup",5,16,1);
        tools[2] = Tool("Pocketknife",10,36,2);
        tools[3] = Tool("Mop",20,80,3);
        tools[4] = Tool("Clipboard",30,128,4);
        tools[5] = Tool("White Truck", 45,200,5);
    }   
}

void attemptMissions(Player& p, Mission* missions){
    cout << "Available Missions: " << endl;
    for (int i=0;i<10;i++){
        if (!missions[i].getCompleted()){
            cout << "[" << i+1 << "] " << missions[i].getName() << " - Difficulty: " << missions[i].getDifficulty() << endl;
            cout << "    - Energy Cost: " << missions[i].getEnergy() << endl;
            cout << "    - Rewards: $" << missions[i].getCredits() << ", +" <<missions[i].getReputation() << " Reputation" << endl << endl;
        }
    }
    int select;
    cout << "Please select a mission number: ";
    cin >> select;
    while (missions[select-1].getCompleted() || select < 1 || select > 10){
        cout << "That is not a valid mission number. Please select a valid mission number: ";
        cin >> select;
    }
    missions[select-1].attempt(p);
}

int main(){
    cout << "Please enter your name: ";

    string name;
    getline(cin,name);

    string backgroundNames[5] = {"Tireless","Prepared","Wealthy","Thrifty","Renowned"};
    cout << "Welcome " << name << "!" << endl << endl;
    cout << "Please select a background to aid you on your journey:" << endl;
    cout << "[1] Tireless - You use less energy." << endl;
    cout << "[2] Prepared - You start the game with increased skill." << endl;
    cout << "[3] Wealthy - You start the game with more money." << endl;
    cout << "[4] Thrify - Items cost less to purchace." << endl;
    cout << "[5] Renowned - You gain bonuses based on your renown." << endl;
    int background;
    cout << "Please select a number from 1-5: ";
    cin >> background;
    while (background < 1 || background > 5){
        cout << "That is not a valid background. Please select a number from 1-5: ";
        cin >> background;
    }

    //tool info
    Tool tools[6];
    makeTools(tools,background);
    Mission missions[10];
    makeMissions(missions);

    Player p = Player(name,background,tools[0]);

    int day = 0;

    while (day<14){
        cout << "Day " << day+1 << " of 14" << endl << endl;
        cout << "   [1] View Status\n";
        cout << "   [2] Train\n";
        cout << "   [3] Rest\n";
        cout << "   [4] Visit Shop\n";
        cout << "   [5] Attempt Mission\n";
        cout << "   [6] Quit\n" << endl;
        cout << "Please select a number from 1-6: ";
        cin >> background;
        while (background < 1 || background > 6){
            cout << "That is not a valid number. Please select a number from 1-6: ";
            cin >> background;
        }
        if (background == 1){
            p.printStats(backgroundNames);
        } else if (background == 2){
            p.train();
            day++;
        } else if (background == 3){
            p.rest();
            day++;
        } else if (background == 4){
            shop(p,tools);
        } else if (background == 5){
            attemptMissions(p,missions);
            day++;
        } else{
            day = 14;
        }
        if (p.getEnergy()<1){
            day = 14;
            cout << "You ran out of energy!\n";
        }
    }
    
    int score = p.getScore();
    cout << "=====Final Report====" << endl;
    cout << "Player: " << p.getName() << endl;
    cout << "Background: " << backgroundNames[p.getBackground()-1] << endl << endl;
    cout << "Energy: " << p.getEnergy() << endl;
    cout << "Money: $" << p.getCredits() << endl;
    cout << "Skill: " << p.getSkill() << endl;
    cout << "Reputation: " << p.getReputation() << endl;
    cout << "Missions Completed: " << p.getMissionsComp() << endl << endl;
    cout << "Final Score: " << score << endl;
    cout << "Rank: ";
    if (score<200){
        cout << "CIT";
    } else if (score < 300){
        cout << "Newbie Staff";
    } else if (score < 400){
        cout << "Average Staff";
    } else if (score < 500){
        cout << "Experienced Staff";
    } else if (score < 600){
        cout << "Area Director";
    } else if (score < 800){
        cout << "Admin Staff";
    } else{
        cout << "Camp Director";
    }
    cout << endl;

    return 0;
}
