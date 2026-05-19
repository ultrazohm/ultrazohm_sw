/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package UZ_GUI;


import java.io.DataInputStream;
import java.io.DataOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.net.SocketException;
import java.net.SocketTimeoutException;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.channels.FileChannel;
import java.nio.channels.FileLock;
import java.nio.channels.OverlappingFileLockException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.nio.file.StandardOpenOption;
import java.time.Instant;
import java.time.ZoneId;
import java.time.format.DateTimeFormatter;
import java.util.ArrayDeque;
import java.util.ArrayList;
import java.util.List;
import java.util.Locale;
import java.util.concurrent.CopyOnWriteArrayList;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JOptionPane;
import java.util.Properties;

/**
 *
 * @author z002311d
 */
public class Transmitter implements Runnable
{
    final static int ANZAHL_MESSWERTE = 22; 
    int ANZAHL_MESSREIHEN_PRO_TCP_PAKET =0; //Init with 0, because read chosen number from property-file 
    final static int BYTE_NUMBER_PER_TCP_PACKAGE = 2048; 
    private static final int DEFAULT_SOCKET_TIMEOUT_MS = 5000;
    private final int expectedPacketBytes;
    private static final DateTimeFormatter DIAGNOSTIC_TIME_FORMAT =
            DateTimeFormatter.ofPattern("yyyy-MM-dd HH:mm:ss.SSSXXX", Locale.US);
    private static final ZoneId DIAGNOSTIC_TIME_ZONE = ZoneId.systemDefault();
    
    // IP settings and number of channels are configured in the property file in the JavaScope folder.
    private Logger logger = Logger.getLogger("Chat");
    final static int PORT = 1000;
    private static final boolean DEFAULT_SINGLE_INSTANCE_SOCKET_GUARD_ENABLED = true;
    private String ipAddress;
    private String statusMessage;
    private Thread clientThread;

    private OutputStream outputStream;
    private DataOutputStream dataOutputStream;
    
    private InputStream inputStream;
    private DataInputStream dataInputStream;
    int bytesRead;
    
    private int demoMode;
    
    long currentCommand;
    int pendingCommandCount;
    ArrayDeque<Long> pendingCommandQueue;

    private Socket socket;
    private FileChannel connectionLockChannel;
    private FileLock connectionLock;
    private Path connectionLockPath;
    private boolean connectionValid; 
    private volatile boolean disconnectRequested;
    private volatile boolean connectionTimeoutEnabled;
    private volatile boolean suppressZeroCommandReplies;
    private volatile boolean printSentCommands;
    private volatile boolean singleInstanceSocketGuardEnabled;
    private final Object commandWriteLock = new Object();
    private String receivedText;
    private byte[] receiveBuffer;
    private UZ_GUI_view view;
    private long connectionStartMillis;
    private long lastPacketReadMillis;
    private long totalPacketsReceived;
    private long totalBytesReceived;
    private int lastSuccessfulReadBytes;
    AnzeigeDaten displayDataBuffer;
    private final List<TransmitterListener> listeners = new CopyOnWriteArrayList<TransmitterListener>();

    // Preallocated buffers for parsing (avoids 330+ allocations per packet)
    private ByteBuffer parseBuffer;
    private long[] slowDataContentBuffer;
    private float[] cacheBuffer;
    private final PropertyFileDiagnostics propertyDiagnostics;


