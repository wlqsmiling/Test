/*
 * @Date: 2024-04-10 15:01:38
 * @LastEditors: liqunwu wlqsmiling@gmail.com
 * @LastEditTime: 2024-04-17 16:51:07
 * @FilePath: \Test\testjava\hello.java
 */

package testjava;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.Iterator;

// 程序25 题目：一个5位数，判断它是不是回文数
public abstract class Hello {
    public static void main(String[] args) {
        Scanner input = new Scanner(System.in);
        int n = input.nextInt();
        boolean[] arr = new boolean[n];
        for (int i = 0; i < arr.length; i++) {
            arr[i] = true;
        }
        int leftCount = n;
        int index = 0;
        int countNum = 0;
        while (leftCount > 1) {
            if (arr[index] == true) {
                countNum++;
                if (countNum == 3) {
                    arr[index] = false;
                    leftCount--;
                    countNum = 0;
                }
            }
            index++;
            if (index == n) {
                index = 0;
            }
        }
        for (int i = 0; i < n; i++) {
            if (arr[i] == true) {
                System.out.println(i + 1);
            }
        }
    }
}