 
//方法一。
/***********************************************************************************
 *从字符串的后面开始扫描,把结果保存到result中。当往result中加入新的字符时，
 *它与result中已存在的每一个字符组合成新的字符加入到result中。
***********************************************************************************/
typedef vector<string>strVector; 
void doCombine(const string&original, strVector &result_container, unsigned offset) { 
 
    if (offset >= original.size()) 
         return; 
 
    doCombine(original, result_container, offset+1); 
 
    const unsigned nCount = result_container.size(); 
 
    result_container.push_back(string(1, original[offset])); 
 
    for (unsigned index = 0; index < nCount; ++index) { 
         string temp(1, original[offset]); 
        temp.append(result_container[index]); 
         result_container.push_back(temp);  
   } 
}
 
void combine(const char *szStr){ 
    const string original(szStr); 
    vector<string> container; 
 
    if (!original.size()) 
         return; 
 
    doCombine(original, container, 0); 
 
    for (unsigned index = 0; index < container.size(); ++index) { 
               cout<< container[index].c_str() <<endl; 
    }
} 
 
 
//方法二。
/************************************************************************************ 
 *从字符串的前面开始扫描，取出第一个字符，与剩余的字符相组合。
 *然后回溯之。如'abc',-->'a', 'ab', 'abc', 'abcd', 'abd', 'ac'.....
************************************************************************************/
void str_doCombine(const string&original, string &result, unsigned offset) { 
 
         const unsigned nLength = original.size();  
 
         if (offset >= nLength)
                return; 
 
         for (unsigned index = offset; index <nLength; ++index) { 
                result.append(1, original[index]); 
                cout << result.c_str() <<endl; 
                str_doCombine(original, result, index +1); 
                result.resize(result.size() - 1);     //backtrace
         } 
}
 
void str_combine(const char *szStr){ 
         string original(szStr); 
         string result; 
 
         if (!original.size())
                return; 
 
         str_doCombine(original, result, 0); 
} 
