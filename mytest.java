public class assignemnt{
    public static void main(String[] args){
        System.out.println(new A().a2().length);
    }
}

class A{
    
    public int a2(){
        int a1;
        int a2;
        a1 = 1;
        a2 = 2;
        if (a1 < a2){
            a1 = 3 * this.a2();
            a1 = 3 * a2;
        }
        else{
            a1 = 4;
        }
        return a1;
    }
}