    public Transmitter(int demoMode, Properties prop, UZ_GUI_view view)   // 0=normal, 1=demo-mode
    {
        ipAddress = "localhost";
        statusMessage = "nothing";
        receivedText = "";
        outputStream = null;
        inputStream = null;
        clientThread = new Thread(this);
        currentCommand = 0;
        pendingCommandCount = 0;
        pendingCommandQueue = new ArrayDeque<Long>();
        connectionValid = true;
        disconnectRequested = false;
        connectionTimeoutEnabled = true;
        suppressZeroCommandReplies = false;
        printSentCommands = false;
        singleInstanceSocketGuardEnabled = readBooleanProperty(
                prop,
                "singleInstanceSocketGuardEnabled",
                DEFAULT_SINGLE_INSTANCE_SOCKET_GUARD_ENABLED
        );
        this.demoMode = demoMode;
        this.view = view;
        connectionStartMillis = 0;
        lastPacketReadMillis = 0;
        totalPacketsReceived = 0;
        totalBytesReceived = 0;
        lastSuccessfulReadBytes = 0;
        propertyDiagnostics = PropertyFileDiagnostics.loadDefault();
        ANZAHL_MESSREIHEN_PRO_TCP_PAKET = readMeasurementsPerPacket(prop);
        expectedPacketBytes = calculateExpectedPacketBytes(ANZAHL_MESSREIHEN_PRO_TCP_PAKET);
        if (expectedPacketBytes > BYTE_NUMBER_PER_TCP_PACKAGE) {
            logger.warning("Expected packet size " + expectedPacketBytes
                    + " exceeds legacy receive buffer size " + BYTE_NUMBER_PER_TCP_PACKAGE
                    + ". Using dynamic receive buffer for full-frame reads.");
        }
        receiveBuffer = new byte[Math.max(BYTE_NUMBER_PER_TCP_PACKAGE, expectedPacketBytes)];
        System.out.println("Chosen measurements per TCP packet = " + ANZAHL_MESSREIHEN_PRO_TCP_PAKET);
        System.out.println("Expected TCP payload per packet = " + expectedPacketBytes + " bytes");
        System.out.println("printSentCommands = 0 (runtime toggle via ScopeDev)");

        // Preallocate parsing buffers (avoids 330+ allocations per packet)
        parseBuffer = ByteBuffer.wrap(receiveBuffer).order(ByteOrder.LITTLE_ENDIAN);
        slowDataContentBuffer = new long[ANZAHL_MESSREIHEN_PRO_TCP_PAKET];
        cacheBuffer = new float[(ANZAHL_MESSWERTE - 1) * ANZAHL_MESSREIHEN_PRO_TCP_PAKET];

        // Preallocate AnzeigeDaten (reused each packet, safe because listener callback is synchronous)
        displayDataBuffer = new AnzeigeDaten(ANZAHL_MESSREIHEN_PRO_TCP_PAKET);
    }

    private int readMeasurementsPerPacket(Properties prop)
    {
        final int defaultValue = 15;
        String value = prop.getProperty("MEASUREMENTS_PER_TCP_PACKET");
        if (value == null) {
            return defaultValue;
        }
        String normalized = value.trim().replace(',', '.');
        if (normalized.isEmpty()) {
            propertyDiagnostics.printInvalidScalar(
                    "MEASUREMENTS_PER_TCP_PACKET",
                    value,
                    "a positive integer",
                    Integer.toString(defaultValue)
            );
            return defaultValue;
        }

        double parsed;
        try {
            parsed = Double.parseDouble(normalized);
        } catch (NumberFormatException exception) {
            propertyDiagnostics.printInvalidScalar(
                    "MEASUREMENTS_PER_TCP_PACKET",
                    value,
                    "a positive integer",
                    Integer.toString(defaultValue)
            );
            return defaultValue;
        }

        int packetCount = (int) parsed;
        if (packetCount <= 0) {
            propertyDiagnostics.printValidationIssue(
                    "MEASUREMENTS_PER_TCP_PACKET",
                    "Value " + value.trim() + " must be > 0. Using " + defaultValue + "."
            );
            return defaultValue;
        }
        if (Math.abs(parsed - packetCount) > 1e-9) {
            propertyDiagnostics.printValidationIssue(
                    "MEASUREMENTS_PER_TCP_PACKET",
                    "Value " + value.trim() + " is not an integer. Using truncated value " + packetCount + "."
            );
        }
        return packetCount;
    }

    private boolean readBooleanProperty(Properties prop, String key, boolean defaultValue)
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

    private int calculateExpectedPacketBytes(int measurementsPerPacket)
    {
        final int statusBytes = 4;
        final int bytesPerSample = 4 + ((ANZAHL_MESSWERTE - 1) * 4); // slowDataContent + 21 floats
        return statusBytes + (measurementsPerPacket * bytesPerSample);
    }

