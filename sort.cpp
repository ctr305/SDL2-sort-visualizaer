//Sorting algorithm visualizer in SDL2

#include <SDL2/SDL.h>
#include <iostream>
#include <random>

void drawState(std::vector<int>& numbers, SDL_Renderer* r, int red, int blue){
  int index=0;
  for(int i : numbers){
    if(index == red){
      SDL_SetRenderDrawColor(r,255,0,0,255);
    }else if(index == blue){
      SDL_SetRenderDrawColor(r,0,0,255,255);
    }else{
      SDL_SetRenderDrawColor(r,255,255,255,0);
    }
    SDL_RenderDrawLine(r,index,99,index,i);
    index++;
  }
}

void simpleSort(std::vector<int> numbers, SDL_Renderer* renderer){
  std::cout << "Original vector: ";

  for(int i=0; i<numbers.size(); i++){
    std::cout << numbers[i] << " ";
    for(int j=0; j<numbers.size(); j++){
      if(numbers[i] > numbers[j]){
        int aux1, aux2;
        aux1 = numbers[i];
        aux2 = numbers[j];
        numbers[i] = aux2;
        numbers[j] = aux1;
      }
      //Clear screen
      SDL_SetRenderDrawColor(renderer,0,0,0,255);
      SDL_RenderClear(renderer);

      //Draw state
      drawState(numbers,renderer,i,j);

      SDL_RenderPresent(renderer);
      SDL_Delay(5);
    }
  }
}

int main(int argc, char *argv[]){

  std::random_device r;
  std::uniform_int_distribution<> n(1,99);
  std::vector<int> numbers;

  for(int i=0; i<100; i++){
    numbers.push_back(n(r));
  }

  SDL_Window* window;
  SDL_Renderer* renderer;
  SDL_CreateWindowAndRenderer(
                              100*10, 100*10, 0,
                              &window,&renderer);
  SDL_RenderSetScale(renderer,10,10);

  //sorting algorithm

  if(argv[1] == "simple"){
    simpleSort(numbers,renderer);
  }else{
    simpleSort(numbers,renderer);
  }

  std::cout << "\nSorted vector: ";

  for(int i=0; i<numbers.size(); i++){
    std::cout << numbers[i] << " ";
  }

  std::cout << "\n";

  return 0;
}
