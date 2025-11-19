/* Tower of Hanoi: Moving n discs from sour via aux to dest.
*/
#include <stdio.h>

void hanoi(int n, char sour, char aux, char dest) {
  static int step = 1;
  if (n > 0) {
    hanoi(n-1, sour, dest, aux);
    printf("Step %d: Move disk %d from '%c' to '%c' \n", step++, n, sour, dest);
    hanoi(n-1, aux, sour, dest);
  }
}

int main(void) {
  int k;
  
  do {
    printf("Please enter the number of disks: ");
    scanf("%d",&k); // Enter a number k.
  } while (k<1 || k>12);

  printf("\n");  
  hanoi(k, 'A', 'B', 'C');
  printf("\nFinish!!!\n\n");
  
  system("pause");
  return 0;
}