    @Override
    public void run()
    {
        try {
            clientEinrichten();
            while(connectionValid)
            {
                try
                {   
                    if (this.demoMode == 0){ // normaler Betrieb
                        dataInputStream.readFully(receiveBuffer, 0, expectedPacketBytes);  // BLOCKIERT bis genau ein Paket
                        bytesRead = expectedPacketBytes;
                        lastPacketReadMillis = System.currentTimeMillis();
                        totalPacketsReceived++;
                        totalBytesReceived += bytesRead;
                        lastSuccessfulReadBytes = bytesRead;
                    }
                    sendCommand();  // sofort zuruecksenden!
                    
                    // ------ neu: pendingCommandQueue -------------
                    if (pendingCommandCount > 0)
                    {
                        Long nextCommand = pendingCommandQueue.poll();  // O(1) instead of O(n) with ArrayList.remove(0)
                        if (nextCommand != null) {
                            currentCommand = nextCommand;
                            pendingCommandCount--;
                        }
                    }
                    // ---------------------------------

                    // ################ Werte interpretieren #######################
                    // Use preallocated parseBuffer wrapped around receiveBuffer (avoids 330+ allocations per packet)
                    // parseBuffer is already configured with LITTLE_ENDIAN byte order

                    // Status (first 4 bytes as unsigned int -> long)
                    long status = ((long)(parseBuffer.getInt(0) & 0xFFFFFFFFL));

                    // Zeit & Messwerte - read slowDataContent using absolute getInt
                    final int slowDataOffset = 4;  // starts after status
                    for (int sampleIndex = 0; sampleIndex < ANZAHL_MESSREIHEN_PRO_TCP_PAKET; sampleIndex++)
                    {
                        slowDataContentBuffer[sampleIndex] = ((long)(parseBuffer.getInt(slowDataOffset + sampleIndex * 4) & 0xFFFFFFFFL));
                    }

                    // Read float values using absolute getFloat
                    final int floatDataOffset = 4 + ANZAHL_MESSREIHEN_PRO_TCP_PAKET * 4;
                    final int numFloats = (ANZAHL_MESSWERTE - 1) * ANZAHL_MESSREIHEN_PRO_TCP_PAKET;
                    for (int floatIndex = 0; floatIndex < numFloats; floatIndex++)
                    {
                        cacheBuffer[floatIndex] = parseBuffer.getFloat(floatDataOffset + floatIndex * 4);
                    }

                    // Populate preallocated displayDataBuffer (reused each packet)
                    displayDataBuffer.status = status;
                    for (int sampleIndex = 0; sampleIndex < ANZAHL_MESSREIHEN_PRO_TCP_PAKET; sampleIndex++)
                    {
                        displayDataBuffer.slowDataContent[sampleIndex] = slowDataContentBuffer[sampleIndex];
                    }

                    for (int sampleIndex = 0; sampleIndex < ANZAHL_MESSREIHEN_PRO_TCP_PAKET; sampleIndex++)
                    {
                        for (int valueIndex = 0; valueIndex < (ANZAHL_MESSWERTE - 1); valueIndex++)
                        {
                            float value = cacheBuffer[(ANZAHL_MESSREIHEN_PRO_TCP_PAKET * valueIndex) + sampleIndex];
                            if (valueIndex <= 19) {
                                displayDataBuffer.val[valueIndex][sampleIndex] = value;
                            }
                            else if (valueIndex == 20){
                                displayDataBuffer.slowDataID[sampleIndex] = (int)value;
                            }
                        }
                    }
                    notifyListeners(displayDataBuffer);
                }
                catch (IOException ioException)
                {
                    boolean expectedDisconnect = isExpectedDisconnect(ioException);
                    connectionValid = false;
                    if (!expectedDisconnect) {
                        long disconnectTimestampMillis = System.currentTimeMillis();
                        logger.log(Level.SEVERE, buildDisconnectDiagnostics(ioException, disconnectTimestampMillis), ioException);
                        JOptionPane.showMessageDialog(
                                null,
                                buildDisconnectDialogMessage(ioException, disconnectTimestampMillis),
                                "Exception",
                                JOptionPane.INFORMATION_MESSAGE
                        );
                    } else {
                        logger.fine("Socket closed during disconnect.");
                    }
                    view.getBtnConnect().setEnabled(true);
                    closeSocketQuietly();
                }
                catch (Exception exception)
                {
                    logger.info("general exception -- ");
                    logger.severe(exception.toString());
                    System.out.println("Transmitter: general exception --");
                }
            }
        } finally {
            closeSocketQuietly();
            clientThread = null;
        }
    }
    
