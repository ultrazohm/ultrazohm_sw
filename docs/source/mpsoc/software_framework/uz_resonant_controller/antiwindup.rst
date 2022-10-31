Saturation and Anti-Windup
--------------------------
The output of the controller is limited by the input values ``upper_limit`` and ``lower_limit``.
As an anti-windup strategy the back calculation method is used.
The gain of the anti-windup feedback is given by the input value ``antiwindup_gain``.
To disable the anti-windup strategy the feedback can be set to 0.