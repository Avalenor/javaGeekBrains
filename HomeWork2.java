package HomeWorkApp;

public class HomeWork2 {
    public static void main(String[] args) {
        System.out.println(method1(5,10));
        method4("gfgf", 5);
        System.out.println(method5(2000));

    }
    //задача1
    public static boolean method1(int a, int b) {
        int s =a+b;
        if (s>=10 && s<=20){
           return(true);
        }else{
            return(false);
        }
    }
    //задача2
    public static void method2(int a){
        if (a>=0){
            System.out.println("положительное");
        }else{
            System.out.println("отрицательное");
        }
    }
    //задача3
    public static boolean method3(int a){
        if (a>=0) {
            return(false);
        }else{
            return(true);
        }
    }
    //задача4
    public static void method4(String a, int b){
        int i = 0;
        while (i<b){
            i++;
            System.out.println(a);
        }
    }
    //задача5*
    public static boolean method5(int a){
      if (a%4==0 && (a%100!=0 || a%400==0)){
          return (true);
      }else{
          return (false);
      }
    }

}
