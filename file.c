#include <stdio.h>
#include <stdlib.h>

int main ( )  {
// radius 
const int RAD = 10;

// tolerance 
const int TOL = 5;

for(int x = -RAD; x <= RAD; x++)
{

  for(int y = -RAD; y <= RAD; y++)
  {

    int eq = x*x + y*y - RAD * RAD;

    printf(abs(eq) < TOL ? "*" : " ");

  }

  printf("\r\n");

}

return 0;

}

// #include <iostream> 
// #include<math.h> 
// using namespace std; 
// int main()
// { 
//     float n,j,i,p; 
//     cout<<"enter n \n"; 
//     cin>>n;n=n+3; 
//     p=floor((4*n-2.5)/5.8); 
//     for(j=p;j>=-p;j--){ 
//     for(i=-n;i<=n;i++){ 
//     if(p*p*i*i+n*n*j*j<=n*n*p*p) 
//     cout<<"*"; 
//     else{cout<<" ";} 
// } 
// cout<<endl;} 
// return 0;} 


// https://www.geeksforgeeks.org/draw-circle-without-floating-point-arithmetic-unpublished/

void drawCircle(int r) // code with cpp !!!!!!
{
    // Consider a rectangle of size N*N
    int N = 2*r+1;
 
    int x, y;  // Coordinates inside the rectangle
 
    // Draw a square of size N*N.
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // Start from the left most corner point
            x = i-r;
            y = j-r;
 
            // If this point is inside the circle, print it
            if (x*x + y*y <= r*r+1 )
                printf(".");
            else // If outside the circle, print space
                printf(" ");
            printf(" ");
        }
        printf("\n");
    }
}

// Driver Program to test above function
int  main()
{
    drawCircle(8);
    return 0;
}
