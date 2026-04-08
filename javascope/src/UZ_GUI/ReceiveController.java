/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package UZ_GUI;

import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.Paint;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.io.File;
import java.io.BufferedWriter;
import java.io.FileWriter;
import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.time.LocalTime;
import java.time.format.DateTimeFormatter;
import java.text.Format;
import java.text.NumberFormat;
import java.text.SimpleDateFormat;
import java.text.DecimalFormat;
import java.text.DecimalFormatSymbols;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Date;
import java.util.IdentityHashMap;
import java.util.List;
import java.util.Locale;
import java.util.Map;
import java.util.Properties;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import javax.swing.JTextField;
import javax.swing.SwingUtilities;
import javax.swing.table.DefaultTableModel;
import org.jfree.chart.ChartMouseEvent;
import org.jfree.chart.ChartMouseListener;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.LegendItemCollection;
import org.jfree.chart.axis.ValueAxis;
import org.jfree.chart.entity.ChartEntity;
import org.jfree.chart.entity.LegendItemEntity;
import org.jfree.chart.panel.CrosshairOverlay;
import org.jfree.chart.plot.Crosshair;
import org.jfree.chart.plot.XYPlot;
import org.jfree.chart.renderer.xy.XYItemRenderer;
import org.jfree.data.xy.XYDataset;
import org.jfree.data.xy.XYSeries;
import org.jfree.data.xy.XYSeriesCollection;

/**
 *
 * @author z002311d
 */
public class ReceiveController implements TransmitterListener, ActionListener, WindowListener
{
    int ringBufferSamples;
    
    int SLOW_DATA_REFRESH_RATE_MS = 20;

    // Chart update rate in milliseconds (e.g., 100 = 10fps, 50 = 20fps, 1000 = 1fps -- prior 1000)
    static final int CHART_REFRESH_RATE_MS = 500;
    private static final int PACKET_RATE_WINDOW_MS = 1000;
    private static final double PACKET_RATE_MIN_RATIO = 0.95; // 95%
    private static final int PACKET_RATE_WARN_WINDOWS = 5;    // consecutive windows
    private static final int PACKET_RATE_AVG_WINDOWS = 10;    // 10s moving average
    private static final int THROUGHPUT_WINDOW_MS = 1000;
    private static final int LIFECHECK_MAX_VALUE = 1000;
    private static final DateTimeFormatter LIFECHECK_TIME_FORMATTER = DateTimeFormatter.ofPattern("HH:mm:ss", Locale.US);

    // Debug: scope update rate monitoring (set to true to enable console output)
    private static final boolean DEBUG_SCOPE_UPDATE_RATE = false;
    private long debugChartUpdateCount = 0;
    private long debugPacketCount = 0;
    private long debugLastStatTime = System.currentTimeMillis();

    private Logger logger = Logger.getLogger("Chat");
    private final PropertyFileDiagnostics propertyDiagnostics = PropertyFileDiagnostics.loadDefault();
    final static int LOG_INTERVALS[] = {20, 100, 500, 1000, 10000, 60000, 600000, 3600000};
    final static int TIMEBASE_FACTORS[] = {1, 5, 10, 50, 100};
    final static int LOGBASE_FACTORS[] = {1, 5, 10, 50, 100, 500, 1000, 5000, 10000};
    private UZ_GUI_view view;
    private UZ_SCOPE_view viewSCOPE;
    private Transmitter transmitter;
    private SendController sendCont;
    private BufferedWriter logWriter;  // BufferedWriter for efficient CSV logging
     
    private boolean connectionIndicatorOn;
    private boolean connected;
    private static final int MAX_CHANNELS = 20;
    private static final String ZERO_VALUE = "ZEROVALUE";
    private static final String ERROR_CODE_SIGNAL_IDENTIFIER = "JSSD_FLOAT_Error_Code";
    private static final String ERROR_CODE_TEXT_UNAVAILABLE = "ERR N/A";
    private static final String ERROR_CODE_TEXT_ACTIVE = "ERR ACTIVE";
    private static final String ERROR_CODE_TEXT_LATCHED_PREFIX = "LAST ERR: ";
    private static final String ERROR_CODE_TEXT_NO_ERROR = "NO ERROR";
    private static final String ERROR_CODE_TEXT_PREFIX = "ERR: ";
    private static final int ERROR_STATUS_BIT = 2;
    private static final Color ERROR_CODE_COLOR_UNKNOWN = new Color(180, 180, 180);
    private static final Color ERROR_CODE_COLOR_OK = new Color(80, 200, 120);
    private static final Color ERROR_CODE_COLOR_ACTIVE = new Color(255, 70, 70);
    private static final Color ERROR_CODE_COLOR_LATCHED = new Color(255, 170, 0);
    private static final String FAST_DATA_DISABLED_HEADER_PAD = ";;;;;;;;;;;;;;;;;;;;;";
    private static final String FAST_DATA_DISABLED_ROW_PAD = ";;;;;;;;;;;;;;;;;;;;";
    private static final int MAX_SAMPLE_RATE_HZ = 200000;
    private static final int DEFAULT_SCOPE_RING_BUFFER_SAMPLES = 5000;
    private static final int AUTO_DETECT_CONNECT_DELAY_MS = 5000;
    private static final int AUTO_DETECT_WINDOW_MS = 5000;
    private static final double AUTO_DETECT_SNAP_TOLERANCE = 0.05; // 5% snap-to-nominal tolerance
    private static final double LOG_TIME_ROUNDING_SCALE = 100_000_000.0; // 10 ns resolution in seconds
    private enum AcquisitionMode { AUTO, NORMAL, SINGLE }
    private enum AcquisitionState { RUNNING, ARMED, TRIGGERED, STOPPED }
    private boolean loggingOnOff, savingData, slowDataLogOnOff, fastDataLogOnOff, extLoggingOnOff;   // true=on, false=off
    private ChartPanel chPanel;
    private boolean pendingGraphUpdate;
    private volatile double[][] lastRenderedSnapshot;
    private AcquisitionMode acquisitionMode;
    private AcquisitionState acquisitionState;
    long lastTimestamp;
    
    private ScopeRingBuffer scopeRingBuffer;
    CrosshairOverlay crosshairOverlay;
    
    int chnum;
    
    double[] myIQfactor;
    
    double[] myIQfactor_CHx;
    double[] scaleCHx;
    double[] offsetCHx;
    
    
    int ringReadPtr;  // Snapshot of ring buffer write pointer for chart updates
    double[] newvals;  // reusable array for per-sample values (avoids allocation in hot loop)
    double[][] chdata;  // reusable array for per-packet channel data (avoids allocation per packet)
    XYSeries[] chartSeries;  // Preallocated chart series (reused each update)
    XYSeriesCollection chartDataset;  // Preallocated dataset (reused each update)

    private javax.swing.JToggleButton[] channelVisibilityButtons;
    private java.awt.Color[] channelVisibilityColors;
    private static final Color CHANNEL_DISABLED_COLOR = new Color(120, 120, 120);
    private static final Color LEGEND_VISIBLE_COLOR = new Color(66, 201, 76);
    private static final Color SCALE_OFFSET_INVALID_COLOR = new Color(255, 70, 70);
    private JTextField[] scaleFields;
    private JTextField[] offsetFields;
    private List<javax.swing.JComboBox<String>> channelSelectCombos;
    private List<javax.swing.AbstractButton> scalePlusButtons;
    private List<javax.swing.AbstractButton> scaleMinusButtons;
    private boolean[] logZeroValueChannelSelection;
    private boolean logChannelSelectionDirty;
    private StringBuilder logPacketBuilder;
    private boolean logHeaderWritten;
    private int[] slowDataLogColumnByIndex;
    private long[] slowDataLogEventCounts;
    private int loggedSlowDataColumnCount;
    private long slowDataLogInvalidIdCount;
    private double logTimeStep_usec;
    private boolean suppressSlowLoggingSessionSummary;
    private final Object logWriteLock = new Object();
    private final Map<Object, Runnable> scaleButtonActions = new IdentityHashMap<>();
    private Font scaleOffsetBaseFont;
    private Color scaleOffsetBaseColor;
    private Font triggerValueBaseFont;
    private Color triggerValueBaseColor;
    private boolean scaleOffsetListenersInitialized;
    private boolean triggerControlsInitialized;
    private boolean timeBaseControlsInitialized;
    private boolean channelSelectListenersInitialized;
    private boolean suppressSelectDataEvents;
    int scopeChannelNumber;
    double manualTimeStep_usec;
    double smallestTimeStep_usec;
    int timeFactor;
    volatile int logFactor;
    int dataPointCounter;
    long lastSystemMillis, generalDataCounter, lastSystemMillisSlowData;
    long slowDataContent[];
    ArrayList<String> slowDataIntOrFloat;
    ArrayList<String> slowDataSignalNames;
    private List<javax.swing.JTextField> sendFields;
    private List<javax.swing.JTextField> rcvFields;
    private List<MovingAverage> movingAverage;
    int screenRefreshTime;
    
    int triggermode;    // 0=auto, then CH1-rising=1, CH1-falling=2, CH2-rising=3, ...
    boolean trigOccured;
    boolean triggerCaptureComplete;
    double triggervalue, pretrigger, triggerLastCompareValue, triggerLastCompareValue2;
    boolean triggerCompareValid;
    int dataPointCounter_trigOccured; // 0-based index of the trigger sample in decimated scope data
    private AnzeigeDaten adata;
    private boolean is_first_call, update_func_runs;  
    private long time_stamp_connect;
    private long lastStatus = Long.MIN_VALUE;
    private long ledLastStatus = Long.MIN_VALUE;  // For LED change detection (updated after LED checks)
    private boolean autoDetectSamplingRate;
    private boolean forceSamplingDetect;
    private boolean pauseAckCommandEnabled;
    private boolean samplingRateLocked;
    private long samplingDetectStartMs;
    private long samplingDetectPacketCount;
    private boolean samplingDetectStarted;
    private long samplingDetectDelayUntilMs;
    private long packetRateWindowStartMs;
    private long packetRateCount;
    private int packetRateBelowCount;
    private double[] packetRateRatioWindow;
    private int packetRateRatioIndex;
    private int packetRateRatioCount;
    private long throughputWindowStartMs;
    private long throughputWindowBytes;
    private boolean lifecheckMonitorEnabled;
    private int[] lifecheckSlotByChannelIndex;
    private int[] lifecheckPreviousValues;
    private boolean[] lifecheckHasPrevious;
    private String[] lifecheckSignalNames;
    private long lifecheckErrorCount;
    private ArrayDeque<String> lifecheckRecentErrors;
    private boolean lifecheckErrorLatched;
    
    private NumberFormat numberFormatPrecision8;
    private NumberFormat numberFormatTwoDecimals;
    private NumberFormat numberFormatThreeDecimals;
    private NumberFormat numberFormatNoDecimals;
    private DefaultTableModel slowDataTableModel;
    //Moving Average
    private float errorCode; 
    private boolean errorCodeKnown;
    private int errorCodeSlowDataIndex = -1;
    MovingAverage errorCodeAverage = new MovingAverage(1);

    int[] JSSD_indices;
    
    boolean AutoMeasure = false;
    boolean FirstTimeAutoMeasure = true;
    
    private int n_max;
    public float ActiveState;
    public float cest;
    public float cest0;
    public float dest;
    public float LoadInertia;
    public float MotorInertia;
    public float Wtemp;
    private long LookAndFeel_timestamp;
    

    
    public ReceiveController(UZ_GUI_view view, UZ_SCOPE_view viewSCOPE,  Transmitter transmitter, SendController sendCont, ChartPanel chPanel, int chnum, Properties prop)
     {
        connected = false;
        
        pendingGraphUpdate = false;
        acquisitionMode = AcquisitionMode.AUTO;
        acquisitionState = AcquisitionState.STOPPED;
        
        this.view = view;
        this.viewSCOPE = viewSCOPE;
        this.transmitter = transmitter;
        this.sendCont = sendCont;
        transmitter.addListener(this);
        view.addWindowListener(this);
        this.chPanel = chPanel;
        this.chPanel.addChartMouseListener(chartMouseListener);
        installDomainResetHook();
        crosshairOverlay = new CrosshairOverlay();
        
        this.chnum = chnum;
        chdata = new double[chnum][transmitter.ANZAHL_MESSREIHEN_PRO_TCP_PAKET];  // preallocate for per-packet data

        ringBufferSamples = DEFAULT_SCOPE_RING_BUFFER_SAMPLES; // number of samples in scope ring buffer

        // Preallocate chart objects (reused each update, updated on EDT)
        chartSeries = new XYSeries[chnum];
        chartDataset = new XYSeriesCollection();
        for (int seriesIndex = 0; seriesIndex < chnum; seriesIndex++) {
            chartSeries[seriesIndex] = new XYSeries("CH" + (seriesIndex + 1), false);  // false = don't auto-sort (faster)
            chartDataset.addSeries(chartSeries[seriesIndex]);
        }
        // Avoid recreating datasets during updates; keep one dataset bound to the plot
        chPanel.getChart().getXYPlot().setDataset(chartDataset);
        configureDomainAxis();
        System.out.println("ANZAHL KANÄLE: " + chnum);

        initChannelVisibilityButtons();
        initChannelComponentArrays();
        initScaleButtonActions();
                
        view.getBtnRunStop().addActionListener(this);
        view.getBtnSingleShot().addActionListener(this);
        view.getBtnFixAxis().addActionListener(this);
        view.getCombo_LogNthValue().addActionListener(this);
        initFieldCollections();
        initMovingAverages();
                    
        
        view.getBtnDetectSamplingRate().addActionListener(this);
        if (viewSCOPE.getBtnScopeDevDetectSamplingRate() != null) {
            viewSCOPE.getBtnScopeDevDetectSamplingRate().addActionListener(this);
        }
        if (viewSCOPE.getBtnScopeDevPauseAck() != null) {
            viewSCOPE.getBtnScopeDevPauseAck().addActionListener(this);
        }
        if (viewSCOPE.getBtnScopeDevPrintSentCommands() != null) {
            viewSCOPE.getBtnScopeDevPrintSentCommands().addActionListener(this);
        }
        if (viewSCOPE.getBtnScopeDevSingleInstanceGuard() != null) {
            viewSCOPE.getBtnScopeDevSingleInstanceGuard().addActionListener(this);
        }
        if (viewSCOPE.getBtnScopeDevLifecheckMonitor() != null) {
            viewSCOPE.getBtnScopeDevLifecheckMonitor().addActionListener(this);
        }
        view.getBtnDisconnect().addActionListener(this);
        view.getBtnLogOnOff().addActionListener(this);
        view.getBtnChange_fastDataLog().addActionListener(this);
        view.getBtnChange_slowDataLog().addActionListener(this);
        view.getBtnSet_extLogging().addActionListener(this);
        view.getBtnConnect().addActionListener(this);
        view.getBtnSaveSettings().addActionListener(this);
        
        for (javax.swing.AbstractButton button : scalePlusButtons) {
            if (button != null) {
                button.addActionListener(this);
            }
        }
        for (javax.swing.AbstractButton button : scaleMinusButtons) {
            if (button != null) {
                button.addActionListener(this);
            }
        }
        
        //NumberFormat zur Darstellung der Nachkommastellen
        numberFormatPrecision8 = NumberFormat.getInstance(Locale.US);
        numberFormatPrecision8.setMaximumFractionDigits(8);
        numberFormatTwoDecimals = NumberFormat.getInstance(Locale.US);
        numberFormatTwoDecimals.setMaximumFractionDigits(2);
        numberFormatThreeDecimals = NumberFormat.getInstance(Locale.US);
        numberFormatThreeDecimals.setMaximumFractionDigits(3);
        numberFormatNoDecimals = NumberFormat.getInstance(Locale.US);
        numberFormatNoDecimals.setMaximumFractionDigits(0);
        
        

        
        scopeRingBuffer = new ScopeRingBuffer(chnum, ringBufferSamples);
                
        myIQfactor = new double[] {1.0, 2.0, 4.0, 8.0, 16.0, 32.0, 64.0, 128.0, 256.0, 512.0, 1024.0, 2048.0, 4096.0, 8192.0, 16384.0};
        myIQfactor_CHx = new double[]{32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0, 32.0};  // 4 channels but now extended to 20 channels

        

        scaleCHx = new double[chnum];
        Arrays.fill(scaleCHx, 1);
        
        offsetCHx = new double[chnum];
        Arrays.fill(offsetCHx, 0);
        
        // read init values from properties.
        String[] valuesScale = getPropertyTokens(prop, "initScaleCHx");
        for (int scaleIndex = 0; scaleIndex < valuesScale.length && scaleIndex < chnum; scaleIndex++)
        {
            scaleCHx[scaleIndex] = parseDoubleListEntry("initScaleCHx", valuesScale[scaleIndex], scaleIndex + 1, scaleCHx[scaleIndex]);
        }
        for (int channelIndex = 0; channelIndex < Math.min(chnum, scaleFields.length); channelIndex++) {
            scaleFields[channelIndex].setText("" + scaleCHx[channelIndex]);
        }
        String[] valuesOffset = getPropertyTokens(prop, "initOffsetCHx");
        for (int offsetIndex = 0; offsetIndex < valuesOffset.length && offsetIndex < chnum; offsetIndex++)
        {
            offsetCHx[offsetIndex] = parseDoubleListEntry("initOffsetCHx", valuesOffset[offsetIndex], offsetIndex + 1, offsetCHx[offsetIndex]);
        }
        for (int channelIndex = 0; channelIndex < Math.min(chnum, offsetFields.length); channelIndex++) {
            offsetFields[channelIndex].setText("" + offsetCHx[channelIndex]);
        }

        initScaleOffsetFields();
        initTriggerControls();
        initTimeBaseControls();
        
        
        manualTimeStep_usec = getDoubleProperty(prop, "smallestTimeStepUSEC", 100.0);     // usec
        smallestTimeStep_usec = manualTimeStep_usec;
        if (smallestTimeStep_usec > 0) {
            updateSamplingRateDisplay(1_000_000.0 / smallestTimeStep_usec);
        }
        resetPacketRateMonitor();
        autoDetectSamplingRate = getBooleanProperty(prop, "autoDetectSamplingRate", false);
        boolean sendZeroAckCommand = getBooleanProperty(prop, "sendZeroAckCommand", true);
        applyPauseAckCommandEnabled(!sendZeroAckCommand, false);
        updateScopeDevPrintSentCommandsButtonState();
        updateScopeDevSingleInstanceGuardButtonState();
        resetThroughputMonitor();
        scopeChannelNumber = getIntProperty(prop, "scopeChannelNumber", chnum); 
        timeFactor = 1;     // 1= plot each data point, 10=every 10th, and so on
        logFactor = 1;
        updateLogFactorFromSelection();
        dataPointCounter = 0;
        generalDataCounter = 0;
        if (autoDetectSamplingRate) {
            resetSamplingRateDetection();
        }
        updateLogOnOffButtonState();
        screenRefreshTime = 1000;
        lastTimestamp = 0;
        lastSystemMillis = System.currentTimeMillis();
        lastSystemMillisSlowData = lastSystemMillis;
        String triggerModeRaw = prop.getProperty("triggerMode");
        if (triggerModeRaw != null && prop.getProperty("triggerChannel") == null) {
            triggermode = getIntProperty(prop, "triggerMode", 0);
        } else {
            int triggerChannel = getIntProperty(prop, "triggerChannel", 0);
            int triggerEdge = parseTriggerEdge(prop.getProperty("triggerEdge"), 1);
            triggermode = toTriggerMode(triggerChannel, triggerEdge);
        }
        int triggerModeMax = Math.max(0, 2 * chnum);
        if (triggermode < 0) {
            triggermode = 0;
        } else if (triggermode > triggerModeMax) {
            triggermode = triggerModeMax;
        }
        triggervalue = getDoubleProperty(prop, "triggerValue", 0.0);
        pretrigger = getDoubleProperty(prop, "pretrigger", 0.5);
        if (pretrigger < 0.0) {
            pretrigger = 0.0;
        } else if (pretrigger > 1.0) {
            pretrigger = 1.0;
        }
        acquisitionMode = resolveContinuousAcquisitionMode();
        acquisitionState = AcquisitionState.STOPPED;
        resetTriggerCaptureState();

        syncTriggerUiFromMode();
        view.getTxtTriggerValue().setText(Double.toString(triggervalue));
        view.getSliPreTrigger().setValue((int)Math.round(pretrigger * 10.0));
        
        // ring buffer now serves as the single source of truth for scope data
        newvals = new double[chnum];  // preallocate reusable array
        suppressSelectDataEvents = true;
        readChannelsStringsFromFileLineByLine();
        String[] valuesPreSelectChannels = getPropertyTokens(prop, "preSelectedChannelNumbers");   
        int channelCount = Math.min(chnum, Math.min(channelSelectCombos.size(), valuesPreSelectChannels.length));
        for (int channelIndex = 0; channelIndex < channelCount; channelIndex++) {
            javax.swing.JComboBox<String> combo = channelSelectCombos.get(channelIndex);
            int fallbackIndex = combo.getSelectedIndex();
            if (fallbackIndex < 0) {
                fallbackIndex = 0;
            }
            int selectedIndex = (int) parseDoubleListEntry(
                    "preSelectedChannelNumbers",
                    valuesPreSelectChannels[channelIndex],
                    channelIndex + 1,
                    fallbackIndex
            );
            int maxIndex = combo.getItemCount() - 1;
            if (maxIndex < 0) {
                continue;
            }
            if (selectedIndex < 0 || selectedIndex > maxIndex) {
                propertyDiagnostics.printValidationIssue(
                        "preSelectedChannelNumbers",
                        "Entry " + (channelIndex + 1) + " has out-of-range index " + selectedIndex
                                + " (valid range: 0.." + maxIndex + "). Using " + fallbackIndex + "."
                );
                selectedIndex = fallbackIndex;
            }
            combo.setSelectedIndex(selectedIndex);
        }
        suppressSelectDataEvents = false;
        initChannelSelectListeners();
        
        applyPreSelectedChannelVisibility(prop);
        logZeroValueChannelSelection = new boolean[Math.max(chnum, 1)];
        logChannelSelectionDirty = true;
        logPacketBuilder = new StringBuilder(4096);
        refreshLogChannelSelection();
        slowDataIntOrFloat = new ArrayList<String>();
        slowDataSignalNames = readSlowDataStringsFromFileLineByLine();
        int numberOfSlowDataContents = slowDataSignalNames.size();
        slowDataContent = new long[numberOfSlowDataContents];
        initLifecheckMonitor();
        readSndFieldDespcriptionsFromFileLineByLine();
        readSndFieldLabelsFromFileLineByLine();
        readRcvFieldDespcriptionsFromFileLineByLine();  
        readRcvFieldLabelsFromFileLineByLine();
        readMyButtonsLabelsFromFileLineByLine();       
        JSSD_indices = readRcvFieldSlowDataToDisplayFromFileLineByLine();
        resetErrorCodeState();
        setErrorResetControlEnabled(false);
        
        savingData=false;
        loggingOnOff = false;
        slowDataLogOnOff = false;
        fastDataLogOnOff = true;
        extLoggingOnOff = false;
        logHeaderWritten = false;
        acquisitionState = AcquisitionState.STOPPED;
        update_func_runs = false;
        is_first_call = true;
    }
        
