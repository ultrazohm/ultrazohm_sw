package UZ_GUI;

import java.io.IOException;
import java.nio.charset.StandardCharsets;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Resolves properties keys to source line numbers in properties.ini and prints
 * user-facing parse diagnostics to stderr.
 */
final class PropertyFileDiagnostics {

    private static final String DEFAULT_PROPERTIES_FILE = "properties.ini";

    private final Path path;
    private final Map<String, LineInfo> lineInfos;

    private static final class LineInfo {
        final int lineNumber;
        final String lineText;

        LineInfo(int lineNumber, String lineText) {
            this.lineNumber = lineNumber;
            this.lineText = lineText;
        }
    }

    private PropertyFileDiagnostics(Path path, Map<String, LineInfo> lineInfos) {
        this.path = path;
        this.lineInfos = lineInfos;
    }

    static PropertyFileDiagnostics loadDefault() {
        return load(Paths.get(DEFAULT_PROPERTIES_FILE));
    }

    static PropertyFileDiagnostics load(Path path) {
        Map<String, LineInfo> infos = new HashMap<String, LineInfo>();
        try {
            List<String> lines = Files.readAllLines(path, StandardCharsets.UTF_8);
            for (int i = 0; i < lines.size(); i++) {
                String key = extractKey(lines.get(i));
                if (key != null && !infos.containsKey(key)) {
                    infos.put(key, new LineInfo(i + 1, lines.get(i)));
                }
            }
        } catch (IOException ignored) {
            // Diagnostics are best effort; parsing should still continue.
        }
        return new PropertyFileDiagnostics(path, infos);
    }

    void printInvalidScalar(String key, String invalidValue, String expected, String fallbackValue) {
        String detail = "Invalid value for key '" + key + "': " + quote(invalidValue)
                + ". Expected " + expected + ". Using fallback " + fallbackValue + ".";
        print(key, detail);
    }

    void printInvalidListEntry(String key, int oneBasedEntryIndex, String invalidValue, String expected, String fallbackValue) {
        String detail = "Invalid value for key '" + key + "', entry " + oneBasedEntryIndex + ": "
                + quote(invalidValue) + ". Expected " + expected + ". Using fallback " + fallbackValue + ".";
        print(key, detail);
    }

    void printValidationIssue(String key, String detail) {
        print(key, detail);
    }

    private void print(String key, String detail) {
        LineInfo info = lineInfos.get(key);
        String location;
        if (info == null) {
            location = path.getFileName().toString() + ":?";
        } else {
            location = path.getFileName().toString() + ":" + info.lineNumber;
        }

        StringBuilder message = new StringBuilder();
        message.append("[properties] ").append(location).append(" ").append(detail);
        if (info != null) {
            message.append(" Source: ").append(info.lineText.trim());
        }
        System.err.println(message.toString());
    }

    private static String quote(String value) {
        if (value == null) {
            return "<null>";
        }
        return "\"" + value.trim() + "\"";
    }

    private static String extractKey(String line) {
        if (line == null) {
            return null;
        }
        String trimmed = line.trim();
        if (trimmed.isEmpty() || trimmed.startsWith("#") || trimmed.startsWith("!")) {
            return null;
        }

        int separator = findKeyValueSeparator(line);
        if (separator <= 0) {
            return null;
        }

        String key = line.substring(0, separator).trim();
        if (key.isEmpty() || key.startsWith("#") || key.startsWith("!")) {
            return null;
        }
        return key;
    }

    private static int findKeyValueSeparator(String line) {
        boolean escaping = false;
        for (int i = 0; i < line.length(); i++) {
            char c = line.charAt(i);
            if (escaping) {
                escaping = false;
                continue;
            }
            if (c == '\\') {
                escaping = true;
                continue;
            }
            if (c == '=' || c == ':') {
                return i;
            }
        }
        return -1;
    }
}
