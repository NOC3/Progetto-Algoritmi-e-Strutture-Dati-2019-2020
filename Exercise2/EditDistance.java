public class EditDistance {
    /*recursive edit distance (non-memoization)*/
    public static int edit_distance(String s1, String s2){
        if(s1.length()==0){
            return s2.length();
        }else if(s2.length()==0){   
            return s1.length();
        }else{
            if(s1.charAt(0)==s2.charAt(0)){
                return edit_distance(s1.substring(1), s2.substring(1));
            } else {
                return 1+java.lang.Math.min(edit_distance(s1.substring(1), s2), edit_distance(s1, s2.substring(1)) ); 
            }
        }
    }

    /*wrapper edit_distance_dyn & initialization matrix used for memoization*/
    public static int edit_distance_dyn(String s1, String s2){
        int x =s1.length(); 
        int y = s2.length();
        int [][] m=new int[x][y];
        for(int i =0; i<x; i++){
            for(int j=0; j<y;j++)
                m[i][j]=-1;
        }
        return edit_distance_dyn(s1, s2, m, x, y);
    }

    /*recursive edit distance (memoization)*/
    private static int edit_distance_dyn(String s1, String s2, int[][] m, int x, int y){
        if(x==0)
            return y;
            
        if(y==0)
            return x;
        
        if(m[x-1][y-1]!=-1)
            return m[x-1][y-1];
        
        if(s1.charAt(x-1)==s2.charAt(y-1))
            return m[x-1][y-1] = edit_distance_dyn(s1, s2,m, x-1, y-1);

        return m[x-1][y-1]=1+java.lang.Math.min(edit_distance_dyn(s1, s2, m, x-1, y), edit_distance_dyn(s1, s2,m , x, y-1));//min(insert,canc)
    }                
}
