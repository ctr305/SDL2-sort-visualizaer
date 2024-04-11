//Sorting algorithm visualizer in SDL2

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
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

void renderSelectionSort(std::vector<int> numbers, SDL_Renderer* renderer){
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

      drawState(numbers,renderer,i,j);

      SDL_RenderPresent(renderer);
      SDL_Delay(5);
    }
  }
}

void renderQuickSort(std::vector<int> numbers, SDL_Renderer* renderer){
  auto partition = [&] (std::vector<int>& numbers, int low, int high){
    int pivot = numbers[high];
    int i = low-1;
    for(int j=low; j<high; j++){
      if(numbers[j] < pivot){
        i++;
        std::swap(numbers[i],numbers[j]);
      }
      SDL_SetRenderDrawColor(renderer,0,0,0,255);
      SDL_RenderClear(renderer);
      drawState(numbers,renderer,i,j);
      SDL_RenderPresent(renderer);
      SDL_Delay(5);
    }
    std::swap(numbers[i+1],numbers[high]);
    return i+1;
  };

  auto quicksort = [&] (std::vector<int>& numbers, int low, int high, auto&& quicksort) -> void{
    if(low < high){
      int pi = partition(numbers,low,high);
      quicksort(numbers,low,pi-1,quicksort);
      quicksort(numbers,pi+1,high,quicksort);
    }
  };

  quicksort(numbers,0,numbers.size()-1,quicksort);
}

void renderMergeSort(std::vector<int> numbers,SDL_Renderer* renderer);

void renderBubbleSort(std::vector<int> numbers,SDL_Renderer* renderer);

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
      renderSelectionSort(numbers,renderer);
    }else if(argv[1] == std::string("quick")){
      std::cout << "\nUsing quick sort";
      renderQuickSort(numbers,renderer);
    }else if(argv[1] == std::string("merge")){
      std::cout << "\nUsing mergesort";
      //renderMergeSort(numbers,renderer);
    }else if(argv[1] == std::string("bubble")){
      std::cout << "\nUsing bubble sort";
      //renderBubbleSort(numbers,renderer);
    }
  }else{
    renderSelectionSort(numbers,renderer);
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
