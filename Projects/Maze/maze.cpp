#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// main function to read, solve maze, and print result
int main() {
   int rows, cols, result;
   char** mymaze;

   mymaze = read_maze(&rows, &cols); // FILL THIS IN
   
   if (mymaze == NULL) {
      cout << "Error, input format incorrect" << endl;
      return 1;
   }

   // when working on Checkpoint 3, you will call maze_search here.
   // here. but for Checkpoint 1, just assume we found the path.
   result = 1; // TO BE CHANGED

   result = maze_search(mymaze, rows, cols);

   // examine value returned by maze_search and print appropriate output
   if (result == 1) { // path found!
      print_maze(mymaze, rows, cols);
   }
   else if (result == 0) { // no path :(
      cout << "No path could be found!" << endl;
   }
   else { // result == -1
      cout << "Invalid maze." << endl;
   }

   // ADD CODE HERE to delete all memory 
   // that read_maze allocated
   for (int i = 0; i < rows; i++) {
      delete mymaze[i];
   }
   delete mymaze;

   return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 * -1 if invalid maze (not exactly one S and one F)
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 *************************************************/
int maze_search(char** maze, int rows, int cols) {
   Location start;
   bool start_found = false;
   bool finish_found = false;
   for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
         if (maze[i][j] == 'S') {
            if (start_found) {
               cout << "More than one Start found" << endl;
               return -1;
            }
            start.row = i;
            start.col = j;
            start_found = true;
         }
         if (maze[i][j] == 'F') {
            if (finish_found) {
               cout << "More than one Finish found" << endl;
               return -1;
            }
            finish_found = true;
         }
      }
   }
   if (!start_found || !finish_found) {
      return -1;
   }

   bool** visited = new bool*[rows];
   for (int i = 0; i < rows; i++) {
      visited[i] = new bool[cols];
      for (int j = 0; j < cols; j++) {
         visited[i][j] = false;
      }
   }

   Location** predecessor = new Location*[rows];
   for (int i = 0; i < rows; i++) {
      predecessor[i] = new Location[cols];
      for (int j = 0; j < cols; j++) {
         predecessor[i][j].row = -1;
         predecessor[i][j].col = -1;
      }
   }

   Queue q(rows * cols);
   q.add_to_back(start);
   finish_found = false;
   Location loc;
   while (!q.is_empty() && !finish_found) {
      loc = q.remove_from_front();
      visited[loc.row][loc.col] = true;
      for (int i = 0; i < 4 && !finish_found; i++) {
         Location neighbor = loc;
         if (i == 0) {
            neighbor.row += 1;
         } else if (i == 1) {
            neighbor.row -= 1;
         } else if (i == 2) {
            neighbor.col += 1;
         } else {
            neighbor.col -= 1;
         }
         if (neighbor.row < 0 || neighbor.row >= rows || 
            neighbor.col < 0 || neighbor.col >= cols) {
            continue;
         }
         if (maze[neighbor.row][neighbor.col] == 'F') {
            finish_found = true;
         } else if (!visited[neighbor.row][neighbor.col] &&
                    maze[neighbor.row][neighbor.col] == '.') {
            q.add_to_back(neighbor);
            predecessor[neighbor.row][neighbor.col] = loc;
         }
      }
   }
   if (finish_found) {
      while (loc.row != start.row || loc.col != start.col) {
         maze[loc.row][loc.col] = '*';
         loc =predecessor[loc.row][loc.col];
      }
   }

   for (int i = 0; i < rows; i++) {
      delete[] visited[i];
      delete[] predecessor[i];
   }
   delete[] visited;
   delete[] predecessor;

   if (finish_found) {
      return 1;
   } else {
      return 0;
   }
}
