/*
 * This Java source file was generated by the Gradle 'init' task.
 */
package Lab3;

import java.util.ArrayList;
import java.util.LinkedList;

public class App {
    public String getGreeting() {
        return "Hello world.";
    }

    public static void main(String[] args) {
        ListTester testArr = new ListTester(new ArrayList());
        ListTester testLink = new ListTester(new LinkedList());


        System.out.println(testArr.testAdd(100));
        System.out.println(testLink.testAdd(100));
    }
}
