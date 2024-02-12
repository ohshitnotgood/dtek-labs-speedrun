#include <stdio.h>

char *text1 = "This is a string.";
char *text2 = "Yet another thing.";

// list1: 	.space 80
// list2: 	.space 80
// count:	.word  0
int list1[80];
int list2[80];
int count = 0;

void printlist(const int *lst)
{
  printf("ASCII codes and corresponding characters.\n");
  while (*lst != 0)
  {
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char *c)
{
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c, (int)*(c + 1), (int)*(c + 2), (int)*(c + 3));
}

void copycodes(char *text, int *list, int *count)
{
  // copycodes:
  // loop:
  // 	lb	$t0,0($a0)
  // 	beq	$t0,$0,done
  while (*text != 0)
  {
    // 	sw	$t0,0($a1)
    *list = *text;
    // 	addi	$a0,$a0,1
    text += 1;
    // 	addi	$a1,$a1,4
    list += 1; //Only increase by 1, as C automatically points to the next element in the array, instead of manually having to skip 4 bytes

    // 	lw	$t1,0($a2)
    // 	addi	$t1,$t1,1
    // 	sw	$t1,0($a2)
    *count += 1;
  }
}

void work()
{
  // la 	$a0,text1
  // la	$a1,list1
  // la	$a2,count
  // jal	copycodes
  copycodes(text1, list1, &count);

  // la 	$a0,text2
  // la	$a1,list2
  // la	$a2,count
  // jal	copycodes
  copycodes(text2, list2, &count);
}

int main(void)
{
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char *)&count); //little endian: least significant byte first
}
