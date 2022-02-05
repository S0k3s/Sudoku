#include<iostream>
#include<time.h>
#include<algorithm>
using namespace std;
// ¹²³⁴⁵⁶⁷⁸⁹

void print(int boardFunc[][9], int numLock[][9]) { // printing 81 numbers in a 3x3x3 pattern

   cout << "\033c";

   for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
         if (boardFunc[j][i] == 0){
            cout << "[  ]";
         }
         else {
            if (numLock[j][i] == 0) {
               cout << "[" << boardFunc[j][i] << " ]";
            }
            else {cout << "[" << boardFunc[j][i] << ".]";}
         }

         if (j == 2 || j == 5) {
            cout << "    ";
         }
      }
      cout << endl << endl;
      if (i == 2 || i == 5) {
         cout << endl;
      }
   }

}

void shuffle(int place[]) { // shuffleing numbers around in the array
   int temp = 0;  // temporary number
   int random = 0;   // random number

   for (int i = 0; i < 9; i++){
      random = rand() % 9; // getting unique random number every loop
      temp = place[i]; 
      place[i] = place[random];  // swaping current selected array value with chosen random array value
      place[random] = temp;      
   }
}

int main() {
   srand(time(NULL));
   int yCor, xCor, digit;
   int place [9] = {1, 2, 3, 4, 5, 6, 7, 8, 9}; // initializing numbers from 1 - 9
   bool completion = false;

   shuffle(place); // getting a random order those numbers

   // Declaring placeholder letters and their values
   int a = place[0],b = place[1],c = place[2],d = place[3],e = place[4],f = place[5],g = place[6],h = place[7],k = place[8]; 
   int board [9][9] = { // setting up board shape
      {d, c, e, b, f, k, g, h, a},
      {f, h, b, e, g, a, d, k, c},
      {a, k, g, h, c, d, e, f, b},
      {h, b, f, a, k, e, c, d, g},
      {c, g, d, f, h, b, k, a, e},
      {k, e, a, g, d, c, f, b, h},
      {e, a, k, c, b, f, h, g, d},
      {b, d, h, k, e, g, a, c, f},
      {g, f, c, d, a, h, b, e, k},
   };

   for (int i = 0; i < 1 ; i++) { // normally take away 45 numbers
      for (; ;) {
         int randomX = rand() % 9;
         int randomY = rand() % 9;
         if (board [randomX][randomY] != 0) {
            board [randomX][randomY] = 0;
            break;
         }
      }
   }

   int boardArchive [9][9];
   for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
         boardArchive[j][i] = board[j][i]; // Used to make the original numbers non-changeble
      }
   }

   print(board, boardArchive); // print start board

   while (completion == false) { 
      cout << "Enter x coordinate:"; // input what x coordinate
      cin >> xCor;
      cout << "Enter y coordinate:"; // input what y coordinate
      cin >> yCor;
      cout << "Enter value:"; // input what value
      cin >> digit;

      if ((0 < xCor && xCor < 10) && (0 < yCor && yCor < 10) && (0 < digit && digit < 10)) { // making sure all input values are valid
         int xBoxCor;
         int yBoxCor;
         int error = 0;

         if (boardArchive[xCor - 1][yCor - 1] == 0) {
            for (int i = 0; i < 9; i++) {
               if (board[xCor - 1][i] == digit) { // Checking if value is used in selected colum
                  cout << "Number already used in this collum" << endl; // Collum allert
                  error = 1;
               }
            }
            for (int i = 0; i < 9; i++) {
               if (board[i][yCor - 1] == digit) { // Checking if value is used in selected row
                  cout << "Number already used in this row" << endl; // Row allert
                  error = 2;
               }
            }

            // Checking which box the value belongs to 
            if (xCor < 4) {xBoxCor = 0;} 
            else if (xCor > 6) {xBoxCor = 6;} 
            else {xBoxCor = 3;} 

            if (yCor < 4) {yBoxCor = 0;} 
            else if (yCor > 6) {yBoxCor = 6;}
            else {yBoxCor = 3;}

            for (int i = 0; i < 3; i++) { // seeing if the value is taken in that box
               for (int j = 0; j < 3; j++) {
                  if (board[xBoxCor][yBoxCor] == digit) {error = 3;}
                  yBoxCor++;
               }
               xBoxCor++;
            }
            if (error == 3) {
               cout << "Number allready used in this box" << endl;
            }
            if (error == 0) {
               board [xCor - 1][yCor - 1] = digit; // print the adjusted board
               print(board, boardArchive);
            }
         }
         else {
            cout << "You can't change a permanent number" << endl;
         }
      }
      else {
         cout << "Try that one again jimbo" << endl; // Invalid input allert
      }

      bool l = false; // if 0 is in the board
      for (int i = 0; i < 9 && l == false; i++) { // checking if board is completly full
         for (int j = 0; j < 9 && l == false; j++) {
            if (board [j][i] == 0) {
               l = true;
            }
         }
      }
      if (l == false) {
         completion = true;
         cout << endl << endl << "Congratulations";
      }
   
   }
   return 0;
}