    private void closeSocketQuietly()
    {
        Socket currentSocket = socket;
        socket = null;
        if (currentSocket != null) {
            try {
                currentSocket.shutdownInput();
            } catch (IOException ignore) {
            }
            try {
                currentSocket.shutdownOutput();
            } catch (IOException ignore) {
            }
            try {
                currentSocket.close();
            } catch (IOException closeException) {
                if (!isExpectedDisconnect(closeException)) {
                    logger.severe(closeException.toString());
                }
            }
        }
        dataInputStream = null;
        dataOutputStream = null;
        inputStream = null;
        outputStream = null;
        releaseConnectionLock();
    }

    private void clientEinrichten() {
        if (this.demoMode == 0) // normaler Betrieb
        {
            try {
                System.out.println("Open socket to " + ipAddress + ":" + PORT);
                socket = new Socket();
                socket.connect(new java.net.InetSocketAddress(ipAddress, PORT), DEFAULT_SOCKET_TIMEOUT_MS);
                System.out.println("Try autoconnect");
                applyCurrentSocketReadTimeout();
                statusMessage = "Client: Connection established IP: " + socket.getRemoteSocketAddress().toString();
                System.out.println("Connection attempt succeeded: " + socket.getRemoteSocketAddress().toString());
                notifyListeners(null);
                logger.info(statusMessage);
                outputStream = socket.getOutputStream();
                dataOutputStream = new DataOutputStream(outputStream);
                inputStream = socket.getInputStream();
                dataInputStream = new DataInputStream(inputStream);
                connectionStartMillis = System.currentTimeMillis();
                lastPacketReadMillis = 0;
                totalPacketsReceived = 0;
                totalBytesReceived = 0;
                lastSuccessfulReadBytes = 0;
                connectionValid = true;
                disconnectRequested = false;
            } catch (Exception exception) {
                logger.severe(exception.toString());
                connectionValid = false;
                String message = "Connection attempt failed.";
                String exceptionMessage = exception.getMessage();
                if (exceptionMessage != null) {
                    String lowerMessage = exceptionMessage.toLowerCase();
                    if (lowerMessage.contains("timed out")) {
                        message = "Connection attempt timed out. The device may not be ready yet.\nPlease retry with Connect.";
                    } else if (lowerMessage.contains("refused")) {
                        message = "Connection was refused. The device may already be connected by another GUI,\n"
                                + "or it is not ready yet.\nPlease retry with Connect.";
                    } else {
                        message = "Connection attempt failed: " + exceptionMessage + "\nPlease retry with Connect.";
                    }
                } else {
                    message = "Connection attempt failed. The device may not be ready yet.\nPlease retry with Connect.";
                }
                logger.warning(message.replace('\n', ' '));
                System.out.println("Connection attempt failed: " + ipAddress + ":" + PORT + " - " + message.replace('\n', ' '));
                view.getBtnConnect().setEnabled(true);
                closeSocketQuietly();
            }
        }
        else
        {
            try {
            statusMessage = "Client: Connection established IP: DEMO";
            System.out.println("Connection attempt succeeded: DEMO");
            notifyListeners(null);
            logger.info(statusMessage);
            } 
            catch (Exception exception) {
            logger.severe(exception.toString());
            connectionValid = false;
            logger.info("shutdown");
            }
        }
    }


