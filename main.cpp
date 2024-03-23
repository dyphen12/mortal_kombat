#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_keycode.h> 
#include "championship.hpp"
#include <random>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>

#define SCREEN_WIDTH 1280 
#define SCREEN_HEIGHT 720 

#define ARENA_WIDTH 616
#define ARENA_HEIGHT 616

#define FLOOR_WIDTH 700
#define FLOOR_HEIGHT 700

#define KARATEKA_WIDTH 21
#define KARATEKA_HEIGHT 35

#define KARATEKA_OIZUKI_WIDTH 56
#define KARATEKA_OIZUKI_HEIGHT 35

#define KARATEKA_GYAKUZUKI_WIDTH 56
#define KARATEKA_GYAKUZUKI_HEIGHT 35

#define KARATEKA_BASIC_WIDTH 42
#define KARATEKA_BASIC_HEIGHT 35

#define KARATEKA_MAEGERI_WIDTH 70
#define KARATEKA_MAEGERI_HEIGHT 35

#define KARATEKA_YOKOGERI_WIDTH 77
#define KARATEKA_YOKOGERI_HEIGHT 28

#define KARATEKA_AGEUKE_WIDTH 49
#define KARATEKA_AGEUKE_HEIGHT 35

#define KARATEKA_MAWASHIZUKI_WIDTH 56
#define KARATEKA_MAWASHIZUKI_HEIGHT 35

#define KARATEKA_HEIKOZUKI_WIDTH 56
#define KARATEKA_HEIKOZUKI_HEIGHT 35

#define KARATEKA_URAZUKI_WIDTH 56
#define KARATEKA_URAZUKI_HEIGHT 35

#define KARATEKA_KINGERI_WIDTH 42
#define KARATEKA_KINGERI_HEIGHT 35

#define KARATEKA_USHIROGERI_WIDTH 91
#define KARATEKA_USHIROGERI_HEIGHT 42

#define REFEREE_STANDUP_WIDTH 35
#define REFEREE_STANDUP_HEIGHT 21

#define REFEREE_LEFTPOINT_WIDTH 56
#define REFEREE_LEFTPOINT_HEIGHT 21

#define REFEREE_RIGHTPOINT_WIDTH 56
#define REFEREE_RIGHTPOINT_HEIGHT 21

#define REFEREE_STARTMATCH_WIDTH 35
#define REFEREE_STARTMATCH_HEIGHT 42

#define REFEREE_PENALTYLEFT_WIDTH 35
#define REFEREE_PENALTYLEFT_HEIGHT 42

#define REFEREE_PENALTYRIGHT_WIDTH 35
#define REFEREE_PENALTYRIGHT_HEIGHT 42

#define YUKO_TEXTBOX_WIDTH 92
#define YUKO_TEXTBOX_HEIGHT 44

#define WAZARI_TEXTBOX_WIDTH 132
#define WAZARI_TEXTBOX_HEIGHT 44

#define IPPON_TEXTBOX_WIDTH 112
#define IPPON_TEXTBOX_HEIGHT 44

#define CLOCK_WIDTH 108
#define CLOCK_HEIGHT 44

#define NUMBER_WIDTH 16
#define NUMBER_HEIGHT 28

#define COLON_WIDTH 4
#define COLON_HEIGHT 16

#define TREE_WIDTH 120
#define TREE_HEIGHT 244

#define COUNTER_WIDTH 60
#define COUNTER_HEIGHT 44

bool isMovingRight = false;
bool isMovingLeft = false;
bool isMovingUp = false;
bool isMovingDown = false;
bool isMKeyPressed = false;
bool isNKeyPressed = false;
bool isBKeyPressed = false;
bool isJKeyPressed = false;
bool isKKeyPressed = false;

int karatekaSpriteSizeW;
int karatekaSpriteSizeH;

// Function to generate a random number with seeding options
int rngA(bool useSpecificSeed) {
    static random_device rd; // Static to ensure initialization happens only once
    static mt19937 generator(rd()); // Static to maintain generator state

    int seedValue = 3456;

    if (useSpecificSeed) {
        generator.seed(seedValue);
    } else {
        generator.seed(rd()); // Seed with new random value
    }

    uniform_int_distribution<int> distribution(1, 100); // Generates numbers between 1 and 100
    return distribution(generator);
}

int rngB(bool useSpecificSeed) {
    static random_device rd; // Static to ensure initialization happens only once
    static mt19937 generator(rd()); // Static to maintain generator state

    int seedValue = 6543;

    if (useSpecificSeed) {
        generator.seed(seedValue);
    } else {
        generator.seed(rd()); // Seed with new random value
    }

    uniform_int_distribution<int> distribution(1, 100); // Generates numbers between 1 and 100
    return distribution(generator);
}

Match* setKaratekasStartPosition(Match* match, int width, int height){

    // Karateka A

    int karatekaCenterX = (SCREEN_WIDTH - width) / 2;
    int karatekaCenterY = (SCREEN_HEIGHT - height) / 2;

    PositionVector* posvk1 = new PositionVector(); // Create new PositionVector;
    posvk1->loadPosition(karatekaCenterX-90, karatekaCenterY); //Load Karateka1 position in the arena into the PositionVector      

    match->getKaratekaA()->setPosition(posvk1);

    // Karateka B

    int karateka2CenterX = (SCREEN_WIDTH - width) / 2;
    int karateka2CenterY = (SCREEN_HEIGHT - height) / 2;

    PositionVector* posvk2 = new PositionVector(); // Create new PositionVector;
    posvk2->loadPosition(karateka2CenterX+95, karateka2CenterY); //Load Karateka1 position in the arena into the PositionVector      

    match->getKaratekaB()->setPosition(posvk2);

    return match;

}


