// On linux compile with:
// g++ -std=c++17 main.cpp -o prog -lSDL2 -lSDL2_image -ldl
//g++ -std=c++17 TexturedRectangle.cpp main.cpp -o prog -lSDL2 -lSDL2_image -ldl -lSDL2_ttf
// C++ Standard Libraries
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <filesystem>
#include <map>
#include <iterator>
#include <random>
namespace fs = std::filesystem;
// Third Party
#include <SDL2/SDL.h> // For Mac, use <SDL.h>
#include <SDL2/SDL_ttf.h>
#include "TexturedRectangle.hpp"

#define WINDOW_WIDTH 1280
#define WINDOW_HEIGHT 960
#define CARD_WIDTH 250/1.5
#define CARD_HEIGHT 363/1.5
#define BUTTON_WIDTH 350
#define BUTTON_HEIGHT 100
#define BUTTON_ONE_POS_X WINDOW_WIDTH - BUTTON_WIDTH;
#define BUTTON_ONE_POS_Y WINDOW_HEIGHT - BUTTON_HEIGHT;
std::map<std::string, std::string> allCards { 
    {"2c", "2_of_clubs"}, {"2d", "2_of_diamonds"}, {"2h", "2_of_hearts"},{"2s", "2_of_spades"},
    {"3c", "3_of_clubs"}, {"3d", "3_of_diamonds"}, {"3h", "3_of_hearts"},{"3s", "3_of_spades"},
    {"4c", "4_of_clubs"}, {"4d", "4_of_diamonds"}, {"4h", "4_of_hearts"},{"4s", "4_of_spades"},
    {"5c", "5_of_clubs"}, {"5d", "5_of_diamonds"}, {"5h", "5_of_hearts"},{"5s", "5_of_spades"},
    {"6c", "6_of_clubs"}, {"6d", "6_of_diamonds"}, {"6h", "6_of_hearts"},{"6s", "6_of_spades"},
    {"7c", "7_of_clubs"}, {"7d", "7_of_diamonds"}, {"7h", "7_of_hearts"},{"7s", "7_of_spades"},
    {"8c", "8_of_clubs"}, {"8d", "8_of_diamonds"}, {"8h", "8_of_hearts"},{"8s", "8_of_spades"},
    {"9c", "9_of_clubs"}, {"9d", "9_of_diamonds"}, {"9h", "9_of_hearts"},{"9s", "9_of_spades"},
    {"10c", "10_of_clubs"}, {"10d", "10_of_diamonds"}, {"10h", "10_of_hearts"},{"10s", "10_of_spades"},
    {"jc", "jack_of_clubs"}, {"jd", "jack_of_diamonds"}, {"jh", "jack_of_hearts"},{"js", "jack_of_spades"},
    {"qc", "queen_of_clubs"}, {"qd", "queen_of_diamonds"}, {"qh", "queen_of_hearts"},{"qs", "queen_of_spades"},
    {"kc", "king_of_clubs"}, {"kd", "king_of_diamonds"}, {"kh", "king_of_hearts"},{"ks", "king_of_spades"},
    {"ac", "ace_of_clubs"}, {"ad", "ace_of_diamonds"}, {"ah", "ace_of_hearts"},{"as", "ace_of_spades"}
    };


SDL_Rect createRect(int x, int y, int w, int h){
    SDL_Rect Message_rect;
    Message_rect.x = x; //controls the rect's x coordinate 
    Message_rect.y = y; // controls the rect's y coordinte
    Message_rect.w = w; // controls the width of the rect
    Message_rect.h = h; // controls the height of the rect
    return Message_rect;
}

void addMessageTexture(std::vector<std::pair<SDL_Rect, SDL_Texture*>> &Messages, std::string stringMsg, SDL_Renderer* renderer, int x, int y, int w, int h){
    TTF_Font* Sans = TTF_OpenFont("Sans.ttf", 100);
    SDL_Color White = {255, 255, 255};

    SDL_Surface* surfaceMessage = TTF_RenderText_Solid(Sans, stringMsg.c_str(), White); 
    SDL_Texture* Message = SDL_CreateTextureFromSurface(renderer, surfaceMessage);
    SDL_Rect Message_rect = createRect(x,y,w,h);
    Messages.push_back ( std::make_pair(Message_rect,Message) );

}


