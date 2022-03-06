#include <iostream>
#include <unistd.h> //Allows us to use the sleep() function which allows for pauses in the code.
#include <ctime>
#include <stdlib.h>
using namespace std;

void characterSelection(string &name, string &specialty, int stats[]);
void checkStats(int stats[], string &name);
void creditMenu();
void clearScreen();
void introScreen();
void miniBoss1(int stats[], int &boss);
void miniBoss2(int stats[], int &boss);
void finalBoss(int stats[], int &boss);
void endGame(int boss);
char characterPeb();
char characterLeb();
char characterSteb();

int main() {
    unsigned seed = time(0);
    srand(seed);
    char choice;
    string name = "Peeb";   //If player starts the game without choosing a character, they get to use Peeb!
    string specialty = "Everything";
    int day = 1, week = 1;
    const int SIZE = 6;
    int stats[SIZE] = {2, 2, 2, 2, 2, 2}; //Math, Science, pSolve, strength,defense, attack respectivly
    int random, boss = 0;
    bool playedBefore = false;
    introScreen();

    do{ //Main menu 
        clearScreen();
        cout<< "███╗░░░███╗███████╗███╗░░██╗████████╗░█████╗░██╗░░░░░██╗████████╗██╗░░░██╗\n";
        cout<< "████╗░████║██╔════╝████╗░██║╚══██╔══╝██╔══██╗██║░░░░░██║╚══██╔══╝╚██╗░██╔╝\n";
        cout<< "██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░███████║██║░░░░░██║░░░██║░░░░╚████╔╝░\n";
        cout<< "██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░██╔══██║██║░░░░░██║░░░██║░░░░░╚██╔╝░░\n";
        cout<< "██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░██║░░██║███████╗██║░░░██║░░░░░░██║░░░\n";
        cout<< "╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░░╚═╝░░░░░░╚═╝░░░\n\n";
        cout<< "Main Menu\n"
            << "---------\n"
            << "1. Check Stats\n"
            << "2. Credits\n"
            << "3. Characters\n"
            << "4. Start Game\n";
        cin >> choice;
        while(choice < '1' || choice > '4') {
            cout << "Invalid Selection. Enter an option from the menu." << endl;
            cin >> choice;
        }
        //Choices for the other menus.
        switch(choice) {
            case '1': checkStats(stats, name);
                break;
            case '2': creditMenu();
                break;
            case '3': characterSelection(name, specialty, stats);
                break;
            case '4': clearScreen();
                break;
        }
    }while(choice != '4');
    if(playedBefore == false) {
        cout << "Your name is " << name << " and your specialty is " << specialty << ". You are a first year \n"
            << "student at TAMUCC and your goal is to complete your first semester, \n"
            << "but there's a catch. There will be a combat system similar to Pokemon that \n"
            << "will assist you throughout the semester you play.\n\n";
        usleep(7000000);
        cout << "The semester you will be playing in is simulated in that it is 3 weeks long. \n" 
            << "Each week will have a quiz/test (mini boss/boss) you must complete/fight in order \n"
            << "to finish the semester. When you take/fight these quizzes/tests, you must keep \n"
            << "track of your health (mental health) and make sure it does not reach 0. If your \n"
            << "health does manage to reach 0, you will fail that test/quiz but you will be able \n"
            << "to keep playing. Depending on if you complete the test or not, your semester \n"
            << "average grade will be affected.\n\n";
        usleep(10000000);
        cout << "Lastly, you will make your own decisions each day of the school week and depending \n"
            << "on your decisions, you will affect your stats. There will also be random events \n" 
            << "that also occur that will affect your stats. The stats are Problem-Solving, \n" 
            << "Math, Science, Strength, Attack, and Defense. Problem-Solving means that you will \n"
            << "have an easier time on a quiz/test that is Problem-Solving based. The same goes \n"
            << "for the Math and Science stats. Strength allows you hit the quiz/test for more \n"
            << "damage. Attack allows you to increase your chance to hit the test/quiz. Defense \n"
            << "allows you to evade the attacks more often from the quiz/test.\n\n";
        usleep(10000000);
        cout << "Now that you know how to play the game, good luck on your semester and have fun!\n\n";
        cout << "Enter '1' to begin the game!" << endl;
        cin >> choice;
        while(choice != '1') {
            cout << "Invalid Selection. Please Enter '1' to play the game!." << endl;
            cin >> choice;
        }
        playedBefore = true;
        clearScreen();
    }
    //Daily routine that offers choices to the user each day
    for(week = 1; week <= 3; week++) {
        for(day = 1; day <= 5; day++) {
            if(day == 5 && week == 1) {
                miniBoss1(stats, boss);
            }
            if(day == 5 && week == 2) {
                miniBoss2(stats, boss);
            }
            if(day == 5 && week == 3) {
                finalBoss(stats, boss);
                endGame(boss);
            }
            cout << "Day " << day << " Week " << week << endl;
            cout << "------------" << endl << endl;
            //Waking up, the player has a chance to either wake up late or early which affects stats.
            random = rand() % 6;
            if(random == 0) {
                if(stats[3] > 1) {
                    cout << "You wake up late for Day " << day << " Week " << week << " of school!" << endl << endl;
                    cout << "-1" << " Strength" << endl;
                    stats[3] -= 1;
                    cout << "Current Strength: " << stats[3] << endl << endl;
                }
                else
                    cout << "You wake up late for Day " << day << " Week " << week << " of school!" << endl << endl;
            }
            else {
                random = 1 + rand() % 2;
                cout << "You wake up early for Day " << day << " Week " << week << " of school!" << endl << endl;
                cout << "+" << random << " Strength" << endl;
                stats[3] += random;
                cout << "Current Strength: " << stats[3] << endl << endl;
            }
            //Question 1: choices for what to do after the player wakes up.
            cout << "What do you want to do?\n"
                << "1. Go to school\n"
                << "2. Skip school but attend online\n"
                << "3. Go back to bed\n";
            cin >> choice;
            while(choice < '1' || choice > '3') {
                cout << "Invalid Selection. Enter an option from above." << endl;
                cin >> choice;
            }
            cout << endl;
            //Changes stats depending on the decision the user chose for question 1.
            switch(choice) {
                case '1': random = 1 + rand() % 2;
                        stats[5] += random;
                        cout << "+" << random << " Attack" << endl;
                        random = 1 + rand() % 2;
                        stats[4] += random;
                        cout << "+" << random << " Defense" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Defense: " << stats[4] << endl << endl;
                    break;
                case '2': if(stats[5] > 1) {
                            stats[5] -= 1;
                            cout << "-1" << " Attack" << endl;
                        }
                        stats[4] += 1;
                        cout << "+1" << " Defense" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Defense: " << stats[4] << endl << endl;
                    break;
                case '3': if(stats[5] > 1) {
                            stats[5] -= 1;
                            cout << "-1" << " Attack" << endl;
                        }
                        if(stats[4] > 1) {
                            stats[4] -= 1;
                            cout << "-1" << " Defense" << endl;
                        }
                        random = 1 + rand() % 2;
                        stats[3] += random;
                        cout << "+" << random << " Strength" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Defense: " << stats[4] << endl;
                        cout << "Current Strength: " << stats[3] << endl << endl;
                    break;
            }
            //Question 2: Choices for if the user wants to do their homework.
            cout << "School has ended and you have homework. What do you want to do?\n"
                << "1. Finish the homework\n"
                << "2. Skip the homework and take a nap\n"
                << "3. Do your hobby and skip the homework\n";
            cin >> choice;
            while(choice < '1' || choice > '3') {
                cout << "Invalid Selection. Enter an option from above." << endl;
                cin >> choice;
            }
            cout << endl;
            //Changes stats depending on the decision the user chose for question 2.
            switch(choice) {
                case '1': random = 1 + rand() % 2;
                        stats[5] += random;
                        cout << "+" << random << " Attack" << endl;
                        random = 1 + rand() % 2;
                        stats[3] += random;
                        cout << "+" << random << " Strength" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Strength: " << stats[3] << endl << endl;
                    break;
                case '2': if(stats[5] > 1) {
                            stats[5] -= 2;
                            cout << "-1" << " Attack" << endl;
                        }
                        random = 1 + rand() % 3;
                        stats[4] += random;
                        cout << "+" << random << " Defense" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Defense: " << stats[4] << endl << endl;
                    break;
                case '3': if(stats[4] > 1) {
                            stats[4] -= 1;
                            cout << "-1" << " Defense" << endl;
                        }
                        random = 1 + rand() % 3;
                        stats[4] += random;
                        cout << "+" << random << " Attack" << endl;
                        cout << "Current Defense: " << stats[4] << endl;
                        cout << "Current Attack: " << stats[5] << endl << endl;
                    break;
            }
            //Question 3: Choices for how the user wants to spend their night.
            cout << "It is getting late, how do you spend your night?\n"
                << "1. Go to sleep\n"
                << "2. Stay up late but study\n";
            cin >> choice;
            while(choice < '1' || choice > '2') {
                cout << "Invalid Selection. Enter an option from above." << endl;
                cin >> choice;
            }
            cout << endl;
            //Changes stats depending on the decision the user chose for question 3.
            switch(choice) {
                case '1': stats[5] += 1;
                        cout << "+1" << " Attack" << endl;
                        stats[4] += 1;
                        cout << "+1" << " Defense" << endl;
                        stats[3] += 1;
                        cout << "+1" << " Strength" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Defense: " << stats[4] << endl;
                        cout << "Current Strength: " << stats[3] << endl << endl;
                    break;
                case '2': if(stats[5] > 1) {
                            stats[5] -= 1;
                            cout << "-1" << " Attack" << endl;
                        }
                        if(stats[4] > 1) {
                            stats[4] -= 1;
                            cout << "-1" << " Defense" << endl;
                        }
                        random = 2 + rand() % 3;
                        stats[3] += random;
                        cout << "+" << random << " Strength" << endl;
                        cout << "Current Attack: " << stats[5] << endl;
                        cout << "Current Defense: " << stats[4] << endl;
                        cout << "Current Strength: " << stats[3] << endl << endl;
                    break;
            }
            cout << "Enter '1' to continue." << endl;
            cin >> choice;
            while(choice != '1') {
                cout << "Invalid Selection. Please enter '1' to continue." << endl;
                cin >> choice;
            }
            clearScreen();
            //The user has completed the day. The user can now choose what skill they want
            //to put a skill point in.
            cout << "Congratulations! You have completed Day " << day << " Week " << week << "!" << endl << endl;
            cout << "You have achieved a skill point for completing the day!" << endl << endl;
            cout << "Choose one of the following skills to put a skill point in.\n"
                << "1. Math Skill\n"
                << "2. Science Skill\n"
                << "3. Problem-Solving Skill\n";
            cin >> choice;
            while(choice < '1' || choice > '3') {
                cout << "Invalid Selection. Enter an option from above." << endl;
                cin >> choice;
            }
            cout << endl;
            switch(choice) {
                case '1': stats[0] += 1;
                        cout << "+1" << " Math" << endl;
                        cout << endl;
                    break;
                case '2': stats[1] += 1;
                        cout << "+1" << " Science" << endl;
                        cout << endl;
                    break;
                case '3': stats[2] += 1;
                        cout << "+1" << " Problem-Solving" << endl;
                        cout << endl;
                    break;
            }
            cout << "Current Stats:" << endl;
            cout << "-------------" << endl;
            cout << "Attack Skill: " << stats[5] << endl;
            cout << "Defense Skll: " << stats[4] << endl;
            cout << "Strength Skill: " << stats[3] << endl;
            cout << "Current Math Skill: " << stats[0] << endl;
            cout << "Current Science Skill: " << stats[1] << endl;
            cout << "Current Problem-Solving Skill: " << stats[2] << endl << endl;
            cout << "Enter '1' to move on to the next day!" << endl;
            cin >> choice;
            while(choice != '1') {
                cout << "Invalid Selection. Please enter '1' to continue." << endl;
                cin >> choice;
            }
            clearScreen();
        }
    }
    return 0;
}

