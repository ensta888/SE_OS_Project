/**
 * Helpers for manipulating strings.
 */
#define MAXARGS 10

/* Split the string 'string' into an array argtab of strings, 
   using the space delimiter
   @param string the string to split
   @param argtab the array of splits. 
   Must be initialized before call to a size big enough to get the result of splitting.
   Last element of argtab must be NULL, to indicate the end of split
   @return the number of elements in argtab.
*/
int str_split(char * string, char * argtab[]);


/* 
   Check if string 'str' starts with 'prefix'
   @param prefix the prefix string
   @param str the string to check against prefix
   @return 1 if string str starts with string prefix, 0 if not, -1 if strings
   are null.
*/
int startswith(char *prefix, char*str);
