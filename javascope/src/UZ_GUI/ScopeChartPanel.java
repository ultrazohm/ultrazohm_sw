package UZ_GUI;

import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;

/**
 * ChartPanel extension that exposes hooks for axis auto-reset actions
 * (popup reset and mouse drag reset paths).
 */
public class ScopeChartPanel extends ChartPanel {
    private transient Runnable domainResetHook;

    public ScopeChartPanel(JFreeChart chart) {
        super(chart);
    }

    public void setDomainResetHook(Runnable domainResetHook) {
        this.domainResetHook = domainResetHook;
    }

    @Override
    public void restoreAutoBounds() {
        super.restoreAutoBounds();
        runDomainResetHook();
    }

    @Override
    public void restoreAutoDomainBounds() {
        super.restoreAutoDomainBounds();
        runDomainResetHook();
    }

    private void runDomainResetHook() {
        if (domainResetHook != null) {
            domainResetHook.run();
        }
    }
}