    public void init_LogToFile() throws IOException
    {
        closeLogWriter();
        String fileName = createLogFileName();
        logWriter = new BufferedWriter(new FileWriter(fileName), 65536);  // 64KB buffer
        logHeaderWritten = false;
        logWriter.flush();
        String message = "Created new log file: " + fileName;
        System.out.println(message);
    }

    private void closeLogWriter() throws IOException
    {
        BufferedWriter writerToClose = logWriter;
        logWriter = null;
        if (writerToClose == null) {
            return;
        }
        IOException failure = null;
        try {
            writerToClose.flush();
        } catch (IOException exception) {
            failure = exception;
        }
        try {
            writerToClose.close();
        } catch (IOException exception) {
            if (failure == null) {
                failure = exception;
            } else {
                failure.addSuppressed(exception);
            }
        }
        if (failure != null) {
            throw failure;
        }
    }

    private String createLogFileName()
    {
        Date date = new Date();
        Format formatter = new SimpleDateFormat("yyyy-MM-dd_HH-mm-ss");
        String baseName = "Log_" + formatter.format(date);
        String fileName = baseName + ".csv";
        int suffix = 1;
        while (Files.exists(Paths.get(fileName))) {
            fileName = baseName + "_" + suffix + ".csv";
            suffix++;
        }
        return fileName;
    }

    private boolean startFreshLogFile() {
        try {
            init_LogToFile();
            return true;
        } catch (IOException exception) {
            logger.severe("Failed to initialize log file: " + exception);
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
            return false;
        }
    }

    public boolean writeScopeSettingsToProperties()
    {
        Path path = Paths.get("properties.ini");
        List<String> lines;
        try {
            lines = Files.readAllLines(path, StandardCharsets.UTF_8);
        } catch (IOException exception) {
            logger.severe("Failed to read properties.ini: " + exception);
            return false;
        }

        int channelCount = scopeChannelNumber > 0 ? scopeChannelNumber : chnum;
        channelCount = Math.min(channelCount, chnum);

        int[] selectedIndices = new int[channelCount];
        for (int index = 0; index < channelCount; index++) {
            selectedIndices[index] = getSelectedChannelIndex(index);
        }

        int[] visibility = new int[channelCount];
        XYItemRenderer renderer = chPanel.getChart().getXYPlot().getRenderer();
        for (int index = 0; index < channelCount; index++) {
            Boolean visible = renderer.isSeriesVisible(index);
            visibility[index] = (visible == null || visible) ? 1 : 0;
        }

        int triggerChannel = 0;
        String triggerEdge = "rising";
        if (triggermode > 0) {
            triggerChannel = toTriggerChannel(triggermode);
            triggerEdge = toTriggerEdge(triggermode) == 1 ? "rising" : "falling";
        }

        updatePropertyLine(lines, "smallestTimeStepUSEC", formatDoubleForProperty(smallestTimeStep_usec));
        updatePropertyLine(lines, "autoDetectSamplingRate", autoDetectSamplingRate ? "1" : "0");
        updatePropertyLine(lines, "sendZeroAckCommand", pauseAckCommandEnabled ? "0" : "1");
        updatePropertyLine(lines, "triggerChannel", Integer.toString(triggerChannel));
        updatePropertyLine(lines, "triggerEdge", triggerEdge);
        updatePropertyLine(lines, "triggerValue", formatDoubleForProperty(triggervalue));
        updatePropertyLine(lines, "pretrigger", formatDoubleForProperty(pretrigger));
        updatePropertyLine(lines, "initScaleCHx", formatDoubleListForProperty(scaleCHx, channelCount));
        updatePropertyLine(lines, "initOffsetCHx", formatDoubleListForProperty(offsetCHx, channelCount));
        updatePropertyLine(lines, "preSelectedChannelNumbers", formatIntListForProperty(selectedIndices, channelCount));
        updatePropertyLine(lines, "preSelectedChannelVisibility", formatIntListForProperty(visibility, channelCount));

        try {
            Files.write(path, lines, StandardCharsets.UTF_8);
        } catch (IOException exception) {
            logger.severe("Failed to write properties.ini: " + exception);
            return false;
        }
        return true;
    }
    
    private boolean getBooleanProperty(Properties prop, String key, boolean defaultValue)
    {
        String value = prop.getProperty(key);
        if (value == null) {
            return defaultValue;
        }
        String normalized = value.trim().toLowerCase(Locale.US);
        if (normalized.equals("1") || normalized.equals("true") || normalized.equals("yes") || normalized.equals("on")) {
            return true;
        }
        if (normalized.equals("0") || normalized.equals("false") || normalized.equals("no") || normalized.equals("off")) {
            return false;
        }
        propertyDiagnostics.printInvalidScalar(
                key,
                value,
                "one of 1/0/true/false/yes/no/on/off",
                Boolean.toString(defaultValue)
        );
        return defaultValue;
    }

    private boolean parseVisibilityToken(String value, boolean defaultValue, int oneBasedEntryIndex)
    {
        if (value == null) {
            return defaultValue;
        }
        String normalized = value.trim().toLowerCase(Locale.US);
        if (normalized.isEmpty()) {
            return defaultValue;
        }
        if (normalized.equals("1") || normalized.equals("true") || normalized.equals("yes") || normalized.equals("on")
                || normalized.equals("visible") || normalized.equals("enabled")) {
            return true;
        }
        if (normalized.equals("0") || normalized.equals("false") || normalized.equals("no") || normalized.equals("off")
                || normalized.equals("hidden") || normalized.equals("disabled")) {
            return false;
        }
        propertyDiagnostics.printInvalidListEntry(
                "preSelectedChannelVisibility",
                oneBasedEntryIndex,
                value,
                "one of 1/0/true/false/yes/no/on/off/visible/hidden",
                Boolean.toString(defaultValue)
        );
        return defaultValue;
    }

    private void applyPreSelectedChannelVisibility(Properties prop)
    {
        if (chPanel == null || chPanel.getChart() == null || chPanel.getChart().getXYPlot() == null) {
            return;
        }
        XYItemRenderer renderer = chPanel.getChart().getXYPlot().getRenderer();
        if (renderer == null) {
            return;
        }

        String visibilitySetting = prop.getProperty("preSelectedChannelVisibility");
        String[] visibilityTokens = visibilitySetting == null ? new String[0] : visibilitySetting.split(";");

        for (int channelIndex = 0; channelIndex < chnum; channelIndex++) {
            boolean defaultVisible = true;
            if (channelSelectCombos != null && channelIndex < channelSelectCombos.size()) {
                defaultVisible = !isZeroValueSelection(channelSelectCombos.get(channelIndex));
            }
            boolean visible = defaultVisible;
            if (channelIndex < visibilityTokens.length) {
                visible = parseVisibilityToken(visibilityTokens[channelIndex], defaultVisible, channelIndex + 1);
            }
            renderer.setSeriesVisible(channelIndex, visible, false);
            updateLegendItemPaint(channelIndex, visible);
            updateChannelToggleAppearance(channelIndex, visible);
        }
        chPanel.repaint();
    }

    private int getIntProperty(Properties prop, String key, int defaultValue)
    {
        String value = prop.getProperty(key);
        if (value == null) {
            return defaultValue;
        }
        try {
            return Integer.parseInt(value.trim());
        } catch (NumberFormatException e) {
            propertyDiagnostics.printInvalidScalar(key, value, "an integer", Integer.toString(defaultValue));
            return defaultValue;
        }
    }

    private double getDoubleProperty(Properties prop, String key, double defaultValue)
    {
        String value = prop.getProperty(key);
        if (value == null) {
            return defaultValue;
        }
        try {
            String normalized = value.trim().replace(',', '.');
            return Double.parseDouble(normalized);
        } catch (NumberFormatException e) {
            propertyDiagnostics.printInvalidScalar(key, value, "a floating-point number", Double.toString(defaultValue));
            return defaultValue;
        }
    }

    private String[] getPropertyTokens(Properties prop, String key)
    {
        String raw = prop.getProperty(key);
        if (raw == null) {
            return new String[0];
        }
        return raw.split(";");
    }

    private double parseDoubleListEntry(String key, String rawValue, int oneBasedEntryIndex, double defaultValue)
    {
        if (rawValue == null) {
            return defaultValue;
        }
        String normalized = rawValue.trim().replace(',', '.');
        if (normalized.isEmpty()) {
            return defaultValue;
        }
        try {
            return Double.parseDouble(normalized);
        } catch (NumberFormatException exception) {
            propertyDiagnostics.printInvalidListEntry(
                    key,
                    oneBasedEntryIndex,
                    rawValue,
                    "a floating-point number",
                    Double.toString(defaultValue)
            );
            return defaultValue;
        }
    }

    private int parseTriggerEdge(String value, int defaultEdge)
    {
        if (value == null) {
            return defaultEdge;
        }
        String normalized = value.trim().toLowerCase(Locale.US);
        if (normalized.equals("1") || normalized.equals("rising") || normalized.equals("rise") || normalized.equals("up")) {
            return 1;
        }
        if (normalized.equals("2") || normalized.equals("falling") || normalized.equals("fall") || normalized.equals("down")) {
            return 2;
        }
        propertyDiagnostics.printInvalidScalar(
                "triggerEdge",
                value,
                "rising/falling (or 1/2)",
                defaultEdge == 2 ? "falling" : "rising"
        );
        return defaultEdge;
    }

    private int toTriggerMode(int triggerChannel, int triggerEdge)
    {
        if (triggerChannel <= 0) {
            return 0;
        }
        int boundedChannel = Math.max(1, Math.min(triggerChannel, chnum));
        int normalizedEdge = (triggerEdge == 2) ? 2 : 1;
        int channelIndex = boundedChannel - 1;
        return (channelIndex * 2) + (normalizedEdge == 1 ? 1 : 2);
    }

    private int toTriggerChannel(int triggerMode)
    {
        if (triggerMode <= 0) {
            return 0;
        }
        int channel = ((triggerMode - 1) / 2) + 1;
        return Math.max(1, Math.min(channel, chnum));
    }

    private int toTriggerEdge(int triggerMode)
    {
        if (triggerMode <= 0) {
            return 1;
        }
        return (triggerMode % 2 == 1) ? 1 : 2;
    }

    private AcquisitionMode resolveContinuousAcquisitionMode()
    {
        return triggermode > 0 ? AcquisitionMode.NORMAL : AcquisitionMode.AUTO;
    }

    private boolean isScopeRunning()
    {
        return acquisitionState != AcquisitionState.STOPPED;
    }

    private boolean isSingleShotActive()
    {
        return acquisitionMode == AcquisitionMode.SINGLE
            && (acquisitionState == AcquisitionState.ARMED || acquisitionState == AcquisitionState.TRIGGERED);
    }

    private boolean isSingleShotArmed()
    {
        return acquisitionMode == AcquisitionMode.SINGLE && acquisitionState == AcquisitionState.ARMED;
    }

    private void resetTriggerCaptureState()
    {
        trigOccured = false;
        triggerCaptureComplete = false;
        dataPointCounter_trigOccured = -1;
        triggerLastCompareValue = 0.0;
        triggerLastCompareValue2 = 0.0;
        triggerCompareValid = false;
    }

    private void updateDomainRange()
    {
        ValueAxis domain = chPanel.getChart().getXYPlot().getDomainAxis();  // x-Achse
        double xStep = smallestTimeStep_usec * 0.000001 * timeFactor;
        double safeStep = xStep > 0.0 ? xStep : 1e-6;
        double upperBound = Math.max(safeStep, (ringBufferSamples+1) * safeStep);
        domain.setLowerMargin(0.0);
        domain.setUpperMargin(0.0);
        domain.setAutoRange(false);
        domain.setRange(0.0, upperBound);
    }

    private void resetScopeBufferForSamplingRateChange()
    {
        if (scopeRingBuffer == null) {
            return;
        }
        // Keep the scope buffer depth stable when the detected sample rate changes.
        // Preserving the stale preset time window collapses the visible span after
        // auto-detection (for example 100 kHz preset -> 10 kHz detected).
        resetScopeBuffer(DEFAULT_SCOPE_RING_BUFFER_SAMPLES);
    }

    private void resetScopeBuffer(int newSamplesPerChannel)
    {
        if (scopeRingBuffer == null || newSamplesPerChannel <= 0) {
            return;
        }
        if (newSamplesPerChannel == ringBufferSamples) {
            scopeRingBuffer.deleteAllChannels();
        } else {
            scopeRingBuffer = new ScopeRingBuffer(chnum, newSamplesPerChannel);
            ringBufferSamples = newSamplesPerChannel;
        }
        ringReadPtr = scopeRingBuffer.snapshotWritePtr();
        dataPointCounter = 0;
        pendingGraphUpdate = false;
        resetTriggerCaptureState();
    }

    private double[][] snapshotScopeBufferData(int writeIndexSnapshot)
    {
        int bufferLen = scopeRingBuffer.getSizePerChannel();
        double[][] dataSnapshot = new double[chnum][bufferLen];
        for (int seriesIndex = 0; seriesIndex < chnum; seriesIndex++) {
            for (int sampleIndex = 0; sampleIndex < bufferLen; sampleIndex++) {
                dataSnapshot[seriesIndex][sampleIndex] = scopeRingBuffer.getValueAt(seriesIndex, sampleIndex, writeIndexSnapshot);
            }
        }
        return dataSnapshot;
    }

    private void renderScopeSnapshot(double[][] dataSnapshot, int bufferLen, double xStep, int currentTriggermode, double currentTriggervalue, double currentPretrigger)
    {
        XYPlot plot = chPanel.getChart().getXYPlot();
        if (plot.getDataset() != chartDataset) {
            plot.setDataset(chartDataset);
        }
        XYItemRenderer renderer = plot.getRenderer();
        boolean[] visibleChannels = new boolean[chnum];
        for (int seriesIndex = 0; seriesIndex < chnum; seriesIndex++) {
            visibleChannels[seriesIndex] = renderer.isSeriesVisible(seriesIndex);
        }
        boolean isDarkMode = true;
        for (int seriesIndex = 0; seriesIndex < chnum; seriesIndex++) {
            chartSeries[seriesIndex].setNotify(false);
            chartSeries[seriesIndex].clear();
            if (visibleChannels[seriesIndex]) {
                for (int sampleIndex = 0; sampleIndex < bufferLen; sampleIndex++) {
                    chartSeries[seriesIndex].add(sampleIndex * xStep, dataSnapshot[seriesIndex][sampleIndex]);
                }
            }
            chartSeries[seriesIndex].setNotify(true);
        }

        updateTriggerOverlay(currentTriggermode, currentTriggervalue, currentPretrigger, xStep, isDarkMode);
        chPanel.repaint();
    }

    private void clearScopeChart()
    {
        final double xStep = smallestTimeStep_usec * 0.000001 * timeFactor;
        final int currentTriggermode = triggermode;
        final double currentTriggervalue = triggervalue;
        final double currentPretrigger = pretrigger;

        SwingUtilities.invokeLater(() -> {
            XYPlot plot = chPanel.getChart().getXYPlot();
            if (plot.getDataset() != chartDataset) {
                plot.setDataset(chartDataset);
            }
            for (int seriesIndex = 0; seriesIndex < chnum; seriesIndex++) {
                chartSeries[seriesIndex].setNotify(false);
                chartSeries[seriesIndex].clear();
                chartSeries[seriesIndex].setNotify(true);
            }
            updateTriggerOverlay(currentTriggermode, currentTriggervalue, currentPretrigger, xStep, true);
            chPanel.repaint();
        });
    }

    private void configureDomainAxis()
    {
        ValueAxis domain = chPanel.getChart().getXYPlot().getDomainAxis();
        if (domain == null) {
            return;
        }
        domain.setLowerMargin(0.0);
        domain.setUpperMargin(0.0);
    }

    private void installDomainResetHook()
    {
        if (chPanel instanceof ScopeChartPanel) {
            ((ScopeChartPanel) chPanel).setDomainResetHook(() -> SwingUtilities.invokeLater(this::updateDomainRange));
        }
    }

    private void updateSamplingRateDisplay(double sampleRateHz)
    {
        final String text = String.format(Locale.US, "sampling rate %.1f kHz", sampleRateHz / 1000.0);
        if (SwingUtilities.isEventDispatchThread()) {
            view.getTxtSamplingRateKHz().setText(text);
        } else {
            SwingUtilities.invokeLater(() -> view.getTxtSamplingRateKHz().setText(text));
        }
    }

    private void updateSamplingRateStatusDisplay(String text, Color color)
    {
        if (SwingUtilities.isEventDispatchThread()) {
            view.getTxtSamplingRateStatus().setText(text);
            view.getTxtSamplingRateStatus().setForeground(color);
        } else {
            SwingUtilities.invokeLater(() -> {
                view.getTxtSamplingRateStatus().setText(text);
                view.getTxtSamplingRateStatus().setForeground(color);
            });
        }
    }

    private String formatDoubleForProperty(double value)
    {
        DecimalFormat df = new DecimalFormat("0.########", DecimalFormatSymbols.getInstance(Locale.US));
        df.setGroupingUsed(false);
        return df.format(value);
    }

    private double roundLogTimestampSeconds(double seconds)
    {
        return Math.rint(seconds * LOG_TIME_ROUNDING_SCALE) / LOG_TIME_ROUNDING_SCALE;
    }

    private String formatDoubleListForProperty(double[] values, int count)
    {
        StringBuilder builder = new StringBuilder(count * 6);
        for (int index = 0; index < count; index++) {
            if (index > 0) {
                builder.append(" ; ");
            }
            builder.append(formatDoubleForProperty(values[index]));
        }
        return builder.toString();
    }

    private String formatIntListForProperty(int[] values, int count)
    {
        StringBuilder builder = new StringBuilder(count * 4);
        for (int index = 0; index < count; index++) {
            if (index > 0) {
                builder.append(" ; ");
            }
            builder.append(values[index]);
        }
        return builder.toString();
    }

