#include <stdio.h>
#include <string.h>

/*
** int memcmp(const void *str1, const void *str2, size_t n);
**
** str1 -- 指向内存块的指针。 
** str2 -- 指向内存块的指针。
** n -- 要被比较的字节数。
**
** 如果返回值 < 0，则表示 str1 小于 str2。
** 如果返回值 > 0，则表示 str1 大于 str2。
** 如果返回值 = 0，则表示 str1 等于 str2。
**
*/

int main ()
{
   char str1[15];
   char str2[15];
   char str3[15];
   char str4[15];
   int ret;

   memcpy(str1, "abcdef", 6);
   memcpy(str2, "ABCDEF", 6);
   memcpy(str3, "ABCDE", 5);
   memcpy(str4, "abcdef", 6);

   // ret = memcmp(str1, str2, 5); // str2 小于 str1
//    ret = memcmp(str2, str3, 5);    // str2 等于 str3

   ret = memcmp(str1, str4, strlen("abcdef"));

   if(ret > 0)
   {
      printf("str2 小于 str1\r\n");
   }
   else if(ret < 0)
   {
      printf("str1 小于 str2\r\n");
   }
   else
   {
      printf("str1 等于 str2\r\n");
   }
   
   return(0);
}