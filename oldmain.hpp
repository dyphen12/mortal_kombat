#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <SDL2/SDL_keycode.h> // Include for keyboard input
#include "championship.hpp"

#define SCREEN_WIDTH 1280 //640
#define SCREEN_HEIGHT 720 //360

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

#define KARATEKA_AGEUKE_WIDTH 49
#define KARATEKA_AGEUKE_HEIGHT 35

#define TREE_WIDTH 120
#define TREE_HEIGHT 244

bool isMovingRight = false;
bool isMovingLeft = false;
bool isMovingUp = false;
bool isMovingDown = false;
bool isMKeyPressed = false;
bool isNKeyPressed = false;
bool isBKeyPressed = false;
//int karatekaSpeed = 2; // Adjust movement speed

int karatekaSpriteSizeW;
int karatekaSpriteSizeH;


int main(int argc, char** argv){
    // SDL initialization
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return 1;
    }

    // Create window (replace "SLD test" with your desired title)
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
        return 1; // Handle error here
    }

    SDL_Texture* karatekaTexture = IMG_LoadTexture(renderer, "assets/Karateka.png");
    if (!karatekaTexture) {
        printf("Failed to load karateka texture! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karateka2Texture = IMG_LoadTexture(renderer, "assets/Karateka_var.png");
    if (!karateka2Texture) {
        printf("Failed to load karateka texture! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* treeTexture = IMG_LoadTexture(renderer, "assets/tree.png");
    if (!treeTexture) {
        printf("Failed to load tree! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* grassTexture = IMG_LoadTexture(renderer, "assets/grass.png");
    if (!grassTexture) {
        printf("Failed to load grass! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    // KARATEKA 1 Textures

    SDL_Texture* karatekaBasicStanceTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_basic_stance.png");
    if (!karatekaBasicStanceTexture) {
        printf("Failed to load karateka basic stance sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karatekaOiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_oi_zuki.png");
    if (!karatekaOiZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karatekaGyakuZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_gyaku_zuki.png");
    if (!karatekaGyakuZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karatekaAgeUkeTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_age_uke.png");
    if (!karatekaAgeUkeTexture) {
        printf("Failed to load karateka age uke sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karatekaYokoGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_yoko_geri.png");
    if (!karatekaYokoGeriTexture) {
        printf("Failed to load karateka yokogeri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karatekaMaeGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka_mae_geri.png");
    if (!karatekaMaeGeriTexture) {
        printf("Failed to load karateka mae geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    // KARATEKA 2 Textures

    SDL_Texture* karateka2BasicStanceTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_basic_stance.png");
    if (!karatekaBasicStanceTexture) {
        printf("Failed to load karateka basic stance sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karateka2OiZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_oi_zuki.png");
    if (!karatekaOiZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karateka2GyakuZukiTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_gyaku_zuki.png");
    if (!karatekaGyakuZukiTexture) {
        printf("Failed to load karateka oi_zuki sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karateka2AgeUkeTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_age_uke.png");
    if (!karateka2AgeUkeTexture) {
        printf("Failed to load karateka age uke sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karateka2YokoGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_yoko_geri.png");
    if (!karateka2YokoGeriTexture) {
        printf("Failed to load karateka2 yoko geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    SDL_Texture* karateka2MaeGeriTexture = IMG_LoadTexture(renderer, "assets/karateka_sprites/Karateka2_mae_geri.png");
    if (!karateka2MaeGeriTexture) {
        printf("Failed to load karateka mae geri sprite! SDL_image Error: %s\n", IMG_GetError());
        return 1; // Handle error here
    }

    // Get screen dimensions
    int screenWidth = SCREEN_WIDTH;
    int screenHeight = SCREEN_HEIGHT;

    int centerX = (screenWidth - FLOOR_WIDTH) / 2;
    int centerY = (screenHeight - FLOOR_HEIGHT) / 2;

    int arenaCenterX = (screenWidth - ARENA_WIDTH) / 2;
    int arenaCenterY = (screenHeight - ARENA_HEIGHT) / 2;

    int karatekaCenterX = (screenWidth - KARATEKA_WIDTH) / 2;
    int karatekaCenterY = (screenHeight - KARATEKA_HEIGHT) / 2;

    int karateka2CenterX = (screenWidth - KARATEKA_WIDTH) / 2;
    int karateka2CenterY = (screenHeight - KARATEKA_HEIGHT) / 2;

    int treeCenterX = (screenWidth - TREE_WIDTH) / 2;
    int treeCenterY = (screenHeight - TREE_HEIGHT) / 2;
    

    //run_karateka_process();

    //Championship* WKChampionship = new Championship();

    //WKChampionship->printKaratekaList();

    //WKChampionship->signUpKarateka(G1);
    //WKChampionship->signUpKarateka(G2);

    //WKChampionship->printKaratekaList();

    // MATCH SIMULATION DEVELOPMENT

    //Karateka* G1 = new Karateka(1);
    //Karateka* G2 = new Karateka(2);

    //G1->setName("Shara Hubrich");
    //G2->setName("Miho Miyahara");

    //G1->setStyle("shotokan");
    //G2->setStyle("shotokan");


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
    //cout<<" QQQQQ "<<q;


    // Setting Karateka B

    Shotokan* B = new Shotokan(3); // Create new karateka shotokan style

    B->setName("Shara Hubrich"); // Set Karateka Name

    // Loading Starting Arena Position on the Karateka
    PositionVector* posvk2 = new PositionVector(); // Create new PositionVector;
    posvk2->loadPosition(karateka2CenterX+95, karateka2CenterY); //Load Karateka1 position in the arena into the PositionVector
    B->setPosition(posvk2); // Set PositionVector into Karateka
    PositionVector* postempB = B->getPositionVector(); // PositionVector Test
    cout<<"Position of Karateka B:  X="<<postempB->x<<" Y="<<postempB->y<<endl; // Print Karateka 1 starting position on the arena


    // Setting Match

    Match* match1 = new Match(A,B);
    match1->printMatchNames();
    match1->simulateMatch();


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

        // Clear screen (adjust color if needed)
        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
        SDL_RenderClear(renderer);

        // Handle player input
        //const Uint8* state = SDL_GetKeyboardState(NULL); // Get keyboard state

        // GAME LOGIC

        //Karateka* k1 = new Karateka(1);
        //Karateka* k2 = new Karateka(2);

        //Match* match = new Match(k1, k2);

        //match->startMatch();


        // MOVEMENT PROCESS

        //run_karateka_process();

 

        // Handle player input
        const Uint8* state = SDL_GetKeyboardState(NULL); // Get keyboard state

        // Update movement flags based on key presses
        // Update movement flags based on key presses
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
    

        // Update and render the rest of your game logic (replace with your logic)
        // G1->doSomething();
        // A->doSomethingElse();


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
       
        // Define a rectangle to represent the position and size of the arena on the screen
        SDL_Rect arenaRect = {arenaCenterX, arenaCenterY, ARENA_WIDTH, ARENA_HEIGHT}; // Adjust values as needed

        // Render the texture to the screen
        SDL_RenderCopy(renderer, arenaTexture, NULL, &arenaRect);



        // KARATEKA A // Keyboard Controlled
        //posvk1->loadPosition

        //UPDATE POSITION VECTOR
        //A->updatePosition("forward");
        //A->updatePosition("left");

        SDL_Rect karatekaRect;
        SDL_Rect karateka2Rect;

        

        isMKeyPressed = state[SDL_SCANCODE_M];
        isNKeyPressed = state[SDL_SCANCODE_N];
        isBKeyPressed = state[SDL_SCANCODE_B];
        if (isMKeyPressed){

            string result = A->punch("oi-zuki");

            bool areKaratekasColliding = A->checkCollision(karatekaRect, karateka2Rect);

            if (areKaratekasColliding){
                
                cout<<"Yuko!"<<endl;
            }

            cout<<"Oi Zuki!"<<endl;
            // Define a rectangle to represent the position and size of the arena on the screen
            karatekaRect = {karatekaCenterX-90, karatekaCenterY, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karatekaOiZukiTexture, NULL, &karatekaRect);
            
        } else if (isNKeyPressed){

            string result = A->manualkick("mae-geri");

            cout<<"Mae Geri!"<<endl;
            // Define a rectangle to represent the position and size of the arena on the screen
            karatekaRect = {karatekaCenterX-90, karatekaCenterY, KARATEKA_MAEGERI_WIDTH, KARATEKA_MAEGERI_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karatekaMaeGeriTexture, NULL, &karatekaRect);
            
        } else if (isBKeyPressed){

            string result = A->block();

            cout<<"block!"<<endl;
            // Define a rectangle to represent the position and size of the arena on the screen
            karatekaRect = {karatekaCenterX-90, karatekaCenterY, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karatekaAgeUkeTexture, NULL, &karatekaRect);
            
        } else {
            // Define a rectangle to represent the position and size of the arena on the screen
            karatekaRect = {karatekaCenterX-90, karatekaCenterY, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karatekaBasicStanceTexture, NULL, &karatekaRect);
            
        }
        

        // Define a rectangle to represent the position and size of the arena on the screen
        //SDL_Rect karatekaRect = {A->getPositionVector()->x, A->getPositionVector()->y, KARATEKA_WIDTH, KARATEKA_HEIGHT}; // Adjust values as needed

        // Render the texture to the screen
        //SDL_RenderCopy(renderer, karatekaTexture, NULL, &karatekaRect);


        // KARATEKA 2 // Simulated

        if (B->punch("oi-zuki") == "oi-zuki"){

            cout<<"Oi Zuki!"<<endl;
            // Define a rectangle to represent the position and size of the arena on the screen
            karateka2Rect = {B->getPositionVector()->x, B->getPositionVector()->y, KARATEKA_OIZUKI_WIDTH, KARATEKA_OIZUKI_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karateka2OiZukiTexture, NULL, &karateka2Rect);
            
        } else if (B->punch("gyaku-zuki") == "gyaku-zuki"){

            cout<<"Gyaku Zuki!"<<endl;
            // Define a rectangle to represent the position and size of the arena on the screen
            karateka2Rect = {B->getPositionVector()->x, B->getPositionVector()->y, KARATEKA_GYAKUZUKI_WIDTH, KARATEKA_GYAKUZUKI_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karateka2GyakuZukiTexture, NULL, &karateka2Rect);
            
        } else if (B->block() == "block"){

            string result = B->block();

            cout<<"block!"<<endl;
            // Define a rectangle to represent the position and size of the arena on the screen
            karatekaRect = {B->getPositionVector()->x, B->getPositionVector()->y, KARATEKA_AGEUKE_WIDTH, KARATEKA_AGEUKE_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karateka2AgeUkeTexture, NULL, &karatekaRect);
            
        } else {
            // Define a rectangle to represent the position and size of the arena on the screen
            karateka2Rect = {B->getPositionVector()->x, B->getPositionVector()->y, KARATEKA_BASIC_WIDTH, KARATEKA_BASIC_HEIGHT}; // Adjust values as needed

            // Render the texture to the screen
            SDL_RenderCopy(renderer, karateka2BasicStanceTexture, NULL, &karateka2Rect);
            
        }


        

        // Define a rectangle to represent the position and size of the arena on the screen
        // SDL_Rect karateka2Rect = {karateka2CenterX+95, karateka2CenterY, KARATEKA_WIDTH, KARATEKA_HEIGHT}; // Adjust values as needed

        // Render the texture to the screen
        // SDL_RenderCopy(renderer, karateka2Texture, NULL, &karateka2Rect);       


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