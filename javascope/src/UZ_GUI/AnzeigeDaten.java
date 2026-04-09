/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package UZ_GUI;

/**
 *
 * @author Philipp Löhdefink
 */



public class AnzeigeDaten {
    final static int ANZAHL_WERTE_PRO_ANZEIGEDATEN = 20;
    public long status;
    public long[] slowDataContent;
    public int[] slowDataID;
    public float[][] val;
    
    
    AnzeigeDaten(int anzahl_messreihen_pro_tcp_paket)
    {
        status = 0;
        slowDataContent = new long[anzahl_messreihen_pro_tcp_paket];
        slowDataID = new int[anzahl_messreihen_pro_tcp_paket];
        //val = new float[ANZAHL_WERTE_PRO_ANZEIGEDATEN][anzahl_messreihen_pro_tcp_paket];
        val = new float[ANZAHL_WERTE_PRO_ANZEIGEDATEN][];
        for (int i=0; i<ANZAHL_WERTE_PRO_ANZEIGEDATEN; i++)
        {
            val[i] = new float[anzahl_messreihen_pro_tcp_paket];
        }

        
    }
    
    public void printToConsole() {
        System.out.println("Anzeigedaten: ");
        for (int i=0; i<ANZAHL_WERTE_PRO_ANZEIGEDATEN; i++)
        {
            String str = "" + i + ": ";
            for (int j=0; j<val[0].length; j++)
            {
                str = "" + str + val[i][j] + "; ";
            }
            System.out.println(str);
        }
    }
    
}


        
