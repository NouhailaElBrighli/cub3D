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
