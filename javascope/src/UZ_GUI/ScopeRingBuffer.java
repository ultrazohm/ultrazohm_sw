/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
package UZ_GUI;

/**
 *
 * @author LoehdefinkPh
 */
public class ScopeRingBuffer {

    private double[][] ringBuffer;
    private int writeIndex;
    private int channelCount;
    private int samplesPerChannel;

    public ScopeRingBuffer(int channelCount, int samplesPerChannel) {

        writeIndex = 0;
        this.channelCount = channelCount;
        this.samplesPerChannel = samplesPerChannel;

        ringBuffer = new double[channelCount][];
        for (int channelIndex = 0; channelIndex < channelCount; channelIndex++)
        {
            ringBuffer[channelIndex] = new double[samplesPerChannel];
        }
        for (int channelIndex = 0; channelIndex < channelCount; channelIndex++)
        {
            for (int sampleIndex = 0; sampleIndex < samplesPerChannel; sampleIndex++)
            {
                ringBuffer[channelIndex][sampleIndex] = 0.0;
            }
        }
    }
    
    public void deleteAllChannels()
    {
        writeIndex = 0;
        for (int channelIndex = 0; channelIndex < channelCount; channelIndex++)
        {
            for (int sampleIndex = 0; sampleIndex < samplesPerChannel; sampleIndex++)
            {
                ringBuffer[channelIndex][sampleIndex] = 0.0;
            }
        }
    }
    
    public int addValues(double[] newValues)
    {
        int result = -1;
        if (newValues.length != channelCount)
        {
            System.out.println("------>> ScopeRingBuffer: Wrong number of new values added! ---------------------- ");
        }
        else
        {
            for (int channelIndex = 0; channelIndex < channelCount; channelIndex++)
            {
                ringBuffer[channelIndex][writeIndex] = newValues[channelIndex];
            }
            writeIndex++;
            if (writeIndex >= samplesPerChannel) {
                writeIndex = 0;
            }
            result = 0;
        }
        return result;
    }
    
    public int getNextWritePtr()
    {
        return writeIndex;
    }

    public int snapshotWritePtr()
    {
        return writeIndex;
    }

    public int getSizePerChannel()
    {
        return samplesPerChannel;
    }
    
    public double[] readRawArrayValuesPerChannel(int channelIndex)
    {
        // read array from 0 to end, not considering actual writeIndex position.
        return ringBuffer[channelIndex];
    }
    
    public double getValueAt(int channelIndex, int logicalIndex, int writeIndexSnapshot)
    {
        int bufferIndex = writeIndexSnapshot + logicalIndex;
        if (bufferIndex >= samplesPerChannel) {
            bufferIndex -= samplesPerChannel;
        }
        return ringBuffer[channelIndex][bufferIndex];
    }

}
