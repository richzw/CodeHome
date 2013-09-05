/*
Q: 给定一个字符串，仅由a,b,c 3种小写字母组成。当出现连续两个不同的字母时，你可以用另外一个字母替换它，如
有ab或ba连续出现，你把它们替换为字母c；
有ac或ca连续出现时，你可以把它们替换为字母b；
有bc或cb 连续出现时，你可以把它们替换为字母a。
你可以不断反复按照这个规则进行替换，你的目标是使得最终结果所得到的字符串尽可能短，求最终结果的最短长度。

输入：字符串。长度不超过200，仅由abc三种小写字母组成。
输出： 按照上述规则不断消除替换，所得到的字符串最短的长度。
例如：输入cab，输出2。因为我们可以把它变为bb或者变为cc。
输入bcab，输出1。尽管我们可以把它变为aab -> ac -> b，也可以把它变为bbb，但因为前者长度更短，所以输出1。
*/

/*
个人思路: “abc” 等效 "bcbc";
因此我猜想将整个字符串中的a替换为bc、得到一个只有bc组成的字符串 A！再对 A 进行分解、我发现最后结果非1即2.
当 A.length() % 2 == 0 && (A中包含的“b”的个数 % 2 == 0) 为true时。其最终消除结果为2.否则为1！
*/

public static int minLength( String s ) {
    int len = s.length();
    if ( s.indexOf( "a" )+s.indexOf( "b" )+s.indexOf( "c" ) == -2 ) 
        return len;
    String temp = "";
    //判断字符串是否包含a、并将其替换为bc
    if ( s.indexOf( "a" ) > -1 ){
        temp = s.replaceAll( "a" , "bc" );
        len = temp.length();
    }
    int bLen = temp.replaceAll( "b" , "" ).trim().length();
    if (len % 2 == 0 && bLen % 2 == 0) return 2;
    else return 1;
}