    void startClient(String ipAddress)
    {
        String normalizedIp = ipAddress == null ? "" : ipAddress.trim();
        if (normalizedIp.isEmpty()) {
            normalizedIp = "localhost";
        }
        this.ipAddress = normalizedIp;
        disconnectRequested = false;
        connectionValid = true;
        if (singleInstanceSocketGuardEnabled && !acquireConnectionLock()) {
            String message = "Connection to " + this.ipAddress + ":" + PORT + " is already in use by another JavaScope instance.\n"
                    + "Close the other GUI session (or disconnect there) and retry.";
            logger.warning(message.replace('\n', ' '));
            JOptionPane.showMessageDialog(null, message, "Socket already in use", JOptionPane.INFORMATION_MESSAGE);
            view.getBtnConnect().setEnabled(true);
            return;
        }
        clientThread = null;
        clientThread = new Thread(this);
        clientThread.start();
    }

    public String getEmpfString() {
        return receivedText;
    }
    
    public byte[] getBuf() {
        return receiveBuffer;
    }

    public void addListener(TransmitterListener listener)
    {
        if (listener != null)
        {
            listeners.add(listener);
        }
    }

    public void disconnect()
    {
        disconnectRequested = true;
        connectionValid = false;
        closeSocketQuietly();
        Thread thread = clientThread;
        if (thread != null && thread != Thread.currentThread()) {
            try {
                thread.join(1000);
            } catch (InterruptedException exception) {
                Thread.currentThread().interrupt();
            }
        }
    }

    public void removeListener(TransmitterListener listener)
    {
        if (listener != null)
        {
            listeners.remove(listener);
        }
    }
    
    public void setCommand(long commandValue)
    {
        currentCommand = commandValue;
        pendingCommandQueue.clear();
        pendingCommandCount = 0;
    }

    public void setSuppressZeroCommandReplies(boolean suppress)
    {
        suppressZeroCommandReplies = suppress;
    }

    public void setPrintSentCommandsEnabled(boolean enabled)
    {
        printSentCommands = enabled;
        System.out.println("printSentCommands = " + (enabled ? "1" : "0"));
    }

    public boolean isPrintSentCommandsEnabled()
    {
        return printSentCommands;
    }

    public synchronized boolean setSingleInstanceSocketGuardEnabled(boolean enabled)
    {
        singleInstanceSocketGuardEnabled = enabled;
        if (!enabled) {
            releaseConnectionLock();
            return true;
        }
        Socket currentSocket = socket;
        if (currentSocket != null && currentSocket.isConnected() && !currentSocket.isClosed()) {
            if (!acquireConnectionLock()) {
                singleInstanceSocketGuardEnabled = false;
                return false;
            }
        }
        return true;
    }

    public boolean isSingleInstanceSocketGuardEnabled()
    {
        return singleInstanceSocketGuardEnabled;
    }

    public int getExpectedPacketBytes()
    {
        return expectedPacketBytes;
    }

    public synchronized void setConnectionTimeoutEnabled(boolean enabled)
    {
        connectionTimeoutEnabled = enabled;
        applyCurrentSocketReadTimeout();
    }

    public void sendImmediateZeroCommand()
    {
        if (demoMode != 0 || suppressZeroCommandReplies || !connectionValid) {
            return;
        }
        writeCommandImmediate(0L);
    }
    
    public void setCommandList(ArrayList<Long> commandList)
    {
        pendingCommandQueue.clear();
        pendingCommandQueue.addAll(commandList);
        pendingCommandCount = pendingCommandQueue.size();
    }

    private byte[] longToBytes(long value) {
        byte[] bytes = new byte[] {
                    (byte) value,
                    (byte) (value >> 8),
                    (byte) (value >> 16),
                    (byte) (value >> 24),
                    (byte) (value >> 32),
                    (byte) (value >> 40),
                    (byte) (value >> 48),
                    (byte) (value >> 56)
        };
        return bytes;
    }

    private void sendCommand()
    {
        // Fault injection: drop idle (0x00) replies while enabled.
        if (suppressZeroCommandReplies && currentCommand == 0L) {
            return;
        }

        if (demoMode == 0)
        {
            if (writeCommandImmediate(currentCommand)) {
                currentCommand = 0;
            }
        }
    }

