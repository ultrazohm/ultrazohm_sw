package UZ_GUI;

import java.awt.Component;
import java.awt.Container;
import javax.swing.JTextField;
import javax.swing.text.AbstractDocument;
import javax.swing.text.AttributeSet;
import javax.swing.text.BadLocationException;
import javax.swing.text.DocumentFilter;

/**
 * Converts decimal commas to dots for editable text fields.
 */
public final class DecimalSeparatorSupport
{
    private DecimalSeparatorSupport()
    {
    }

    public static void installOnContainer(Container container)
    {
        if (container == null) {
            return;
        }
        installOnComponent(container);
    }

    private static void installOnComponent(Component component)
    {
        if (component instanceof JTextField) {
            installOnTextField((JTextField) component);
        }
        if (component instanceof Container) {
            for (Component child : ((Container) component).getComponents()) {
                installOnComponent(child);
            }
        }
    }

    private static void installOnTextField(JTextField field)
    {
        if (field == null || !field.isEditable()) {
            return;
        }
        if (!(field.getDocument() instanceof AbstractDocument)) {
            return;
        }
        AbstractDocument document = (AbstractDocument) field.getDocument();
        DocumentFilter existingFilter = document.getDocumentFilter();
        if (existingFilter instanceof CommaToDotDocumentFilter) {
            return;
        }
        document.setDocumentFilter(new CommaToDotDocumentFilter(existingFilter));
        String text = field.getText();
        if (text != null && text.indexOf(',') >= 0) {
            field.setText(text.replace(',', '.'));
        }
    }

    private static final class CommaToDotDocumentFilter extends DocumentFilter
    {
        private final DocumentFilter delegate;

        private CommaToDotDocumentFilter(DocumentFilter delegate)
        {
            this.delegate = delegate;
        }

        private String normalize(String text)
        {
            return text == null ? null : text.replace(',', '.');
        }

        @Override
        public void insertString(FilterBypass fb, int offset, String string, AttributeSet attr) throws BadLocationException
        {
            if (delegate != null) {
                delegate.insertString(fb, offset, normalize(string), attr);
            } else {
                super.insertString(fb, offset, normalize(string), attr);
            }
        }

        @Override
        public void replace(FilterBypass fb, int offset, int length, String text, AttributeSet attrs) throws BadLocationException
        {
            if (delegate != null) {
                delegate.replace(fb, offset, length, normalize(text), attrs);
            } else {
                super.replace(fb, offset, length, normalize(text), attrs);
            }
        }

        @Override
        public void remove(FilterBypass fb, int offset, int length) throws BadLocationException
        {
            if (delegate != null) {
                delegate.remove(fb, offset, length);
            } else {
                super.remove(fb, offset, length);
            }
        }
    }
}
