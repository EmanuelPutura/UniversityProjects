package sdi.web;

public class Main {
    public static void main(String[] args) {
        while(true) {
            System.out.println("Hello world!");
            try {
                Thread.sleep(1000);
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
    }
}
