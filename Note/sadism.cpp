#include <iostream> 
 class R2I { 
     const static int DIG; 
 public: 
     constexpr static char IN [] = "MMMDCCXCIV"; //Input goes here 
     const static int OUT; 
 }; 
 //// 
 template <char C> struct ID {}; 
 template <> struct ID <'I'> {static const int I = 0; static const int V = 1;}; 
 template <> struct ID <'V'> {static const int I = 1; static const int V = 5;}; 
 template <> struct ID <'X'> {static const int I = 2; static const int V = 10;}; 
 template <> struct ID <'L'> {static const int I = 3; static const int V = 50;}; 
 template <> struct ID <'C'> {static const int I = 4; static const int V = 100;}; 
 template <> struct ID <'D'> {static const int I = 5; static const int V = 500;}; 
 template <> struct ID <'M'> {static const int I = 6; static const int V = 1000;}; 
 template <bool A, bool B, int I0, int I1> 
 struct DiffHelper{ static const int D = 9;}; 
 template<int I0, int I1> 
 struct DiffHelper <true, true, I0, I1>{ 
      static const int VAL0 = ID<R2I::IN[I0]>::I; 
      static const int VAL1 = ID<R2I::IN[I1]>::I; 
      static const int D = (VAL0 -  VAL1 <= -3) ? -3 : (( VAL0 -  VAL1 >= 1) ? 1 : (VAL0 -  VAL1)); 
 }; 
 template <int I0, int I1> struct Diff {static const int D = DiffHelper<(I0 < sizeof(R2I::IN) - 1), (I1 < sizeof(R2I::IN) - 1), I0, I1>::D;}; 
 //// 
 template <int N, int C, int P> struct R2IHelper {const static int DIG = -4000;}; 
 template <int P, int N>    struct R2IHelper<N, 9, P>  {const static int DIG = ID<R2I::IN[P]>::V;}; 
 template <int P>    struct R2IHelper<9, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V * 4/5 + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I) % 2, Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<9, 9, P>    {const static int DIG = ID<R2I::IN[P]>::V * 4/5;}; 
 template <int P>    struct R2IHelper<6, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I) % 2, Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<6, 0, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<2, Diff<P+1, P+2>::D, P+1>::DIG;}; 
 template <int P>    struct R2IHelper<4, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V * 3/5 + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I + 1) % 2, Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<4, 9, P>    {const static int DIG = ID<R2I::IN[P]>::V * 3/5;}; 
 template <int P>    struct R2IHelper<3, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I) % 2 , Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<2, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I) % 2 , Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<2, 0, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<3, Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<1, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I==1)*6 + (ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I + 1) % 2, Diff<P+1, P+2>::D, P+1>::DIG;}; 
 template <int P>    struct R2IHelper<0, 1, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<(ID<R2I::IN[P]>::I - ID<R2I::IN[P+1]>::I) % 2 , Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<0, 0, P>    {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<2, Diff<P+1, P+2>::D, P+1>::DIG; }; 
 template <int P>    struct R2IHelper<0, -1, P>   {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<4, Diff<P, P+2>::D, P+1>::DIG;};  
 template <int P>    struct R2IHelper<0, -2, P>   {const static int DIG = ID<R2I::IN[P]>::V + R2IHelper<9, Diff<P, P+2>::D, P+1>::DIG;}; 
 //// 
 const int R2I::DIG = R2IHelper<ID<R2I::IN[0]>::I % 2 , Diff<0, 1>::D, 0>::DIG; 
 const int R2I::OUT = DIG > 0 ? DIG : 0; 
 using namespace std; 
   
 int main() 
 { 
     char carr[R2I::OUT]; 
     cout<<sizeof(carr)<<endl; 
 }	
