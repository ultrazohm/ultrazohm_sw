/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package UZ_GUI;

/**
 *
 * @author Michael Hoerner
 */
public class MovingAverage {
     
    
    private float [] window;
    private int n, insert;
    private float sum;

    public MovingAverage(int size) {
        window = new float[size];
        insert = 0;
        sum = 0;
    }
    
    public float next(float val) {
        if (n < window.length)  n++;
        sum -= window[insert];
        sum += val;
        window[insert] = val;
        insert = (insert + 1) % window.length;
        return (float)sum / n;
    }
}
