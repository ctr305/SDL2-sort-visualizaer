//Sorting algorithm visualizer in SDL2

#include <SDL2/SDL.h>
#include <iostream>
#include <random>
#include <string_view>

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

void selectionSort(std::vector<int> numbers, SDL_Renderer* renderer){
  for(int i=0; i<numbers.size(); i++){
    for(int j=0; j<numbers.size(); j++){
      if(numbers[i] > numbers[j]){
        int aux;
        aux = numbers[i];
        numbers[i] = numbers[j];
        numbers[j] = aux;
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

void quickSort(std::vector<int> numbers,SDL_Renderer* renderer);

void mergeSort(std::vector<int> numbers,SDL_Renderer* renderer);

void bubbleSort(std::vector<int> numbers,SDL_Renderer* renderer);

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

  if(argc == 2){
    if(argv[1] == std::string("selection")){
      std::cout << "\nUsing selection sort";
      selectionSort(numbers,renderer);
    }else if(argv[1] == std::string("quick")){
      std::cout << "\nUsing quick sort";
      //quickSort(numbers,renderer);
    }else if(argv[1] == std::string("merge")){
      std::cout << "\nUsing mergesort";
    }else if(argv[1] == std::string("bubble")){
      std::cout << "\nUsing bubble sort";
      //bubbleSort(numbers,renderer);
    }
  }else{
    selectionSort(numbers,renderer);
  }

  //Pause screen to observe sorted vector
  SDL_Delay(1000);

  /*
   * std::cout << "\n\nSorted vector: ";
   * for(int i=0; i<numbers.size(); i++){
   * std::cout << numbers[i] << " ";
   * }
   */

  std::cout << "\n";

  return 0;
}
