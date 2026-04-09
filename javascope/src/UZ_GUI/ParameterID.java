/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package UZ_GUI;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Paint;
import java.awt.event.ActionEvent;
import java.awt.Dimension;
import java.io.FileWriter;
import java.io.IOException;
import java.text.Format;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.Properties;
import javax.swing.JOptionPane;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.axis.NumberAxis;
import org.jfree.chart.axis.NumberTickUnit;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.title.PaintScaleLegend;
import org.jfree.data.Range;
import org.jfree.data.xy.DefaultXYZDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;
import org.jfree.chart.renderer.xy.XYLineAndShapeRenderer;
import java.awt.Rectangle;
import org.jfree.chart.ChartFactory;
import org.jfree.chart.JFreeChart;
import org.jfree.chart.axis.AxisLocation;
import org.jfree.chart.renderer.LookupPaintScale;
import org.jfree.chart.renderer.xy.XYBlockRenderer;
import org.jfree.chart.ui.RectangleEdge;

/**
 *
 * @author hufnagelde
 */
public class ParameterID extends ReceiveController
{
    private UZ_SCOPE_view viewSCOPE;
    private UZ_ParaID_view viewParaID;
    private Transmitter transmitter;
    private FileWriter dataWriter;
    private ReceiveController recvCont;
    private ChartPanel FluxChPanel1;
    private ChartPanel FluxChPanel2;
    private JFreeChart FluxChart1;
    private JFreeChart FluxChart2;
    private ChartPanel FrictionID_ChPanel;
    private ChartPanel chPanel;
    private SendController sendCont;
    
    private int n_max;
    private int N_Visco;
    public float ViscoFriction;
    public float CoulTorque;
    public float BreakTorque;
    public float ActiveState;
    public float Wtemp;
    double[][]TMID_Speed_spectrum;
    double[][]TMID_Torque_spectrum;
    double[][]TMID_Transfer_fc;
    public float FluxTempConst;
    public float FluxTempError;
    public double FluxTempSum [];
    public double FluxTempCount [];
    public double psi_array [];
    public int MapCount;
    public float psid_grid;
    public float psiq_grid;
    public float psi_arr;
    public float FluxTemp;
    public double [] psid_map;
    public double [] psiq_map;
    public double [] psiq_x;
    public double [] psid_x;
    public double [] psiq_y;
    public double [] psid_y;
    public float LdOnline;
    public float LqOnline;
    public float PsiPMOnline;
    public float RsOnline;
    public double I_rat;
    public int ArrCount;
    public float MeasArraySpeed;
    public float MeasArrayTorque;
    float [][] FrictionID_Array;
    private PaintScaleLegend fluxQLegend;
    private PaintScaleLegend fluxDLegend;
    private long oldStatus;  // Store status value directly (AnzeigeDaten is reused)
    private volatile boolean parameterIdReady = false;
    
    //Get Button Mapping from javascope.h
    ArrayList<String> ButtonNames;
    
