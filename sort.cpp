//Sorting algorithm visualizer in SDL2

#include <SDL2/SDL.h>
#include <iostream>
#include <random>

int main(){

  std::random_device r;
  std::uniform_int_distribution<> n(1,99);
  std::vector<int> numbers;

  for(int i=0; i<100; i++){
    numbers.push_back(n(r));
  }

  SDL_Window* window = nullptr;
  SDL_Renderer* renderer = nullptr;
  SDL_CreateWindowAndRenderer(
                              100*10, 100*10, 0,
                              &window,&renderer);
  SDL_RenderSetScale(renderer,10,10);

  //sorting algorithm

  std::cout << "Original vector: ";

  for(int i=0; i<numbers.size(); i++){
    std::cout << numbers[i] << " ";
    for(int j=0; j<numbers.size(); j++){
      if(numbers[i] < numbers[j]){
        int aux1, aux2;
        aux1 = numbers[i];
        aux2 = numbers[j];
        numbers[i] = aux2;
        numbers[j] = aux1;
      }
    }
  }

  std::cout << "\nSorted vector: ";

  for(int i=0; i<numbers.size(); i++){
    std::cout << numbers[i] << " ";
  }

  std::cout << "\n";

  return 0;
}
