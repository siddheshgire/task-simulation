#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

const int BAR_LENGTH = 20;
const int MAX_TASKS = 10;

// Struct to hold individual task data
typedef struct {
  int id;
  int progress;
  int step;
} Task;

void print_bar(Task task);
void clear_screen();

int main() {
  Task tasks[MAX_TASKS];
  srand(time(NULL));

  // Initialization: Assigning random step speeds to simulate varying task loads
  for (int i = 0; i < MAX_TASKS; i++) {
    tasks[i].id = i + 1;
    tasks[i].progress = 0;
    tasks[i].step = rand() % 5 + 1; 
  }

  int tasks_incomplete = 1;
  
  // Main Simulation Loop
  while (tasks_incomplete) {
    tasks_incomplete = 0;
    clear_screen();
    
    printf("\n--- Concurrent Task Simulation ---\n\n");

    for (int i = 0; i < MAX_TASKS; i++) {
      tasks[i].progress += tasks[i].step;
      
      // Cap progress at 100%
      if (tasks[i].progress > 100) {
        tasks[i].progress = 100;
      } else if (tasks[i].progress < 100) {
        tasks_incomplete = 1; // If any task is under 100, keep looping
      }
      
      print_bar(tasks[i]);
    }
    
    sleep(1); // Pause for 1 second to create the animation effect
  }
  
  printf("\n? All tasks completed successfully!\n");
  return 0;
}

// Cross-platform screen clearing
void clear_screen() {
  #ifdef _WIN32
    system("cls");
  #else
    system("clear");
  #endif
}

// Visualizes the progress percentage as a loading bar
void print_bar(Task task) {
  int bars_to_show = (task.progress * BAR_LENGTH) / 100;
  
  // Dynamic formatting for neat alignment
  if(task.id < 10) {
      printf("Task %d:  [", task.id);
  } else {
      printf("Task %d: [", task.id);
  }
  
  for (int i = 0; i < BAR_LENGTH; i++) {
    if (i < bars_to_show) {
      printf("=");
    } else {
      printf(" ");
    }
  }
  printf("] %3d%%\n", task.progress);
}