//Animation for the intro of the game.
void introScreen(){
    clearScreen();
    //Displays a firework animation.
    for(int i = 0; i < 2; i++){
        cout<< "\n\n\n"
            << "           ...\n"
            << "          :   :\n"
            << "          '...'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "          .''''.\n"
            << "         :  ..  :\n"
            << "         :  ''  :\n"
            << "          '....'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "          .  :  .\n"
            << "        '.   :   .'\n"
            << "       .   '.:. '  .\n"
            << "       .   .': '.  .\n"
            << "        .'   :   '.\n"
            << "          '  :  '\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "                            ...\n"
            << "                           :   :\n"
            << "                           '...'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "                           .''''.\n"
            << "                          :  ..  :\n"
            << "                          :  ''  :\n"
            << "                           '....'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "                          .  :  .\n"
            << "                        '.   :   .'\n"
            << "                       .   '.:. '  .\n"
            << "                       .   .': '.  .\n"
            << "                        .'   :   '.\n"
            << "                          '  :  '\n";
        usleep(500000);
        clearScreen();
    }

    //Displays the animation for the name of the game.
    cout<< "███╗░░░███╗███████╗███╗░░██╗████████╗░█████╗░██╗░░░░░██╗████████╗██╗░░░██╗\n";
    usleep(500000);
    cout<< "████╗░████║██╔════╝████╗░██║╚══██╔══╝██╔══██╗██║░░░░░██║╚══██╔══╝╚██╗░██╔╝\n";
    usleep(500000);
    cout<< "██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░███████║██║░░░░░██║░░░██║░░░░╚████╔╝░\n";
    usleep(500000);
    cout<< "██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░██╔══██║██║░░░░░██║░░░██║░░░░░╚██╔╝░░\n";
    usleep(500000);
    cout<< "██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░██║░░██║███████╗██║░░░██║░░░░░░██║░░░\n";
    usleep(500000);
    cout<< "╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░░╚═╝░░░░░░╚═╝░░░\n";
    usleep(1000000);
    cout << "\nPress enter to continue";
    cin.get();
}