    public ParameterID(UZ_GUI_view view, UZ_SCOPE_view viewSCOPE, UZ_ParaID_view viewParaID, Transmitter transmitter, ChartPanel chPanel, int chnum, Properties prop, SendController sendCont, ReceiveController recvCont)
    {
        super(view, viewSCOPE, transmitter, sendCont, chPanel, chnum, prop);
        this.viewSCOPE = viewSCOPE;
        this.viewParaID = viewParaID;
        this.transmitter = transmitter;
        this.sendCont = sendCont;       
        this.recvCont = recvCont;
        this.chPanel = chPanel;
        recvCont.get_chPanel().removeChartMouseListener(chartMouseListener);
        
        FrictionID_Array = new float [2][256];
        psid_map=new double [400];
        psiq_map=new double [400];
        psid_x=new double [400];
        psiq_x=new double [400];
        psid_y=new double [400];
        psiq_y=new double [400];
        I_rat = 8.0;
        FluxTempSum=new double [100];
        FluxTempCount=new double [100];
        ButtonNames = sendCont.ButtonNames;
        slowDataSignalNames = recvCont.slowDataSignalNames;
        viewParaID.getBtn_OID_SaveMaps().addActionListener(this);
        viewParaID.getBtn_Save_FrictionID().addActionListener(this);
        //ParameterID
        viewParaID.getBtnActivate_ElectricalID().addActionListener(this);
        viewParaID.getBtnActivate_FrictionID().addActionListener(this);
        viewParaID.getBtnActivate_TwoMassID().addActionListener(this);
        viewParaID.getBtnActivate_FluxMapID().addActionListener(this);
        viewParaID.getBtnSet_EID_goeAmp().addActionListener(this);
        viewParaID.getBtnSet_EID_SAMPLETIMEISR().addActionListener(this);
        viewParaID.getBtnSet_EID_goeFreq().addActionListener(this);
        viewParaID.getBtnSet_EID_DUTYCYC().addActionListener(this);
        viewParaID.getBtnSet_EID_MAXCURRENT().addActionListener(this);
        viewParaID.getBtnSet_EID_NREFM().addActionListener(this);
        viewParaID.getBtn_EID_IDENTLQ().addActionListener(this);
        viewParaID.getBtn_ParaID_ACCEPT().addActionListener(this);
        viewParaID.getBtn_ParaID_RESET().addActionListener(this);
        viewParaID.getBtn_ParaID_EnSystem().addActionListener(this);
        viewParaID.getBtn_ParaID_EnControl().addActionListener(this);
        viewParaID.getBtn_ParaID_Stop().addActionListener(this);      
        viewParaID.getBtn_EID_AdmitParams().addActionListener(this);
        viewParaID.getBtn_FMID_ToggleAutomatedMeasuring().addActionListener(this);
        viewParaID.getBtnSet_FMID_id_start().addActionListener(this);
        viewParaID.getBtnSet_FMID_id_stop().addActionListener(this);
        viewParaID.getBtnSet_FMID_id_step().addActionListener(this);
        viewParaID.getBtnSet_FMID_iq_start().addActionListener(this);
        viewParaID.getBtnSet_FMID_iq_stop().addActionListener(this);
        viewParaID.getBtnSet_FMID_iq_step().addActionListener(this);
        viewParaID.getBtnSet_FMID_set_ref_R().addActionListener(this);
        viewParaID.getBtnSet_FMID_set_identRamp().addActionListener(this);
        viewParaID.getBtnSet_FMID_set_ref_Winding().addActionListener(this);
        viewParaID.getBtn_FMID_IDENTRSONLINE().addActionListener(this);
        viewParaID.getBtnActivate_ParameterID().addActionListener(this);
        viewParaID.getBtnSet_FID_eta_n().addActionListener(this);
        viewParaID.getBtnSet_FID_Brk_Count().addActionListener(this);
        viewParaID.getBtnSet_FID_s_step().addActionListener(this);
        viewParaID.getBtnSet_FID_N_visco().addActionListener(this);
        viewParaID.getBtnSet_FID_N_Brk().addActionListener(this);
        viewParaID.getBtnSet_FID_max_speed().addActionListener(this);
        viewParaID.getBtn_Save_FrictionID().addActionListener(this);
        viewParaID.getBtnActivate_OnlineID().addActionListener(this);
        viewParaID.getBtnSet_OID_Ref_R1().addActionListener(this);
        viewParaID.getBtnSet_OID_Ref_Temp().addActionListener(this);
        viewParaID.getBtnSet_OID_d_Current_Steps().addActionListener(this);
        viewParaID.getBtnSet_OID_identRangeA().addActionListener(this);
        viewParaID.getBtnSet_OID_identTime().addActionListener(this);
        viewParaID.getBtnSet_OID_max_res_Current().addActionListener(this);
        viewParaID.getBtnSet_OID_maximumSpeed().addActionListener(this);
        viewParaID.getBtnSet_OID_minimumSpeed().addActionListener(this);
        viewParaID.getBtnSet_OID_q_Current_Steps().addActionListener(this);
        viewParaID.getBtnSet_OID_identRAmp().addActionListener(this);
        viewParaID.getBtn_OID_EnableRefControl().addActionListener(this);
        viewParaID.getBtn_OID_OnlineReset().addActionListener(this);
        viewParaID.getBtn_OID_RefreshFlux().addActionListener(this);
        viewParaID.getBtn_OID_SaveMaps().addActionListener(this);
        viewParaID.getBtnSet_TMID_PRBS_Scale().addActionListener(this);
        viewParaID.getBtnSet_TMID_d_TMS_start().addActionListener(this);
        viewParaID.getBtnSet_TMID_f_max().addActionListener(this);
        viewParaID.getBtnSet_TMID_f_min().addActionListener(this);
        viewParaID.getBtnSet_TMID_n_ref().addActionListener(this);
        viewParaID.getBtn_ParaID_CurrentControl().addActionListener(this);
        viewParaID.getBtn_ParaID_SpeedControl().addActionListener(this);
        viewParaID.getBtn_ParaID_Disable_Control().addActionListener(this);
        
        
        //----------------------------Flux Maps-----------------------------------
        //----------------------------Map1----------------------------------------
        double[] zvalues = new double[20*20]; 

        for (int gridRow = 0; gridRow < 20; gridRow++){
            for (int gridColumn = 0; gridColumn < 20; gridColumn++){
                psid_x[gridColumn*20+gridRow]=-3*I_rat+(4*gridColumn*I_rat)/19;
                psiq_x[gridColumn*20+gridRow]=-3*I_rat+(4*gridColumn*I_rat)/19;
                psid_y[gridColumn*20+gridRow]=-3*I_rat+(6*gridRow*I_rat)/19;
                psiq_y[gridColumn*20+gridRow]=-3*I_rat+(6*gridRow*I_rat)/19;
            }        
        } 
        for (int gridRow = 0; gridRow < 20; gridRow++){
            for (int gridColumn = 0; gridColumn < 20; gridColumn++) {
                final int gridIndex = gridColumn*20+gridRow;
                zvalues[gridIndex] =  (gridColumn);
            }
        }   
        
        NumberAxis xAxis = new NumberAxis("Current in d-Axis in A");
        xAxis.setStandardTickUnits(NumberAxis.createStandardTickUnits ());
        xAxis.setTickUnit (new NumberTickUnit(3,recvCont.getNf3(),3));
        Range rangex=new Range(getMinDouble(psid_x)-0.000001,getMaxDouble(psid_x)+0.000001);
        xAxis.setRange(rangex);
        NumberAxis yAxis = new NumberAxis("Current in q-Axis in A");
        yAxis.setStandardTickUnits(NumberAxis.createStandardTickUnits ());
        yAxis.setTickUnit (new NumberTickUnit(4,recvCont.getNf3(),3));
        Range rangey=new Range(getMinDouble(psid_y)-0.000001,getMaxDouble(psid_y)+0.000001);
        yAxis.setRange(rangey);

        // create a paint-scale and a legend showing it
        LookupPaintScale paintScale;
        paintScale = new LookupPaintScale(0, getMaxDouble(zvalues)-getMinDouble(zvalues), (Paint) Color.RED);
        Color legendColor = Color.BLUE;
        paintScale.add(0.0, (Paint) legendColor);
        legendColor = Color.CYAN.darker();   
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.11, (Paint) legendColor);
        legendColor = Color.CYAN;
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.22, (Paint) legendColor);
        legendColor = Color.GREEN;
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.33, (Paint) legendColor);
        legendColor = Color.GREEN.darker();
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.44, (Paint) legendColor);
        legendColor = Color.YELLOW.darker();
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.55, (Paint) legendColor);
        legendColor = Color.ORANGE.darker();
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.66, (Paint) legendColor);
        legendColor = Color.ORANGE;
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.77, (Paint) legendColor);
        legendColor = Color.YELLOW;
        paintScale.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.88, (Paint) legendColor);

        fluxDLegend = new PaintScaleLegend(paintScale, new NumberAxis());
        fluxDLegend.setPosition(RectangleEdge.RIGHT);
        fluxDLegend.setAxisLocation(AxisLocation.TOP_OR_RIGHT);
        fluxDLegend.setBackgroundPaint(null);
        fluxDLegend.getAxis().setTickLabelPaint(Color.black);
    

        DefaultXYZDataset datasetflux = new DefaultXYZDataset();
        datasetflux.addSeries("Just one Series", new double[][] { psid_x, psid_y, zvalues });        
        
        // finally a renderer and a plot
        XYPlot plot = new XYPlot(datasetflux, xAxis, yAxis, new XYBlockRenderer());
        ((XYBlockRenderer)plot.getRenderer()).setPaintScale(paintScale);
        
               
        
        FluxChart1 = new JFreeChart(null, null, plot, false);
        FluxChart1.addSubtitle(fluxDLegend);
        FluxChPanel1 = new ChartPanel(FluxChart1);
        FluxChPanel1.setPreferredSize( new java.awt.Dimension( 500 , 300 ) );
        viewParaID.getPlotFlux().add(FluxChPanel1, "PlotFlux");
        FluxChart1.setBackgroundPaint(null);
        ((XYBlockRenderer) FluxChPanel1.getChart().getXYPlot().getRenderer()).setBlockHeight((getMaxDouble(psid_y)-getMinDouble(psid_y))/22);
        ((XYBlockRenderer) FluxChPanel1.getChart().getXYPlot().getRenderer()).setBlockWidth((getMaxDouble(psid_x)-getMinDouble(psid_x))/22);
        
        
        //----------------------------Map2----------------------------------------
                      
        NumberAxis xAxis2 = new NumberAxis("Current in d-Axis in A");
        xAxis2.setStandardTickUnits(NumberAxis.createStandardTickUnits ());
        xAxis2.setTickUnit (new NumberTickUnit(3,recvCont.getNf3(),3));
        rangex = new Range(getMinDouble(psiq_x)-0.000001,getMaxDouble(psiq_x)+0.000001);
        xAxis2.setRange(rangex);

        NumberAxis yAxis2 = new NumberAxis("Current in q-Axis in A"); 
        yAxis2.setStandardTickUnits(NumberAxis.createStandardTickUnits ());
        yAxis2.setTickUnit (new NumberTickUnit(4,recvCont.getNf3(),3));
        rangey=new Range(getMinDouble(psiq_y)-0.000001,getMaxDouble(psiq_y)+0.000001);
        yAxis2.setRange(rangey);

     
      
        // create a paint-scale and a legend showing it
        LookupPaintScale paintScale2;
        paintScale2 = new LookupPaintScale(0, getMaxDouble(zvalues)-getMinDouble(zvalues), (Paint) Color.RED);
        legendColor = Color.BLUE;
        paintScale2.add(0.0, (Paint) legendColor);
        legendColor = Color.CYAN.darker();
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.11, (Paint) legendColor);
        legendColor = Color.CYAN;
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.22, (Paint) legendColor);
        legendColor = Color.GREEN;
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.33, (Paint) legendColor);
        legendColor = Color.GREEN.darker();
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.44, (Paint) legendColor);
        legendColor = Color.YELLOW.darker();
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.55, (Paint) legendColor);
        legendColor = Color.ORANGE.darker();
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.66, (Paint) legendColor);
        legendColor = Color.ORANGE;
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.77, (Paint) legendColor);
        legendColor = Color.YELLOW;
        paintScale2.add((getMaxDouble(zvalues)-getMinDouble(zvalues))*0.88, (Paint) legendColor);

        fluxQLegend = new PaintScaleLegend(paintScale2, new NumberAxis());
        fluxQLegend.setPosition(RectangleEdge.RIGHT);
        fluxQLegend.setAxisLocation(AxisLocation.TOP_OR_RIGHT);
        fluxQLegend.setBackgroundPaint(null);
        fluxQLegend.getAxis().setTickLabelPaint(Color.black);
        
    

        DefaultXYZDataset datasetflux2 = new DefaultXYZDataset();
        datasetflux2.addSeries("Just one Series", new double[][] { psid_x, psid_y, zvalues });        
     
        // finally a renderer and a plot
        XYPlot plot2 = new XYPlot(datasetflux2, xAxis2, yAxis2, new XYBlockRenderer());
        ((XYBlockRenderer)plot2.getRenderer()).setPaintScale(paintScale2);
              
        FluxChart2 = new JFreeChart(null, null, plot2, false);
        FluxChart2.addSubtitle(fluxQLegend);
        FluxChPanel2 = new ChartPanel(FluxChart2);
        FluxChPanel2.setPreferredSize( new java.awt.Dimension( 500 , 300 ) );
        viewParaID.getPlotFlux2().add(FluxChPanel2, "PlotFlux2");
        FluxChart2.setBackgroundPaint(null);
        ((XYBlockRenderer) FluxChPanel2.getChart().getXYPlot().getRenderer()).setBlockHeight((getMaxDouble(psiq_y)-getMinDouble(psiq_y))/22);
        ((XYBlockRenderer) FluxChPanel2.getChart().getXYPlot().getRenderer()).setBlockWidth((getMaxDouble(psiq_x)-getMinDouble(psiq_x))/22);
        
        //----------------------------FrictionID Chart----------------------------------------
        JFreeChart FrictionID_Chart = ChartFactory.createXYLineChart("Torque vs. Speed", "Speed in rad/s", "Torque in Nm", null);
        FrictionID_ChPanel = new ChartPanel(FrictionID_Chart);
        viewParaID.getPlotFrictionID().add(FrictionID_ChPanel, "PlotFrictionID");
        FrictionID_ChPanel.setMaximumSize(new Dimension(900,400));
        FrictionID_ChPanel.setPreferredSize(new Dimension(900,400));
        FrictionID_Chart.setBackgroundPaint(null);
        XYPlot FIDplot = FrictionID_ChPanel.getChart().getXYPlot();
        XYLineAndShapeRenderer renderer = new XYLineAndShapeRenderer( );
        renderer.setSeriesPaint( 0 , Color.RED );
        renderer.setSeriesLinesVisible(0, false);
        renderer.setSeriesShape(0, new Rectangle(0,0,7,7));
        renderer.setSeriesPaint( 1 , Color.BLUE );
        renderer.setSeriesShapesVisible(1, false);
        FIDplot.setRenderer( renderer );
        NumberAxis xxAxis = new NumberAxis();
        xxAxis.setStandardTickUnits(NumberAxis.createStandardTickUnits ());
                   
        recvCont.getNf3().setMaximumFractionDigits(0);
        xxAxis.setTickUnit (new NumberTickUnit(10,recvCont.getNf3(),3));
        xxAxis.setVisible(true);
            
        FrictionID_ChPanel.getChart().getXYPlot().setDomainAxis(xxAxis);
        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setLabel("Speed in rad/s");
        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setLabel("Friction in Nm");
        Color frictionText = new Color(0xD1, 0xD5, 0xDB);
        Color frictionGrid = new Color(0x4A, 0x4D, 0x52);
        Color frictionBg = new Color(0x1F, 0x21, 0x24);
        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setLabelPaint(frictionText);
        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(frictionText);
        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setLabelPaint(frictionText);
        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(frictionText);
        FrictionID_ChPanel.getChart().getTitle().setPaint(frictionText);
        FrictionID_ChPanel.getChart().getLegend().setItemPaint(frictionText);
        FrictionID_ChPanel.getChart().getXYPlot().setBackgroundPaint(frictionBg);
        FrictionID_ChPanel.getChart().getXYPlot().setDomainGridlinePaint(frictionGrid);
        FrictionID_ChPanel.getChart().getXYPlot().setRangeGridlinePaint(frictionGrid);
        FrictionID_ChPanel.getChart().getXYPlot().getRenderer().setSeriesPaint(0, Color.decode("#ff0000"));
        FrictionID_ChPanel.getChart().getXYPlot().getRenderer().setSeriesPaint(1, Color.decode("#ba55d3"));
        FrictionID_ChPanel.getChart().getXYPlot().getRenderer().setSeriesStroke(1, new BasicStroke(2.0f));
        FrictionID_ChPanel.getChart().setTitle("Frictiontorque");  
        XYSeriesCollection MechDataSet = new XYSeriesCollection();
        XYSeries[] MechSer = new XYSeries[2];
            
        n_max=Integer.parseInt(viewParaID.getTxt_FID_max_speed_ref().getText());
        N_Visco=Integer.parseInt(viewParaID.getTxt_FID_N_visco_values_ref().getText());
        MechSer[0]= new XYSeries("Measurement values");
        MechSer[1]=new XYSeries("Regression line");
        MechDataSet.addSeries(MechSer[0]);
        MechDataSet.addSeries(MechSer[1]);
        FrictionID_ChPanel.getChart().getXYPlot().setDataset(MechDataSet);
        FrictionID_ChPanel.getChart().getLegend().setBackgroundPaint(null);
        parameterIdReady = true;
    }
    @Override
    public void actionPerformed (ActionEvent event){
        if (viewParaID == null) {
            return;
        }
        Object quelle = event.getSource();
        if ( quelle == viewParaID.getBtn_OID_SaveMaps())
        {
            try {   
                init_SaveMaps();
            } catch (IOException exception) {
                JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
            }
        }
        else if ( quelle == viewParaID.getBtn_Save_FrictionID())
        {
            try {       
                init_FrictionID_curve();
            } catch (IOException exception) {
                JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
            }
        }
        ParameterID_ActionEvents(viewParaID, transmitter, quelle);
    }
    
    @Override
    public void onTransmitterUpdate(Transmitter source, Object payload)
    {
        if (!parameterIdReady || recvCont == null) {
            return;
        }
        if (recvCont.get_update_func_runs()) 
        {
            if(recvCont.get_is_first_call()){oldStatus = recvCont.get_adata().status;}
            if (sendCont.DarkLightModeChanged == true) { //Only gets called, if the button to change the dark/light mode has been pressed
                if (ActiveState < 141 || ActiveState > 150 ) {
                    viewParaID.getTxt_EID_LockRotor().setBackground(null);
                    viewParaID.getTxt_EID_LockRotor().setForeground(viewParaID.getTxt_EID_LockRotor().getBackground());
                }
                if (viewParaID.getTxt_FMID_status().getForeground() != Color.black) {
                    viewParaID.getTxt_FMID_status().setBackground(null);
                    viewParaID.getTxt_FMID_status().setForeground(viewParaID.getTxt_FMID_status().getBackground());
                }
                  boolean isDarkMode = true;
                  if (isDarkMode) {    
                        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setLabelPaint(Color.lightGray);
                        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(Color.lightGray);
                        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setLabelPaint(Color.lightGray);
                        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(Color.lightGray);
                        FrictionID_ChPanel.getChart().getTitle().setPaint(Color.lightGray);
                        FrictionID_ChPanel.getChart().getLegend().setItemPaint(Color.lightGray); 
                        FluxChPanel1.getChart().getXYPlot().getDomainAxis().setLabelPaint(Color.lightGray);
                        FluxChPanel1.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(Color.lightGray);
                        FluxChPanel1.getChart().getXYPlot().getRangeAxis().setLabelPaint(Color.lightGray);
                        FluxChPanel1.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(Color.lightGray);
                        fluxDLegend.getAxis().setTickLabelPaint(Color.lightGray);
                        FluxChPanel1.getChart().clearSubtitles();
                        FluxChart1.addSubtitle(fluxDLegend);
                        FluxChPanel2.getChart().getXYPlot().getDomainAxis().setLabelPaint(Color.lightGray);
                        FluxChPanel2.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(Color.lightGray);
                        FluxChPanel2.getChart().getXYPlot().getRangeAxis().setLabelPaint(Color.lightGray);
                        FluxChPanel2.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(Color.lightGray);
                        fluxQLegend.getAxis().setTickLabelPaint(Color.lightGray);
                        FluxChPanel2.getChart().clearSubtitles();
                        FluxChart2.addSubtitle(fluxQLegend);
                        FrictionID_ChPanel.getChart().getXYPlot().setBackgroundPaint(Color.black);
                        FrictionID_ChPanel.getChart().getXYPlot().setDomainGridlinePaint(Color.white);
                        FrictionID_ChPanel.getChart().getXYPlot().setRangeGridlinePaint(Color.white);
                } else {
                        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setLabelPaint(Color.black);
                        FrictionID_ChPanel.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(Color.black);
                        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setLabelPaint(Color.black);
                        FrictionID_ChPanel.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(Color.black);
                        FrictionID_ChPanel.getChart().getTitle().setPaint(Color.black);
                        FrictionID_ChPanel.getChart().getLegend().setItemPaint(Color.black);
                        FluxChPanel1.getChart().getXYPlot().getDomainAxis().setLabelPaint(Color.black);
                        FluxChPanel1.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(Color.black);
                        FluxChPanel1.getChart().getXYPlot().getRangeAxis().setLabelPaint(Color.black);
                        FluxChPanel1.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(Color.black);
                        fluxDLegend.getAxis().setTickLabelPaint(Color.black);
                        FluxChPanel1.getChart().clearSubtitles();
                        FluxChart1.addSubtitle(fluxDLegend);
                        FluxChPanel2.getChart().getXYPlot().getDomainAxis().setLabelPaint(Color.black);
                        FluxChPanel2.getChart().getXYPlot().getDomainAxis().setTickLabelPaint(Color.black);
                        FluxChPanel2.getChart().getXYPlot().getRangeAxis().setLabelPaint(Color.black);
                        FluxChPanel2.getChart().getXYPlot().getRangeAxis().setTickLabelPaint(Color.black);
                        fluxQLegend.getAxis().setTickLabelPaint(Color.black);
                        FluxChPanel2.getChart().clearSubtitles();
                        FluxChart2.addSubtitle(fluxQLegend);
                        FrictionID_ChPanel.getChart().getXYPlot().setBackgroundPaint(Color.white);
                        FrictionID_ChPanel.getChart().getXYPlot().setDomainGridlinePaint(Color.black);
                        FrictionID_ChPanel.getChart().getXYPlot().setRangeGridlinePaint(Color.black);
                } 
            }
            try {   
                 
                if ( recvCont.getScopeRunStop() == true ) {
                    update_ParaID_graph();
                }
                if (System.currentTimeMillis() - recvCont.lastSystemMillisSlowData > recvCont.SLOW_DATA_REFRESH_RATE_MS)        // > xx ms
                {
                    update_ParaID_values();
                }
            } catch (Exception exception) {
                recvCont.getLogger().info("ReceiveController: exception in update/ParaID_Graph -- ");
                recvCont.getLogger().severe(exception.toString());
                System.out.println("ReceiveController: exception in update/ParaID_Graph");
            }
             
            // Statuslampen steuern
            if (viewSCOPE.getTxtReady().getBackground() !=  viewParaID.getTxt_ParaID_Ready().getBackground()){
                viewParaID.getTxt_ParaID_Ready().setBackground(viewSCOPE.getTxtReady().getBackground());
            }
            if (viewSCOPE.getTxtRunning().getBackground() !=  viewParaID.getTxt_ParaID_Running().getBackground()){
                viewParaID.getTxt_ParaID_Running().setBackground(viewSCOPE.getTxtRunning().getBackground());
            }            
            if (viewSCOPE.getTxtError().getBackground() !=  viewParaID.getTxt_ParaID_Error().getBackground()){
                viewParaID.getTxt_ParaID_Error().setBackground(viewSCOPE.getTxtError().getBackground());
            }     
            if (viewSCOPE.getTxtUser().getBackground() !=  viewParaID.getTxt_ParaID_User().getBackground()){
                viewParaID.getTxt_ParaID_User().setBackground(viewSCOPE.getTxtUser().getBackground());
            }
            if ((recvCont.is_status_bit_true(13)) && (did_status_bit_change(13) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_EID_IDENTLQ().setBackground(Color.green);
            }
            if ((!recvCont.is_status_bit_true(13)) && (did_status_bit_change(13) || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_EID_IDENTLQ().setBackground(null);
                viewParaID.getTxt_EID_IDENTLQ().setForeground(viewParaID.getTxt_EID_IDENTLQ().getBackground());
            }
            
            if ((recvCont.is_status_bit_true(14)) && (did_status_bit_change(14) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_FMID_RSONLINE_status().setBackground(Color.green);
            }
            if ((!recvCont.is_status_bit_true(14)) && (did_status_bit_change(14) || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_FMID_RSONLINE_status().setBackground(null);
                viewParaID.getTxt_FMID_RSONLINE_status().setForeground(viewParaID.getTxt_FMID_RSONLINE_status().getBackground());
            }
            
            if ((recvCont.is_status_bit_true(15)) && (did_status_bit_change(15) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
               viewParaID.getTxt_FMID_AMMactive().setBackground(Color.green);
            }
            if ((!recvCont.is_status_bit_true(15)) && (did_status_bit_change(15) || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_FMID_AMMactive().setBackground(null);
                viewParaID.getTxt_FMID_AMMactive().setForeground(viewParaID.getTxt_FMID_AMMactive().getBackground());
            }
            
            if ((recvCont.is_status_bit_true(16)) && (did_status_bit_change(16) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_ParaID_ControlStatus().setBackground(Color.green);
                viewParaID.getTxt_ParaID_ControlStatus().setText("Current Control");
            }
            
            if ((recvCont.is_status_bit_true(17)) && (did_status_bit_change(17) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_ParaID_ControlStatus().setBackground(Color.green);
                viewParaID.getTxt_ParaID_ControlStatus().setText("Speed Control");
            }
            
            if ((recvCont.is_status_bit_true(18)) && (did_status_bit_change(18) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_ParaID_ControlStatus().setBackground(Color.black);
                viewParaID.getTxt_ParaID_ControlStatus().setText("No Control");
            }
          
            if ((recvCont.is_status_bit_true(19)) && (did_status_bit_change(19) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_ParameterID().setBackground(Color.green);
                viewParaID.getTxt_ParameterID().setText("Enabled");
            }
            if ((!recvCont.is_status_bit_true(19)) && (did_status_bit_change(19) || recvCont.get_is_first_call() || sendCont.did_LookAndFeel_change())){
                viewParaID.getTxt_ParameterID().setBackground(Color.black);
                viewParaID.getTxt_ParameterID().setText("Disabled");
            }
            //Has to be called after the last "access" to oldStatus
            oldStatus = recvCont.get_adata().status;
        }
       
    }
     
     
    public void init_SaveMaps() throws IOException
    {
        Date date = new Date();
        Format formatter = new SimpleDateFormat("YYYY-MM-dd_HH-mm-ss");
        dataWriter = new FileWriter("FluxMapData_" + formatter.format(date) + ".csv");
        dataWriter.append("FluxMapData_ " + formatter.format(date) + " \n");          
           
        try {
            dataWriter.append("Rated Current in A"+";");
            dataWriter.append(String.valueOf(I_rat)+";");
            dataWriter.append("\n");
            dataWriter.append("Permanent Flux in Vs"+";");
            dataWriter.append(String.valueOf(PsiPMOnline)+";");
            dataWriter.append("\n");
            dataWriter.append("Phaseresistance in Ohm"+";");
            dataWriter.append(String.valueOf(RsOnline)+";");
            dataWriter.append("\n");
            dataWriter.append("Windingtemperatur in Celsius Degree"+";");
            dataWriter.append(String.valueOf(Wtemp)+";");
            dataWriter.append("\n");
            dataWriter.append("Temperaturcoefficient of d-Flux"+";");
            dataWriter.append(String.valueOf(FluxTempConst)+";");
            dataWriter.append("\n");
            dataWriter.append("Temperaturerror of d-Flux"+";");
            dataWriter.append(String.valueOf(FluxTempError)+";");
            dataWriter.append("\n");
            dataWriter.append("\n");     
            dataWriter.append("FluxMap in d-Axis;");
            dataWriter.append("\n");
            dataWriter.append("d-Current in A (x-Axis);");
            dataWriter.append("\n");                       
           
            for (int rowIndex = 0; rowIndex < 20; rowIndex++) {
                for (int columnIndex = 0; columnIndex < 20; columnIndex++) {
                    dataWriter.append(String.valueOf(psid_x[columnIndex * 20 + rowIndex]) + ";");
                }
                dataWriter.append("\n");
            }
            dataWriter.append("q-Current in A (y-Axis);");
            dataWriter.append("\n");
            for (int rowIndex = 0; rowIndex < 20; rowIndex++) {
                for (int columnIndex = 0; columnIndex < 20; columnIndex++) {
                    dataWriter.append(String.valueOf(psid_y[columnIndex * 20 + rowIndex]) + ";");
                }
                dataWriter.append("\n");
            }
            dataWriter.append("d-Flux Values in mVs;");
            dataWriter.append("\n");
            for (int rowIndex = 0; rowIndex < 20; rowIndex++) {
                for (int columnIndex = 0; columnIndex < 20; columnIndex++) {
                     dataWriter.append(String.valueOf(psid_map[columnIndex * 20 + rowIndex]) + ";");
                }
                dataWriter.append("\n");
            }
            dataWriter.append("\n");
            dataWriter.append("FluxMap in q-Axis;");
            dataWriter.append("\n");
            dataWriter.append("d-Current in A (x-Axis);");
            dataWriter.append("\n");
                             
                        
            for (int rowIndex = 0; rowIndex < 20; rowIndex++) {
                for (int columnIndex = 0; columnIndex < 20; columnIndex++) {
                    dataWriter.append(String.valueOf(psiq_x[columnIndex * 20 + rowIndex]) + ";");
                }
                dataWriter.append("\n");
            }
            dataWriter.append("q-Current in A (y-Axis);");
            dataWriter.append("\n");
            for (int rowIndex = 0; rowIndex < 20; rowIndex++) {
                for (int columnIndex = 0; columnIndex < 20; columnIndex++) {
                    dataWriter.append(String.valueOf(psiq_y[columnIndex * 20 + rowIndex]) + ";");
                }
                dataWriter.append("\n");
            }
            dataWriter.append("q-Flux Values in mVs;");
            dataWriter.append("\n");
            for (int rowIndex = 0; rowIndex < 20; rowIndex++) {
                for (int columnIndex = 0; columnIndex < 20; columnIndex++) {
                    dataWriter.append(String.valueOf(psiq_map[columnIndex * 20 + rowIndex]) + ";");
                }
                dataWriter.append("\n");
            }
            dataWriter.append("\n");
        } catch (IOException exception) {
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }      
        dataWriter.flush();
        dataWriter.close();
    }
    
    public void init_FrictionID_curve() throws IOException
    {
        Date date = new Date();
        Format formatter = new SimpleDateFormat("YYYY-MM-dd_HH-mm-ss");
        dataWriter = new FileWriter("FrictionIDData_" + formatter.format(date) + ".csv");
        dataWriter.append("FrictionIDData_a_ " + formatter.format(date) + " \n");         
           
        try {
            dataWriter.append("Breakaway Torque in Nm"+";");
            dataWriter.append(String.valueOf(BreakTorque)+";");
            dataWriter.append("\n");
            dataWriter.append("Coloumb Torque in Nm"+";");
            dataWriter.append(String.valueOf(CoulTorque)+";");
            dataWriter.append("\n");
            dataWriter.append("Viscous Friction in Nms/rad"+";");
            dataWriter.append(String.valueOf(ViscoFriction)+";");
            dataWriter.append("\n");
            dataWriter.append("Speed in rad/s (x-Axis);Torque in Nm (y-Axis);");
            dataWriter.append("\n");
            for (int sampleIndex = 0; sampleIndex < 256; sampleIndex++) {
                if (FrictionID_Array[0][sampleIndex] != 0) {
                dataWriter.append(String.valueOf(FrictionID_Array[1][sampleIndex]) + ";");
                dataWriter.append(String.valueOf(FrictionID_Array[0][sampleIndex]) + ";");
                dataWriter.append("\n");
                }
            }
        } catch (IOException exception) {
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }         
        dataWriter.flush();
        dataWriter.close();
    }  
    
    public void update_ParaID_values() {
        //--------------------------------------------------------//
        //----------------------ParameterID------------------------
        //-------------------------------------------------------//
        ActiveState=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("activeState"), 2).toString());
        viewParaID.getTxt_activeState().setText(recvCont.getNf3().format(ActiveState));
                   
        //ElectricalID
        viewParaID.getTxt_EID_Rs().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Rs_Offline"), 2).toString()))); 
        viewParaID.getTxt_EID_Ld().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Ld_Offline"), 2).toString())));                   
        viewParaID.getTxt_EID_Lq().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Lq_Offline"), 2).toString())));               
        viewParaID.getTxt_EID_psiPM().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("PsiPM_Offline"), 2).toString())));               
        viewParaID.getTxt_EID_J().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("J"), 2).toString())*1000)); 
        viewParaID.getTxt_EID_p().setText(recvCont.getNf3().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("polePairs"), 2).toString()))); 
        viewParaID.getTxt_EID_encoderOffset().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("encoderOffset"), 2).toString()))); 
                 
        //FrictionID
        BreakTorque = Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Stribtorque") , 2).toString());
        viewParaID.getTxt_FID_M_Brk_motor2().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Stribtorque"), 2).toString()))); 
        CoulTorque=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Coulombtorque") , 2).toString());
        viewParaID.getTxt_FID_M_Coul_motor().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Coulombtorque"), 2).toString()))); 
        ViscoFriction=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Viscotorque") , 2).toString());
        viewParaID.getTxt_FID_d_fric_motor().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Viscotorque"), 2).toString())*1000)); 
                   
        //TwoMassID
        viewParaID.getTxt_TMID_J_total().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("TrainInertia"), 2).toString())*1000)); 
        viewParaID.getTxt_TMID_J_load().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("LoadInertia"), 2).toString())*1000)); 
        viewParaID.getTxt_TMID_J_motor().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("totalRotorInertia"), 2).toString())*1000));                 
        viewParaID.getTxt_TMID_c_est().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("c_est"), 2).toString()))); 
        viewParaID.getTxt_TMID_d_est().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("d_est"), 2).toString())));
        
        //OnlineID
        LdOnline=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Ld_Online") , 2).toString())*1000;
        LqOnline=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Lq_Online"), 2).toString())*1000;
        PsiPMOnline=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("PsiPM_Online"), 2).toString())*1000;
        RsOnline=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Rs_Online"), 2).toString())*1000;
        viewParaID.getTxt_OID_Ld().setText(recvCont.getNf().format(LdOnline));
        viewParaID.getTxt_OID_Lq().setText(recvCont.getNf().format(LqOnline));
        viewParaID.getTxt_OID_PsiPm().setText(recvCont.getNf().format(PsiPMOnline));
        viewParaID.getTxt_OID_Rph().setText(recvCont.getNf().format(RsOnline));
        viewParaID.getTxt_n_OID_FluxPoints().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("n_FluxPoints"), 2).toString())));                   
        
        //FluxMapID
        viewParaID.getTxt_FMID_resistance().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Rs_online_FMID"), 2).toString()))); 
        viewParaID.getTxt_FMID_windingTemp().setText(recvCont.getNf().format(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("Wtemp_FMID"), 2).toString()))); 
                   
        ArrayList<Long> commands = new ArrayList<>();
        //Update FrictionID curve
        if ( Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("ArrayCounter"), 2).toString()) == Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("ArrayControlCounter"), 2).toString()) ) {
            ArrCount = (int)Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("ArrayCounter") , 2).toString());
            MeasArraySpeed = Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("measArraySpeed") , 2).toString());
            MeasArrayTorque = Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("measArrayTorque") , 2).toString());
            FrictionID_Array[(int)0][ArrCount] = MeasArrayTorque;
            FrictionID_Array[(int)1][ArrCount] = MeasArraySpeed;
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_Array_Control_counter"),Integer.toString(ArrCount)));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        //Update Flux Maps
        if ( Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("MapCounter"), 2).toString()) == Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("MapControlCounter"), 2).toString()) ) {
            I_rat=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("I_rated"), 2).toString());
            MapCount=(int)(Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("MapCounter"), 2).toString()));
            psid_grid=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("psidMap"), 2).toString());
            psiq_grid=Float.parseFloat(recvCont.getTableModel().getValueAt(slowDataSignalNames.indexOf("psiqMap"), 2).toString());
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_Fluxmap_Control_counter"),Integer.toString(MapCount)));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
            if(psid_grid<1000&&psid_grid>-1000&&MapCount<400){
                psid_map[MapCount]=(double)psid_grid;
            }
            if(psiq_grid<1000&&psiq_grid>-1000&&MapCount<400){
                psiq_map[MapCount]=(double)psiq_grid;
            }
                   }
                   
                   
        if(viewParaID.getBtnActivate_ElectricalID().isSelected() == true) {   
            if(ActiveState >= 100 && ActiveState < 170) {
                viewParaID.getTxt_ElectricalID().setBackground(Color.yellow);
                viewParaID.getTxt_ElectricalID().setText("Active");
                viewParaID.getTxt_ElectricalID().setForeground(Color.black);
                if (ActiveState == 141 && (recvCont.is_status_bit_true(13))) {
                    viewParaID.getTxt_EID_LockRotor().setText("LOCK rotor and press ACCEPT");
                    viewParaID.getTxt_EID_LockRotor().setBackground(Color.yellow);
                    viewParaID.getTxt_EID_LockRotor().setForeground(Color.black);
                } else if (ActiveState == 144 && (recvCont.is_status_bit_true(13))) {
                    viewParaID.getTxt_EID_LockRotor().setText("UNLOCK rotor and press ACCEPT");
                } else if (ActiveState == 150) {
                    viewParaID.getTxt_EID_LockRotor().setBackground(null);
                    viewParaID.getTxt_EID_LockRotor().setForeground(viewParaID.getTxt_EID_LockRotor().getBackground());
                }
            } else if (ActiveState == 170) {
                viewParaID.getTxt_ElectricalID().setBackground(Color.green);
                viewParaID.getTxt_ElectricalID().setText("Finished");
                viewParaID.getTxt_ElectricalID().setForeground(Color.white);
            }
        }
                
        if(viewParaID.getBtnActivate_FrictionID().isSelected() == true) {   
            if(ActiveState >= 300 && ActiveState < 340) {
                viewParaID.getTxt_FrictionID().setBackground(Color.yellow);
                viewParaID.getTxt_FrictionID().setText("Active");
                viewParaID.getTxt_FrictionID().setForeground(Color.black);
            } else if (ActiveState == 340) {
                viewParaID.getTxt_FrictionID().setBackground(Color.green);
                viewParaID.getTxt_FrictionID().setText("Finished");
                viewParaID.getTxt_FrictionID().setForeground(Color.white);
            }
        }
        
        if(viewParaID.getBtnActivate_TwoMassID().isSelected() == true) {   
            if(ActiveState >= 200 && ActiveState < 230) {
                viewParaID.getTxt_TwoMassID().setBackground(Color.yellow);
                viewParaID.getTxt_TwoMassID().setText("Active");
                viewParaID.getTxt_TwoMassID().setForeground(Color.black);
            } else if (ActiveState == 230) {
                viewParaID.getTxt_TwoMassID().setBackground(Color.green);
                viewParaID.getTxt_TwoMassID().setText("Finished");
                viewParaID.getTxt_TwoMassID().setForeground(Color.white);
            }
        }
        
        if(viewParaID.getBtnActivate_FluxMapID().isSelected() == true) {
            if(ActiveState >= 400 && ActiveState < 450) {
                viewParaID.getTxt_FluxMapID().setBackground(Color.yellow);
                viewParaID.getTxt_FluxMapID().setText("Active");
                viewParaID.getTxt_FluxMapID().setForeground(Color.black);
                viewParaID.getTxt_FMID_status().setForeground(Color.black);
                if (viewParaID.getBtn_FMID_ToggleAutomatedMeasuring().isSelected() == true) {
                switch((int)ActiveState) {
                    case 420:
                        viewParaID.getTxt_FMID_status().setBackground(Color.yellow);
                        viewParaID.getTxt_FMID_status().setText("Heating");
                        break;
                  case 410:
                        viewParaID.getTxt_FMID_status().setBackground(Color.yellow);
                        viewParaID.getTxt_FMID_status().setText("Cooling");
                        break;
                    case 402:
                        viewParaID.getTxt_FMID_status().setText("Setting ref value");
                        viewParaID.getTxt_FMID_status().setBackground(Color.yellow);
                        break;
                    case 403:
                        viewParaID.getTxt_FMID_status().setText("Collecting data");
                        viewParaID.getTxt_FMID_status().setBackground(Color.yellow);
                        break;
                    case 404:
                        viewParaID.getTxt_FMID_status().setText("Wait for collect to finish");
                        viewParaID.getTxt_FMID_status().setBackground(Color.yellow);                  
                 default:
                        viewParaID.getTxt_FMID_status().setBackground(null);
                        viewParaID.getTxt_FMID_status().setText("Waiting");
                }
            }
            } else if (ActiveState == 450) {
                viewParaID.getTxt_FluxMapID().setBackground(Color.green);
                viewParaID.getTxt_FluxMapID().setText("Finished");
                viewParaID.getTxt_FMID_status().setText("Finished");
                viewParaID.getTxt_FMID_status().setBackground(Color.green);
            }
            viewParaID.getTxt_FMID_i_d_current().setText(recvCont.getNf1().format(recvCont.getAverageValue(3)));
            viewParaID.getTxt_FMID_i_q_current().setText(recvCont.getNf1().format(recvCont.getAverageValue(4)));
            
        }
                
        if(viewParaID.getBtnActivate_OnlineID().isSelected() == true){
            if(ActiveState >= 500 && ActiveState <= 504) {
                viewParaID.getTxt_OnlineID().setBackground(Color.green);
                viewParaID.getTxt_OnlineID().setText("Active");
            }
        }

    }
    public void update_ParaID_graph() {
        //---------------------------------------------------------
        //----------------ParameterID------------------------------
        //---------------------------------------------------------
        if(ActiveState>=330 && ActiveState<=341){  
            boolean value_found = false;
            XYSeriesCollection MechDataSet = new XYSeriesCollection();
            XYSeries[] MechSer = new XYSeries[2];
            n_max=Integer.parseInt(viewParaID.getTxt_FID_max_speed_ref().getText());
            N_Visco=Integer.parseInt(viewParaID.getTxt_FID_N_visco_values_ref().getText());
            
            MechSer[0]= new XYSeries("Measurement values");
            MechSer[1]=new XYSeries("Regression line");
            for (int sampleIndex = 1; sampleIndex < N_Visco; sampleIndex++){
                if(FrictionID_Array[1][sampleIndex]!=0){
                MechSer[0].add(FrictionID_Array[1][sampleIndex],FrictionID_Array[0][sampleIndex]);
                value_found = true;
                }  
                
            }
            for (int speedIndex = 1; speedIndex < n_max/10; speedIndex++){            
                if(ViscoFriction!=0&&CoulTorque!=0){
                    MechSer[1].add(speedIndex,speedIndex*ViscoFriction+CoulTorque);
                }
            }
            if(value_found) {
                MechDataSet.addSeries(MechSer[0]);
                MechDataSet.addSeries(MechSer[1]);
                FrictionID_ChPanel.getChart().getXYPlot().setDataset(MechDataSet);
                FrictionID_ChPanel.repaint();
            }
        }    
        
        if(ActiveState >= 500 && ActiveState <= 504) {      
            DefaultXYZDataset datasetpsid = new DefaultXYZDataset();
            datasetpsid.addSeries("psid_map", new double[][] {  psid_x, psid_y, psid_map}); 
            DefaultXYZDataset datasetpsiq = new DefaultXYZDataset();
            datasetpsiq.addSeries("psiq_map", new double[][] {  psiq_x, psiq_y, psiq_map});      
      
            // create a paint-scale and a legend showing it
            LookupPaintScale paintScale;
            paintScale = new LookupPaintScale(getMinDouble(psid_map)-0.000001, getMaxDouble(psid_map)+0.000001, (Paint) Color.RED);
            Color legendColor = Color.BLUE;
            paintScale.add(getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.CYAN.darker();   
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.11+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.CYAN;
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.22+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.GREEN;
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.33+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.GREEN.darker();
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.44+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.YELLOW.darker();
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.55+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.ORANGE.darker();
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.66+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.ORANGE;
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.77+getMinDouble(psid_map), (Paint) legendColor);
            legendColor = Color.YELLOW;
            paintScale.add((getMaxDouble(psid_map)-getMinDouble(psid_map))*0.88+getMinDouble(psid_map), (Paint) legendColor);

            ((XYBlockRenderer) FluxChPanel1.getChart().getXYPlot().getRenderer()).setPaintScale(paintScale);               
            ((PaintScaleLegend) FluxChPanel1.getChart().getSubtitle(0)).setScale(paintScale);
            Range range=new Range(getMinDouble(psid_map)-0.000001,getMaxDouble(psid_map)+0.000001);
            ((PaintScaleLegend) FluxChPanel1.getChart().getSubtitle(0)).getAxis().setRange(range);
            FluxChPanel1.getChart().getXYPlot().setDataset(datasetpsid);
            FluxChPanel1.repaint();
                
            // create a paint-scale and a legend showing it

            paintScale = new LookupPaintScale(getMinDouble(psiq_map)-0.000001, getMaxDouble(psiq_map)+0.000001, (Paint) Color.RED);
            legendColor = Color.BLUE;
            paintScale.add(getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.CYAN.darker();   
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.11+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.CYAN;
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.22+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.GREEN;
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.33+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.GREEN.darker();
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.44+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.YELLOW.darker();
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.55+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.ORANGE.darker();
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.66+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.ORANGE;
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.77+getMinDouble(psiq_map), (Paint) legendColor);
            legendColor = Color.YELLOW;
            paintScale.add((getMaxDouble(psiq_map)-getMinDouble(psiq_map))*0.88+getMinDouble(psiq_map), (Paint) legendColor);

            ((XYBlockRenderer) FluxChPanel2.getChart().getXYPlot().getRenderer()).setPaintScale(paintScale);
            ((PaintScaleLegend) FluxChPanel2.getChart().getSubtitle(0)).setScale(paintScale);
            Range range2=new Range(getMinDouble(psiq_map)-0.000001,getMaxDouble(psiq_map)+0.000001);
            ((PaintScaleLegend) FluxChPanel2.getChart().getSubtitle(0)).getAxis().setRange(range2);
            FluxChPanel2.getChart().getXYPlot().setDataset(datasetpsiq);          
            FluxChPanel2.repaint();
        }
    }
    
    public void ParameterID_Enable_ElectricalID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_ElectricalID().setBackground(Color.blue);
        viewParaID.getTxt_ElectricalID().setText("Requested");
        viewParaID.getTxt_ElectricalID().setForeground(Color.white);
        viewParaID.getTxt_EID_SAMPLETIMEISRref().setEnabled(true);
        viewParaID.getTxt_EID_NREFMref().setEnabled(true);
        viewParaID.getTxt_EID_goeAmpref().setEnabled(true);
        viewParaID.getTxt_EID_goeFreq().setEnabled(true);
        viewParaID.getTxt_EID_DUTYCYCref().setEnabled(true);
        viewParaID.getTxt_EID_MAXCURRENTref().setEnabled(true);
        viewParaID.getBtn_EID_IDENTLQ().setEnabled(true);
        viewParaID.getBtn_EID_AdmitParams().setEnabled(true);
        viewParaID.getBtnSet_EID_DUTYCYC().setEnabled(true);
        viewParaID.getBtnSet_EID_MAXCURRENT().setEnabled(true);
        viewParaID.getBtnSet_EID_NREFM().setEnabled(true);
        viewParaID.getBtnSet_EID_SAMPLETIMEISR().setEnabled(true);
        viewParaID.getBtnSet_EID_goeAmp().setEnabled(true);
        viewParaID.getBtnSet_EID_goeFreq().setEnabled(true);
        viewParaID.getBtn_EID_AdmitParams().setEnabled(true);
    }
    
    public void ParameterID_Disable_ElectricalID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_ElectricalID().setBackground(Color.black);
        viewParaID.getTxt_ElectricalID().setText("Disabled");
        viewParaID.getTxt_ElectricalID().setForeground(Color.white);
        viewParaID.getTxt_EID_SAMPLETIMEISRref().setEnabled(false);
        viewParaID.getTxt_EID_NREFMref().setEnabled(false);
        viewParaID.getTxt_EID_goeAmpref().setEnabled(false);
        viewParaID.getTxt_EID_goeFreq().setEnabled(false);
        viewParaID.getTxt_EID_DUTYCYCref().setEnabled(false);
        viewParaID.getTxt_EID_MAXCURRENTref().setEnabled(false);
        viewParaID.getBtn_EID_IDENTLQ().setEnabled(false);
        viewParaID.getBtn_EID_AdmitParams().setEnabled(false);   
        viewParaID.getBtnSet_EID_DUTYCYC().setEnabled(false);
        viewParaID.getBtnSet_EID_MAXCURRENT().setEnabled(false);
        viewParaID.getBtnSet_EID_NREFM().setEnabled(false);
        viewParaID.getBtnSet_EID_SAMPLETIMEISR().setEnabled(false);
        viewParaID.getBtnSet_EID_goeAmp().setEnabled(false);
        viewParaID.getBtnSet_EID_goeFreq().setEnabled(false);     
        viewParaID.getBtn_EID_AdmitParams().setEnabled(false);
        viewParaID.getTxt_EID_IDENTLQ().setBackground(null);
        viewParaID.getTxt_EID_IDENTLQ().setForeground(viewParaID.getTxt_EID_IDENTLQ().getBackground());
    }
    
    public void ParameterID_Enable_FrictionID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_FrictionID().setBackground(Color.blue);               
        viewParaID.getTxt_FrictionID().setText("Requested");   
        viewParaID.getTxt_FID_Brk_Count_ref().setEnabled(true);
        viewParaID.getTxt_FID_N_Brk_values_ref().setEnabled(true);
        viewParaID.getTxt_FID_N_visco_values_ref().setEnabled(true);
        viewParaID.getTxt_FID_s_step_ref().setEnabled(true);
        viewParaID.getTxt_FID_max_speed_ref().setEnabled(true);
        viewParaID.getTxt_FID_eta_speed_ref().setEnabled(true);
        viewParaID.getBtnSet_FID_Brk_Count().setEnabled(true);
        viewParaID.getBtnSet_FID_N_Brk().setEnabled(true);
        viewParaID.getBtnSet_FID_N_visco().setEnabled(true);
        viewParaID.getBtnSet_FID_eta_n().setEnabled(true);
        viewParaID.getBtnSet_FID_max_speed().setEnabled(true);
        viewParaID.getBtnSet_FID_s_step().setEnabled(true);
        viewParaID.getBtn_Save_FrictionID().setEnabled(true);
    }
    
    public void ParameterID_Disable_FrictionID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_FrictionID().setBackground(Color.black);
        viewParaID.getTxt_FrictionID().setText("Disabled");
        viewParaID.getTxt_FrictionID().setForeground(Color.white);
        viewParaID.getTxt_FID_Brk_Count_ref().setEnabled(false);
        viewParaID.getTxt_FID_N_Brk_values_ref().setEnabled(false);
        viewParaID.getTxt_FID_N_visco_values_ref().setEnabled(false);
        viewParaID.getTxt_FID_s_step_ref().setEnabled(false);
        viewParaID.getTxt_FID_max_speed_ref().setEnabled(false);
        viewParaID.getTxt_FID_eta_speed_ref().setEnabled(false);
        viewParaID.getBtnSet_FID_Brk_Count().setEnabled(false);
        viewParaID.getBtnSet_FID_N_Brk().setEnabled(false);
        viewParaID.getBtnSet_FID_N_visco().setEnabled(false);
        viewParaID.getBtnSet_FID_eta_n().setEnabled(false);
        viewParaID.getBtnSet_FID_max_speed().setEnabled(false);
        viewParaID.getBtnSet_FID_s_step().setEnabled(false);
        viewParaID.getBtn_Save_FrictionID().setEnabled(false);
    }

    public void ParameterID_Enable_TwoMassID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_TwoMassID().setBackground(Color.blue);
        viewParaID.getTxt_TwoMassID().setText("Requested");
        viewParaID.getTxt_TMID_n_ref_measurement().setEnabled(true);
        viewParaID.getTxt_TMID_Scale_PRBS_ref().setEnabled(true);
        viewParaID.getTxt_TMID_d_TMS_start_ref().setEnabled(true);
        viewParaID.getTxt_TMID_f_max_ref().setEnabled(true);
        viewParaID.getTxt_TMID_f_min_ref().setEnabled(true);  
        viewParaID.getBtnSet_TMID_PRBS_Scale().setEnabled(true); 
        viewParaID.getBtnSet_TMID_d_TMS_start().setEnabled(true); 
        viewParaID.getBtnSet_TMID_f_max().setEnabled(true); 
        viewParaID.getBtnSet_TMID_f_min().setEnabled(true); 
        viewParaID.getBtnSet_TMID_n_ref().setEnabled(true); 
    }
    
    public void ParameterID_Disable_TwoMassID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_TwoMassID().setBackground(Color.black);
        viewParaID.getTxt_TwoMassID().setText("Disabled");
        viewParaID.getTxt_TMID_n_ref_measurement().setEnabled(false);
        viewParaID.getTxt_TMID_Scale_PRBS_ref().setEnabled(false);
        viewParaID.getTxt_TMID_d_TMS_start_ref().setEnabled(false);
        viewParaID.getTxt_TMID_f_max_ref().setEnabled(false);
        viewParaID.getTxt_TMID_f_min_ref().setEnabled(false); 
        viewParaID.getBtnSet_TMID_PRBS_Scale().setEnabled(false); 
        viewParaID.getBtnSet_TMID_d_TMS_start().setEnabled(false); 
        viewParaID.getBtnSet_TMID_f_max().setEnabled(false); 
        viewParaID.getBtnSet_TMID_f_min().setEnabled(false); 
        viewParaID.getBtnSet_TMID_n_ref().setEnabled(false); 
    }
    
    public void ParameterID_Enable_FluxMapID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_FluxMapID().setBackground(Color.blue);
        viewParaID.getTxt_FluxMapID().setForeground(Color.white);
        viewParaID.getTxt_FluxMapID().setText("Requested");
        viewParaID.getTxt_FMID_i_d_start_ref().setEnabled(true);
        viewParaID.getTxt_FMID_i_d_stop_ref().setEnabled(true);
        viewParaID.getTxt_FMID_i_d_stepsize_ref().setEnabled(true);
        viewParaID.getTxt_FMID_i_q_start_ref().setEnabled(true);
        viewParaID.getTxt_FMID_i_q_stop_ref().setEnabled(true);
        viewParaID.getTxt_FMID_i_q_stepsize_ref().setEnabled(true);
        viewParaID.getTxt_FMID_set_ref_R_ref().setEnabled(true);
        viewParaID.getTxt_FMID_Rs_ident_amplitude_ref().setEnabled(true);
        viewParaID.getTxt_FMID_set_ref_Temp_ref().setEnabled(true);
        viewParaID.getBtn_FMID_IDENTRSONLINE().setEnabled(true);
        viewParaID.getBtn_FMID_ToggleAutomatedMeasuring().setEnabled(true);
        viewParaID.getBtnSet_FMID_id_start().setEnabled(true);
        viewParaID.getBtnSet_FMID_id_step().setEnabled(true);
        viewParaID.getBtnSet_FMID_id_stop().setEnabled(true);
        viewParaID.getBtnSet_FMID_iq_start().setEnabled(true);
        viewParaID.getBtnSet_FMID_iq_step().setEnabled(true);
        viewParaID.getBtnSet_FMID_iq_stop().setEnabled(true);
        viewParaID.getBtnSet_FMID_set_identRamp().setEnabled(true);
        viewParaID.getBtnSet_FMID_set_ref_R().setEnabled(true);
        viewParaID.getBtnSet_FMID_set_ref_Winding().setEnabled(true);
    }
    
    public void ParameterID_Disable_FluxMapID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_FluxMapID().setBackground(Color.black);
        viewParaID.getTxt_FluxMapID().setForeground(Color.white);
        viewParaID.getTxt_FluxMapID().setText("Disabled");
        viewParaID.getTxt_FMID_i_d_start_ref().setEnabled(false);
        viewParaID.getTxt_FMID_i_d_stop_ref().setEnabled(false);
        viewParaID.getTxt_FMID_i_d_stepsize_ref().setEnabled(false);
        viewParaID.getTxt_FMID_i_q_start_ref().setEnabled(false);
        viewParaID.getTxt_FMID_i_q_stop_ref().setEnabled(false);
        viewParaID.getTxt_FMID_i_q_stepsize_ref().setEnabled(false);
        viewParaID.getTxt_FMID_set_ref_R_ref().setEnabled(false);
        viewParaID.getTxt_FMID_Rs_ident_amplitude_ref().setEnabled(false);
        viewParaID.getTxt_FMID_set_ref_Temp_ref().setEnabled(false);
        viewParaID.getBtn_FMID_IDENTRSONLINE().setEnabled(false);
        viewParaID.getBtn_FMID_ToggleAutomatedMeasuring().setEnabled(false);
        viewParaID.getBtnSet_FMID_id_start().setEnabled(false);
        viewParaID.getBtnSet_FMID_id_step().setEnabled(false);
        viewParaID.getBtnSet_FMID_id_stop().setEnabled(false);
        viewParaID.getBtnSet_FMID_iq_start().setEnabled(false);
        viewParaID.getBtnSet_FMID_iq_step().setEnabled(false);
        viewParaID.getBtnSet_FMID_iq_stop().setEnabled(false);
        viewParaID.getBtnSet_FMID_set_identRamp().setEnabled(false);
        viewParaID.getBtnSet_FMID_set_ref_R().setEnabled(false);
        viewParaID.getBtnSet_FMID_set_ref_Winding().setEnabled(false);
    }
    
    public void ParameterID_Enable_OnlineID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_OnlineID().setBackground(Color.blue);
        viewParaID.getTxt_OnlineID().setText("Requested");
        viewParaID.getTxt_OID_Ref_minimumSpeed().setEnabled(true);
        viewParaID.getTxt_OID_Ref_maximumSpeed().setEnabled(true);
        viewParaID.getTxt_OID_Ref_R().setEnabled(true);
        viewParaID.getTxt_OID_Ref_Temp().setEnabled(true);
        viewParaID.getTxt_OID_max_res_Current().setEnabled(true);
        viewParaID.getTxt_OID_q_Current_Steps().setEnabled(true);
        viewParaID.getTxt_OID_d_Current_Steps().setEnabled(true);
        viewParaID.getTxt_OID_Ref_identRangeA().setEnabled(true);
        viewParaID.getTxt_OID_Ref_identTime().setEnabled(true);
        viewParaID.geTtxt_OID_Ref_identRAmp().setEnabled(true);
        viewParaID.getBtn_OID_RefreshFlux().setEnabled(true);
        viewParaID.getBtn_OID_SaveMaps().setEnabled(true);
        viewParaID.getBtn_OID_EnableRefControl().setEnabled(true);
        viewParaID.getBtn_OID_OnlineReset().setEnabled(true);
        viewParaID.getBtnSet_OID_Ref_R1().setEnabled(true);
        viewParaID.getBtnSet_OID_Ref_Temp().setEnabled(true);
        viewParaID.getBtnSet_OID_d_Current_Steps().setEnabled(true);
        viewParaID.getBtnSet_OID_identRangeA().setEnabled(true);
        viewParaID.getBtnSet_OID_identTime().setEnabled(true);
        viewParaID.getBtnSet_OID_max_res_Current().setEnabled(true);
        viewParaID.getBtnSet_OID_maximumSpeed().setEnabled(true);
        viewParaID.getBtnSet_OID_minimumSpeed().setEnabled(true);
        viewParaID.getBtnSet_OID_q_Current_Steps().setEnabled(true);
        viewParaID.getBtnSet_OID_identRAmp().setEnabled(true);
    }
    
    public void ParameterID_Disable_OnlineID_Buttons(UZ_ParaID_view viewParaID) {
        viewParaID.getTxt_OnlineID().setBackground(Color.black);
        viewParaID.getTxt_OnlineID().setText("Disabled");
        viewParaID.getTxt_OID_Ref_minimumSpeed().setEnabled(false);
        viewParaID.getTxt_OID_Ref_maximumSpeed().setEnabled(false);
        viewParaID.getTxt_OID_Ref_R().setEnabled(false);
        viewParaID.getTxt_OID_Ref_Temp().setEnabled(false);
        viewParaID.getTxt_OID_max_res_Current().setEnabled(false);
        viewParaID.getTxt_OID_q_Current_Steps().setEnabled(false);
        viewParaID.getTxt_OID_d_Current_Steps().setEnabled(false);
        viewParaID.getTxt_OID_Ref_identRangeA().setEnabled(false);
        viewParaID.getTxt_OID_Ref_identTime().setEnabled(false);
        viewParaID.geTtxt_OID_Ref_identRAmp().setEnabled(false);
        viewParaID.getBtn_OID_RefreshFlux().setEnabled(false);
        viewParaID.getBtn_OID_SaveMaps().setEnabled(false);
        viewParaID.getBtn_OID_EnableRefControl().setEnabled(false);
        viewParaID.getBtn_OID_EnableRefControl().setSelected(false);
        viewParaID.getBtn_OID_OnlineReset().setEnabled(false);
        viewParaID.getBtnSet_OID_Ref_R1().setEnabled(false);
        viewParaID.getBtnSet_OID_Ref_Temp().setEnabled(false);
        viewParaID.getBtnSet_OID_d_Current_Steps().setEnabled(false);
        viewParaID.getBtnSet_OID_identRangeA().setEnabled(false);
        viewParaID.getBtnSet_OID_identTime().setEnabled(false);
        viewParaID.getBtnSet_OID_max_res_Current().setEnabled(false);
        viewParaID.getBtnSet_OID_maximumSpeed().setEnabled(false);
        viewParaID.getBtnSet_OID_minimumSpeed().setEnabled(false);
        viewParaID.getBtnSet_OID_q_Current_Steps().setEnabled(false);
        viewParaID.getBtn_OID_EnableRefControl().setForeground(Color.red);
        viewParaID.getBtn_OID_EnableRefControl().setSelected(false);
        viewParaID.getBtnSet_OID_identRAmp().setEnabled(false);
    }
    
    public void ParameterID_ActionEvents(UZ_ParaID_view viewParaID,  Transmitter transmitter, Object quelle){
            if( quelle == viewParaID.getBtnActivate_ParameterID()) {
            long commandIndex;                     
                        
            
            if(viewParaID.getBtnActivate_ParameterID().isSelected() == true) {
                viewParaID.getBtnActivate_ElectricalID().setEnabled(true);
                viewParaID.getBtnActivate_FluxMapID().setEnabled(true);
                viewParaID.getBtnActivate_FrictionID().setEnabled(true);
                viewParaID.getBtnActivate_TwoMassID().setEnabled(true);
                viewParaID.getBtnActivate_OnlineID().setEnabled(true);
                viewParaID.getBtn_ParaID_CurrentControl().setEnabled(true);
                viewParaID.getBtn_ParaID_Disable_Control().setEnabled(true);
                viewParaID.getBtn_ParaID_SpeedControl().setEnabled(true);
                viewParaID.getTxt_ParaID_ControlStatus().setEnabled(true);
                viewParaID.getBtnActivate_ParameterID().setForeground(Color.green);
                commandIndex = ButtonNames.indexOf("ParaID_Enable_ParameterID"); //Enable
            } else {
                viewParaID.getBtnActivate_ElectricalID().setEnabled(false);
                viewParaID.getBtnActivate_ElectricalID().setSelected(false);
                viewParaID.getBtnActivate_FluxMapID().setEnabled(false);
                viewParaID.getBtnActivate_FluxMapID().setSelected(false);
                viewParaID.getBtnActivate_FrictionID().setEnabled(false);
                viewParaID.getBtnActivate_FrictionID().setSelected(false);
                viewParaID.getBtnActivate_TwoMassID().setEnabled(false);
                viewParaID.getBtnActivate_TwoMassID().setSelected(false);
                viewParaID.getBtnActivate_OnlineID().setEnabled(false);
                viewParaID.getBtnActivate_OnlineID().setSelected(false);
                viewParaID.getBtn_ParaID_CurrentControl().setEnabled(false);
                viewParaID.getBtn_ParaID_Disable_Control().setEnabled(false);
                viewParaID.getBtn_ParaID_SpeedControl().setEnabled(false);
                viewParaID.getTxt_ParaID_ControlStatus().setEnabled(false);
                viewParaID.getBtn_OID_EnableRefControl().setForeground(Color.red);
                viewParaID.getBtn_OID_EnableRefControl().setSelected(false);
                viewParaID.getBtnActivate_ParameterID().setForeground(Color.black);
                if(viewParaID.getTxt_ElectricalID().getText() != "Finished") {
                    viewParaID.getTxt_ElectricalID().setText("Disabled");
                    viewParaID.getTxt_ElectricalID().setBackground(Color.black);
                    viewParaID.getTxt_ElectricalID().setForeground(Color.white);
                }
                if(viewParaID.getTxt_FluxMapID().getText() != "Finished") {
                    viewParaID.getTxt_FluxMapID().setText("Disabled");
                    viewParaID.getTxt_FluxMapID().setBackground(Color.black);
                    viewParaID.getTxt_FluxMapID().setForeground(Color.white);
                }
                if(viewParaID.getTxt_TwoMassID().getText() != "Finished") {
                    viewParaID.getTxt_TwoMassID().setText("Disabled");
                    viewParaID.getTxt_TwoMassID().setBackground(Color.black);
                    viewParaID.getTxt_TwoMassID().setForeground(Color.white);
                }
                if(viewParaID.getTxt_FrictionID().getText() != "Finished") {
                    viewParaID.getTxt_FrictionID().setText("Disabled");
                    viewParaID.getTxt_FrictionID().setBackground(Color.black);
                    viewParaID.getTxt_FrictionID().setForeground(Color.white);
                }
                if (viewParaID.getTxt_OnlineID().getText() != "Disabled") {
                    viewParaID.getTxt_OnlineID().setText("Disabled");
                    viewParaID.getTxt_OnlineID().setBackground(Color.black);
                }
                
                commandIndex = ButtonNames.indexOf("ParaID_Disable_ParameterID"); //Enable
            }
            transmitter.setCommand(commandIndex);
        }
        
        else if(quelle == viewParaID.getBtn_ParaID_EnSystem())
        {
            long commandIndex;
            commandIndex = ButtonNames.indexOf("Enable_System");
            transmitter.setCommand(commandIndex);
        }
        else if( quelle == viewParaID.getBtn_ParaID_EnControl())
        {    
            long commandIndex;
            commandIndex = ButtonNames.indexOf("Enable_Control");  
            transmitter.setCommand(commandIndex);                
        } 
        else if( quelle == viewParaID.getBtn_ParaID_Stop()){   
            long commandIndex;
            commandIndex = ButtonNames.indexOf("Stop");
            transmitter.setCommand(commandIndex);
        }
        
        else if (quelle == viewParaID.getBtn_ParaID_ACCEPT()) {
            long commandIndex;
            commandIndex = ButtonNames.indexOf("ParaID_ACCEPT");
            transmitter.setCommand(commandIndex);
        }
        
        else if (quelle == viewParaID.getBtn_ParaID_RESET()) {
            long commandIndex;
            ParameterID_Disable_ElectricalID_Buttons(viewParaID);
            viewParaID.getBtnActivate_ElectricalID().setSelected(false);            
            ParameterID_Disable_FrictionID_Buttons(viewParaID);
            viewParaID.getBtnActivate_FrictionID().setSelected(false);
            ParameterID_Disable_TwoMassID_Buttons(viewParaID);
            viewParaID.getBtnActivate_TwoMassID().setSelected(false);
            ParameterID_Disable_FluxMapID_Buttons(viewParaID);
            viewParaID.getBtnActivate_FluxMapID().setSelected(false);
            ParameterID_Disable_OnlineID_Buttons(viewParaID);
            viewParaID.getBtnActivate_OnlineID().setSelected(false);      
            viewParaID.getTxt_FMID_status().setBackground(null);
            viewParaID.getTxt_FMID_status().setText("Waiting");
            commandIndex = ButtonNames.indexOf("ParaID_RESET");
            transmitter.setCommand(commandIndex);
        }
       
        //--------------------------------------------------------
        //ElectricalID
        //
        //
        //---------------------------------------------------------
        else if( quelle == viewParaID.getBtnActivate_ElectricalID()) {
            long commandIndex;
            if(viewParaID.getBtnActivate_ElectricalID().isSelected() == true) {
                ParameterID_Enable_ElectricalID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Enable_ElectricalID"); //Enable
            } else {
                ParameterID_Disable_ElectricalID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Disable_ElectricalID"); //Disable
            }
            transmitter.setCommand(commandIndex); 
        }
        
        else if( quelle == viewParaID.getBtn_EID_IDENTLQ()){    
            long commandIndex;
            if (viewParaID.getBtn_EID_IDENTLQ().isSelected() == true){
                commandIndex = ButtonNames.indexOf("ParaID_EID_Enable_IdentLQ"); //Enable
                viewParaID.getBtn_EID_IDENTLQ().setForeground(Color.green);
            }else{
                commandIndex = ButtonNames.indexOf("ParaID_EID_Disable_IdentLQ"); //Disable
                viewParaID.getBtn_EID_IDENTLQ().setForeground(Color.red);
            }
            transmitter.setCommand(commandIndex); 
        }
        
        else if( quelle == viewParaID.getBtnSet_EID_SAMPLETIMEISR())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_EID_sampleTimeISR"), viewParaID.getTxt_EID_SAMPLETIMEISRref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }

        else if( quelle == viewParaID.getBtnSet_EID_goeFreq() )
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_EID_goertzl_Freq"), viewParaID.getTxt_EID_goeFreq().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }  
        else if( quelle == viewParaID.getBtnSet_EID_DUTYCYC() )
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_EID_DutyCyc"), viewParaID.getTxt_EID_DUTYCYCref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewParaID.getBtnSet_EID_NREFM() )
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_EID_n_ref_meas"), viewParaID.getTxt_EID_NREFMref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewParaID.getBtnSet_EID_goeAmp() )
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_EID_goertzl_Amp"), viewParaID.getTxt_EID_goeAmpref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        else if( quelle == viewParaID.getBtnSet_EID_MAXCURRENT() )
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_EID_MaxContinousCurrent"), viewParaID.getTxt_EID_MAXCURRENTref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        
         else if( quelle == viewParaID.getBtn_EID_AdmitParams())
        {   
           long commandIndex;
           commandIndex = ButtonNames.indexOf("ParaID_EID_Admit_Params");
           transmitter.setCommand(commandIndex);
        } 
        
        //--------------------------------------------------------
        //FrictionID
        //
        //
        //---------------------------------------------------------
        else if( quelle == viewParaID.getBtnActivate_FrictionID()) {
            long commandIndex;
            if(viewParaID.getBtnActivate_FrictionID().isSelected() == true) {
                ParameterID_Enable_FrictionID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Enable_FrictionID"); //Enable
            } else {
                ParameterID_Disable_FrictionID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Disable_FrictionID"); //Disable
            }
            transmitter.setCommand(commandIndex); 
        }
        
        else if( quelle == viewParaID.getBtnSet_FID_max_speed())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_max_speed"), viewParaID.getTxt_FID_max_speed_ref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        } 
        
        else if( quelle == viewParaID.getBtnSet_FID_N_Brk())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_N_Brk"), viewParaID.getTxt_FID_N_Brk_values_ref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        } 
        
        else if( quelle == viewParaID.getBtnSet_FID_N_visco())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_N_Visco"), viewParaID.getTxt_FID_N_visco_values_ref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        
        else if( quelle == viewParaID.getBtnSet_FID_s_step())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_s_step"), viewParaID.getTxt_FID_s_step_ref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        
        else if( quelle == viewParaID.getBtnSet_FID_Brk_Count())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_Brk_Count"), viewParaID.getTxt_FID_Brk_Count_ref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        
        else if( quelle == viewParaID.getBtnSet_FID_eta_n())
        {            
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FID_eta_speed"), viewParaID.getTxt_FID_eta_speed_ref().getText()));
            if (commands.contains((long)0) == false)    // "0" bedeutet fehlerhaftes Element!
                transmitter.setCommandList(commands);
        }
        
        //--------------------------------------------------------
        //TwoMassID
        //
        //
        //---------------------------------------------------------
        else if( quelle == viewParaID.getBtnActivate_TwoMassID()) {
            long commandIndex;
            if(viewParaID.getBtnActivate_TwoMassID().isSelected() == true) {
                ParameterID_Enable_TwoMassID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Enable_TwoMassID"); //Enable
            } else {
                ParameterID_Disable_TwoMassID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Disable_TwoMassID"); //Disable
            }
            transmitter.setCommand(commandIndex); 
        }
        
        else if( quelle == viewParaID.getBtnSet_TMID_PRBS_Scale()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_TMID_Scale_PRBS"), viewParaID.getTxt_TMID_Scale_PRBS_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_TMID_d_TMS_start()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_TMID_d_TMS_start"), viewParaID.getTxt_TMID_d_TMS_start_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_TMID_n_ref()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_TMID_n_ref"), viewParaID.getTxt_TMID_n_ref_measurement().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_TMID_f_min()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_TMID_f_min"), viewParaID.getTxt_TMID_f_min_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_TMID_f_max()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_TMID_f_max"), viewParaID.getTxt_TMID_f_max_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        //--------------------------------------------------------
        //FluxMapID
        //
        //
        //---------------------------------------------------------
        else if( quelle == viewParaID.getBtnActivate_FluxMapID()) {
           long commandIndex;
            if(viewParaID.getBtnActivate_FluxMapID().isSelected() == true) {
                ParameterID_Enable_FluxMapID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Enable_FluxMapID"); //Enable
            } else {
                ParameterID_Disable_FluxMapID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Disable_FluxMapID"); //Disable
            }
            transmitter.setCommand(commandIndex); 
        }
        
        else if( quelle == viewParaID.getBtn_FMID_ToggleAutomatedMeasuring()) {
           long commandIndex;
           if(viewParaID.getBtn_FMID_ToggleAutomatedMeasuring().isSelected() == true) {
               commandIndex = ButtonNames.indexOf("ParaID_FMID_enable_AMM");
           } else {
               commandIndex = ButtonNames.indexOf("ParaID_FMID_disable_AMM");
           }
           transmitter.setCommand(commandIndex);
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_id_start()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_i_d_start"), viewParaID.getTxt_FMID_i_d_start_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_id_stop()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_i_d_stop"), viewParaID.getTxt_FMID_i_d_stop_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_id_step()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_i_d_step"), viewParaID.getTxt_FMID_i_d_stepsize_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_iq_start()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_i_q_start"), viewParaID.getTxt_FMID_i_q_start_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_iq_stop()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_i_q_stop"), viewParaID.getTxt_FMID_i_q_stop_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_iq_step()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_i_q_step"), viewParaID.getTxt_FMID_i_q_stepsize_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_set_ref_Winding()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_Temp_ref"), viewParaID.getTxt_FMID_set_ref_Temp_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_set_identRamp()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_identRAmp"), viewParaID.getTxt_FMID_Rs_ident_amplitude_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_FMID_set_ref_R()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_FMID_Rs_ref"), viewParaID.getTxt_FMID_set_ref_R_ref().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtn_FMID_IDENTRSONLINE()) {
            long commandIndex;
            if (viewParaID.getBtn_FMID_IDENTRSONLINE().isSelected() == true) {
                commandIndex = ButtonNames.indexOf("ParaID_FMID_enable_ident_R");
            } else {
                commandIndex = ButtonNames.indexOf("ParaID_FMID_disable_ident_R");
            }
            transmitter.setCommand(commandIndex);
        }

        
        //--------------------------------------------------------
        //OnlineID
        //
        //
        //---------------------------------------------------------
        else if( quelle == viewParaID.getBtnActivate_OnlineID()) {
            long commandIndex;
            if(viewParaID.getBtnActivate_OnlineID().isSelected() == true) {
               ParameterID_Enable_OnlineID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Enable_OnlineID"); //Enable
            } else {
                ParameterID_Disable_OnlineID_Buttons(viewParaID);
                commandIndex = ButtonNames.indexOf("ParaID_Disable_OnlineID"); //Disable
            }
            transmitter.setCommand(commandIndex);
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_d_Current_Steps()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_d_current_steps"), viewParaID.getTxt_OID_d_Current_Steps().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_q_Current_Steps()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_q_current_steps"), viewParaID.getTxt_OID_q_Current_Steps().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_max_res_Current()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_max_current"), viewParaID.getTxt_OID_max_res_Current().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtn_OID_RefreshFlux()){    
            long commandIndex;
                commandIndex = ButtonNames.indexOf("ParaID_OID_Refresh_Flux_Maps");  
            transmitter.setCommand(commandIndex);    
        }
        
        else if(quelle == viewParaID.getBtn_OID_EnableRefControl()){
            long commandIndex;
            if(viewParaID.getBtn_OID_EnableRefControl().isSelected() == true) {
                commandIndex = ButtonNames.indexOf("ParaID_OID_Enable_AutoCurrentControl");
                viewParaID.getBtn_OID_EnableRefControl().setForeground(Color.green);
            } else {
                commandIndex = ButtonNames.indexOf("ParaID_OID_Disable_AutoCurrentControl");
                viewParaID.getBtn_OID_EnableRefControl().setForeground(Color.red);
            }
            transmitter.setCommand(commandIndex);
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_Ref_Temp()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_ref_temp"), viewParaID.getTxt_OID_Ref_Temp().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_Ref_R1()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_ref_Rs"), viewParaID.getTxt_OID_Ref_R().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_minimumSpeed()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_min_speed"), viewParaID.getTxt_OID_Ref_minimumSpeed().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_maximumSpeed()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_max_speed"), viewParaID.getTxt_OID_Ref_maximumSpeed().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_identRangeA()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_Ident_range_factor"), viewParaID.getTxt_OID_Ref_identRangeA().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_identTime()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_max_ident_pause"), viewParaID.getTxt_OID_Ref_identTime().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
        else if( quelle == viewParaID.getBtnSet_OID_identRangeA()) {
            ArrayList<Long> commands = new ArrayList<Long>();
            commands.add(sendCont.getParamCmd(ButtonNames.indexOf("ParaID_OID_identR_Amp"), viewParaID.geTtxt_OID_Ref_identRAmp().getText()));
            if (commands.contains((long)0) == false) {
                transmitter.setCommandList(commands);
            }
        }
        
         else if( quelle == viewParaID.getBtn_OID_OnlineReset())
        {   
           long commandIndex;
           viewParaID.getBtn_OID_EnableRefControl().setForeground(Color.red);
           viewParaID.getBtn_OID_EnableRefControl().setSelected(false);
           commandIndex = ButtonNames.indexOf("ParaID_OID_Reset_OnlineID");
           transmitter.setCommand(commandIndex);
        }
            
        else if(quelle == viewParaID.getBtn_ParaID_CurrentControl())
        {    
            long commandIndex;      
            commandIndex = ButtonNames.indexOf("ParaID_Enable_Current_Control");              
            transmitter.setCommand(commandIndex);
        }        
        
        else if(quelle == viewParaID.getBtn_ParaID_SpeedControl())
        {    
            long commandIndex;
            commandIndex = ButtonNames.indexOf("ParaID_Enable_Speed_Control");              
            transmitter.setCommand(commandIndex);           
        }
        
        else if(quelle == viewParaID.getBtn_ParaID_Disable_Control())
        {    
            long commandIndex;     
            commandIndex = ButtonNames.indexOf("ParaID_Disable_FOC_Control"); 
            transmitter.setCommand(commandIndex);           
        }
    }
    
    public static double getMaxDouble(double[] data) {

        double[] copy = Arrays.copyOf(data, data.length);
        Arrays.sort(copy);
        return copy[data.length - 1];
    }

    public static double getMinDouble(double[] data) {

        double[] copy = Arrays.copyOf(data, data.length);
        Arrays.sort(copy);
        return copy[0];
    }
    
    
    /**
     * Returns true, if the status-bit is different to the one from the previous time-step
     * 
     * @param status_bit specified bit_number
     * @return bool
     */
    @Override
    public boolean did_status_bit_change(int status_bit) {
        return (((recvCont.get_adata().status >> status_bit) & 1) != ((oldStatus >> status_bit) & 1));
    }

}