    private int getSelectedChannelIndex(int index)
    {
        initChannelComponentArrays();
        if (index < 0 || index >= channelSelectCombos.size()) {
            return 0;
        }
        javax.swing.JComboBox<String> combo = channelSelectCombos.get(index);
        return combo == null ? 0 : combo.getSelectedIndex();
    }

    private void initChannelComponentArrays()
    {
        if (scaleFields == null) {
            scaleFields = new JTextField[] {
                viewSCOPE.getTxtScaleCH1(), viewSCOPE.getTxtScaleCH2(), viewSCOPE.getTxtScaleCH3(), viewSCOPE.getTxtScaleCH4(), viewSCOPE.getTxtScaleCH5(),
                viewSCOPE.getTxtScaleCH6(), viewSCOPE.getTxtScaleCH7(), viewSCOPE.getTxtScaleCH8(), viewSCOPE.getTxtScaleCH9(), viewSCOPE.getTxtScaleCH10(),
                viewSCOPE.getTxtScaleCH11(), viewSCOPE.getTxtScaleCH12(), viewSCOPE.getTxtScaleCH13(), viewSCOPE.getTxtScaleCH14(), viewSCOPE.getTxtScaleCH15(),
                viewSCOPE.getTxtScaleCH16(), viewSCOPE.getTxtScaleCH17(), viewSCOPE.getTxtScaleCH18(), viewSCOPE.getTxtScaleCH19(), viewSCOPE.getTxtScaleCH20()
            };
        }
        if (offsetFields == null) {
            offsetFields = new JTextField[] {
                viewSCOPE.getTxtOffsetCH1(), viewSCOPE.getTxtOffsetCH2(), viewSCOPE.getTxtOffsetCH3(), viewSCOPE.getTxtOffsetCH4(), viewSCOPE.getTxtOffsetCH5(),
                viewSCOPE.getTxtOffsetCH6(), viewSCOPE.getTxtOffsetCH7(), viewSCOPE.getTxtOffsetCH8(), viewSCOPE.getTxtOffsetCH9(), viewSCOPE.getTxtOffsetCH10(),
                viewSCOPE.getTxtOffsetCH11(), viewSCOPE.getTxtOffsetCH12(), viewSCOPE.getTxtOffsetCH13(), viewSCOPE.getTxtOffsetCH14(), viewSCOPE.getTxtOffsetCH15(),
                viewSCOPE.getTxtOffsetCH16(), viewSCOPE.getTxtOffsetCH17(), viewSCOPE.getTxtOffsetCH18(), viewSCOPE.getTxtOffsetCH19(), viewSCOPE.getTxtOffsetCH20()
            };
        }
        if (channelSelectCombos == null) {
            channelSelectCombos = Arrays.asList(
                viewSCOPE.getComboSelectData1(), viewSCOPE.getComboSelectData2(), viewSCOPE.getComboSelectData3(), viewSCOPE.getComboSelectData4(),
                viewSCOPE.getComboSelectData5(), viewSCOPE.getComboSelectData6(), viewSCOPE.getComboSelectData7(), viewSCOPE.getComboSelectData8(),
                viewSCOPE.getComboSelectData9(), viewSCOPE.getComboSelectData10(), viewSCOPE.getComboSelectData11(), viewSCOPE.getComboSelectData12(),
                viewSCOPE.getComboSelectData13(), viewSCOPE.getComboSelectData14(), viewSCOPE.getComboSelectData15(), viewSCOPE.getComboSelectData16(),
                viewSCOPE.getComboSelectData17(), viewSCOPE.getComboSelectData18(), viewSCOPE.getComboSelectData19(), viewSCOPE.getComboSelectData20()
            );
        }
        if (scalePlusButtons == null) {
            scalePlusButtons = Arrays.asList(
                viewSCOPE.getBtnScalePlusCH1(), viewSCOPE.getBtnScalePlusCH2(), viewSCOPE.getBtnScalePlusCH3(), viewSCOPE.getBtnScalePlusCH4(),
                viewSCOPE.getBtnScalePlusCH5(), viewSCOPE.getBtnScalePlusCH6(), viewSCOPE.getBtnScalePlusCH7(), viewSCOPE.getBtnScalePlusCH8(),
                viewSCOPE.getBtnScalePlusCH9(), viewSCOPE.getBtnScalePlusCH10(), viewSCOPE.getBtnScalePlusCH11(), viewSCOPE.getBtnScalePlusCH12(),
                viewSCOPE.getBtnScalePlusCH13(), viewSCOPE.getBtnScalePlusCH14(), viewSCOPE.getBtnScalePlusCH15(), viewSCOPE.getBtnScalePlusCH16(),
                viewSCOPE.getBtnScalePlusCH17(), viewSCOPE.getBtnScalePlusCH18(), viewSCOPE.getBtnScalePlusCH19(), viewSCOPE.getBtnScalePlusCH20()
            );
        }
        if (scaleMinusButtons == null) {
            scaleMinusButtons = Arrays.asList(
                viewSCOPE.getBtnScaleMinusCH1(), viewSCOPE.getBtnScaleMinusCH2(), viewSCOPE.getBtnScaleMinusCH3(), viewSCOPE.getBtnScaleMinusCH4(),
                viewSCOPE.getBtnScaleMinusCH5(), viewSCOPE.getBtnScaleMinusCH6(), viewSCOPE.getBtnScaleMinusCH7(), viewSCOPE.getBtnScaleMinusCH8(),
                viewSCOPE.getBtnScaleMinusCH9(), viewSCOPE.getBtnScaleMinusCH10(), viewSCOPE.getBtnScaleMinusCH11(), viewSCOPE.getBtnScaleMinusCH12(),
                viewSCOPE.getBtnScaleMinusCH13(), viewSCOPE.getBtnScaleMinusCH14(), viewSCOPE.getBtnScaleMinusCH15(), viewSCOPE.getBtnScaleMinusCH16(),
                viewSCOPE.getBtnScaleMinusCH17(), viewSCOPE.getBtnScaleMinusCH18(), viewSCOPE.getBtnScaleMinusCH19(), viewSCOPE.getBtnScaleMinusCH20()
            );
        }
    }

    private void initScaleButtonActions()
    {
        initChannelComponentArrays();
        if (!scaleButtonActions.isEmpty()) {
            return;
        }
        for (int channelIndex = 0; channelIndex < scalePlusButtons.size(); channelIndex++) {
            final int index = channelIndex;
            javax.swing.AbstractButton plusButton = scalePlusButtons.get(channelIndex);
            if (plusButton != null) {
                scaleButtonActions.put(plusButton, () -> ScalePlusMinusButton(index, 1));
            }
            javax.swing.AbstractButton minusButton = scaleMinusButtons.get(channelIndex);
            if (minusButton != null) {
                scaleButtonActions.put(minusButton, () -> ScalePlusMinusButton(index, 0));
            }
        }
    }

    private boolean handleScaleButtonAction(Object source)
    {
        Runnable action = scaleButtonActions.get(source);
        if (action == null) {
            return false;
        }
        action.run();
        return true;
    }

    private void updatePropertyLine(List<String> lines, String key, String value)
    {
        String keyNormalized = key.trim();
        for (int lineIndex = 0; lineIndex < lines.size(); lineIndex++) {
            String line = lines.get(lineIndex);
            String trimmed = line.trim();
            if (trimmed.isEmpty() || trimmed.startsWith("#") || trimmed.startsWith("!")) {
                continue;
            }
            int eqIndex = line.indexOf('=');
            if (eqIndex < 0) {
                continue;
            }
            String lineKey = line.substring(0, eqIndex).trim();
            if (lineKey.equals(keyNormalized)) {
                lines.set(lineIndex, keyNormalized + " = " + value);
                return;
            }
        }
        lines.add(keyNormalized + " = " + value);
    }

    private void updateDetectSamplingButtonState()
    {
        boolean enabled = connected && !loggingOnOff;
        view.getBtnDetectSamplingRate().setEnabled(enabled);
        if (viewSCOPE.getBtnScopeDevDetectSamplingRate() != null) {
            viewSCOPE.getBtnScopeDevDetectSamplingRate().setEnabled(enabled);
        }
    }

    private void updateLogOnOffButtonState()
    {
        boolean rateKnown = !autoDetectSamplingRate || samplingRateLocked;
        view.getBtnLogOnOff().setEnabled(rateKnown && !extLoggingOnOff);
    }

    private void setPauseAckCommandEnabled(boolean enabled)
    {
        applyPauseAckCommandEnabled(enabled, true);
    }

    private void markLogChannelSelectionDirty()
    {
        logChannelSelectionDirty = true;
        synchronized (logWriteLock) {
            if (loggingOnOff) {
                logHeaderWritten = false;
            }
        }
    }

    private void refreshLogChannelSelection()
    {
        if (!logChannelSelectionDirty) {
            return;
        }
        if (logZeroValueChannelSelection == null || logZeroValueChannelSelection.length < chnum) {
            logZeroValueChannelSelection = new boolean[Math.max(chnum, 1)];
        }
        initChannelComponentArrays();
        int channelCount = Math.min(chnum, channelSelectCombos.size());
        for (int channelIndex = 0; channelIndex < channelCount; channelIndex++) {
            logZeroValueChannelSelection[channelIndex] = isZeroValueSelection(channelSelectCombos.get(channelIndex));
        }
        for (int channelIndex = channelCount; channelIndex < logZeroValueChannelSelection.length; channelIndex++) {
            logZeroValueChannelSelection[channelIndex] = false;
        }
        logChannelSelectionDirty = false;
    }

    private void updateLogFactorFromSelection()
    {
        int selectedIndex = view.getCombo_LogNthValue().getSelectedIndex();
        if (selectedIndex < 0 || selectedIndex >= LOGBASE_FACTORS.length) {
            logFactor = 1;
            return;
        }
        logFactor = LOGBASE_FACTORS[selectedIndex];
    }

    private void applyPauseAckCommandEnabled(boolean enabled, boolean sendImmediateAckOnResume)
    {
        pauseAckCommandEnabled = enabled;
        if (transmitter != null) {
            transmitter.setSuppressZeroCommandReplies(enabled);
            if (sendImmediateAckOnResume && !enabled) {
                transmitter.sendImmediateZeroCommand();
            }
        }
        updateScopeDevPauseAckButtonState();
        updateDetectSamplingButtonState();
    }

    private void updateScopeDevPauseAckButtonState()
    {
        if (viewSCOPE.getBtnScopeDevPauseAck() == null) {
            return;
        }
        viewSCOPE.getBtnScopeDevPauseAck().setText(
                pauseAckCommandEnabled
                        ? "pause 0x00 ack commands: ON"
                        : "pause 0x00 ack commands: OFF"
        );
    }

    private void updateScopeDevPrintSentCommandsButtonState()
    {
        if (viewSCOPE.getBtnScopeDevPrintSentCommands() == null) {
            return;
        }
        boolean enabled = transmitter != null && transmitter.isPrintSentCommandsEnabled();
        viewSCOPE.getBtnScopeDevPrintSentCommands().setText(
                enabled
                        ? "printSentCommands: ON"
                        : "printSentCommands: OFF"
        );
    }

    private void updateScopeDevSingleInstanceGuardButtonState()
    {
        if (viewSCOPE.getBtnScopeDevSingleInstanceGuard() == null) {
            return;
        }
        boolean enabled = transmitter != null && transmitter.isSingleInstanceSocketGuardEnabled();
        viewSCOPE.getBtnScopeDevSingleInstanceGuard().setText(
                enabled
                        ? "single-instance guard: ON"
                        : "single-instance guard: OFF"
        );
    }

    private void resetThroughputMonitor()
    {
        throughputWindowStartMs = 0;
        throughputWindowBytes = 0;
        updateScopeDevThroughputDisplay(0.0);
    }

    private void updateThroughputMonitor(long nowMs)
    {
        if (transmitter == null) {
            return;
        }
        int packetBytes = transmitter.getExpectedPacketBytes();
        if (packetBytes <= 0) {
            return;
        }
        if (throughputWindowStartMs == 0) {
            throughputWindowStartMs = nowMs;
            throughputWindowBytes = 0;
        }
        throughputWindowBytes += packetBytes;
        long elapsedMs = nowMs - throughputWindowStartMs;
        if (elapsedMs < THROUGHPUT_WINDOW_MS) {
            return;
        }
        double elapsedSec = elapsedMs / 1000.0;
        double throughputMbitPerSec = (throughputWindowBytes * 8.0) / (elapsedSec * 1_000_000.0);
        updateScopeDevThroughputDisplay(throughputMbitPerSec);
        throughputWindowStartMs = nowMs;
        throughputWindowBytes = 0;
    }

    private void updateScopeDevThroughputDisplay(double throughputMbitPerSec)
    {
        if (viewSCOPE.getTxtScopeDevThroughput() == null) {
            return;
        }
        final String text = String.format(Locale.US, "%.2f MBit/s", throughputMbitPerSec);
        if (SwingUtilities.isEventDispatchThread()) {
            viewSCOPE.getTxtScopeDevThroughput().setText(text);
        } else {
            SwingUtilities.invokeLater(() -> viewSCOPE.getTxtScopeDevThroughput().setText(text));
        }
    }

    private void setScopeDevStatusBackground(javax.swing.JTextField field, Color color)
    {
        if (field != null) {
            field.setBackground(color);
        }
    }

    private void initLifecheckMonitor()
    {
        lifecheckMonitorEnabled = false;
        refreshLifecheckMonitorSignalsFromSelectedChannels();
        updateScopeDevLifecheckMonitorButtonState();
    }

    private void refreshLifecheckMonitorSignalsFromSelectedChannels()
    {
        initChannelComponentArrays();
        int channelCount = Math.max(chnum, 0);
        lifecheckSlotByChannelIndex = new int[channelCount];
        Arrays.fill(lifecheckSlotByChannelIndex, -1);

        ArrayList<String> detectedSignals = new ArrayList<>();
        int comboCount = channelSelectCombos == null ? 0 : channelSelectCombos.size();
        int monitoredChannels = Math.min(channelCount, comboCount);
        for (int channelIndex = 0; channelIndex < monitoredChannels; channelIndex++) {
            String selectedLabel = getSelectedChannelLabel(channelIndex);
            String signalName = extractSignalNameFromChannelLabel(selectedLabel);
            if (!isLifecheckSignalName(signalName)) {
                continue;
            }
            lifecheckSlotByChannelIndex[channelIndex] = detectedSignals.size();
            detectedSignals.add("CH" + (channelIndex + 1) + "=" + signalName);
        }

        lifecheckSignalNames = detectedSignals.toArray(new String[0]);
        lifecheckPreviousValues = new int[lifecheckSignalNames.length];
        lifecheckHasPrevious = new boolean[lifecheckSignalNames.length];
        resetLifecheckMonitorState();
    }

    private String extractSignalNameFromChannelLabel(String channelLabel)
    {
        if (channelLabel == null) {
            return "";
        }
        String trimmed = channelLabel.trim();
        int indexSeparator = trimmed.indexOf(')');
        if (indexSeparator >= 0 && indexSeparator + 1 < trimmed.length()) {
            return trimmed.substring(indexSeparator + 1).trim();
        }
        return trimmed;
    }

    private boolean isLifecheckSignalName(String signalName)
    {
        if (signalName == null) {
            return false;
        }
        String normalized = signalName.trim().toLowerCase(Locale.US);
        if (normalized.contains("lifecheck")) {
            return true;
        }
        if (!normalized.startsWith("cnt_") || normalized.length() <= 4) {
            return false;
        }
        for (int index = 4; index < normalized.length(); index++) {
            if (!Character.isDigit(normalized.charAt(index))) {
                return false;
            }
        }
        return true;
    }

    private void setLifecheckMonitorEnabled(boolean enabled)
    {
        lifecheckMonitorEnabled = enabled;
        refreshLifecheckMonitorSignalsFromSelectedChannels();
        updateScopeDevLifecheckMonitorButtonState();
    }

    private void resetLifecheckMonitorState()
    {
        if (lifecheckHasPrevious != null) {
            Arrays.fill(lifecheckHasPrevious, false);
        }
        if (lifecheckRecentErrors == null) {
            lifecheckRecentErrors = new ArrayDeque<>();
        } else {
            lifecheckRecentErrors.clear();
        }
        lifecheckErrorCount = 0;
        lifecheckErrorLatched = false;
        updateScopeDevLifecheckDisplay();
    }

    private void updateScopeDevLifecheckMonitorButtonState()
    {
        if (viewSCOPE.getBtnScopeDevLifecheckMonitor() == null) {
            return;
        }
        viewSCOPE.getBtnScopeDevLifecheckMonitor().setText(
                lifecheckMonitorEnabled
                        ? "lifecheck monitor: ON"
                        : "lifecheck monitor: OFF"
        );
    }

    private void processLifecheckSample(int channelIndex, double rawValue)
    {
        if (!lifecheckMonitorEnabled || lifecheckSignalNames == null || lifecheckSlotByChannelIndex == null) {
            return;
        }
        if (channelIndex < 0 || channelIndex >= lifecheckSlotByChannelIndex.length) {
            return;
        }
        int slot = lifecheckSlotByChannelIndex[channelIndex];
        if (slot < 0 || slot >= lifecheckSignalNames.length) {
            return;
        }

        String signalName = lifecheckSignalNames[slot];
        Integer maybeValue = decodeLifecheckValue(rawValue);
        if (maybeValue == null) {
            reportLifecheckError(signalName, "non-numeric value");
            return;
        }
        int value = maybeValue.intValue();
        if (value < 0 || value > LIFECHECK_MAX_VALUE) {
            reportLifecheckError(signalName, "out of range: " + value);
            lifecheckPreviousValues[slot] = value;
            lifecheckHasPrevious[slot] = true;
            return;
        }

        if (!lifecheckHasPrevious[slot]) {
            lifecheckPreviousValues[slot] = value;
            lifecheckHasPrevious[slot] = true;
            return;
        }

        int prevValue = lifecheckPreviousValues[slot];
        boolean wrapped = (prevValue == 999 || prevValue == 1000) && value == 0;
        if (!wrapped) {
            int expected = prevValue + 1;
            if (value != expected) {
                int lost;
                if (prevValue == 999 || prevValue == 1000) {
                    lost = value;
                } else if (value > prevValue) {
                    lost = value - prevValue - 1;
                } else {
                    lost = (LIFECHECK_MAX_VALUE - prevValue) + value;
                }
                reportLifecheckError(
                        signalName,
                        String.format(Locale.US, "gap %d -> %d (missed %d)", prevValue, value, lost)
                );
            }
        }

        lifecheckPreviousValues[slot] = value;
    }

    private Integer decodeLifecheckValue(double rawValue)
    {
        if (!Double.isFinite(rawValue)) {
            return null;
        }
        if (rawValue > Integer.MAX_VALUE || rawValue < Integer.MIN_VALUE) {
            return null;
        }
        return (int) rawValue;
    }

    private void reportLifecheckError(String signalName, String details)
    {
        lifecheckErrorCount++;
        lifecheckErrorLatched = true;
        if (lifecheckRecentErrors == null) {
            lifecheckRecentErrors = new ArrayDeque<>();
        }
        String compactSignal = compactLifecheckSignal(signalName);
        String timestamp = LocalTime.now().format(LIFECHECK_TIME_FORMATTER);
        String message = timestamp + " " + compactSignal + " " + details;
        lifecheckRecentErrors.addFirst(message);
        updateScopeDevLifecheckDisplay();
    }

    private String compactLifecheckSignal(String signalName)
    {
        if (signalName == null) {
            return "?";
        }
        int splitIndex = signalName.indexOf('=');
        if (splitIndex > 0) {
            return signalName.substring(0, splitIndex);
        }
        return signalName;
    }

    private void updateScopeDevLifecheckDisplay()
    {
        javax.swing.JTextField statusField = viewSCOPE.getTxtScopeDevLifecheckStatus();
        javax.swing.JList<String> errorList = viewSCOPE.getListScopeDevLifecheckErrors();
        if (statusField == null || errorList == null) {
            return;
        }

        final String statusText;
        final String[] errorItems;
        final Color statusColor;
        if (lifecheckSignalNames == null || lifecheckSignalNames.length == 0) {
            statusText = "NO SIG";
            errorItems = new String[] {"Select a lifecheck channel"};
            statusColor = Color.GRAY;
        } else if (!lifecheckMonitorEnabled) {
            statusText = "OFF";
            errorItems = new String[] {"Monitoring disabled"};
            statusColor = Color.GRAY;
        } else if (lifecheckErrorLatched) {
            statusText = "GAPS: " + lifecheckErrorCount;
            if (lifecheckRecentErrors == null || lifecheckRecentErrors.isEmpty()) {
                errorItems = new String[] {"-"};
            } else {
                errorItems = lifecheckRecentErrors.toArray(new String[0]);
            }
            statusColor = Color.RED;
        } else {
            statusText = "OK";
            errorItems = new String[] {"No gaps detected"};
            statusColor = new Color(0, 128, 0);
        }

        Runnable updateUi = () -> {
            statusField.setText(statusText);
            statusField.setForeground(statusColor);
            errorList.setListData(errorItems);
        };

        if (SwingUtilities.isEventDispatchThread()) {
            updateUi.run();
        } else {
            SwingUtilities.invokeLater(updateUi);
        }
    }