    private boolean writeCommandImmediate(long commandValue)
    {
        DataOutputStream stream = dataOutputStream;
        if (stream == null) {
            return false;
        }

        byte[] commandBytes = longToBytes(commandValue);
        synchronized (commandWriteLock)
        {
            try
            {
                stream.write(commandBytes);
                stream.flush();
                printSentCommand(commandValue);
                return true;
            }
            catch (IOException ioException)
            {
                if (!isExpectedDisconnect(ioException)) {
                    Logger.getLogger(Transmitter.class.getName()).log(Level.SEVERE, null, ioException);
                } else {
                    logger.fine("Ignoring write failure during disconnect.");
                }
                return false;
            }
        }
    }

    private void printSentCommand(long commandValue)
    {
        if (!printSentCommands) {
            return;
        }
        // Suppress idle zero-reply spam in debug output.
        if (commandValue == 0L) {
            return;
        }
        int commandId = (int) (commandValue & 0xFFFFFFFFL);
        int valueBits = (int) ((commandValue >>> 32) & 0xFFFFFFFFL);
        float floatValue = Float.intBitsToFloat(valueBits);
        System.out.println(String.format(
                Locale.US,
                "TX command: raw=0x%016X id=%d valueBits=0x%08X value=%s",
                commandValue,
                commandId,
                valueBits,
                Float.toString(floatValue)
        ));
    }

    private synchronized void applyCurrentSocketReadTimeout()
    {
        Socket currentSocket = socket;
        if (currentSocket == null) {
            return;
        }
        int timeoutMs = connectionTimeoutEnabled ? DEFAULT_SOCKET_TIMEOUT_MS : 0;
        try {
            currentSocket.setSoTimeout(timeoutMs);
        } catch (SocketException exception) {
            logger.fine("Could not apply socket timeout to " + ipAddress + ":" + PORT + ": " + exception.getMessage());
        }
    }

    private boolean isExpectedDisconnect(IOException exception)
    {
        if (disconnectRequested || !connectionValid || socket == null) {
            return true;
        }
        if (exception instanceof SocketException) {
            String message = exception.getMessage();
            if (message != null && message.toLowerCase().contains("socket closed")) {
                return true;
            }
        }
        return false;
    }

    private String buildDisconnectDialogMessage(IOException exception, long disconnectTimestampMillis)
    {
        String reason;
        if (exception instanceof SocketTimeoutException) {
            reason = "socket read timed out";
        } else {
            String exceptionMessage = exception.getMessage();
            reason = (exceptionMessage == null || exceptionMessage.trim().isEmpty())
                    ? exception.getClass().getSimpleName()
                    : exception.getClass().getSimpleName() + ": " + exceptionMessage;
        }
        return "Ethernet connection lost at " + formatTimestamp(disconnectTimestampMillis) + ".\nReason: " + reason + ".";
    }