int main(int argc, char** argv){
    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Create window 
    SDL_Window* window = SDL_CreateWindow("Karate Championship Sim", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, 0);
    if (!window) {
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Create renderer
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_image
    int imgFlags = IMG_INIT_PNG;
    if (!(IMG_Init(imgFlags) & imgFlags)) {
        printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Load image (replace with your image path)
    SDL_Texture* texture = IMG_LoadTexture(renderer, "assets/Floor.png");
    if (!texture) {
        printf("Failed to load texture! SDL_image Error: %s\n", IMG_GetError());
        return 1;
    }

    // Assuming "Arena.png" is in the same directory as your code
    SDL_Texture* arenaTexture = IMG_LoadTexture(renderer, "assets/Arena.png");
    if (!arenaTexture) {
        printf("Failed to load arena texture! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaTexture = IMG_LoadTexture(renderer, "assets/Karateka.png");
    if (!karatekaTexture) {
        printf("Failed to load karateka texture! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2Texture = IMG_LoadTexture(renderer, "assets/Karateka_var.png");
    if (!karateka2Texture) {
        printf("Failed to load karateka texture! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* treeTexture = IMG_LoadTexture(renderer, "assets/tree.png");
    if (!treeTexture) {
        printf("Failed to load tree! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* grassTexture = IMG_LoadTexture(renderer, "assets/grass.png");
    if (!grassTexture) {
        printf("Failed to load grass! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    // KARATEKA 1 Textures

    SDL_Texture* karatekaBasicStanceTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_basic_stance.png");
    if (!karatekaBasicStanceTexture) {
        printf("Failed to load karateka basic stance sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaOiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_oi_zuki.png");
    if (!karatekaOiZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaGyakuZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_gyaku_zuki.png");
    if (!karatekaGyakuZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaHeikoZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_heiko_zuki.png");
    if (!karatekaHeikoZukiTexture) {
        printf("Failed to load karateka heiko zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaUraZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_ura_zuki.png");
    if (!karatekaUraZukiTexture) {
        printf("Failed to load karateka ura zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaMawashiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_mawashi_zuki.png");
    if (!karatekaMawashiZukiTexture) {
        printf("Failed to load karateka mawashi zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaAgeUkeTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_age_uke.png");
    if (!karatekaAgeUkeTexture) {
        printf("Failed to load karateka age uke sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaYokoGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_yoko_geri.png");
    if (!karatekaYokoGeriTexture) {
        printf("Failed to load karateka yokogeri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaMaeGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_mae_geri.png");
    if (!karatekaMaeGeriTexture) {
        printf("Failed to load karateka mae geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaKinGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_kin_geri.png");
    if (!karatekaKinGeriTexture) {
        printf("Failed to load karateka kin geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karatekaUshiroGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_ushiro_geri.png");
    if (!karatekaUshiroGeriTexture) {
        printf("Failed to load karateka ushiro geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    // KARATEKA 2 Textures

    SDL_Texture* karateka2BasicStanceTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_basic_stance.png");
    if (!karateka2BasicStanceTexture) {
        printf("Failed to load karateka basic stance sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2OiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_oi_zuki.png");
    if (!karateka2OiZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2GyakuZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_gyaku_zuki.png");
    if (!karateka2GyakuZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2HeikoZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_heiko_zuki.png");
    if (!karateka2HeikoZukiTexture) {
        printf("Failed to load karateka heiko zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2UraZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_ura_zuki.png");
    if (!karateka2UraZukiTexture) {
        printf("Failed to load karateka ura zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2MawashiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_mawashi_zuki.png");
    if (!karateka2MawashiZukiTexture) {
        printf("Failed to load karateka mawashi zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2AgeUkeTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_age_uke.png");
    if (!karateka2AgeUkeTexture) {
        printf("Failed to load karateka age uke sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2YokoGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_yoko_geri.png");
    if (!karateka2YokoGeriTexture) {
        printf("Failed to load karateka2 yoko geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2MaeGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_mae_geri.png");
    if (!karateka2MaeGeriTexture) {
        printf("Failed to load karateka mae geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2KinGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_kin_geri.png");
    if (!karateka2KinGeriTexture) {
        printf("Failed to load karateka kin geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2UshiroGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_ushiro_geri.png");
    if (!karateka2UshiroGeriTexture) {
        printf("Failed to load karateka ushiro geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    // Referee Textures

    SDL_Texture* refereeStandUpTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/Referee_stand_up.png");
    if (!refereeStandUpTexture) {
        printf("Failed to load referee stand up sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* refereeLeftPointTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/Referee_left_point.png");
    if (!refereeLeftPointTexture) {
        printf("Failed to load referee left point sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* refereeRightPointTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/Referee_right_point.png");
    if (!refereeRightPointTexture) {
        printf("Failed to load referee right point sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* refereeStartMatchTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/Referee_start_match.png");
    if (!refereeStartMatchTexture) {
        printf("Failed to load referee start match sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* refereePenaltyLeftTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/Referee_penalty_left.png");
    if (!refereePenaltyLeftTexture) {
        printf("Failed to load referee penalty left sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* refereePenaltyRightTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/Referee_penalty_right.png");
    if (!refereePenaltyRightTexture) {
        printf("Failed to load referee penalty right sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    // Text Box Textures

    SDL_Texture* yukoTextBoxTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/yuko_text_box.png");
    if (!yukoTextBoxTexture) {
        printf("Failed to load yuko text box sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* wazariTextBoxTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/wazari_text_box.png");
    if (!wazariTextBoxTexture) {
        printf("Failed to load wazari text box sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* ipponTextBoxTexture = IMG_LoadTexture(renderer, "assets/referee_sprites/ippon_text_box.png");
    if (!ipponTextBoxTexture) {
        printf("Failed to load ippon text box sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    // Clock

    SDL_Texture* clockTexture = IMG_LoadTexture(renderer, "assets/clock/clock.png");
    if (!clockTexture) {
        printf("Failed to load clock sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* zeroTexture = IMG_LoadTexture(renderer, "assets/clock/0.png");
    if (!zeroTexture) {
        printf("Failed to load zero sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* oneTexture = IMG_LoadTexture(renderer, "assets/clock/1.png");
    if (!oneTexture) {
        printf("Failed to load one sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* twoTexture = IMG_LoadTexture(renderer, "assets/clock/2.png");
    if (!twoTexture) {
        printf("Failed to load two sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* threeTexture = IMG_LoadTexture(renderer, "assets/clock/3.png");
    if (!threeTexture) {
        printf("Failed to load three sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* fourTexture = IMG_LoadTexture(renderer, "assets/clock/4.png");
    if (!fourTexture) {
        printf("Failed to load four sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* fiveTexture = IMG_LoadTexture(renderer, "assets/clock/5.png");
    if (!fiveTexture) {
        printf("Failed to load five sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* sixTexture = IMG_LoadTexture(renderer, "assets/clock/6.png");
    if (!sixTexture) {
        printf("Failed to load six sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* sevenTexture = IMG_LoadTexture(renderer, "assets/clock/7.png");
    if (!sevenTexture) {
        printf("Failed to load seven sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* eightTexture = IMG_LoadTexture(renderer, "assets/clock/8.png");
    if (!eightTexture) {
        printf("Failed to load eight sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* nineTexture = IMG_LoadTexture(renderer, "assets/clock/9.png");
    if (!nineTexture) {
        printf("Failed to load nine sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* colonTexture = IMG_LoadTexture(renderer, "assets/clock/colon.png");
    if (!colonTexture) {
        printf("Failed to load colon sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    // Point Counter

    SDL_Texture* counterTexture = IMG_LoadTexture(renderer, "assets/clock/counter.png");
    if (!counterTexture) {
        printf("Failed to load counter sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    


    // Get screen dimensions
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    int centerX = (screenWidth - FLOOR_WIDTH) / 2;
    int centerY = (screenHeight - FLOOR_HEIGHT) / 2;

    int arenaCenterX = (screenWidth - ARENA_WIDTH) / 2;
    int arenaCenterY = (screenHeight - ARENA_HEIGHT) / 2;

    int karatekaCenterX = ((screenWidth - KARATEKA_WIDTH) / 2)-90;
    int karatekaCenterY = (screenHeight - KARATEKA_HEIGHT) / 2;

    int karateka2CenterX = (screenWidth - KARATEKA_WIDTH) / 2;
    int karateka2CenterY = (screenHeight - KARATEKA_HEIGHT) / 2;

    int treeCenterX = (screenWidth - TREE_WIDTH) / 2;
    int treeCenterY = (screenHeight - TREE_HEIGHT) / 2;

    int refereeCenterX = (screenWidth - REFEREE_STANDUP_WIDTH) / 2;
    int refereeCenterY = ((screenHeight - REFEREE_STANDUP_HEIGHT) / 2)-250;

    int yukoTextBoxCenterX = (screenWidth - YUKO_TEXTBOX_WIDTH) / 2;
    int yukoTextBoxCenterY = ((screenHeight - YUKO_TEXTBOX_HEIGHT) / 2)-290;

    int wazariTextBoxCenterX = ((screenWidth - WAZARI_TEXTBOX_WIDTH) / 2);
    int wazariTextBoxCenterY = ((screenHeight - WAZARI_TEXTBOX_HEIGHT) / 2)-290;

    int ipponTextBoxCenterX = ((screenWidth - IPPON_TEXTBOX_WIDTH) / 2);
    int ipponTextBoxCenterY = ((screenHeight - IPPON_TEXTBOX_HEIGHT) / 2)-290;

    int clockCenterX = ((screenWidth - CLOCK_WIDTH) / 2)+3;
    int clockCenterY = ((screenHeight - CLOCK_HEIGHT) / 2)-330;

    int numberCenterX = ((screenWidth - NUMBER_WIDTH) / 2)+3;
    int numberCenterY = ((screenHeight - NUMBER_HEIGHT) / 2)-330;

    int colonCenterX = ((screenWidth - COLON_WIDTH) / 2)+3;
    int colonCenterY = ((screenHeight - COLON_HEIGHT) / 2)-330;

    int counterCenterX = ((screenWidth - COUNTER_WIDTH) / 2)-200;
    int counterCenterY = ((screenHeight - COUNTER_HEIGHT) / 2)-330;

    int counter2CenterX = ((screenWidth - COUNTER_WIDTH) / 2)+200;
    int counter2CenterY = ((screenHeight - COUNTER_HEIGHT) / 2)-330;


    // Championship Implementation

    Championship* wkc_womens_kumite = new Championship();

    string name;

    // Open the file for reading
    ifstream file("karatekanames.txt");

    // Check if the file was opened successfully
    if (file.is_open()) {
        // Read each line from the file
        while (std::getline(file, name)) {

        // Add the name to the vector
        //cout<<name<<endl;

        bool shotokanOrGoju = (rngA(false) <= 50);

        if(shotokanOrGoju){

            Shotokan* newKarateka = new Shotokan(3); // Create new karateka shotokan style

            newKarateka->setName(name); // Set Karateka Name

            int randomNum = rngA(false);

            int randomSpeed = randomNum % 3 + 1; // Ensures a result between 1 and 3

            newKarateka->setSpeed(randomSpeed);

            wkc_womens_kumite->signUpKarateka(newKarateka);

            //cout<<"New Shotokan signed up!"<<endl;

        } else {

            GojuRyu* newKarateka = new GojuRyu(3); // Create new karateka shotokan style

            newKarateka->setName(name); // Set Karateka Name

            int randomNum = rngA(false);

            int randomSpeed = randomNum % 3 + 1; // Ensures a result between 1 and 3

            newKarateka->setSpeed(randomSpeed);

            wkc_womens_kumite->signUpKarateka(newKarateka);

            //cout<<"New GojuRyu signed up!"<<endl;
        }

        //Shotokan* newKarateka = new Shotokan(3); // Create new karateka shotokan style

        

        }

        // Close the file
        file.close();
    } else {
        cerr << "Error: Could not open file 'karatekanames.txt'." << std::endl;
    }


    //wkc_womens_kumite->printKaratekaList();
    //cout<<wkc_womens_kumite->countKaratekas()<<endl;

    wkc_womens_kumite->calculateMatches();

    int matchesLeft = wkc_womens_kumite->getMatchesLeft();

    cout<<"Matches Left: "<<matchesLeft<<endl;

    while (wkc_womens_kumite->simulateChampionship() != NULL){
        //cout<<"Running Bottom Half First Round!";

        //Match* nextMatch = wkc_womens_kumite->bottomHalfRun();

        Match* nextMatch = wkc_womens_kumite->simulateChampionship();

        // MATCH IMPLEMENTATION
    

    // Setting Karateka A

    // Loading Starting Arena Position on the Karateka
    PositionVector* posvk1 = new PositionVector(); // Create new PositionVector;
    posvk1->loadPosition(karatekaCenterX-90, karatekaCenterY); //Load Karateka1 position in the arena into the PositionVector
    nextMatch->getKaratekaA()->setPosition(posvk1); // Set PositionVector into Karateka
    PositionVector* postemp = nextMatch->getKaratekaA()->getPositionVector(); // PositionVector Test
    cout<<"Position of Karateka A:  X="<<postemp->x<<" Y="<<postemp->y<<endl; // Print Karateka 1 starting position on the arena
    int q = nextMatch->getKaratekaA()->getPositionVector()->x;
    posvk1->x = karatekaCenterX;
    posvk1->y = karatekaCenterY;

    // Setting Karateka B

    PositionVector* posvk2 = new PositionVector(); 
    posvk2->loadPosition(karateka2CenterX+95, karateka2CenterY); 
    nextMatch->getKaratekaB()->setPosition(posvk2); 
    PositionVector* postempB = nextMatch->getKaratekaB()->getPositionVector(); 
    cout<<"Position of Karateka B:  X="<<postempB->x<<" Y="<<postempB->y<<endl; 
    
    nextMatch->getKaratekaB()->setArenaSide("right");
    cout<<"Arena side = "<<nextMatch->getKaratekaB()->getArenaSide()<<endl;
    

    // Setting Match

    Match* match = nextMatch;
    match->printMatchNames();
    match->simulateMatch();
    match->getKaratekaA()->getMatchState()->setKaratekaPositionVector(posvk1);
    match->getKaratekaA()->getMatchState()->setOpponentPosition(posvk2);
    match->getKaratekaB()->getMatchState()->setKaratekaPositionVector(posvk2);
    match->getKaratekaB()->getMatchState()->setOpponentPosition(posvk1);

    State* matchState = match->getKaratekaA()->getMatchState();


    //match->getKaratekaA()->getMatchState()->printState();

    
    
    uint64_t animationStartTime;     // Time when Yuko animation started

    bool isYukoLeftAnimationPlaying = false;  // Flag to track animation state

    bool isWazariLeftAnimationPlaying = false;  // Flag to track animation state

    bool isIpponLeftAnimationPlaying = false;  // Flag to track animation state

    bool isYukoRightAnimationPlaying = false;  // Flag to track animation state

    bool isIpponRightAnimationPlaying = false;  // Flag to track animation state

    bool isWazariRightAnimationPlaying = false;  // Flag to track animation state

    bool isWinningAnimationPlaying = false;  // Flag to track animation state

    bool isStartMatchAnimationPlaying = false; // Flag to track animation state

    bool isOiZukiAnimationPlaying = false; // Flag to track animation state

    bool isPenaltyLeftAnimationPlaying = false;

    bool isPenaltyRightAnimationPlaying = false;

    bool wait = false;


    uint64_t matchStartTime;  // Time when the match starts
    const double matchDuration = 1.0 * 60.0;  // Match duration in seconds (3 minutes)
    bool matchOngoing = true;  // Flag to track match state

    matchStartTime = SDL_GetPerformanceCounter();

    Referee* referee = new Referee(match);


     // Main loop
    bool running = true;
    while (running) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
            }
        }

        // TIME

        

        uint64_t frequency = SDL_GetPerformanceFrequency();  // Get clock frequency

        uint64_t matchCurrentTime = SDL_GetPerformanceCounter();
        double matchDeltaTime = (double)(matchCurrentTime - matchStartTime) / (double)frequency;

        // Update remaining time
        double remainingTime = matchDuration - matchDeltaTime;

        // Check if match has ended
        if (remainingTime <= 0.0) {
            matchOngoing = false;
            // Handle match ending (e.g., display message, stop simulation)
        }

        int minutes = (int)floor(remainingTime / 60);
        int seconds = (int)fmod(remainingTime, 60);

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // SIM LOGIC
        
        // RENDERING TASKS
        // ARENA RENDERING

        // GRASS

        SDL_Rect grassRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; 

        SDL_RenderCopy(renderer, grassTexture, NULL, &grassRect);

        SDL_Rect dstRect = {centerX, centerY, FLOOR_WIDTH, FLOOR_HEIGHT};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
       
        SDL_Rect arenaRect = {arenaCenterX, arenaCenterY, ARENA_WIDTH, ARENA_HEIGHT}; 
        SDL_RenderCopy(renderer, arenaTexture, NULL, &arenaRect);



        // KARATEK A COUNTER

        SDL_Rect counterRect = {counterCenterX, counterCenterY, COUNTER_WIDTH, COUNTER_HEIGHT}; 
        SDL_RenderCopy(renderer, counterTexture, NULL, &counterRect);


        // First digit
        SDL_Rect counterdigit1Rect = {numberCenterX-214, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT};


        if (match->getKaratekaA()->getPoints() >= 90 && match->getKaratekaA()->getPoints() <= 99){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 80 && match->getKaratekaA()->getPoints() <= 89){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 70 && match->getKaratekaA()->getPoints() <= 79){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 60 && match->getKaratekaA()->getPoints() <= 69){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 50 && match->getKaratekaA()->getPoints() <= 59){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 40 && match->getKaratekaA()->getPoints() <= 49){
            SDL_RenderCopy(renderer, fourTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 30 && match->getKaratekaA()->getPoints() <= 39){
            SDL_RenderCopy(renderer, threeTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 20 && match->getKaratekaA()->getPoints() <= 29){
            SDL_RenderCopy(renderer, twoTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 10 && match->getKaratekaA()->getPoints() <= 19){
            SDL_RenderCopy(renderer, oneTexture, NULL, &counterdigit1Rect);
        } else if (match->getKaratekaA()->getPoints() >= 0 && match->getKaratekaA()->getPoints() <= 9){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &counterdigit1Rect);
        }

        SDL_Rect counterdigit2Rect = {numberCenterX-192, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT};


        int pointsLastDigit = match->getKaratekaA()->getPoints() % 10; // lastDigit will be 9

        if (pointsLastDigit == 9){
            SDL_RenderCopy(renderer, nineTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 8){
            SDL_RenderCopy(renderer, eightTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 7){
            SDL_RenderCopy(renderer, sevenTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 6){
            SDL_RenderCopy(renderer, sixTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 5){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 4){
            SDL_RenderCopy(renderer, fourTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 3){
            SDL_RenderCopy(renderer, threeTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 2){
            SDL_RenderCopy(renderer, twoTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 1){
            SDL_RenderCopy(renderer, oneTexture, NULL, &counterdigit2Rect);
        } else if (pointsLastDigit == 0){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &counterdigit2Rect);
        }


        // KARATEKA B COUNTER

        SDL_Rect counter2Rect = {counter2CenterX, counter2CenterY, COUNTER_WIDTH, COUNTER_HEIGHT}; 
        SDL_RenderCopy(renderer, counterTexture, NULL, &counter2Rect);


        // First digit
        SDL_Rect counter2digit1Rect = {numberCenterX+186, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT}; 

        if (match->getKaratekaB()->getPoints() >= 90 && match->getKaratekaB()->getPoints() <= 99){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 80 && match->getKaratekaB()->getPoints() <= 89){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 70 && match->getKaratekaB()->getPoints() <= 79){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 60 && match->getKaratekaB()->getPoints() <= 69){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 50 && match->getKaratekaB()->getPoints() <= 59){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 40 && match->getKaratekaB()->getPoints() <= 49){
            SDL_RenderCopy(renderer, fourTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 30 && match->getKaratekaB()->getPoints() <= 39){
            SDL_RenderCopy(renderer, threeTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 20 && match->getKaratekaB()->getPoints() <= 29){
            SDL_RenderCopy(renderer, twoTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 10 && match->getKaratekaB()->getPoints() <= 19){
            SDL_RenderCopy(renderer, oneTexture, NULL, &counter2digit1Rect);
        } else if (match->getKaratekaB()->getPoints() >= 0 && match->getKaratekaB()->getPoints() <= 9){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &counter2digit1Rect);
        }  

        
        SDL_Rect counter2digit2Rect = {numberCenterX+208, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT};

        int pointsLastDigit2 = match->getKaratekaB()->getPoints() % 10; // lastDigit will be 9

        if (pointsLastDigit2 == 9){
            SDL_RenderCopy(renderer, nineTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 8){
            SDL_RenderCopy(renderer, eightTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 7){
            SDL_RenderCopy(renderer, sevenTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 6){
            SDL_RenderCopy(renderer, sixTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 5){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 4){
            SDL_RenderCopy(renderer, fourTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 3){
            SDL_RenderCopy(renderer, threeTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 2){
            SDL_RenderCopy(renderer, twoTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 1){
            SDL_RenderCopy(renderer, oneTexture, NULL, &counter2digit2Rect);
        } else if (pointsLastDigit2 == 0){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &counter2digit2Rect);
        }


        // CLOCK

        SDL_Rect clockRect = {clockCenterX, clockCenterY, CLOCK_WIDTH, CLOCK_HEIGHT}; 
        SDL_RenderCopy(renderer, clockTexture, NULL, &clockRect);


        // First digit
        SDL_Rect digit1Rect = {numberCenterX-34, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT};
        SDL_RenderCopy(renderer, zeroTexture, NULL, &digit1Rect);

        // Second Digit
        SDL_Rect digit2Rect = {numberCenterX-14, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT}; 

        if (minutes == 3){
            SDL_RenderCopy(renderer, threeTexture, NULL, &digit2Rect);
        } else if (minutes == 2){
            SDL_RenderCopy(renderer, twoTexture, NULL, &digit2Rect);
        } else if (minutes == 1){
            SDL_RenderCopy(renderer, oneTexture, NULL, &digit2Rect);
        } else if (minutes >= 0){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &digit2Rect);
        }

        SDL_Rect colonRect = {colonCenterX, colonCenterY, COLON_WIDTH, COLON_HEIGHT}; 
        SDL_RenderCopy(renderer, colonTexture, NULL, &colonRect);

        SDL_Rect digit3Rect = {numberCenterX+14, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT};

        if (seconds >= 50 && seconds <= 59){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &digit3Rect);
        } else if (seconds >= 40 && seconds <= 49){
            SDL_RenderCopy(renderer, fourTexture, NULL, &digit3Rect);
        } else if (seconds >= 30 && seconds <= 39){
            SDL_RenderCopy(renderer, threeTexture, NULL, &digit3Rect);
        } else if (seconds >= 20 && seconds <= 29){
            SDL_RenderCopy(renderer, twoTexture, NULL, &digit3Rect);
        } else if (seconds >= 10 && seconds <= 19){
            SDL_RenderCopy(renderer, oneTexture, NULL, &digit3Rect);
        } else if (seconds >= 0 && seconds <= 9){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &digit3Rect);
        }

        int lastDigit = seconds % 10; // lastDigit will be 9
        SDL_Rect digit4Rect = {numberCenterX+34, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT}; 

        if (lastDigit == 9){
            SDL_RenderCopy(renderer, nineTexture, NULL, &digit4Rect);
        } else if (lastDigit == 8){
            SDL_RenderCopy(renderer, eightTexture, NULL, &digit4Rect);
        } else if (lastDigit == 7){
            SDL_RenderCopy(renderer, sevenTexture, NULL, &digit4Rect);
        } else if (lastDigit == 6){
            SDL_RenderCopy(renderer, sixTexture, NULL, &digit4Rect);
        } else if (lastDigit == 5){
            SDL_RenderCopy(renderer, fiveTexture, NULL, &digit4Rect);
        } else if (lastDigit == 4){
            SDL_RenderCopy(renderer, fourTexture, NULL, &digit4Rect);
        } else if (lastDigit == 3){
            SDL_RenderCopy(renderer, threeTexture, NULL, &digit4Rect);
        } else if (lastDigit == 2){
            SDL_RenderCopy(renderer, twoTexture, NULL, &digit4Rect);
        } else if (lastDigit == 1){
            SDL_RenderCopy(renderer, oneTexture, NULL, &digit4Rect);
        } else if (lastDigit >= 0){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &digit4Rect);
        }

        // REFEREE 

        SDL_Rect refereeRect;

        SDL_Rect yukoTextBoxRect;

        SDL_Rect wazariTextBoxRect;

        SDL_Rect ipponTextBoxRect;

        uint64_t currentTime = SDL_GetPerformanceCounter();
        double deltaTime = (double)(currentTime - animationStartTime) / (double)frequency;

        // Left Point Animation

        // Check if animation needs to be played
        if (isYukoLeftAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isYukoLeftAnimationPlaying = false;
            wait = false;
            } else {
                // Render Text Box

                yukoTextBoxCenterX = (screenWidth - YUKO_TEXTBOX_WIDTH) / 2;
                yukoTextBoxCenterY = ((screenHeight - YUKO_TEXTBOX_HEIGHT) / 2)-290;
                yukoTextBoxRect = {yukoTextBoxCenterX, yukoTextBoxCenterY, YUKO_TEXTBOX_WIDTH, YUKO_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, yukoTextBoxTexture, NULL, &yukoTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite

                refereeRect = {refereeCenterX-21, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isWazariLeftAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isWazariLeftAnimationPlaying = false;
            wait = false;
            } else {
                // Render Text Box

                wazariTextBoxCenterX = ((screenWidth - WAZARI_TEXTBOX_WIDTH) / 2);
                wazariTextBoxCenterY = ((screenHeight - WAZARI_TEXTBOX_HEIGHT) / 2)-290;
                wazariTextBoxRect = {wazariTextBoxCenterX, wazariTextBoxCenterY, WAZARI_TEXTBOX_WIDTH, WAZARI_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, wazariTextBoxTexture, NULL, &wazariTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite

                refereeRect = {refereeCenterX-21, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isIpponLeftAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isIpponLeftAnimationPlaying = false;
            wait = false;
            } else {
                // Render Text Box

                ipponTextBoxCenterX = ((screenWidth - IPPON_TEXTBOX_WIDTH) / 2);
                ipponTextBoxCenterY = ((screenHeight - IPPON_TEXTBOX_HEIGHT) / 2)-290;
                ipponTextBoxRect = {ipponTextBoxCenterX, ipponTextBoxCenterY, IPPON_TEXTBOX_WIDTH, IPPON_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, ipponTextBoxTexture, NULL, &ipponTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite
                refereeRect = {refereeCenterX-21, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isYukoRightAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isYukoRightAnimationPlaying = false;
            wait = false;
            } else {
                // Render Text Box

                yukoTextBoxCenterX = (screenWidth - YUKO_TEXTBOX_WIDTH) / 2;
                yukoTextBoxCenterY = ((screenHeight - YUKO_TEXTBOX_HEIGHT) / 2)-290;
                yukoTextBoxRect = {yukoTextBoxCenterX, yukoTextBoxCenterY, YUKO_TEXTBOX_WIDTH, YUKO_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, yukoTextBoxTexture, NULL, &yukoTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with Right point sprite
                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_RIGHTPOINT_WIDTH, REFEREE_RIGHTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeRightPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isIpponRightAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isIpponRightAnimationPlaying = false;
            wait = false;
            } else {
                // Render Text Box

                ipponTextBoxCenterX = ((screenWidth - IPPON_TEXTBOX_WIDTH) / 2);
                ipponTextBoxCenterY = ((screenHeight - IPPON_TEXTBOX_HEIGHT) / 2)-290;
                ipponTextBoxRect = {ipponTextBoxCenterX, ipponTextBoxCenterY, IPPON_TEXTBOX_WIDTH, IPPON_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, ipponTextBoxTexture, NULL, &ipponTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite
                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_RIGHTPOINT_WIDTH, REFEREE_RIGHTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeRightPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isWazariRightAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isWazariRightAnimationPlaying = false;
            wait = false;
            } else {
                // Render Text Box

                wazariTextBoxCenterX = ((screenWidth - WAZARI_TEXTBOX_WIDTH) / 2);
                wazariTextBoxCenterY = ((screenHeight - WAZARI_TEXTBOX_HEIGHT) / 2)-290;
                wazariTextBoxRect = {wazariTextBoxCenterX, wazariTextBoxCenterY, WAZARI_TEXTBOX_WIDTH, WAZARI_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, wazariTextBoxTexture, NULL, &wazariTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with Right point sprite

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeRightPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isStartMatchAnimationPlaying) {
            if (deltaTime >= 3.0) {  // Animation duration is 5 seconds
            isStartMatchAnimationPlaying = false;
            wait = false;
            } else {

                // Render referee with Right point sprite

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_STARTMATCH_WIDTH, REFEREE_STARTMATCH_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeStartMatchTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isPenaltyLeftAnimationPlaying) {
            if (deltaTime >= 3.0) {  // Animation duration is 5 seconds
            isPenaltyLeftAnimationPlaying = false;
            wait = false;
            } else {

                // Render referee with Right point sprite

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_PENALTYLEFT_WIDTH, REFEREE_PENALTYLEFT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereePenaltyLeftTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isPenaltyRightAnimationPlaying) {
            if (deltaTime >= 3.0) {  // Animation duration is 5 seconds
            isPenaltyRightAnimationPlaying = false;
            wait = false;
            } else {

                // Render referee with Right point sprite

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_PENALTYRIGHT_WIDTH, REFEREE_PENALTYRIGHT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereePenaltyRightTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else {



            // Render referee with normal sprite
            refereeRect = {refereeCenterX, refereeCenterY, REFEREE_STANDUP_WIDTH, REFEREE_STANDUP_HEIGHT};
            SDL_RenderCopyEx(renderer, refereeStandUpTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);


            
        }

        // Turn Set Up

        bool isFirstTurn = rngA(false) % 2 == 0; // 50% chance of being first

        // Decide the order of evaluating karatekas based on the random number generator
        bool evaluateKaratekaAFirst = (rngA(false) <= 50);

        
        // KARATEKAS RECT
        SDL_Rect karatekaRect;
        SDL_Rect karateka2Rect;

 
        bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

        string karateka1Action = match->getKaratekaA()->getDecision(rngA(false));
        string karateka2Action = match->getKaratekaB()->getDecision(rngB(false));

        //cout<<"Karateka 1 Decision: "<<karateka1Action<<endl;
        //cout<<"Karateka 2 Decision: "<<karateka2Action<<endl;

        /*

        // MANUAL CONTROLLERS
        // Handle player input
        const Uint8* state = SDL_GetKeyboardState(NULL); // Get keyboard state
        isMovingRight = state[SDL_SCANCODE_RIGHT];
        isMovingLeft = state[SDL_SCANCODE_LEFT];
        isMovingUp = state[SDL_SCANCODE_UP];
        isMovingDown = state[SDL_SCANCODE_DOWN];
        
        // Update karateka position based on movement flags
        if (isMovingRight && !isMovingLeft) {
            karatekaCenterX += 2;
        } else if (isMovingLeft && !isMovingRight) {
            karatekaCenterX -= 2;
        }
        if (isMovingUp && !isMovingDown) {
            karatekaCenterY -= 2;
        } else if (isMovingDown && !isMovingUp) {
            karatekaCenterY += 2;
        }

        posvk1->x = karatekaCenterX-90;
        posvk1->x = karatekaCenterX;
        posvk1->y = karatekaCenterY;

        match->getKaratekaA()->setPosition(posvk1);
        
        */

        



        if (evaluateKaratekaAFirst) {

        // KARATEKA A // Simulated

        if(!wait){

            if (karateka1Action == "left"){

                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("left");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("left");
                }
                
            } else if (karateka1Action == "right"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("right");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("right");
                }
                
            } 

            if (karateka1Action == "forward"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("forward");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("forward");
                }

                

                
            } else if (karateka1Action == "backward"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("backward");

                } else {
                    match->getKaratekaA()->updatePositionRecoil("backward");
                }
            } 

            if(karateka1Action == "backward-left"){
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("backward");
                match->getKaratekaA()->updatePosition("left");
            } else {
                match->getKaratekaA()->updatePositionRecoil("backward");
                match->getKaratekaA()->updatePositionRecoil("left");
            } 
            } else if (karateka1Action == "backward-right") {
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("backward");
                match->getKaratekaA()->updatePosition("right");

            } else {
                match->getKaratekaA()->updatePositionRecoil("backward");
                match->getKaratekaA()->updatePositionRecoil("right");
            }
            }

            if(karateka1Action == "forward-left"){
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("left");
            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("left");
            } 
            } else if (karateka1Action == "forward-right") {
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("right");

            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("right");
            }
            }



            if (karateka1Action == "oi-zuki"){ // if(decisionMaker() == "oi-zuki")

            string result = match->getKaratekaA()->punch("oi-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaOiZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "kin-geri"){ // if(decisionMaker() == "kin-geri")

            string result = match->getKaratekaA()->punch("kin-geri");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_KINGERI_WIDTH, KARATEKA_KINGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaKinGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "ushiro-geri"){ // if(decisionMaker() == "ushiro-geri")

            string result = match->getKaratekaA()->punch("ushiro-geri");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Wazari!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isWazariLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("wazari");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_USHIROGERI_WIDTH, KARATEKA_USHIROGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaUshiroGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "ura-zuki"){ // if(decisionMaker() == "ura-zuki")

            string result = match->getKaratekaA()->punch("ura-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_URAZUKI_WIDTH, KARATEKA_URAZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaUraZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "heiko-zuki"){ // if(decisionMaker() == "heiko-zuki")

            string result = match->getKaratekaA()->punch("heiko-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Ippon!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isIpponLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("ippon");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_HEIKOZUKI_WIDTH, KARATEKA_HEIKOZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaHeikoZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "mawashi-zuki"){ // if(decisionMaker() == "oi-zuki")

            string result = match->getKaratekaA()->punch("mawashi-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Wazari Call
                    cout<<"Wazari!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isWazariLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("wazari");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_MAWASHIZUKI_WIDTH, KARATEKA_MAWASHIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaMawashiZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "mae-geri"){

            string result = match->getKaratekaA()->kick("mae-geri");

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaMaeGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() != "block"){
                // Wazari Call
                cout<<"Wazari!"<<endl;

                
                // Referee Call
                    
                // Start animation
                isWazariLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaA()->setPoints("wazari");

                match = setKaratekasStartPosition(match, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                match->getKaratekaB()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka1Action == "block"){

            string result = match->getKaratekaA()->block();

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; 

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            SDL_RenderCopyEx(renderer, karatekaAgeUkeTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            
        } else if (karateka1Action == "yoko-geri"){

            string result = match->getKaratekaA()->kick("yoko-geri");

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaYokoGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() != "block"){
                // Ippon Call
                cout<<"Ippon!"<<endl;

                // Referee Call
                    
                // Start animation
                isIpponLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaA()->setPoints("ippon");

                match = setKaratekasStartPosition(match, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                match->getKaratekaB()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka1Action == "gyaku-zuki"){

            string result = match->getKaratekaA()->punch("gyaku-zuki");

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaGyakuZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() != "block"){
                // Yuko Call

                cout<<"Yuko!"<<endl;

                // Referee Call
                    
                // Start animation
                isYukoLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match->getKaratekaA()->setPoints("yuko");
                match = setKaratekasStartPosition(match, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                match->getKaratekaB()->updateMatchState();
                //matchState->printState();
                
            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else {

            // Set KaratekaState
            match->getKaratekaA()->setMatchStateMovement("stand-up");
            //match->getKaratekaA()->updateMatchState();

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            // Before rendering the karateka:
            SDL_RenderCopyEx(renderer, karatekaBasicStanceTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        }

        match->getKaratekaA()->setKaratekaRect(&karatekaRect);


        } else {

            // Set KaratekaState
            match->getKaratekaA()->setMatchStateMovement("stand-up");
            //match->getKaratekaA()->updateMatchState();

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            // Before rendering the karateka:
            SDL_RenderCopyEx(renderer, karatekaBasicStanceTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

        }

               

        // KARATEKA 2 // Simulated


        if(!wait){

        if (karateka2Action == "left"){

            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("left");
            } else {
                match->getKaratekaB()->updatePositionRecoil("left");
            }
            
        } else if (karateka2Action == "right"){
            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("right");
            } else {
                match->getKaratekaB()->updatePositionRecoil("right");
            }
            
        } 

        if (karateka2Action == "forward"){
            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("forward");
            } else {
                match->getKaratekaB()->updatePositionRecoil("forward");
            }

            

            
        } else if (karateka2Action == "backward"){
            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("backward");

            } else {
                match->getKaratekaB()->updatePositionRecoil("backward");
            }

            
        } 

        if(karateka2Action == "backward-left"){
        if(!areKaratekasColliding){
            match->getKaratekaA()->updatePosition("backward");
            match->getKaratekaA()->updatePosition("left");
        } else {
            match->getKaratekaA()->updatePositionRecoil("backward");
            match->getKaratekaA()->updatePositionRecoil("left");
        } 
        } else if (karateka2Action == "backward-right") {
        if(!areKaratekasColliding){
            match->getKaratekaA()->updatePosition("backward");
            match->getKaratekaA()->updatePosition("right");

        } else {
            match->getKaratekaA()->updatePositionRecoil("backward");
            match->getKaratekaA()->updatePositionRecoil("right");
        }
        }

        if(karateka2Action == "forward-left"){
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("left");
            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("left");
            } 
            } else if (karateka2Action == "forward-right") {
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("right");

            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("right");
            }
            }


        if (karateka2Action == "oi-zuki"){ //if(karateka2Action == "oi-zuki")

            string result = match->getKaratekaB()->punch("oi-zuki"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2OiZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "kin-geri"){ //if(karateka2Action == "kin-geri")

            string result = match->getKaratekaB()->punch("kin-geri"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_KINGERI_WIDTH, KARATEKA_KINGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2KinGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "ushiro-geri"){ //if(karateka2Action == "ushiro-geri")

            string result = match->getKaratekaB()->punch("ushiro-geri"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Wazari!"<<endl;
                match->getKaratekaB()->setPoints("wazari");

                // Start animation
                isWazariRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_USHIROGERI_WIDTH, KARATEKA_USHIROGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2UshiroGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "ura-zuki"){ //if(karateka2Action == "ura-zuki")

            string result = match->getKaratekaB()->punch("ura-zuki"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_URAZUKI_WIDTH, KARATEKA_URAZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2UraZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "heiko-zuki"){ //if(karateka2Action == "heiko-zuki")

            string result = match->getKaratekaB()->punch("heiko-zuki"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Ippon!"<<endl;
                match->getKaratekaB()->setPoints("ippon");

                // Start animation
                isIpponRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_HEIKOZUKI_WIDTH, KARATEKA_HEIKOZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2HeikoZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "mawashi-zuki"){ // if(decisionMaker() == "oi-zuki")

            string result = match->getKaratekaB()->punch("mawashi-zuki");           

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Wazari Call
                    cout<<"Wazari!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isWazariRightAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaB()->setPoints("wazari");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaB()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaB()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_MAWASHIZUKI_WIDTH, KARATEKA_MAWASHIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2MawashiZukiTexture, NULL, &karatekaRect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "gyaku-zuki"){ //(match->getKaratekaB()->punch("gyaku-zuki") == "gyaku-zuki"

            string result = match->getKaratekaB()->punch("gyaku-zuki"); 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2GyakuZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka2Action == "block"){ //karateka2Action == "block"

            string result = match->getKaratekaB()->block();

            karatekaRect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            SDL_RenderCopyEx(renderer, karateka2AgeUkeTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "yoko-geri"){ // YOKO GERI // (match->getKaratekaB()->kick("yoko-geri") == "yoko-geri"

            string result = match->getKaratekaB()->kick("yoko-geri");           

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2YokoGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){
                // Ippon Call
                cout<<"Ippon!"<<endl;

                // Referee Call
                    
                // Start animation
                isIpponRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaB()->setPoints("ippon");

                match = setKaratekasStartPosition(match, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka2Action == "mae-geri"){ // MAE GERI

            string result = match->getKaratekaB()->kick("mae-geri");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2MaeGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){
                // Ippon Call
                cout<<"Wazari!"<<endl;

                // Referee Call
                    
                // Start animation
                isWazariRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaB()->setPoints("wazari");

                match = setKaratekasStartPosition(match, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else {

            match->getKaratekaB()->setMatchStateMovement("stand-up");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2BasicStanceTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } 
       
        match->getKaratekaB()->setKaratekaRect(&karateka2Rect);


        } else {

            match->getKaratekaB()->setMatchStateMovement("stand-up");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2BasicStanceTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

        }
        } else {


            // KARATEKA 2 // Simulated

        if(!wait){

        if (karateka2Action == "left"){

            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("left");
            } else {
                match->getKaratekaB()->updatePositionRecoil("left");
            }
            
        } else if (karateka2Action == "right"){
            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("right");
            } else {
                match->getKaratekaB()->updatePositionRecoil("right");
            }
            
        } 

        if (karateka2Action == "forward"){
            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("forward");
            } else {
                match->getKaratekaB()->updatePositionRecoil("forward");
            }

            

            
        } else if (karateka2Action == "backward"){
            if(!areKaratekasColliding){
                match->getKaratekaB()->updatePosition("backward");

            } else {
                match->getKaratekaB()->updatePositionRecoil("backward");
            }

            
        } 

        if(karateka2Action == "backward-left"){
        if(!areKaratekasColliding){
            match->getKaratekaA()->updatePosition("backward");
            match->getKaratekaA()->updatePosition("left");
        } else {
            match->getKaratekaA()->updatePositionRecoil("backward");
            match->getKaratekaA()->updatePositionRecoil("left");
        } 
        } else if (karateka2Action == "backward-right") {
        if(!areKaratekasColliding){
            match->getKaratekaA()->updatePosition("backward");
            match->getKaratekaA()->updatePosition("right");

        } else {
            match->getKaratekaA()->updatePositionRecoil("backward");
            match->getKaratekaA()->updatePositionRecoil("right");
        }
        }

        if(karateka2Action == "forward-left"){
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("left");
            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("left");
            } 
            } else if (karateka2Action == "forward-right") {
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("right");

            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("right");
            }
            }


        if (karateka2Action == "oi-zuki"){ //if(karateka2Action == "oi-zuki")

            string result = match->getKaratekaB()->punch("oi-zuki"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2OiZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "kin-geri"){ //if(karateka2Action == "kin-geri")

            string result = match->getKaratekaB()->punch("kin-geri"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_KINGERI_WIDTH, KARATEKA_KINGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2KinGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "ushiro-geri"){ //if(karateka2Action == "ushiro-geri")

            string result = match->getKaratekaB()->punch("ushiro-geri"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Wazari!"<<endl;
                match->getKaratekaB()->setPoints("wazari");

                // Start animation
                isWazariRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_USHIROGERI_WIDTH, KARATEKA_USHIROGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2UshiroGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "ura-zuki"){ //if(karateka2Action == "ura-zuki")

            string result = match->getKaratekaB()->punch("ura-zuki"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_URAZUKI_WIDTH, KARATEKA_URAZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2UraZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "heiko-zuki"){ //if(karateka2Action == "heiko-zuki")

            string result = match->getKaratekaB()->punch("heiko-zuki"); 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                
                cout<<"Ippon!"<<endl;
                match->getKaratekaB()->setPoints("ippon");

                // Start animation
                isIpponRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            } 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_HEIKOZUKI_WIDTH, KARATEKA_HEIKOZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2HeikoZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "mawashi-zuki"){ // if(decisionMaker() == "oi-zuki")

            string result = match->getKaratekaB()->punch("mawashi-zuki");           

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Wazari Call
                    cout<<"Wazari!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isWazariRightAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaB()->setPoints("wazari");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaB()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaB()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_MAWASHIZUKI_WIDTH, KARATEKA_MAWASHIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2MawashiZukiTexture, NULL, &karatekaRect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "gyaku-zuki"){ //(match->getKaratekaB()->punch("gyaku-zuki") == "gyaku-zuki"

            string result = match->getKaratekaB()->punch("gyaku-zuki"); 

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2GyakuZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){

                cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");

                // Start animation
                isYukoRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;
                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka2Action == "block"){ //karateka2Action == "block"

            string result = match->getKaratekaB()->block();

            karatekaRect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; 

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            SDL_RenderCopyEx(renderer, karateka2AgeUkeTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka2Action == "yoko-geri"){ // YOKO GERI // (match->getKaratekaB()->kick("yoko-geri") == "yoko-geri"

            string result = match->getKaratekaB()->kick("yoko-geri");           

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2YokoGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){
                // Ippon Call
                cout<<"Ippon!"<<endl;

                // Referee Call
                    
                // Start animation
                isIpponRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaB()->setPoints("ippon");

                match = setKaratekasStartPosition(match, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka2Action == "mae-geri"){ // MAE GERI

            string result = match->getKaratekaB()->kick("mae-geri");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2MaeGeriTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->getKaratekaMovement() != "block"){
                // Ippon Call
                cout<<"Wazari!"<<endl;

                // Referee Call
                    
                // Start animation
                isWazariRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaB()->setPoints("wazari");

                match = setKaratekasStartPosition(match, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaB()->updateMatchState();
                match->getKaratekaA()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else {

            match->getKaratekaB()->setMatchStateMovement("stand-up");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2BasicStanceTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } 
       
        match->getKaratekaB()->setKaratekaRect(&karateka2Rect);


        } else {

            match->getKaratekaB()->setMatchStateMovement("stand-up");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2BasicStanceTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

        }
        


        if(!wait){

            if (karateka1Action == "left"){

                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("left");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("left");
                }                
            } else if (karateka1Action == "right"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("right");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("right");
                }                
            } 


            if (karateka1Action == "forward"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("forward");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("forward");
                }               
            } else if (karateka1Action == "backward"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("backward");

                } else {
                    match->getKaratekaA()->updatePositionRecoil("backward");
                }
            } 

            if(karateka1Action == "backward-left"){
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("backward");
                    match->getKaratekaA()->updatePosition("left");
                } else {
                    match->getKaratekaA()->updatePositionRecoil("forward");
                    match->getKaratekaA()->updatePositionRecoil("left");
                } 
            } else if (karateka1Action == "backward-right") {
                if(!areKaratekasColliding){
                    match->getKaratekaA()->updatePosition("backward");
                    match->getKaratekaA()->updatePosition("right");

                } else {
                    match->getKaratekaA()->updatePositionRecoil("backward");
                    match->getKaratekaA()->updatePositionRecoil("right");
                }
            }

            if(karateka1Action == "forward-left"){
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("left");
            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("left");
            } 
            } else if (karateka1Action == "forward-right") {
            if(!areKaratekasColliding){
                match->getKaratekaA()->updatePosition("forward");
                match->getKaratekaA()->updatePosition("right");

            } else {
                match->getKaratekaA()->updatePositionRecoil("forward");
                match->getKaratekaA()->updatePositionRecoil("right");
            }
            }



        if (karateka1Action == "oi-zuki"){ // if(decisionMaker() == "oi-zuki")

            string result = match->getKaratekaA()->punch("oi-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaOiZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "kin-geri"){ // if(decisionMaker() == "kin-geri")

            string result = match->getKaratekaA()->punch("kin-geri");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_KINGERI_WIDTH, KARATEKA_KINGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaKinGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "ushiro-geri"){ // if(decisionMaker() == "ushiro-geri")

            string result = match->getKaratekaA()->punch("ushiro-geri");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Wazari!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isWazariLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("wazari");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_USHIROGERI_WIDTH, KARATEKA_USHIROGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaUshiroGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "ura-zuki"){ // if(decisionMaker() == "ura-zuki")

            string result = match->getKaratekaA()->punch("ura-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_URAZUKI_WIDTH, KARATEKA_URAZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaUraZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "heiko-zuki"){ // if(decisionMaker() == "heiko-zuki")

            string result = match->getKaratekaA()->punch("heiko-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Ippon!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isIpponLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("ippon");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_HEIKOZUKI_WIDTH, KARATEKA_HEIKOZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaHeikoZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "mawashi-zuki"){ // if(decisionMaker() == "oi-zuki")

            string result = match->getKaratekaA()->punch("mawashi-zuki");           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Wazari Call
                    cout<<"Wazari!"<<endl;


                    // Referee Call
                    
                    // Start animation
                    isWazariLeftAnimationPlaying = true;
                    wait = true;


                    animationStartTime = SDL_GetPerformanceCounter();
                    // End Animation

                    match->getKaratekaA()->setPoints("wazari");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    match->getKaratekaB()->updateMatchState();
                    //matchState->printState();

                }

            } 

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_MAWASHIZUKI_WIDTH, KARATEKA_MAWASHIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaMawashiZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (karateka1Action == "mae-geri"){

            string result = match->getKaratekaA()->kick("mae-geri");

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaMaeGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() != "block"){
                // Wazari Call
                cout<<"Wazari!"<<endl;

                
                // Referee Call
                    
                // Start animation
                isWazariLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaA()->setPoints("wazari");

                match = setKaratekasStartPosition(match, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                match->getKaratekaB()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka1Action == "block"){

            string result = match->getKaratekaA()->block();

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; 

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            SDL_RenderCopyEx(renderer, karatekaAgeUkeTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            
        } else if (karateka1Action == "yoko-geri"){

            string result = match->getKaratekaA()->kick("yoko-geri");

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaYokoGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() != "block"){
                // Ippon Call
                cout<<"Ippon!"<<endl;

                // Referee Call
                    
                // Start animation
                isIpponLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation


                match->getKaratekaA()->setPoints("ippon");

                match = setKaratekasStartPosition(match, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                match->getKaratekaB()->updateMatchState();
                //matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (karateka1Action == "gyaku-zuki"){

            string result = match->getKaratekaA()->punch("gyaku-zuki");

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaGyakuZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() != "block"){
                // Yuko Call

                cout<<"Yuko!"<<endl;

                // Referee Call
                    
                // Start animation
                isYukoLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
                // End Animation

                match->getKaratekaA()->setPoints("yuko");
                match = setKaratekasStartPosition(match, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                match->getKaratekaB()->updateMatchState();
                //matchState->printState();
                
            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->getKaratekaMovement() == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else {

            // Set KaratekaState
            match->getKaratekaA()->setMatchStateMovement("stand-up");
            //match->getKaratekaA()->updateMatchState();

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            // Before rendering the karateka:
            SDL_RenderCopyEx(renderer, karatekaBasicStanceTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        }

        match->getKaratekaA()->setKaratekaRect(&karatekaRect);


        } else {

            // Set KaratekaState
            match->getKaratekaA()->setMatchStateMovement("stand-up");
            //match->getKaratekaA()->updateMatchState();

            karatekaRect = {match->getKaratekaA()->getPositionVector()->x, match->getKaratekaA()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            // Before rendering the karateka:
            SDL_RenderCopyEx(renderer, karatekaBasicStanceTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

        }

        }
        

        match->getKaratekaA()->updateMatchState();
        match->getKaratekaB()->updateMatchState();

        match->setTimeLeft(remainingTime);

        Karateka* winner = referee->declareWinner();
        
        Karateka* penalty = referee->callPenalty();

        if (penalty != NULL){
            match = setKaratekasStartPosition(match, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT);
            karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
            karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

            match->getKaratekaA()->updateMatchState();
            match->getKaratekaB()->updateMatchState();

            if(penalty == match->getKaratekaA()){
                cout<<"Penalty Commited by Karateka A!"<<endl;
                isPenaltyLeftAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();
            } else if (penalty == match->getKaratekaB()){
                cout<<"Penalty Commited by Karateka B!"<<endl;
                isPenaltyRightAnimationPlaying = true;
                wait = true;
                animationStartTime = SDL_GetPerformanceCounter();

            }

        }
        

        if (winner != NULL){
            match->setWinner(winner);
            wkc_womens_kumite->retrieveMatches(match);
            cout<<"The Winner is "<<match->getWinner()->getName()<<endl;
            running = false;
        }

        // ALWAYS RENDER THE PRESENT
        // Update the screen
        SDL_RenderPresent(renderer);



        
    }


    }

    




    
    // Clean up
    SDL_DestroyTexture(arenaTexture);
    SDL_DestroyTexture(karatekaTexture);
    SDL_DestroyTexture(karateka2Texture);
    SDL_DestroyTexture(grassTexture);
    SDL_DestroyTexture(karatekaBasicStanceTexture);
    SDL_DestroyTexture(karatekaOiZukiTexture);
    SDL_DestroyTexture(karatekaAgeUkeTexture);
    SDL_DestroyTexture(karatekaYokoGeriTexture);
    SDL_DestroyTexture(karatekaMaeGeriTexture);
    SDL_DestroyTexture(karateka2BasicStanceTexture);
    SDL_DestroyTexture(karateka2OiZukiTexture);
    SDL_DestroyTexture(karateka2GyakuZukiTexture);
    SDL_DestroyTexture(karateka2AgeUkeTexture);
    SDL_DestroyTexture(karateka2MaeGeriTexture);
    SDL_DestroyTexture(refereeStandUpTexture);
    SDL_DestroyTexture(refereeLeftPointTexture);
    SDL_DestroyTexture(refereeRightPointTexture);
    SDL_DestroyTexture(refereeStartMatchTexture);
    SDL_DestroyTexture(yukoTextBoxTexture);
    SDL_DestroyTexture(wazariTextBoxTexture);
    SDL_DestroyTexture(ipponTextBoxTexture);
    SDL_DestroyTexture(clockTexture);
    SDL_DestroyTexture(zeroTexture);
    SDL_DestroyTexture(oneTexture);
    SDL_DestroyTexture(twoTexture);
    IMG_Quit(); 
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}