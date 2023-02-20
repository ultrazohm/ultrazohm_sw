
library ieee;
use ieee.std_logic_1164.all;
use ieee.numeric_std.all;



package syn_functions_pkg is

    -----------------------------------------------
    -- Useful types and functions from VHDL 2008 --
    -----------------------------------------------

    type boolean_vector         is array (natural range <>) of boolean;
    type integer_vector         is array (natural range <>) of integer;
    type natural_vector         is array (natural range <>) of natural;
    type positive_vector        is array (natural range <>) of positive;
    type real_vector            is array (natural range <>) of real;
    type time_vector            is array (natural range <>) of time;

    function "sla"
    (
        arg     : unsigned;
        count   : integer
    )
    return unsigned;

    function "sla"
    (
        arg     : signed;
        count   : integer
    )
    return signed;

    function "sra"
    (
        arg     : unsigned;
        count   : integer
    )
    return unsigned;

    function "sra"
    (
        arg     : signed;
        count   : integer
    )
    return signed;



    ---------------
    -- Frequency --
    ---------------

    type frequency is range 0 to integer'high
    units
        Hz;             -- Hertz
        kHz = 1000 Hz;  -- Kilohertz
        MHz = 1000 KHz; -- Megahertz
        GHz = 1000 MHz; -- Gigahertz
    end units;

    function to_integer
    (
        f : frequency
    )
    return integer;

    function to_frequency
    (
        i : integer
    )
    return frequency;

    function frequency_to_period
    (
        f : frequency
    )
    return time;

    function period_to_frequency
    (
        t : time
    )
    return frequency;



    -----------------------------------------
    -- Other array types missing from VHDL --
    -----------------------------------------

    type severity_level_vector      is array (natural range <>) of severity_level;
    type file_open_kind_vector      is array (natural range <>) of file_open_kind;
    type file_open_status_vector    is array (natural range <>) of file_open_status;
    type delay_length_vector        is array (natural range <>) of delay_length;
    type frequency_vector           is array (natural range <>) of frequency;



    -----------------------------
    -- Conditional expressions --
    -----------------------------

    function if_then_else
    (
        condition   : boolean;
        when_true   : boolean;
        when_false  : boolean
    )
    return boolean;

    function if_then_else
    (
        condition   : boolean;
        when_true   : bit;
        when_false  : bit
    )
    return bit;

    function if_then_else
    (
        condition   : boolean;
        when_true   : character;
        when_false  : character
    )
    return character;

    function if_then_else
    (
        condition   : boolean;
        when_true   : severity_level;
        when_false  : severity_level
    )
    return severity_level;

    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_kind;
        when_false  : file_open_kind
    )
    return file_open_kind;

    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_status;
        when_false  : file_open_status
    )
    return file_open_status;

    function if_then_else
    (
        condition   : boolean;
        when_true   : real;
        when_false  : real
    )
    return real;

    function if_then_else
    (
        condition   : boolean;
        when_true   : integer;
        when_false  : integer
    )
    return integer;

    function if_then_else
    (
        condition   : boolean;
        when_true   : time;
        when_false  : time
    )
    return time;

    function if_then_else
    (
        condition   : boolean;
        when_true   : frequency;
        when_false  : frequency
    )
    return frequency;

    function if_then_else
    (
        condition   : boolean;
        when_true   : std_logic;
        when_false  : std_logic
    )
    return std_logic;

    function if_then_else
    (
        condition   : boolean;
        when_true   : boolean_vector;
        when_false  : boolean_vector
    )
    return boolean_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : bit_vector;
        when_false  : bit_vector
    )
    return bit_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : string;
        when_false  : string
    )
    return string;

    function if_then_else
    (
        condition   : boolean;
        when_true   : severity_level_vector;
        when_false  : severity_level_vector
    )
    return severity_level_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_kind_vector;
        when_false  : file_open_kind_vector
    )
    return file_open_kind_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_status_vector;
        when_false  : file_open_status_vector
    )
    return file_open_status_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : real_vector;
        when_false  : real_vector
    )
    return real_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : integer_vector;
        when_false  : integer_vector
    )
    return integer_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : time_vector;
        when_false  : time_vector
    )
    return time_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : frequency_vector;
        when_false  : frequency_vector
    )
    return frequency_vector;

    function if_then_else
    (
        condition   : boolean;
        when_true   : std_logic_vector;
        when_false  : std_logic_vector
    )
    return std_logic_vector;



    ------------------------
    -- Math log2 function --
    ------------------------

    function floor_log2
    (
        n : natural
    )
    return integer;

    function ceil_log2
    (
        n : natural
    )
    return integer;

    function pos_ceil_log2
    (
        n : natural
    )
    return integer;

    function log2
    (
        n : natural
    )
    return integer;



    ------------------------
    -- Math log3 function --
    ------------------------

    function floor_log3
    (
        n : natural
    )
    return integer;

    function ceil_log3
    (
        n : natural
    )
    return integer;

    function pos_ceil_log3
    (
        n : natural
    )
    return integer;

    function log3
    (
        n : natural
    )
    return integer;



    ---------------------------
    -- Min and max functions --
    ---------------------------

    function min
    (
        n1 : integer;
        n2 : integer
    )
    return integer;

    function min
    (
        values : integer_vector
    )
    return integer;

    function max
    (
        n1 : integer;
        n2 : integer
    )
    return integer;

    function max
    (
        values : integer_vector
    )
    return integer;



    function min
    (
        x1 : real;
        x2 : real
    )
    return real;

    function min
    (
        values : real_vector
    )
    return real;

    function max
    (
        x1 : real;
        x2 : real
    )
    return real;

    function max
    (
        values : real_vector
    )
    return real;



    function min
    (
        t1 : time;
        t2 : time
    )
    return time;

    function min
    (
        values : time_vector
    )
    return time;

    function max
    (
        t1 : time;
        t2 : time
    )
    return time;

    function max
    (
        values : time_vector
    )
    return time;



    function min
    (
        t1 : frequency;
        t2 : frequency
    )
    return frequency;

    function min
    (
        values : frequency_vector
    )
    return frequency;

    function max
    (
        t1 : frequency;
        t2 : frequency
    )
    return frequency;

    function max
    (
        values : frequency_vector
    )
    return frequency;



    ----------------------
    -- Reverse function --
    ----------------------

    function reverse
    (
        vector          : std_logic_vector;
        symbol_width    : positive
    )
    return std_logic_vector;



    ---------------------
    -- Repeat function --
    ---------------------

    function repeat
    (
        vector  : boolean_vector;
        n       : natural
    )
    return boolean_vector;


    function repeat
    (
        vector  : integer_vector;
        n       : natural
    )
    return integer_vector;


    function repeat
    (
        vector  : natural_vector;
        n       : natural
    )
    return natural_vector;


    function repeat
    (
        vector  : positive_vector;
        n       : natural
    )
    return positive_vector;


    function repeat
    (
        vector  : real_vector;
        n       : natural
    )
    return real_vector;


    function repeat
    (
        vector  : time_vector;
        n       : natural
    )
    return time_vector;


    function repeat
    (
        vector  : severity_level_vector;
        n       : natural
    )
    return severity_level_vector;


    function repeat
    (
        vector  : file_open_kind_vector;
        n       : natural
    )
    return file_open_kind_vector;


    function repeat
    (
        vector  : file_open_status_vector;
        n       : natural
    )
    return file_open_status_vector;


    function repeat
    (
        vector  : delay_length_vector;
        n       : natural
    )
    return delay_length_vector;


    function repeat
    (
        vector  : frequency_vector;
        n       : natural
    )
    return frequency_vector;


    function repeat
    (
        vector  : bit_vector;
        n       : natural
    )
    return bit_vector;


    function repeat
    (
        vector  : string;
        n       : natural
    )
    return string;


    function repeat
    (
        vector  : std_logic_vector;
        n       : natural
    )
    return std_logic_vector;



    -------------------
    -- Pad functions --
    -------------------

    function left_pad
    (
        vector  : std_logic_vector;
        width   : natural;
        pad_bit : std_logic := '0'
    )
    return std_logic_vector;

    function right_pad
    (
        vector  : std_logic_vector;
        width   : natural;
        pad_bit : std_logic := '0'
    )
    return std_logic_vector;