int main(int argc, char* argv[]){
    // Create a window data type
    // This pointer will point to the 
    // window that is allocated from SDL_CreateWindow
    SDL_Window* window=nullptr;

    // Initialize the video subsystem.
    // iF it returns less than 1, then an
    // error code will be received.
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        std::cout << "SDL could not be initialized: " <<
                  SDL_GetError();
    }else{
        std::cout << "SDL video system is ready to go\n";
    }
    // Request a window to be created for our platform
    // The parameters are for the title, x and y position,
    // and the width and height of the window.
    window = SDL_CreateWindow("Blackjack Basic Strategy",20, 20, WINDOW_WIDTH,WINDOW_HEIGHT,SDL_WINDOW_SHOWN);

    SDL_Renderer* renderer = nullptr;
    renderer = SDL_CreateRenderer(window,-1,SDL_RENDERER_ACCELERATED);

    std::vector<std::shared_ptr<TexturedRectangle>> dealerCards;
    std::shared_ptr<TexturedRectangle> dealerCard = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/2_of_clubs.bmp");
    dealerCards.push_back(dealerCard);
    dealerCard = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/misc_cards/card_back.bmp");
    dealerCards.push_back(dealerCard);

    std::vector<std::shared_ptr<TexturedRectangle>> playerCards;
    std::shared_ptr<TexturedRectangle> playerCard = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/2_of_clubs.bmp");
    playerCards.push_back(playerCard);
    playerCard = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/2_of_clubs.bmp");
    playerCards.push_back(playerCard);

    /*std::string path = "./images/bmp-cards";
    std::string s;
    for (const auto & entry : fs::directory_iterator(path)){

        std::cout << entry.path() << "is regular file: " << entry.is_regular_file() << std::endl;
        
        std::cout << s << std::endl;
    }*/

    std::map<std::string, std::shared_ptr<TexturedRectangle>> cardTextures;
    std::shared_ptr<TexturedRectangle> cardTexture;
    for (auto& [key, value]: allCards) {
        cardTexture = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/" + value + ".bmp");
        cardTextures.insert ( std::pair<std::string,std::shared_ptr<TexturedRectangle>>(key,cardTexture) );
        std::cout << key << " has value " << value << std::endl;
}


    /*std::vector<std::shared_ptr<TexturedRectangle>> playerOptions;
    std::shared_ptr<TexturedRectangle> playerCard = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/2_of_clubs.bmp");
    playerCards.push_back(playerCard);
    playerCard = std::make_shared<TexturedRectangle>(renderer,"./images/bmp-cards/2_of_clubs.bmp");
    playerCards.push_back(playerCard);*/
    
    for(int i=0; i < dealerCards.size(); i++){
        dealerCards[i]->SetRectangleProperties(WINDOW_WIDTH/2 - CARD_WIDTH/2 + i*50,30 + i * 40,CARD_WIDTH,CARD_HEIGHT);
    }
    for(int i=0; i < playerCards.size(); i++){
        playerCards[i]->SetRectangleProperties(WINDOW_WIDTH/2 - CARD_WIDTH/2 + i*50, WINDOW_HEIGHT - CARD_HEIGHT,CARD_WIDTH,CARD_HEIGHT);
    }

    //SPLITS
    //Split the pair
    //Split if DAS is offered
    //Don't split

    //SOFT TOTALS
    //Hit
    //Stand
    //Double if allowed, or hit
    //Double if allowed, or stand

    //HARD TOTALS
    //Hit
    //Stand
    //Double if allowed, or hit


    TTF_Init();
    std::vector<std::pair<SDL_Rect, SDL_Texture*>> Messages;

    addMessageTexture(Messages, "HIT", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - 40, WINDOW_HEIGHT - BUTTON_HEIGHT + BUTTON_HEIGHT/2 - 40,80,80);
    addMessageTexture(Messages, "STAND", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - 60, WINDOW_HEIGHT - BUTTON_HEIGHT*2 + BUTTON_HEIGHT/2 - 40,120,80);
    addMessageTexture(Messages, "DOUBLE IF ALLOWED, OR HIT", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT - BUTTON_HEIGHT*3 + BUTTON_HEIGHT/2 - 25, BUTTON_WIDTH, 50);
    addMessageTexture(Messages, "DOUBLE IF ALLOWED, OR STAND", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT - BUTTON_HEIGHT*4 + BUTTON_HEIGHT/2 - 25, BUTTON_WIDTH, 50);


    addMessageTexture(Messages, "SPLIT PAIR", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - 90, WINDOW_HEIGHT - BUTTON_HEIGHT + BUTTON_HEIGHT/2 - 40,180,80);
    addMessageTexture(Messages, "SPLIT IF DAS IS OFFERED", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT - BUTTON_HEIGHT*2 + BUTTON_HEIGHT/2 - 25,BUTTON_WIDTH,50);
    addMessageTexture(Messages, "DON'T SPLIT", renderer, WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - 70, WINDOW_HEIGHT - BUTTON_HEIGHT*3 + BUTTON_HEIGHT/2 - 25, 150, 50);

   /* SDL_Surface* surfaceMessage2 = TTF_RenderText_Solid(Sans, "STAND", White); 
    SDL_Texture* Message2 = SDL_CreateTextureFromSurface(renderer, surfaceMessage2);
    SDL_Rect Message_rect2 = createRect(WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - 60, WINDOW_HEIGHT - BUTTON_HEIGHT*2 + BUTTON_HEIGHT/2 - 40,120,80);
    Messages.push_back ( std::make_pair(Message_rect2,Message2) );

    SDL_Surface* surfaceMessage3 = TTF_RenderText_Solid(Sans, "DOUBLE IF ALLOWED, OR HIT", White); 
    SDL_Texture* Message3 = SDL_CreateTextureFromSurface(renderer, surfaceMessage3);
    SDL_Rect Message_rect3 = createRect(WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT - BUTTON_HEIGHT*3 + BUTTON_HEIGHT/2 - 25, BUTTON_WIDTH, 50);
    Messages.push_back ( std::make_pair(Message_rect3,Message3) );*/

    /*SDL_Surface* surfaceMessage4 = TTF_RenderText_Solid(Sans, "DOUBLE IF ALLOWED, OR STAND", White); 
    SDL_Texture* Message4 = SDL_CreateTextureFromSurface(renderer, surfaceMessage4);
    SDL_Rect Message_rect4 = createRect(WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - BUTTON_WIDTH/2, WINDOW_HEIGHT - BUTTON_HEIGHT*4 + BUTTON_HEIGHT/2 - 25, BUTTON_WIDTH, 50);
    Messages.push_back ( std::make_pair(Message_rect4,Message4) );*/


    //Message_rect.x = WINDOW_WIDTH - BUTTON_WIDTH + BUTTON_WIDTH/2 - 25; //controls the rect's x coordinate 
    //Message_rect.y = WINDOW_HEIGHT - BUTTON_HEIGHT + BUTTON_HEIGHT/2 - 25; // controls the rect's y coordinte
    //Message_rect.w = 50; // controls the width of the rect
    //Message_rect.h = 50; // controls the height of the rect



    // Create a rectangle
    SDL_Rect rectangle;
    rectangle.x = WINDOW_WIDTH - BUTTON_WIDTH;
    rectangle.y = WINDOW_HEIGHT - BUTTON_HEIGHT;
    rectangle.w = BUTTON_WIDTH;
    rectangle.h = BUTTON_HEIGHT;

    SDL_Rect rectangle2;
    rectangle2.x = WINDOW_WIDTH - BUTTON_WIDTH;
    rectangle2.y = WINDOW_HEIGHT - BUTTON_HEIGHT*2;
    rectangle2.w = BUTTON_WIDTH;
    rectangle2.h = BUTTON_HEIGHT;

    SDL_Rect rectangle3;
    rectangle3.x = WINDOW_WIDTH - BUTTON_WIDTH;
    rectangle3.y = WINDOW_HEIGHT - BUTTON_HEIGHT*3;
    rectangle3.w = BUTTON_WIDTH;
    rectangle3.h = BUTTON_HEIGHT;

    SDL_Rect rectangle4;
    rectangle4.x = WINDOW_WIDTH - BUTTON_WIDTH;
    rectangle4.y = WINDOW_HEIGHT - BUTTON_HEIGHT*4;
    rectangle4.w = BUTTON_WIDTH;
    rectangle4.h = BUTTON_HEIGHT;
    // Infinite loop for our application
    bool gameIsRunning = true;

    bool colorRectangle = false;
    bool colorRectangle2 = false;
    bool colorRectangle3 = false;
    bool colorRectangle4 = false;

    std::map<std::string, std::shared_ptr<TexturedRectangle>>::iterator item = cardTextures.begin();
    std::vector<std::pair<std::string, std::shared_ptr<TexturedRectangle>>> erasedCards;
    std::vector<std::shared_ptr<TexturedRectangle>>::iterator dealerCardFirstPos;
    std::vector<std::string> cardsOnTable;

    //what table do we need to use?
    //pairs, softs or hards?
    std::vector<int> cardValues;
    bool useSplitTable = false;
    bool useSoftTable = false;
    bool useHardTable = false;
    // Main application loop
    while(gameIsRunning){
        SDL_Event event;

        // (1) Handle Input
        // Start our event loop
        while(SDL_PollEvent(&event)){
            // Handle each specific event
            if(event.type == SDL_QUIT){
                gameIsRunning= false;
            }
            if(event.type == SDL_MOUSEMOTION){
                //std::cout << "mouse has been moved\n";
                //std::cout << "mouse moved x: " << event.button.x;

                //choice boxes
                if( (event.button.x > rectangle.x) && (event.button.x < (rectangle.x + rectangle.w)) &&
                    (event.button.y > rectangle.y) && (event.button.y < (rectangle.y + rectangle.h))){
                    colorRectangle = true;
                }else{
                    colorRectangle = false;
                }
                if( (event.button.x > rectangle2.x) && (event.button.x < (rectangle2.x + rectangle2.w)) &&
                    (event.button.y > rectangle2.y) && (event.button.y < (rectangle2.y + rectangle2.h))){
                    colorRectangle2 = true;
                }else{
                    colorRectangle2 = false;
                }
                if( (event.button.x > rectangle3.x) && (event.button.x < (rectangle3.x + rectangle3.w)) &&
                    (event.button.y > rectangle3.y) && (event.button.y < (rectangle3.y + rectangle3.h))){
                    colorRectangle3 = true;
                }else{
                    colorRectangle3 = false;
                }
                if( (event.button.x > rectangle4.x) && (event.button.x < (rectangle4.x + rectangle4.w)) &&
                    (event.button.y > rectangle4.y) && (event.button.y < (rectangle4.y + rectangle4.h))){
                    colorRectangle4 = true;
                }else{
                    colorRectangle4 = false;
                }
            }
            if(event.type == SDL_MOUSEBUTTONDOWN){
                //std::cout << "mouse has been clicked\n";
                if(event.button.button == SDL_BUTTON_LEFT){
                    playerCards.clear();
                    cardsOnTable.clear();
                    cardValues.clear();
                    useSoftTable = false;
                    useSplitTable = false;
                    useHardTable = false;

                    for( int i = 0; i<2; i++){
                        item = cardTextures.begin();
                        std::advance( item, rand() % cardTextures.size());
                        item->second->SetRectangleProperties(WINDOW_WIDTH/2 - CARD_WIDTH/2 + i*50, WINDOW_HEIGHT - CARD_HEIGHT,CARD_WIDTH,CARD_HEIGHT);
                        playerCards.push_back(item->second);
                        erasedCards.push_back(std::make_pair(item->first, item->second));
                        cardTextures.erase(item->first);
                        //std::cout << "item->first: " << item->first << "\n";
                        cardsOnTable.push_back(item->first);
                    }

                    item = cardTextures.begin();
                    std::advance( item, rand() % cardTextures.size());
                    item->second->SetRectangleProperties(WINDOW_WIDTH/2 - CARD_WIDTH/2 ,30,CARD_WIDTH,CARD_HEIGHT);
                    dealerCards[0] = item->second;
                    cardsOnTable.push_back(item->first);
                    for(auto& erasedCard: erasedCards){
                        cardTextures.insert(erasedCard);
                    }
                    for(auto& cardOnTable: cardsOnTable){
                        std::cout << "Cards on table: " << cardOnTable << std::endl;
                    }


                    //convert card strings to values
                    for(auto& cardOnTable: cardsOnTable){
                        cardOnTable.resize(1);
                        if(cardOnTable == "k" || cardOnTable == "q" || cardOnTable == "j" || cardOnTable == "1"){
                            cardValues.push_back(10);
                        }else if(cardOnTable == "a"){
                            cardValues.push_back(0);
                        }else{
                            cardValues.push_back(stoi(cardOnTable));
                        }
                    }

                    //choosing which tables to use
                    if(cardsOnTable[0] == cardsOnTable[1]){
                        useSplitTable = true;
                        std::cout << "split table\n";
                    }else if(cardValues[0] == 0 || cardValues[1] == 0){
                        useSoftTable = true;
                        std::cout << "soft table\n";
                    }else{
                        useHardTable = true;
                        std::cout << "hard table\n";
                    }
                    std::cout << "first card val: " << cardValues[0] << " second card val: " << cardValues[1] << std::endl;
                    std::cout << "mouse left been clicked\n";
            }
            }
        }
        // (2) Handle Updates
        

        
        
        // (3) Clear and Draw the Screen
        // Gives us a clear "canvas"
        SDL_SetRenderDrawColor(renderer,6,69,52,SDL_ALPHA_OPAQUE);
        SDL_RenderClear(renderer);

        // Do our drawing
        SDL_SetRenderDrawColor(renderer,1,40,27,SDL_ALPHA_OPAQUE);
        if(colorRectangle == true){
            SDL_RenderFillRect(renderer,&rectangle);
        }
        if(colorRectangle2 == true){
            SDL_RenderFillRect(renderer,&rectangle2);
        }
        if(colorRectangle3 == true){
            SDL_RenderFillRect(renderer,&rectangle3);
        }
        SDL_RenderDrawRect(renderer,&rectangle);
        SDL_RenderDrawRect(renderer,&rectangle2);
        SDL_RenderDrawRect(renderer,&rectangle3);
        if(useSoftTable == true){
            if(colorRectangle4 == true){
                SDL_RenderFillRect(renderer,&rectangle4);
            }
            SDL_RenderDrawRect(renderer,&rectangle4);
        }
        
        int i = 0;
        for(auto& elem: Messages){
            i++;
            if(useSplitTable && i < 5)continue;
            if(useHardTable && i > 3)break;
            if(useSoftTable && i > 4)break;

            SDL_RenderCopy(renderer, elem.second, NULL, &elem.first);
        }

        for(auto& rect: dealerCards){
            rect->Render(renderer);
        }

        

        for(auto& rect: playerCards){
            rect->Render(renderer);
        }

        // Finally show what we've drawn
        SDL_RenderPresent(renderer);

    }

    // We destroy our window. We are passing in the pointer
    // that points to the memory allocated by the 
    // 'SDL_CreateWindow' function. Remember, this is
    // a 'C-style' API, we don't have destructors.
    SDL_DestroyWindow(window);
    
    // our program.
    SDL_Quit();
    return 0;
}
