/*
 * @Date: 2024-04-10 15:01:38
 * @LastEditors: liqunwu wlqsmiling@gmail.com
 * @LastEditTime: 2024-07-12 10:21:18
 * @FilePath: \Test\testjava\hello.java
 */

package testjava;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashSet;
import java.util.LinkedList;
import java.util.List;
import java.util.Scanner;
import java.util.Set;
import java.util.Vector;
import java.util.Iterator;

// 有n个人围成一圈，顺序排号。从第一个人开始报数（从1到3报数），凡报到3的人退出圈子，问最后留下的是原来第几号的那位。

public abstract class Hello {
    public static void main(String[] args) {
        NPersonCircle.func();
    }
}