/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */

package UZ_GUI;

import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

/**
 *
 * @author z002311d
 */
public class ConnectController implements ActionListener
{
    private UZ_GUI_view view;
    private UZ_SCOPE_view viewSCOPE;
    private Transmitter transmitter;

    public ConnectController(UZ_GUI_view view, UZ_SCOPE_view viewSCOPE, Transmitter transmitter)
    {
        this.view = view;
        this.viewSCOPE = viewSCOPE;
        this.transmitter = transmitter;
        this.view.getBtnConnect().addActionListener(this);
        this.view.getTxtIPAdresse().addActionListener(this);
    }

    @Override
    public void actionPerformed(ActionEvent e)
    {
        Object quelle = e.getSource();
        if((quelle == view.getBtnConnect()) || (quelle == view.getTxtIPAdresse()))
        {
            if (!view.getBtnConnect().isEnabled()) {
                return;
            }
            view.getBtnConnect().setEnabled(false);
            transmitter.startClient(view.getTxtIPAdresse().getText());
        }
    }

}
