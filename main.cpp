#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_keycode.h> 
#include "championship.hpp"
#include <random>
#include <cmath>

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

#define REFEREE_STANDUP_WIDTH 35
#define REFEREE_STANDUP_HEIGHT 21

#define REFEREE_LEFTPOINT_WIDTH 56
#define REFEREE_LEFTPOINT_HEIGHT 21

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

int rng(){
    random_device rd;
    mt19937 generator(rd());
    uniform_int_distribution<int> distribution(1, 30); // Generates numbers between 1 and 10
    int random_number = distribution(generator);
    return random_number;
}

Match* setKaratekasStartPosition(Match* match, int width, int height){

    int karatekaCenterX = (SCREEN_WIDTH - width) / 2;
    int karatekaCenterY = (SCREEN_HEIGHT - height) / 2;

    PositionVector* posvk1 = new PositionVector(); // Create new PositionVector;
    posvk1->loadPosition(karatekaCenterX-90, karatekaCenterY); //Load Karateka1 position in the arena into the PositionVector      

    posvk1->x = karatekaCenterX-90;
    posvk1->y = karatekaCenterY;

    match->getKaratekaA()->setPosition(posvk1);

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

    // KARATEKA 2 Textures

    SDL_Texture* karateka2BasicStanceTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_basic_stance.png");
    if (!karatekaBasicStanceTexture) {
        printf("Failed to load karateka basic stance sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2OiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_oi_zuki.png");
    if (!karatekaOiZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; 
    }

    SDL_Texture* karateka2GyakuZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_gyaku_zuki.png");
    if (!karatekaGyakuZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
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
    

    // Setting Karateka A

    Shotokan* A = new Shotokan(3); // Create new karateka shotokan style

    A->setName("Miho Miyahara"); // Set Karateka Name

    // Loading Starting Arena Position on the Karateka
    PositionVector* posvk1 = new PositionVector(); // Create new PositionVector;
    posvk1->loadPosition(karatekaCenterX-90, karatekaCenterY); //Load Karateka1 position in the arena into the PositionVector
    A->setPosition(posvk1); // Set PositionVector into Karateka
    PositionVector* postemp = A->getPositionVector(); // PositionVector Test
    cout<<"Position of Karateka A:  X="<<postemp->x<<" Y="<<postemp->y<<endl; // Print Karateka 1 starting position on the arena
    int q = A->getPositionVector()->x;

    A->setArenaSide("left");
    cout<<"Arena side = "<<A->getArenaSide()<<endl;

    // Setting Karateka B

    Shotokan* B = new Shotokan(3); 

    B->setName("Shara Hubrich"); 

    PositionVector* posvk2 = new PositionVector(); 
    posvk2->loadPosition(karateka2CenterX+95, karateka2CenterY); 
    B->setPosition(posvk2); 
    PositionVector* postempB = B->getPositionVector(); 
    cout<<"Position of Karateka B:  X="<<postempB->x<<" Y="<<postempB->y<<endl; 
    
    B->setArenaSide("right");
    cout<<"Arena side = "<<B->getArenaSide()<<endl;


    // Setting Match

    Match* match = new Match(A,B);
    match->printMatchNames();
    match->simulateMatch();

    State* matchState = match->getKaratekaA()->getMatchState();

    bool isYukoLeftAnimationPlaying = false;  // Flag to track animation state
    uint64_t animationStartTime;     // Time when Yuko animation started

    bool isWazariLeftAnimationPlaying = false;  // Flag to track animation state

    bool isIpponLeftAnimationPlaying = false;  // Flag to track animation state


    uint64_t matchStartTime;  // Time when the match starts
    const double matchDuration = 3.0 * 60.0;  // Match duration in seconds (3 minutes)
    bool matchOngoing = true;  // Flag to track match state

    matchStartTime = SDL_GetPerformanceCounter();

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

        // Display remaining time (e.g., using text rendering functions)
        //cout << "Time Remaining: " << minutes << ":" << seconds << endl;

        


        // Clear screen (adjust color if needed)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // GAME LOGIC

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
        posvk1->y = karatekaCenterY;

        match->getKaratekaA()->setPosition(posvk1);
        

        // RENDERING TASKS
        // ARENA RENDERING

        // GRASS
        // Define a rectangle to represent the position and size of the grass on the screen
        SDL_Rect grassRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT}; // Adjust values as needed

        // Render the texture to the screen
        SDL_RenderCopy(renderer, grassTexture, NULL, &grassRect);

        // Render image (adjust position and size as needed)
        SDL_Rect dstRect = {centerX, centerY, FLOOR_WIDTH, FLOOR_HEIGHT};
        SDL_RenderCopy(renderer, texture, NULL, &dstRect);
       
        SDL_Rect arenaRect = {arenaCenterX, arenaCenterY, ARENA_WIDTH, ARENA_HEIGHT}; 
        SDL_RenderCopy(renderer, arenaTexture, NULL, &arenaRect);



        // KARATEK A COUNTER

        SDL_Rect counterRect = {counterCenterX, counterCenterY, COUNTER_WIDTH, COUNTER_HEIGHT}; 
        SDL_RenderCopy(renderer, counterTexture, NULL, &counterRect);


        // First digit
        SDL_Rect counterdigit1Rect = {numberCenterX-214, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT};
        //SDL_RenderCopy(renderer, zeroTexture, NULL, &counterdigit1Rect);


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
        //SDL_RenderCopy(renderer, zeroTexture, NULL, &counterdigit2Rect);


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
        //SDL_RenderCopy(renderer, zeroTexture, NULL, &counter2digit1Rect);  

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
        //SDL_RenderCopy(renderer, zeroTexture, NULL, &counter2digit2Rect);

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

        //cout << "Time Remaining: " << minutes << ":" << seconds << endl;


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
        } else if (minutes == 0){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &digit2Rect);
        }

        //SDL_Rect digit1Rect = {numberCenterX-34, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT}; 
        //SDL_Rect digit2Rect = {numberCenterX-14, numberCenterY, NUMBER_WIDTH, NUMBER_HEIGHT}; 
        //SDL_RenderCopy(renderer, zeroTexture, NULL, &digit2Rect);

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
        } else if (lastDigit == 0){
            SDL_RenderCopy(renderer, zeroTexture, NULL, &digit4Rect);
        }

        


        
        //SDL_RenderCopy(renderer, zeroTexture, NULL, &digit4Rect);

        

        SDL_Rect karatekaRect;
        SDL_Rect karateka2Rect;

        // REFEREE 

        SDL_Rect refereeRect;

        SDL_Rect yukoTextBoxRect;

        SDL_Rect wazariTextBoxRect;

        SDL_Rect ipponTextBoxRect;

        //refereeRect = {refereeCenterX, refereeCenterY, REFEREE_STANDUP_WIDTH, REFEREE_STANDUP_HEIGHT}; 

        //SDL_RenderCopyEx(renderer, refereeStandUpTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);

        uint64_t currentTime = SDL_GetPerformanceCounter();
        double deltaTime = (double)(currentTime - animationStartTime) / (double)frequency;

        // Check if animation needs to be played
        if (isYukoLeftAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isYukoLeftAnimationPlaying = false;
            } else {
                // Render Text Box

                yukoTextBoxCenterX = (screenWidth - YUKO_TEXTBOX_WIDTH) / 2;
                yukoTextBoxCenterY = ((screenHeight - YUKO_TEXTBOX_HEIGHT) / 2)-290;
                yukoTextBoxRect = {yukoTextBoxCenterX, yukoTextBoxCenterY, YUKO_TEXTBOX_WIDTH, YUKO_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, yukoTextBoxTexture, NULL, &yukoTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite
                refereeCenterX = (screenWidth - REFEREE_LEFTPOINT_WIDTH) / 2;
                refereeCenterY = ((screenHeight - REFEREE_LEFTPOINT_HEIGHT) / 2)-250;
                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isWazariLeftAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isWazariLeftAnimationPlaying = false;
            } else {
                // Render Text Box

                wazariTextBoxCenterX = ((screenWidth - WAZARI_TEXTBOX_WIDTH) / 2);
                wazariTextBoxCenterY = ((screenHeight - WAZARI_TEXTBOX_HEIGHT) / 2)-290;
                wazariTextBoxRect = {wazariTextBoxCenterX, wazariTextBoxCenterY, WAZARI_TEXTBOX_WIDTH, WAZARI_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, wazariTextBoxTexture, NULL, &wazariTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite
                refereeCenterX = (screenWidth - REFEREE_LEFTPOINT_WIDTH) / 2;
                refereeCenterY = ((screenHeight - REFEREE_LEFTPOINT_HEIGHT) / 2)-250;
                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else if (isIpponLeftAnimationPlaying) {
            if (deltaTime >= 1.0) {  // Animation duration is 5 seconds
            isIpponLeftAnimationPlaying = false;
            } else {
                // Render Text Box

                ipponTextBoxCenterX = ((screenWidth - IPPON_TEXTBOX_WIDTH) / 2);
                ipponTextBoxCenterY = ((screenHeight - IPPON_TEXTBOX_HEIGHT) / 2)-290;
                ipponTextBoxRect = {ipponTextBoxCenterX, ipponTextBoxCenterY, IPPON_TEXTBOX_WIDTH, IPPON_TEXTBOX_HEIGHT};
                SDL_RenderCopyEx(renderer, ipponTextBoxTexture, NULL, &ipponTextBoxRect, 0, NULL, SDL_FLIP_NONE);


                // Render referee with left point sprite
                refereeCenterX = (screenWidth - REFEREE_LEFTPOINT_WIDTH) / 2;
                refereeCenterY = ((screenHeight - REFEREE_LEFTPOINT_HEIGHT) / 2)-250;
                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT};
                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
            }
        } else {
            // Render referee with normal sprite
            refereeCenterX = (screenWidth - REFEREE_STANDUP_WIDTH) / 2;
            refereeCenterY = ((screenHeight - REFEREE_STANDUP_HEIGHT) / 2)-250;
            refereeRect = {refereeCenterX, refereeCenterY, REFEREE_STANDUP_WIDTH, REFEREE_STANDUP_HEIGHT};
            SDL_RenderCopyEx(renderer, refereeStandUpTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
        }

        // KARATEKA A // Keyboard Controlled

        //State* karateka1State = A->getKaratekaState();

        isMKeyPressed = state[SDL_SCANCODE_M];
        isNKeyPressed = state[SDL_SCANCODE_N];
        isBKeyPressed = state[SDL_SCANCODE_B];
        isJKeyPressed = state[SDL_SCANCODE_J];
        isKKeyPressed = state[SDL_SCANCODE_K];

        


        if (isMKeyPressed){

            string result = match->getKaratekaA()->punch("oi-zuki", rng());           

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                if (match->getKaratekaB()->getMatchState()->movement == "block"){
                    //cout<<"Attack Blocked!"<<endl;
                    
                } else {

                    // Yuko Call
                    cout<<"Yuko!"<<endl;



                    // Referee Call
                    
                    // Start animation
                    isYukoLeftAnimationPlaying = true;
                    animationStartTime = SDL_GetPerformanceCounter();

                    refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT}; 

                    SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
                    // End Animation

                    match->getKaratekaA()->setPoints("yuko");
                    match = setKaratekasStartPosition(match, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT);
                    karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                    karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                    match->getKaratekaA()->updateMatchState();
                    matchState->printState();

                }

            } 

            karatekaRect = {karatekaCenterX, karatekaCenterY, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaOiZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else if (isNKeyPressed){

            string result = match->getKaratekaA()->manualkick("mae-geri");

            karatekaRect = {karatekaCenterX, karatekaCenterY, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaMaeGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->movement != "block"){
                // Wazari Call
                cout<<"Wazari!"<<endl;

                
                // Referee Call
                    
                // Start animation
                isWazariLeftAnimationPlaying = true;
                animationStartTime = SDL_GetPerformanceCounter();

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT}; 

                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
                // End Animation


                match->getKaratekaA()->setPoints("wazari");

                match = setKaratekasStartPosition(match, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->movement == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (isBKeyPressed){

            string result = match->getKaratekaA()->block(rng());

            karatekaRect = {karatekaCenterX, karatekaCenterY, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; 

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            SDL_RenderCopyEx(renderer, karatekaAgeUkeTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            
        } else if (isJKeyPressed){

            string result = match->getKaratekaA()->manualkick("yoko-geri");

            karatekaRect = {karatekaCenterX, karatekaCenterY, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaYokoGeriTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->movement != "block"){
                // Ippon Call
                cout<<"Ippon!"<<endl;

                // Referee Call
                    
                // Start animation
                isIpponLeftAnimationPlaying = true;
                animationStartTime = SDL_GetPerformanceCounter();

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT}; 

                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
                // End Animation


                match->getKaratekaA()->setPoints("ippon");

                match = setKaratekasStartPosition(match, KARATEKA_YOKOGERI_WIDTH, KARATEKA_YOKOGERI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                matchState->printState();

            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->movement == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (isKKeyPressed){

            string result = match->getKaratekaA()->punch("gyaku-zuki", rng());

            karatekaRect = {karatekaCenterX, karatekaCenterY, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karatekaGyakuZukiTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaA()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->movement != "block"){
                // Yuko Call

                cout<<"Yuko!"<<endl;

                // Referee Call
                    
                // Start animation
                isYukoLeftAnimationPlaying = true;
                animationStartTime = SDL_GetPerformanceCounter();

                refereeRect = {refereeCenterX, refereeCenterY, REFEREE_LEFTPOINT_WIDTH, REFEREE_LEFTPOINT_HEIGHT}; 

                SDL_RenderCopyEx(renderer, refereeLeftPointTexture, NULL, &refereeRect, 0, NULL, SDL_FLIP_NONE);
                // End Animation

                match->getKaratekaA()->setPoints("yuko");
                match = setKaratekasStartPosition(match, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT);
                karatekaCenterX = match->getKaratekaA()->getPositionVector()->x;
                karatekaCenterY = match->getKaratekaA()->getPositionVector()->y;

                match->getKaratekaA()->updateMatchState();
                matchState->printState();
                
            } else if (areKaratekasColliding && match->getKaratekaB()->getMatchState()->movement == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else {

            // Set KaratekaState
            match->getKaratekaA()->setMatchStateMovement("stand-up");

            karatekaRect = {karatekaCenterX, karatekaCenterY, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            // Before rendering the karateka:
            SDL_RenderCopyEx(renderer, karatekaBasicStanceTexture, NULL, &karatekaRect, match->getKaratekaA()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        }

        match->getKaratekaA()->setKaratekaRect(&karatekaRect);
        

        // KARATEKA 2 // Simulated

        bool fuck = true;

        //B->updatePosition("left");
        //B->updatePosition("forward");
        
        // if match->getKaratekaB()->getDecision() == "oi-zuki"
        if (match->getKaratekaB()->punch("oi-zuki", rng()) == "oi-zuki"){

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2OiZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->movement != "block"){
                //cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");
            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->movement == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (match->getKaratekaB()->punch("gyaku-zuki", rng()) == "gyaku-zuki"){

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2GyakuZukiTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);

            bool areKaratekasColliding = match->getKaratekaB()->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->movement != "block"){
                //cout<<"Yuko!"<<endl;
                match->getKaratekaB()->setPoints("yuko");
            } else if (areKaratekasColliding && match->getKaratekaA()->getMatchState()->movement == "block"){
                //cout<<"Attack Blocked!"<<endl;
            }
            
        } else if (match->getKaratekaB()->block(rng()) == "block"){

            string result = match->getKaratekaB()->block(rng());

            karatekaRect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2AgeUkeTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        } else {

            match->getKaratekaB()->setMatchStateMovement("stand-up");

            karateka2Rect = {match->getKaratekaB()->getPositionVector()->x, match->getKaratekaB()->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; 

            SDL_RenderCopyEx(renderer, karateka2BasicStanceTexture, NULL, &karateka2Rect, match->getKaratekaB()->getRotationAngle(), NULL, SDL_FLIP_NONE);
            
        }
        match->getKaratekaB()->setKaratekaRect(&karateka2Rect);

        match->getKaratekaA()->updateMatchState();
        match->getKaratekaB()->updateMatchState();


   


        // ALWAYS RENDER THE PRESENT
        // Update the screen
        SDL_RenderPresent(renderer);

        
    }

    // Clean up
    SDL_DestroyTexture(arenaTexture);
    IMG_Quit(); // Important to deinitialize SDL_image
    SDL_DestroyTexture(texture);
    IMG_Quit();
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}