package UZ_GUI;

import java.io.BufferedReader;
import java.io.File;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

/**
 * Shared parser for javascope.h sections.
 */
public final class JavascopeHeaderParser {

    public enum ParseMode {
        IDENTIFIER,
        COMPACT_TEXT
    }

    public static final class SectionReadResult {
        private final File sourceFile;
        private final ArrayList<String> entries;
        private final int startMarkerCount;
        private final int endMarkerCount;

        SectionReadResult(File sourceFile, ArrayList<String> entries, int startMarkerCount, int endMarkerCount) {
            this.sourceFile = sourceFile;
            this.entries = entries;
            this.startMarkerCount = startMarkerCount;
            this.endMarkerCount = endMarkerCount;
        }

        public File getSourceFile() {
            return sourceFile;
        }

        public ArrayList<String> getEntries() {
            return new ArrayList<>(entries);
        }

        public int getStartMarkerCount() {
            return startMarkerCount;
        }

        public int getEndMarkerCount() {
            return endMarkerCount;
        }
    }

    private JavascopeHeaderParser() {
    }

    public static File resolveHeaderFile() {
        File header = new File("../vitis/software/Baremetal/src/include/javascope.h");
        if (!header.exists()) {
            header = new File("javascope.h");
        }
        return header;
    }

    public static SectionReadResult readSection(String startMarker, String endMarker, ParseMode mode) throws IOException {
        File sourceFile = resolveHeaderFile();
        return readSection(sourceFile, startMarker, endMarker, mode);
    }

    public static SectionReadResult readSection(File sourceFile, String startMarker, String endMarker, ParseMode mode) throws IOException {
        ArrayList<String> entries = new ArrayList<>();
        if (sourceFile == null) {
            return new SectionReadResult(null, entries, 0, 0);
        }

        String normalizedStart = normalizeMarkerToken(startMarker);
        String normalizedEnd = normalizeMarkerToken(endMarker);
        int startMarkerCount = 0;
        int endMarkerCount = 0;
        boolean inSection = false;

        try (BufferedReader reader = new BufferedReader(new FileReader(sourceFile))) {
            String line;
            while ((line = reader.readLine()) != null) {
                String markerCandidate = normalizeMarkerToken(line);

                if (!normalizedStart.isEmpty() && markerCandidate.equals(normalizedStart)) {
                    startMarkerCount++;
                    inSection = true;
                    String startEntry = sanitizeEntry(line, mode);
                    if (!startEntry.isEmpty()) {
                        entries.add(startEntry);
                    }
                    continue;
                }

                if (!normalizedEnd.isEmpty() && markerCandidate.equals(normalizedEnd)) {
                    endMarkerCount++;
                    inSection = false;
                    continue;
                }

                if (!inSection) {
                    continue;
                }

                String entry = sanitizeEntry(line, mode);
                if (!entry.isEmpty()) {
                    entries.add(entry);
                }
            }
        }

        return new SectionReadResult(sourceFile, entries, startMarkerCount, endMarkerCount);
    }

    private static String sanitizeEntry(String rawLine, ParseMode mode) {
        String token = stripInlineComments(rawLine).trim();
        if (token.isEmpty()) {
            return "";
        }

        token = removeTrailingDelimiters(token);

        if (mode == ParseMode.IDENTIFIER) {
            token = token.replaceAll("\\s+", "");
            int assignmentIndex = token.indexOf('=');
            if (assignmentIndex >= 0) {
                token = token.substring(0, assignmentIndex);
            }
            token = removeTrailingDelimiters(token);
            return token;
        }

        token = token.replaceAll("\\s+", "");
        token = token.replace("=0", "");
        token = removeTrailingDelimiters(token);
        return token;
    }

    private static String normalizeMarkerToken(String rawLine) {
        String token = stripInlineComments(rawLine).trim();
        if (token.isEmpty()) {
            return "";
        }
        token = removeTrailingDelimiters(token);
        token = token.replaceAll("\\s+", "");
        return token;
    }

    private static String stripInlineComments(String rawLine) {
        if (rawLine == null) {
            return "";
        }

        String token = rawLine;
        int lineCommentIndex = token.indexOf("//");
        if (lineCommentIndex >= 0) {
            token = token.substring(0, lineCommentIndex);
        }

        while (true) {
            int blockStart = token.indexOf("/*");
            if (blockStart < 0) {
                break;
            }
            int blockEnd = token.indexOf("*/", blockStart + 2);
            if (blockEnd < 0) {
                token = token.substring(0, blockStart);
                break;
            }
            token = token.substring(0, blockStart) + token.substring(blockEnd + 2);
        }

        return token;
    }

    private static String removeTrailingDelimiters(String token) {
        if (token == null) {
            return "";
        }
        String result = token.trim();
        while (!result.isEmpty()) {
            char tail = result.charAt(result.length() - 1);
            if (tail == ',' || tail == ';') {
                result = result.substring(0, result.length() - 1).trim();
            } else {
                break;
            }
        }
        return result;
    }
}
