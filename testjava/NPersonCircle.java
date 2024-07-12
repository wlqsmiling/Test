/*
 * @Date: 2024-07-12 10:26:28
 * @LastEditors: liqunwu wlqsmiling@gmail.com
 * @LastEditTime: 2024-07-12 10:27:35
 * @FilePath: \Test\testjava\NPersonCircle.java
 */
package testjava;

public class NPersonCircle {
    public static void func() {
        int[] arr = { 1, 2, 3, 4, 5, 6, 7 };

        int leftPeople = arr.length;
        int i = 0;
        int nowNum = 1;
        while (leftPeople > 1) {
            i = i % arr.length;
            if (arr[i] != 0) {
                if (nowNum == 3) {
                    leftPeople--;
                    nowNum = 1;
                    arr[i] = 0;
                } else {
                    nowNum++;
                }
                
                i++;
            } else {
                i++;
                continue;
            }
        }

        for(int j = 0; j < arr.length; j++) {
            if(arr[j] != 0) {
                System.out.println(arr[j]);
            }
        }

        System.out.println("hello world!");
    }
}