//Character selection - Lists the characters that are available to be choosen.
void characterSelection(string &name, string &specialty, int stats[]) {
    char choice, characterDecision;

    //Character selection menu.
    clearScreen();
    cout<< "Character Selection\n"
        << "-------------------\n"
        << "Choose a Character to See Their Stats:\n"
        << "1. Peb (Mathematician)\n"   //Peb - Math
        << "2. Leb (Scientist)\n"   //Leb - Science
        << "3. Steb (Problem Solver)\n"   //Steb - Problem-Solving
        << "4. Back to Main Menu\n";
    cin >> choice;
    while(choice < '1' || choice > '4'){
        cout << "Invalid Selection. Enter an option from the menu." << endl;
        cin >> choice;
    }

    //Choices of all 3 characters.
    switch(choice){
        //Peb's character choice.
        case '1': characterDecision = characterPeb();
            if(characterDecision == 'Y' || characterDecision == 'y'){
                stats[0] = 3;
                stats[1] = 1;
                stats[2] = 1;
                stats[5] = 1;
                stats[4] = 3;
                stats[3] = 1;
                name = "Peb";
                specialty = "Math";
            }
            break;
        //Leb's character choice.
        case '2': characterDecision = characterLeb();
            if(characterDecision == 'Y' || characterDecision == 'y'){
                stats[0] = 1;
                stats[1] = 3;
                stats[2] = 1;
                stats[5] = 3;
                stats[4] = 1;
                stats[3] = 1;
                name = "Leb";
                specialty = "Science";
            }
            break;
        //Steb's character choice.
        case '3': characterDecision = characterSteb();
            if(characterDecision == 'Y' || characterDecision == 'y'){
                stats[0] = 1;
                stats[1] = 1;
                stats[2] = 3;
                stats[5] = 1;
                stats[4] = 1;
                stats[3] = 3;
                name = "Steb";
                specialty = "Problem-Solving";
            }
            break;
    }
}