    private String buildDisconnectDiagnostics(IOException exception, long disconnectTimestampMillis)
    {
        long connectionUptimeMillis = connectionStartMillis > 0 ? disconnectTimestampMillis - connectionStartMillis : -1;
        long silentForMillis = lastPacketReadMillis > 0 ? disconnectTimestampMillis - lastPacketReadMillis : -1;

        String remoteAddress = "n/a";
        String localAddress = "n/a";
        String socketTimeoutMillis = "n/a";
        String keepAlive = "n/a";
        String tcpNoDelay = "n/a";
        Socket currentSocket = socket;
        if (currentSocket != null) {
            remoteAddress = String.valueOf(currentSocket.getRemoteSocketAddress());
            localAddress = String.valueOf(currentSocket.getLocalSocketAddress());
            try {
                socketTimeoutMillis = Integer.toString(currentSocket.getSoTimeout());
            } catch (SocketException ignored) {
            }
            try {
                keepAlive = Boolean.toString(currentSocket.getKeepAlive());
            } catch (SocketException ignored) {
            }
            try {
                tcpNoDelay = Boolean.toString(currentSocket.getTcpNoDelay());
            } catch (SocketException ignored) {
            }
        }

        String exceptionMessage = exception.getMessage();
        if (exceptionMessage == null || exceptionMessage.trim().isEmpty()) {
            exceptionMessage = "<no exception message>";
        }

        return String.format(
                Locale.US,
                "Ethernet connection lost at %s (epochMs=%d) cause=%s: %s, remote=%s, local=%s, " +
                        "soTimeoutMs=%s, keepAlive=%s, tcpNoDelay=%s, expectedPacketBytes=%d, connectionUptimeMs=%d, silentForMs=%d, " +
                        "lastReadBytes=%d, packetsReceived=%d, bytesReceived=%d, pendingCommands=%d, currentCommand=0x%016X, " +
                        "disconnectRequested=%s, thread=%s",
                formatTimestamp(disconnectTimestampMillis),
                disconnectTimestampMillis,
                exception.getClass().getSimpleName(),
                exceptionMessage,
                remoteAddress,
                localAddress,
                socketTimeoutMillis,
                keepAlive,
                tcpNoDelay,
                expectedPacketBytes,
                connectionUptimeMillis,
                silentForMillis,
                lastSuccessfulReadBytes,
                totalPacketsReceived,
                totalBytesReceived,
                pendingCommandCount,
                currentCommand,
                disconnectRequested,
                Thread.currentThread().getName()
        );
    }

    private String formatTimestamp(long epochMillis)
    {
        if (epochMillis <= 0) {
            return "n/a";
        }
        return DIAGNOSTIC_TIME_FORMAT.format(Instant.ofEpochMilli(epochMillis).atZone(DIAGNOSTIC_TIME_ZONE));
    }

    private void notifyListeners(Object payload)
    {
        for (TransmitterListener listener : listeners)
        {
            try
            {
                listener.onTransmitterUpdate(this, payload);
            }
            catch (Exception exception)
            {
                logger.info("Transmitter: exception in notifyListeners -- ");
                logger.severe(exception.toString());
                System.out.println("Transmitter: exception in notifyListeners");
            }
        }
    }

    private synchronized boolean acquireConnectionLock()
    {
        if (demoMode != 0) {
            return true;
        }

        releaseConnectionLock();
        try {
            Path lockDir = Paths.get(System.getProperty("java.io.tmpdir"), "javascope_socket_locks");
            Files.createDirectories(lockDir);
            connectionLockPath = lockDir.resolve(buildConnectionLockFileName(ipAddress));
            connectionLockChannel = FileChannel.open(connectionLockPath, StandardOpenOption.CREATE, StandardOpenOption.WRITE);
            try {
                connectionLock = connectionLockChannel.tryLock();
            } catch (OverlappingFileLockException overlapException) {
                connectionLock = null;
            }
            if (connectionLock == null) {
                if (connectionLockChannel != null) {
                    connectionLockChannel.close();
                }
                connectionLockChannel = null;
                return false;
            }
            return true;
        } catch (IOException exception) {
            logger.warning("Could not create socket lock for " + ipAddress + ":" + PORT + ": " + exception.getMessage());
            releaseConnectionLock();
            return true;
        }
    }

    private synchronized void releaseConnectionLock()
    {
        if (connectionLock != null) {
            try {
                connectionLock.release();
            } catch (IOException ignored) {
            } finally {
                connectionLock = null;
            }
        }
        if (connectionLockChannel != null) {
            try {
                connectionLockChannel.close();
            } catch (IOException ignored) {
            } finally {
                connectionLockChannel = null;
            }
        }
        connectionLockPath = null;
    }

    private String buildConnectionLockFileName(String host)
    {
        String normalizedHost = host == null ? "localhost" : host.trim().toLowerCase(Locale.US);
        if (normalizedHost.isEmpty()) {
            normalizedHost = "localhost";
        }
        normalizedHost = normalizedHost.replaceAll("[^a-z0-9._-]", "_");
        return normalizedHost + "_" + PORT + ".lock";
    }

}