    private void resetPacketRateMonitor()
    {
        packetRateWindowStartMs = 0;
        packetRateCount = 0;
        packetRateBelowCount = 0;
        if (packetRateRatioWindow == null || packetRateRatioWindow.length != PACKET_RATE_AVG_WINDOWS) {
            packetRateRatioWindow = new double[PACKET_RATE_AVG_WINDOWS];
        }
        packetRateRatioIndex = 0;
        packetRateRatioCount = 0;
        updateSamplingRateStatusDisplay("throughput n/a", Color.GRAY);
    }

    private void updatePacketRateStatus(long nowMs, int samplesPerPacket)
    {
        if (smallestTimeStep_usec <= 0 || samplesPerPacket <= 0) {
            updateSamplingRateStatusDisplay("throughput n/a", Color.GRAY);
            return;
        }
        if (packetRateWindowStartMs == 0) {
            packetRateWindowStartMs = nowMs;
            packetRateCount = 0;
        }
        packetRateCount++;
        long elapsedMs = nowMs - packetRateWindowStartMs;
        if (elapsedMs < PACKET_RATE_WINDOW_MS) {
            return;
        }
        double actualPps = packetRateCount / (elapsedMs / 1000.0);
        double expectedSampleRate = 1_000_000.0 / smallestTimeStep_usec;
        double expectedPps = expectedSampleRate / samplesPerPacket;
        if (expectedPps <= 0.0) {
            updateSamplingRateStatusDisplay("throughput n/a", Color.GRAY);
        } else {
            double ratio = actualPps / expectedPps;
            if (packetRateRatioWindow == null || packetRateRatioWindow.length != PACKET_RATE_AVG_WINDOWS) {
                packetRateRatioWindow = new double[PACKET_RATE_AVG_WINDOWS];
                packetRateRatioIndex = 0;
                packetRateRatioCount = 0;
            }
            packetRateRatioWindow[packetRateRatioIndex] = ratio;
            packetRateRatioIndex = (packetRateRatioIndex + 1) % PACKET_RATE_AVG_WINDOWS;
            if (packetRateRatioCount < PACKET_RATE_AVG_WINDOWS) {
                packetRateRatioCount++;
            }
            double sum = 0.0;
            for (int i = 0; i < packetRateRatioCount; i++) {
                sum += packetRateRatioWindow[i];
            }
            double avgRatio = sum / packetRateRatioCount;
            String percentText = String.format(Locale.US, "%.1f%%", avgRatio * 100.0);
            if (avgRatio < PACKET_RATE_MIN_RATIO) {
                packetRateBelowCount++;
            } else {
                packetRateBelowCount = 0;
            }
            boolean warn = packetRateBelowCount >= PACKET_RATE_WARN_WINDOWS;
            String throughputText = "throughput " + percentText;
            if (warn) {
                throughputText += " (LOW)";
            }
            updateSamplingRateStatusDisplay(throughputText, warn ? Color.RED : Color.GREEN);
        }
        packetRateWindowStartMs = nowMs;
        packetRateCount = 0;
    }

    private void resetSamplingRateDetection()
    {
        samplingRateLocked = false;
        samplingDetectStartMs = 0;
        samplingDetectPacketCount = 0;
        samplingDetectStarted = false;
        samplingDetectDelayUntilMs = 0;
    }

    private void triggerSamplingRateDetection()
    {
        resetSamplingRateDetection();
        forceSamplingDetect = true;
        samplingDetectDelayUntilMs = 0;
        updateLogOnOffButtonState();
        System.out.println("Sampling rate auto-detection triggered.");
    }

    private void printDetectedSamplingRate(double sampleRateHz, double rawSampleRateHz, double packetsPerSec, int samplesPerPacket, long measuredMs, long packetCount, double nominalSampleRateHz, boolean snapped)
    {
        System.out.println(String.format(Locale.US,
            "Detected sampling rate: %.1f Hz (raw %.1f Hz, nominal %.1f Hz, snapped %s, time step %.6f us, packets/s %.1f, packets %d, samples/packet %d, window %d ms)",
            sampleRateHz, rawSampleRateHz, nominalSampleRateHz, snapped ? "yes" : "no",
            smallestTimeStep_usec, packetsPerSec, packetCount, samplesPerPacket, measuredMs));
    }

    private void maybeAutoDetectSamplingRate(long nowMs, int samplesPerPacket)
    {
        if (!(autoDetectSamplingRate || forceSamplingDetect) || samplingRateLocked) {
            return;
        }
        if (samplingDetectDelayUntilMs > 0 && nowMs < samplingDetectDelayUntilMs) {
            return;
        }
        if (!samplingDetectStarted) {
            samplingDetectStartMs = nowMs;
            samplingDetectPacketCount = 0;
            samplingDetectStarted = true;
        }
        long elapsedMs = nowMs - samplingDetectStartMs;
        samplingDetectPacketCount++;
        long measuredMs = elapsedMs;
        if (measuredMs < AUTO_DETECT_WINDOW_MS) {
            return;
        }
        double packetsPerSec = samplingDetectPacketCount / (measuredMs / 1000.0);
        double rawSampleRate = packetsPerSec * samplesPerPacket;
        if (rawSampleRate <= 0.0) {
            return;
        }
        double nominalSampleRate = 0.0;
        boolean snapped = false;
        if (manualTimeStep_usec > 0) {
            nominalSampleRate = 1_000_000.0 / manualTimeStep_usec;
            double diffRatio = Math.abs(rawSampleRate - nominalSampleRate) / nominalSampleRate;
            if (diffRatio <= AUTO_DETECT_SNAP_TOLERANCE) {
                snapped = true;
            }
        }

        double sampleRate = snapped ? nominalSampleRate : rawSampleRate;
        // Round to the nearest whole kHz step
        double rateKHz = Math.round(sampleRate / 1000.0);
        sampleRate = rateKHz * 1000.0;
        if (sampleRate > MAX_SAMPLE_RATE_HZ) {
            sampleRate = MAX_SAMPLE_RATE_HZ;
        }
        smallestTimeStep_usec = Math.max(1e-6, 1_000_000.0 / sampleRate);
        resetScopeBufferForSamplingRateChange();
        samplingRateLocked = true;
        updateLogOnOffButtonState();
        forceSamplingDetect = false;
        updateDomainRange();
        updateSamplingRateDisplay(sampleRate);
        clearScopeChart();
        resetPacketRateMonitor();
        printDetectedSamplingRate(sampleRate, rawSampleRate, packetsPerSec, samplesPerPacket, measuredMs, samplingDetectPacketCount, nominalSampleRate, snapped);
    }

    private String getSelectedChannelLabel(int index)
    {
        initChannelComponentArrays();
        if (index < 0 || index >= channelSelectCombos.size()) {
            return "";
        }
        javax.swing.JComboBox<String> combo = channelSelectCombos.get(index);
        Object selectedItem = combo == null ? null : combo.getSelectedItem();
        return selectedItem == null ? "" : selectedItem.toString();
    }

    private String[] getSelectedChannelLabels(boolean removeSpaces)
    {
        int count = Math.min(chnum, MAX_CHANNELS);
        String[] labels = new String[count];
        for (int labelIndex = 0; labelIndex < count; labelIndex++) {
            String label = getSelectedChannelLabel(labelIndex);
            labels[labelIndex] = removeSpaces ? label.replace(" ", "") : label;
        }
        return labels;
    }
    
    @Override
    public void actionPerformed(ActionEvent actionEvent)
    {
        Object quelle = actionEvent.getSource();
        if ( quelle == view.getBtnConnect())
        {
            ArrayList<Long> commands = new ArrayList<Long>();

            transmitter.setCommandList(commands);

            connected = false;
            resetErrorCodeState();
            setErrorResetControlEnabled(false);
            resetThroughputMonitor();
            resetLifecheckMonitorState();
            view.getBtnDisconnect().setEnabled(false);
            updateDetectSamplingButtonState();
            
            // enable Scope Controls
            view.getBtnRunStop().setEnabled(true);
            view.getBtnSingleShot().setEnabled(true);
            view.getBtnTriggerEnabled().setEnabled(true);
            view.getBtnFixAxis().setEnabled(true);
            updateLogOnOffButtonState();
            view.getBtnChange_fastDataLog().setEnabled(true);
            view.getBtnChange_slowDataLog().setEnabled(true);
            view.getBtnSet_extLogging().setEnabled(true);
            view.setLogOnOffHighlighted(loggingOnOff);
            view.setLogStatusHighlighted(loggingOnOff);
            view.setFastDataLogHighlighted(fastDataLogOnOff);
            view.setSlowDataLogHighlighted(slowDataLogOnOff);
            view.setExtLoggingHighlighted(extLoggingOnOff);
            setSendFieldsEnabled(true);
            acquisitionMode = resolveContinuousAcquisitionMode();
            acquisitionState = AcquisitionState.RUNNING;
            pendingGraphUpdate = false;
            resetTriggerCaptureState();
            dataPointCounter = 0;
            updateSingleShotButtonState();
            set_Txt_RunStop();
            time_stamp_connect = System.currentTimeMillis();
            
        }

        else if ( quelle == view.getBtnDisconnect())
        {
            if (loggingOnOff) {
                loggingOnOff = Turn_Logging_on_off(false);
            }
            if (transmitter != null) {
                transmitter.disconnect();
            }
            connected = false;
            resetErrorCodeState();
            setErrorResetControlEnabled(false);
            if (acquisitionMode == AcquisitionMode.SINGLE) {
                acquisitionMode = resolveContinuousAcquisitionMode();
            }
            acquisitionState = AcquisitionState.STOPPED;
            pendingGraphUpdate = false;
            resetTriggerCaptureState();
            dataPointCounter = 0;
            updateSingleShotButtonState();
            set_Txt_RunStop();
            view.getBtnConnect().setEnabled(true);
            view.getBtnDisconnect().setEnabled(false);
            updateDetectSamplingButtonState();
            resetPacketRateMonitor();
            resetThroughputMonitor();
            resetLifecheckMonitorState();
        }
        
        else if( quelle == view.getBtnRunStop() )
        {            
            if (isScopeRunning()) {
                if (acquisitionMode == AcquisitionMode.SINGLE) {
                    acquisitionMode = resolveContinuousAcquisitionMode();
                }
                acquisitionState = AcquisitionState.STOPPED;
            } else {
                if (acquisitionMode == AcquisitionMode.SINGLE) {
                    acquisitionMode = resolveContinuousAcquisitionMode();
                }
                acquisitionState = AcquisitionState.RUNNING;
            }
            pendingGraphUpdate = false;
            resetTriggerCaptureState();
            dataPointCounter = 0;
            updateSingleShotButtonState();
            set_Txt_RunStop();
        }
        
        else if ( quelle == view.getBtnSingleShot())
        {
            if (isSingleShotActive()) {
                return;
            }
            view.setTriggerEnabled(true);
            applyTriggerFromUi(false, false, false);

            // Start single-shot from a clean capture state to avoid stale samples
            // from previous acquisitions on the left side of the scope image.
            if (scopeRingBuffer != null) {
                scopeRingBuffer.deleteAllChannels();
                ringReadPtr = scopeRingBuffer.snapshotWritePtr();
            }
            dataPointCounter = 0;
            resetTriggerCaptureState();
            pendingGraphUpdate = false;
            acquisitionMode = AcquisitionMode.SINGLE;
            acquisitionState = AcquisitionState.ARMED;
            updateSingleShotButtonState();
            set_Txt_RunStop();

            for (int seriesIndex = 0; seriesIndex < chnum; seriesIndex++) {
                chartSeries[seriesIndex].setNotify(false);
                chartSeries[seriesIndex].clear();
                chartSeries[seriesIndex].setNotify(true);
            }
            if (chPanel.getChart().getXYPlot().getDataset() != chartDataset) {
                chPanel.getChart().getXYPlot().setDataset(chartDataset);
            }

            final double xStep = smallestTimeStep_usec * 0.000001 * timeFactor;
            updateTriggerOverlay(triggermode, triggervalue, pretrigger, xStep, true);
            chPanel.repaint();
        } 
        
        else if ( quelle == view.getBtnLogOnOff())
        {
            if (extLoggingOnOff == false) {
               loggingOnOff = Turn_Logging_on_off(loggingOnOff); 
            }     
        }
        
        else if ( quelle == view.getBtnSet_extLogging()) {
            if (extLoggingOnOff == false) {
                extLoggingOnOff = true;
                view.setExtLoggingHighlighted(true);
                view.getBtnLogOnOff().setEnabled(false);
            } else {
                extLoggingOnOff = false;
                view.setExtLoggingHighlighted(false);
                view.getBtnLogOnOff().setEnabled(true);
            }
        }
        
        else if ( quelle == view.getBtnChange_fastDataLog()) {
            if(fastDataLogOnOff == true) {
                fastDataLogOnOff = false;
                view.setFastDataLogHighlighted(false);
            } else {              
                fastDataLogOnOff = true;
                view.setFastDataLogHighlighted(true);
            }
        }
        
        else if ( quelle == view.getBtnChange_slowDataLog()) {
            if(slowDataLogOnOff == true) {
                slowDataLogOnOff = false;
                view.setSlowDataLogHighlighted(false);
            } else {              
                slowDataLogOnOff = true;
                view.setSlowDataLogHighlighted(true);
            }
        }

        else if ( quelle == view.getBtnDetectSamplingRate()
                || quelle == viewSCOPE.getBtnScopeDevDetectSamplingRate())
        {
            triggerSamplingRateDetection();
        }

        else if (quelle == viewSCOPE.getBtnScopeDevPauseAck())
        {
            setPauseAckCommandEnabled(!pauseAckCommandEnabled);
        }

        else if (quelle == viewSCOPE.getBtnScopeDevPrintSentCommands())
        {
            if (transmitter != null) {
                transmitter.setPrintSentCommandsEnabled(!transmitter.isPrintSentCommandsEnabled());
            }
            updateScopeDevPrintSentCommandsButtonState();
        }

        else if (quelle == viewSCOPE.getBtnScopeDevSingleInstanceGuard())
        {
            if (transmitter != null) {
                boolean desired = !transmitter.isSingleInstanceSocketGuardEnabled();
                boolean changed = transmitter.setSingleInstanceSocketGuardEnabled(desired);
                if (!changed && desired) {
                    JOptionPane.showMessageDialog(
                            null,
                            "Could not enable single-instance guard because the current target lock is already held by another JavaScope instance.",
                            "Socket lock not available",
                            JOptionPane.INFORMATION_MESSAGE
                    );
                }
            }
            updateScopeDevSingleInstanceGuardButtonState();
        }

        else if (quelle == viewSCOPE.getBtnScopeDevLifecheckMonitor())
        {
            setLifecheckMonitorEnabled(!lifecheckMonitorEnabled);
        }
        
        else if ( quelle == view.getCombo_LogNthValue())
        {
            updateLogFactorFromSelection();
        }

        else if ( quelle == view.getBtnSaveSettings())
        {
            boolean saved = writeScopeSettingsToProperties();
            if (saved) {
                logger.info("Saved scope settings to properties.ini");
            } else {
                logger.warning("Failed to save scope settings to properties.ini");
            }
        }
        else if (handleScaleButtonAction(quelle))
        {
            // handled in dispatch map
        }

        else if ( quelle == view.getBtnFixAxis())
        {
            updateDomainRange();
            
            ValueAxis range = chPanel.getChart().getXYPlot().getRangeAxis();  // y-Achse
            range.setAutoRange(false);
            range.setRange(-10.0, 10.0);
        }
        
    }
  
