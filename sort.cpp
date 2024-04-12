//Sorting algorithm visualizer in SDL2

#include <SDL2/SDL.h>
#include <SDL2/SDL_render.h>
#include <SDL2/SDL_timer.h>
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

void finalState(std::vector<int>& numbers, SDL_Renderer* r){
  SDL_SetRenderDrawColor(r,0,0,0,255);
  SDL_RenderClear(r);
  drawState(numbers,r,-1,-1);
  for (int i = 0; i < numbers.size(); i++) {
    SDL_SetRenderDrawColor(r,0,0,255,255);
    SDL_RenderDrawLine(r,i,99,i,numbers[i]);
    SDL_RenderPresent(r);
    SDL_Delay(5);
    SDL_SetRenderDrawColor(r,255,255,255,255);
    SDL_RenderDrawLine(r,i,99,i,numbers[i]);
  }
  SDL_Delay(5000);
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
  finalState(numbers,renderer);
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
  finalState(numbers,renderer);
}

void renderMergeSort(std::vector<int> numbers,SDL_Renderer* renderer){
  auto merge = [&] (std::vector<int>& numbers, int left, int mid, int right, SDL_Renderer* renderer){
    int n1 = mid - left + 1;
    int n2 = right - mid;

    std::vector<int> L,R;

    for(int i=0; i<n1; i++){
      L.push_back(numbers[left+i]);
    }
    for(int j=0; j<n2; j++){
      R.push_back(numbers[mid+1+j]);
    }

    int i=0, j=0, k=left;
    
    while (i < n1 && j < n2) {
      if (L[i] <= R[j]) {
        numbers[k] = L[i];
        i++;
      } else {
        numbers[k] = R[j];
        j++;
      }
      SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
      SDL_RenderClear(renderer);
      drawState(numbers, renderer, i, j);
      SDL_RenderPresent(renderer);
      SDL_Delay(5);
      k++;
    }

    while (i < n1) {
      numbers[k] = L[i];
      i++;
      k++;
    }

    while (j < n2) {
      numbers[k] = R[j];
      j++;
      k++;
    }
  };
  
  auto mergesort = [&] (std::vector<int>& numbers, int left, int right, SDL_Renderer* renderer, auto&& merge, auto&& mergesort) -> void{
    if(left < right){
      int mid = left + (right - left) / 2;
      mergesort(numbers,left,mid,renderer,merge,mergesort);
      mergesort(numbers,mid+1,right,renderer,merge,mergesort);
      merge(numbers,left,mid,right,renderer);
    }
  };

  mergesort(numbers,0,numbers.size()-1,renderer,merge,mergesort);
  finalState(numbers,renderer);
}

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

  if(argc == 2){
    if(argv[1] == std::string("selection")){
      std::cout << "\nUsing selection sort";
      renderSelectionSort(numbers,renderer);
    }else if(argv[1] == std::string("quick")){
      std::cout << "\nUsing quick sort";
      renderQuickSort(numbers,renderer);
    }else if(argv[1] == std::string("merge")){
      std::cout << "\nUsing mergesort";
      renderMergeSort(numbers,renderer);
    }else if(argv[1] == std::string("bubble")){
      std::cout << "\nUsing bubble sort";
      //renderBubbleSort(numbers,renderer);
    }else if(argv[1] == std::string("suite")){
      std::cout << "\nUsing suite of sorting algorithms";
      renderSelectionSort(numbers,renderer);
      renderQuickSort(numbers,renderer);
      renderMergeSort(numbers,renderer);
  }else{
    renderSelectionSort(numbers,renderer);
  }

  std::cout << "\n";;

  }else{
    renderSelectionSort(numbers,renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return 0;
}
