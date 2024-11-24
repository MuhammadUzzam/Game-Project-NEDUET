#include "raylib.h"
#include "raymath.h"

//coin setup
int coinscore=0;
typedef struct Coin {
    Vector2 position;
    bool collected;
} Coin;

Sound coinSound;
Texture2D frames[6]; 
Texture2D scarfy;
int currentFrame = 0;
float frameTime = 0.1f; 
float timer = 0.0f;     

// Coin positions and setup
Coin coins[50];
int collected = 0;
void DrawCoins() {
    // This loop draws coins in groups of 5 with a dynamic gap
    for (int i = 0; i < 50; i++) {        
        if (!coins[i].collected) {
            // Source rectangle for coin animation frame
            Rectangle sourceRect = {0, 0, (float)frames[currentFrame].width, (float)frames[currentFrame].height};
            
            
            // Calculate which group the coin is in (0-4, 5-9, 10-14, etc.)
            int groupIndex = i / 5; // Every 5 coins will belong to a new group
            
            // Set the initial starting point (gap between groups of coins)
            coins[i].position.x = 600 + (groupIndex * 700); // Gap between groups of coins
            
            // Within each group, position coins in a row with a 50-pixel gap
            coins[i].position.x += (i % 5) * 50; // For coins 0-4 in the group, the x positions will be 0, 50, 100, ...

            // Adjust Y position based on groupIndex
            if (groupIndex %2==0 ) {
                // For the first two groups, place them in the air (y = 400)
                coins[i].position.y = 420; 
               
            } else {
                // For the third group, place it closer to the ground (y = 550)
                coins[i].position.y = 520;  // Zameen ke paas
              
            }
            // Destination rectangle for drawing the coin
            Rectangle destRect = {coins[i].position.x, coins[i].position.y, frames[currentFrame].width * 0.01f, frames[currentFrame].height * 0.01f};
            
            // Draw the coin
            DrawTexturePro(frames[currentFrame], sourceRect, destRect, (Vector2){0, 0}, 0.0f, WHITE);
           // DrawRectangleLines(coins[i].position.x, coins[i].position.y, frames[currentFrame].width * 0.0f, frames[currentFrame].height * 0.0f, RED); // Coin outline
        }
    }
}
void UpdateCoinAnimation() {
    timer += GetFrameTime();
    if (timer >= frameTime) {
        timer = 0.0f;
        currentFrame = (currentFrame + 1) % 6; // Cycle through frames
    }
}
void UpdateCoinCollection(Vector2 scarfyPosition, Rectangle scarfyRect, Sound coinSound) {
    for (int i = 0; i < 50; i++) {
        if (!coins[i].collected) { // Check if the coin has already been collected
            Rectangle coinRect = {coins[i].position.x, coins[i].position.y, frames[currentFrame].width * 0.5f, frames[currentFrame].height * 0.5f};
            
            if (CheckCollisionRecs(scarfyRect, coinRect)) {
                PlaySound(coinSound);   // Play coin collection sound
                coins[i].collected = true;  // Mark the coin as collected
                collected += 1;  // Increase the score
            }
        }
    }
}
void ResetCoins() {
    collected=0;
     for (int i = 0; i < 50; i++) {
        
        coins[i].position = (Vector2){100.0f + 1000.0f, 400.0f};
        coins[i].collected = false;
        //coinscore = 0;
        
    }
}
const int screenWidth = 900;
const int screenHeight = 600;
const int scarfySpeed =4;
const float gravity = 0.3;
const int groundYPos = 3 * (screenHeight) / 4;
const int jumpUpFrame = 3;
const int jumpDownFrame = 4;
const int maxObstacles = 100;  // Maximum number of obstacles
typedef struct Obstacle {
    Rectangle rect;
    float speed;
} Obstacle;
const int num_of_Backgrounds = 30;
bool isScarfyOnGround(Texture2D* scarfy, Vector2* scarfyPosition) {
    if (scarfyPosition->y + scarfy->height >= groundYPos) {
        return true;
    } else {
        return false;
    }
}
void DrawScrollingBackground(Texture2D background, float offset, float speed) {
    float backgroundWidth = background.width;
    float firstPosition = -offset * speed / 4;
    // Draw the two backgrounds
    DrawTexture(background, (int)firstPosition, -170, WHITE);
    for (int i = 0; i < num_of_Backgrounds; i++) {
        float position = firstPosition + i * backgroundWidth;
        DrawTexture(background, (int)position, -170, WHITE);
    }
} 
  bool checkCollision(Vector2 scarfyPosition, Rectangle scarfyRect, Obstacle obstacle) {
    return CheckCollisionRecs(scarfyRect, obstacle.rect);
}
void updateObstacle(Obstacle* obstacle) {
    obstacle->rect.x -= obstacle->speed;
}
int main(void)
{
    InitWindow(screenWidth, screenHeight, "raylib - 2D Character Animation");
    InitAudioDevice();          
    Texture2D scarfy = LoadTexture("scarfy.png");    
    for (int i = 0; i < 6; i++) {
        char filename[20];
        sprintf(filename, "c%d.png", i); // It saves the output to a char array name filename
        frames[i] = LoadTexture(filename);
    }
     for (int i = 0; i < 50; i++) {        
        coins[i].position = (Vector2){100.0f + 1000.0f, 400.0f};
        coins[i].collected = false;       
    }
    
    Texture2D frontbackground= LoadTexture("front.png");
    Texture2D background0 = LoadTexture("layer0.png");
    Texture2D background1 = LoadTexture("layer1.png");
    Texture2D background2 = LoadTexture("layer2.png");
    Texture2D background3 = LoadTexture("layer3.png");
    Texture2D background4l = LoadTexture("layer4l.png");
    Texture2D background4 = LoadTexture("layer4.png");
    Texture2D background5 = LoadTexture("layer5.png");
    Texture2D background6 = LoadTexture("layer6.png");
    Texture2D background7l = LoadTexture("layer7l.png");
    Texture2D background7 = LoadTexture("layer7.png");
    Texture2D background8 = LoadTexture("layer8.png");
    Texture2D background9 = LoadTexture("layer9.png");
    Texture2D obstacleTexture = LoadTexture("obstacle1.png");
    
    Obstacle obstacles[maxObstacles];
    for (int i = 0; i < maxObstacles; i++) {
       if(i%2==0) 
       {           
       obstacles[i].rect = (Rectangle){screenWidth + i * 800, groundYPos + 30, 20, 100};  // Set initial position at the ground level
        obstacles[i].speed = 5.0f;
       }
        else
        {
             obstacles[i].rect = (Rectangle){screenWidth + i * 1600, groundYPos + 60, 20, 80};  // Set initial position at the ground level
        obstacles[i].speed = 8.0f;               
        }   
    }
    
    float backgroundOffset[13] = {0.0f};
    float scales[13] = {0.3f, 0.6f, 0.9f, 1.2f, 1.5f, 1.8f, 2.1f, 2.4f, 2.7f, 3.0f, 0.0f, 0.0f};
    float scale = 0.5f;// scarfy a size
    Vector2 origin = {0.0f, 0.0f};
    Camera2D camera = {0};      
    unsigned numberFrames = 6;
    float framewidth = scarfy.width / numberFrames;
    Rectangle frameRec = {0.0f, 0.0f, (float)framewidth, (float)scarfy.height};
    Vector2 scarfyPosition = {screenWidth / 2.0f, groundYPos - scarfy.height}; // Scarfy ka position ground se adjust
for (int i = 0; i < maxObstacles; i++) {
    obstacles[i].rect.y = groundYPos+140 - obstacles[i].rect.height; // Sab obstacles ground par align
}
Rectangle scarfyRect = { scarfyPosition.x+20, scarfyPosition.y+180, framewidth * scale, scarfy.height * scale };
 // Scarfy ki scaling ke hisaab se adjust
    Vector2 scarfyVelocity = {0.0f, 0.0f};
    camera.target = scarfyPosition;
    camera.offset = (Vector2){screenWidth / 2.0f, screenHeight / 2.0f};
    camera.rotation = 0.0f; //it is for future improvement
    camera.zoom = 1.0f;    
    Font myFont = LoadFont("font.ttf");
    Sound footstepSound = LoadSound("Single-footstep-in-grass-A-www.fesliyanstudios.com.mp3");
    Sound landingSound = LoadSound("Single-footstep-in-grass-B-www.fesliyanstudios.com.mp3");
    Sound clickingSound = LoadSound("Video-Game-Unlock-Sound-A1-8bit-www.fesliyanstudios.com.mp3");
     Sound coinSound = LoadSound("sound.mp3");
    Sound backgroundSound = LoadSound("merx-market-song-33936.mp3");
    unsigned frameDelay = 5;
    unsigned frameDelayCounter = 0;
    unsigned frameIndex = 0;            
    bool gameStarted = false;
    Rectangle startButton = {screenWidth / 2 - 50, screenHeight / 2 - 20, 100, 40};
    bool gameOver = false;
     bool canMove = !gameOver;
    int score = 0;   
    SetTargetFPS(60);
    while (!WindowShouldClose()) {        
         UpdateCoinAnimation();       
        // Update collection
        UpdateCoinCollection(scarfyPosition, scarfyRect,coinSound);                       
        if (!gameStarted) {
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
               PlaySound(clickingSound);                           
                Vector2 mousePosition = GetMousePosition();
                if (CheckCollisionPointRec(mousePosition, startButton)) {
                    gameStarted = true;
                  //  PlaySound(backgroundSound);
                }
            }
        } else {
            if (isScarfyOnGround(&scarfy, &scarfyPosition)) {
                if (IsKeyDown(KEY_SPACE) || IsGamepadButtonDown(0, GAMEPAD_BUTTON_LEFT_FACE_UP)) {
                    scarfyVelocity.y = -2 * scarfySpeed;
                    score=score + 100;
                }
                if(canMove)scarfyVelocity.x = scarfySpeed;
            } else {
                if(canMove)scarfyVelocity.x = scarfySpeed;
            }
                 for (int i = 0; i < maxObstacles; i++) {
                updateObstacle(&obstacles[i]);
            }
            scarfyRect.x = scarfyPosition.x -370; // Scarfy ka horizontal position update karo
            scarfyRect.y = scarfyPosition.y + 180;
            // for checking collision
            for (int i = 0; i < maxObstacles; i++) {
                if (checkCollision(scarfyPosition, scarfyRect, obstacles[i])) {
                   gameOver = true;
                   scarfyVelocity = (Vector2){0.0f, 0.0f}; 
                   canMove = false;
                   ResetCoins();                  
               }
            }
            //for background
            for (int i = 0; i < 13; i++) {
                backgroundOffset[i] += scarfyVelocity.x * scales[i];
                if (backgroundOffset[i] >= background0.width) {
                    backgroundOffset[i] -= background0.width;
                }
            }
            bool scarfyMoving = scarfyVelocity.x != 0.0f || scarfyVelocity.y != 0.0f;
            bool wasScarfyOnGround = isScarfyOnGround(&scarfy, &scarfyPosition);
            scarfyPosition = Vector2Add(scarfyPosition, scarfyVelocity);
            bool scarfyOnGround = isScarfyOnGround(&scarfy, &scarfyPosition);
            if (scarfyOnGround) {
                scarfyVelocity.y = 0;
                scarfyPosition.y = groundYPos - scarfy.height;
                if (!wasScarfyOnGround) PlaySound(landingSound);
            } else {
                scarfyVelocity.y += gravity;
            }
            ++frameDelayCounter;
            if (frameDelayCounter > frameDelay) {
                frameDelayCounter = 0;
                if (scarfyMoving) {
                    if (scarfyOnGround) {
                        ++frameIndex;
                        frameIndex %= numberFrames;
                        if (frameIndex == 1 || frameIndex == 4) PlaySound(footstepSound);
                    } else {
                        if (scarfyVelocity.y < 0) {
                            frameIndex = jumpUpFrame;
                        } else {
                            frameIndex = jumpDownFrame;
                        }
                    }
                    frameRec.x = (float)framewidth * frameIndex;
                }
            }            
        }
        camera.target.x = scarfyPosition.x;
        BeginDrawing();
        ClearBackground(RAYWHITE);           
        if (gameStarted) {
            BeginMode2D(camera);            
            DrawScrollingBackground(background0, backgroundOffset[0], 0.1f);
            DrawScrollingBackground(background1, backgroundOffset[1], 0.2f);
            DrawScrollingBackground(background2, backgroundOffset[2], 0.3f);
            DrawScrollingBackground(background3, backgroundOffset[3], 0.4f);
            DrawScrollingBackground(background4l, backgroundOffset[4], 0.5f);
            DrawScrollingBackground(background4, backgroundOffset[5], 0.6f);
            DrawScrollingBackground(background5, backgroundOffset[6], 0.7f);
            DrawScrollingBackground(background6, backgroundOffset[7], 0.8f);
            DrawScrollingBackground(background7l, backgroundOffset[8], 0.9f);
            DrawScrollingBackground(background7, backgroundOffset[9], 1.0f);
            DrawScrollingBackground(background8, backgroundOffset[10], 0.0f);
            DrawScrollingBackground(background9, backgroundOffset[11], 0.0f);
            DrawCoins();
// DrawRectangleLines(scarfyRect.x, scarfyRect.y, scarfyRect.width-15, scarfyRect.height, DARKGREEN);  // You can change the color
             for (int i = 0; i < maxObstacles; i++) {
    DrawTexture(obstacleTexture, (int)obstacles[i].rect.x, (int)obstacles[i].rect.y, WHITE); // Draw the obstacle
}
            DrawTexturePro(scarfy, frameRec, (Rectangle){scarfyPosition.x-380, scarfyPosition.y + 180, framewidth * scale, scarfy.height * scale}, origin, 0.0f, WHITE);
         EndMode2D();
          DrawText(TextFormat("Score: %d", score), 800, 10, 20, WHITE);
          DrawText(TextFormat("Coins collected: %d", collected), 50, 10, 20, WHITE);            
        }
          if (!gameStarted) {
            DrawTexture(frontbackground, 0, 0, WHITE);
            Rectangle startButton = { screenWidth / 2 - 50, screenHeight / 2 -20, 130, 55 };
            DrawRectangleRec(startButton, GRAY);
            DrawTextEx(myFont,"START", (Vector2){screenWidth / 2 - 30, screenHeight / 2 - 10}, 20,2, BLACK);
            Rectangle logoRect = { screenWidth / 2 - 270, screenHeight / 2 - 110, 600, 65 }; // Adjust position and size
            DrawRectangleRec(logoRect, BLACK);
            DrawTextEx(myFont,"ScarFy The Runner", (Vector2){screenWidth / 2 - 250, screenHeight / 2 - 100},40,2, GREEN);            
          }
          if (gameOver) {
                scarfyVelocity.x = 0; // Stop Scarfy from moving horizontally
            scarfyVelocity.y = 0; // Stop Scarfy from jumping/falling
            for (int i = 0; i < 13; i++) {
                backgroundOffset[i] = backgroundOffset[i]; // Keep background offset static (no scrolling)
            }            
    // Game Over Screen
    DrawTextEx(myFont, "GAME OVER! Press R to restart", (Vector2){screenWidth / 2 - 200, screenHeight / 2 - 20}, 20.0f, 2.0f, RED);
    if (IsKeyPressed(KEY_R) || IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        // Reset game state to try again
        gameOver = false;
        scarfyPosition = (Vector2){screenWidth / 2.0f, groundYPos - scarfy.height}; // Reset Scarfy position
        score = 0; // Reset Score
        collected = 0;
        ResetCoins();
        for (int i = 0; i < maxObstacles; i++) {
            // Reset obstacles positions
            obstacles[i].rect.x = screenWidth + i * 800;
        }           
        canMove = true;
    }
}
        EndDrawing();        
    }
    CloseWindow();
    return 0;
}