// one large fie with n lines tatolly. output m lines randomly.

class LuckyBox{
	private int red, white;
	private static Random random = new Random();
	
	public LuckyBox(int n, int m){
		if (n<m)
			throw new IllegalArgumentException();
		this.red = n, this.white = n-m;
	}
	
	// Hope you will get a red. Try it
	public boolean draw(){
		int iRet = random.nextInt(red+white);
		boolean ret = iRet < red? true:false;
		
		if (ret){
			--red;
		}else{
			--white;
		}
		
		return ret;
	}
}
