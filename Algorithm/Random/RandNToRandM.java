/*
第1步，getRandom1To5()等概率随机产生：1,2,3,4,5；
第2步，getRandom1To5()-1等概率随机产生：0,1,2,3,4；
第3步，(getRandom1To5()-1)*5等概率随机产生：0,5,10,15,20；
第4步，(getRandom1To5()-1)*5+(getRandom1To5()-1)等概率随机产生：0,1,2,3,…,23,24。
         注意这两个getRandom1To5()是指独立的两次调用，请不要化简。这是”插空儿”过程；
第5步，如果第4步产生的结果大于20，则重复进行第4步，直到产生的结果在0~20之间。
      同时可以轻易知道出现21~24的概率，会平均分配到0~20上。这是”筛”过程；
第6步，因为第5步的结果是等概率随机的产生0~20，所以第5步的结果再%7，就会等概率的随机产生0~6；
第7步，第6步的结果+1，就会等概率的随机产生1~7
过程结束。具体请参看如下代码中的getRandom1To7方法：
*/ 
     public static int getRandom1To5() {
         return (int) (Math.random() * 5) + 1;// 1,2,3,4,5
     }
  
     public static int getRandom1To7() {
         int num = 0;
         do {
             num = (getRandom1To5() - 1) * 5 + getRandom1To5() - 1;// 0,1,2,3,...,23,24
         } while (num > 20);
         return num % 7 + 1;
     }
/*进阶1：
虽然getRandom01P方法以p的概率产生0，以1-p的概率产生1，但是getRandom01P产生01和10的概率却都是p*(1-p)，
 可以利用这一点来实现等概率随机产生0和1的函数：
*/ 
     public static int getRandom01P() {
         // you can change p to what you like, but it must be (0,1)
         double p = 0.83;
         return Math.random() < p ? 0 : 1;
     }
  
     public static int getRandom01() {
         int randomNum;
         do {
             randomNum = getRandom01P();
         } while (randomNum == getRandom01P());
         return randomNum == 1 ? 1 : 0;
     }
/*     
第1步，实现等概率随机产生0和1的函数(如上代码中的getRandom01方法)；
第2步，getRandom01()*2，等概率随机产生：0,2
第3步，getRandom01()*2+getRandom01()，等概率随机产生：0,1,2,3。注意这两个getRandom01()是指独立的两次调用，
       请不要化简；这是”插空儿”过程；
第3步说明我们已经可以实现等概率随机产生0~3的函数，具体请参看如下代码中的getRandom0To3方法：
*/  
     public static int getRandom0To3() {
         return getRandom01() * 2 + getRandom01();
     }
/*     
  第4步，getRandom0To3()*4+getRandom0To3()，等概率随机产生：0,1,2,…,14,15。注意这两个getRandom0To3()是指独立的两次调用，
   请不要化简；这是”插空儿”过程；
第5步，如果第4步产生的结果大于11，则重复进行第4步，直到产生的结果在0~11之间；同时可以轻易知道出现12~15的概率，
   会平均分配到0~11上。这是”筛”过程；
第6步，因为第5步的结果是等概率随机的产生0~11，所以第5步的结果再%6，就会等概率的随机产生0~5；
第7步，第6步的结果+1，就会等概率的随机产生1~6；
过程结束。进阶解法的全部代码请参看如下代码中的getRandom1To6方法：
*/  
     public static int getRandom01P() {
         // you can change p to what you like, but it must be (0,1)
         double p = 0.83;
         return Math.random() < p ? 0 : 1;
     }
  
     public static int getRandom01() {
         int randomNum;
         do {
             randomNum = getRandom01P();
         } while (randomNum == getRandom01P());
         return randomNum == 1 ? 1 : 0;
     }
  
     public static int getRandom0To3() {
         return getRandom01() * 2 + getRandom01();
     }
  
     public static int getRandom1To6() {
         int num = 0;
         do {
             num = getRandom0To3() * 4 + getRandom0To3();// 0,1,2,3,..,13,14,15
         } while (num > 11);
         return num % 6 + 1;
     } 
