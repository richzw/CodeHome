/*
 Q: Write an efficient function that deletes characters from an ASCII string. Use the prototype
    		string removeChars( string str, string remove );
    where any character existing in remove must be deleted from str. For example,
	given a str of "Battle of the Vowels: Hawaii vs. Grozny" and a remove of
	"aeiou", the function should transform str to “Bttl f th Vwls: Hwl vs. Grzny”.
*/

 /*
  * @func: remove chars from source string
  * @params: psource{char*}, the source string
  *          premove{char*}, the remove chars
  * @return: {char*}, the header of new string.
  */
 char* removeChars(char* psource, char* premove){

     // put the remove chars into harsh-table
     char ascii_array[128] = {0};
     while(*premove != '\0')
             ascii_array[*premove++] = 1;

     // remove chars from source string,
     // through two pointers, in-place removing chars
     char* pnew = psource; // the new pointer to removed string
     char* pold = psource;

     while (*pold != '\0'){
         if (ascii_array[*pold] != 1){
             *pnew++ = *pold;
         }
         ++pold;
     }
     *(++pnew) = '\0';

     return psource;
 }


 int main(){
     char ch_arr[] = "Battle of the Vowels: Hawaii";
     char rem_arr[] = "aeiou";

     char* p = removeChars(ch_arr, rem_arr);
     cout << p << endl;

     return 0;
 }