    public void onTransmitterUpdate(Transmitter source, Object payload)
    {
        // Connection established notification (payload is null)
        if (payload == null)
        {
            // Purge scope ring buffer on new connection
            if (scopeRingBuffer != null)
            {
                scopeRingBuffer.deleteAllChannels();
            }
            resetTriggerCaptureState();
            pendingGraphUpdate = false;
            dataPointCounter = 0;
            // Send select data commands on connection
            if (sendCont != null)
            {
                sendCont.sendSelectDataAll();
            }
            resetPacketRateMonitor();
            if (autoDetectSamplingRate) {
                resetSamplingRateDetection();
                samplingDetectDelayUntilMs = System.currentTimeMillis() + AUTO_DETECT_CONNECT_DELAY_MS;
                updateLogOnOffButtonState();
            }
            resetThroughputMonitor();
            resetLifecheckMonitorState();
            return;
        }

        // Debug: count packets received
        if (DEBUG_SCOPE_UPDATE_RATE) {
            debugPacketCount++;
        }

        if (connectionIndicatorOn)
        {
            view.getLblAnzeigeConnected().setText("~#~#~#");
            connectionIndicatorOn = false;
        }
        else
        {
            view.getLblAnzeigeConnected().setText("#~#~#~");
            connectionIndicatorOn = true;
        }

        if (payload instanceof AnzeigeDaten)
        {
            adata = (AnzeigeDaten)payload;
            if(is_first_call) {
                ledLastStatus = adata.status;
            }
            update_func_runs = true;
            long currentTimeMillis = System.currentTimeMillis();
            if (adata.status != lastStatus) {
                lastStatus = adata.status;
                String statusBinaryString = Long.toBinaryString(adata.status);
                StringBuilder statusBinaryBuilder = new StringBuilder();
                for (int toPrepend=32-statusBinaryString.length(); toPrepend>0; toPrepend--) statusBinaryBuilder.append('0');
                statusBinaryBuilder.append(statusBinaryString);
                String statusResult = statusBinaryBuilder.toString();
                view.getLblStatusUnten().setText("Status: "+statusResult);
            }
           
           
            int val_per_ch_in_packet = 1; // since only 1 word (4bytes) perchannel is transmitted, this value is hardwared to being 1 for now
            int samplesPerPacket = transmitter.ANZAHL_MESSREIHEN_PRO_TCP_PAKET * val_per_ch_in_packet;
            maybeAutoDetectSamplingRate(currentTimeMillis, samplesPerPacket);
            updatePacketRateStatus(currentTimeMillis, samplesPerPacket);
            updateThroughputMonitor(currentTimeMillis);
            // chdata is preallocated at class level to avoid allocation per packet 

            // Umsortieren, iterating over samples per package
            for (int sampleIndex = 0; sampleIndex < transmitter.ANZAHL_MESSREIHEN_PRO_TCP_PAKET; sampleIndex++)
            {
                for (int channelIndex = 0; channelIndex < chnum; channelIndex++)
                {
                    for (int valueIndex = 0; valueIndex < val_per_ch_in_packet; valueIndex++) {
                        double sampleValue = (double) adata.val[channelIndex * val_per_ch_in_packet + valueIndex][sampleIndex];
                        chdata[channelIndex][val_per_ch_in_packet * sampleIndex + valueIndex] = sampleValue;
                        processLifecheckSample(channelIndex, sampleValue);
                    }
                }
                
                int slowDataIndex = adata.slowDataID[sampleIndex];
                if (slowDataIndex >= 0 && slowDataIndex < slowDataContent.length)
                {
                    long slowDataValue = adata.slowDataContent[sampleIndex];
                    slowDataContent[slowDataIndex] = slowDataValue;
                }
            } 
            
            // Nun liegen in chdata[<20>][<ANZAHL_MESSREIHEN_PRO_TCP_PAKET * val_per_ch_in_packet>] die umgerechneten Messdaten vor.
            // Hier liegen die Daten als reale Werte in ihrer Skalierung wie auf dem Prozessor vor.
            // Hier kann ein Logging in Datei erfolgen.
            // Alles weitere ist nur zum Anzeigen in der GUI, Daten werden nicht gespeichert. (Bis auf GUI-Funktionen)
             
            // Logging
            synchronized (logWriteLock)
            {
                if (loggingOnOff == true && logWriter != null)
                {
                    try
                    {
                        refreshLogChannelSelection();

                        if (!logHeaderWritten) {
                            // Use replace() instead of replaceAll() - no regex overhead
                            String[] chLabels = getSelectedChannelLabels(true);
                            StringBuilder header = new StringBuilder(256 + (loggedSlowDataColumnCount * 16));
                            header.append("time;");
                            for (int channelIndex = 0; channelIndex < chnum; channelIndex++) {
                                header.append("CH").append(channelIndex + 1).append('=').append(chLabels[channelIndex]).append(';');
                            }

                            if (slowDataLogOnOff == true) {
                                for (int slowDataIndex = 0; slowDataIndex < slowDataSignalNames.size(); slowDataIndex++) {
                                    if (isLoggableSlowDataIndex(slowDataIndex)) {
                                        header.append(formatSlowDataLogHeaderName(slowDataIndex)).append(';');
                                    }
                                }
                            }
                            header.append("\n");
                            logWriter.write(header.toString());
                            logHeaderWritten = true;
                        }
                        if (logPacketBuilder == null) {
                            logPacketBuilder = new StringBuilder(4096);
                        }
                        logPacketBuilder.setLength(0);
                        double timeStepSec = logTimeStep_usec * 0.000001;
                        for (int packetSampleIndex = 0; packetSampleIndex < (transmitter.ANZAHL_MESSREIHEN_PRO_TCP_PAKET * val_per_ch_in_packet); packetSampleIndex++) {
                            long absoluteSampleIndex = generalDataCounter + packetSampleIndex;
                            boolean shouldLogFastRow = fastDataLogOnOff && ((absoluteSampleIndex % logFactor) == 0);
                            int slowDataIndex = adata.slowDataID[packetSampleIndex];
                            long slowDataRawValue = adata.slowDataContent[packetSampleIndex];
                            boolean shouldLogSlowEvent = false;
                            if (slowDataLogOnOff) {
                                if (slowDataIndex == 0) {
                                    // Ignore the placeholder ID completely.
                                } else if (!isValidSlowDataIndex(slowDataIndex)) {
                                    slowDataLogInvalidIdCount++;
                                } else {
                                    shouldLogSlowEvent = true;
                                    if (slowDataLogEventCounts != null && slowDataIndex < slowDataLogEventCounts.length) {
                                        slowDataLogEventCounts[slowDataIndex]++;
                                    }
                                }
                            }
                            if (!shouldLogFastRow && !shouldLogSlowEvent) {
                                continue;
                            }

                            double timeSec = roundLogTimestampSeconds(absoluteSampleIndex * timeStepSec);
                            logPacketBuilder.append(formatFloatingValueForLog(timeSec)).append(";");
                            if (shouldLogFastRow) {
                                // Use pre-computed flags and loop instead of 20 if/else blocks
                                for (int channelIndex = 0; channelIndex < chnum; channelIndex++) {
                                    if (logZeroValueChannelSelection[channelIndex]) {
                                        logPacketBuilder.append(";");
                                    } else {
                                        logPacketBuilder.append(formatFloatingValueForLog(chdata[channelIndex][packetSampleIndex])).append(";");
                                    }
                                }
                            } else {
                                appendBlankCsvColumns(logPacketBuilder, chnum);
                            }

                            if (slowDataLogOnOff == true) {
                                if (shouldLogSlowEvent) {
                                    appendSlowDataLogColumns(logPacketBuilder, slowDataIndex, slowDataRawValue);
                                } else {
                                    appendBlankCsvColumns(logPacketBuilder, loggedSlowDataColumnCount);
                                }
                            }
                            logPacketBuilder.append("\n");
                        }
                        if (logPacketBuilder.length() > 0) {
                            logWriter.write(logPacketBuilder.toString());
                        }
                    }
                    catch (Exception exception)
                    {
                        System.out.print(exception.toString());
                        JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
                    }
                }
            }
            // Auswertung für Darstellung in der Scope-GUI
            int pretriggerSamples = (int)Math.round(pretrigger * (ringBufferSamples - 1));
            int postTriggerSamples = (ringBufferSamples - 1) - pretriggerSamples;
            boolean refreshWindowElapsed = currentTimeMillis - lastSystemMillis > CHART_REFRESH_RATE_MS;
            boolean rollingSnapshotPending = false;
            boolean triggerSnapshotPending = false;
            boolean freezeDecimatedWritesForPacket = false;
            for (int packetSampleIndex = 0; packetSampleIndex < (transmitter.ANZAHL_MESSREIHEN_PRO_TCP_PAKET * val_per_ch_in_packet); packetSampleIndex++)
            {
                generalDataCounter++;   // never reset this counter, data-type long.
                // newvals is preallocated at class level to avoid 15 allocations per packet
                for (int channelIndex=0; channelIndex<chnum; channelIndex++)
                {
                    newvals[channelIndex] = (chdata[channelIndex][packetSampleIndex] + offsetCHx[channelIndex]) / scaleCHx[channelIndex];
                }
                
                boolean isDecimatedSample = ((generalDataCounter % timeFactor) == 0); // %1 always returns 0
                boolean freezeBuffer = freezeDecimatedWritesForPacket
                    || (acquisitionMode == AcquisitionMode.SINGLE
                        && acquisitionState == AcquisitionState.TRIGGERED
                        && triggerCaptureComplete);
                if (isDecimatedSample && !freezeBuffer)   // always write into the ring buffer, only considering the timeFactor
                {
                    dataPointCounter++;
                    scopeRingBuffer.addValues(newvals);     // always write into the ringbuffer!
                }

                if (triggermode > 0)
                {
                    boolean triggerArmed = dataPointCounter >= pretriggerSamples;
                    if (!triggerArmed) {
                        triggerCompareValid = false;
                    } else if (!trigOccured) {   // only get first trigger after pretrigger buffer is filled
                        trigOccured = triggerEventOccured(packetSampleIndex); // look for trigger on full-rate samples
                        if (trigOccured && dataPointCounter_trigOccured == -1) {
                            dataPointCounter_trigOccured = Math.max(0, dataPointCounter - 1);
                            if (acquisitionMode == AcquisitionMode.SINGLE && acquisitionState == AcquisitionState.ARMED) {
                                acquisitionState = AcquisitionState.TRIGGERED;
                                updateSingleShotButtonState();
                            }
                        }
                    }
                }
                
                // Auto mode: rolling update
                if (!pendingGraphUpdate
                    && acquisitionMode == AcquisitionMode.AUTO
                    && refreshWindowElapsed)
                {
                    pendingGraphUpdate = true;
                    rollingSnapshotPending = true;
                }

                // Single-shot armed: keep rolling display while waiting for trigger.
                if (!pendingGraphUpdate
                    && acquisitionMode == AcquisitionMode.SINGLE
                    && acquisitionState == AcquisitionState.ARMED
                    && refreshWindowElapsed)
                {
                    pendingGraphUpdate = true;
                    rollingSnapshotPending = true;
                }

                // Triggered capture completion for NORMAL and SINGLE modes.
                if (triggermode > 0
                    && !pendingGraphUpdate
                    && trigOccured
                    && !triggerCaptureComplete
                    && dataPointCounter_trigOccured != -1)
                {
                    int lastSampleIndex = dataPointCounter - 1;
                    int samplesAfterTrigger = lastSampleIndex - dataPointCounter_trigOccured;
                    if (samplesAfterTrigger >= postTriggerSamples) {
                        triggerCaptureComplete = true;
                        triggerSnapshotPending = true;
                        freezeDecimatedWritesForPacket = true;
                        pendingGraphUpdate = true;
                    }
                }
                
            }
            if (rollingSnapshotPending || triggerSnapshotPending) {
                // Finalize snapshots after the packet loop so no tail samples wrap to the left edge.
                ringReadPtr = scopeRingBuffer.snapshotWritePtr();
            }
                
            // Graphen aktualisieren    // (System.currentTimeMillis() - lastSystemMillis > 1000)
            try {
                if (pendingGraphUpdate && isScopeRunning())
                {
                    boolean singleRollingRefresh =
                        acquisitionMode == AcquisitionMode.SINGLE
                        && acquisitionState == AcquisitionState.ARMED
                        && !triggerCaptureComplete;
                    boolean singleCaptureCompleted =
                        acquisitionMode == AcquisitionMode.SINGLE
                        && acquisitionState == AcquisitionState.TRIGGERED
                        && triggerCaptureComplete;

                    if (!singleRollingRefresh) {
                        dataPointCounter = 0;
                        resetTriggerCaptureState();
                    }

                    pendingGraphUpdate = false;
                    lastSystemMillis = System.currentTimeMillis();

                    // Debug: count chart updates and print stats every 5 seconds
                    if (DEBUG_SCOPE_UPDATE_RATE) {
                        debugChartUpdateCount++;
                        long debugNow = System.currentTimeMillis();
                        if (debugNow - debugLastStatTime >= 5000) {
                            double elapsedSec = (debugNow - debugLastStatTime) / 1000.0;
                            System.out.println(String.format(
                                "[DEBUG] Packets: %d (%.1f/s), Chart updates: %d (%.1f/s), Ratio: %.1f:1",
                                debugPacketCount, debugPacketCount / elapsedSec,
                                debugChartUpdateCount, debugChartUpdateCount / elapsedSec,
                                debugPacketCount / (double) Math.max(1, debugChartUpdateCount)));
                            debugPacketCount = 0;
                            debugChartUpdateCount = 0;
                            debugLastStatTime = debugNow;
                        }
                    }

                    if (singleCaptureCompleted) {
                        acquisitionMode = resolveContinuousAcquisitionMode();
                        acquisitionState = AcquisitionState.STOPPED;
                        updateSingleShotButtonState();
                        set_Txt_RunStop();
                    }
                    
                    final double xStep = smallestTimeStep_usec * 0.000001 * timeFactor;
                    final int bufferLen = scopeRingBuffer.getSizePerChannel();
                    final int snapshotPtr = ringReadPtr;
                    final double[][] dataSnapshot = snapshotScopeBufferData(snapshotPtr);
                    lastRenderedSnapshot = dataSnapshot;
                    final int currentTriggermode = triggermode;
                    final double currentTriggervalue = triggervalue;
                    final double currentPretrigger = pretrigger;

                    SwingUtilities.invokeLater(() ->
                        renderScopeSnapshot(dataSnapshot, bufferLen, xStep, currentTriggermode, currentTriggervalue, currentPretrigger)
                    );
                    
                  

                }

                long nowSlow = System.currentTimeMillis();
                if (nowSlow - lastSystemMillisSlowData > SLOW_DATA_REFRESH_RATE_MS)        // > xx ms
                {
                    lastSystemMillisSlowData = nowSlow;
                    slowDataTableModel = (DefaultTableModel)viewSCOPE.getTbSlowData3().getModel();
                    for (int slowDataIndex = 0; slowDataIndex < slowDataContent.length; slowDataIndex++)
                    {
                        if (slowDataIntOrFloat.get(slowDataIndex).contains("float"))
                        {
                            slowDataTableModel.setValueAt(Float.toString(Float.intBitsToFloat((int)slowDataContent[slowDataIndex])), slowDataIndex, 2);
                        }else{
                            slowDataTableModel.setValueAt(Long.toString(slowDataContent[slowDataIndex]), slowDataIndex, 2);
                        }
                    }
                    
                    
                    //UPDATE DISPLAY DATA CONTROL
                    refreshErrorCodeState();
                    for (int fieldIndex = 0; fieldIndex < rcvFields.size(); fieldIndex++) {
                        int mappedSlowDataIndex = JSSD_indices[fieldIndex + 1];
                        if (isValidSlowDataIndex(mappedSlowDataIndex)
                            && !ZERO_VALUE.equals(slowDataSignalNames.get(mappedSlowDataIndex))){
                            rcvFields.get(fieldIndex).setText(numberFormatTwoDecimals.format(getAverageValue(fieldIndex)));
                        }
                    }

                }
            } catch (Exception exception) {
                logger.info("ReceiveController: exception in update/Graph -- ");
                logger.severe(exception.toString());
                System.out.println("ReceiveController: exception in update/Graph");
            }
            
            // Statuslampen steuern
            if ((is_status_bit_true(0)) && (did_status_bit_change(0) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtReady().setBackground(Color.green);
                viewSCOPE.getTxtReady1().setBackground(Color.green);
                setScopeDevStatusBackground(viewSCOPE.getTxtReadyDev(), Color.green);
            }
            if ((!is_status_bit_true(0)) && (did_status_bit_change(0) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtReady().setBackground(null);
                viewSCOPE.getTxtReady1().setBackground(null);
                setScopeDevStatusBackground(viewSCOPE.getTxtReadyDev(), null);
            }

            if ((is_status_bit_true(1)) && (did_status_bit_change(1) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtRunning().setBackground(Color.green);
                viewSCOPE.getTxtRunning1().setBackground(Color.green);
                setScopeDevStatusBackground(viewSCOPE.getTxtRunningDev(), Color.green);
            }
            if ((!is_status_bit_true(1)) && (did_status_bit_change(1) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtRunning().setBackground(null);
                viewSCOPE.getTxtRunning1().setBackground(null);
                setScopeDevStatusBackground(viewSCOPE.getTxtRunningDev(), null);
            }
            
            if ((is_status_bit_true(ERROR_STATUS_BIT)) && (did_status_bit_change(ERROR_STATUS_BIT) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtError().setBackground(Color.red);
                viewSCOPE.getTxtError1().setBackground(Color.red);
                setScopeDevStatusBackground(viewSCOPE.getTxtErrorDev(), Color.red);
            }
            if ((!is_status_bit_true(ERROR_STATUS_BIT)) && (did_status_bit_change(ERROR_STATUS_BIT) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtError().setBackground(null);
                viewSCOPE.getTxtError1().setBackground(null);
                setScopeDevStatusBackground(viewSCOPE.getTxtErrorDev(), null);
            }            

            if ((is_status_bit_true(3)) && (did_status_bit_change(3) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtUser().setBackground(Color.green);
                viewSCOPE.getTxtUser1().setBackground(Color.green);
                setScopeDevStatusBackground(viewSCOPE.getTxtUserDev(), Color.green);
            }
            if ((!is_status_bit_true(3)) && (did_status_bit_change(3) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtUser().setBackground(null);
                viewSCOPE.getTxtUser1().setBackground(null);
                setScopeDevStatusBackground(viewSCOPE.getTxtUserDev(), null);
            }
            
            if ((is_status_bit_true(4)) && (did_status_bit_change(4) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn1().setBackground(Color.green);
            }
            if ((!is_status_bit_true(4)) && (did_status_bit_change(4) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn1().setBackground(null);
                viewSCOPE.getTxtBtn1().setForeground(viewSCOPE.getTxtBtn1().getBackground());
            }
            
            if ((is_status_bit_true(5)) && (did_status_bit_change(5) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn2().setBackground(Color.green);
            }
            if ((!is_status_bit_true(5)) && (did_status_bit_change(5) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn2().setBackground(null);
                viewSCOPE.getTxtBtn2().setForeground(viewSCOPE.getTxtBtn2().getBackground());
            }
            
            if ((is_status_bit_true(6)) && (did_status_bit_change(6) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn3().setBackground(Color.green);
            }
            if ((!is_status_bit_true(6)) && (did_status_bit_change(6) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn3().setBackground(null);
                viewSCOPE.getTxtBtn3().setForeground(viewSCOPE.getTxtBtn3().getBackground());
            }
            
            if ((is_status_bit_true(7)) && (did_status_bit_change(7) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn4().setBackground(Color.green);
            }
            if ((!is_status_bit_true(7)) && (did_status_bit_change(7) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn4().setBackground(null);
                viewSCOPE.getTxtBtn4().setForeground(viewSCOPE.getTxtBtn4().getBackground());
            }
            
            if ((is_status_bit_true(8)) && (did_status_bit_change(8) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn5().setBackground(Color.green);
            }
            if ((!is_status_bit_true(8)) && (did_status_bit_change(8) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn5().setBackground(null);
                viewSCOPE.getTxtBtn5().setForeground(viewSCOPE.getTxtBtn5().getBackground());
            }
            
            if ((is_status_bit_true(9)) && (did_status_bit_change(9) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn6().setBackground(Color.green);
            }
            if ((!is_status_bit_true(9)) && (did_status_bit_change(9) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn6().setBackground(null);
                viewSCOPE.getTxtBtn6().setForeground(viewSCOPE.getTxtBtn6().getBackground());
            }
            
            if ((is_status_bit_true(10)) && (did_status_bit_change(10) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn7().setBackground(Color.green);
            }
            if ((!is_status_bit_true(10)) && (did_status_bit_change(10) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn7().setBackground(null);
                viewSCOPE.getTxtBtn7().setForeground(viewSCOPE.getTxtBtn7().getBackground());
            }
            
            if ((is_status_bit_true(11)) && (did_status_bit_change(11) || is_first_call || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn8().setBackground(Color.green);
            }
            if ((!is_status_bit_true(11)) && (did_status_bit_change(11) || sendCont.did_LookAndFeel_change())){
                viewSCOPE.getTxtBtn8().setBackground(null);
                viewSCOPE.getTxtBtn8().setForeground(viewSCOPE.getTxtBtn8().getBackground());
            }
            
            if ((is_status_bit_true(12)) && (did_status_bit_change(12) || is_first_call || sendCont.did_LookAndFeel_change())){
                if (extLoggingOnOff == true) {
                    loggingOnOff = Turn_Logging_on_off(false);
                }
            }
            if ((!is_status_bit_true(12)) && (did_status_bit_change(12) || sendCont.did_LookAndFeel_change())){
                if (extLoggingOnOff == true) {
                    loggingOnOff = Turn_Logging_on_off(true);
                }
            }
            if(is_first_call && ((System.currentTimeMillis() - time_stamp_connect) >= 150)) {is_first_call = false;}
            ledLastStatus = adata.status;
            if(sendCont.did_LookAndFeel_change() && LookAndFeel_timestamp <= 0.0) {
                LookAndFeel_timestamp = System.currentTimeMillis();
            } else if (sendCont.did_LookAndFeel_change() && ((System.currentTimeMillis() - LookAndFeel_timestamp) >= 500.0)){
                sendCont.reset_LookAndFeel_change();
                LookAndFeel_timestamp = 0L;
            }
        }
  
        if (connected == false)
        {
            connected = true;

            view.getBtnConnect().setEnabled(false);
            view.getTxtIPAdresse().setEnabled(false);
            view.getBtnDisconnect().setEnabled(true);
            updateDetectSamplingButtonState();
            updateLogOnOffButtonState();
            updateSingleShotButtonState();
           
            
            updateDomainRange();

            ValueAxis range = chPanel.getChart().getXYPlot().getRangeAxis();  // y-Achse
            range.setAutoRange(true);
            

            //Control panel
            viewSCOPE.getBtnStop3().setEnabled(true);
            setErrorResetControlEnabled(true);
        }
    }
    
    
     
    private boolean triggerEventOccured(int packetSampleIndex)
    {
        boolean retval = false;
        double currVal = 0.0;
        int edge = -1;  // 1=rising, 0=falling
        if (triggermode == 0)   // auto
        {
            retval = true;  // at auto-mode, trigger is always active.
            triggerLastCompareValue = 0.0;
            triggerLastCompareValue2 = 0.0;
            triggerCompareValid = false;
        }
        else if (triggermode > 0 && triggermode <= (2*chnum))
        {
            int trigchan = (triggermode-1)/2;   // integer division to get only CH0, CH1, CH2 or CH3
            currVal = chdata[trigchan][packetSampleIndex];
            edge = triggermode % 2; // 1=rising, 0=falling
            double trigvalRaw = triggervalue;
            if (!triggerCompareValid) {
                triggerLastCompareValue = currVal;
                triggerLastCompareValue2 = currVal;
                triggerCompareValid = true;
                return false;
            }
            if (edge == 1)  // rising edge
            {
                if (currVal >= trigvalRaw && triggerLastCompareValue <= trigvalRaw && triggerLastCompareValue2 < trigvalRaw)
                    retval = true;
            }
            else  // falling edge
            {
                if (currVal <= trigvalRaw && triggerLastCompareValue >= trigvalRaw && triggerLastCompareValue2 > trigvalRaw)
                    retval = true;
            }
            triggerLastCompareValue2 = triggerLastCompareValue;
            triggerLastCompareValue = currVal;
        }
        else
        {
            System.out.println("------>> RecvCtrl/triggerEventOccured: Wrong triggermode index! ---------------------- ");
        }
        
        return retval;
    }
    
    
    public void readChannelsStringsFromFileLineByLine() {
        try {
            final String startMarker = "JSO_ZEROVALUE=0";
            final String endMarker = "JSO_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.IDENTIFIER
            );
            reportHeaderMarkerIssue("JS_OberservableData", startMarker, endMarker, section);

            ArrayList<String> entries = section.getEntries();
            if (entries.isEmpty()) {
                entries.add("JSO_ZEROVALUE");
            }
            ArrayList<String> list = new ArrayList<>(entries.size());
            for (int entryIndex = 0; entryIndex < entries.size(); entryIndex++) {
                String line = entries.get(entryIndex).replace("JSO_", "");
                list.add(entryIndex + ") " + line);
            }

            initChannelComponentArrays();
            for (javax.swing.JComboBox<String> combo : channelSelectCombos) {
                if (combo != null) {
                    combo.removeAllItems();
                }
            }

            for (String item : list) {
                for (javax.swing.JComboBox<String> combo : channelSelectCombos) {
                    if (combo != null) {
                        combo.addItem(item);
                    }
                }
            }
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    }
    
    public boolean Turn_Logging_on_off(boolean loggingOnOff) {
        synchronized (logWriteLock) {
            if (loggingOnOff == true) {
                    finishSlowLoggingSession();
                    try {
                        closeLogWriter();
                    } catch (IOException exception) {
                        logger.severe("Failed to close log file: " + exception);
                    }
                    loggingOnOff = false;
                    logHeaderWritten = false;
                    view.getTxt_LogStatus().setText("Log OFF");
                    view.setLogOnOffHighlighted(false);
                    view.getBtnLogOnOff().setText("Logging OFF");
                    view.setLogStatusHighlighted(false);
                    view.getBtnChange_fastDataLog().setEnabled(true);
                    view.getBtnChange_slowDataLog().setEnabled(true);
                }
                else {
                    if (!startFreshLogFile()) {
                        this.loggingOnOff = false;
                        updateDetectSamplingButtonState();
                        return false;
                    }
                    logTimeStep_usec = Math.max(1e-6, smallestTimeStep_usec);
                    resetSlowLoggingSessionCounters();
                    loggingOnOff = true;
                    view.setLogOnOffHighlighted(true);
                    view.getBtnLogOnOff().setText("Logging ON ");
                    view.getTxt_LogStatus().setText("Log ON");
                    view.setLogStatusHighlighted(true);
                    view.getBtnChange_fastDataLog().setEnabled(false);
                    view.getBtnChange_slowDataLog().setEnabled(false);
                }
            this.loggingOnOff = loggingOnOff;
        }
        updateDetectSamplingButtonState();
        return (loggingOnOff);
    }

    public ArrayList<String> readSlowDataStringsFromFileLineByLine() {
        ArrayList<String> list = new ArrayList<String>();
        ArrayList<String> list2 = new ArrayList<String>();
        int parsedErrorCodeIndex = -1;
        try {
            final String startMarker = "JSSD_ZEROVALUE=0";
            final String endMarker = "JSSD_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.IDENTIFIER
            );
            reportHeaderMarkerIssue("JS_SlowData", startMarker, endMarker, section);

            if (slowDataIntOrFloat != null) {
                slowDataIntOrFloat.clear();
            }
            for (String token : section.getEntries()) {
                if (parsedErrorCodeIndex < 0 && ERROR_CODE_SIGNAL_IDENTIFIER.equals(token)) {
                    parsedErrorCodeIndex = list2.size();
                }
                if (token.contains("FLOAT_")) {
                    slowDataIntOrFloat.add("float");
                } else {
                    slowDataIntOrFloat.add("int");
                }
                String line = normalizeSlowDataSignalName(token);
                list.add(line);
                list2.add(line);
            }
            if (list.isEmpty()) {
                list.add("ZEROVALUE");
                list2.add("ZEROVALUE");
                slowDataIntOrFloat.add("int");
            }

            slowDataSignalNames = list2;
            rebuildSlowDataLogColumns();
            errorCodeSlowDataIndex = parsedErrorCodeIndex;
            if (errorCodeSlowDataIndex < 0) {
                reportMissingErrorCodeSignal(section.getSourceFile());
            }
            slowDataTableModel = (DefaultTableModel)viewSCOPE.getTbSlowData3().getModel();
            int rowCount = Math.min(list.size(), slowDataTableModel.getRowCount());
            for (int listIndex = 0; listIndex < rowCount; listIndex++) {
                slowDataTableModel.setValueAt(Integer.toString(listIndex), listIndex, 0);
                slowDataTableModel.setValueAt(list.get(listIndex), listIndex, 1);
            }
            autoSizeSlowDataVariableColumn(list);
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
        
    return slowDataSignalNames;
    }

    private String normalizeSlowDataSignalName(String identifier)
    {
        if (identifier == null) {
            return "";
        }
        return identifier
            .replace("JSSD_", "")
            .replace("FLOAT_", "")
            .replace("INT_", "");
    }

    private void rebuildSlowDataLogColumns()
    {
        if (slowDataSignalNames == null) {
            slowDataLogColumnByIndex = new int[0];
            slowDataLogEventCounts = new long[0];
            loggedSlowDataColumnCount = 0;
            resetSlowLoggingSessionCounters();
            return;
        }
        slowDataLogColumnByIndex = new int[slowDataSignalNames.size()];
        Arrays.fill(slowDataLogColumnByIndex, -1);
        int columnIndex = 0;
        for (int slowDataIndex = 0; slowDataIndex < slowDataSignalNames.size(); slowDataIndex++) {
            if (!isLoggableSlowDataIndex(slowDataIndex)) {
                continue;
            }
            slowDataLogColumnByIndex[slowDataIndex] = columnIndex;
            columnIndex++;
        }
        loggedSlowDataColumnCount = columnIndex;
        slowDataLogEventCounts = new long[slowDataSignalNames.size()];
        resetSlowLoggingSessionCounters();
    }

    private void resetSlowLoggingSessionCounters()
    {
        if (slowDataLogEventCounts != null) {
            Arrays.fill(slowDataLogEventCounts, 0L);
        }
        slowDataLogInvalidIdCount = 0L;
    }

    private void finishSlowLoggingSession()
    {
        if (!suppressSlowLoggingSessionSummary) {
            printSlowLoggingSessionSummary();
        }
        resetSlowLoggingSessionCounters();
    }

    private void printSlowLoggingSessionSummary()
    {
        long loggedEventTotal = 0L;
        int loggedSignalCount = 0;
        if (slowDataLogEventCounts != null) {
            for (int slowDataIndex = 0; slowDataIndex < slowDataLogEventCounts.length; slowDataIndex++) {
                long eventCount = slowDataLogEventCounts[slowDataIndex];
                loggedEventTotal += eventCount;
                if (eventCount <= 0L || !isLoggableSlowDataIndex(slowDataIndex)) {
                    continue;
                }
                loggedSignalCount++;
            }
        }
        if (loggedEventTotal == 0L && slowDataLogInvalidIdCount == 0L) {
            return;
        }

        StringBuilder summary = new StringBuilder(256);
        long totalObservedEvents = loggedEventTotal + slowDataLogInvalidIdCount;
        summary.append("Slow data log summary: total=").append(totalObservedEvents)
            .append(", logged=").append(loggedEventTotal);
        if (loggedSignalCount > 0) {
            summary.append(" across ").append(loggedSignalCount).append(" signals");
        }
        if (slowDataLogInvalidIdCount > 0L) {
            summary.append(", unknown IDs=").append(slowDataLogInvalidIdCount)
                .append(" (not in local JS_SlowData)");
        }
        logger.info(summary.toString());
    }

    private boolean isLoggableSlowDataIndex(int slowDataIndex)
    {
        return isValidSlowDataIndex(slowDataIndex)
            && !ZERO_VALUE.equals(slowDataSignalNames.get(slowDataIndex));
    }

    private int getSlowDataLogColumnIndex(int slowDataIndex)
    {
        if (slowDataLogColumnByIndex == null
            || slowDataIndex < 0
            || slowDataIndex >= slowDataLogColumnByIndex.length) {
            return -1;
        }
        return slowDataLogColumnByIndex[slowDataIndex];
    }

    private String formatSlowDataValueForLog(int slowDataIndex, long rawValue)
    {
        if (isFloatSlowData(slowDataIndex)) {
            return formatFloatingValueForLog(Float.intBitsToFloat((int) rawValue));
        }
        return Long.toString(rawValue);
    }

    private String formatSlowDataLogHeaderName(int slowDataIndex)
    {
        return "SD" + slowDataIndex + "_" + slowDataSignalNames.get(slowDataIndex);
    }

    private String formatFloatingValueForLog(double value)
    {
        if (value == 0.0d) {
            return "0";
        }
        return Double.toString(value);
    }

    private void appendBlankCsvColumns(StringBuilder builder, int columnCount)
    {
        for (int columnIndex = 0; columnIndex < columnCount; columnIndex++) {
            builder.append(';');
        }
    }

    private void appendSlowDataLogColumns(StringBuilder builder, int slowDataIndex, long rawValue)
    {
        if (loggedSlowDataColumnCount <= 0) {
            return;
        }
        int logColumnIndex = getSlowDataLogColumnIndex(slowDataIndex);
        if (logColumnIndex < 0) {
            appendBlankCsvColumns(builder, loggedSlowDataColumnCount);
            return;
        }
        appendBlankCsvColumns(builder, logColumnIndex);
        builder.append(formatSlowDataValueForLog(slowDataIndex, rawValue)).append(';');
        appendBlankCsvColumns(builder, loggedSlowDataColumnCount - logColumnIndex - 1);
    }

    private boolean isFloatSlowData(int slowDataIndex)
    {
        return slowDataIntOrFloat != null
            && slowDataIndex >= 0
            && slowDataIndex < slowDataIntOrFloat.size()
            && "float".equals(slowDataIntOrFloat.get(slowDataIndex));
    }

    private void reportMissingErrorCodeSignal(File sourceFile)
    {
        String fileLabel = sourceFile == null ? "javascope.h" : sourceFile.getAbsolutePath();
        logger.warning(
            "JS_SlowData in " + fileLabel + " does not contain " + ERROR_CODE_SIGNAL_IDENTIFIER
                + ". Error code display is unavailable."
        );
    }

    private boolean isErrorStatusActive()
    {
        return connected
            && adata != null
            && (((adata.status >> ERROR_STATUS_BIT) & 1) == 1);
    }

    private float getSlowDataValueAsFloat(int slowDataIndex)
    {
        if (slowDataContent == null || slowDataIndex < 0 || slowDataIndex >= slowDataContent.length) {
            return 0.0f;
        }
        long rawValue = slowDataContent[slowDataIndex];
        if (isFloatSlowData(slowDataIndex)) {
            return Float.intBitsToFloat((int) rawValue);
        }
        return (float) rawValue;
    }

    private void refreshErrorCodeState()
    {
        if (!isValidSlowDataIndex(errorCodeSlowDataIndex)) {
            errorCodeKnown = false;
            updateErrorCodeDisplay();
            return;
        }

        errorCode = errorCodeAverage.next(getSlowDataValueAsFloat(errorCodeSlowDataIndex));
        errorCodeKnown = true;
        updateErrorCodeDisplay();
    }

    private void resetErrorCodeState()
    {
        errorCode = 0.0f;
        errorCodeKnown = false;
        errorCodeAverage = new MovingAverage(1);
        updateErrorCodeDisplay();
    }

    private void setErrorResetControlEnabled(boolean enabled)
    {
        if (viewSCOPE != null && viewSCOPE.getBtnErrorReset3() != null) {
            viewSCOPE.getBtnErrorReset3().setEnabled(enabled);
        }
    }

    private void updateErrorCodeDisplay()
    {
        JTextField errorField = viewSCOPE != null ? viewSCOPE.getTxtErrorCode() : null;
        if (errorField == null) {
            return;
        }

        boolean errorStatusActive = isErrorStatusActive();

        if (errorStatusActive) {
            if (errorCodeKnown && errorCode != 0.0f) {
                errorField.setText(ERROR_CODE_TEXT_PREFIX + numberFormatNoDecimals.format(errorCode));
            } else {
                errorField.setText(ERROR_CODE_TEXT_ACTIVE);
            }
            errorField.setForeground(ERROR_CODE_COLOR_ACTIVE);
            return;
        }

        if (!errorCodeKnown) {
            errorField.setText(ERROR_CODE_TEXT_UNAVAILABLE);
            errorField.setForeground(ERROR_CODE_COLOR_UNKNOWN);
            return;
        }

        if (errorCode == 0.0f) {
            errorField.setText(ERROR_CODE_TEXT_NO_ERROR);
            errorField.setForeground(ERROR_CODE_COLOR_OK);
            return;
        }

        errorField.setText(ERROR_CODE_TEXT_LATCHED_PREFIX + numberFormatNoDecimals.format(errorCode));
        errorField.setForeground(ERROR_CODE_COLOR_LATCHED);
    }

    private void autoSizeSlowDataVariableColumn(ArrayList<String> names) {
        if (viewSCOPE == null || viewSCOPE.getTbSlowData3() == null) {
            return;
        }
        javax.swing.JTable table = viewSCOPE.getTbSlowData3();
        FontMetrics metrics = table.getFontMetrics(table.getFont());
        int maxWidth = 0;
        for (int index = 1; index < names.size(); index++) {
            int width = metrics.stringWidth(names.get(index)) + 16;
            if (width > maxWidth) {
                maxWidth = width;
            }
        }
        int varMinWidth = 160;
        int varMaxWidth = 260;
        int cappedWidth = Math.min(varMaxWidth, Math.max(varMinWidth, maxWidth));
        javax.swing.table.TableColumnModel columns = table.getColumnModel();
        if (columns.getColumnCount() > 2) {
            int valueMinWidth = metrics.stringWidth("000000000000") + 16;
            int valuePrefWidth = columns.getColumn(2).getPreferredWidth();
            int reduceBy = (int)Math.round(valuePrefWidth * 0.1);
            int newValuePref = Math.max(valueMinWidth, valuePrefWidth - reduceBy);
            int gainedWidth = valuePrefWidth - newValuePref;
            int newVarPref = Math.min(varMaxWidth, cappedWidth + gainedWidth);

            columns.getColumn(1).setMinWidth(varMinWidth);
            columns.getColumn(1).setMaxWidth(varMaxWidth);
            columns.getColumn(1).setPreferredWidth(newVarPref);

            columns.getColumn(2).setMinWidth(valueMinWidth);
            columns.getColumn(2).setPreferredWidth(newValuePref);
        } else if (columns.getColumnCount() > 1) {
            columns.getColumn(1).setPreferredWidth(cappedWidth);
        }
    }

    private void reportHeaderMarkerIssue(String sectionName, String startMarker, String endMarker, JavascopeHeaderParser.SectionReadResult section)
    {
        if (section == null) {
            return;
        }
        if (section.getStartMarkerCount() == 1 && section.getEndMarkerCount() == 1) {
            return;
        }
        String fileLabel = section.getSourceFile() == null ? "javascope.h" : section.getSourceFile().getAbsolutePath();
        JOptionPane.showMessageDialog(
            null,
            "Invalid File: " + fileLabel + "\n"
                + "Section '" + sectionName + "' must contain exactly one start marker and one end marker.\n"
                + "Start marker '" + startMarker + "' found " + section.getStartMarkerCount() + " time(s).\n"
                + "End marker '" + endMarker + "' found " + section.getEndMarkerCount() + " time(s).",
            "Error",
            JOptionPane.INFORMATION_MESSAGE
        );
    }

    private boolean isValidSlowDataIndex(int slowDataIndex)
    {
        return slowDataSignalNames != null
            && slowDataIndex >= 0
            && slowDataIndex < slowDataSignalNames.size();
    }

    private void reportInvalidSlowDataDisplayEntries(List<String> missingEntries, File sourceFile)
    {
        if (missingEntries == null || missingEntries.isEmpty()) {
            return;
        }
        String fileLabel = sourceFile == null ? "javascope.h" : sourceFile.getAbsolutePath();
        StringBuilder message = new StringBuilder();
        message.append("Invalid File: ").append(fileLabel).append("\n")
            .append("Section 'SLOWDAT_DISPLAY' contains entries that are not present in JS_SlowData.\n")
            .append("The missing entries were replaced with ZEROVALUE:\n");
        for (String entry : missingEntries) {
            message.append(" - ").append(entry).append("\n");
        }
        logger.warning(message.toString());
        JOptionPane.showMessageDialog(
            null,
            message.toString(),
            "Error",
            JOptionPane.INFORMATION_MESSAGE
        );
    }

    private ArrayList<String> normalizeSlowDataDisplayEntries(ArrayList<String> entries, File sourceFile)
    {
        final int expectedEntryCount = 21; // zerovalue + 20 visible receive fields
        ArrayList<String> normalized = new ArrayList<>();
        if (entries != null) {
            normalized.addAll(entries);
        }

        if (normalized.isEmpty()) {
            normalized.add("ZEROVALUE");
        }

        String fileLabel = sourceFile == null ? "javascope.h" : sourceFile.getAbsolutePath();
        if (normalized.size() == expectedEntryCount + 1) {
            String ignoredEntry = normalized.get(normalized.size() - 1);
            System.out.println(
                "Note: " + fileLabel + " contains 21 SLOWDAT_DISPLAY entries for 20 receive fields. "
                    + "Ignoring the extra entry '" + ignoredEntry + "'."
            );
            normalized.remove(normalized.size() - 1);
        }

        if (normalized.size() < expectedEntryCount) {
            JOptionPane.showMessageDialog(
                null,
                "Invalid File: " + fileLabel + "\n"
                    + "Section 'SLOWDAT_DISPLAY' expected at least " + expectedEntryCount + " entries, but found "
                    + normalized.size() + ".\n"
                    + "Missing entries are filled with ZEROVALUE.",
                "Error",
                JOptionPane.INFORMATION_MESSAGE
            );
            while (normalized.size() < expectedEntryCount) {
                normalized.add("ZEROVALUE");
            }
        } else if (normalized.size() > expectedEntryCount + 1) {
            JOptionPane.showMessageDialog(
                null,
                "Invalid File: " + fileLabel + "\n"
                    + "Section 'SLOWDAT_DISPLAY' contains " + (normalized.size() - 1)
                    + " entries for 20 receive fields.\n"
                    + "Only the first 20 entries will be used.",
                "Error",
                JOptionPane.INFORMATION_MESSAGE
            );
            while (normalized.size() > expectedEntryCount) {
                normalized.remove(normalized.size() - 1);
            }
        }

        return normalized;
    }

    private ArrayList<String> ensureSectionEntryCount(ArrayList<String> input, int expectedEntries, String sectionName, String fallbackPrefix)
    {
        ArrayList<String> entries = new ArrayList<>();
        if (input != null) {
            entries.addAll(input);
        }
        if (entries.size() >= expectedEntries) {
            return entries;
        }
        JOptionPane.showMessageDialog(
            null,
            "Invalid File: javascope.h\n"
                + "Section '" + sectionName + "' expected at least " + expectedEntries + " entries, but found " + entries.size() + ".\n"
                + "Missing entries are filled with fallback placeholders.",
            "Error",
            JOptionPane.INFORMATION_MESSAGE
        );
        while (entries.size() < expectedEntries) {
            entries.add(fallbackPrefix + "_" + entries.size());
        }
        return entries;
    }
    

    public void readSndFieldDespcriptionsFromFileLineByLine() {
        try {
            final String startMarker = "SND_FLD_ZEROVALUE=0";
            final String endMarker = "SND_FLD_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.COMPACT_TEXT
            );
            reportHeaderMarkerIssue("SND_FLD", startMarker, endMarker, section);
            ArrayList<String> list = ensureSectionEntryCount(section.getEntries(), 21, "SND_FLD", "send_field");

            javax.swing.JPanel[] fields = new javax.swing.JPanel[] {
                viewSCOPE.getField_1(), viewSCOPE.getField_2(), viewSCOPE.getField_3(), viewSCOPE.getField_4(), viewSCOPE.getField_5(),
                viewSCOPE.getField_6(), viewSCOPE.getField_7(), viewSCOPE.getField_8(), viewSCOPE.getField_9(), viewSCOPE.getField_10(),
                viewSCOPE.getField_11(), viewSCOPE.getField_12(), viewSCOPE.getField_13(), viewSCOPE.getField_14(), viewSCOPE.getField_15(),
                viewSCOPE.getField_16(), viewSCOPE.getField_17(), viewSCOPE.getField_18(), viewSCOPE.getField_19(), viewSCOPE.getField_20()
            };
            for (int index = 0; index < fields.length; index++) {
                fields[index].setBorder(javax.swing.BorderFactory.createTitledBorder(list.get(index + 1)));
            }
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    }    

    public void readSndFieldLabelsFromFileLineByLine() {
        try {
            final String startMarker = "SND_LABELS_ZEROVALUE=0";
            final String endMarker = "SND_LABELS_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.COMPACT_TEXT
            );
            reportHeaderMarkerIssue("SND_LABELS", startMarker, endMarker, section);
            ArrayList<String> list = ensureSectionEntryCount(section.getEntries(), 21, "SND_LABELS", "unit");

            javax.swing.JLabel[] labels = new javax.swing.JLabel[] {
                viewSCOPE.getLbl_snd_fld_1(), viewSCOPE.getLbl_snd_fld_2(), viewSCOPE.getLbl_snd_fld_3(), viewSCOPE.getLbl_snd_fld_4(), viewSCOPE.getLbl_snd_fld_5(),
                viewSCOPE.getLbl_snd_fld_6(), viewSCOPE.getLbl_snd_fld_7(), viewSCOPE.getLbl_snd_fld_8(), viewSCOPE.getLbl_snd_fld_9(), viewSCOPE.getLbl_snd_fld_10(),
                viewSCOPE.getLbl_snd_fld_11(), viewSCOPE.getLbl_snd_fld_12(), viewSCOPE.getLbl_snd_fld_13(), viewSCOPE.getLbl_snd_fld_14(), viewSCOPE.getLbl_snd_fld_15(),
                viewSCOPE.getLbl_snd_fld_16(), viewSCOPE.getLbl_snd_fld_17(), viewSCOPE.getLbl_snd_fld_18(), viewSCOPE.getLbl_snd_fld_19(), viewSCOPE.getLbl_snd_fld_20()
            };
            for (int index = 0; index < labels.length; index++) {
                labels[index].setText(list.get(index + 1));
            }
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    } 
    
    
    public void readRcvFieldDespcriptionsFromFileLineByLine() {
        try {
            final String startMarker = "RCV_FLD_ZEROVALUE=0";
            final String endMarker = "RCV_FLD_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.COMPACT_TEXT
            );
            reportHeaderMarkerIssue("RCV_FLD", startMarker, endMarker, section);
            ArrayList<String> list = ensureSectionEntryCount(section.getEntries(), 21, "RCV_FLD", "receive_field");

            javax.swing.JPanel[] fields = new javax.swing.JPanel[] {
                viewSCOPE.getReceive_field_1(), viewSCOPE.getReceive_field_2(), viewSCOPE.getReceive_field_3(), viewSCOPE.getReceive_field_4(), viewSCOPE.getReceive_field_5(),
                viewSCOPE.getReceive_field_6(), viewSCOPE.getReceive_field_7(), viewSCOPE.getReceive_field_8(), viewSCOPE.getReceive_field_9(), viewSCOPE.getReceive_field_10(),
                viewSCOPE.getReceive_field_11(), viewSCOPE.getReceive_field_12(), viewSCOPE.getReceive_field_13(), viewSCOPE.getReceive_field_14(), viewSCOPE.getReceive_field_15(),
                viewSCOPE.getReceive_field_16(), viewSCOPE.getReceive_field_17(), viewSCOPE.getReceive_field_18(), viewSCOPE.getReceive_field_19(), viewSCOPE.getReceive_field_20()
            };
            for (int index = 0; index < fields.length; index++) {
                fields[index].setBorder(javax.swing.BorderFactory.createTitledBorder(list.get(index + 1)));
            }
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    }
    
    public void readRcvFieldLabelsFromFileLineByLine() {
        try {
            final String startMarker = "RCV_LABELS_ZEROVALUE=0";
            final String endMarker = "RCV_LABELS_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.COMPACT_TEXT
            );
            reportHeaderMarkerIssue("RCV_LABELS", startMarker, endMarker, section);
            ArrayList<String> list = ensureSectionEntryCount(section.getEntries(), 21, "RCV_LABELS", "unit");

            javax.swing.JLabel[] labels = new javax.swing.JLabel[] {
                viewSCOPE.getLbl_rcv_fld_1(), viewSCOPE.getLbl_rcv_fld_2(), viewSCOPE.getLbl_rcv_fld_3(), viewSCOPE.getLbl_rcv_fld_4(), viewSCOPE.getLbl_rcv_fld_5(),
                viewSCOPE.getLbl_rcv_fld_6(), viewSCOPE.getLbl_rcv_fld_7(), viewSCOPE.getLbl_rcv_fld_8(), viewSCOPE.getLbl_rcv_fld_9(), viewSCOPE.getLbl_rcv_fld_10(),
                viewSCOPE.getLbl_rcv_fld_11(), viewSCOPE.getLbl_rcv_fld_12(), viewSCOPE.getLbl_rcv_fld_13(), viewSCOPE.getLbl_rcv_fld_14(), viewSCOPE.getLbl_rcv_fld_15(),
                viewSCOPE.getLbl_rcv_fld_16(), viewSCOPE.getLbl_rcv_fld_17(), viewSCOPE.getLbl_rcv_fld_18(), viewSCOPE.getLbl_rcv_fld_19(), viewSCOPE.getLbl_rcv_fld_20()
            };
            for (int index = 0; index < labels.length; index++) {
                labels[index].setText(list.get(index + 1));
            }
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    }
        public void readMyButtonsLabelsFromFileLineByLine() {
        try {
            final String startMarker = "MYBUTTONS_LABELS_ZEROVALUE=0";
            final String endMarker = "MYBUTTONS_LABELS_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.COMPACT_TEXT
            );
            reportHeaderMarkerIssue("MYBUTTONS_LABELS", startMarker, endMarker, section);
            ArrayList<String> list = ensureSectionEntryCount(section.getEntries(), 9, "MYBUTTONS_LABELS", "MyButton");

            javax.swing.JButton[] buttons = new javax.swing.JButton[] {
                viewSCOPE.getMyBtn_1(), viewSCOPE.getMyBtn_2(), viewSCOPE.getMyBtn_3(), viewSCOPE.getMyBtn_4(),
                viewSCOPE.getMyBtn_5(), viewSCOPE.getMyBtn_6(), viewSCOPE.getMyBtn_7(), viewSCOPE.getMyBtn_8()
            };
            for (int index = 0; index < buttons.length; index++) {
                buttons[index].setText(list.get(index + 1));
            }
        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    }
    public int[] readRcvFieldSlowDataToDisplayFromFileLineByLine() {
        int[] indices = {0};
        try {
            final String startMarker = "SLOWDAT_DISPLAY_ZEROVALUE=0";
            final String endMarker = "SLOWDAT_DISPLAY_ENDMARKER";
            JavascopeHeaderParser.SectionReadResult section = JavascopeHeaderParser.readSection(
                startMarker,
                endMarker,
                JavascopeHeaderParser.ParseMode.IDENTIFIER
            );
            reportHeaderMarkerIssue("SLOWDAT_DISPLAY", startMarker, endMarker, section);

            ArrayList<String> list = new ArrayList<>();
            for (String token : section.getEntries()) {
                String line = token
                    .replace("JSSD_", "")
                    .replace("FLOAT_", "")
                    .replace("INT_", "");
                list.add(line);
            }
            list = normalizeSlowDataDisplayEntries(list, section.getSourceFile());

            //Get indices of SlowData to be displayed within the SlowData table
            indices = new int[list.size()];
            if (indices.length > 0) {
                indices[0] = 0;
            }
            ArrayList<String> missingEntries = new ArrayList<>();
            for (int listIndex = 1; listIndex < list.size(); listIndex++) {
                String signalName = list.get(listIndex);
                int signalIndex = slowDataSignalNames.indexOf(signalName);
                if (signalIndex < 0) {
                    missingEntries.add(signalName + " (display field " + listIndex + ")");
                    signalIndex = 0;
                }
                indices[listIndex] = signalIndex;
            }
            reportInvalidSlowDataDisplayEntries(missingEntries, section.getSourceFile());

        } catch (IOException exception) {
            exception.printStackTrace();
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
        
    return indices;
        
    }    
    
    /**
     * Returns whether scope acquisition/rendering is currently running.
     *
     * @return true when not stopped
     */
    public boolean getScopeRunStop() {
        return isScopeRunning();
    }

    /**
     * Function to stop or start the scope
     * 
     * @param value bool
     */
    public void setScopeRunStop(boolean value) {
        if (value) {
            if (acquisitionState == AcquisitionState.STOPPED) {
                acquisitionState = AcquisitionState.RUNNING;
            }
        } else {
            if (acquisitionMode == AcquisitionMode.SINGLE) {
                acquisitionMode = resolveContinuousAcquisitionMode();
            }
            acquisitionState = AcquisitionState.STOPPED;
            pendingGraphUpdate = false;
            resetTriggerCaptureState();
            dataPointCounter = 0;
        }
        updateSingleShotButtonState();
        set_Txt_RunStop();
    } 
    
    /**
     * Returns true, if the specified bit is equal to 1
     * 
     * @param bit_number specified bit number 
     * @return bool
     */
    public boolean is_status_bit_true(int bit_number) {
        boolean output = false;
        if (((adata.status >> bit_number) & 1) == 1) {
            output = true;
        }
        return output;
    }
    
    /**
     * Returns true, if the status-bit is different to the one from the previous time-step
     * 
     * @param status_bit specified bit_number
     * @return bool
     */
    public boolean did_status_bit_change(int status_bit) {
        return (((adata.status >> status_bit) & 1) != ((ledLastStatus >> status_bit) & 1));
    }
    
    /**
     * returns the value of is_first_call. It is true, if the update-function for the first time
     * 
     * @return 
     */
    public boolean get_is_first_call(){
        return is_first_call;
    }
    
    /**
     * Syncs ledLastStatus with current adata.status
     */
    public void sync_adata_with_old_adata(){
        ledLastStatus = adata.status;
    }
  
    /**
     * 
     * @return value of movingAverage at index (1-20)
     */
    public float getAverageValue(int index) {
        int slowDataIndex = JSSD_indices[index + 1];
        if (!isValidSlowDataIndex(slowDataIndex) || slowDataTableModel == null) {
            return 0.0f;
        }
        Object tableValue = slowDataTableModel.getValueAt(slowDataIndex, 2);
        if (tableValue == null) {
            return 0.0f;
        }
        try {
            return movingAverage.get(index).next(Float.parseFloat(tableValue.toString()));
        } catch (NumberFormatException exception) {
            return 0.0f;
        }
    }        
    
    /**
     * 
     * @return value of errorCode
     */
    public float getErCode() {
        return errorCode;
    }  
    
    /**
     * 
     * @return the logger to display information in the console
     */
    public Logger getLogger() {
        return logger;
    }
    
    /**
     * 
     * @return NumberFormat numberFormatPrecision8
     */
    public NumberFormat getNf() {
        return numberFormatPrecision8;
    }
    
    /**
     * 
     * @return NumberFormat numberFormatTwoDecimals
     */
    public NumberFormat getNf1() {
        return numberFormatTwoDecimals;
    }
    
    /**
     * 
     * @return NumberFormat numberFormatThreeDecimals
     */
    public NumberFormat getNf2() {
        return numberFormatThreeDecimals;
    }
    
    /**
     * 
     * @return NumberFormat numberFormatNoDecimals
     */
    public NumberFormat getNf3() {
        return numberFormatNoDecimals;
    }
    
    public DefaultTableModel getTableModel() {
        return slowDataTableModel;
    }
    /**
     * Returns true, if the update function in the ReceiveController has run once.
     * 
     * @return bool
     */
    public boolean get_update_func_runs() {
        return update_func_runs;
    }
 
    /**
     * Returns the chPanel of the ReceiveController
     * 
     * @return ChartPanel
     */
    public ChartPanel get_chPanel() {
        return chPanel;
    }
    
    public AnzeigeDaten get_adata() {
        return adata;
    }
    
    public void set_Txt_RunStop() {
        if (isScopeRunning()) {
            view.getTxt_RunStop().setText("►");
            view.getTxt_RunStop().setForeground(Color.green);
        } else {
            view.getTxt_RunStop().setText("||");
            view.getTxt_RunStop().setForeground(Color.red);
        }
    }

    private void updateSingleShotButtonState() {
        view.setSingleShotPending(isSingleShotArmed());
        view.getBtnSingleShot().setEnabled(connected);
    }
    
    
void ScalePlusMinusButton(int channelIndex, int plusminus)    // plus=1, minus=0
    {
        initChannelComponentArrays();
        if (channelIndex < 0 || channelIndex >= scaleCHx.length || channelIndex >= scaleFields.length) {
            return;
        }
        int plus=1, minus=0;
        JTextField scaleField = scaleFields[channelIndex];
        if (scaleField == null) {
            return;
        }
        double oldScaleValue = scaleCHx[channelIndex];
        double newScaleValue = 0.0;
        if (plusminus == minus)  {
            if (oldScaleValue <= 0.1)
                newScaleValue = oldScaleValue / 2.0;
            else if (oldScaleValue > 0.1 && oldScaleValue <= 0.2)
                newScaleValue = 0.1;
            else if (oldScaleValue > 0.2 && oldScaleValue <= 0.5)
                newScaleValue = 0.2;
            else if (oldScaleValue > 0.5 && oldScaleValue <= 1.0)
                newScaleValue = 0.5;
            else if (oldScaleValue > 1.0 && oldScaleValue <= 2.0)
                newScaleValue = 1.0;
            else if (oldScaleValue > 2.0 && oldScaleValue <= 5.0)
                newScaleValue = 2.0;
            else if (oldScaleValue > 5.0 && oldScaleValue <= 10.0)
                newScaleValue = 5.0;
            else if (oldScaleValue > 10.0 && oldScaleValue <= 20.0)
                newScaleValue = 10.0;
            else if (oldScaleValue > 20.0 && oldScaleValue <= 50.0)
                newScaleValue = 20.0;
            else if (oldScaleValue > 50.0 && oldScaleValue <= 100.0)
                newScaleValue = 50.0;
            else
                newScaleValue = oldScaleValue / 2.0;
        } else if (plusminus == plus)  {
            if (oldScaleValue <= 0.1)
                newScaleValue = oldScaleValue * 2.0;
            else if (oldScaleValue > 0.1 && oldScaleValue <= 0.2)
                newScaleValue = 0.5;
            else if (oldScaleValue > 0.2 && oldScaleValue <= 0.5)
                newScaleValue = 1.0;
            else if (oldScaleValue > 0.5 && oldScaleValue <= 1.0)
                newScaleValue = 2.0;
            else if (oldScaleValue > 1.0 && oldScaleValue <= 2.0)
                newScaleValue = 5.0;
            else if (oldScaleValue > 2.0 && oldScaleValue <= 5.0)
                newScaleValue = 10.0;
            else if (oldScaleValue > 5.0 && oldScaleValue <= 10.0)
                newScaleValue = 20.0;
            else if (oldScaleValue > 10.0 && oldScaleValue <= 20.0)
                newScaleValue = 50.0;
            else if (oldScaleValue > 20.0 && oldScaleValue <= 50.0)
                newScaleValue = 100.0;
            else if (oldScaleValue > 50.0 && oldScaleValue <= 100.0)
                newScaleValue = 200.0;
            else
                newScaleValue = oldScaleValue * 2.0;
        }
        scaleCHx[channelIndex] = newScaleValue;
        scaleField.setText(Double.toString(newScaleValue));
        markScaleOffsetValid(scaleField);
    }

    

    @Override
    public void windowOpened(WindowEvent windowEvent) {
    }

    @Override
    public void windowClosing(WindowEvent windowEvent) {
        System.out.println("Closing!");
        suppressSlowLoggingSessionSummary = true;
        try {
            if (view != null && view.getBtnDisconnect() != null && view.getBtnDisconnect().isEnabled()) {
                view.getBtnDisconnect().doClick();
            } else if (connected && transmitter != null) {
                transmitter.disconnect();
            }
        } catch (Exception exception) {
            logger.severe("Disconnect on close failed: " + exception.toString());
        }
        try
        {
            synchronized (logWriteLock) {
                if (logWriter != null) {
                    finishSlowLoggingSession();
                    logWriter.close();
                    logWriter = null;
                }
            }
        }
        catch (Exception exception)
        {
            System.out.print(exception.toString());
            JOptionPane.showMessageDialog(null, exception.toString(), "Exception" , JOptionPane.INFORMATION_MESSAGE);
        }
    }

    @Override
    public void windowClosed(WindowEvent windowEvent) {
    }

    @Override
    public void windowIconified(WindowEvent windowEvent) {
    }

    @Override
    public void windowDeiconified(WindowEvent windowEvent) {
    }

    @Override
    public void windowActivated(WindowEvent windowEvent) {
    }

    @Override
    public void windowDeactivated(WindowEvent windowEvent) {
    }

    private void initChannelVisibilityButtons() {
        channelVisibilityButtons = viewSCOPE.getChannelVisibilityButtons();
        if (channelVisibilityButtons == null || chPanel == null) {
            return;
        }

        XYItemRenderer renderer = chPanel.getChart().getXYPlot().getRenderer();
        int count = Math.min(chnum, channelVisibilityButtons.length);
        channelVisibilityColors = new Color[count];

        for (int i = 0; i < count; i++) {
            javax.swing.JToggleButton button = channelVisibilityButtons[i];
            if (button == null) {
                continue;
            }
            Color color = extractColor(renderer.getSeriesPaint(i));
            if (color == null) {
                color = Color.white;
            }
            channelVisibilityColors[i] = color;
            button.setText("CH" + (i + 1));
            button.setSelected(true);
            updateChannelToggleAppearance(i, true);
            final int idx = i;
            button.addActionListener(evt -> toggleChannelVisibility(idx, button.isSelected()));
        }

        for (int i = count; i < channelVisibilityButtons.length; i++) {
            if (channelVisibilityButtons[i] != null) {
                channelVisibilityButtons[i].setVisible(false);
            }
        }

        javax.swing.JButton disableAllButton = viewSCOPE.getBtnDisableAllChannels();
        if (disableAllButton != null) {
            disableAllButton.addActionListener(evt -> setAllChannelVisibility(false));
        }
        javax.swing.JButton enableAllButton = viewSCOPE.getBtnEnableAllChannels();
        if (enableAllButton != null) {
            enableAllButton.addActionListener(evt -> setAllChannelVisibility(true));
        }

        if (chPanel.getChart().getLegend() != null) {
            chPanel.getChart().getLegend().setVisible(false);
        }
    }

    private void initScaleOffsetFields() {
        initChannelComponentArrays();
        if (scaleOffsetListenersInitialized) {
            return;
        }

        JTextField sampleField = scaleFields.length > 0 ? scaleFields[0] : null;
        if (sampleField != null) {
            scaleOffsetBaseFont = sampleField.getFont();
            scaleOffsetBaseColor = sampleField.getForeground();
        }

        ActionListener applyListener = event -> applyScaleOffsetFromField((JTextField) event.getSource());
        java.awt.event.FocusListener focusListener = new java.awt.event.FocusAdapter() {
            @Override
            public void focusLost(java.awt.event.FocusEvent event) {
                applyScaleOffsetFromField((JTextField) event.getSource());
            }
        };

        registerScaleOffsetListeners(scaleFields, applyListener, focusListener);
        registerScaleOffsetListeners(offsetFields, applyListener, focusListener);
        scaleOffsetListenersInitialized = true;
    }

    private void initFieldCollections()
    {
        if (sendFields == null) {
            sendFields = Arrays.asList(
                viewSCOPE.getTxt_snd_fld_1(), viewSCOPE.getTxt_snd_fld_2(), viewSCOPE.getTxt_snd_fld_3(), viewSCOPE.getTxt_snd_fld_4(),
                viewSCOPE.getTxt_snd_fld_5(), viewSCOPE.getTxt_snd_fld_6(), viewSCOPE.getTxt_snd_fld_7(), viewSCOPE.getTxt_snd_fld_8(),
                viewSCOPE.getTxt_snd_fld_9(), viewSCOPE.getTxt_snd_fld_10(), viewSCOPE.getTxt_snd_fld_11(), viewSCOPE.getTxt_snd_fld_12(),
                viewSCOPE.getTxt_snd_fld_13(), viewSCOPE.getTxt_snd_fld_14(), viewSCOPE.getTxt_snd_fld_15(), viewSCOPE.getTxt_snd_fld_16(),
                viewSCOPE.getTxt_snd_fld_17(), viewSCOPE.getTxt_snd_fld_18(), viewSCOPE.getTxt_snd_fld_19(), viewSCOPE.getTxt_snd_fld_20()
            );
        }
        if (rcvFields == null) {
            rcvFields = Arrays.asList(
                viewSCOPE.getTxt_rcv_fld_1(), viewSCOPE.getTxt_rcv_fld_2(), viewSCOPE.getTxt_rcv_fld_3(), viewSCOPE.getTxt_rcv_fld_4(),
                viewSCOPE.getTxt_rcv_fld_5(), viewSCOPE.getTxt_rcv_fld_6(), viewSCOPE.getTxt_rcv_fld_7(), viewSCOPE.getTxt_rcv_fld_8(),
                viewSCOPE.getTxt_rcv_fld_9(), viewSCOPE.getTxt_rcv_fld_10(), viewSCOPE.getTxt_rcv_fld_11(), viewSCOPE.getTxt_rcv_fld_12(),
                viewSCOPE.getTxt_rcv_fld_13(), viewSCOPE.getTxt_rcv_fld_14(), viewSCOPE.getTxt_rcv_fld_15(), viewSCOPE.getTxt_rcv_fld_16(),
                viewSCOPE.getTxt_rcv_fld_17(), viewSCOPE.getTxt_rcv_fld_18(), viewSCOPE.getTxt_rcv_fld_19(), viewSCOPE.getTxt_rcv_fld_20()
            );
        }
    }

    private void setSendFieldsEnabled(boolean enabled)
    {
        initFieldCollections();
        for (javax.swing.JTextField field : sendFields) {
            if (field != null) {
                field.setEnabled(enabled);
            }
        }
    }

    private void initMovingAverages()
    {
        if (movingAverage != null) {
            return;
        }
        movingAverage = new ArrayList<>(MAX_CHANNELS);
        for (int channelIndex = 0; channelIndex < MAX_CHANNELS; channelIndex++) {
            movingAverage.add(new MovingAverage(20));
        }
    }

    private void initTriggerControls() {
        if (triggerControlsInitialized) {
            return;
        }
        javax.swing.JTextField triggerField = view.getTxtTriggerValue();
        if (triggerField != null) {
            triggerValueBaseFont = triggerField.getFont();
            triggerValueBaseColor = triggerField.getForeground();
            ActionListener applyListener = event -> applyTriggerFromUi(true, true, true);
            java.awt.event.FocusListener focusListener = new java.awt.event.FocusAdapter() {
                @Override
                public void focusLost(java.awt.event.FocusEvent event) {
                    applyTriggerFromUi(true, true, true);
                }
            };
            triggerField.addActionListener(applyListener);
            triggerField.addFocusListener(focusListener);
        }

        syncTriggerUiFromMode();

        javax.swing.JComboBox<String> triggerCombo = view.getComboTrigger();
        if (triggerCombo != null) {
            triggerCombo.addActionListener(event -> applyTriggerFromUi(false, true, true));
        }

        javax.swing.JToggleButton triggerEnableButton = view.getBtnTriggerEnabled();
        if (triggerEnableButton != null) {
            triggerEnableButton.addActionListener(event -> applyTriggerFromUi(false, true, false));
        }

        javax.swing.JToggleButton triggerEdgeButton = view.getBtnTriggerEdge();
        if (triggerEdgeButton != null) {
            triggerEdgeButton.addActionListener(event -> applyTriggerFromUi(false, true, true));
        }

        javax.swing.JSlider preTriggerSlider = view.getSliPreTrigger();
        if (preTriggerSlider != null) {
            preTriggerSlider.addChangeListener(event -> applyTriggerFromUi(false, true, true));
        }
        triggerControlsInitialized = true;
    }

    private void initTimeBaseControls() {
        if (timeBaseControlsInitialized) {
            return;
        }
        javax.swing.JComboBox<String> timeBaseCombo = view.getComboTimeBase();
        if (timeBaseCombo != null) {
            timeBaseCombo.addActionListener(event -> applyTimeBaseFromUi());
        }
        timeBaseControlsInitialized = true;
    }

    private void registerScaleOffsetListeners(JTextField[] fields, ActionListener actionListener, java.awt.event.FocusListener focusListener) {
        if (fields == null) {
            return;
        }
        for (JTextField field : fields) {
            if (field == null) {
                continue;
            }
            field.addActionListener(actionListener);
            field.addFocusListener(focusListener);
        }
    }

    private void applyScaleOffsetFromField(JTextField field) {
        if (field == null) {
            return;
        }
        int scaleIndex = indexOf(scaleFields, field);
        if (scaleIndex >= 0) {
            applyScaleOffsetValue(field, scaleCHx, scaleIndex);
            return;
        }
        int offsetIndex = indexOf(offsetFields, field);
        if (offsetIndex >= 0) {
            applyScaleOffsetValue(field, offsetCHx, offsetIndex);
        }
    }

    private void applyScaleOffsetValue(JTextField field, double[] target, int index) {
        String raw = field.getText();
        if (raw == null) {
            markScaleOffsetInvalid(field);
            return;
        }
        String normalized = raw.trim().replace(',', '.');
        if (normalized.isEmpty()) {
            markScaleOffsetInvalid(field);
            return;
        }
        try {
            double value = Double.parseDouble(normalized);
            if (index >= 0 && index < target.length) {
                target[index] = value;
            }
            markScaleOffsetValid(field);
        } catch (NumberFormatException ex) {
            markScaleOffsetInvalid(field);
        }
    }

    private int indexOf(JTextField[] fields, JTextField field) {
        if (fields == null) {
            return -1;
        }
        for (int i = 0; i < fields.length; i++) {
            if (fields[i] == field) {
                return i;
            }
        }
        return -1;
    }

    private void markScaleOffsetValid(JTextField field) {
        if (scaleOffsetBaseFont != null) {
            field.setFont(scaleOffsetBaseFont);
        }
        if (scaleOffsetBaseColor != null) {
            field.setForeground(scaleOffsetBaseColor);
        }
    }

    private void markScaleOffsetInvalid(JTextField field) {
        if (scaleOffsetBaseFont != null) {
            field.setFont(scaleOffsetBaseFont.deriveFont(Font.BOLD));
        } else {
            field.setFont(field.getFont().deriveFont(Font.BOLD));
        }
        field.setForeground(SCALE_OFFSET_INVALID_COLOR);
    }

    private void applyTriggerFromUi(boolean requireValidValue) {
        applyTriggerFromUi(requireValidValue, true, true);
    }

    private void applyTriggerFromUi(boolean requireValidValue, boolean requestImmediateRefresh) {
        applyTriggerFromUi(requireValidValue, requestImmediateRefresh, true);
    }

    private void applyTriggerFromUi(boolean requireValidValue, boolean requestImmediateRefresh, boolean autoEnableTrigger) {
        javax.swing.JToggleButton triggerEnableButton = view.getBtnTriggerEnabled();
        boolean triggerEnabled = triggerEnableButton != null && triggerEnableButton.isSelected();
        if (autoEnableTrigger && triggerEnableButton != null && !triggerEnabled) {
            view.setTriggerEnabled(true);
            triggerEnabled = true;
        }

        int triggerChannel = 0;
        javax.swing.JComboBox<String> triggerCombo = view.getComboTrigger();
        if (triggerEnabled && triggerCombo != null) {
            int selectedIndex = triggerCombo.getSelectedIndex();
            if (selectedIndex >= 0) {
                triggerChannel = selectedIndex + 1;
            }
        }

        int triggerEdge = 1;
        javax.swing.JToggleButton triggerEdgeButton = view.getBtnTriggerEdge();
        if (triggerEdgeButton != null) {
            triggerEdge = triggerEdgeButton.isSelected() ? 1 : 2;
        }
        triggermode = toTriggerMode(triggerChannel, triggerEdge);
        syncTriggerUiFromMode();

        boolean valueValid = true;
        javax.swing.JTextField triggerField = view.getTxtTriggerValue();
        if (triggerField != null) {
            String raw = triggerField.getText();
            String normalized = raw == null ? "" : raw.trim().replace(',', '.');
            if (normalized.isEmpty()) {
                valueValid = false;
                markTriggerValueInvalid(triggerField);
            } else {
                try {
                    triggervalue = Double.parseDouble(normalized);
                    markTriggerValueValid(triggerField);
                } catch (NumberFormatException ex) {
                    valueValid = false;
                    markTriggerValueInvalid(triggerField);
                }
            }
        }

        int slival = view.getSliPreTrigger().getValue();
        pretrigger = ((double) slival) / 10.0;

        if (requireValidValue && !valueValid) {
            return;
        }

        AcquisitionMode continuousMode = resolveContinuousAcquisitionMode();
        if (acquisitionMode == AcquisitionMode.SINGLE) {
            if (triggermode <= 0) {
                acquisitionMode = continuousMode;
                if (isScopeRunning()) {
                    acquisitionState = AcquisitionState.RUNNING;
                }
            } else if (isScopeRunning()) {
                acquisitionState = AcquisitionState.ARMED;
            }
        } else {
            acquisitionMode = continuousMode;
        }

        System.out.println("Trigger: mode = " + triggermode + ", trigval = " + triggervalue + ", pretrig = " + pretrigger);
        resetTriggerCaptureState();
        updateSingleShotButtonState();
        if (requestImmediateRefresh) {
            requestImmediateTriggerRefresh();
        }
    }

    private void syncTriggerUiFromMode()
    {
        int triggerChannel = toTriggerChannel(triggermode);
        int triggerEdge = toTriggerEdge(triggermode);
        boolean triggerEnabled = triggerChannel > 0;

        view.setTriggerEnabled(triggerEnabled);

        javax.swing.JComboBox<String> triggerCombo = view.getComboTrigger();
        if (triggerCombo != null) {
            int maxIndex = Math.max(0, triggerCombo.getItemCount() - 1);
            if (triggerEnabled) {
                int selectedIndex = Math.max(0, Math.min(triggerChannel - 1, maxIndex));
                if (triggerCombo.getSelectedIndex() != selectedIndex) {
                    triggerCombo.setSelectedIndex(selectedIndex);
                }
            }
            triggerCombo.setEnabled(true);
        }

        javax.swing.JToggleButton triggerEdgeButton = view.getBtnTriggerEdge();
        if (triggerEdgeButton != null) {
            boolean rising = triggerEnabled ? (triggerEdge != 2) : triggerEdgeButton.isSelected();
            view.setTriggerEdgeRising(rising);
            triggerEdgeButton.setEnabled(true);
        }
    }

    private void updateTriggerOverlay(int currentTriggermode, double currentTriggervalue, double currentPretrigger, double xStep, boolean isDarkMode)
    {
        chPanel.removeOverlay(crosshairOverlay);
        crosshairOverlay.clearDomainCrosshairs();
        crosshairOverlay.clearRangeCrosshairs();
        if (currentTriggermode <= 0) {
            return;
        }

        int triggerChannel = toTriggerChannel(currentTriggermode);
        double yCoord = toDisplayValueForChannel(currentTriggervalue, triggerChannel - 1);
        float[] dash = {2f, 0f, 2f};
        int pretriggerSamplesCrosshair = (int)Math.round(currentPretrigger * (ringBufferSamples - 1));
        double xCrossVal = pretriggerSamplesCrosshair * xStep;
        Color crossColor = isDarkMode ? Color.WHITE : Color.GRAY;
        Crosshair xCrosshair = new Crosshair(xCrossVal, crossColor, new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND, 1.0f, dash, 2f));
        xCrosshair.setLabelPaint(Color.BLACK);
        xCrosshair.setLabelBackgroundPaint(Color.ORANGE);
        xCrosshair.setLabelVisible(true);
        Crosshair yCrosshair = new Crosshair(yCoord, crossColor, new BasicStroke(1, BasicStroke.CAP_BUTT, BasicStroke.JOIN_ROUND, 1.0f, dash, 2f));
        yCrosshair.setLabelPaint(Color.BLACK);
        yCrosshair.setLabelBackgroundPaint(Color.ORANGE);
        yCrosshair.setLabelVisible(true);
        crosshairOverlay.addDomainCrosshair(xCrosshair);
        crosshairOverlay.addRangeCrosshair(yCrosshair);
        chPanel.addOverlay(crosshairOverlay);
    }

    private double toDisplayValueForChannel(double rawValue, int channelIndex)
    {
        if (scaleCHx == null || offsetCHx == null) {
            return rawValue;
        }
        if (channelIndex < 0 || channelIndex >= chnum || channelIndex >= scaleCHx.length || channelIndex >= offsetCHx.length) {
            return rawValue;
        }
        double scale = scaleCHx[channelIndex];
        double offset = offsetCHx[channelIndex];
        if (!Double.isFinite(scale) || Math.abs(scale) < 1e-12 || !Double.isFinite(offset)) {
            return rawValue;
        }
        return (rawValue + offset) / scale;
    }

    private void requestImmediateTriggerRefresh()
    {
        // While single-shot is armed, applying trigger settings must re-arm trigger logic
        // without forcing an immediate capture completion/update.
        final boolean singleShotArmed = isSingleShotArmed();
        if (!singleShotArmed && isScopeRunning()) {
            ringReadPtr = scopeRingBuffer.snapshotWritePtr();
            pendingGraphUpdate = true;
        }
        final int currentTriggermode = triggermode;
        final double currentTriggervalue = triggervalue;
        final double currentPretrigger = pretrigger;
        final double xStep = smallestTimeStep_usec * 0.000001 * timeFactor;
        SwingUtilities.invokeLater(() -> {
            updateTriggerOverlay(currentTriggermode, currentTriggervalue, currentPretrigger, xStep, true);
            chPanel.repaint();
        });
    }

    private void applyTimeBaseFromUi() {
        int selectedIndex = view.getComboTimeBase().getSelectedIndex();
        if (selectedIndex < 0 || selectedIndex >= TIMEBASE_FACTORS.length) {
            return;
        }
        timeFactor = TIMEBASE_FACTORS[selectedIndex];
        updateDomainRange();
    }

    private void markTriggerValueValid(JTextField field) {
        if (triggerValueBaseFont != null) {
            field.setFont(triggerValueBaseFont);
        }
        if (triggerValueBaseColor != null) {
            field.setForeground(triggerValueBaseColor);
        }
    }

    private void markTriggerValueInvalid(JTextField field) {
        if (triggerValueBaseFont != null) {
            field.setFont(triggerValueBaseFont.deriveFont(Font.BOLD));
        } else {
            field.setFont(field.getFont().deriveFont(Font.BOLD));
        }
        field.setForeground(SCALE_OFFSET_INVALID_COLOR);
    }

    private void initChannelSelectListeners() {
        if (channelSelectListenersInitialized) {
            return;
        }
        initChannelComponentArrays();
        ActionListener listener = this::handleChannelSelectionChanged;
        for (javax.swing.JComboBox<String> combo : channelSelectCombos) {
            if (combo != null) {
                combo.addActionListener(listener);
            }
        }
        channelSelectListenersInitialized = true;
    }

    private void handleChannelSelectionChanged(ActionEvent event) {
        if (suppressSelectDataEvents) {
            return;
        }
        Object source = event.getSource();
        for (int channelIndex = 0; channelIndex < channelSelectCombos.size(); channelIndex++) {
            javax.swing.JComboBox<String> combo = channelSelectCombos.get(channelIndex);
            if (combo == source) {
                toggleChannelVisibility(channelIndex, !isZeroValueSelection(combo), false);
                markLogChannelSelectionDirty();
                refreshLifecheckMonitorSignalsFromSelectedChannels();
                if (connected && sendCont != null) {
                    sendCont.sendSelectDataSingle(channelIndex, combo.getSelectedIndex());
                }
                return;
            }
        }
    }

    private void applyZeroValueChannelVisibility() {
        if (channelSelectCombos == null) {
            return;
        }
        int count = Math.min(chnum, channelSelectCombos.size());
        for (int channelIndex = 0; channelIndex < count; channelIndex++) {
            javax.swing.JComboBox<String> combo = channelSelectCombos.get(channelIndex);
            toggleChannelVisibility(channelIndex, !isZeroValueSelection(combo));
        }
    }

    private boolean isZeroValueSelection(javax.swing.JComboBox<String> combo) {
        if (combo == null) {
            return false;
        }
        if (combo.getSelectedIndex() == 0) {
            return true;
        }
        Object selectedItem = combo.getSelectedItem();
        if (selectedItem == null) {
            return false;
        }
        String normalized = selectedItem.toString().replace(" ", "").toUpperCase(Locale.US);
        return normalized.contains(ZERO_VALUE);
    }

    private void toggleChannelVisibility(int index, boolean visible) {
        toggleChannelVisibility(index, visible, true);
    }

    private void toggleChannelVisibility(int index, boolean visible, boolean fillFromSnapshot) {
        XYItemRenderer renderer = chPanel.getChart().getXYPlot().getRenderer();
        renderer.setSeriesVisible(index, visible, true);
        updateLegendItemPaint(index, visible);
        updateChannelToggleAppearance(index, visible);
        if (visible && fillFromSnapshot) {
            fillSeriesFromLastSnapshot(index);
        }
    }

    private void fillSeriesFromLastSnapshot(int index) {
        double[][] snapshot = lastRenderedSnapshot;
        if (snapshot == null || index < 0 || index >= snapshot.length) {
            return;
        }
        if (chartSeries == null || index >= chartSeries.length || chartSeries[index] == null) {
            return;
        }
        if (chartSeries[index].getItemCount() > 0) {
            return;  // series already populated from last render, nothing to restore
        }
        if (scopeRingBuffer == null) {
            return;
        }
        final double xStep = smallestTimeStep_usec * 0.000001 * timeFactor;
        final double[] channelData = snapshot[index];
        final int bufferLen = Math.min(scopeRingBuffer.getSizePerChannel(), channelData.length);
        if (bufferLen == 0) {
            return;
        }
        chartSeries[index].setNotify(false);
        for (int sampleIndex = 0; sampleIndex < bufferLen; sampleIndex++) {
            chartSeries[index].add(sampleIndex * xStep, channelData[sampleIndex]);
        }
        chartSeries[index].setNotify(true);
    }

    private void setAllChannelVisibility(boolean visible) {
        if (channelVisibilityButtons == null || chPanel == null) {
            return;
        }
        int count = Math.min(chnum, channelVisibilityButtons.length);
        for (int i = 0; i < count; i++) {
            boolean targetVisible = visible;
            if (visible && channelSelectCombos != null && i < channelSelectCombos.size()) {
                targetVisible = !isZeroValueSelection(channelSelectCombos.get(i));
            }
            toggleChannelVisibility(i, targetVisible);
        }
    }

    private void updateChannelToggleAppearance(int index, boolean visible) {
        if (channelVisibilityButtons == null || index < 0 || index >= channelVisibilityButtons.length) {
            return;
        }
        javax.swing.JToggleButton button = channelVisibilityButtons[index];
        if (button == null) {
            return;
        }
        button.setSelected(visible);
        Color color = CHANNEL_DISABLED_COLOR;
        if (visible && channelVisibilityColors != null && index < channelVisibilityColors.length) {
            Color seriesColor = channelVisibilityColors[index];
            if (seriesColor != null) {
                color = seriesColor;
            }
        }
        button.setForeground(color);
    }

    private void updateLegendItemPaint(int index, boolean visible) {
        try {
            LegendItemCollection items = chPanel.getChart().getXYPlot().getLegendItems();
            if (items != null && index >= 0 && index < items.getItemCount()) {
                items.get(index).setLabelPaint(visible ? LEGEND_VISIBLE_COLOR : null);
            }
        } catch (Exception ignored) {
            // Legend might be hidden or unavailable.
        }
    }

    private Color extractColor(Paint paint) {
        if (paint instanceof Color) {
            return (Color) paint;
        }
        return null;
    }

    public ChartMouseListener chartMouseListener = new ChartMouseListener() {
            @Override
            public void chartMouseMoved(ChartMouseEvent mouseEvent) {
            }
            @Override
            public void chartMouseClicked(ChartMouseEvent chartMouseEvent) {
                ChartEntity entity = chartMouseEvent.getEntity();
                if (chartMouseEvent.getEntity() instanceof LegendItemEntity) {
                  LegendItemEntity itemEntity = (LegendItemEntity) entity;
                  XYDataset dataset = (XYDataset) itemEntity.getDataset();
                  int index = dataset.indexOf(itemEntity.getSeriesKey());
                  XYPlot plot = (XYPlot) chartMouseEvent.getChart().getPlot();

                  //set the renderer to hide the series
                  XYItemRenderer renderer = plot.getRenderer();
                  renderer.setSeriesVisible(index, !renderer.isSeriesVisible(index), true);
                  boolean visible = renderer.isSeriesVisible(index);
                  updateLegendItemPaint(index, visible);
                  updateChannelToggleAppearance(index, visible);
            }
        }
    };
    
     
    
    } 