//Check Stats Option - Displays stats to user.
void checkStats(int stats[], string &name){
    string choice;
    clearScreen();
    
    //Stats menu displaying the current stats of the user.
    cout << "Stats" << endl;
    cout << "-----" << endl;
    cout << "Current Stats:" << endl;
    cout << "Your Name: " << name << endl;
    cout << "Attack Skill: " << stats[5] << endl;
    cout << "Defense Skill: " << stats[4] << endl;
    cout << "Strength Skill: " << stats[3] << endl;
    cout << "Math Skill: " << stats[0] << endl;
    cout << "Science Skill: " << stats[1] << endl;
    cout << "Problem-Solving Skill: " << stats[2] << endl << endl;
    cout << "Enter anything to go back to the main menu." << endl;
    cin >> choice;
    //Just for fun if the player types in "anything".
    if(choice == "anything"){
        cout << "\nReally?" << endl;
        usleep(2000000);
    }
}

//Credits menu - Shows the names of the people in the best group.
void creditMenu(){
    char choice;
    clearScreen();

    //Credits menu screen.
    cout<< "Credits\n"
        << "-------\n"
        << "Game Created By:\n"
        << "Jorge Juarez - Lead Designer\n"
        << "Jason Garcia - Lead Programmer\n\n";
    cout<< "Enter '1' to go back to the main menu." << endl;
    cin >> choice;
    while(choice != '1'){
        cout << "Invalid Selection. Please enter '1' to go back to the main menu." << endl;
        cin >> choice;
    }
}

//Clears the Screen.
void clearScreen(){
    cout << "\33[H\33[2J";
}

