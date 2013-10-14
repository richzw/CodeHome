/*
某序列只有四种字符：( , ) , [ , ] （即圆括号 和 方括号） 
( )，[ ] 是合法的序列，合法序列之间的串接和嵌套也是合法的，比如（[ ()()[][] ]） 是合法的 
现在给定一个序列，请问最少添加多少个符号，才能使之成为合法序列。 
比如： ( ]() ) 只需要添加一个符号  
*/

//in: input parentheses like: 
//"([(])([)])" 
//"([)])" 
//"([(])" 
//index: current insert parenthese 
//buff: result buff, only ( and [ are kept inside 
int GetInsertNumber(string &par, int index, string buff) 
{ 
     //if parentheses are used up, buff.length() right parentheses are needed to fit the left parentheses in buff 
     //this is the end of recursive calls 
     if(index >=(int) par.length()){ 
         return buff.length(); 
     } 
  
     char insert = par[index]; 
     if(insert=='(' || insert=='['){ 
         //insert ( & [ is ok 
         buff.append(1,insert); 
         return GetInsertNumber(par,1+index,buff); 
     }else if(!buff.empty() && ( buff.back()=='(' && insert==')' || buff.back()=='[' && insert==']')){ 
         //if insert fits buff.top() 
         buff.pop_back(); 
         return GetInsertNumber(par,1+index,buff); 
     }else{ 
         //insert doesn't fit buff.top(), one parenthese should be inserted 
         int left=INT_MAX,right=INT_MAX; 
         //1: try to insert one which fits insert char, the result is skip this insert char 
         right = 1 + GetInsertNumber(par,1+index,buff); 
         //2: try to insert one which fits buff.top(), the result is pop the buff 
         if(!buff.empty()){ 
             buff.pop_back(); 
             left = 1 + GetInsertNumber(par,index,buff); 
         } 
  
         return left<=right?left:right; 
     } 
}
