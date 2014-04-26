int Rand3()
{
    int x;
    do
    {
        x = Rand5();
    } while (x >= 3);
    return x;
}

int Rand7()
{
    int x = 0;
    do{
      x = Rand5()*5 + Rand5();
    }while(x >= 21);
    
    return x%7;
}