//Peb's Character Description/Stats Page - Here, the player chooses if they want to play as Peb or not.
char characterPeb(){
    char choice;
    clearScreen();

    //Peb's character skills menu.
    cout<< "Peb's Character:\n"
        << "----------------\n"
        << "Description: Peb's strong point is in math. Looks like :)\n\n"
        << "Peb's Stats:\n"
        << "Attack Skill: 1\n"
        << "Defense Skill: 3\n"
        << "Strength Skill: 1\n"
        << "Math Skill: 3\n"
        << "Science Skill: 1\n"
        << "Problem-Solving Skill: 1\n\n";

    //Players choice of Yes or No when asked to choose Peb.
    cout << "Would you like to choose Peb as your character? (Y/N)" << endl;
    cin >> choice;
    while(!(choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')){
        cout << "Invalid Selection. Please choose 'Y' or 'N'." << endl;
        cin >> choice;
    }
    return choice; //Returns the player's choice back to the character selection menu.
}

//Leb's Character Description/Stats Page - Here, the player chooses if they want to play as Leb or not.
char characterLeb(){
    char choice;
    clearScreen();

    //Leb's character skills menu.
    cout<< "Leb's Character:\n"
        << "----------------\n"
        << "Description: Leb's strong point is in science. Looks like B)\n\n"
        << "Leb's Stats:\n"
        << "Attack Skill: 3\n"
        << "Defense Skill: 1\n"
        << "Strength Skill: 1\n"
        << "Math Skill: 1\n"
        << "Science Skill: 3\n"
        << "Problem-Solving Skill: 1\n\n";

    //Players choice of Yes or No when asked to choose Leb.
    cout << "Would you like to choose Leb as your character? (Y/N)" << endl;
    cin >> choice;
    while(!(choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')){
        cout << "Invalid Selection. Please choose 'Y' or 'N'." << endl;
        cin >> choice;
    }
    return choice; //Returns the player's choice back to the character selection menu.
}

//Steb's Character Description/Stats Page - Here, the player chooses if they want to play as Steb or not.
char characterSteb(){
    char choice;
    clearScreen();

    //Steb's character skills menu.
    cout<< "Steb's Character:\n"
        << "----------------\n"
        << "Description: Steb's strong point is in problem-solving. Looks like ;-;\n\n"
        << "Steb's Stats:\n"
        << "Attack Skill: 1\n"
        << "Defense Skill: 1\n"
        << "Strength Skill: 3\n"
        << "Math Skill: 1\n"
        << "Science Skill: 1\n"
        << "Problem-Solving Skill: 3\n\n";

    //Players choice of Yes or No when asked to choose Steb.
    cout << "Would you like to choose Steb as your character? (Y/N)" << endl;
    cin >> choice;
    while(!(choice == 'Y' || choice == 'y' || choice == 'N' || choice == 'n')){
        cout << "Invalid Selection. Please choose 'Y' or 'N'." << endl;
        cin >> choice;
    }
    return choice; //Returns the player's choice back to the character selection menu.
}

//The first mini boss for the user to fight.
void miniBoss1(int stats[], int &boss) {
    int bossHealth = 100, playerHealth = 100+(stats[2]*20)+(stats[4]*1.25), random, cooldown = 0;
    int playerHealthStart = 100+(stats[2]*20)+(stats[4]*1.25);
    char choice;
    unsigned seed = time(0);
    srand(seed);

    clearScreen();
    cout << "A Problem-Solving Quiz Has Appeared! (Boss 1/3)" << endl << endl;
    cout << "Quiz Health: " << bossHealth << "/100" << endl << endl;
    cout << "Enter '1' to continue to the boss fight!" << endl;
    cin >> choice;
    while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
    }
    clearScreen();
    do {
        cout << "Quiz Health: " << bossHealth << "/100" << endl << endl;
        cout << "Your Mental Health: " << playerHealth << "/" << playerHealthStart << endl << endl;
        cout << "Attack Option:\n"
             << "1. Stab (Normal Attack)\n"
             << "2. Slash (Heavy Attack)\n";
        cin >> choice;
        while(choice < '1' || choice > '2') {
        cout << "Invalid Selection. Please enter an option from above." << endl;
        cin >> choice;
        }
        if(cooldown > 0) {
            while(choice == '2') {
                cout << "The slash attack is on cooldown for " << cooldown << " more turn(s)." << endl; cout << "Please choose another attack option!" << endl;
                cin >> choice;
                while(choice < '1' || choice > '2') {
                    cout << "Invalid Selection. Please enter '1' to continue." << endl;
                    cin >> choice;
                }
            }
        }
        switch(choice) {
            case '1':
                random = 1 + rand() % 20;
                if(stats[5] > 0 && stats[5] <= 5) {
                    if(random >= 1 && random <= 18) {
                        random = 1 + rand() % stats[5];
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 5 && stats[5] <= 10) {
                    if(random >= 1 && random <= 16) {
                        random = 5 + rand() % stats[5];
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 10 && stats[5] <= 100) {
                    if(random >= 1 && random <= 14) {
                    random = 10 + rand() % stats[5];
                    bossHealth -= random;
                    cout << "You hit the Quiz for " << random << " damage!" << endl;
                    usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                break;
            case '2':
                random = 1 + rand() % 20;
                if(stats[5] > 0 && stats[5] <= 5) {
                    if(random >= 1 && random <= 10) {
                        random = 1 + rand() % stats[5]+(stats[3]*0.35);
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 5 && stats[5] <= 10) {
                    if(random >= 1 && random <= 12) {
                        random = 5 + rand() % stats[5]+(stats[3]*0.35);
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 10 && stats[5] <= 100) {
                    if(random >= 1 && random <= 14) {
                    random = 10 + rand() % stats[5]+(stats[3]*0.35);
                    bossHealth -= random;
                    cout << "You hit the Quiz for " << random << " damage!" << endl;
                    cooldown = 4;
                    usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                break;
        }
        if(cooldown > 0) {
            cooldown -= 1;
        }
        if(bossHealth > 0) {
            cout << "\nThe Quiz Attacks!" << endl;
            usleep(2000000);
            random = 1 + rand() % 20;
            if(random >= 1 && random <= 17){
                random = 1 + rand() % 10;
                playerHealth -= random;
                cout << "The Quiz hit for " << random << " damage!" << endl;
                usleep(2000000);
            }
            else {
                cout << "The Quiz missed!" << endl;
                usleep(2000000);
            }
        }
        clearScreen();
    }while(bossHealth > 0 && playerHealth > 0);
    clearScreen();
    if(bossHealth <= 0) {
        boss += 1;
        cout << "You have won the battle against the Quiz!" << endl;
        cout << "You are one step closer to finishing the semester!" << endl << endl;
        usleep(3000000);
        cout << "Enter '1' to continue playing!" << endl;
        cin >> choice;
        while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
        }
        clearScreen();
    }
    if(playerHealth <= 0) {
        cout << "You have failed the battle against the Quiz!" << endl;
        cout << "Don't worry, you can still proceed to play the game!" << endl << endl;
        usleep(3000000);
        cout << "Enter '1' to continue playing!" << endl;
        cin >> choice;
        while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
        }
        clearScreen();
    }
}

//The second mini boss for the user to fight.
void miniBoss2(int stats[], int &boss) {
    int bossHealth = 300, playerHealth = 100+(stats[0]*20)+(stats[4]*1.25), random, cooldown = 0;
    int playerHealthStart = 100+(stats[0]*20)+(stats[4]*1.25);
    char choice;
    unsigned seed = time(0);
    srand(seed);

    clearScreen();
    cout << "A Math Quiz Has Appeared! (Boss 2/3)" << endl << endl;
    cout << "Quiz Health: " << bossHealth << "/300" << endl << endl;
    cout << "Enter '1' to continue to the boss fight!" << endl;
    cin >> choice;
    while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
    }
    clearScreen();
    do {
        cout << "Quiz Health: " << bossHealth << "/300" << endl << endl;
        cout << "Your Mental Health: " << playerHealth << "/" << playerHealthStart << endl << endl;
        cout << "Attack Option:\n"
             << "1. Stab (Normal Attack)\n"
             << "2. Slash (Heavy Attack)\n";
        cin >> choice;
        while(choice < '1' || choice > '2') {
        cout << "Invalid Selection. Please enter an option from above." << endl;
        cin >> choice;
        }
        if(cooldown > 0) {
            while(choice == '2') {
                cout << "The slash attack is on cooldown for " << cooldown << " more turn(s)." << endl; cout << "Please choose another attack option!" << endl;
                cin >> choice;
                while(choice < '1' || choice > '2') {
                    cout << "Invalid Selection. Please enter '1' to continue." << endl;
                    cin >> choice;
                }
            }
        }
        switch(choice) {
            case '1':
                random = 1 + rand() % 20;
                if(stats[5] > 0 && stats[5] <= 5) {
                    if(random >= 1 && random <= 18) {
                        random = 1 + rand() % stats[5];
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 5 && stats[5] <= 15) {
                    if(random >= 1 && random <= 16) {
                        random = 5 + rand() % stats[5];
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 15 && stats[5] <= 100) {
                    if(random >= 1 && random <= 14) {
                    random = 10 + rand() % stats[5];
                    bossHealth -= random;
                    cout << "You hit the Quiz for " << random << " damage!" << endl;
                    usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                break;
            case '2':
                random = 1 + rand() % 20;
                if(stats[5] > 0 && stats[5] <= 10) {
                    if(random >= 1 && random <= 10) {
                        random = 1 + rand() % stats[5]+(stats[3]*0.5);
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 5 && stats[5] <= 15) {
                    if(random >= 1 && random <= 12) {
                        random = 5 + rand() % stats[5]+(stats[3]*0.5);
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 15 && stats[5] <= 100) {
                    if(random >= 1 && random <= 14) {
                    random = 10 + rand() % stats[5]+(stats[3]*0.5);
                    bossHealth -= random;
                    cout << "You hit the Quiz for " << random << " damage!" << endl;
                    cooldown = 4;
                    usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                break;
        }
        if(cooldown > 0) {
            cooldown -= 1;
        }
        if(bossHealth > 0) {
            cout << "\nThe Quiz Attacks!" << endl;
            usleep(2000000);
            random = 1 + rand() % 20;
            if(random >= 1 && random <= 17){
                random = 1 + rand() % 10;
                playerHealth -= random;
                cout << "The Quiz hit for " << random << " damage!" << endl;
                usleep(2000000);
            }
            else {
                cout << "The Quiz missed!" << endl;
                usleep(2000000);
            }
        }
        clearScreen();
    }while(bossHealth > 0 && playerHealth > 0);
    clearScreen();
    if(bossHealth <= 0) {
        boss += 1;
        cout << "You have won the battle against the Quiz!" << endl;
        cout << "You are one step closer to finishing the semester!" << endl << endl;
        usleep(3000000);
        cout << "Enter '1' to continue playing!" << endl;
        cin >> choice;
        while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
        }
        clearScreen();
    }
    if(playerHealth <= 0) {
        cout << "You have failed the battle against the Quiz!" << endl;
        cout << "Don't worry, you can still proceed to play the game!" << endl << endl;
        usleep(3000000);
        cout << "Enter '1' to continue playing!" << endl;
        cin >> choice;
        while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
        }
        clearScreen();
    }
}

void finalBoss(int stats[], int &boss) {
    int bossHealth = 500, playerHealth = 100+(stats[1]*20)+(stats[4]*1.25), random, cooldown = 0;
    int playerHealthStart = 100+(stats[1]*20)+(stats[4]*1.25);
    char choice;
    unsigned seed = time(0);
    srand(seed);

    clearScreen();
    cout << "A Science Quiz Has Appeared! (Boss 3/3) FINAL BOSS" << endl << endl;
    cout << "Quiz Health: " << bossHealth << "/500" << endl << endl;
    cout << "Enter '1' to continue to the boss fight!" << endl;
    cin >> choice;
    while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to continue." << endl;
        cin >> choice;
    }
    clearScreen();
    do {
        cout << "Quiz Health: " << bossHealth << "/500" << endl << endl;
        cout << "Your Mental Health: " << playerHealth << "/" << playerHealthStart << endl << endl;
        cout << "Attack Option:\n"
             << "1. Stab (Normal Attack)\n"
             << "2. Slash (Heavy Attack)\n";
        cin >> choice;
        while(choice < '1' || choice > '2') {
        cout << "Invalid Selection. Please enter an option from above." << endl;
        cin >> choice;
        }
        if(cooldown > 0) {
            while(choice == '2') {
                cout << "The slash attack is on cooldown for " << cooldown << " more turn(s)." << endl; cout << "Please choose another attack option!" << endl;
                cin >> choice;
                while(choice < '1' || choice > '2') {
                    cout << "Invalid Selection. Please enter '1' to continue." << endl;
                    cin >> choice;
                }
            }
        }
        switch(choice) {
            case '1':
                random = 1 + rand() % 20;
                if(stats[5] > 0 && stats[5] <= 5) {
                    if(random >= 1 && random <= 18) {
                        random = 5 + rand() % stats[5];
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 5 && stats[5] <= 15) {
                    if(random >= 1 && random <= 16) {
                        random = 10 + rand() % stats[5];
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 15 && stats[5] <= 100) {
                    if(random >= 1 && random <= 14) {
                    random = 15 + rand() % stats[5];
                    bossHealth -= random;
                    cout << "You hit the Quiz for " << random << " damage!" << endl;
                    usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        usleep(2000000);
                    }
                }
                break;
            case '2':
                random = 1 + rand() % 20;
                if(stats[5] > 0 && stats[5] <= 10) {
                    if(random >= 1 && random <= 10) {
                        random = 5 + rand() % stats[5]+(stats[3]*0.5);
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 5 && stats[5] <= 15) {
                    if(random >= 1 && random <= 12) {
                        random = 10 + rand() % stats[5]+(stats[3]*0.5);
                        bossHealth -= random;
                        cout << "You hit the Quiz for " << random << " damage!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                if(stats[5] > 15 && stats[5] <= 100) {
                    if(random >= 1 && random <= 14) {
                    random = 15 + rand() % stats[5]+(stats[3]*0.5);
                    bossHealth -= random;
                    cout << "You hit the Quiz for " << random << " damage!" << endl;
                    cooldown = 4;
                    usleep(2000000);
                    }
                    else {
                        cout << "You missed!" << endl;
                        cooldown = 4;
                        usleep(2000000);
                    }
                }
                break;
        }
        if(cooldown > 0) {
            cooldown -= 1;
        }
        if(bossHealth > 0) {
            cout << "\nThe Quiz Attacks!" << endl;
            usleep(2000000);
            random = 1 + rand() % 20;
            if(random >= 1 && random <= 17){
                random = 5 + rand() % 20;
                playerHealth -= random;
                cout << "The Quiz hit for " << random << " damage!" << endl;
                usleep(2000000);
            }
            else {
                cout << "The Quiz missed!" << endl;
                usleep(2000000);
            }
        }
        clearScreen();
    }while(bossHealth > 0 && playerHealth > 0);
    clearScreen();
    if(bossHealth <= 0) {
        boss += 1;
        cout << "You have won the battle against the final Test!" << endl;
        cout << "You have completed the semester!" << endl << endl;
        usleep(3000000);
        cout << "Enter '1' to end the game!" << endl;
        cin >> choice;
        while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to end the game." << endl;
        cin >> choice;
        }
        clearScreen();
    }
    if(playerHealth <= 0) {
        cout << "You have failed the battle against the final Test!" << endl;
        cout << "Don't worry, you still finished the semester!" << endl << endl;
        usleep(3000000);
        cout << "Enter '1' to end the game!" << endl;
        cin >> choice;
        while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to end the game." << endl;
        cin >> choice;
        }
        clearScreen();
    }
}

void endGame(int boss) {
    char choice;

    cout << "You have successfully finished the semester! You defeated " << boss << "/3 bosses!" << endl << endl;
    cout << "In all seriousness, mental health is a huge concern in college. Keep a positive " << endl; 
    cout << "mindset and don't focus on the negatives but instead the positives." << endl << endl;
    usleep(2000000);
    cout << "Thank you for playing Mentality!" << endl << endl;
    cout << "Enter '1' to see the credits." << endl;
    cin >> choice;
    while(choice != '1') {
        cout << "Invalid Selection. Please enter '1' to see the credits!" << endl;
        cin >> choice;
    }
    clearScreen();
    //Displays a firework animation.
    for(int i = 0; i < 2; i++){
        cout<< "\n\n\n"
            << "           ...\n"
            << "          :   :\n"
            << "          '...'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "          .''''.\n"
            << "         :  ..  :\n"
            << "         :  ''  :\n"
            << "          '....'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "          .  :  .\n"
            << "        '.   :   .'\n"
            << "       .   '.:. '  .\n"
            << "       .   .': '.  .\n"
            << "        .'   :   '.\n"
            << "          '  :  '\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "                            ...\n"
            << "                           :   :\n"
            << "                           '...'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "                           .''''.\n"
            << "                          :  ..  :\n"
            << "                          :  ''  :\n"
            << "                           '....'\n";
        usleep(500000);
        clearScreen();
        cout<< "\n\n\n"
            << "                          .  :  .\n"
            << "                        '.   :   .'\n"
            << "                       .   '.:. '  .\n"
            << "                       .   .': '.  .\n"
            << "                        .'   :   '.\n"
            << "                          '  :  '\n";
        usleep(500000);
        clearScreen();
    }
    //Displays the animation for the name of the game.
    cout<< "███╗░░░███╗███████╗███╗░░██╗████████╗░█████╗░██╗░░░░░██╗████████╗██╗░░░██╗\n";
    usleep(500000);
    cout<< "████╗░████║██╔════╝████╗░██║╚══██╔══╝██╔══██╗██║░░░░░██║╚══██╔══╝╚██╗░██╔╝\n";
    usleep(500000);
    cout<< "██╔████╔██║█████╗░░██╔██╗██║░░░██║░░░███████║██║░░░░░██║░░░██║░░░░╚████╔╝░\n";
    usleep(500000);
    cout<< "██║╚██╔╝██║██╔══╝░░██║╚████║░░░██║░░░██╔══██║██║░░░░░██║░░░██║░░░░░╚██╔╝░░\n";
    usleep(500000);
    cout<< "██║░╚═╝░██║███████╗██║░╚███║░░░██║░░░██║░░██║███████╗██║░░░██║░░░░░░██║░░░\n";
    usleep(500000);
    cout<< "╚═╝░░░░░╚═╝╚══════╝╚═╝░░╚══╝░░░╚═╝░░░╚═╝░░╚═╝╚══════╝╚═╝░░░╚═╝░░░░░░╚═╝░░░\n";
    usleep(1000000);
    cout << "Game Created By:\n"
         << "Jorge Juarez - Lead Designer\n"
         << "Jason Garcia - Lead Programmer\n\n";
    usleep(10000000);
    exit(0);
}