end package syn_functions_pkg;



package body syn_functions_pkg is

    -----------------------------------------------
    -- Useful types and functions from VHDL 2008 --
    -----------------------------------------------

    function "sla"
    (
        arg     : unsigned;
        count   : integer
    )
    return unsigned is
    begin
        if (count >= 0) then
            return shift_left(arg, count);
        else
            return shift_right(arg, -count);
        end if;
    end function "sla";

    function "sla"
    (
        arg     : signed;
        count   : integer
    )
    return signed is
    begin
        if (count >= 0) then
            return shift_left(arg, count);
        else
            return shift_right(arg, -count);
        end if;
    end function "sla";

    function "sra"
    (
        arg     : unsigned;
        count   : integer
    )
    return unsigned is
    begin
        if (count >= 0) then
            return shift_right(arg, count);
        else
            return shift_left(arg, -count);
        end if;
    end function "sra";

    function "sra"
    (
        arg     : signed;
        count   : integer
    )
    return signed is
    begin
        if (count >= 0) then
            return shift_right(arg, count);
        else
            return shift_left(arg, -count);
        end if;
    end function "sra";



    ---------------
    -- Frequency --
    ---------------

    function to_integer
    (
        f : frequency
    )
    return integer is
    begin
        return (f / (1 Hz));
    end function to_integer;

    function to_frequency
    (
        i : integer
    )
    return frequency is
    begin
        return (i * (1 Hz));
    end function to_frequency;

    function frequency_to_period
    (
        f : frequency
    )
    return time is
    begin
        return ((1 sec) / to_integer(f));
    end function frequency_to_period;

    function period_to_frequency
    (
        t : time
    )
    return frequency is
    begin
        return (((1 sec) / t) * (1 Hz));
    end function period_to_frequency;



    -----------------------------
    -- Conditional expressions --
    -----------------------------

    function if_then_else
    (
        condition   : boolean;
        when_true   : boolean;
        when_false  : boolean
    )
    return boolean is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : bit;
        when_false  : bit
    )
    return bit is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : character;
        when_false  : character
    )
    return character is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : severity_level;
        when_false  : severity_level
    )
    return severity_level is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_kind;
        when_false  : file_open_kind
    )
    return file_open_kind is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_status;
        when_false  : file_open_status
    )
    return file_open_status is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : real;
        when_false  : real
    )
    return real is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : integer;
        when_false  : integer
    )
    return integer is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : time;
        when_false  : time
    )
    return time is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : frequency;
        when_false  : frequency
    )
    return frequency is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : std_logic;
        when_false  : std_logic
    )
    return std_logic is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : boolean_vector;
        when_false  : boolean_vector
    )
    return boolean_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : bit_vector;
        when_false  : bit_vector
    )
    return bit_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : string;
        when_false  : string
    )
    return string is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : severity_level_vector;
        when_false  : severity_level_vector
    )
    return severity_level_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_kind_vector;
        when_false  : file_open_kind_vector
    )
    return file_open_kind_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : file_open_status_vector;
        when_false  : file_open_status_vector
    )
    return file_open_status_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : real_vector;
        when_false  : real_vector
    )
    return real_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : integer_vector;
        when_false  : integer_vector
    )
    return integer_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : time_vector;
        when_false  : time_vector
    )
    return time_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : frequency_vector;
        when_false  : frequency_vector
    )
    return frequency_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    function if_then_else
    (
        condition   : boolean;
        when_true   : std_logic_vector;
        when_false  : std_logic_vector
    )
    return std_logic_vector is
    begin
        if condition then
            return when_true;
        else
            return when_false;
        end if;
    end function if_then_else;



    -------------------------
    -- Math log2 functions --
    -------------------------

    function floor_log2
    (
        n : natural
    )
    return integer is
    begin
        for res in 0 to 31 loop
            if (((2 ** res) = n) or ((2 ** (res + 1)) > n)) then
                return res;
            end if;
        end loop;
        report "floor_log2: unexpected_error"
        severity failure;
        return -1;
    end function floor_log2;

    function ceil_log2
    (
        n : natural
    )
    return integer is
    begin
        for res in 0 to 31 loop
            if ((2 ** res) >= n) then
                return res;
            end if;
        end loop;
        report "ceil_log2: unexpected_error"
        severity failure;
        return -1;
    end function ceil_log2;

    function pos_ceil_log2
    (
        n : natural
    )
    return integer is
    begin
        return max(1, ceil_log2(n));
    end function pos_ceil_log2;

    function log2
    (
        n : natural
    )
    return integer is
    begin
        assert (floor_log2(n) = ceil_log2(n))
        report "log2: n is not a power of 2"
        severity failure;
        return floor_log2(n);
    end function log2;



    -------------------------
    -- Math log3 functions --
    -------------------------

    function floor_log3
    (
        n : natural
    )
    return integer is
    begin
        for res in 0 to 31 loop
            if (((3 ** res) = n) or ((3 ** (res + 1)) > n)) then
                return res;
            end if;
        end loop;
        report "floor_log3: unexpected_error"
        severity failure;
        return -1;
    end function floor_log3;

    function ceil_log3
    (
        n : natural
    )
    return integer is
    begin
        for res in 0 to 31 loop
            if ((3 ** res) >= n) then
                return res;
            end if;
        end loop;
        report "ceil_log3: unexpected_error"
        severity failure;
        return -1;
    end function ceil_log3;

    function pos_ceil_log3
    (
        n : natural
    )
    return integer is
    begin
        return max(1, ceil_log3(n));
    end function pos_ceil_log3;

    function log3
    (
        n : natural
    )
    return integer is
    begin
        assert (floor_log3(n) = ceil_log3(n))
        report "log3: n is not a power of 3"
        severity failure;
        return floor_log3(n);
    end function log3;



    ---------------------------
    -- Min and max functions --
    ---------------------------

    function min
    (
        n1 : integer;
        n2 : integer
    )
    return integer is
    begin
        if (n1 < n2) then
            return n1;
        else
            return n2;
        end if;
    end function min;

    function min
    (
        values : integer_vector
    )
    return integer is
        variable min : integer;
    begin
        min := values(values'left);
        for i in values'range loop
            if (values(i) < min) then
                min := values(i);
            end if;
        end loop;
        return min;
    end function min;

    function max
    (
        n1 : integer;
        n2 : integer
    )
    return integer is
    begin
        if (n1 > n2) then
            return n1;
        else
            return n2;
        end if;
    end function max;

    function max
    (
        values : integer_vector
    )
    return integer is
        variable max : integer;
    begin
        max := values(values'left);
        for i in values'range loop
            if (values(i) > max) then
                max := values(i);
            end if;
        end loop;
        return max;
    end function max;

    function min
    (
        x1 : real;
        x2 : real
    )
    return real is
    begin
        if (x1 < x2) then
            return x1;
        else
            return x2;
        end if;
    end function min;

    function min
    (
        values : real_vector
    )
    return real is
        variable min : real;
    begin
        min := values(values'left);
        for i in values'range loop
            if (values(i) < min) then
                min := values(i);
            end if;
        end loop;
        return min;
    end function min;

    function max
    (
        x1 : real;
        x2 : real
    )
    return real is
    begin
        if (x1 > x2) then
            return x1;
        else
            return x2;
        end if;
    end function max;

    function max
    (
        values : real_vector
    )
    return real is
        variable max : real;
    begin
        max := values(values'left);
        for i in values'range loop
            if (values(i) > max) then
                max := values(i);
            end if;
        end loop;
        return max;
    end function max;

    function min
    (
        t1 : time;
        t2 : time
    )
    return time is
    begin
        if (t1 < t2) then
            return t1;
        else
            return t2;
        end if;
    end function min;

    function min
    (
        values : time_vector
    )
    return time is
        variable min : time;
    begin
        min := values(values'left);
        for i in values'range loop
            if (values(i) < min) then
                min := values(i);
            end if;
        end loop;
        return min;
    end function min;

    function max
    (
        t1 : time;
        t2 : time
    )
    return time is
    begin
        if (t1 > t2) then
            return t1;
        else
            return t2;
        end if;
    end function max;

    function max
    (
        values : time_vector
    )
    return time is
        variable max : time;
    begin
        max := values(values'left);
        for i in values'range loop
            if (values(i) > max) then
                max := values(i);
            end if;
        end loop;
        return max;
    end function max;

    function min
    (
        t1 : frequency;
        t2 : frequency
    )
    return frequency is
    begin
        if (t1 < t2) then
            return t1;
        else
            return t2;
        end if;
    end function min;

    function min
    (
        values : frequency_vector
    )
    return frequency is
        variable min : frequency;
    begin
        min := values(values'left);
        for i in values'range loop
            if (values(i) < min) then
                min := values(i);
            end if;
        end loop;
        return min;
    end function min;

    function max
    (
        t1 : frequency;
        t2 : frequency
    )
    return frequency is
    begin
        if (t1 > t2) then
            return t1;
        else
            return t2;
        end if;
    end function max;

    function max
    (
        values : frequency_vector
    )
    return frequency is
        variable max : frequency;
    begin
        max := values(values'left);
        for i in values'range loop
            if (values(i) > max) then
                max := values(i);
            end if;
        end loop;
        return max;
    end function max;



    ----------------------
    -- Reverse function --
    ----------------------

    function reverse
    (
        vector          : std_logic_vector;
        symbol_width    : positive
    )
    return std_logic_vector is

        variable var_vector : std_logic_vector((vector'length - 1) downto 0);   -- Copy of vector, but we know exactly the range
        variable var_result : std_logic_vector((vector'length - 1) downto 0);   -- Result of symbol reversing
        variable result     : std_logic_vector(vector'range);                   -- Result, but with the same range as input vector

        variable nb_symbols : positive;

    begin

        assert ((vector'length mod symbol_width) = 0)
        report "vector width (" & positive'image(vector'length) & ") is not a multiple of symbol width (" & positive'image(symbol_width) & ")"
        severity error;

        nb_symbols := (vector'length / symbol_width);

        -- Work on var_vector instead of vector because we know its range
        var_vector := vector;

        -- Symbols switching
        for i in 0 to (nb_symbols - 1) loop
            var_result(((symbol_width * (i + 1)) - 1) downto (symbol_width * i)) := var_vector(((symbol_width * (nb_symbols - i)) - 1) downto (symbol_width * (nb_symbols - 1 - i)));
        end loop;

        -- Return result instead of var_result because it has the same range as vector
        result := var_result;

        return result;

    end function reverse;



    ---------------------
    -- Repeat function --
    ---------------------

    function repeat
    (
        vector  : boolean_vector;
        n       : natural
    )
    return boolean_vector is
        constant length : natural   := vector'length;

        variable result : boolean_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : integer_vector;
        n       : natural
    )
    return integer_vector is
        constant length : natural   := vector'length;

        variable result : integer_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : natural_vector;
        n       : natural
    )
    return natural_vector is
        constant length : natural   := vector'length;

        variable result : natural_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : positive_vector;
        n       : natural
    )
    return positive_vector is
        constant length : natural   := vector'length;

        variable result : positive_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : real_vector;
        n       : natural
    )
    return real_vector is
        constant length : natural   := vector'length;

        variable result : real_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : time_vector;
        n       : natural
    )
    return time_vector is
        constant length : natural   := vector'length;

        variable result : time_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : severity_level_vector;
        n       : natural
    )
    return severity_level_vector is
        constant length : natural   := vector'length;

        variable result : severity_level_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : file_open_kind_vector;
        n       : natural
    )
    return file_open_kind_vector is
        constant length : natural   := vector'length;

        variable result : file_open_kind_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : file_open_status_vector;
        n       : natural
    )
    return file_open_status_vector is
        constant length : natural   := vector'length;

        variable result : file_open_status_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : delay_length_vector;
        n       : natural
    )
    return delay_length_vector is
        constant length : natural   := vector'length;

        variable result : delay_length_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : frequency_vector;
        n       : natural
    )
    return frequency_vector is
        constant length : natural   := vector'length;

        variable result : frequency_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : bit_vector;
        n       : natural
    )
    return bit_vector is
        constant length : natural   := vector'length;

        variable result : bit_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : string;
        n       : natural
    )
    return string is
        constant length : natural   := vector'length;

        variable result : string(1 to (length * n));
    begin
        for i in 1 to (n - 1) loop
            result(((i * length) + 1) to ((i + 1) * length)) := vector;
        end loop;

        return result;
    end function repeat;


    function repeat
    (
        vector  : std_logic_vector;
        n       : natural
    )
    return std_logic_vector is
        constant length : natural   := vector'length;

        variable result : std_logic_vector(0 to ((length * n) - 1));
    begin
        for i in 0 to (n - 1) loop
            result((i * length) to (((i + 1) * length) - 1)) := vector;
        end loop;

        return result;
    end function repeat;



    -------------------
    -- Pad functions --
    -------------------

    function left_pad
    (
        vector  : std_logic_vector;
        width   : natural;
        pad_bit : std_logic := '0'
    )
    return std_logic_vector is
        variable    pad_width   : natural   := max(0, (width - vector'length));
    begin
        return (1 to pad_width => pad_bit) & vector;
    end function left_pad;

    function right_pad
    (
        vector  : std_logic_vector;
        width   : natural;
        pad_bit : std_logic := '0'
    )
    return std_logic_vector is
        variable    pad_width   : natural   := max(0, (width - vector'length));
    begin
        return vector & (1 to pad_width => pad_bit);
    end function right_pad;



end package body syn_functions_pkg;



